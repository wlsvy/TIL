#pragma once
#include <iostream>
#include <vector>
#include <string>
#include <deque>
using namespace std;

//decltype�� �۵� ����� �����϶�.

namespace Item03 {

	/*
		decltype �� �־��� �̸��̳� ǥ������ ������ �˷��ش�.
		���ø� �߷а� auto�ʹ� �޸� decltype�� �־��� �̸��̳� ǥ������ ��ü���� ������ �״�� �����ش�.
		(������ �� const Ư¡����)
	*/

	struct Widget{};

	const int i = 0;									//decltype(i) : const int

	bool f(const Widget & w) { return true; }			//decltype(w) : const Widget &
														//decltype(f) : bool(const Widget &)

	struct Point {
		int x, y;
	};
	//decltype(Point::x) : int
	//decltype(Point::y) : int

	Widget w;		//decltype(w) : widget
					//decltype(f(w)) : bool

	vector<int> v;	//decltype(v) : vector<int>
					//decltype(v[0]) : int &

	namespace UsingDecltype0 {
		template<typename Container, typename Index>
		auto Access(Container& c, Index i) {					//�ܼ� auto ���� ���ø� Ÿ�� �߷� �������� ������(&)�� ���õȴ�.
			return c[i];
		}

		inline void RunSample() {
			std::deque<int> d = { 0, 0, 0, 0, 0, 0 };

			//Access(d, 5) = 10;	����, ��ȯ Ÿ���� int �̸� �������̴�.
		}
	}

	namespace UsingDecltype1 {
		template<typename Container, typename Index>
		auto Access(Container& c, Index i) 
			-> decltype(c[i])									//decltype(c[i])�� c, i�� ������ �ʿ��ϱ� ������ �Ű����� ��� ������ ��ġ��
		{
			return c[i];
		}

		inline void RunSample() {
			std::deque<int> d = { 0, 0, 0, 0, 0, 0 };

			Access(d, 5) = 10;	//��ȯ Ÿ���� int & �̸� ������ ����
		}
	}

	namespace UsingDecltype2 {
		template<typename Container, typename Index>
		decltype(auto) Access(Container& c, Index i)			//decltype(auto) ���� auto �� ��ȯ Ÿ���� �����Ǿ�� ���� ���ϰ�, decltype�� ���� �������� decltype �� ��Ģ�� ����Ǿ�� ���� ���Ѵ�.
		{
			return c[i];
		}

		inline void RunSample() {
			std::deque<int> d = { 0, 0, 0, 0, 0, 0 };

			Access(d, 5) = 10;	//��ȯ Ÿ���� int & �̸� ������ ����
		}
	}

	namespace UsingDecltype3 {
		template<typename Container, typename Index>
		decltype(auto) Access(Container&& c, Index i)			//���� ���� Ȱ��, �������� ������ �� ���� ��� ó���� �� �ֵ��� ����
		{
			return std::forward<Container>(c)[i];
		}

		inline void RunSample() {
			std::deque<int> d = { 0, 0, 0, 0, 0, 0 };

			Access(d, 5) = 10;	//��ȯ Ÿ���� int & �̸� ������ ����

			auto createDeque = []() {return std::deque<int>({ 0, 0, 0, 0, 0, 0 }); };

			Access(createDeque(), 5) = 10;	//������ �Ű����� ����

			decltype(auto) rValue = forward<deque<int>>(d);	//std::deque<int> &&
		}
	}
	

	/*
	
		�� ��, decltype�� ���� ���� ����� �����ϴ� ���

		������ ��ȣ�� ���θ�, �� ������ �ƴ� �������� ������ �����Ѵ�.

	*/


	decltype(auto) f1() {
		int x = 0;
		return x;		//��ȯ Ÿ�� : int
	}

	decltype(auto) f2() {
		int x = 0;
		return (x);		//��ȯ Ÿ�� : int &
	}

}

