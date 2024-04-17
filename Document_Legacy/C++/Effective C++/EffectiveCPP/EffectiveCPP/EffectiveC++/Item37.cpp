#include <iostream>
#include <vector>
#include <string>
#include <functional>
using namespace std;

//어떤 함수에 대해서도 상속받은 기본 매개변수 값은 절대로 재정의하지 말자

namespace Item37 {
	class Shape {
	public:
		enum ShapeColor { Red, Green, Blue };
		virtual void draw(ShapeColor color = Red) const {}
	};

	class Rectangle : public Shape {
	public:
		virtual void draw(ShapeColor color = Green) const {}	//기본 매개변수 값 변경
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
			Rectangle::draw(Shape::Red) 호출, Green 이 아니다!
			매개변수는 기본값은 정적으로 바인딩되기 때문
			가상함수는 동적 바인딩되기 때문에 Rectangle의 것을 사용하지만 기본 매개변수는 Shape의 것을 사용한다
		*/
		pc->draw();
	}
}