#pragma once
#include <iostream>
#include <vector>
#include <string>
#include <tuple>
using namespace std;

//범위 없는 enum 보다 범위 있는 enum을 선호하라

namespace Item10 {

	namespace Unscoped {
		//범위 없는 enum은 enum을 포함하는 범위에 속한다. -> namespace 오염 우려가 있다.
		enum Color {black, white, red};

		//auto white = false; 오류, 이미 white가 선언되어 있다.
	}

	namespace Scoped {
		//이제 Color 범위에 속하게 된다.
		enum class Color { black, white, red };

		auto white = false; //문제 없음
	}

	enum SystemStatus;

	void DoSomething(size_t) { cout << "DoSomething(size_t)" << endl; }
	void DoSomething(SystemStatus) { cout << "DoSomething(SystemStatus)" << endl; }

	/*
		범위 없는 enum의 단점으로 책에서는 전방선언이 안된다고 언급됐지만, 직접 해보니 전방선언이 가능하다!
		즉 전방선언을 통해 컴파일 의존성을 줄일 수 있다.
	*/
	enum SystemStatus
	{
		good = 0,
		failed = 1,
		incomplete = 100,
		corrupt = 200,
		indeterminate = 0xfffffff
	};

	inline void RunSample() {
		/*
			범위없는 enum의 단점. 암묵적으로 정수 형식으로 변환되므로 오류를 발생시킬 수 있다.
		*/
		auto uc = Unscoped::red;
		if (uc < 14.5) {	//암시적으로 double 과 비교, size_t로 형변환
			DoSomething(uc);	//"DoSomething(size_t)"
		}


		auto sc = Scoped::Color::red;
		/*if (sc < 14.5) {	//오류 :범위 있는 enum은 암시적으로 다른 형식으로 변환되지 않는다.
			DoSomething(sc);
		}*/

		DoSomething(good);	//"DoSomething(SystemStatus)"
	}

	

	namespace Unscoped {
		/*
		메모리를 효율적으로 사용하기 위해 컴파일러들은 주어진 enum의 열거자 값들의 범위를 표현할 수 있는 가장 작은 바탕 형식을 선택한다.
		Ex) Color 값은 경우 char 로 표현, SystemStatus 같은 경우 int

		범위 있는 enum의 기본 바탕 형식은 int 이며 프로그래머가 명시적으로 다른 형식을 지정 가능하다.
		*/
		enum UserInfoFields : std::uint8_t;	//전방선언과 동시에 바탕 형식 지정

		enum UserInfoFields : std::uint8_t	//정의와 동시에 바탕 형식 지정
		{
			uiName,
			uiEmail,
			uiReputation
		};

		using UserInfo = std::tuple<string, string, size_t>;

		void RunUserInfoSample() {
			UserInfo uInfo;
			auto name = std::get<uiName>(uInfo);	//암시적으로 정수로 변환되는 특징 활용.(컴파일 시간에 변환되므로 get<size_t> 에 값을 넣을 수 있다.)
			auto mail = std::get<uiEmail>(uInfo);
			auto reputation = std::get<uiReputation>(uInfo);
		}
	}

	namespace Scoped {
		/*
			벙위 없는 enum 보다 범위 있는 enum 이 더 불편한 경우,
		*/
		enum class UserInfoFields : std::uint8_t
		{
			uiName,
			uiEmail,
			uiReputation
		};

		template<typename E>
		constexpr auto toUTtype(E enumerator) noexcept {
			return static_cast<std::underlying_type_t<E>>(enumerator);	//enum 값을 바꾸는 함수가 필요하다. 튜플의 값을 얻는 get 함수에 사용하기 위해서 constexpr 선언
		}

		using UserInfo = std::tuple<string, string, size_t>;

		void RunUserInfoSample() {
			UserInfo uInfo;
			auto name = std::get<toUTtype(UserInfoFields::uiName)>(uInfo);	//번거로운 타이핑 작업 필요
			auto mail = std::get<toUTtype(UserInfoFields::uiEmail)>(uInfo);
			auto reputation = std::get<toUTtype(UserInfoFields::uiReputation)>(uInfo);
		}
	}
	

	
}