import requests

url = "https://api.notion.com/v1/databases/63d758d87e41483ebab7def5d939f616"

headers = {
    "Accept": "application/json",
    "Notion-Version": "2022-02-22",
    "Authorization": "Bearer secret_V03L7Q3wQGwizHR1KStIE5yT3m1PM36JJhUouWfEdTj"
}

response = requests.get(url, headers=headers)

print(response.text)