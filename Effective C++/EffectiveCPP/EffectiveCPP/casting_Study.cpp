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
			return false;	//_rObj �� const ��ü�̹Ƿ�, Ŭ������ const ����Լ��� ȣ�� ����
							// non-const ����Լ��� ȣ���ҷ��� const�� ������Ѵ�.
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
		cout << ConstInt << endl;	//�� ������ ����. const ���� �״��

		return 0;
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

	void Dynamic_Cast_tmain(int argc, char* argv[])
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

		// ������ ���� : ��ȯ�� �� ���� Ÿ�� (dynamic_cast �ʿ�)
		//pBaseOne = static_cast<BaseOne*>( pBaseTwo );   

		return 0;
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

		return 0;
	}
}