#pragma once
#include <iostream>
#include <vector>
#include <string>
using namespace std;

//���ø� ���� ���� ��Ģ�� �����϶�

namespace Item01 {

	/*
		template<typename T>
		void f(ParamType param);	//�Լ� ����

		f(expr);					//�Լ� ȣ��

		������ ���� �����Ϸ��� expr�� �̿��ؼ� �� ���� ������ �����Ѵ�.
		���� T�� ���� ������ �����ϰ� �ι�°�� ParamType �� ���ؼ� �����Ѵ�.
	*/

	namespace ParamType_Pointer_0 {
		//ParmaType�� ���ø� Ÿ���� ������ Ȥ�� ���� ���������� ���� ����(Universal Reference)�� �ƴ�

		template<typename T>
		void f(T& param) {}

		inline void RunSample() {
			int x = 27;
			const int cx = x;
			const int & rcx = x;

			f(x);	// T : int,			param Ÿ���� int &
			f(cx);	// T : const int,	param Ÿ���� cosnt int &
			f(rcx);	// T : const int,	param Ÿ���� const int &

			/*
				�� ��° ȣ�⿡�� T�� const int �� ����, �� �߷� ���������� const Ư¡�� ����
				�� ��° ȣ�⿡�� T�� const int �� ����,(���� ������ �ƴ� ������ ����) �� �߷� �������� �������� ����.
			*/

		}
	}

	namespace ParamType_Pointer_1 {
		//ParmaType�� ���ø� Ÿ���� ������ Ȥ�� ���� ���������� ���� ����(Universal Reference)�� �ƴ�

		template<typename T>
		void f(const T& param) {}

		inline void RunSample() {
			int x = 27;
			const int cx = x;
			const int & rcx = x;

			f(x);	// T : int,	param Ÿ���� const int &
			f(cx);	// T : int,	param Ÿ���� cosnt int &
			f(rcx);	// T : int,	param Ÿ���� const int &
		}
	}

	namespace ParamType_UniversalReference {
		//ParmaType�� ���ø� Ÿ���� ���� ����(Universal Reference)

		template<typename T>
		void f(T&& param) {}

		inline void RunSample() {
			int x = 27;
			const int cx = x;
			const int & rcx = x;

			f(x);	//�Ű������� ������, T : int&,			param Ÿ���� int &
			f(cx);	//�Ű������� ������, T : const int&,	param Ÿ���� cosnt int &
			f(rcx);	//�Ű������� ������, T : const int&,	param Ÿ���� const int &
			f(27);	//�Ű������� ������, T : int,			param Ÿ���� int&&
		}
	}

	namespace ParamType_Value {
		//ParmaType�� ���ø� Ÿ���� ���� Ȥ�� �����Ͱ� �ƴ�, �� �μ��� ������ ���޵Ǵ� ��Ȳ(pass by value)

		template<typename T>
		void f(T param) {}

		inline void RunSample() {
			int x = 27;
			const int cx = x;
			const int & rcx = x;

			f(x);	//�Ű������� ������, T : int,	param Ÿ���� int
			f(cx);	//�Ű������� ������, T : int,	param Ÿ���� int
			f(rcx);	//�Ű������� ������, T : int,	param Ÿ���� int

			/*
				const int Ÿ�Ե� �μ��� �Ѱ��� �� int �� ��ȯ, �� ����� ���� ������ ��ü�� �����ǹǷ� const ������ �ƴϴ�
			*/

			const char* const ptr = "Fun With Pointer";

			f(ptr);	//�Ű������� ������, T : const char*, param Ÿ���� : const char*
			/*
				��ǥ ���� ������ const �� ����������, ��ǥ �������� const(������ �ּڰ� ���� �Ұ���)�� �׷��� ����
			*/
		}
	}

	namespace ParamType_Array0 {
		//ParmaType�� ���ø� Ÿ�� �迭

		/*
		void myfunc(int param[]) {}
		void myfunc(int* param) {}	// ���� ������ �Լ�
		*/


		template<typename T>
		void f(T param) {}

		inline void RunSample() {

			const char str[] = "Fun With Pointer";
			const char* ptr = str;	//�迭�� �����ͷ� �ر�, ptr�� str�� ù��° ���Ұ��� ����Ŵ

			f(str);	// str�� �迭������, T�� const char*�� ����
			f(ptr);
		}
	}

	namespace ParamType_Array1 {
		//�迭�� ������ �����Ҷ�

		template<typename T>
		void f(T& param) {}

		inline void RunSample() {

			const char str[] = "Fun With Pointer";

			f(str);	//T�� const char [17], paramType �� const char (&)[17] �� ����
		}

		//���� ���, ���ø� �Ű����� �������� �迭 ũ�� �˾Ƴ���
		template<typename T, std::size_t N>
		constexpr std::size_t arraySize(T(&)[N]) noexcept {
			return N;
		}
	}

	namespace ParamType_Function {
		//ParamType �� �Լ� �����϶�

		inline void someFunc(int i, double d) {
			cout << i << " " << d << endl;
		}

		template<typename T>
		void f1(T param) { }

		template<typename T>
		void f2(T& param) { }

		inline void RunSample() {

			f1(someFunc);	//�� ����, paramType �� void(*)(int, double)
			f2(someFunc);	//���� ����, paramType �� void(&)(int, double)
		}
	}
}

