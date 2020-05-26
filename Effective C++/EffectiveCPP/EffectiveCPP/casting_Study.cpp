#include <iostream>
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
		bool IsZero(const ExternalClass& _rObj) const
		{
			if (const_cast<ExternalClass&>(_rObj).GetValue() == 0) return true;
			return false;	//_rObj 는 const 객체이므로, 클래스네 const 멤버함수만 호출 가능
							// non-const 멤버함수를 호출할려면 const를 떼어야한다.
		}
	};

	int const_cast_test_main(int argc, char* argv[])
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

		return 0;
	}
}

namespace DynamicCast_Study {
	/*
	Dynamic cast 제약조건
	* 상속 관계 안에서만 사용할 수 있다.
	* 하나 이상의 가상함수를 가지고 있어야 한다.
	*컴파일러의 RTTI 설정이 켜져 있어야 한다.
	*/

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

	void Dynamic_Cast_tmain(int argc, char* argv[])
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

namespace StaticCastStudy {
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

	int Static_Cast_main(int argc, char* argv[])
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

		// 컴파일 오류 : 변환할 수 없는 타입 (dynamic_cast 필요)
		//pBaseOne = static_cast<BaseOne*>( pBaseTwo );   

		return 0;
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

namespace Rcast_Study {
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

	int Reinterpret_Cast_tmain(int argc, char* argv[])
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

		return 0;
	}
}