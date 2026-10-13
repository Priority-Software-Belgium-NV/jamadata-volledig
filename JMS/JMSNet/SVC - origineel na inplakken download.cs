using System;
using System.Collections.Generic;
using System.Security.Cryptography.X509Certificates;
using System.Linq;
using System.Text;
using System.Net;
using System.IO;
using System.Xml;
using System.Xml.Linq;
using Newtonsoft.Json;
using Renci.SshNet;
using Renci.SshNet.Sftp;
using Newtonsoft.Json.Linq;




using System.Net.Http;
using System.Net.Http.Headers;
using System.Threading.Tasks;

namespace PeppolDownloadSample
{
  class Program
  {
    // ==== CONFIG (VUL DIT IN) ====
    private const string ClientId = "TODO-CLIENT-ID";
    private const string ClientSecret = "TODO-CLIENT-SECRET";

    private const string ClientCertPath = @"C:\certs\ibanity-client.pfx";
    private const string ClientCertPassword = "TODO-PFX-PASSWORD";

    private const string PreferredDocumentId = ""; // bv. "c784b3f2-...."
    private const string OutputFolder = @"C:\temp\peppol";
    private const string BaseUrl = "https://api.ibanity.com/einvoicing";
    // ==============================

    static void Main(string[] args)
    {
      try
      {
        Directory.CreateDirectory(OutputFolder);

        // In .NET Framework stel je TLS & CRL zo in (globaal):
        ServicePointManager.SecurityProtocol = SecurityProtocolType.Tls12;
        ServicePointManager.CheckCertificateRevocationList = true;

        Run().GetAwaiter().GetResult();
        Console.WriteLine("Klaar.");
      }
      catch (Exception ex)
      {
        Console.Error.WriteLine(ex);
      }
    }

    private static async Task Run()
    {
      // HttpClient met clientcertificaat (mTLS) – WebRequestHandler in .NET Framework 4.x
      var handler = new WebRequestHandler();

      var cert = new X509Certificate2(
          ClientCertPath,
          ClientCertPassword,
          X509KeyStorageFlags.MachineKeySet | X509KeyStorageFlags.Exportable
      );

      handler.ClientCertificates.Add(cert);

      using (var http = new HttpClient(handler) { Timeout = TimeSpan.FromSeconds(60) })
      {
        // 1) OAuth2 client credentials
        var token = await GetAccessToken(http);
        Console.WriteLine("Access token verkregen.");

        // 2) Lijst inkomende Peppol-documenten
        var listEndpoint = $"{BaseUrl}/peppol/inbound/documents";
        var listJson = await GetJson(http, token, listEndpoint);
        var docId = ResolveDocumentId(listJson, PreferredDocumentId);

        if (string.IsNullOrWhiteSpace(docId))
        {
          Console.WriteLine("Geen inkomende documenten gevonden.");
          return;
        }

        Console.WriteLine("Te downloaden documentId: " + docId);

        // 3) Document downloaden
        var getEndpoint = $"{BaseUrl}/peppol/inbound/documents/{docId}";
        await DownloadInboundDocument(http, token, getEndpoint);
      }
    }

    private static async Task<string> GetAccessToken(HttpClient http)
    {
      var tokenEndpoint = $"{BaseUrl}/oauth2/token";

      var basic = Convert.ToBase64String(Encoding.UTF8.GetBytes($"{ClientId}:{ClientSecret}"));
      var req = new HttpRequestMessage(HttpMethod.Post, tokenEndpoint);
      req.Headers.Authorization = new AuthenticationHeaderValue("Basic", basic);
      req.Content = new StringContent("grant_type=client_credentials", Encoding.UTF8, "application/x-www-form-urlencoded");

      using (var resp = await http.SendAsync(req))
      {
        var body = await resp.Content.ReadAsStringAsync();
        if (!resp.IsSuccessStatusCode)
          throw new InvalidOperationException($"Token aanvraag faalde ({resp.StatusCode}): {body}");

        var json = JObject.Parse(body);
        return json.Value<string>("access_token");
      }
    }

    private static async Task<JObject> GetJson(HttpClient http, string token, string url)
    {
      var req = new HttpRequestMessage(HttpMethod.Get, url);
      req.Headers.Authorization = new AuthenticationHeaderValue("Bearer", token);
      req.Headers.Accept.Add(new MediaTypeWithQualityHeaderValue("application/vnd.api+json"));

      using (var resp = await http.SendAsync(req))
      {
        var body = await resp.Content.ReadAsStringAsync();
        if (!resp.IsSuccessStatusCode)
          throw new InvalidOperationException($"GET {url} faalde ({resp.StatusCode}): {body}");

        return JObject.Parse(body);
      }
    }

    private static string ResolveDocumentId(JObject listJson, string preferred)
    {
      if (!string.IsNullOrWhiteSpace(preferred))
        return preferred;

      var data = listJson["data"] as JArray;
      if (data == null || data.Count == 0) return null;

      return data[0].Value<string>("id");
    }

    private static async Task DownloadInboundDocument(HttpClient http, string token, string getEndpoint)
    {
      var req = new HttpRequestMessage(HttpMethod.Get, getEndpoint);
      req.Headers.Authorization = new AuthenticationHeaderValue("Bearer", token);
      req.Headers.Accept.Add(new MediaTypeWithQualityHeaderValue("application/vnd.api+json"));

      using (var resp = await http.SendAsync(req))
      {
        var contentBytes = await resp.Content.ReadAsByteArrayAsync();
        var contentType = resp.Content.Headers.ContentType?.MediaType ?? "application/octet-stream";

        if (!resp.IsSuccessStatusCode)
        {
          var errorText = Encoding.UTF8.GetString(contentBytes);
          throw new InvalidOperationException($"GET {getEndpoint} faalde ({resp.StatusCode}): {errorText}");
        }

        // Probeer JSON (base64-payload); anders schrijf binaire content
        JObject json = null;
        try { json = JObject.Parse(Encoding.UTF8.GetString(contentBytes)); } catch { /* geen JSON */ }

        if (json != null && json["data"] != null)
        {
          var attributes = json["data"]["attributes"] as JObject;
          if (attributes == null)
            throw new InvalidOperationException("Onverwacht JSON-formaat: geen attributes gevonden.");

          var fileName = attributes.Value<string>("fileName");
          var attrContentType = attributes.Value<string>("contentType");
          var base64 = attributes.Value<string>("content");

          if (string.IsNullOrEmpty(base64))
            throw new InvalidOperationException("Geen 'content' gevonden in attributes (base64 verwacht).");

          var fileBytes = Convert.FromBase64String(base64);
          if (string.IsNullOrEmpty(fileName))
            fileName = GuessFileName(attrContentType);

          var path = Path.Combine(OutputFolder, fileName);
          File.WriteAllBytes(path, fileBytes);
          Console.WriteLine($"Document opgeslagen: {path} ({attrContentType})");
        }
        else
        {
          var fileName = GuessFileName(contentType);
          var path = Path.Combine(OutputFolder, fileName);
          File.WriteAllBytes(path, contentBytes);
          Console.WriteLine($"Document opgeslagen: {path} ({contentType})");
        }
      }
    }

    private static string GuessFileName(string contentType)
    {
      var ext = ".bin";
      if (string.Equals(contentType, "application/xml", StringComparison.OrdinalIgnoreCase) ||
          string.Equals(contentType, "text/xml", StringComparison.OrdinalIgnoreCase))
        ext = ".xml";
      else if (string.Equals(contentType, "application/pdf", StringComparison.OrdinalIgnoreCase))
        ext = ".pdf";
      else if (string.Equals(contentType, "application/json", StringComparison.OrdinalIgnoreCase))
        ext = ".json";

      return "peppol-document" + ext;
    }
  }
}








namespace JMSNet  // PAS OP: Als ge hier functies of variabelen wijzigt, dan de jmsnet.dll ook kopieren in P:\jms\jms (nodig voor jms om te weten wat de functies zijn) !!!
{
    public class SVC
    {
        // Vast geprogrammeerde CodaBox URL + X-Software-Company key
        string CodaBoxTESTUrl = "https://sandbox-api.codabox.com/v2";
        string CodaBoxTESTCompanyToken = "017a3b44-8474-4a5e-b987-c2ad7d5b69f2";
        string CodaBoxUrl = "https://api.codabox.com/v2";
        string CodaBoxCompanyToken = "d1b8e287-9094-4839-96a5-1194a531316f";
     //   string IbanityUrl = "https://api.ibanity.com";

        // Vaste PRODUCTIE gegevens voor Priority-Jamadata
        static string PIbanityClientID = "f78dfd06-99e4-4702-8fc1-c54f8dbf7894";
        static string PIbanityClientSecret = "76c9d80b-aadc-4f97-9c84-6756976ee88d";
        static string PIbanityCertPasword = "Jamadata192";
        static string PIbanityPfxFilename = "IbanityP.jam";  // certificaat dat JAARLIJKS moet vervangen worden (certificate.PFX, getekend met Jamadata192)
        static string PIbanityUrl = "https://api.ibanity.com";
    // Vaste TEST gegevens voor Priority-Jamadata (sandbox)
    static string TIbanityClientID = "fb6f0064-7511-4a54-a93a-d922a28406fe";
    static string TIbanityClientSecret = "valid_client_secret"; // "826c71a7-b026-487f-9afc-ba057014ff32";
    static string TIbanityCertPasword = "Jamadata192";
    static string TIbanityPfxFilename = "IbanityS.jam";  // certificaat dat JAARLIJKS moet vervangen worden (certificate.PFX, getekend met Jamadata192)
    static string TIbanityUrl = "https://api.ibanity.com";
    // testklant For Peppol, “9925:BE0010012671”
    //  static string TIbanityClientID = "de858d37-d14a-4778-ac51-5091f5a7e9e5";
    // static string TIbanityClientSecret = "UfNBCVlHqe3qhcn61DPg5Xbz4EVwlo01"; // "826c71a7-b026-487f-9afc-ba057014ff32";
    //   static string TIbanityCertPasword = "Jamadata192";
    //   static string TIbanityPfxFilename = "IbanityT.jam";  // certificaat dat JAARLIJKS moet vervangen worden (certificate.PFX, getekend met Jamadata192)

    string IbanityClientID = PIbanityClientID;
        string IbanityClientSecret = PIbanityClientSecret;
        string IbanityCertPasword = PIbanityCertPasword;
        string IbanityPfxFilename = PIbanityPfxFilename;
        string IbanityUrl = PIbanityUrl;
    X509Certificate2 IbanityCert;
        string IbanityToken = "";
        string PathToGeel = "";

        public SVC()
        {
            PathToGeel = "";
        }

        public SVC(string pathToGeel)
        {
            PathToGeel = pathToGeel;
        }

        public bool IbanityGetToken(out string Reply,string debug_)
        {
            Reply = "";
            bool Valid = true;

      if (debug_.ToLower() == "yes")
      {
        IbanityClientID = TIbanityClientID;
        IbanityClientSecret = TIbanityClientSecret;
        IbanityCertPasword = TIbanityCertPasword;
        IbanityPfxFilename = TIbanityPfxFilename;
        IbanityUrl = TIbanityUrl;
      }
      else
      {
        IbanityClientID = PIbanityClientID;
        IbanityClientSecret = PIbanityClientSecret;
        IbanityCertPasword = PIbanityCertPasword;
        IbanityPfxFilename = PIbanityPfxFilename;
        IbanityUrl = PIbanityUrl;
      }

      if (IbanityToken == "")  // als er nog geen token is opgevraagd, dan eerst certificaat aanmaken
            {
                if (File.Exists(IbanityPfxFilename)) IbanityCert = new X509Certificate2(IbanityPfxFilename, IbanityCertPasword);
                else { Reply = "Certificaat-bestand ontbreekt!"; return false; }
            }
            /*
				  // code Nino
				  ServicePointManager.SecurityProtocol = (SecurityProtocolType)3072 | (SecurityProtocolType)768 | SecurityProtocolType.Tls;
				  //Opstarten netwerkverzoek naar ibanity
				  HttpWebRequest request = (HttpWebRequest)WebRequest.Create("https://api.ibanity.com/einvoicing/oauth2/token");

				  //certificaat aan verzoek toevoegen
				  request.ClientCertificates.Add(IbanityCert);

				  //Verdere eigenschappen verzoek toevoegen
				  request.ContentType = "application/x-www-form-urlencoded";
				  request.Accept = "application/vnd.api+json";

				  //Opmaken inloggegevens in het format clientid:clientsecret
				  string credentials = IbanityClientID + ":" + IbanityClientSecret;
				  string auth = Convert.ToBase64String(Encoding.Default.GetBytes(credentials));

				  //Inloggegevens toevoegen aan authenticatieheader verzoek
				  request.Headers["Authorization"] = "Basic " + auth;

				  //type verzoek verklaren
				  request.Method = "POST";

				  //Inhoud verzoek opstellen
				  string postdata = "grant_type=client_credentials";
				  ASCIIEncoding encoding = new ASCIIEncoding();
				  byte[] bytes = encoding.GetBytes(postdata);

				  //Verzoek versturen
				  request.ContentLength = bytes.Length;
				  Stream newStream = request.GetRequestStream();
				  newStream.Write(bytes, 0, bytes.Length);

				  //wachten op antwoord
				  HttpWebResponse response = request.GetResponse() as HttpWebResponse;

				  //antwoord uitlezen
				  StreamReader reader = new StreamReader(response.GetResponseStream(), encoding);
				  string content = reader.ReadToEnd();
			  */

            // hier nieuwe code
            ServicePointManager.SecurityProtocol = (SecurityProtocolType)3072 | (SecurityProtocolType)768 | SecurityProtocolType.Tls;
            var request = (HttpWebRequest)WebRequest.Create(IbanityUrl + "/einvoicing/oauth2/token");
            request.ReadWriteTimeout = 10000; //this can cause issues which is why we are manually setting this
            request.ClientCertificates.Add(IbanityCert);  //certificaat aan verzoek toevoegen
            request.ContentType = "application/x-www-form-urlencoded";
            request.Accept = "application/vnd.api+json";
            //Opmaken inloggegevens in het format clientid:clientsecret
            string credentials = IbanityClientID + ":" + IbanityClientSecret;
            string auth = Convert.ToBase64String(Encoding.Default.GetBytes(credentials));
            request.Headers["Authorization"] = "Basic " + auth; //Inloggegevens toevoegen aan authenticatieheader verzoek
            request.Method = "POST";
            //Inhoud verzoek opstellen
            string postdata = "grant_type=client_credentials";
            ASCIIEncoding encoding = new ASCIIEncoding();
            byte[] bytes = encoding.GetBytes(postdata);

            //Verzoek versturen
            request.ContentLength = bytes.Length;
            Stream newStream = request.GetRequestStream();
            newStream.Write(bytes, 0, bytes.Length);

            try
            {
                HttpWebResponse resp = (HttpWebResponse)request.GetResponse();
                string respStr = new StreamReader(resp.GetResponseStream()).ReadToEnd();
                Reply = respStr;
                // HIER DE TOKEN NOG UIT HALEN
                JsonTextReader reader = new JsonTextReader(new StringReader(respStr));
                while (reader.Read())
                {
                    if (reader.Value != null)
                    {
                        if (reader.Value.Equals("access_token"))
                        {
                            reader.Read();
                            IbanityToken = reader.Value.ToString();
                            break;
                        }
                    }
                }
                reader.Close();

            }
            catch (WebException ex)
            {
                Valid = false;
                HttpWebResponse WebResp = (HttpWebResponse)ex.Response;
                Reply = WebResp.StatusDescription;
                string respStr = new StreamReader(WebResp.GetResponseStream()).ReadToEnd();
                if (respStr.Length > 0) Reply = respStr;

            }
            catch (Exception)
            {
                Valid = false;
            }

            return Valid;
        }

        public bool IbanityCheckVAT(string VAT, out string Reply, string debug_)
        {
            Reply = "";
            bool Valid = true, ViaVAT = true;
            string jsonData;

      if (debug_.ToLower() == "yes")
      {
        IbanityClientID = TIbanityClientID;
        IbanityClientSecret = TIbanityClientSecret;
        IbanityCertPasword = TIbanityCertPasword;
        IbanityPfxFilename = TIbanityPfxFilename;
        IbanityUrl = TIbanityUrl;
      }
      else
      {
        IbanityClientID = PIbanityClientID;
        IbanityClientSecret = PIbanityClientSecret;
        IbanityCertPasword = PIbanityCertPasword;
        IbanityPfxFilename = PIbanityPfxFilename;
        IbanityUrl = PIbanityUrl;
      }



      if (IbanityToken == "")  // als er nog geen token is opgevraagd, dan eerst certificaat aanmaken
            {
                if (IbanityGetToken(out Reply, debug_) == false) return false;
                Reply = "";
            }

            string countryCode = "";
            VAT = VAT.ToUpper();
            if (VAT.Length > 3 && VAT[0] >= 'A' && VAT[0] <= 'Z' && VAT[1] >= 'A' && VAT[1] <= 'Z')
            {
                countryCode = VAT.Substring(0, 2);
                VAT = VAT.Substring(2);
            }
            string vatNumber = VAT.Replace(".", "").Trim();
            if (countryCode == "BE" && vatNumber.Length == 10) { vatNumber = "BE" + vatNumber; ViaVAT = true; }
            if (countryCode == "" && vatNumber.Length == 10) { ViaVAT = false; }

            if (countryCode != "BE" && countryCode != "")
            {
                Reply = "Only BE-CBE";
                return false;
            }
            jsonData = "{\"data\":{\"type\": \"peppolCustomerSearch\",\"attributes\": {\"customerReference\": ";
            if (ViaVAT) jsonData += "\"9925:" + vatNumber + "\"}}}"; // via BTW -nummer
            else jsonData += "\"0208:" + vatNumber + "\"}}}"; // via KBO -nummer

            ServicePointManager.SecurityProtocol = (SecurityProtocolType)3072 | (SecurityProtocolType)768 | SecurityProtocolType.Tls;
            var request = (HttpWebRequest)WebRequest.Create(IbanityUrl + "/einvoicing/peppol/customer-searches");
            request.ReadWriteTimeout = 10000; //this can cause issues which is why we are manually setting this
            request.ClientCertificates.Add(IbanityCert);  //certificaat aan verzoek toevoegen
            request.ContentType = "application/vnd.api+json";
            request.Accept = "application/vnd.api+json";
            //Opmaken inloggegevens in het format clientid:clientsecret
            string credentials = IbanityClientID + ":" + IbanityClientSecret;
            string auth = Convert.ToBase64String(Encoding.Default.GetBytes(credentials));
            request.Headers["Authorization"] = "Bearer " + IbanityToken; //Token toevoegen aan authenticatieheader verzoek
            request.Method = "POST";

            using (var streamWriter = new StreamWriter(request.GetRequestStream()))
            {
                // we want to remove new line characters otherwise it will return an error
                streamWriter.Write(jsonData.Replace("\n", "").Replace("\r", ""));
                streamWriter.Flush();
                streamWriter.Close();
            }

            try
            {
                HttpWebResponse resp = (HttpWebResponse)request.GetResponse();
                string respStr = new StreamReader(resp.GetResponseStream()).ReadToEnd();
                Reply = respStr;
            }
            catch (WebException ex)
            {
                Valid = false;
                HttpWebResponse WebResp = (HttpWebResponse)ex.Response;
                Reply = WebResp.StatusDescription;
                string respStr = new StreamReader(WebResp.GetResponseStream()).ReadToEnd();
                if (respStr.Length > 0) Reply = respStr;
            }
            return Valid;
        }

        public bool IbanityCheckGLN(string GLN, out string Reply, string debug_)
        {
            Reply = "";
            bool Valid = true;
            string jsonData;

      if (debug_.ToLower() == "yes")
      {
        IbanityClientID = TIbanityClientID;
        IbanityClientSecret = TIbanityClientSecret;
        IbanityCertPasword = TIbanityCertPasword;
        IbanityPfxFilename = TIbanityPfxFilename;
        IbanityUrl = TIbanityUrl;
      }
      else
      {
        IbanityClientID = PIbanityClientID;
        IbanityClientSecret = PIbanityClientSecret;
        IbanityCertPasword = PIbanityCertPasword;
        IbanityPfxFilename = PIbanityPfxFilename;
        IbanityUrl = PIbanityUrl;
      }



      if (IbanityToken == "")  // als er nog geen token is opgevraagd, dan eerst certificaat aanmaken
            {
                if (IbanityGetToken(out Reply, debug_) == false) return false;
                Reply = "";
            }

            jsonData = "{\"data\":{\"type\": \"peppolCustomerSearch\",\"attributes\": {\"customerReference\": ";
            jsonData += "\"0088:" + GLN + "\"}}}";

            ServicePointManager.SecurityProtocol = (SecurityProtocolType)3072 | (SecurityProtocolType)768 | SecurityProtocolType.Tls;
            var request = (HttpWebRequest)WebRequest.Create(IbanityUrl + "/einvoicing/peppol/customer-searches");
            request.ReadWriteTimeout = 10000; //this can cause issues which is why we are manually setting this
            request.ClientCertificates.Add(IbanityCert);  //certificaat aan verzoek toevoegen
            request.ContentType = "application/vnd.api+json";
            request.Accept = "application/vnd.api+json";
            //Opmaken inloggegevens in het format clientid:clientsecret
            string credentials = IbanityClientID + ":" + IbanityClientSecret;
            string auth = Convert.ToBase64String(Encoding.Default.GetBytes(credentials));
            request.Headers["Authorization"] = "Bearer " + IbanityToken; //Token toevoegen aan authenticatieheader verzoek
            request.Method = "POST";

            using (var streamWriter = new StreamWriter(request.GetRequestStream()))
            {
                // we want to remove new line characters otherwise it will return an error
                streamWriter.Write(jsonData.Replace("\n", "").Replace("\r", ""));
                streamWriter.Flush();
                streamWriter.Close();
            }

            try
            {
                HttpWebResponse resp = (HttpWebResponse)request.GetResponse();
                string respStr = new StreamReader(resp.GetResponseStream()).ReadToEnd();
                Reply = respStr;
            }
            catch (WebException ex)
            {
                Valid = false;
                HttpWebResponse WebResp = (HttpWebResponse)ex.Response;
                Reply = WebResp.StatusDescription;
                string respStr = new StreamReader(WebResp.GetResponseStream()).ReadToEnd();
                if (respStr.Length > 0) Reply = respStr;
            }
            return Valid;
        }

        public bool IbanityShowLicence(string Licence, out string Reply, string debug_) // om naam,btw,iban te tonen van key (punt +.4 en icoon)
        {
            Reply = "";
            bool Valid = true;

      if (debug_.ToLower() == "yes")
      {
        IbanityClientID = TIbanityClientID;
        IbanityClientSecret = TIbanityClientSecret;
        IbanityCertPasword = TIbanityCertPasword;
        IbanityPfxFilename = TIbanityPfxFilename;
        IbanityUrl = TIbanityUrl;
      }
      else
      {
        IbanityClientID = PIbanityClientID;
        IbanityClientSecret = PIbanityClientSecret;
        IbanityCertPasword = PIbanityCertPasword;
        IbanityPfxFilename = PIbanityPfxFilename;
        IbanityUrl = PIbanityUrl;
      }


      if (IbanityToken == "")  // als er nog geen token is opgevraagd, dan eerst certificaat aanmaken
            {
                if (IbanityGetToken(out Reply, debug_) == false) return false;
                Reply = "";
            }

            ServicePointManager.SecurityProtocol = (SecurityProtocolType)3072 | (SecurityProtocolType)768 | SecurityProtocolType.Tls;
            var request = (HttpWebRequest)WebRequest.Create(IbanityUrl + "/einvoicing/suppliers/" + Licence);
            request.ReadWriteTimeout = 10000; //this can cause issues which is why we are manually setting this
            request.ClientCertificates.Add(IbanityCert);  //certificaat aan verzoek toevoegen
            request.Accept = "application/vnd.api+json";
            //Opmaken inloggegevens in het format clientid:clientsecret
            string credentials = IbanityClientID + ":" + IbanityClientSecret;
            string auth = Convert.ToBase64String(Encoding.Default.GetBytes(credentials));
            request.Headers["Authorization"] = "Bearer " + IbanityToken; //Token toevoegen aan authenticatieheader verzoek
            request.Method = "GET";
            try
            {
                HttpWebResponse resp = (HttpWebResponse)request.GetResponse();
                string respStr = new StreamReader(resp.GetResponseStream()).ReadToEnd();
                Reply = respStr;
            }
            catch (WebException ex)
            {
                Valid = false;
                HttpWebResponse WebResp = (HttpWebResponse)ex.Response;
                Reply = WebResp.StatusDescription;
                string respStr = new StreamReader(WebResp.GetResponseStream()).ReadToEnd();
                if (respStr.Length > 0) Reply = respStr;
            }
            return Valid;
        }
        public bool IbanityUBLUpload(string License, string VAT, string CNflag, string FileName, out string Reply, string debug_)
        {
            Reply = "";
            bool Valid = true;
            string boundary = "-------------------" + DateTime.Now.Ticks.ToString("x");
            boundary = "------------------------eb7d3e04622c2a8d";
            string errorFile = "";

            if (debug_.ToLower() == "yes")
            {
              IbanityClientID = TIbanityClientID;
              IbanityClientSecret = TIbanityClientSecret;
              IbanityCertPasword = TIbanityCertPasword;
              IbanityPfxFilename = TIbanityPfxFilename;
        IbanityUrl = TIbanityUrl;
      }
            else
            {
              IbanityClientID = PIbanityClientID;
              IbanityClientSecret = PIbanityClientSecret;
              IbanityCertPasword = PIbanityCertPasword;
              IbanityPfxFilename = PIbanityPfxFilename;
        IbanityUrl = PIbanityUrl;
      }


      if (PathToGeel != "")
                errorFile = PathToGeel + "\\" + Path.GetFileNameWithoutExtension(FileName) + ".err";

            // nieuw

            string UblId = "";

            if (IbanityToken == "")  // als er nog geen token is opgevraagd, dan eerst certificaat aanmaken
            {
                if (IbanityGetToken(out Reply, debug_) == false)
                {
                    if (errorFile != "")
                        File.WriteAllText(errorFile, Reply);

                    return false;
                }

                Reply = "";
            }
            if (VAT.Contains("GLN")) // via GLN-nummer
            {
                VAT = VAT.Remove(0, 3);
                if (IbanityCheckGLN(VAT, out Reply, debug_) == false)
                {
                    if (errorFile != "")
                        File.WriteAllText(errorFile, Reply);

                    return false;
                }
            }
            else
            {
                if (IbanityCheckVAT(VAT, out Reply, debug_) == false)
                {
                    if (errorFile != "")
                        File.WriteAllText(errorFile, Reply);

                    return false;
                }
            }

            Reply = "";
            ServicePointManager.SecurityProtocol = (SecurityProtocolType)3072 | (SecurityProtocolType)768 | SecurityProtocolType.Tls;
            string urlstring = "";
            urlstring = IbanityUrl + "/einvoicing/peppol/suppliers/" + License + "/invoices";

            if (CNflag == "yes" || CNflag == "YES")
            {
                urlstring = IbanityUrl + "/einvoicing/peppol/suppliers/" + License + "/credit-notes";
            }

            var request = (HttpWebRequest)WebRequest.Create(urlstring);
            request.ReadWriteTimeout = 10000; //this can cause issues which is why we are manually setting this
            request.ClientCertificates.Add(IbanityCert);  //certificaat aan verzoek toevoegen
            request.ContentType = "application/xml";

            //Opmaken inloggegevens in het format clientid:clientsecret
            string credentials = IbanityClientID + ":" + IbanityClientSecret;
            string auth = Convert.ToBase64String(Encoding.Default.GetBytes(credentials));
            request.Headers["Authorization"] = "Bearer " + IbanityToken; //Token toevoegen aan authenticatieheader verzoek
            request.Headers.Add("Content-Disposition", "inline; filename=\"" + FileName + "\"");
            request.Method = "POST";
            FileInfo fi = new FileInfo(FileName);
            int fileLength = (int)fi.Length;
            FileStream rdr = new FileStream(FileName, FileMode.Open);

            Stream requestStream = request.GetRequestStream();
            rdr.CopyTo(requestStream);
            requestStream.Close();
            rdr.Close();

            try
            {
                HttpWebResponse resp = (HttpWebResponse)request.GetResponse();
                string respStr = new StreamReader(resp.GetResponseStream()).ReadToEnd();
                Reply = respStr;

                // HIER DE TOKEN NOG UIT HALEN
                JsonTextReader reader = new JsonTextReader(new StringReader(respStr));

                while (reader.Read())
                {
                    if (reader.Value != null)
                    {
                        if (reader.Value.Equals("id"))
                        {
                            reader.Read();
                            UblId = reader.Value.ToString();
                            break;
                        }
                    }
                }

                reader.Close();
            }
            catch (WebException ex)
            {
                if (errorFile != "")
                    File.WriteAllText(errorFile, Reply);

                Valid = false;
                HttpWebResponse WebResp = (HttpWebResponse)ex.Response;
                Reply = WebResp.StatusDescription;

                if (errorFile != "")
                    File.AppendAllText(errorFile, "\r\n\r\nStatusDescription: " + Reply + "\r\n\r\n");

                string respStr = new StreamReader(WebResp.GetResponseStream()).ReadToEnd();

                if (respStr.Length > 0)
                {
                    Reply = respStr;

                    if (errorFile != "")
                        File.AppendAllText(errorFile, respStr);
                }
            }

            if (Valid)
            {
                IbanityUBLStatus(License, UblId, CNflag, out Reply, debug_);
            }

            return Valid;
        }

        public bool IbanityUBLStatus(string License, string UBLId, string CNflag, out string Reply, string debug_)
        {
            Reply = "";
            bool Valid = true;

      if (debug_.ToLower() == "yes")
      {
        IbanityClientID = TIbanityClientID;
        IbanityClientSecret = TIbanityClientSecret;
        IbanityCertPasword = TIbanityCertPasword;
        IbanityPfxFilename = TIbanityPfxFilename;
        IbanityUrl = TIbanityUrl;
      }
      else
      {
        IbanityClientID = PIbanityClientID;
        IbanityClientSecret = PIbanityClientSecret;
        IbanityCertPasword = PIbanityCertPasword;
        IbanityPfxFilename = PIbanityPfxFilename;
        IbanityUrl = PIbanityUrl;
      }


      if (IbanityToken == "")  // als er nog geen token is opgevraagd, dan eerst certificaat aanmaken
            {
                if (IbanityGetToken(out Reply, debug_) == false) return false;
                Reply = "";
            }


            ServicePointManager.SecurityProtocol = (SecurityProtocolType)3072 | (SecurityProtocolType)768 | SecurityProtocolType.Tls;
            string urlstring = "";
            urlstring = IbanityUrl + "/einvoicing/peppol/suppliers/" + License + "/invoices/" + UBLId;
            if (CNflag == "yes" || CNflag == "YES")
            {
                urlstring = IbanityUrl + "/einvoicing/peppol/suppliers/" + License + "/credit-notes/" + UBLId;
            }
            var request = (HttpWebRequest)WebRequest.Create(urlstring);

            //     var request = (HttpWebRequest)WebRequest.Create(IbanityUrl + "/einvoicing/peppol/suppliers/" + License + "/invoices/" + UBLId);
            request.ReadWriteTimeout = 10000; //this can cause issues which is why we are manually setting this
            request.ClientCertificates.Add(IbanityCert);  //certificaat aan verzoek toevoegen
            request.Accept = "application/vnd.api+json";
            //Opmaken inloggegevens in het format clientid:clientsecret
            string credentials = IbanityClientID + ":" + IbanityClientSecret;
            string auth = Convert.ToBase64String(Encoding.Default.GetBytes(credentials));
            request.Headers["Authorization"] = "Bearer " + IbanityToken; //Token toevoegen aan authenticatieheader verzoek
            request.Method = "GET";

            try
            {
                HttpWebResponse resp = (HttpWebResponse)request.GetResponse();
                string respStr = new StreamReader(resp.GetResponseStream()).ReadToEnd();
                Reply = respStr;
            }
            catch (WebException ex)
            {
                Valid = false;
                HttpWebResponse WebResp = (HttpWebResponse)ex.Response;
                Reply = WebResp.StatusDescription;
                string respStr = new StreamReader(WebResp.GetResponseStream()).ReadToEnd();
                if (respStr.Length > 0) Reply = respStr;
            }

            return Valid;
        }

        public bool PepPolCheckVAT(string User, string PW, string VAT, out string Reply)
        {
            Reply = "";
            bool Valid = true, ViaVAT = true;
            string jsonData;

            string CbUrl = CodaBoxUrl;
            string CbCtoken = CodaBoxCompanyToken;
            if (User.Contains("!")) // Beginnend met een !, dan is TEST werken
            {
                User = User.Replace("!", "");
                CbUrl = CodaBoxTESTUrl; CbCtoken = CodaBoxTESTCompanyToken;
            }

            string countryCode = "";
            VAT = VAT.ToUpper();
            if (VAT.Length > 3 && VAT[0] >= 'A' && VAT[0] <= 'Z' && VAT[1] >= 'A' && VAT[1] <= 'Z')
            {
                countryCode = VAT.Substring(0, 2);
                VAT = VAT.Substring(2);
            }
            string vatNumber = VAT.Replace(".", "").Trim();
            if (countryCode == "BE" && vatNumber.Length == 10) { vatNumber = "BE" + vatNumber; ViaVAT = true; }
            if (countryCode == "" && vatNumber.Length == 10) { ViaVAT = false; }

            if (countryCode != "BE" && countryCode != "")
            {
                Reply = "Only BE-CBE";
                return false;
            }
            if (ViaVAT)
            {
                jsonData = "{\"scheme_id\": \"9925\", \"value\": \"" + vatNumber + "\"}"; // via BTW -nummer
            }
            else
            {
                jsonData = "{\"scheme_id\": \"0208\", \"value\": \"" + vatNumber + "\"}"; // via KBO -nummer
            }
            // string jsonData = "{\"scheme_id\": \"BE:CBE\", \"value\": \"" + vatNumber + "\"}";

            var httpWebRequest = (HttpWebRequest)WebRequest.Create(CbUrl + "/peppol/receiver/check-presence/");
            httpWebRequest.ReadWriteTimeout = 10000; //this can cause issues which is why we are manually setting this
            httpWebRequest.ContentType = "application/json";
            httpWebRequest.Accept = "*/*";
            httpWebRequest.Method = "POST";
            httpWebRequest.Headers.Add("X-Software-Company", CbCtoken);
            httpWebRequest.Credentials = new NetworkCredential(User, PW);
            using (var streamWriter = new StreamWriter(httpWebRequest.GetRequestStream()))
            {
                // we want to remove new line characters otherwise it will return an error
                streamWriter.Write(jsonData.Replace("\n", "").Replace("\r", ""));
                streamWriter.Flush();
                streamWriter.Close();
            }

            try
            {
                HttpWebResponse resp = (HttpWebResponse)httpWebRequest.GetResponse();
                string respStr = new StreamReader(resp.GetResponseStream()).ReadToEnd();
                Reply = respStr;
            }
            catch (WebException ex)
            {
                Valid = false;
                HttpWebResponse WebResp = (HttpWebResponse)ex.Response;
                Reply = WebResp.StatusDescription;
                string respStr = new StreamReader(WebResp.GetResponseStream()).ReadToEnd();
                if (respStr.Length > 0) Reply = respStr;
            }
            return Valid;
        }
        public bool PepPolUBLUpload(string User, string PW, string License, string FileName, out string Reply)
        {
            Reply = "";
            bool Valid = true;
            string boundary = "-------------------" + DateTime.Now.Ticks.ToString("x");
            boundary = "------------------------eb7d3e04622c2a8d";

            string CbUrl = CodaBoxUrl;
            string CbCtoken = CodaBoxCompanyToken;
            if (User.Contains("!")) // Beginnend met een !, dan is TEST werken
            {
                User = User.Replace("!", "");
                CbUrl = CodaBoxTESTUrl; CbCtoken = CodaBoxTESTCompanyToken;
            }
            var httpWebRequest = (HttpWebRequest)WebRequest.Create(CbUrl + "/peppol/licences/" + License + "/upload/");
            httpWebRequest.ReadWriteTimeout = 100000; //this can cause issues which is why we are manually setting this
            httpWebRequest.Accept = "*/*";
            httpWebRequest.Method = "POST";
            httpWebRequest.UserAgent = "curl/7.54.0";
            httpWebRequest.Headers.Add("X-Software-Company", CbCtoken);
            httpWebRequest.Credentials = new NetworkCredential(User, PW);
            httpWebRequest.ContentType = "multipart/form-data; boundary=" + boundary;

            FileInfo fi = new FileInfo(FileName);
            int fileLength = (int)fi.Length;
            FileStream rdr = new FileStream(FileName, FileMode.Open);

            Stream requestStream = httpWebRequest.GetRequestStream();

            var buffer = Encoding.ASCII.GetBytes("--" + boundary + Environment.NewLine);
            requestStream.Write(buffer, 0, buffer.Length);
            buffer = Encoding.UTF8.GetBytes(string.Format("Content-Disposition: form-data; name=\"file\"; filename=\"" + Path.GetFileName(FileName) + "\"\r\n"));
            requestStream.Write(buffer, 0, buffer.Length);
            buffer = Encoding.ASCII.GetBytes(string.Format("Content-Type: application/xml\r\n\r\n"));
            requestStream.Write(buffer, 0, buffer.Length);
            rdr.CopyTo(requestStream);
            buffer = Encoding.ASCII.GetBytes(Environment.NewLine);
            requestStream.Write(buffer, 0, buffer.Length);

            var boundaryBuffer = Encoding.ASCII.GetBytes("--" + boundary + "--");
            requestStream.Write(boundaryBuffer, 0, boundaryBuffer.Length);

            requestStream.Close();
            rdr.Close();

            try
            {
                HttpWebResponse resp = (HttpWebResponse)httpWebRequest.GetResponse();
                string respStr = new StreamReader(resp.GetResponseStream()).ReadToEnd();
                Reply = respStr;
            }
            catch (WebException ex)
            {
                Valid = false;
                HttpWebResponse WebResp = (HttpWebResponse)ex.Response;
                Reply = WebResp.StatusDescription;
                string respStr = new StreamReader(WebResp.GetResponseStream()).ReadToEnd();
                if (respStr.Length > 0) Reply = respStr;
            }

            return Valid;
        }


        public bool PepPolUBLStatus(string User, string PW, string UBLId, out string Reply)
        {
            Reply = "";
            bool Valid = true;

            string CbUrl = CodaBoxUrl;
            string CbCtoken = CodaBoxCompanyToken;
            if (User.Contains("!")) // Beginnend met een !, dan is TEST werken
            {
                User = User.Replace("!", "");
                CbUrl = CodaBoxTESTUrl; CbCtoken = CodaBoxTESTCompanyToken;
            }

            var httpWebRequest = (HttpWebRequest)WebRequest.Create(CbUrl + "/peppol/ubl/" + UBLId + "/");
            httpWebRequest.ReadWriteTimeout = 10000; //this can cause issues which is why we are manually setting this
            httpWebRequest.ContentType = "application/json";
            httpWebRequest.Accept = "*/*";
            httpWebRequest.Method = "GET";
            httpWebRequest.Headers.Add("X-Software-Company", CbCtoken);
            httpWebRequest.Credentials = new NetworkCredential(User, PW);

            try
            {
                HttpWebResponse resp = (HttpWebResponse)httpWebRequest.GetResponse();
                string respStr = new StreamReader(resp.GetResponseStream()).ReadToEnd();
                Reply = respStr;
            }
            catch (WebException ex)
            {
                Valid = false;
                HttpWebResponse WebResp = (HttpWebResponse)ex.Response;
                Reply = WebResp.StatusDescription;
                string respStr = new StreamReader(WebResp.GetResponseStream()).ReadToEnd();
                if (respStr.Length > 0) Reply = respStr;
            }

            return Valid;
        }

        public bool FtpUpload(string Server, string User, string PW, string FileName)
        {

            if (Server.IndexOf("ftp://") < 0) Server = "ftp://" + Server + "/" + Path.GetFileName(FileName);
            try
            {
                // Get the object used to communicate with the server.  
                FtpWebRequest request = (FtpWebRequest)WebRequest.Create(Server);
                request.Method = WebRequestMethods.Ftp.UploadFile;
                request.UseBinary = true;
                request.Credentials = new NetworkCredential(User, PW);

                byte[] data = File.ReadAllBytes(FileName);
                request.ContentLength = data.Length;
                Stream stream = request.GetRequestStream();
                stream.Write(data, 0, data.Length);
                stream.Close();

                FtpWebResponse response = (FtpWebResponse)request.GetResponse();
                // Console.WriteLine("Upload File Complete, status {0}", response.StatusDescription);
                response.Close();

                if (response.StatusDescription.IndexOf("226") >= 0) return true;
                else return false;
            }
            catch
            {
                return false;
            }
        }

        public bool SFtpUpload(string Server, string User, string PW, string FileName, string PortNr)
        {
            int port_ = 0;
            if (PortNr != "") port_ = Convert.ToInt32(PortNr);
            if (port_ == 0) port_ = 22;
            try
            {
                var connectionInfo = new ConnectionInfo(Server, port_, User, new PasswordAuthenticationMethod(User, PW));
                using (var client = new SftpClient(connectionInfo))
                {
                    string localFileName = Directory.GetCurrentDirectory() + "\\" + FileName;
                    client.Connect();
                    Stream stream = new FileStream(localFileName, FileMode.Open);
                    client.UploadFile(stream, "/" + User + "/" + FileName);
                    client.Disconnect();
                    stream.Close();
                }
                return true;
            }
            catch
            {
                return false;
            }
        }

        public bool SFtpUpload(string Server, string User, string PW, string FileName, string PortNr, string FtpFileName)
        {
            int port_ = 0;
            if (PortNr != "") port_ = Convert.ToInt32(PortNr);
            if (port_ == 0) port_ = 22;
            try
            {
                var connectionInfo = new ConnectionInfo(Server, port_, User, new PasswordAuthenticationMethod(User, PW));
                using (var client = new SftpClient(connectionInfo))
                {
                    string localFileName = Directory.GetCurrentDirectory() + "\\" + FileName;
                    client.Connect();
                    Stream stream = new FileStream(localFileName, FileMode.Open);
                    if (FtpFileName != "") client.UploadFile(stream, "/" + FtpFileName);
                    else client.UploadFile(stream, "/" + User + "/" + FileName);
                    client.Disconnect();
                    stream.Close();
                }
                return true;
            }
            catch
            {
                return false;
            }

        }

        public string FtpDownload(string Server, string User, string PW, string FileName)
        {

            if (Server.IndexOf("ftp://") < 0) Server = "ftp://" + Server + "/" + Path.GetFileName(FileName);
            try
            {
                // Get the object used to communicate with the server. 
                FtpWebRequest request = (FtpWebRequest)WebRequest.Create(Server);
                request.Method = WebRequestMethods.Ftp.DownloadFile;
                request.UseBinary = true;
                request.Credentials = new NetworkCredential(User, PW);

                FtpWebResponse response = (FtpWebResponse)request.GetResponse();

                Stream responseStream = response.GetResponseStream();
                int buflen = 256 * 256;
                byte[] data = new byte[buflen];

                string TempFileName = Path.GetTempFileName();
                if (File.Exists(TempFileName)) File.Delete(TempFileName);
                string RetFileName = TempFileName.Replace(Path.GetFileName(TempFileName), FileName);
                FileStream fil = File.Create(RetFileName);

                while (true)
                {
                    int readlen = responseStream.Read(data, 0, buflen);
                    if (readlen <= 0) break;
                    fil.Write(data, 0, readlen);
                }
                fil.Close();

                // Console.WriteLine("Download Complete, status {0}", response.StatusDescription);
                response.Close();

                return RetFileName;
            }
            catch (Exception)
            {
                return "";
            }
        }

        public string SFtpDownload(string Server, string User, string PW, string FileName, string PortNr)
        {
            string RetFileName = "";
            int port_ = 0;
            if (PortNr != "") port_ = Convert.ToInt32(PortNr);
            if (port_ == 0) port_ = 22;
            try
            {
                var connectionInfo = new ConnectionInfo(Server, port_, User, new PasswordAuthenticationMethod(User, PW));
                using (var client = new SftpClient(connectionInfo))
                {
                    string localFileName = Directory.GetCurrentDirectory() + "\\" + FileName;
                    RetFileName = localFileName.Replace(Path.GetFileName(localFileName), FileName);
                    Stream stream = new FileStream(localFileName, FileMode.OpenOrCreate);
                    stream.SetLength(0);
                    client.Connect();
                    client.DownloadFile("/" + User + "/" + FileName, stream); ;
                    client.Disconnect();
                    stream.Close();
                }
                return RetFileName;
            }
            catch
            {
                return "";
            }
        }

        public string SFtpDownload2(string Server, string User, string PW, string FileName, string PortNr)
        {
            string RetFileName = "";
            int port_ = 0;
            if (PortNr != "") port_ = Convert.ToInt32(PortNr);
            if (port_ == 0) port_ = 22;
            try
            {
                var connectionInfo = new ConnectionInfo(Server, port_, User, new PasswordAuthenticationMethod(User, PW));
                using (var client = new SftpClient(connectionInfo))
                {
                    string localFileName = Directory.GetCurrentDirectory() + "\\" + Path.GetFileName(FileName);
                    RetFileName = localFileName.Replace(Path.GetFileName(localFileName), Path.GetFileName(FileName));
                    Stream stream = new FileStream(localFileName, FileMode.OpenOrCreate);
                    stream.SetLength(0);
                    client.Connect();
                    client.DownloadFile(FileName, stream); ;
                    client.Disconnect();
                    stream.Close();
                }
                return RetFileName;
            }
            catch (Exception)
            {
                return "";
            }
        }

        public string FtpDirectory(string Server, string User, string PW)
        {
            if (Server.IndexOf("ftp://") < 0) Server = "ftp://" + Server;
            try
            {
                // Get the object used to communicate with the server. 
                FtpWebRequest request = (FtpWebRequest)WebRequest.Create(Server);
                request.Credentials = new NetworkCredential(User, PW);
                request.Method = WebRequestMethods.Ftp.ListDirectory;

                FtpWebResponse response = (FtpWebResponse)request.GetResponse();

                Stream responseStream = response.GetResponseStream();
                int buflen = 256 * 256 + 1;
                byte[] data = new byte[buflen];
                string DirListing = "";

                while (true)
                {
                    int readlen = responseStream.Read(data, 0, buflen - 1);
                    if (readlen <= 0) break;
                    DirListing += System.Text.Encoding.Default.GetString(data, 0, readlen);
                }

                // Console.WriteLine("Download Complete, status {0}", response.StatusDescription);
                response.Close();

                return DirListing;
            }
            catch (Exception)
            {
                return "";
            }
        }

        public string SFtpDirectory(string Server, string User, string PW, string PortNr)
        {
            int port_ = 0;
            if (PortNr != "") port_ = Convert.ToInt32(PortNr);
            if (port_ == 0) port_ = 22;
            try
            {
                var connectionInfo = new ConnectionInfo(Server, port_, User, new PasswordAuthenticationMethod(User, PW));
                using (var client = new SftpClient(connectionInfo))
                {
                    client.Connect();
                    List<ISftpFile> directory = client.ListDirectory("/" + User).ToList();
                    string files = "";
                    foreach (ISftpFile file in directory)
                    {
                        files = files + file.Name + "\n";
                    }
                    client.Disconnect();
                    return files;
                }
            }
            catch
            {
                return "";
            }
        }

        public string SFtpDirectory(string Server, string User, string PW, string PortNr, string Directory)
        {
            int port_ = 0;

            if (PortNr != "")
                port_ = Convert.ToInt32(PortNr);

            if (port_ == 0)
                port_ = 22;

            try
            {
                var connectionInfo = new ConnectionInfo(Server, port_, User, new PasswordAuthenticationMethod(User, PW));

                using (var client = new SftpClient(connectionInfo))
                {
                    client.Connect();
                    List<ISftpFile> directory = client.ListDirectory(Directory).ToList();
                    string files = "";

                    foreach (ISftpFile file in directory)
                    {
                        files = files + file.Name + "\n";
                    }

                    client.Disconnect();
                    return files;
                }
            }
            catch
            {
                return "";
            }
        }

        public string FtpDelete(string Server, string User, string PW, string FileName)
        {

            if (Server.IndexOf("ftp://") < 0) Server = "ftp://" + Server + "/" + Path.GetFileName(FileName);
            try
            {
                // Get the object used to communicate with the server. 
                FtpWebRequest request = (FtpWebRequest)WebRequest.Create(Server);
                request.Method = WebRequestMethods.Ftp.DeleteFile;
                request.Credentials = new NetworkCredential(User, PW);

                FtpWebResponse response = (FtpWebResponse)request.GetResponse();

                Stream responseStream = response.GetResponseStream();
                int buflen = 256 * 256 + 1;
                byte[] data = new byte[buflen];

                string Reply = "Deleted"; // normaal geen response terug ...

                while (true)
                {
                    int readlen = responseStream.Read(data, 0, buflen - 1);
                    if (readlen <= 0) break;
                    Reply += System.Text.Encoding.Default.GetString(data, 0, readlen);
                }

                // Console.WriteLine("Download Complete, status {0}", response.StatusDescription);
                response.Close();

                return Reply;
            }
            catch (Exception)
            {
                return "";
            }
        }

        public string SFtpDelete(string Server, string User, string PW, string FileName, string PortNr)
        {
            string Reply = "Deleted"; // normaal geen response terug ...
            int port_ = 0;
            if (PortNr != "") port_ = Convert.ToInt32(PortNr);
            if (port_ == 0) port_ = 22;
            try
            {
                var connectionInfo = new ConnectionInfo(Server, port_, User, new PasswordAuthenticationMethod(User, PW));
                using (var client = new SftpClient(connectionInfo))
                {
                    client.Connect();
                    client.DeleteFile("/" + User + "/" + FileName);
                    client.Disconnect();
                }
                return Reply;
            }
            catch
            {
                return "";
            }
        }

        public string SFtpDelete2(string Server, string User, string PW, string FileName, string PortNr)
        {
            string Reply = "Deleted"; // normaal geen response terug ...
            int port_ = 0;
            if (PortNr != "") port_ = Convert.ToInt32(PortNr);
            if (port_ == 0) port_ = 22;
            try
            {
                var connectionInfo = new ConnectionInfo(Server, port_, User, new PasswordAuthenticationMethod(User, PW));
                using (var client = new SftpClient(connectionInfo))
                {
                    client.Connect();
                    client.DeleteFile(FileName);
                    client.Disconnect();
                }
                return Reply;
            }
            catch
            {
                return "";
            }
        }


        public bool WebrequestJson(string Url, string Method, string User, string PW, string HeaderKey, string HeaderValue, string Message, string FileName, bool ForceUnchangedInput, bool ForceUnchangedOutput, out string Reply)
        {
            bool Valid = true;
            string JsonData = "";
            int retry_count = 0;

        redo_request:;
            Valid = true; JsonData = ""; Reply = "";
            try
            {
                if (string.IsNullOrWhiteSpace(Url) && string.IsNullOrWhiteSpace(Method))
                {
                    //a Url and Method MUST be given
                    Reply = "{\"error\":\"Missing Url or Method\"}";
                    if (!ForceUnchangedOutput)
                    {
                        Reply = JsonToXml(Reply);
                    }
                    return false;
                }

                var httpWebRequest = (HttpWebRequest)WebRequest.Create(Url);
                httpWebRequest.ReadWriteTimeout = 30000; //this can cause issues which is why we are manually setting this
                httpWebRequest.ContentType = "application/json";
                httpWebRequest.Accept = "*/*";
                httpWebRequest.Method = Method;

                if (!string.IsNullOrWhiteSpace(HeaderKey) && !string.IsNullOrWhiteSpace(HeaderValue))
                {
                    // HEADER
                    httpWebRequest.Headers.Add(HeaderKey, HeaderValue);
                }

                if (!string.IsNullOrWhiteSpace(User) && !string.IsNullOrWhiteSpace(PW))
                {
                    // USER PW
                    httpWebRequest.Credentials = new NetworkCredential(User, PW);
                }

                if (Message.IndexOf("{") == 0) // starts with {
                {
                    // JSON
                    JsonData = Message;
                }
                else if (Message.IndexOf("<") == 0) // starts with <
                {
                    if (!ForceUnchangedInput)
                    {
                        JsonData = XmlToJson(Message);
                    }
                    else
                    {
                        JsonData = Message;
                    }
                }

                if (!string.IsNullOrWhiteSpace(JsonData))
                {
                    try
                    {
                        String vJson = JsonData.Replace("\n", "").Replace("\r", "");

                        byte[] bytes = Encoding.ASCII.GetBytes(vJson);

                        httpWebRequest.ContentLength = bytes.Length;

                        Stream requestStream = httpWebRequest.GetRequestStream();

                        requestStream.Write(bytes, 0, bytes.Length);
                        requestStream.Close();
                    }
                    catch (Exception)
                    {
                        Reply = "";
                    }
                }

                if (FileName.IndexOf("\\") != -1)
                {
                    // FILE
                    string Boundary = "-------------------" + DateTime.Now.Ticks.ToString("x");

                    httpWebRequest.UserAgent = "curl/7.54.0";
                    httpWebRequest.ContentType = "multipart/form-data; boundary=" + Boundary;

                    FileInfo fi = new FileInfo(FileName);
                    int fileLength = (int)fi.Length;
                    FileStream rdr = new FileStream(FileName, FileMode.Open);

                    Stream requestStream = httpWebRequest.GetRequestStream();

                    var buffer = Encoding.ASCII.GetBytes("--" + Boundary + Environment.NewLine);
                    requestStream.Write(buffer, 0, buffer.Length);
                    buffer = Encoding.UTF8.GetBytes(string.Format("Content-Disposition: form-data; name=\"file\"; filename=\"" + Path.GetFileName(FileName) + "\"\r\n"));
                    requestStream.Write(buffer, 0, buffer.Length);
                    buffer = Encoding.ASCII.GetBytes(string.Format("Content-Type: application/xml\r\n\r\n"));
                    requestStream.Write(buffer, 0, buffer.Length);
                    rdr.CopyTo(requestStream);
                    buffer = Encoding.ASCII.GetBytes(Environment.NewLine);
                    requestStream.Write(buffer, 0, buffer.Length);

                    var boundaryBuffer = Encoding.ASCII.GetBytes("--" + Boundary + "--");
                    requestStream.Write(boundaryBuffer, 0, boundaryBuffer.Length);

                    requestStream.Close();
                    rdr.Close();
                }

                // Actually execute the web request
                try
                {
                    //       ServicePointManager.ServerCertificateValidationCallback = delegate { return true; };
                    //                    ServicePointManager.ServerCertificateValidationCallback += (sender, certificate, chain, sslPolicyErrors) => true;
                    //                    ServicePointManager.Expect100Continue = true;
                    ServicePointManager.SecurityProtocol = (SecurityProtocolType)(SecurityProtocolType)48 | (SecurityProtocolType)192 |
            (SecurityProtocolType)768 | (SecurityProtocolType)3072;
                    //                    ServicePointManager.DefaultConnectionLimit = 9999;

                    HttpWebResponse resp = (HttpWebResponse)httpWebRequest.GetResponse();
                    string respStr = new StreamReader(resp.GetResponseStream()).ReadToEnd();
                    Reply = respStr;
                }
                catch (WebException ex)
                {
                    var response = ex.Response as HttpWebResponse;
                    String vException = ex.Message;
                    Valid = false;
                    int vCode = (int)response.StatusCode;
                    if (vCode == 504) // probleem Coca-Cola tgv trage response
                    {
                        retry_count++;
                        if (retry_count < 3) goto redo_request;
                    }
                    string respStr = new StreamReader(response.GetResponseStream()).ReadToEnd();
                    Reply = "HTTPrequest ERROR: " + vCode + " " + respStr; // response.StatusDescription;
                }

                if (!string.IsNullOrWhiteSpace(Reply))
                {
                    if (Reply.IndexOf("{") == 0) // starts with {
                    {
                        //standard convert to xml
                        if (!ForceUnchangedOutput)
                        {
                            Reply = JsonToXml(Reply);
                        }
                    }
                }
            }
            catch (Exception)
            {
                Valid = false;
                Reply = "";
            }

            return Valid;
        }

        // VERGEET NIET DE NewtonSoft.Json.DLL uit de subdir Jms\JmsNet\Bin\Release\ mee te geven met de JMS.EXE !!!!! 
        public string JsonToXml(string Json)
        {
            // returns the Json result as XML in a main body tag of <result>
            Json = Json.Replace("|", " ");
            string XML = "";
            string MainBodyTag = "jamaXml";

            try
            {
                if (string.IsNullOrWhiteSpace(Json)) return XML;
                if (Json.IndexOf("{") == 0)
                {
                    try
                    {
                        //                     XmlDocument xmlDoc = (XmlDocument)JsonConvert.DeserializeXmlNode(Json);
                        JObject oJson = JObject.Parse(Json);
                        String vTemp = oJson.ToString();
                        XNode oNode = JsonConvert.DeserializeXNode(vTemp, MainBodyTag);
                        XML = oNode.ToString();
                        //using (StringWriter sw = new StringWriter())
                        //{
                        //    using (XmlTextWriter tx = new XmlTextWriter(sw))
                        //    {
                        //        xmlDoc.WriteTo(tx);
                        //        XML = sw.ToString();
                        //    }
                        //}
                    }
                    catch (Exception)
                    {
                        XmlDocument xmlDoc = (XmlDocument)JsonConvert.DeserializeXmlNode(Json, MainBodyTag); // put the whole json/xml in a main tag named "result"
                        using (StringWriter sw = new StringWriter())
                        {
                            using (XmlTextWriter tx = new XmlTextWriter(sw))
                            {
                                xmlDoc.WriteTo(tx);
                                XML = sw.ToString();
                            }
                        }
                    }

                    if (XML.IndexOf("<" + MainBodyTag + ">") == 0 || XML.IndexOf("<" + MainBodyTag + " />") == 0)
                    {
                        // XML had main boy element of <xml>
                        XML = XML.Replace("<" + MainBodyTag + ">\r\n", ""); // cut off the main element
                        XML = XML.Replace("<" + MainBodyTag + ">", ""); // cut off the main element
                        XML = XML.Replace("</" + MainBodyTag + ">", "");
                        XML = XML.Replace("<" + MainBodyTag + " />", ""); // cut off the main element
                    }
                }
                else if (Json.IndexOf("<") == 0)
                {
                    XML = Json;
                }

            }
            catch (Exception)
            {
                XML = "";
            }

            return XML;
        }

        public string XmlToJson(string XML)
        {
            // returns the XML result as Json 
            XML = XML.Replace("|", " ");
            string Json = "";
            string MainBodyTag = "jamaXml";

            try
            {
                if (!string.IsNullOrWhiteSpace(XML))
                {
                    if (XML.IndexOf("<") == 0)
                    {
                        try
                        {
                            XML = XML.Replace("\"", "'");
                            XmlDocument xmlDoc = new XmlDocument();
                            xmlDoc.LoadXml(XML);
                            Json = JsonConvert.SerializeXmlNode(xmlDoc);
                        }
                        catch (Exception)
                        {
                            // no main body element, add and try again
                            XML = ("<" + MainBodyTag + ">") + XML + ("</" + MainBodyTag + ">");
                            XmlDocument xmlDoc = new XmlDocument();
                            xmlDoc.LoadXml(XML);
                            Json = JsonConvert.SerializeXmlNode(xmlDoc);
                        }

                        if (XML.IndexOf("<" + MainBodyTag + ">") == 0)
                        {
                            // XML had main boy element of <xml>
                            Json = Json.Replace("{\"" + MainBodyTag + "\":", ""); // cut off the main element, because jon doesn't need it
                            Json = Json.Substring(0, (Json.LastIndexOf("}"))); // cut off the last }, which is double
                        }
                    }
                    else if (XML.IndexOf("{") == 0)
                    {
                        Json = XML;
                    }
                }
            }
            catch (Exception)
            {
                Json = "";
            }

            return Json;
        }
    }
}