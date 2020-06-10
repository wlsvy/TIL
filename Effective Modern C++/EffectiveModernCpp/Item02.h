#pragma once
#include <iostream>
#include <vector>
#include <string>


//auto 형식 연역 규칙을 숙지하라

namespace Item02 {
	using namespace std;

	template<typename T>
	void f(T param) {
		cout << param.size() << endl;
	}
	template<typename T>
	void f2(initializer_list<T> param) {
		cout << param.size() << endl;
	}

	inline void someFunc(int, double) {}

	inline void RunSample() {
		auto x = 27;			//int
		const auto cx = x;		//const int
		const auto & rcx = x;	//const int&
		auto x2 = cx;			//int

		//universal reference
		auto&& uref1 = x;		//int&
		auto&& uref2 = cx;		//const int&
		auto&& uref3 = 27;		//int&&

		//array
		const char name[] = "R. N. Briggs";

		auto arr1 = name;		//const char*
		auto& arr2 = name;		//const char(&)[13]

		//function
		auto func1 = someFunc;	//void (*)(int, double)
		auto& func2 = someFunc;	//void (&)(int, double)

		//initializer
		auto x1 = 27;			//int
		auto x2(27);			//int

		//Uniform initialization 균일 초기화
		auto x3 = { 27 };		//std::initializer_list<int>
		auto x4{ 27 };			//std::initializer_list<int>

		//auto x5 = { 1, 2, 3.0 }; 오류, 연역 불가

		//Passing Initializer List
		auto v = { 1, 2, 3 };
		f(v);	//오류 없음
		//f({ 1, 2, 3 }); 오류, T에 대한 형식을 연역할 수 없음

		f2(v);
		f2({ 1, 2, 3 });

		/*
			auto 형식과 template 형식 연역의 실질적인 차이는 
			
			auto는 중괄호 초기치가 std::initializer_list를 나타낸다고 가정하지만
			템플릿 형식은 그렇지 않다는 것
		*/

		//lambda
		vector<int> v2;
		auto resetV =
			[&v2](const auto& newValue) { v2 = newValue; };
		resetV(vector<int>({ 1, 2, 3 }));
		//resetV({ 1, 2, 3 }); 오류
	}

	

	

	/*
	그 외

	auto createInitList() {
		return { 1, 2, 3 };
	}

	오류, 반환값 auto 타입을 추측할 수 없음
		
	*/
}

