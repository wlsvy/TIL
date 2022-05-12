using RestSharp;
using RestSharp.Authenticators.OAuth2;
using System;
using System.Threading.Tasks;

namespace CSsample
{
    public static class Program
    {
        private static async Task Main()
        {
            var client = new RestClient("https://api.notion.com/v1/databases/63d758d87e41483ebab7def5d939f616");
            client.Authenticator = new OAuth2AuthorizationRequestHeaderAuthenticator(
                accessToken: "secret_V03L7Q3wQGwizHR1KStIE5yT3m1PM36JJhUouWfEdTj",
                tokenType: "Bearer");

            var request = new RestRequest();
            request.Method = Method.Get;
            request.AddHeader("Accept", "application/json");
            request.AddHeader("Notion-Version", "2022-02-22");
            request.AddHeader("Authorization", "Bearer secret_V03L7Q3wQGwizHR1KStIE5yT3m1PM36JJhUouWfEdTj");

            var response = await client.GetAsync(request);
            Console.WriteLine(response.Content);
        }
    }
}