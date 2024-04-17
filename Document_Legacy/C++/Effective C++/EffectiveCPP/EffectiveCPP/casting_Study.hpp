#include <iostream>
#include <vector>
using namespace std;

namespace ConstCast_Study {
	/*
		Converts between types with different cv-qualification.
		const_cast�� ���� �ٸ� cv �����ڸ� ���� Ÿ�԰��� ��ȯ�� �����Ѵ�. (const_cast ���� volatile �Ӽ��� ��ȯ ����)
		https://en.cppreference.com/w/cpp/language/const_cast

		const_cast ������ ũ�� �� ����

		1. Ư�� ���̺귯������ ���� �����ؼ� �ȵ����� const�� �ƴ� ��ü�� �ٷ� ��, const�� ���̴� �뵵
		(C ���̺귯�� �� const Ű���尡 ���ԵǱ� ���� ������� ���̺귯���� �ٷ� �� ����Ѵٰ� ��)

		2. const_cast�� �Ϲ� ��ü, const ��ü���� ���� �ٸ� �Լ��� ȣ���� �� �ߺ��Ǵ� �ڵ� ����

		const_cast ��������
		1. ���� Ÿ�Կ� ���ؼ��� ��ȯ�� ������ �� �ִ�.
		2. �����ϴ� ��ü�� const ��ü�� ���, �ش� �������� const ���� �����Ϸ��� �õ��� ������ ������ ������ �� �ִ�.
		-> ����� �ƴ� ��ü�� ���ؼ��� const_cast�� �����ϴ� ���� �����ϴ�.

		3. �Լ� �����Ϳ� ���ؼ��� �������� �ʴ´�.
	*/
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
			_rObj �� const ��ü�̹Ƿ�, Ŭ���� ���� const ����Լ��� ȣ�� ����
			 non-const ����Լ��� ȣ���ҷ��� const�� ������Ѵ�.
		*/
		bool IsZero(const ExternalClass& _rObj) const
		{
			return const_cast<ExternalClass&>(_rObj).GetValue() == 0;
		}
	};

	//Effective C++ Item 03 ����
	// + https://www.quora.com/In-C-what-is-the-proper-way-to-use-const_cast-so-that-it-does-not-result-in-undefined-behavior
	class TextBlock {
	public:
		TextBlock(std::string str) : text(str) {}

		//��� ��ü�� ���� operator[]
		//const char& operator[](std::size_t position) const { return text[position]; }	

		//���� ��ü�� ���� operator[]
		//char & operator[](std::size_t position) { return text[position]; }				

		//��� ��� �� ���� ��� �Լ����� �ڵ� �ߺ��� ���ϴ� ���.
		/*
			���� ������ ��� ������ ȣ���Ѵ�.

			c++ ���� ĳ������ �� ���� ���� ���̵������, �ڵ� �ߺ��� ���� �ѱ� �� ����.

			��� ���� operator[]�� ȣ��, *this�� const�� ���̰�, ��ȯ Ÿ�Կ��� const�� ����.
			operator[]�ӿ��� operator[] �� ȣ���ϸ� ��������� ��� ȣ���ϰ� �Ǵ�,
			const operator[]�� ȣ���ϱ� ���� ������� *this �� const �� ���δ�.(Ź���� ����� �ƴ����� ����å)
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
		cout << ConstInt << endl;	//�� ������ ����. const ���� �״��
	}
}

namespace DynamicCast_Study {
	/*
	Dynamic cast ��������
	* ��� ���� �ȿ����� ����� �� �ִ�.
	* �ϳ� �̻��� �����Լ��� ������ �־�� �Ѵ�.
	*�����Ϸ��� RTTI ������ ���� �־�� �Ѵ�.
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

	inline void RunSample()
	{
		Base* pBase = new Base;
		Base* pDerived1 = new Derived;
		Derived* pDerived2 = new Derived;
		Derived* pDerived = NULL;

		// ������ ���� : Ÿ�� ��ȯ�� �� �� ����.
		//pDerived = pBase;

		// ������ ���� : ��Ÿ�ӿ� Ÿ�� ��ȯ�� �����ϸ� ���� �����Ѵ�.
		pDerived = dynamic_cast<Derived*>(pBase);
		if (pDerived == NULL)
			cout << "Runtime Error" << endl;

		// ������ ���� : Ÿ�� ��ȯ�� �� �� ����.
		//pDerived = pDerived1;

		// ������ ���� : ��Ÿ�ӿ� Ÿ�� ��ȯ�� �����ϸ� Derived Ÿ���� �����͸� �����Ѵ�.
		pDerived = dynamic_cast<Derived*>(pDerived1);
		if (pDerived)
			pDerived->Put();

		// ������ ���� : �̷� ��쿡�� ĳ������ �ʿ� ����.
		pDerived = pDerived2;
	}
}

namespace StaticCast_Study {
	/*
		Converts between types using a combination of implicit and user-defined conversions.
		Ÿ�԰� �Ͻ��� ��ȯ Ȥ�� ����� ���� ����ȯ �Լ��� ���� Ÿ�԰� ��ȯ�� �����Ѵ�.

		https://en.cppreference.com/w/cpp/language/static_cast

		static_cast < new_type > ( expression )
		- expression���� new_type���� ��ȯ�ϴ� �Ͻ��� ��ȯ Ȥ�� expression���� new_type ��ü�� �����ϴ� �����ڰ� ���� ���,
		�̵� �� ������ ���� ã�Ƽ� �ӽð�ü �����ϰų�, (���࿡ �ִٸ�)����� ���� ����ȯ �Լ��� ȣ���Ѵ�.

		struct B { };
		struct D : B { };
		D d;
		B& br = d;
		static_cast<D&>(br); // lvalue denoting the original d object
		- �� ���, Ÿ�԰˻縦 ���� ����ä ����ȯ�� �����Ѵ�.

		- ���������� ��ȯ
		- new_type �� void �̸� static cast�� Ÿ���� ���� expression ���� ������
		- �迭 ������ Ÿ���� ��ĳ��Ʈ
		- scoped enum�� int �� ��ȯ
		- enum Ÿ�Կ��� �ٸ� enum Ÿ������ ��ȯ����
		- void* �ٸ� ��ü ������ Ÿ������ ��ȯ����
	*/

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

		// �Ͻ��� ĳ���� : ��� �߻�
		IntValue = DoubleValue;
		// ����� ĳ���� : ��� ����
		IntValue = static_cast<int>(DoubleValue);

		// ������ ���� : ��ȯ�� �� ���� Ÿ��
		//char* pChar = static_cast<char*>( &IntValue );

		// ������ ���� : void �����Ϳ��� ��ȯ�� ����
		void* pVoid = &IntValue;
		char* pChar = static_cast<char*>(pVoid);

		BaseOne* pBaseOne = NULL;
		BaseTwo* pBaseTwo = new Derived;
		Derived*    pDerived = NULL;

		// ������ ���� : ������ Ÿ�� ��ȯ�� ���� (Ÿ�� ���� �˻�� ����)
		pDerived = static_cast<Derived*>(pBaseTwo);

		// ������ ���� : ��ȯ�� �� ���� Ÿ��
		//pBaseOne = static_cast<BaseOne*>( pBaseTwo );   

		//======================================
		//cpp reference ���� �ڵ�
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
	'pDerived = static_cast<Derived*>( pBaseTwo );' ���� Ÿ�� ��ȯ�� ������ Ÿ�ӿ� ������.
	pBaseTwo �� NULL �� �� �־ �������� �����Ѵ�.
	��, ��ȯ�Ϸ��� �����Ͱ� ���� ���迡 �ִٸ� � ���� ������ �ִ��� �������� �����Ѵٴ� ���̴�.
	������ ��Ÿ�ӿ� �߻��� ���̰� ��κ� ���α׷��� �ٿ����� �̾��� ���̴�.
	�̷� ������ ������ Ŭ���� ���� ���� Ÿ�� ��ȯ�� dynamic_cast �� ��õ�ϴ� ���̴�.

	��ó: https://prostars.net/64?category=2732 [I'm Prostars]
	*/
}

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

		// ������ ���� : ��ȯ�� �� ���� Ÿ��
		//pCharPtr = IntValue;

		// ������ ���� : ��ȯ�� �� ���� Ÿ��
		//pCharPtr = static_cast<char*>( IntValue );

		// ������ ���� : ������ ������ Ÿ������ ���ؼ��� (�ּҰ� ��ȿ���� �˻����)
		pCharPtr1 = reinterpret_cast<char*>(IntValue);

		// �ش� ������ �ּ� ������ ���� ������ ���� �� ���� ��� (�ſ� ����)
		memcpy(&pCharPtr2, &IntValue, sizeof(pCharPtr2));

		BaseOne* pBaseOne = NULL;
		BaseTwo* pBaseTwo = new BaseTwo;

		// ������ ���� : ��� ���谡 ����
		//pBaseOne = pBaseTwo;

		// ������ ���� : ��Ʈ ������ ���ؼ���
		pBaseOne = reinterpret_cast<BaseOne*>(pBaseTwo);

		// ��Ÿ�� ���� �߻�
		pBaseOne->Put2();

		const char* pConstCharPtr = NULL;
		char* pCharPtr = NULL;

		// ������ ���� : reinterpret_cast �� ������� ���� ����
		//pCharPtr = reinterpret_cast<char*>( pConstCharPtr );

		// ������ ���� : const_cast �� ���� ���
		pCharPtr = const_cast<char*>(pConstCharPtr);
	}
}