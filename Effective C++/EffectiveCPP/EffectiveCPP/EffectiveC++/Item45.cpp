#include <iostream>
#include <vector>
#include <string>
using namespace std;

//"호환되는 모든 타입"을 받아들이는 데는 멤버 함수 템플릿이 직방!

namespace Item45 {

	class Top {};
	class Middle : public Top {};
	class Bottom : public Middle {};

	template<typename T>
	class SmartPtr {
	public:
		explicit SmartPtr(T *realPtr) : heldPtr(realPtr) {}
	private:
		T* heldPtr;
	};

	void func() {

		Top *pt1 = new Middle;
		Top *pt2 = new Bottom;
		const Top *pct = pt1;
		//문제 없이 변환 가능

		/*
			SmartPtr<Top> spt1 = SmartPtr<Middle>(new Middle);
			SmartPtr<Top> spt2 = SmartPtr<Bottom>(new Bottom);
			SmartPtr<const Top> spct = pt1;

			컴파일 에러.
			템플릿 매개변수는 서로 상속관계에 있을지라도, 같은 템플릿으로 부터 만들어진 인스턴스는 어떤 연관관계도 없다
		*/
	}
}

namespace Item45_2 {
	//멤버 함수 템플릿(member function template, 멤버 템플릿 이라고도 함) 을 이용한 방법
	//-> 같은 템플릿을 써서 인스턴스화되지만 타입이 다른 타입의 객체로부터 원하는 객체를 만들어 주는 생성자 
	// 일반화 복사 생성자(generalized copy constructor)

	class Top {};
	class Middle : public Top {};
	class Bottom : public Middle {};

	template<typename T>
	class SmartPtr {
	public:
		/*
			template<typename U>
			SmartPtr(const SmartPtr<U>& other);

			일반화된 복사 생성자를 만들기 위해 마련한 멤버 템플릿
			위의 방식으로 SmartPtr<U> 로부터 SmartPtr<T>를 만들어 낼 수 있다.

			문제는 모든 타입에 대해 변환이 가능해서 int* 가 double* 로 변환될 수 있고
			SmartPtr<Bottom> 이 SmartPtr<Top> 으로 변환될 수 있다. (우리가 바랬던 건 Top -> Bottom 으로의 변환. 반대의 경우까진 필요가 없다)
		*/
		

		template<typename U>
		SmartPtr (const SmartPtr<U>& other) : heldPtr(other.get()) {}	
		/*
			위 방법으로 포인터 타입간의 변환 제약을 줄 수 있다.
			U* 가 T* 로 변환이 가능하지 않다면 컴파일 에러가 발생

			explicit 를 쓰지 않은 이유. 보통의 포인터는 암시적으로 업캐스팅이 가능한 것처럼. 여기서도 암시적 변환을 고려
		*/

		T* get() const { return heldPtr; }
	private:
		T* heldPtr;
	};

	/*
		shared_ptr의 생성자와 대입연산자가 구현된 방식
	*/
	template<class T> 
	class shared_ptr {
	public:
		template<class Y>
		explicit shared_ptr(Y* p);	//호환되는 모든 기본제공 포인터 변환
		template<class Y>
		shared_ptr(shared_ptr<Y> const& r);	//shared_ptr의 일반화 복사 생성자 //shared/weak/auto 포인터로부터 변환
		template<class Y>
		explicit shared_ptr(weak_ptr<Y> const& r);
		template<class Y>
		explicit shared_ptr(auto_ptr<Y>& r);	//auto_ptr 의 경우는 const 가 없는데, auto_ptr은 객체가 복사될 때 소유권 이전이 발생하기 때문

		shared_ptr (shared_ptr const& r);	//shared_ptr의 복사 생성자

		//생성자에서 shared_ptr을 매개변수로 사용하는 경우 explicit을 쓰지 않는데, 이는 다른 포인터 타입은 암시적변환을 허용하지 않고 shared_ptr에 대해서만 허용하겠다는 뜻

		template<class Y>
		shared_ptr& operator=(shared_ptr<Y> const& r);	//shared_ptr의 일반화 복사 대입 연산자 //대입 연산 역시 가능
		template<class Y>
		shared_ptr& operator=(auto_ptr<Y>& r);

		shared_ptr& operator=(shared_ptr const& r);	//복사 대입 연산자

		/*
			컴파일러가 특정 사용자 정의 클래스에 대해서 복사 생성자/대입 연산자가 정의되지 않았으면 스스로 만드는 것처럼
			템플릿 클래스에서 컴파일러가 일반화 복사 생성자를 스스로 만들어버리는 경우가 있다.(물론 프로그래머가 정의하지 않았을 경우)

			일반화 복사 생성자와 복사 생성자는 독립된 것이기 때문에 복사 생성자를 구현한다면 컴파일러가 복사 생성자를 또 만들지는 않겠지만 일반화 복사 생성자는 별개의 일이다. 

			위의 예시에서 처럼 프로그래머가 복사 생성을 스스로 정의하고 싶다면 일반화 복사 생성자와 복사 생성자를 구현해둬야 할 것이다.
			대입 연산자도 마찬가지
		*/
	};
}