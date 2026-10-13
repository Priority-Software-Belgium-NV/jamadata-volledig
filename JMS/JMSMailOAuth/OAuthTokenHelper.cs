using System;
using System.IO;
using System.Threading.Tasks;

using Google.Apis.Auth.OAuth2;
using Microsoft.Identity.Client;

/// <summary>
/// Kleine helperlib (NET Framework 4.6.2) om OAuth2 access tokens op te halen
/// voor Microsoft 365 (Exchange Online / SMTP AUTH) en Gmail/Google Workspace.
///
/// Gebruik samen met MailBee: geef het geretourneerde access token door aan
/// MailBee.OAuth2.GetXOAuthKeyStatic(email, accessToken) en zet vervolgens
/// AuthMethods = SaslOAuth2, Password = XOAUTH2-string, SslMode = UseStartTls.
/// </summary>
public static class OAuthTokenHelper
{
    // =============================
    // Microsoft 365 / Exchange Online
    // App-permissions (client credentials) – non-interactive
    // Vereist: in AAD de app-registratie met toestemming voor SMTP.SendAsApp
    // en (desgewenst) IMAP.AccessAsApp/POP.AccessAsApp. Admin consent nodig.
    // =============================

    /// <summary>
    /// Haalt een access token op voor SMTP AUTH in Exchange Online (client credentials flow).
    /// Scopes/resource: https://outlook.office365.com/.default
    /// </summary>
    public static string GetO365AccessToken(string tenantId, string clientId, string clientSecret)
    {
        return GetO365AccessTokenAsync(tenantId, clientId, clientSecret)
        .GetAwaiter().GetResult();
    }

    /// <summary>
    /// Async variant (aanbevolen als je dit in async code gebruikt).
    /// </summary>
    public static async Task<string> GetO365AccessTokenAsync(string tenantId, string clientId, string clientSecret)
    {
        if (string.IsNullOrWhiteSpace(tenantId)) throw new ArgumentException("tenantId is leeg");
        if (string.IsNullOrWhiteSpace(clientId)) throw new ArgumentException("clientId is leeg");
        if (string.IsNullOrWhiteSpace(clientSecret)) throw new ArgumentException("clientSecret is leeg");

        var app = ConfidentialClientApplicationBuilder
        .Create(clientId)
        .WithTenantId(tenantId)
        .WithClientSecret(clientSecret)
        .Build();

        // SMTP AUTH in EXO gebruikt de OUTLOOK resource
        var scopes = new[] { "https://outlook.office365.com/.default" };

        var result = await app
        .AcquireTokenForClient(scopes)
        .ExecuteAsync()
        .ConfigureAwait(false);


        return result.AccessToken;
    }

    // =============================
    // Google Workspace / Gmail via Service Account + Domain-Wide Delegation
    // Non-interactive: impersonate een gebruiker in het domein.
    // Vereist: SA-json (p12/json) met DWD ingeschakeld en admin-config in Workspace.
    // =============================

    /// <summary>
    /// Haalt een access token op voor Gmail SMTP via service account met domain-wide delegation.
    /// Impersonate de mailboxgebruiker met de volledige scope "https://mail.google.com/".
    /// </summary>
    public static string GetGmailAccessTokenFromServiceAccount(string serviceAccountJsonPath, string userToImpersonate)
    {
        return GetGmailAccessTokenFromServiceAccountAsync(serviceAccountJsonPath, userToImpersonate)
        .GetAwaiter().GetResult();
    }

    /// <summary>
    /// Async variant voor Gmail service account flow.
    /// </summary>
    public static async Task<string> GetGmailAccessTokenFromServiceAccountAsync(string serviceAccountJsonPath, string userToImpersonate)
    {
        if (string.IsNullOrWhiteSpace(serviceAccountJsonPath)) throw new ArgumentException("Pad naar service-account JSON is leeg");
        if (!File.Exists(serviceAccountJsonPath)) throw new FileNotFoundException("Service-account JSON niet gevonden", serviceAccountJsonPath);
        if (string.IsNullOrWhiteSpace(userToImpersonate)) throw new ArgumentException("userToImpersonate (mailbox) is leeg");

        var scopes = new[] { "https://mail.google.com/" }; // SMTP/IMAP/POP volledige toegang

        GoogleCredential credential;
        using (var stream = new FileStream(serviceAccountJsonPath, FileMode.Open, FileAccess.Read))
        {
            credential = GoogleCredential.FromStream(stream)
            .CreateScoped(scopes)
            .CreateWithUser(userToImpersonate);
        }

        // Haal het access token op – geldig ~1 uur
        var token = await credential.UnderlyingCredential
        .GetAccessTokenForRequestAsync()
        .ConfigureAwait(false);

        return token;
    }
}