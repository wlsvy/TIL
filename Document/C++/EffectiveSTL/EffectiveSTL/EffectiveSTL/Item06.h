#pragma once
#include <iostream>
#include <vector>
#include <list>
#include <algorithm>
#include <map>
#include <string>
#include <array>

//C++ 컴파일러의 어이없는 분석 결과를 조심하자

namespace Item06 {
	using namespace std;


	
	inline void RunSample() {
		/*
			C++ 컴파일러는 가끔 문장을 의도하지 않은 방식으로 해석할 때가 있습니다.
			int 데이터가 들어 있는 파일을 가지고 있고, 이 파일에 들어 있는 int를 list에 복사한다고 가정해 보죠. 다음의 코드 정도가 나올 수 있을 것입니다.

			ifstream dataFile("ints.dat");
			list<int> data(istream_iterator<int>(dataFile), istream_iterator<int>());

			이 코드는 잘 컴파일되지만 런타임에 아무런 일도 하지 않습니다.

			파일에서 데이터를 읽지도 않을 뿐더러 list 객체를 만들지도 않습니다.
			이유는 컴파일러가 이 문장을 list 객체의 선언문이 아니라 data라는 이름의 함수 선언문으로 해석하기 때문입니다.

			list<int>의 반환 타입을 가진 함수 말입니다. 이 함수는 두 개의 매개 변수를 받습니다. 하나씩 설명해 보죠.

			첫째 매개 변수는 dataFile이란 이름을 가지고 있습니다. 타입은 istream_iterator<int>입니다. 
			dataFile를 둘러싸고 있는 괄호는 불필요한 것이므로 컴파일러가 무시해 버립니다.

			둘째 매개 변수는 이름을 가지고 있지 않습니다. 타입은 아무 것도 받아들이지 않고 istream_iterator<int>을 반환하는 함수 포인터입니다.
		*/
		
		//이렇게 수정하면 정상적으로 동작합니다.
		/*
			istream dataFile("ints.dat");
			istream_iterator<int> dataBegin(dataFile);
			istream_iterator<int> dataEnd;
				
			list<int> data(dataBegin, dataEnd);
		*/
		
	}
}