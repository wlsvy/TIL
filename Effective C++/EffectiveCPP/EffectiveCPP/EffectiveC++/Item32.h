#pragma once
#include <iostream>
#include <vector>
#include <string>

//public 상속 모형은 반드시 "is-a(...는 ...의 일종이다)"를 따르도록 만들자

namespace Item32 {
	using namespace std;

	/*
		public 상속의 의미는 "is-a(...는 ...의 일종)"입니다. 
		기본 클래스에 적용되는 모든 것들이 파생 클래스에 그대로 적용되어야 합니다. 
		왜냐하면 모든 파생 클래스 객체는 기본 클래스 객체의 일종이기 때문입니다.


		수학에서는 "정사각형은 직사각형의 일종이다." 라는 말은 참이 되지만 이를 그대로 public 상속으로 나타내면 안됩니다. 
		직사각형으로 할 수 있는 모든 일을 정사각형이 할 수 없기 때문입니다.(예를 들어 가로 길이만 변경한다던지...)


		※ public 상속은 기본 클래스 객체가 가진 모든 것들이 파생 클래스 객체에도 그대로 적용된다고 단정하는 상속입니다.
	*/
}