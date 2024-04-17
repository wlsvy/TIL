#pragma once
#include <iostream>
#include <vector>
#include <string>
#include <array>

//std::forward�� ���ؼ� ������ auto&& �Ű��������� decltype�� ����϶�

namespace Item33 {

	/*
		�� ǥ������

		auto f = [](auto x){ return normalize(x); };

		�Ʒ�ó�� ��ȯ�ȴ�.

		class �����Ϸ���_����_�_Ŭ����_�̸� {
		public:
			template <typename T>          
			auto operator()(T x) const { return normalize(x); }     //const�� ���� �ٴ´�.
		};
			
	*/

	

	inline void f() { std::cout << "Void" << std::endl; }
	//inline void f(int) { std::cout << "int" << std::endl; }
	inline void f(int&) { std::cout << "int&" << std::endl; }
	inline void f(int&&) { std::cout << "int&&" << std::endl; }

	template <typename T>                      
	void fwd(T&& param)  
	{
		f(std::forward<T>(param));
	}
	/*
		���� ���ٷ� �Ϻ������� �����ҷ���?

		auto f = [](auto&& x)
		{ return normalize(std::forward<???>(x)); };
	*/

	inline void RunSample() {

		auto fwdLambda = [](auto && param)
		{
			f(std::forward<decltype(param)>(param));
		};

		int i = 0;
		int& ri = i;
		fwdLambda(i);
		fwdLambda(ri);
		fwdLambda(3);
	}
}