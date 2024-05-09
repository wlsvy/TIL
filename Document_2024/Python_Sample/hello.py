import requests

print("hello World")



def ask_chatgpt(question, model="gpt-4", temperature=0.7):
    # OpenAI API의 엔드포인트 URL
    url = "https://api.openai.com/v1/completions"
    api_key = ""

    # 요청 헤더
    headers = {
        "Authorization": f"Bearer {api_key}",
        "Content-Type": "application/json",
    }

    # 요청 본문 데이터
    data = {
        "model": model,
        "prompt": question,
        "temperature": temperature,
        "max_tokens": 100,
    }

    # POST 요청 보내기
    response = requests.post(url, headers=headers, json=data, verify=False)

    # 응답 데이터 확인
    if response.status_code == 200:
        # 성공적으로 응답 받음
        response_data = response.json()
        return response_data["choices"][0]["text"].strip()
    else:
        # 오류 발생
        return f"Error: {response.status_code}"
    
    
# 질문 예시
question = "c# 최신 스펙에 대해 알려줘"
response_text = ask_chatgpt(question)
print(response_text)