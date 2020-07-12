#include <iostream>
#include <vector>
#include <string>
using namespace std;

//"ȣȯ�Ǵ� ��� Ÿ��"�� �޾Ƶ��̴� ���� ��� �Լ� ���ø��� ����!

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
		//���� ���� ��ȯ ����

		/*
			SmartPtr<Top> spt1 = SmartPtr<Middle>(new Middle);
			SmartPtr<Top> spt2 = SmartPtr<Bottom>(new Bottom);
			SmartPtr<const Top> spct = pt1;

			������ ����.
			���ø� �Ű������� ���� ��Ӱ��迡 ��������, ���� ���ø����� ���� ������� �ν��Ͻ��� � �������赵 ����
		*/
	}
}

namespace Item45_2 {
	//��� �Լ� ���ø�(member function template, ��� ���ø� �̶�� ��) �� �̿��� ���
	//-> ���� ���ø��� �Ἥ �ν��Ͻ�ȭ������ Ÿ���� �ٸ� Ÿ���� ��ü�κ��� ���ϴ� ��ü�� ����� �ִ� ������ 
	// �Ϲ�ȭ ���� ������(generalized copy constructor)

	class Top {};
	class Middle : public Top {};
	class Bottom : public Middle {};

	template<typename T>
	class SmartPtr {
	public:
		/*
			template<typename U>
			SmartPtr(const SmartPtr<U>& other);

			�Ϲ�ȭ�� ���� �����ڸ� ����� ���� ������ ��� ���ø�
			���� ������� SmartPtr<U> �κ��� SmartPtr<T>�� ����� �� �� �ִ�.

			������ ��� Ÿ�Կ� ���� ��ȯ�� �����ؼ� int* �� double* �� ��ȯ�� �� �ְ�
			SmartPtr<Bottom> �� SmartPtr<Top> ���� ��ȯ�� �� �ִ�. (�츮�� �ٷ��� �� Top -> Bottom ������ ��ȯ. �ݴ��� ������ �ʿ䰡 ����)
		*/
		

		template<typename U>
		SmartPtr (const SmartPtr<U>& other) : heldPtr(other.get()) {}	
		/*
			�� ������� ������ Ÿ�԰��� ��ȯ ������ �� �� �ִ�.
			U* �� T* �� ��ȯ�� �������� �ʴٸ� ������ ������ �߻�

			explicit �� ���� ���� ����. ������ �����ʹ� �Ͻ������� ��ĳ������ ������ ��ó��. ���⼭�� �Ͻ��� ��ȯ�� ���
		*/

		T* get() const { return heldPtr; }
	private:
		T* heldPtr;
	};

	/*
		shared_ptr�� �����ڿ� ���Կ����ڰ� ������ ���
	*/
	template<class T> 
	class shared_ptr {
	public:
		template<class Y>
		explicit shared_ptr(Y* p);	//ȣȯ�Ǵ� ��� �⺻���� ������ ��ȯ
		template<class Y>
		shared_ptr(shared_ptr<Y> const& r);	//shared_ptr�� �Ϲ�ȭ ���� ������ //shared/weak/auto �����ͷκ��� ��ȯ
		template<class Y>
		explicit shared_ptr(weak_ptr<Y> const& r);
		template<class Y>
		explicit shared_ptr(auto_ptr<Y>& r);	//auto_ptr �� ���� const �� ���µ�, auto_ptr�� ��ü�� ����� �� ������ ������ �߻��ϱ� ����

		shared_ptr (shared_ptr const& r);	//shared_ptr�� ���� ������

		//�����ڿ��� shared_ptr�� �Ű������� ����ϴ� ��� explicit�� ���� �ʴµ�, �̴� �ٸ� ������ Ÿ���� �Ͻ�����ȯ�� ������� �ʰ� shared_ptr�� ���ؼ��� ����ϰڴٴ� ��

		template<class Y>
		shared_ptr& operator=(shared_ptr<Y> const& r);	//shared_ptr�� �Ϲ�ȭ ���� ���� ������ //���� ���� ���� ����
		template<class Y>
		shared_ptr& operator=(auto_ptr<Y>& r);

		shared_ptr& operator=(shared_ptr const& r);	//���� ���� ������

		/*
			�����Ϸ��� Ư�� ����� ���� Ŭ������ ���ؼ� ���� ������/���� �����ڰ� ���ǵ��� �ʾ����� ������ ����� ��ó��
			���ø� Ŭ�������� �����Ϸ��� �Ϲ�ȭ ���� �����ڸ� ������ ���������� ��찡 �ִ�.(���� ���α׷��Ӱ� �������� �ʾ��� ���)

			�Ϲ�ȭ ���� �����ڿ� ���� �����ڴ� ������ ���̱� ������ ���� �����ڸ� �����Ѵٸ� �����Ϸ��� ���� �����ڸ� �� �������� �ʰ����� �Ϲ�ȭ ���� �����ڴ� ������ ���̴�. 

			���� ���ÿ��� ó�� ���α׷��Ӱ� ���� ������ ������ �����ϰ� �ʹٸ� �Ϲ�ȭ ���� �����ڿ� ���� �����ڸ� �����ص־� �� ���̴�.
			���� �����ڵ� ��������
		*/
	};
}