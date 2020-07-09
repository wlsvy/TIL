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

//vector<bool> 보기를 돌같이 하자

namespace Item18 {
	using namespace std;

	/*
		언뜻 멀쩡해 보이는 vector<bool>은 사실 STL 컨테이너로서 두 가지가 잘못되어 있습니다. 
		첫째는 STL 컨테이너가 아니라는 점이고, 
		둘째는 bool을 담고 있지도 않다는 점입니다.

		어떤 객체가 STL 컨테이너의 자격을 갖추려면 C++ 표준안 23.1절에 수록된 요구사항을 만족해야만 합니다. 
		이 요구사항 중 하나가 "c가 타입 T의 객체를 담는 컨테이너라면 c에서 operator[]가 지원되어야 한다"라는 것입니다.

		즉 다음의 코드가 컴파일 되어야 한다는 말이죠.

		T *p = &c[0];
	*/

	inline void RunSample() {

		vector<bool> v;
		//bool *pb = &v[0]; 컴파일 되지 않습니다.

		/*
			하지만 절대로 안 됩니다. 
			vector<bool>은 실제로 bool이 들어 있지 않은 가짜 컨테이너입니다. 
			
			공간을 줄이기 위해 bool을 압축시킨 데이터 표현 방식을 쓰기 때문에 컴파일에 실패합니다.

			대개 "vector"에 저장되는 "bool"을 하나의 비트로 나타내어 한 바이트로 여덟 개의 bool을 담을 수 있게 구현하더군요. 
			즉, vector<bool>은 비트 필드(bitfield)를 써서 bool을 저장하고 있는 것처럼 흉내내는 것일 뿐입니다.

			물론 비트 필드도 bool처럼 두 개의 값만 가질 수 있지요. 
			그러나, 진짜 bool에는 이것에 대한 포인터를 만들 수 있지만, 비트 필드의 각 비트에 대한 포인터를 만들 수는 없지 않습니까?
			
			또한 비트 필드의 각 비트에 대한 참조자도 만들 수 없습니다.
		*/

		/*
			그럼 정말로 vector<bool>같은 객체가 필요할 때 어떻게 해야 할까요? 
			거의 모든 상황에서 통하는 방법은 두 가지 입니다. 
			
			첫째는 deque<bool>인데요. 
			deque는 vector가 할 수 있는 거의 모든 것을 할 수 있고(못 하는 것을 꼽자면 reserve와 capacity가 먼저 떠오르는군요) 진짜 bool을 저장할 수 있는 STL 컨테이너입니다.
		
			물론 deque가 사용하는 내부 메모리는 연속 메모리가 아닙니다.
			그 때문에 bool 배열을 받아들이는 C API(아마도 C99 API일 것입니다. bool이 추가된 것은 C99부터니까요) 등에 넘기고자 할 때에는 손가락만 빨 수밖에 없습니다.
		
			둘째는 bitset(비트셋)입니다. 
			bitset은 STL 컨테이너는 아니지만, 표준 C++ 라이브러리에 속해 있습니다.
			STL 컨테이너와 달리, 비트셋의 크기(요소의 개수)는 컴파일 타임에 고정되기 때문에 요소를 새로 삽입한다든지 제거하는 작업은 할 수 없습니다.
			더욱이 STL 컨테이너가 아니기 때문에 반복자도 지원하지 않습니다.
		*/
	}
}