#pragma once
#include <iostream>
#include <vector>
#include <list>
#include <algorithm>
#include <map>
#include <string>
#include <array>
#include <set>
#include <memory>
#include <functional>
#include <numeric>

//대소문자를 구분하지 않는 문자열 비교는 mismatch 아니면 lexicographical_compare를 써서 간단히 구현할 수 있다

namespace Item35 {
	using namespace std;

	/*
		대소문자를 구분하지 않는 문자열 비교의 구현은 쉬울 수도 있고 그렇지 않을 수도 있습니다. "구분하지 않는 정도를 얼만큼이나 원하냐"에 따라 달라지죠.
		국제화(internationalization)에 대한 사항은 그냥 무시해 버리고 단지 strcmp류의 동작 정도만 원한다면 이 작업은 무척 쉽습니다.

		그런데 strcmp가 넘보기에는 힘든 언어별 문자열의 처리까지 가능하게 하거나 기본 로케일 이외의 로케일을 사용하는 경우라면 일은 상상외로 어렵습니다.
		(이를테면 한국어나 영어 이외의 다른 언어로 쓰여진 텍스트를 가진 문자열)
	*/

	auto ciCharEquality = [](const char c1, const char c2) {
		return tolower(static_cast<unsigned char>(c1)) == tolower(static_cast<unsigned char>(c2));
	};
	auto ciCharLess = [](const char c1, const char c2) {
		return tolower(static_cast<unsigned char>(c1)) < tolower(static_cast<unsigned char>(c2));
	};
	auto ciCharCompare = [](const char c1, const char c2) {
		//tolower의 매개 변수와 반환값은 int 타입이지만, int가 EOF가 아니어야 하면서	unsigned char를 나타낼 수 있는 형식이어야 합니다.
		auto lc1 = tolower(static_cast<unsigned char>(c1));
		auto lc2 = tolower(static_cast<unsigned char>(c2));


		//c1 < c2이면 - 1을, c1 == c2이면 0을 c1 > c2이면 1을 반환합니다.
		if (lc1 < lc2) return -1;
		if (lc1 > lc2) return 1;
		return 0;
	};

	namespace UseMismatch {

		/*
			우선은 두 개의 문자가 "대소문자의 여부만 제외하고" 같은지를 알아내는 방법이 필요합니다.
			두 개의 문자를 모두 소문자(혹은 대문자)로 만든 뒤에 비교를 하면 간단히 해결됩니다
		*/

		int ciStringCompareImpl(const string& s1, const string& s2);
			

		int ciStringCompare(const string& s1, const string& s2)
		{
			if (s1.size() <= s2.size()) return ciStringCompareImpl(s1, s2);
			else return -ciStringCompareImpl(s2, s1);
		}

		int ciStringCompareImpl(const string& s1, const string& s2)
		{
			auto p = mismatch(s1.begin(), s1.end(), s2.begin(), s2.end(), ciCharEquality);

			// true이면, s1과 s2이 같든지, s1이 s2보다 길이가 짧든지 둘 중 하나입니다.
			if (p.first == s1.end()) {
				if (p.second == s2.end()) return 0;
				else return -1;
			}

			return ciCharCompare(*p.first, *p.second);
		}
	}

	namespace UseLexicographical {
		/*
			쉽게 할 수 있는 "대소문자 비구분 문자열 비교법" 두 번째 방법은 STL의 규정에 맞춘 술어 구문을 만들어,
			이것을 연관 컨테이너의 비교 함수처럼 사용하는 것입니다.구현 코드는 상당히 간단하고 이해하기 쉽습니다.

			이전의 ciCharCompare 인터페이스를 술어 구문에 맞게 고치고, 문자열 비교 부분을 lexicographical_compare로 대체하기만 하면 됩니다.

			다른 방법과는 다르게 반환 타입이 bool임을 명심합시다.
		*/

		bool ciStringCompare(const string& s1, const string& s2)
		{
			return lexicographical_compare(s1.begin(), s1.end(), s2.begin(), s2.end(), ciCharLess);
		}
	}

	namespace UseStricmp {
		/*
			사실 이번 항목에서 구현해 본 대소문자 비구분 문자열 비교 함수와 비슷한 것들이 이미 표준 C 라이브러리 등의 비표준 확장 함수로 만들어져 있고, 폭넓게 사용되고 있습니다. 
			이름은 stricmp 혹은 strcmpi 등이며, 이번 항목에서 함께 구현해 본 함수들보다도 국제화 지원이 빈약합니다.
			
			여러분이 이식성에 별 신경을 쓰지 않고, 
			여러분이 사용하는 문자열에는 NULL 문자가 겹쳐서 들어가지 않으며, 
			국제화와 친구할 생각이 별로 없다면 STL을 전혀 사용하지 않고 대소문자 비구분 문자열 비교를 구현할 수 있습니다.

			string 객체를 const char* 포인터로 변환한 다음 strcmpi나 stricmp에 넘기면 되니까요.

			많은 것을 희생했지만, stricmp/strcmpi는 오직 문자열 비교만을 하도록 최적화된 함수이기 때문에 ,
			mismatch나 lexicographical_compare 등의 범용 알고리즘보다 긴 문자열 처리에서 월등히 빠릅니다.
		*/

		auto ciStringCompare(const string& s1, const string& s2)
		{
			return _stricmp(s1.c_str(), s2.c_str());
		}
	}

	inline void RunSample() {
		auto str0 = "Hello World", str1 = "GoodBye World", sameStr = "Same String";
		
		auto res = UseMismatch::ciStringCompare(str0, str1);
		res = UseMismatch::ciStringCompare(str1, str0);
		res = UseMismatch::ciStringCompare(sameStr, sameStr);

		res = UseLexicographical::ciStringCompare(str0, str1);
		res = UseLexicographical::ciStringCompare(str1, str0);
		res = UseLexicographical::ciStringCompare(sameStr, sameStr);

		res = UseStricmp::ciStringCompare(str0, str1);
		res = UseStricmp::ciStringCompare(str1, str0);
		res = UseStricmp::ciStringCompare(sameStr, sameStr);
	}
}