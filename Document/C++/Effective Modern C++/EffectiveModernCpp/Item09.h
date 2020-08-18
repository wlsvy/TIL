#pragma once
#include <iostream>
#include <vector>
#include <list>
#include <string>
using namespace std;

//typedef ���� ��Ī ������ ��ȣ�϶�

namespace Item09 {

	//�Լ� �������� ��Ī�� ������ ���� using ���� ���� ���Ѵ�.
	using FP = void(*)(int, const std::string&); // using
	typedef void(*FP)(int, const std::string&);	//typedef

	//��Ī ���ø�(alias templates) ���� using ���� �����ϱ� ����.
	template<typename T>
	using MyList = std::list<T>;

	MyList<int> li;

	template<typename T>
	struct MyVector {
		typedef std::vector<T> type;
	};

	MyVector<int>::type vi;

	
	template<typename T>
	class Widget {
	private:
		/*
			typedef�� ����� �� ���� �� �Ѱ���
			���ø� �ȿ��� typedef�� ����� �� �̸� �տ� typename�� �ٿ��� �Ѵ�.

			MyVector<T>::type�� ���� ������ ����(dependent type)�̸�, c++�� ��Ģ�� ���� ������ ���� �տ��� typename�� �پ�� �Ѵ�.

			MyVector ����ü�� Ư��ȭ(specialization)�� ���� MyVector<T>::type �� ������ �ƴ� �ٸ� ���� ��Ī�� ���ɼ��� �ֱ� �����̴�.
		*/
		typename MyVector<T>::type wVec;

		/*
			using �� �׷� �ʿ� ����, 
			
			�����Ϸ��� MyList�� ���� ���ø����� �ǹ� �˰� �����Ƿ�, MyList<T>�� �ݵ�� ���� �̸��̴�.
			MyList<T> �� �������� �����̴�.
		*/
		MyList<T> wList;
	};

	/*
		�Ʒ� ���, Ư��ȭ�� ���� MyVector<T>::type�� Ÿ�Ը��� ��Ī���� �ʴ´�.
	*/
	class Wine{};
	template<>
	class MyVector<Wine> {
	private:
		enum class WineType {White, Red};
		WineType type;
	};

	inline void RunSample() {
		/*
			c++���� ���� Ư��(type traits)�� Ȱ���� ��, ���� ������ ã�ƺ��� typedef�� ����ϴ� ���� ���簡 �����ִ�.

			(template struct�� ������ �� �� �ȿ� type�� ������ ��)

			c++14���� std::��ȯ_t ������ ��Ī ���ø��� �߰��Ǿ���.
		*/
		
		std::remove_const<const int>::type i0;	//int
		std::remove_const_t<const int> i1;		//int

		std::remove_reference<int&&>::type i2;	//int
		std::remove_reference_t<int&> i3;		//int
	}
}