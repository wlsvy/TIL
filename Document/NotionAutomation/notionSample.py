from notion.client import NotionClient

client = NotionClient(token_v2 = "2f610594f0f8c246cd75d7cb71c2b441a1c4369d707a8d36bf2f1e083b20b5ba96f227376e7a4f38fa61f46f02c5afc265a25f12b1808074b2a47b2086597418a2304500b4841a0c3c86a8dd1881")
print(client)

mainPage = client.get_block("https://www.notion.so/6485647f2f4b4bfbac195211e43f91b0")
print(mainPage)
print(f'MainPage: Id[{mainPage}], Title[{mainPage.title}], Type[{mainPage.type}]')

print("=====================")

for child in mainPage.children:
    print(f'childPage: Id[{child}], Title[{child.title}], Type[{child.type}]')
    
print("=====================")
    
bookPage = client.get_block("https://www.notion.so/63d758d87e41483ebab7def5d939f616?v=9da806e4055d47c8a69001705d6e9879")
print(f'bookPage: Id[{bookPage}], Title[{bookPage.title}], Type[{bookPage.type}], collection[{bookPage.collection}]')

print("=====================")


lp = client.get_collection_view("https://www.notion.so/63d758d87e41483ebab7def5d939f616?v=9da806e4055d47c8a69001705d6e9879")
cb =client.get_block("https://www.notion.so/63d758d87e41483ebab7def5d939f616?v=9da806e4055d47c8a69001705d6e9879")

print(cb.type)