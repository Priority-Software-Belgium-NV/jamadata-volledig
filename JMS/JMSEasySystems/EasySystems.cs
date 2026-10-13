using Newtonsoft.Json;
using Newtonsoft.Json.Linq;
using System;
using System.Collections.Generic;
using System.IO;
using System.Linq;
using System.Net;
using System.Net.Http;
using System.Net.Http.Headers;
using System.Text;
using System.Threading.Tasks;

namespace JMSEasySystems
{
    public class EasySystems
    {
        // Test endpoints
        private static string AuthURIDebug = "https://auth-test.4exchange.app";
        private static string BaseURIDebug = "https://apitest.tradeinterop.4cee.com";

        // Production endpoints
        private static string AuthURI = "https://auth.4exchange.app";
        private static string BaseURI = "https://api.tradeinterop.4cee.com";

        private static string EasyBearerTokenIn = null;
        private static string EasyBearerTokenOut = null;

        static EasySystems()
        {
            ServicePointManager.SecurityProtocol = SecurityProtocolType.Tls12;
        }

        [STAThread]
        private static string Authenticate(string clientId, string clientSecret, bool isOut, string debug)
        {
            try
            {
                return AuthenticateAsync(clientId, clientSecret, isOut, debug).GetAwaiter().GetResult();
            }
            catch (Exception e)
            {
                return e.Message;
            }
        }

        private static async Task<string> AuthenticateAsync(string clientId, string clientSecret, bool isOut, string debug)
        {
            string authURI = debug.ToLower() == "yes" ? AuthURIDebug : AuthURI;

            try
            {
                var client = new HttpClient();
                var tokenUrl = authURI + "/oauth2/token";

                var request = new HttpRequestMessage(HttpMethod.Post, tokenUrl);
                request.Headers.Accept.Add(new System.Net.Http.Headers.MediaTypeWithQualityHeaderValue("application/json"));

                request.Content = new FormUrlEncodedContent(new[]
                {
                    new KeyValuePair<string, string>("grant_type", "client_credentials"),
                    new KeyValuePair<string, string>("client_id", clientId),
                    new KeyValuePair<string, string>("client_secret", clientSecret),
                    new KeyValuePair<string, string>("scope", "4Exchange/receive 4Exchange/send")
                });

                request.Content.Headers.ContentType = new System.Net.Http.Headers.MediaTypeHeaderValue("application/x-www-form-urlencoded");

                var response = await client.SendAsync(request);
                response.EnsureSuccessStatusCode();

                var payload = await response.Content.ReadAsStringAsync();
                EasySystemsBearerToken bearerToken = JsonConvert.DeserializeObject<EasySystemsBearerToken>(payload);

                if (isOut)
                    EasyBearerTokenOut = bearerToken.access_token;
                else
                    EasyBearerTokenIn = bearerToken.access_token;

                return "OK";
            }
            catch (Exception e)
            {
                return e.Message;
            }
        }

        [STAThread]
        public static string SendDocument(string clientId, string clientSecret, string fileName, string debug)
        {
            try
            {
                return SendDocumentAsync(clientId, clientSecret, fileName, debug).GetAwaiter().GetResult();
            }
            catch (Exception e)
            {
                return e.Message;
            }
        }

        private static async Task<string> SendDocumentAsync(string clientId, string clientSecret, string fileName, string debug)
        {
            string baseURI = debug.ToLower() == "yes" ? BaseURIDebug : BaseURI;

            for (int i = 0; i < 2; i++)
            {
                var client = new HttpClient();
                client.DefaultRequestHeaders.Authorization = new AuthenticationHeaderValue("Bearer", EasyBearerTokenOut);
                var fileBytes = File.ReadAllBytes(fileName);
                var fileContent = new ByteArrayContent(fileBytes);
                fileContent.Headers.ContentType = new MediaTypeHeaderValue("application/xml");

                HttpResponseMessage response = await client.PostAsync(baseURI + "/v3/documents/invoice/send/xml", fileContent);

                if (response.StatusCode == HttpStatusCode.Unauthorized)
                {
                    var authResult = Authenticate(clientId, clientSecret, true, debug);

                    if (authResult == "OK")
                        continue;

                    return authResult;
                }

                if (response.IsSuccessStatusCode)
                {
                    var result = await response.Content.ReadAsStringAsync();
                    EasySystemsSendDocumentResult sendDocumentResult = JsonConvert.DeserializeObject<EasySystemsSendDocumentResult>(result);
                    return string.Format("OK - {0}", sendDocumentResult.documentId);
                }

                return response.ReasonPhrase;
            }

            return "NOK";
        }

        [STAThread]
        public static string GetDocumentStatus(string clientId, string clientSecret, string documentId, string debug)
        {
            try
            {
                return GetDocumentStatusAsync(clientId, clientSecret, documentId, debug).GetAwaiter().GetResult();
            }
            catch (Exception e)
            {
                return e.Message;
            }
        }

        private static async Task<string> GetDocumentStatusAsync(string clientId, string clientSecret, string documentId, string debug)
        {
            string baseURI = debug.ToLower() == "yes" ? BaseURIDebug : BaseURI;

            for (int i = 0; i < 2; i++)
            {
                var client = new HttpClient();
                client.DefaultRequestHeaders.Authorization = new AuthenticationHeaderValue("Bearer", EasyBearerTokenOut);
                HttpResponseMessage response = await client.GetAsync(baseURI + "/v3/documents/status/" + documentId);

                if (response.StatusCode == HttpStatusCode.Unauthorized)
                {
                    var authResult = Authenticate(clientId, clientSecret, true, debug);

                    if (authResult == "OK")
                        continue;

                    return authResult;
                }

                if (response.IsSuccessStatusCode)
                {
                    var result = await response.Content.ReadAsStringAsync();
                    EasySystemsDocumentStatus documentStatus = JsonConvert.DeserializeObject<EasySystemsDocumentStatus>(result);

                    if (string.IsNullOrWhiteSpace(documentStatus.errorMessage))
                        return string.Format("OK - {0}", documentStatus.status);

                    return string.Format("{0} - {1}", documentStatus.status, documentStatus.errorMessage);
                }

                return response.ReasonPhrase;
            }

            return "NOK";
        }

        public static string ExportDocuments(string clientId, string clientSecret, string folder, string markAsExported, string debug)
        {
            try
            {
                var resultArray = ExportDocumentList(clientId, clientSecret, debug);

                if (resultArray[0] == "NoContent")
                    return "OK";

                if (resultArray[0] != "OK")
                    return resultArray[0];

                if (resultArray.Length > 1)
                {
                    for (int i = 1; i < resultArray.Length; i++)
                    {
                        var exportResult = ExportDocument(clientId, clientSecret, resultArray[i], folder, debug);

                        if (exportResult != "OK")
                            return string.Format("Document {0} could not be exported.", resultArray[i]);

                        if (markAsExported == "YES")
                        {
                            var result = MarkDocumentAsExported(clientId, clientSecret, resultArray[i], debug);

                            if (result.ToUpper() != "OK")
                                return result;
                        }
                    }
                }

                return "OK";
            }
            catch (Exception e)
            {
                return e.Message;
            }
        }

        [STAThread]
        private static string[] ExportDocumentList(string clientId, string clientSecret, string debug)
        {
            try
            {
                return ExportDocumentListAsync(clientId, clientSecret, debug).GetAwaiter().GetResult();
            }
            catch (Exception e)
            {
                return new string[] { e.Message };
            }
        }

        private static async Task<string[]> ExportDocumentListAsync(string clientId, string clientSecret, string debug)
        {
            string baseURI = debug.ToLower() == "yes" ? BaseURIDebug : BaseURI;

            for (int i = 0; i < 2; i++)
            {
                var client = new HttpClient();
                client.DefaultRequestHeaders.Authorization = new AuthenticationHeaderValue("Bearer", EasyBearerTokenIn);
                HttpResponseMessage response = await client.GetAsync(baseURI + "/v3/documents/export/list");

                if (response.StatusCode == HttpStatusCode.Unauthorized)
                {
                    var authResult = Authenticate(clientId, clientSecret, false, debug);

                    if (authResult == "OK")
                        continue;

                    return new string[] { authResult };
                }

                if (response.StatusCode == HttpStatusCode.NoContent)
                {
                    return new string[] { "NoContent" };
                }

                if (response.IsSuccessStatusCode)
                {
                    string result = await response.Content.ReadAsStringAsync();
                    string[] resultArrayTemp =  JsonConvert.DeserializeObject<string[]>(result);
                    string[] resultArray = (new[] { "OK" }).Concat(resultArrayTemp).ToArray();
                    return resultArray;
                }

                return new string[] { response.ReasonPhrase };
            }

            return new string[] { "NOK" };
        }

        [STAThread]
        private static string ExportDocument(string clientId, string clientSecret, string documentId, string folder, string debug)
        {
            try
            {
                return ExportDocumentAsync(clientId, clientSecret, documentId, folder, debug).GetAwaiter().GetResult();
            }
            catch (Exception e)
            {
                return e.Message;
            }
        }

        private static async Task<string> ExportDocumentAsync(string clientId, string clientSecret, string documentId, string folder, string debug)
        {
            string baseURI = debug.ToLower() == "yes" ? BaseURIDebug : BaseURI;

            for (int i = 0; i < 2; i++)
            {
                var client = new HttpClient();
                client.DefaultRequestHeaders.Authorization = new AuthenticationHeaderValue("Bearer", EasyBearerTokenIn);
                var response = await client.GetAsync(baseURI + "/v3/documents/export/" + documentId);

                if (response.StatusCode == HttpStatusCode.Unauthorized)
                {
                    var authResult = Authenticate(clientId, clientSecret, false, debug);

                    if (authResult == "OK")
                        continue;

                    return authResult;
                }

                if (response.IsSuccessStatusCode)
                {
                    string result = await response.Content.ReadAsStringAsync();
                    EasySystemsDocument document = JsonConvert.DeserializeObject<EasySystemsDocument>(result);
                    File.WriteAllText(string.Format(@"{0}\{1}.xml", folder, document.documentId), document.xml);
                    return "OK";
                }

                return response.ReasonPhrase;
            }

            return "NOK";
        }

        [STAThread]
        public static string MarkDocumentAsExported(string clientId, string clientSecret, string documentId, string debug)
        {
            try
            {
                return MarkDocumentAsExportedAsync(clientId, clientSecret, documentId, debug).GetAwaiter().GetResult();
            }
            catch (Exception e)
            {
                return e.Message;
            }
        }

        private static async Task<string> MarkDocumentAsExportedAsync(string clientId, string clientSecret, string documentId, string debug)
        {
            string baseURI = debug.ToLower() == "yes" ? BaseURIDebug : BaseURI;

            for (int i = 0; i < 2; i++)
            {
                HttpClient client = new HttpClient();
                client.DefaultRequestHeaders.Authorization = new AuthenticationHeaderValue("Bearer", EasyBearerTokenIn);
                string tokenUrl = string.Format("{0}/v3/documents/export/{1}/status", baseURI, documentId);

                string json = $"{{\"status\":\"EXPORTED\"}}";
                StringContent content = new StringContent(json, Encoding.UTF8, "application/json");

                HttpResponseMessage response = await client.PostAsync(tokenUrl, content);

                if (response.StatusCode == HttpStatusCode.Unauthorized)
                {
                    string authResult = Authenticate(clientId, clientSecret, false, debug);

                    if (authResult == "OK")
                        continue;

                    return authResult;
                }

                if (response.IsSuccessStatusCode)
                    return "OK";

                return response.ReasonPhrase;
            }

            return "NOK";
        }

        [STAThread]
        public static string Lookup(string clientId, string clientSecret, string scheme, string lookupCode, string debug)
        {
            try
            {
                return LookupAsync(clientId, clientSecret, scheme, lookupCode, debug).GetAwaiter().GetResult();
            }
            catch (Exception e)
            {
                return e.Message;
            }
        }

        private static async Task<string> LookupAsync(string clientId, string clientSecret, string scheme, string lookupCode, string debug)
        {
            string baseURI = debug.ToLower() == "yes" ? BaseURIDebug : BaseURI;

            for (int i = 0; i < 2; i++)
            {
                var client = new HttpClient();
                client.DefaultRequestHeaders.Authorization = new AuthenticationHeaderValue("Bearer", EasyBearerTokenOut);
                var response = await client.GetAsync(string.Format("{0}/v3/sml-lookup?scheme={1}&id={2}", baseURI, scheme, lookupCode));

                if (response.StatusCode == HttpStatusCode.Unauthorized)
                {
                    var authResult = Authenticate(clientId, clientSecret, true, debug);

                    if (authResult == "OK")
                        continue;

                    return authResult;
                }

                if (response.StatusCode == HttpStatusCode.NotFound)
                    return string.Format("NOK - Niks gevonden voor {0}:{1}", scheme, lookupCode);

                if (response.IsSuccessStatusCode)
                {
                    string result = await response.Content.ReadAsStringAsync();
                    JObject obj = JObject.Parse(result);
                    return string.Format("OK - {0} - {1}", (string)obj["status"], (string)obj["message"]);
                }

                return response.ReasonPhrase;
            }

            return "NOK";
        }
    }

    class EasySystemsBearerToken
    {
        public string access_token
        {
            get; set;
        }

        public string scope
        {
            get; set;
        }

        public string expires_in
        {
            get; set;
        }

        public string token_type
        {
            get; set;
        }
    }

    class EasySystemsSendDocumentResult
    {
        public string message
        {
            get; set;
        }

        public string documentId
        {
            get; set;
        }
    }

    class EasySystemsDocumentStatus
    {
        public string documentId
        {
            get; set;
        }

        public string status
        {
            get; set;
        }

        public string importDate
        {
            get; set;
        }

        public string exportDate
        {
            get; set;
        }

        public string errorMessage
        {
            get; set;
        }
    }

    class EasySystemsDocument
    {
        public string documentId
        {
            get; set;
        }

        public string xml
        {
            get; set;
        }

        public EasySystemsImage image
        {
            get; set;
        }

        public EasySystemsAttachment[] attachments
        {
            get; set;
        }
    }

    internal class EasySystemsImage
    {
        public string url
        {
            get; set;
        }

        public string fileName
        {
            get; set;
        }
    }

    internal class EasySystemsAttachment
    {
        public string url
        {
            get; set;
        }

        public string fileName
        {
            get; set;
        }
    }

    class EasySystemsValidationResult
    {
        public string transactionId
        {
            get; set;
        }

        public string validationResult
        {
            get; set;
        }

        public EasySystemsValidationResults validationResults
        {
            get; set;
        }
    }

    internal class EasySystemsValidationResults
    {
        public EasySystemsValidationResultSection xmlSyntax
        {
            get; set;
        }

        public EasySystemsValidationResultSection xsdValidation
        {
            get; set;
        }

        public EasySystemsSchematronValidation[] schematronValidation
        {
            get; set;
        }
    }

    internal class EasySystemsValidationResultSection
    {
        public string valid
        {
            get; set;
        }

        public EasySystemsMessage[] messages
        {
            get; set;
        }

        public string result
        {
            get; set;
        }
    }

    internal class EasySystemsMessage
    {
        public string id
        {
            get; set;
        }

        public string flag
        {
            get; set;
        }

        public string location
        {
            get; set;
        }

        public string test
        {
            get; set;
        }

        public string message
        {
            get; set;
        }
    }

    internal class EasySystemsSchematronValidation
    {
        public string xslFile
        {
            get; set;
        }

        public string valid
        {
            get; set;
        }

        public int warnings
        {
            get; set;
        }

        public int errors
        {
            get; set;
        }

        public EasySystemsMessage[] messages
        {
            get; set;
        }
    }
}