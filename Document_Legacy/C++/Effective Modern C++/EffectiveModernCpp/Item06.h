#pragma once
#include <iostream>
#include <vector>
#include <string>
using namespace std;

//auto 가 원하지 않는 형식으로 연역될 때에는 명시적 형식의 초기치를 사용하라

namespace Item06 {
	/*
		겉으로는 보이지 않는 대리자 타입을 주의할 것.

		보이지 않는 대리자 형식 때문에 auto가 초기화 표현식의 형식을 "잘못" 연역할 수 있다.
	*/

	inline vector<bool> CreateBoolVector() { return vector<bool>(10); }
	void TestBool(const bool b) { }

	inline void RunSample() {

		bool value = CreateBoolVector()[5];

		auto autoValue = CreateBoolVector()[5];

		/*
			autoValue 의 타입은 bool 이 아니라 vector<bool>::reference 이다.

			std::vector<bool> 의 경우, bool 값을 1바이트가 아닌 비트값으로 표현하는데

			vector<bool>::reference 는 std::vector<bool> 가 관리하는 비트들을 담은 자료구조의 한 워드를 가리키는 포인터
			+ 해당 워드에서 참조할 비트의 오프셋이 담겨 있다.
		*/

		TestBool(autoValue);	//런타임 에러 발생
		/*
			CreateBoolVector로 생성된 벡터는 해당 코드 라인의 명령이 끝나면 소멸된다. 
			
			즉 vector<bool>::reference가 가리키는 포인터는 dangling 포인터가 되며, bool 변환 과정에서 미정의 행동을 유발한다.
		*/

	}

	namespace UsingStaticCast {
		/*
			static_cast 과 같은 형식 명시 초기치 관용구는 auto가 원하는 형식을 연역하도록 강제한다.

			또한 형변환의 의도를 명확하게 드러낼 수 있다.
		*/

		inline void RunSample() {

			bool value = CreateBoolVector()[5];
			auto autoValue = static_cast<bool>(CreateBoolVector()[5]);	//autoValue는 문제없이 bool 타입으로 선언된다.

			TestBool(autoValue);	//문제없음
		}
	}
}
