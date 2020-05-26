#include <iostream>
#include <vector>
#include <string>
using namespace std;

namespace Item28 {
	//내부에서 사용하는 객체에 대한 '핸들'을 반환하는 코드는 되도록 피하자

	class Point {
	public:
		Point(int x, int y) : X(x), Y(y) {}
		void SetX(int x) { X = x; }
		void SetY(int y) { Y = y; }
	private:
		int X, Y;
	};

	struct RectData {
		Point ulhc;
		Point lrhc;
	};

	class Rectangle {
	public:
		Point& upperLeft() const { return pData->ulhc; }
		Point& lowerRight() const { return pData->lrhc; }
	private:
		std::shared_ptr<RectData> pData;
	};


	void func() {
		//위 코드의 문제점

		const Rectangle rec;
		rec.upperLeft().SetX(3);	//Rectangle의 데이터는 private 선언되었음에도 불구하고 사용자는 데이터의 좌표값을 변경할 수 있다.

		/*
			클래스 데이터 멤버는 아무리 숨겨봤자 그 멤버의 참조자를 반환하는 함수들의 최대 접근도에 따라 캡슐화의 정도가 결정된다.
			위의 예제에서는 Rectangle 클래스의 upperLeft, lowerRight 함수의 반환타입을 const Point& 로 바꾸면 해결된다.
		*/
	}

	class GUIObject {};

	const Rectangle boundingBox(const GUIObject& obj);

	void func2() {
		GUIObject *pgo = new GUIObject();

		const Point *pUpperLeft = &(boundingBox(*pgo).upperLeft()); //사각 테두리 영역으로부터 왼쪽 위 포인터의 주소값 획득

		/*
			주의해야할 점 -> boundingBox(*pgo) 로 생성된 Rectangle 은 임시객체이므로 문장이 끝난 뒤 소멸된다.
			즉 pUpperLeft 는 댕글링 포인터가 되는 것.

			어떤 객체의 내부요소에 대한 핸들(Handle, 다른 객체에 손 댈 수 있게 하는 매개자 - 참조자, 포인터, 반복자)을 반환하는 것을 되도록 피하자
			캡슐화 정도를 높이고, 상수 멤버 함수가 객체의 상수성을 유지한 채로 동작할 수 있도록 하며, 무효참조 핸들이 생기는 경우를 최소화할 수 있다.
		*/
	}

	const Rectangle boundingBox(const GUIObject& obj) {
		return Rectangle();
	}

}