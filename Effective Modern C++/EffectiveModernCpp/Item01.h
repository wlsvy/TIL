#pragma once
#include <iostream>
#include <vector>
#include <string>
using namespace std;

//템플릿 형식 연역 규칙을 숙지하라

namespace Item01 {

	/*
		template<typename T>
		void f(ParamType param);	//함수 선언

		f(expr);					//함수 호출

		컴파일 도중 컴파일러는 expr을 이용해서 두 가지 형식을 추측한다.
		먼저 T에 대한 형식을 추측하고 두번째로 ParamType 에 대해서 추측한다.
	*/

	namespace ParamType_Pointer_0 {
		//ParmaType이 템플릿 타입의 포인터 혹은 참조 형식이지만 보편 참조(Universal Reference)는 아님

		template<typename T>
		void f(T& param) {}

		inline void RunSample() {
			int x = 27;
			const int cx = x;
			const int & rcx = x;

			f(x);	// T : int,			param 타입은 int &
			f(cx);	// T : const int,	param 타입은 cosnt int &
			f(rcx);	// T : const int,	param 타입은 const int &

			/*
				두 번째 호출에서 T는 const int 로 추측, 즉 추론 과정에서는 const 특징을 보존
				세 번째 호출에서 T는 const int 로 추측,(참조 형식이 아닌 비참조 형식) 즉 추론 과정에서 참조성은 무시.
			*/

		}
	}

	namespace ParamType_Pointer_1 {
		//ParmaType이 템플릿 타입의 포인터 혹은 참조 형식이지만 보편 참조(Universal Reference)는 아님

		template<typename T>
		void f(const T& param) {}

		inline void RunSample() {
			int x = 27;
			const int cx = x;
			const int & rcx = x;

			f(x);	// T : int,	param 타입은 const int &
			f(cx);	// T : int,	param 타입은 cosnt int &
			f(rcx);	// T : int,	param 타입은 const int &
		}
	}

	namespace ParamType_UniversalReference {
		//ParmaType이 템플릿 타입의 보편 참조(Universal Reference)

		template<typename T>
		void f(T&& param) {}

		inline void RunSample() {
			int x = 27;
			const int cx = x;
			const int & rcx = x;

			f(x);	//매개변수는 좌측값, T : int&,			param 타입은 int &
			f(cx);	//매개변수는 좌측값, T : const int&,	param 타입은 cosnt int &
			f(rcx);	//매개변수는 좌측값, T : const int&,	param 타입은 const int &
			f(27);	//매개변수는 우측값, T : int,			param 타입은 int&&
		}
	}

	namespace ParamType_Value {
		//ParmaType이 템플릿 타입의 참조 혹은 포인터가 아님, 즉 인수가 값으로 전달되는 상황(pass by value)

		template<typename T>
		void f(T param) {}

		inline void RunSample() {
			int x = 27;
			const int cx = x;
			const int & rcx = x;

			f(x);	//매개변수는 좌측값, T : int,	param 타입은 int
			f(cx);	//매개변수는 좌측값, T : int,	param 타입은 int
			f(rcx);	//매개변수는 좌측값, T : int,	param 타입은 int

			/*
				const int 타입도 인수로 넘겨질 때 int 로 변환, 값 복사로 인해 독립된 객체가 생성되므로 const 형식이 아니다
			*/

			const char* const ptr = "Fun With Pointer";

			f(ptr);	//매개변수는 좌측값, T : const char*, param 타입은 : const char*
			/*
				별표 문양 왼쪽의 const 는 보존되지만, 별표 오른쪽의 const(포인터 주솟값 변경 불가능)는 그렇지 않음
			*/
		}
	}

	namespace ParamType_Array0 {
		//ParmaType이 템플릿 타입 배열

		/*
		void myfunc(int param[]) {}
		void myfunc(int* param) {}	// 둘은 동일한 함수
		*/


		template<typename T>
		void f(T param) {}

		inline void RunSample() {

			const char str[] = "Fun With Pointer";
			const char* ptr = str;	//배열이 포인터로 붕괴, ptr은 str의 첫번째 원소값을 가리킴

			f(str);	// str은 배열이지만, T는 const char*로 추측
			f(ptr);
		}
	}

	namespace ParamType_Array1 {
		//배열을 참조로 전달할때

		template<typename T>
		void f(T& param) {}

		inline void RunSample() {

			const char str[] = "Fun With Pointer";

			f(str);	//T는 const char [17], paramType 은 const char (&)[17] 로 추측
		}

		//응용 방식, 템플릿 매개변수 추측으로 배열 크기 알아내기
		template<typename T, std::size_t N>
		constexpr std::size_t arraySize(T(&)[N]) noexcept {
			return N;
		}
	}

	namespace ParamType_Function {
		//ParamType 이 함수 형식일때

		inline void someFunc(int i, double d) {
			cout << i << " " << d << endl;
		}

		template<typename T>
		void f1(T param) { }

		template<typename T>
		void f2(T& param) { }

		inline void RunSample() {

			f1(someFunc);	//값 전달, paramType 은 void(*)(int, double)
			f2(someFunc);	//참조 전달, paramType 은 void(&)(int, double)
		}
	}
}

