#include <iostream>
#include <vector>
#include <string>
#include <functional>
using namespace std;

//� �Լ��� ���ؼ��� ��ӹ��� �⺻ �Ű����� ���� ����� ���������� ����

namespace Item37 {
	class Shape {
	public:
		enum ShapeColor { Red, Green, Blue };
		virtual void draw(ShapeColor color = Red) const {}
	};

	class Rectangle : public Shape {
	public:
		virtual void draw(ShapeColor color = Green) const {}	//�⺻ �Ű����� �� ����
	};

	class Circle : public Shape {
	public:
		virtual void draw(ShapeColor color) const {}
	};
	
	void func() {
		Shape *ps;
		Shape *pc = new Circle;
		Shape *pr = new Rectangle;

		/*
			Rectangle::draw(Shape::Red) ȣ��, Green �� �ƴϴ�!
			�Ű������� �⺻���� �������� ���ε��Ǳ� ����
			�����Լ��� ���� ���ε��Ǳ� ������ Rectangle�� ���� ��������� �⺻ �Ű������� Shape�� ���� ����Ѵ�
		*/
		pc->draw();
	}
}