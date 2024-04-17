#pragma once
#include <iostream>
#include <vector>
#include <string>
#include <array>
#include <functional>

//��ü�� Ŭ���� ������ �̵��Ϸ��� �ʱ�ȭ �������� ����϶�

namespace Item32 {
	/*
		��ü�� Ŭ���� ������ �̵��� ������ C++14�� �ʱ�ȭ �������� ����϶�.
		�ʱ�ȭ �������δ� ������ ���� �͵��� ������ �� �ִ�.

		1. ���ٷκ��� �����Ǵ� Ŭ���� Ŭ������ ���� ������ ����� �̸�
		2. �� ������ ����� �ʱ�ȭ�ϴ� ǥ����
	*/

	/*
		�̵������� ��ü�� ��� �� ĸ��, ���� ĸ�ĵ� �������� �ʴ�. c++11 ���� �������� �̸� �����ϴ� ����� ������
		c++14 ���ʹ� �ʱ�ȭ �������� ��ü�� �̵���ų �� �ִ�.
	*/

	class Widget {
	public:
		Widget() { std::cout << "default ctor" << std::endl; }
		Widget(const Widget& rhs) { std::cout << "copy ctor" << std::endl; }
		Widget(Widget&& rhs) { std::cout << "move ctor" << std::endl; }
		~Widget() { std::cout << "dtor" << std::endl; }
		
		int val = 0;
	};

	namespace Case0 {
		inline void RunSample() {
			auto pw = std::make_unique<Widget>();
			pw->val = 3;

			{
				auto func = [pw = std::move(pw)]()	//C++ 14
				{
					std::cout << pw->val << std::endl;
				};
				func();
			}
			std::cout << "==============" << std::endl;
		}
		/*
		[]���� �κ��� �ʱ�ȭ �������̴�.
		"="�� �º��� Ŭ���� Ŭ���� ���� ������ ��� (Ŭ�������� �����)�� �̸��̰�, �캯�� �װ��� �ʱ�ȭ�ϴ� ǥ�����̴�.

		"="�� �º��� �캯�� �������ٸ��ٴ� ���̴�.

		 �º��� ������ �ش� Ŭ���� Ŭ������ �����̰�,
		 �캯�� ������ ���ٰ� ���ǵǴ� ������ ������ �����ϴ�.
	*/
	}
	

	namespace Case1 {
		/*
			C++11������ ���� �ۼ��� Ŭ������ std::bind�� �ʱ�ȭ �������� �䳻 �� �� �ִ�.
			C++11������ ��ü�� Ŭ���� ������ �̵��� ����� ����. �̷� ��Ȳ������, ���� �ۼ��� Ŭ������ std::bind�� �ʱ�ȭ �������� �䳻���� ����� ��� �Ѵ�.

			���ε� ��ü�� �̿��� ����� ������ ������ ����.

			��ü�� C++11 Ŭ���� ������ �̵� �����ϴ� ���� �Ұ����ϳ�, ��ü�� C++11 ���ε� ��ü ������ �̵� �����ϴ� ���� �����ϴ�.
			C++11���� �̵� �������� �䳻 ���� �����, ��ü�� ���ε� ��ü ������ �̵� �����ϰ�, �̵� ������ ��ü�� ���ٿ� ������ �����ϴ� ���̴�.
			���ε� ��ü�� ������ Ŭ������ ����� �����Ƿ�, ���ε� ��ü ���� ��ü���� ��ġ Ŭ���� �ȿ� �ִ� ��ó�� ����ϴ� ���� �����ϴ�.
		*/

		inline void RunSample() {
			std::vector<double> vec = { 0.0, 1.0, 2.0, 3.0 };
			auto func = std::bind // C++11���� �ʱ�ȭ ĸ�� �䳻
				(                                    
					[](const std::vector<double>& data)        
					{ 
						for (int i = 0; i < data.size(); i++)
						{
							std::cout << data[i] << " ";
						} 
						std::cout << std::endl;
					},               
					std::move(vec)
				);
			func();


			/*
				�⺻������, ���ٷκ��� ������� Ŭ���� Ŭ������ operator() ��� �Լ��� const�̴�.
		
				�� ������ ���� ���� �ȿ��� Ŭ������ ��� ������ ����� const�� �ȴ�.
				=> �� �κ� ���� �����غ��� �� ������ �����ϴ�. const �� �ƴѰ� ����
			
				�׷��� ���ε� ��ü ���� �̵� ������ data ���纻�� const�� �ƴϴ�.

				���� ���ٸ� mutable�� �����ϸ�, 
				�ش� Ŭ���� Ŭ������ operator()�� const�� ������� ���� ���̹Ƿ� 
				������ �Ű����� ���𿡼� const��  �����ؾ� �����ϴ�.
			*/
			auto val = std::vector<double>{ 1, 1, 1, 1, 1 };
			auto func2 = std::bind
			(
				[](std::vector<double>& data) mutable
				{
					for (int i = 0; i < data.size(); i++)
					{
						data[i] = i;
					}
					for (int i = 0; i < data.size(); i++)
					{
						std::cout << data[i] << " ";
					}
					std::cout << std::endl;
				},
				val
			);
			func2();
			std::cout << "==============" << std::endl;
		}
	}
	
}