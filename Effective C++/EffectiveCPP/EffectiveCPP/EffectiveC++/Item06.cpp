#include <iostream>
#include <vector>
#include <string>

class Item04 {
public:

};

class HomeForSale {
public:

private:
	HomeForSale(const HomeForSale&);	//선언만 달랑 있습니다.
	HomeForSale& operator=(const HomeForSale&);	//요 방식으로, 복사 생성자 와 대입 연산자를 사용할 수 없도록 막아버린다.
};

class Uncopyable {
protected:
	Uncopyable() {}	//생성과 소멸 허용
	~Uncopyable() {}
private:
	Uncopyable(const Uncopyable&);	//복사 생성, 대입은 방지한다. 링크 시점에서 에러 판정
	Uncopyable& operator=(const Uncopyable);
};

class HomeForSale2 : private Uncopyable {	//private 상속
	//복사생성자, 대입 연산자를 선언조차 할 수 없다.
};