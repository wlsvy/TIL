#pragma once
#include <iostream>
#include <vector>
#include <array>
#include <string>

namespace Item15 {

	/*
		constexpr�� ��� ���� ���� ����� �Ӹ� �ƴ϶� ������ �������� �˷����ٴ� ���� ��Ÿ����.
		������ �ý��� ������(embedded)���� �߿��� Ư¡�� �� �ִ�.

		constexpr�� ��ü�� ����� ���� �� ���� ������ �ð��� �˷�����.
		��� constexpr ��ü�� const ���� �ݴ�� �������� �ʴ´�.
	*/

	namespace ConstexprObject {
		inline void RunSample() {

			const int csize1 = 5;
			std::array<int, csize1> arr1;	//����

			int size = 5;
			const int csize2 = size;
			//std::array<int, csize2> arr2;	//���� csize2 �� ������ �ð��� �������� ����

			constexpr int csize3 = 5;
			std::array<int, csize3> arr3;	//����

			//constexpr int csize4 = size;	//����, csize4�� ������ �ð��� �������� ����
		}
	}

	namespace ConstexprFunc {
		constexpr int pow(int base, int exp) noexcept {
			for (int i = 0; i < exp; ++i) {
				base *= exp;
			}
			return base;
		}

		class Widget {
		public:
			Widget() { std::cout << "default ctor" << std::endl; }
		};

		class Point {
		public:
			/*
				point�� ��ü�� ������� double�� ������ ������ �˷��� �� �ֱ� ������, point�� �����ڸ� constexpr���� ���𰡴��ϴ�.
			*/
			constexpr Point(double xVal = 0, double yVal = 0) noexcept : x(xVal), y(yVal) {}
			constexpr double xValue(void) const noexcept { return x; }
			constexpr double yValue(void) const noexcept { return y; }

			/*
				C++ 11���� setX/setY �� constexpr ���� �����ϱ⿡�� �� ���� ������ �־���.
				1. �� �Լ� �ȿ����� ��ü�� ����� ���������� c++11������ constexpr ��� �Լ��� �Ϲ������� const �� ����ȴ�.
				2. �� ��� �Լ����� ��ȯ ������ void�ε� c++11���� void�� ���ͷ� ������ �ƴϴ�.

				C++14������ �� ���� ������ ��������� ������ ����Լ� ���� constexpr ������ �����ϴ�.
			*/
			constexpr void setX(double newX) noexcept { x = newX; }
			constexpr void setY(double newY) noexcept { y = newY; }
			
		private:
			double x, y;
		};

		constexpr Point midpoint(const Point& p1, const Point& p2) noexcept
		{
			//constexr ��� �Լ��� ȣ�Ⱑ���ϴ�.
			return { (p1.xValue() + p2.xValue()) / 2,    
					(p1.yValue() + p2.yValue()) / 2 };   
		}

		constexpr Point reflection(const Point& p) noexcept {
			Point result;
			result.setX(-p.xValue());
			result.setY(-p.yValue());
			return result;
		}

		inline void RunSample() {
			//constexpr Widget w;	//����, �����ڰ� constexpr�� �ƴ�
			constexpr Point p1(1.0f, 2.0f);
			constexpr Point p2(31.2f, 4.1f);
			constexpr auto mid = midpoint(p1, p2);	
			constexpr auto reflectedMid = reflection(mid);
			/*
				������ �ð���, �б� ���� �޸�(Rom)�� �����Ѵ�.
				���������� ��������� �����ߴ� ������ ������ �ð����� �ű�� ��
			*/
		}
	}
}