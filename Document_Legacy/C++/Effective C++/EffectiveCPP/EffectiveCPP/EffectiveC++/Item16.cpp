#include <iostream>
#include <vector>
#include <string>
using namespace std;

//new 및 delete를 사용할 때는 형태를 반드시 맞추자
namespace Item16 {

	void Func() {
		std::string *stringArr = new std::string[100];

		delete stringArr; // 배열 중에서 맨 처음 string 만 반환되고 나머지 99개는 그대로 방치될 가능성이 크다!!
	}

	void Func2() {
		std::string *stringPtr1 = new std::string;
		std::string *stringPtr2 = new std::string[100];

		delete stringPtr1;	//객체 한 개 삭제	
		delete[] stringPtr2;//객체의 배열 삭제

		/*
			[] 연산자를 사용했을 때, delete는 보통 배열의 크기를 먼저 읽고
			(컴파일러 마다 다르지만 보통 배열의 맨 앞부분에 위치한다고 한다)

			배열 크기에 해당하는 횟수만큼 소멸자를 호출한다.
			즉, [] 연산자로 짝을 맞추지 않는다면 미정의 동작이 발생한다.
		*/
	}

	void Func3() {
		//주의할 것
		using AddressLines = std::string[4];

		/*
			비록 배열 선언은 아니지만

			pal이 가리키는 객체는 배열객체이다.
		*/
		std::string *pal = new AddressLines;
		delete[] pal;
	}
}