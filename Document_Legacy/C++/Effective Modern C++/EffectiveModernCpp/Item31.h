#pragma once
#include <iostream>
#include <vector>
#include <string>
#include <array>
#include <functional>

//�⺻ ������ ��带 ���϶�

namespace Item31 {

	/*
		���� ǥ����(lambda expression)�� �̸� �״�� �ϳ��� ǥ��������, �ҽ� �ڵ��� �Ϻ��̴�
		
		Ŭ����(closure)�� ���ٿ� ���� ������� ������� ��ü�̴�. 
		������ ���(capture mode)�� ����, Ŭ������ �������� �������� ���纻�� ���� ���� �ְ� �� �����Ϳ� ���� ������ ���� ���� �ִ�. 
		�� ���� �ڵ��� std::find_if ȣ�⿡�� Ŭ������ ����������� std::find_if�� ��° �μ��� ���޵Ǵ� ��ü�̴�.

		Ŭ���� Ŭ������ Ŭ������ ����� �� ���� Ŭ������ ���Ѵ�. 
		������ ���ٿ� ���� �����Ϸ��� ������ Ŭ���� Ŭ������ ����� ����. 
		���� ���� ������� �ش� Ŭ���� Ŭ������ ��� �Լ��� ���� ���� ������ ��ɵ��� �ȴ�.
	*/

	using FilterContainer = std::vector<std::function<bool(int)>>;
	FilterContainer filters;

	namespace Case0 {
		/*
			�⺻ ���� ĸ�Ĵ� ������ ����� ���� ������ �ִ�.

			�⺻ ���� �������� ����� ���ٿ� ���� ������ Ŭ������ ������,
			ĸ�ĵ� ���� ������ �Ű������� ������ ���� ���ӵǸ�, Ŭ���� ���� ������ ����� �Ҵ´�.
		*/

		template <typename C>
		void workWithContainer(const C& container)
		{
			auto divisor = 5; 
														
			if (std::all_of(std::begin(container), std::end(container),
				[&](const auto& value)
			{ return value % divisor == 0; })) 
			{
				//...
			}
			else 
			{
				//...
			}                                            
		}
		/*
			���� ���ƿ����� ��ȿ������ �ٸ� ���ƿ����� �����ϴٰ� �� �� ����.

			���� ĸ�Ĵ� ���� ���ٰ� ������ ���� �ȿ��� ���̴�, static�� �ƴ� ���� ����(�Ű����� ����)���� ����ȴ�.
		*/

		inline void RunSample()
		{
			auto divisor = 5;

			filters.emplace_back(
				[&](int value) { return value % divisor == 0; }		// ����! divisor�� ���� ������ ���� �� �ִ�.
			);
			/*
				addDivisorFilter �Լ��� ����� ��, �������� divisor�� ��ȯ�ȴ�.
			*/
			filters.emplace_back(
				[&divisor](int value) { return value % divisor == 0; }		// ����! divisor�� ���� ������ ���� �� �ִ�.
			);
			/*
				��������,
				������ ����� ĸ�Ĵ� �� ���� ǥ������ ��ȿ���� divisor�� ���� �����Ѵٴ� ���� ��Ȯ�� ��Ÿ���ٴ� ������ �ִ�.
			*/


		}

		class Widget {
		public:
			void f() {
				auto divisor = 5;

				filters.emplace_back(
					[&](int value)
				{
					return value % divisor == 0;
				}
				);

				filters.back()(3);
			}
		private:
			int m_Val = 3;
		};
	}

	namespace Case1 {
		class Gadget {
		public:
			Gadget() { std::cout << "default ctor" << std::endl; }
			Gadget(const Gadget& rhs) { std::cout << "copy ctor" << std::endl; }
			Gadget(Gadget&& rhs) { std::cout << "move ctor" << std::endl; }
		};

		class Widget {
		public:
			void f() {
				Gadget gadget;
				filters.emplace_back(
					[gadget](int value)		//�� ���� �߻�
				{ 
					auto g = gadget;
					return value % 5 == 0; 
				}		
				);
			}
		};

		inline void RunSample() {
			Widget w;
			w.f();
		}
	}

	namespace Case2 {
		/*
			�⺻ �� �������� ������(Ư�� this)�� ����� ���� �� ������, ���ٰ� �ڱ� �ϰ����̶�� ���ظ� �θ� �� �ִ�.
		*/

		class Widget {
		public:
			void f() {
				/*filters.emplace_back(
					[divisor](int value) { return value % divisor == 0; }
				);*/	//������ ����, divisor�� ĸ���� �� ����.

				filters.emplace_back(
					[=](int value) { return value % divisor == 0; }
				);
				/*
					ĸ�� ���� divisor �� �� ���� �Ǵ�, ���� Widget��ü �����ֱⰡ ������ divisor�� ��������� ������ ������?
					=> ���� �ƴϴ�


					�������� ���� ���ٰ� ������ ���� �ȿ��� ���̴�, static�� �ƴ� ���� ����(�Ű����� ����)���� ����ȴ�.
					
					Widget::f�� �������� divisor�� ���� ������ �ƴ϶� Ŭ������ �� ������ ����̹Ƿ� ĸ�ĵ� �� ����.
					��� ���� ���� ǥ���Ŀ��� [=]�� ���� �� �����ϰ� �ִ� ���� Widget�� this �������̴�.
				*/

				auto thisObj = this;
				filters.emplace_back(
					[thisObj](int value) { return value % thisObj->divisor == 0; }
				);
				/*
					���� �������� �ٲ��.

					�� ��ü�� �ı��ǰ� this �����Ͱ� �Ҹ�� ���� ���� ��ü�� ȣ���Ѵٸ� ������ �ൿ�� �����Ѵ�.
				*/

				filters.emplace_back(
					[divisor = this->divisor](int value) { return value % divisor == 0; }
				);
				/*
					c++14 �� ����� ���ؼ�(�Ϲ�ȭ�� ���� ĸ��)
					�����ϰ� ������ ����.
				*/
			}
		private:
			int divisor = 5;
		};

		inline void RunSample() {
			Widget w;
			w.f();
		}
	}

	namespace Case3 {
		/*
			���� ���� �⺻ ĸ�� ����� �� �ٸ� ������, 
			�ش� Ŭ������ �ڱ� �ϰ����̰� Ŭ���� �ٱ����� �Ͼ�� �������� ��ȭ�κ��� �ݸ��Ǿ� �ִٴ� ���ظ� �θ� �� �ִٴ� ���̴�.

			�ֳ��ϸ� ���ٰ� ���� ������ �Ű����� (ĸ�İ� ������)�Ӹ� �ƴ϶� 
			���� ����� ���� �Ⱓ(static storage duration)�� ���� ��ü���� ������ �� �ֱ� �����̴�.

			���� ����� ���� �Ⱓ�� ���� ��ü�� ���� �ȿ��� ����� ���� ������, ĸ���� ���� ����.

			�׷��� �⺻ �� ĸ�� ����� ǥ��� ��ġ �׷� ��ü�� ��� ĸ�ĵȴٴ� ������ �ش�.
		*/

		void RunSample(void)
		{
			static auto divisor = 5;				//��������

			filters.emplace_back(
				[=](int value)                           
			{ return value % divisor == 0; }        //��� �ƹ��͵� ĸ������ �ʴ´�. ���� ���� ������ ��Ī�Ѵ�.
			);
			/*
				RunSample�� �� ȣ���� ������ divisor�� �����ϸ�, 
				���� �� �Լ��� ���ؼ� filters�� �߰��� ���ٴ� �������� �ٸ� �ൿ(divisor�� �� ���� �����ϴ�)�� ���̰� �ȴ�.

				���ʿ� �⺻ �� ������ ��带 ������� �ʴ´ٸ� ��ó�� ������ ������ ū �ڵ尡 ������� ���赵 �������.
			*/

			++divisor;                                    
		}
	}

	
}