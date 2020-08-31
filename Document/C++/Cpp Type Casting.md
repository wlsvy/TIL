## const_cast

#### Reference 
- [cppreference : const_cast](https://en.cppreference.com/w/cpp/language/const_cast)
- [Effective C++ - 항목 3 : 낌새만 보이면 const를 들이대 보자!](https://github.com/wlsvy/TIL/blob/master/Document/C%2B%2B/Effective%20C%2B%2B/EffectiveCPP/EffectiveCPP/EffectiveC%2B%2B/Item03.cpp)

<br><br>

- Converts between types with different cv-qualification.
- const_cast는 서로 다른 cv 지정자를 가진 타입간의 변환을 수행합니다. (const_cast 지만 volatile 속성도 변환 가능)

- const_cast의 역할은 크게 두 가지
  - 특정 라이브러리에서 값을 변경해선 안되지만 const가 아닌 객체를 다룰 때, const를 붙이는 용도
    - (C 라이브러리 중 const 키워드가 도입되기 전에 만들어진 라이브러리를 다룰 때 사용한다고 함)
  - 일반 객체, const 객체에서 서로 다른 함수를 호출할 때 중복되는 코드 방지
  
- 제약 조건은 크게 세 가지 입니다.
  - 참조 타입에 대해서만 변환을 수행할 수 있다.
  - 참조하는 객체가 const 객체인 경우, 해당 포인터의 const 성을 제거하려는 시도는 미정의 동작을 유발할 수 있다.
    - 상수가 아닌 객체에 대해서만 const_cast를 수행하는 것이 안전하다.
  - 함수 포인터에 대해서는 동작하지 않는다.


```c++

#include <iostream>
#include <vector>
using namespace std;

namespace ConstCast_Study {
	class ExternalClass
	{
	public:
		int GetValue(void) { return Value; }
		void SetValue(int _Value) { Value = _Value; }
	private:
		int Value;
	};

	class TestClass
	{
	public:

		/*
			_rObj 는 const 객체이므로, 클래스 내부 const 멤버함수만 호출 가능
			 non-const 멤버함수를 호출할려면 const를 떼어야한다.
		*/
		bool IsZero(const ExternalClass& _rObj) const
		{
			return const_cast<ExternalClass&>(_rObj).GetValue() == 0;
		}
	};

	//Effective C++ Item 03 참조
	// + https://www.quora.com/In-C-what-is-the-proper-way-to-use-const_cast-so-that-it-does-not-result-in-undefined-behavior
	class TextBlock {
	public:
		TextBlock(std::string str) : text(str) {}

		//상수 객체에 대한 operator[]
		//const char& operator[](std::size_t position) const { return text[position]; }	

		//비상수 객체에 대한 operator[]
		//char & operator[](std::size_t position) { return text[position]; }				

		//상수 멤버 및 비상수 멤버 함수에서 코드 중복을 피하는 방법.
		/*
			비상수 버전이 상수 버전을 호출한다.

			c++ 에서 캐스팅은 썩 좋지 못한 아이디어지만, 코드 중복도 쉽게 넘길 순 없다.

			상수 버전 operator[]를 호출, *this에 const를 붙이고, 반환 타입에서 const를 뗀다.
			operator[]속에서 operator[] 를 호출하면 재귀적으로 계속 호출하게 되니,
			const operator[]를 호출하기 위한 방법으로 *this 에 const 를 붙인다.(탁월한 방법은 아니지만 차선책)
		*/
		const char& operator[](std::size_t position) const { return text[position]; }
		char & operator[] (std::size_t position) {
			return const_cast<char&>(
				static_cast<const TextBlock&>(*this)[position]
				);
		}

	private:
		std::string text;
	};

	inline void RunSample()
	{
		ExternalClass ValueObj;
		ValueObj.SetValue(100);

		TestClass TestObj;
		if (TestObj.IsZero(ValueObj))
			cout << "Zero" << endl;
		else
			cout << "Nonzero" << endl;

		const int ConstInt = 10;
		int* pInt = const_cast<int*>(&ConstInt);
		*pInt = 200;
		cout << ConstInt << endl;	//값 변하지 않음. const 값은 그대로
	}
}
```
## dynamic-cast

- dynamic-cast의 제약 조건
  - 상속 관계 안에서만 사용할 수 있다.
  - 하나 이상의 가상함수를 가지고 있어야 한다.
  - 컴파일러의 RTTI 설정이 켜져 있어야 한다.

```c++
namespace DynamicCast_Study {
	class Base
	{
	public:
		virtual void Put(void) { cout << "Base" << endl; }
	};

	class Derived : public Base
	{
	public:
		void Put(void) { cout << "Derived" << endl; }
	};

	inline void RunSample()
	{
		Base* pBase = new Base;
		Base* pDerived1 = new Derived;
		Derived* pDerived2 = new Derived;
		Derived* pDerived = NULL;

		// 컴파일 오류 : 타입 변환을 할 수 없다.
		//pDerived = pBase;

		// 컴파일 성공 : 런타임에 타입 변환에 실패하며 널을 리턴한다.
		pDerived = dynamic_cast<Derived*>(pBase);
		if (pDerived == NULL)
			cout << "Runtime Error" << endl;

		// 컴파일 오류 : 타입 변환을 할 수 없다.
		//pDerived = pDerived1;

		// 컴파일 성공 : 런타임에 타입 변환에 성공하며 Derived 타입의 포인터를 리턴한다.
		pDerived = dynamic_cast<Derived*>(pDerived1);
		if (pDerived)
			pDerived->Put();

		// 컴파일 성공 : 이런 경우에는 캐스팅이 필요 없다.
		pDerived = pDerived2;
	}
}
```

## static_cast

#### Reference
- [cppreference : static_cast](https://en.cppreference.com/w/cpp/language/static_cast)
<br><br>

`static_cast < new_type > ( expression )`

- expression에서 new_type으로 변환하는 암시적 변환 혹은 expression에서 new_type 객체를 생성하는 생성자가 있을 경우, 이들 중 적합한 것을 찾아서 임시객체 생성하거나, (만약에 있다면)사용자 정의 형변환 함수를 호출합니다.


```c++
struct B { };
struct D : B { };
D* d = new D();
B* b = &d;
void DoSomething(){
	D* d2 = static_cast<D*>(b);
}
```

* static_cast의 특징들을 요약해보자면
- 우측값으로 변환
- new_type 이 void 이면 static cast는 타입평가 이후 expression 값을 버린다
- 배열 참조값 타입을 업캐스트
- scoped enum을 int 로 변환
- enum 타입에서 다른 enum 타입으로 변환가능
- void* 다른 객체 포인터 타입으로 변환가능

```c++
namespace StaticCast_Study {
	struct B {
		int m = 0;
		void hello() const {
			std::cout << "Hello world, this is B!\n";
		}
	};
	struct D : B {
		void hello() const {
			std::cout << "Hello world, this is D!\n";
		}
	};

	enum class E { ONE = 1, TWO, THREE };
	enum EU { ONE = 1, TWO, THREE };

	class BaseOne
	{
	public:
		virtual void Put(void) { cout << "BaseOne" << endl; }
	};

	class BaseTwo
	{
	public:
		virtual void Put(void) { cout << "BaseTwo" << endl; }
	};

	class Derived : public BaseOne, public BaseTwo
	{
	public:
		void Put(void) { cout << "Derived" << endl; }
	};

	inline void RunSample()
	{
		int IntValue = 0;
		double DoubleValue = 100.0;

		// 암시적 캐스팅 : 경고 발생
		IntValue = DoubleValue;
		// 명시적 캐스팅 : 경고 없음
		IntValue = static_cast<int>(DoubleValue);

		// 컴파일 오류 : 변환할 수 없는 타입
		//char* pChar = static_cast<char*>( &IntValue );

		// 컴파일 성공 : void 포인터에서 변환은 가능
		void* pVoid = &IntValue;
		char* pChar = static_cast<char*>(pVoid);

		BaseOne* pBaseOne = NULL;
		BaseTwo* pBaseTwo = new Derived;
		Derived*    pDerived = NULL;

		// 컴파일 성공 : 계층간 타입 변환이 가능 (타입 안전 검사는 안함)
		pDerived = static_cast<Derived*>(pBaseTwo);

		// 컴파일 오류 : 변환할 수 없는 타입
		//pBaseOne = static_cast<BaseOne*>( pBaseTwo );   

		//======================================
		//cpp reference 예제 코드
		//======================================

		// 1: initializing conversion
		int n = static_cast<int>(3.14);
		std::cout << "n = " << n << '\n';
		std::vector<int> v = static_cast<std::vector<int>>(10);
		std::cout << "v.size() = " << v.size() << '\n';

		// 2: static downcast
		D d;
		B& br = d; // upcast via implicit conversion
		br.hello();
		D& another_d = static_cast<D&>(br); // downcast
		another_d.hello();

		// 3: lvalue to xvalue
		std::vector<int> v2 = static_cast<std::vector<int>&&>(v);
		std::cout << "after move, v.size() = " << v.size() << '\n';

		// 4: discarded-value expression
		static_cast<void>(v2.size());

		// 5. inverse of implicit conversion
		void* nv = &n;
		int* ni = static_cast<int*>(nv);
		std::cout << "*ni = " << *ni << '\n';

		// 6. array-to-pointer followed by upcast
		D a[10];
		B* dp = static_cast<B*>(a);

		// 7. scoped enum to int or float
		E e = E::ONE;
		int one = static_cast<int>(e);
		std::cout << one << '\n';

		// 8. int to enum, enum to another enum
		E e2 = static_cast<E>(one);
		EU eu = static_cast<EU>(e2);

		// 9. pointer to member upcast
		int D::*pm = &D::m;
		std::cout << br.*static_cast<int B::*>(pm) << '\n';

		// 10. void* to any type
		void* voidp = &e;
		std::vector<int>* p = static_cast<std::vector<int>*>(voidp);

	}
	/*
	'pDerived = static_cast<Derived*>( pBaseTwo );' 에서 타입 변환은 컴파일 타임에 끝난다.
	pBaseTwo 에 NULL 이 들어가 있어도 컴파일은 성공한다.
	즉, 변환하려는 포인터가 계층 관계에 있다면 어떤 값을 가지고 있던지 컴파일은 성공한다는 말이다.
	문제는 런타임에 발생할 것이고 대부분 프로그램의 다운으로 이어질 것이다.
	이런 문제점 때문에 클래스 계층 간의 타입 변환에 dynamic_cast 를 추천하는 것이다.

	출처: https://prostars.net/64?category=2732 [I'm Prostars]
	*/
}
```

## reinterpret_cast

#### Reference
- [cppreference : reinterpret_cast](https://en.cppreference.com/w/cpp/language/reinterpret_cast)
<br><br>
- 컴파일 시간에 임의 타입의 포인터 간 형 변환을 수행합니다.
- 다이나믹 캐스트와는 다르게 클래스 관계에 따른 안전 검사를 하지 않고 이루어지기 때문에 사용하기에 따라서 굉장히 위험할 수도 있습니다. 보통 비트단위로 활용하는 데이터를 다룰 때 사용합니다.

```c++
namespace Reinterpretcast_Study {
	class BaseOne
	{
	public:
		virtual void Put1(void) { cout << "BaseOne 1" << endl; }
		virtual void Put2(void) { cout << "BaseOne 2" << endl; }
	};

	class BaseTwo
	{
	public:
		virtual void Put1(void) { cout << "BaseTwo 1" << endl; }
	};

	inline void RunSample()
	{
		int IntValue = 1020;
		char* pCharPtr1 = NULL;
		char* pCharPtr2 = NULL;

		// 컴파일 오류 : 변환할 수 없는 타입
		//pCharPtr = IntValue;

		// 컴파일 오류 : 변환할 수 없는 타입
		//pCharPtr = static_cast<char*>( IntValue );

		// 컴파일 성공 : 정수를 포인터 타입으로 재해석함 (주소가 유효한지 검사안함)
		pCharPtr1 = reinterpret_cast<char*>(IntValue);

		// 해당 변수의 주소 영역에 값을 강제로 쓰는 것 같은 결과 (매우 위험)
		memcpy(&pCharPtr2, &IntValue, sizeof(pCharPtr2));

		BaseOne* pBaseOne = NULL;
		BaseTwo* pBaseTwo = new BaseTwo;

		// 컴파일 오류 : 상속 관계가 없음
		//pBaseOne = pBaseTwo;

		// 컴파일 성공 : 비트 단위로 재해석함
		pBaseOne = reinterpret_cast<BaseOne*>(pBaseTwo);

		// 런타임 오류 발생
		pBaseOne->Put2();

		const char* pConstCharPtr = NULL;
		char* pCharPtr = NULL;

		// 컴파일 오류 : reinterpret_cast 도 상수성은 제거 못함
		//pCharPtr = reinterpret_cast<char*>( pConstCharPtr );

		// 컴파일 성공 : const_cast 의 고유 기능
		pCharPtr = const_cast<char*>(pConstCharPtr);
	}
}
```
