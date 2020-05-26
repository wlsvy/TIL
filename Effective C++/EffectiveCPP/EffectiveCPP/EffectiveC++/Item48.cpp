#include <iostream>
#include <vector>
#include <string>
using namespace std;

//템플릿 메타 프로그래밍 하지 않겠는가

namespace Item48 {

	/*
		Tmp(템플릿 메타 프로그래밍, template meta programming)에는 강점이 두 가지 있다. 
		
		1. Tmp를 쓰면 다른 방법으로는 까다롭거나 불가능한 일을 굉장히 쉽게 할 수 있다.
		
		2. 템플릿 메타 프로그램은 c++ 컴파일이 진행되는 동안에 실행되기 때문에, 
		기존 작업을 런타임 영역에서 컴파일 타임 영역으로 전환할 수 있다.

		이 말인 즉슨, 일반적으로 프로그램 실행 도중에 잡혀 왔던 몇몇 에러들을 컴파일 도중에 찾을 수 있다는 것이며, 
		런타임 시간에 수행할 작업을 컴파일 시간에 미리 수행하기 때문에 실행 코드가 작아지고(??), 실행 시간도 짧아지며 메모리도 절약할 수 있다고 한다.

	*/

	//TMP에서는 루프를 빼놓을 수가 없는데, 사실 TMP에서는 반복(iteration) 의미의 진정한 루프는 없기 때문에, 재귀(recursion)을 사용해서 루프의 효과를 낸다. 
	//TMP는 재귀 함수 호출을 만들지 않고 재귀식 템플릿 인스턴스화(recursive template instantiation)를 한다.
	template<unsigned n>
	struct Factorial {
		enum { value = n * Factorial<n - 1>::value };
	};

	template<>	//템플릿 특수화로 재귀 종료 조건 구현
	struct Factorial<0> {
		enum { value = 1 };
	};

	void func() {
		std::cout << Factorial<0>::value << std::endl;
		std::cout << Factorial<1>::value << std::endl;
		std::cout << Factorial<2>::value << std::endl;
		std::cout << Factorial<3>::value << std::endl;
		std::cout << Factorial<4>::value << std::endl;
	}

	/*
		TMP가 강력한 역할을 하는 분야가 있다.

		치수 단위(dimensional unit)의 정확성 확인 - 질량, 거리, 시간 등에 대해서 사용. TMP를 사용한다면 모든 치수 단위의 조합을 컴파일 타임에 확인가능하다.

		행렬 연산의 최적화 - 표현식 템플릿(expression template)을 사용하면 엄청난 효율을 가질 수 있다고 한다.

		맞춤식 디자인 패턴 구현의 생성 - 전략 패턴, 감시자 패턴, 방문자 패턴 등의 디자인 패턴에서 사용. 
		TMP의 정책 기반 설계(policy-based design)라는 것을 사용하면 따로따로 마련된 설계상의 선택을 나타내는 템플릿을 만들어낼 수 있게 된다. 생성식 프로그래밍(generative programming)의 기초라고 하더라.


	*/
}
