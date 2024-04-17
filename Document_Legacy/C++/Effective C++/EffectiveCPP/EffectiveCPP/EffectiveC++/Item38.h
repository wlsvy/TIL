#pragma once
#include <iostream>
#include <vector>
#include <string>
#include <functional>

//"has-a(...는 ...를 가짐)" 혹은 "is-implemented-in-terms-of(...는 ...를 써서 구현됨)"를 모형화할 때는 객체 합성을 사용하자

namespace Item38 {
	using namespace std;

	/*
		객체 합성(composition)의 의미는 public 상속이 가진 의미와 완전히 다릅니다.

		public 상속 : is-a(...는 ...의 일종)
		객체 합성 : has-a(...는 ...를 가짐) 혹은 is-implemented-in-terms-of(...는 ...를 써서 구현됨)
	
	*/

	/*
			- 소프트웨어 개발에서 영역(domain)은 두 가지로 나뉜다. 
			응용 영역(application domain) : 사람, 이동수단 등 실제 사물을 본 따서 만든 객체들이 속한 영역
			구현 영역(implementation domain) : 버퍼, 뮤텍스, 탐색 트리 등 순수하게 시스템 구현만을 위한 인공물들이 속한 영역. 
			
			여기서 객체 합성이 응용 영역의 객체들 사이에서 일어나면 has-a 관계이다. 
			반면 구현 영역에서 일어나면 그 객체 합성의 의미는 (is-implemented-in-terms-of) 관계를 나타낸다.

			써서 구현되는 관계(is implemented in terms of) 형태의 설계
			-> 특정 파생클래스와 기반클래스가 is-a 관계가 아니지만, 파생클래스는 기반 클래스의 기능을 활용해서 구현된 것
	*/
}