#pragma once
#include <iostream>
#include <vector>
#include <list>
#include <algorithm>
#include <map>
#include <string>
#include <array>

//복사(Copy)는 컨테이너 안의 객체에 맞게 비용은 최소화하며, 동작은 정확하게 하자

namespace Item03 {
	using namespace std;

	//move semantic 이 소개되기 이전의 내용임을 감안하자.
	/*
		어찌 보면 STL은 미친듯이 복사만 하는 라이브러리라고 느끼게 할 수 있을 것 같습니다. 
		분명히 STL은 복사를 많이 하긴 하지만, STL은 일반적으로 "불필요한" 복사를 피하도록 설계되었습니다. 
		이것은 사실입니다. 실제로 STL은 일반적으로 불필요한 복사 "생성"을 피하도록 설계되었습니다.
	*/

	class Widget{};

	inline void RunSample() {
		const unsigned int maxNumWidgets = 100;

		Widget w[maxNumWidgets];
		
		vector<Widget> vw;
		vw.reserve(maxNumWidgets);

		/*
			배열의 경우 즉시 원소의 값들을 생성하지만

			벡터의 경우 reserve를 통해 공간만 미리 할당받을 수 있으며, 사용자의 지시가 없으면 객체를 바로 생성하지 않습니다.
		*/
	}
}