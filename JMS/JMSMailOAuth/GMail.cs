using System;
using System.Collections.Generic;
using System.IO;
using System.Linq;
using System.Net;
using System.Net.Http;
using System.Text;
using System.Threading.Tasks;
using JMSTools;
using MailKit.Net.Smtp;
using MailKit.Security;
using MimeKit;
using Newtonsoft.Json;
using Newtonsoft.Json.Linq;

namespace JMSMailOAuth
{
    public class GMail
    {
        static int mailProfile;
        static string[] splitCmd;

        [STAThread]
        public static string SendMail(string PathMailTemplates, string PathSpoolFiles, string Cmd)
        {
            try
            {
                return SendMailAsync(PathMailTemplates, PathSpoolFiles, Cmd).GetAwaiter().GetResult();
            }
            catch (Exception e)
            {
                return e.Message;
            }
        }

        public static async Task<string> SendMailAsync(string PathMailTemplates, string PathSpoolFiles, string Cmd)
        {
            ServicePointManager.SecurityProtocol = SecurityProtocolType.Tls12;

            var credentials = LoadCredentials("credentials.json");
            string clientId = credentials.ClientId;
            string clientSecret = credentials.ClientSecret;
            string redirectUri = credentials.RedirectUris[0];

            TokenResponse token;

            if (File.Exists("token.json"))
            {
                var existing = LoadToken("token.json");
                token = await RefreshAccessTokenAsync(clientId, clientSecret, existing.RefreshToken);
                token.RefreshToken = existing.RefreshToken;
            }
            else
            {
                string authUrl = $"https://accounts.google.com/o/oauth2/v2/auth" +
                                 $"?scope=https%3A%2F%2Fmail.google.com" +
                                 $"&access_type=offline" +
                                 $"&include_granted_scopes=true" +
                                 $"&prompt=consent" +
                                 $"&response_type=code" +
                                 $"&client_id={Uri.EscapeDataString(clientId)}" +
                                 $"&redirect_uri={Uri.EscapeDataString(redirectUri)}";

                Console.WriteLine("Open deze URL in je browser:\n" + authUrl);
                Console.Write("\nPlak hier de autorisatiecode: ");
                string authCode = Console.ReadLine();

                token = await ExchangeCodeForTokenAsync(clientId, clientSecret, redirectUri, authCode);
            }

            SaveToken("token.json", token);

            splitCmd = Cmd.Split(new string[] { "\r\n" }, 20, StringSplitOptions.RemoveEmptyEntries);

            string template = GetString("Template|")[1];

            if (string.IsNullOrWhiteSpace(template))
                return "Template werd niet gespecifieerd.";

            if (!File.Exists(PathMailTemplates + template + ".eml"))
                return "Template {template} werd niet gevonden.";

            var templateMessage = MimeMessage.Load(PathMailTemplates + template + ".eml");
            var htmlPart = templateMessage.HtmlBody;
            var subject = templateMessage.Subject;
            var replaces = GetReplaces();

            foreach (string replace in replaces)
            {
                string[] replaceParts = replace.Split('|');
                htmlPart = htmlPart.Replace("[" + replaceParts[1] + "]", replaceParts[2]);
                subject = subject.Replace("[" + replaceParts[1] + "]", replaceParts[2]);
            }

            mailProfile = GetInteger("MailProfile|");
            var myIni = new IniFile("jms.ini");
            string mailFromName = myIni.Read(MakeMailKeyword("MailFromName"), "MailSettings");
            string mailFromAddress = myIni.Read(MakeMailKeyword("MailFromAddress"), "MailSettings");
            string mailReplyTo = myIni.Read(MakeMailKeyword("MailReplyTo"), "MailSettings");
            string mailConfirmReadTo = myIni.Read(MakeMailKeyword("MailConfirmReadTo"), "MailSettings");
            string mailConfirmReceiptTo = myIni.Read(MakeMailKeyword("MailConfirmReceiptTo"), "MailSettings");

            var message = new MimeMessage();
            message.Date = DateTime.Now;

            if (string.IsNullOrWhiteSpace(mailFromName))
                message.From.Add(MailboxAddress.Parse(mailFromAddress));
            else
                message.From.Add(new MailboxAddress(mailFromName, mailFromAddress));

            if (!string.IsNullOrWhiteSpace(mailReplyTo))
                message.ReplyTo.Add(MailboxAddress.Parse(mailReplyTo));

            if (!string.IsNullOrWhiteSpace(mailConfirmReadTo))
                message.Headers.Add(HeaderId.DispositionNotificationTo, mailConfirmReadTo);

            if (!string.IsNullOrWhiteSpace(mailConfirmReceiptTo))
                message.Headers.Add(HeaderId.ReturnReceiptTo, mailConfirmReceiptTo);


            string[] to = GetString("To|");

            if (to.Count() == 2)
                message.To.Add(MailboxAddress.Parse(to[1]));
            else
                message.To.Add(new MailboxAddress(to[2], to[1]));

            string[] cc = GetString("CC|");

            if (cc.Count() > 1) {
                if (cc.Count() == 2)
                    message.Cc.Add(MailboxAddress.Parse(cc[1]));
                else
                    message.Cc.Add(new MailboxAddress(cc[2], cc[1]));
            }

            string[] bcc = GetString("BCC|");

            if (bcc.Count() > 1)
            {
                if (bcc.Count() == 2)
                    message.Bcc.Add(MailboxAddress.Parse(bcc[1]));
                else
                    message.Bcc.Add(new MailboxAddress(bcc[2], bcc[1]));
            }

            message.Subject = subject;

            var builder = new BodyBuilder
            {
                HtmlBody = htmlPart
            };

            message.Body = builder.ToMessageBody();

            string[] attachmentFile = GetString("AttachJamaFileRef|");
            string[] extraFile = GetString("AttachThisFile|");

            if (attachmentFile.Count() == 2 || extraFile.Count() == 2)
            {
                string prefix = string.Format("{0:X}", int.Parse(attachmentFile[1])).PadLeft(8, '0');
                string jamadataFile = string.Format("{0}{1}*.*", PathSpoolFiles, prefix);
                IEnumerable<string> files = Directory.EnumerateFiles(Path.GetDirectoryName(jamadataFile), Path.GetFileName(jamadataFile));

                if (attachmentFile.Count() > 1 && files.Count() == 1 && File.Exists(files.First()) || File.Exists(extraFile[1]))
                {
                    var multipart = new Multipart("mixed");
                    multipart.Add(message.Body);

                    if (attachmentFile.Count() > 1 && files.Count() == 1 && File.Exists(files.First()))
                    {
                        string[] friendlyNames = files.First().Split('$');
                        string friendlyName = friendlyNames.Count() == 2 ? friendlyNames[1] : Path.GetFileName(files.First());
                        string[] mediaSubTypes = friendlyName.Split('.');
                        string mediaSubType = mediaSubTypes.Count() > 1 ? mediaSubTypes.Last() : "octet-stream";

                        var attachment = new MimePart("application", mediaSubType)
                        {
                            Content = new MimeContent(File.OpenRead(files.First())),
                            ContentDisposition = new ContentDisposition(ContentDisposition.Attachment),
                            ContentTransferEncoding = ContentEncoding.Base64,
                            FileName = friendlyName
                        };

                        multipart.Add(attachment);
                    }

                    if (File.Exists(extraFile[1]))
                    {
                        string friendlyName = Path.GetFileName(extraFile[1]);
                        string[] mediaSubTypes = friendlyName.Split('.');
                        string mediaSubType = mediaSubTypes.Count() > 1 ? mediaSubTypes.Last() : "octet-stream";

                        var attachment = new MimePart("application", mediaSubType)
                        {
                            Content = new MimeContent(File.OpenRead(extraFile[1])),
                            ContentDisposition = new ContentDisposition(ContentDisposition.Attachment),
                            ContentTransferEncoding = ContentEncoding.Base64,
                            FileName = friendlyName
                        };

                        multipart.Add(attachment);
                    }

                    message.Body = multipart;
                }
            }

            try
            {
                using (var smtp = new SmtpClient())
                {
                    await smtp.ConnectAsync("smtp.gmail.com", 587, SecureSocketOptions.StartTls);
                    var oauth2 = new SaslMechanismOAuth2(mailFromAddress, token.AccessToken);
                    await smtp.AuthenticateAsync(oauth2);
                    await smtp.SendAsync(message);
                    await smtp.DisconnectAsync(true);
                }
            }
            catch (Exception e)
            {
                return e.Message;
            }

            return "OK";
        }

        static GoogleCredentials LoadCredentials(string path)
        {
            var json = File.ReadAllText(path);
            var root = JsonConvert.DeserializeObject<RootObject>(json);
            return root.Installed;
        }

        static TokenResponse LoadToken(string path)
        {
            var json = File.ReadAllText(path);
            return JsonConvert.DeserializeObject<TokenResponse>(json);
        }

        static void SaveToken(string path, TokenResponse token)
        {
            var json = JsonConvert.SerializeObject(token, Formatting.Indented);
            File.WriteAllText(path, json);
        }

        static async Task<TokenResponse> RefreshAccessTokenAsync(string clientId, string clientSecret, string refreshToken)
        {
            using (var client = new HttpClient())
            {
                var content = new FormUrlEncodedContent(new[]
                {
                    new KeyValuePair<string, string>("client_id", clientId),
                    new KeyValuePair<string, string>("client_secret", clientSecret),
                    new KeyValuePair<string, string>("refresh_token", refreshToken),
                    new KeyValuePair<string, string>("grant_type", "refresh_token")
                });

                var response = await client.PostAsync("https://oauth2.googleapis.com/token", content);
                var json = await response.Content.ReadAsStringAsync();
                var obj = JObject.Parse(json);

                return new TokenResponse
                {
                    AccessToken = obj["access_token"]?.ToString(),
                    ExpiresIn = obj["expires_in"]?.ToString(),
                    TokenType = obj["token_type"]?.ToString(),
                    RefreshToken = refreshToken
                };
            }
        }

        static async Task<TokenResponse> ExchangeCodeForTokenAsync(string clientId, string clientSecret, string redirectUri, string code)
        {
            using (var client = new HttpClient())
            {
                var content = new FormUrlEncodedContent(new[]
                {
                    new KeyValuePair<string, string>("code", code),
                    new KeyValuePair<string, string>("client_id", clientId),
                    new KeyValuePair<string, string>("client_secret", clientSecret),
                    new KeyValuePair<string, string>("redirect_uri", redirectUri),
                    new KeyValuePair<string, string>("grant_type", "authorization_code")
                });

                var response = await client.PostAsync("https://oauth2.googleapis.com/token", content);
                var json = await response.Content.ReadAsStringAsync();
                var obj = JObject.Parse(json);

                return new TokenResponse
                {
                    AccessToken = obj["access_token"]?.ToString(),
                    RefreshToken = obj["refresh_token"]?.ToString(),
                    ExpiresIn = obj["expires_in"]?.ToString(),
                    TokenType = obj["token_type"]?.ToString()
                };
            }
        }

        static async Task<string> GetAccessTokenAsync(string clientId, string clientSecret, string refreshToken)
        {
            using (var client = new HttpClient())
            {
                var content = new FormUrlEncodedContent(new[]
                {
                    new KeyValuePair<string, string>("client_id", clientId),
                    new KeyValuePair<string, string>("client_secret", clientSecret),
                    new KeyValuePair<string, string>("refresh_token", refreshToken),
                    new KeyValuePair<string, string>("grant_type", "refresh_token")
                });

                var response = await client.PostAsync("https://oauth2.googleapis.com/token", content);
                var json = await response.Content.ReadAsStringAsync();
                var tokenData = JObject.Parse(json);

                return tokenData["access_token"].ToString();
            }
        }

        private static int GetInteger(string toSearch)
        {
            IEnumerable<string> matches_ = splitCmd.Where(s => s.StartsWith(toSearch, StringComparison.InvariantCultureIgnoreCase));

            if (matches_.Count() == 1)
                return int.Parse(matches_.First().Split('|')[1]);

            return 0;
        }

        private static string[] GetString(string toSearch)
        {
            IEnumerable<string> matches_ = splitCmd.Where(s => s.StartsWith(toSearch, StringComparison.InvariantCultureIgnoreCase));

            if (matches_.Count() == 1)
                return matches_.First().Split(new char[] { '|' }, StringSplitOptions.RemoveEmptyEntries);

            return new string[] { "" } ;
        }

        private static IEnumerable<string> GetReplaces()
        {
            return splitCmd.Where(s => s.StartsWith("Replace|", StringComparison.InvariantCultureIgnoreCase));
        }

        private static string MakeMailKeyword(string keyWord) => mailProfile == 0 ? keyWord : string.Format("%s%d", keyWord, mailProfile);
    }

    class RootObject
    {
        [JsonProperty("installed")]
        public GoogleCredentials Installed { get; set; }
    }

    class GoogleCredentials
    {
        [JsonProperty("client_id")]
        public string ClientId { get; set; }

        [JsonProperty("client_secret")]
        public string ClientSecret { get; set; }

        [JsonProperty("redirect_uris")]
        public List<string> RedirectUris { get; set; }
    }

    class TokenResponse
    {
        [JsonProperty("access_token")]
        public string AccessToken { get; set; }

        [JsonProperty("refresh_token")]
        public string RefreshToken { get; set; }

        [JsonProperty("expires_in")]
        public string ExpiresIn { get; set; }

        [JsonProperty("token_type")]
        public string TokenType { get; set; }
    }
}