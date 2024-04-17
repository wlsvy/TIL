#include <iostream>
#include <vector>
#include <string>
using namespace std;

//new ó������ ���� ������ ����� ��������

namespace Item49 {
	/*
		new ó���ڶ�?
		�޸� �Ҵ��� ����� ���� ���� ��Ȳ�� ���� �������� operator new�� ���ܸ� ������ ����, 
		�� �Լ��� ����� �ʿ��� ������ �� �ִ� ���� ó�� �Լ��� �켱������ ȣ���ҵ��� �Ǿ� �ִµ�
		�� ���� ó�� �Լ��� ������ new ó����(new-handler, �Ҵ翡�� ó����)��� �Ѵ�

		(��� ������ �´� ���� �ƴϴ�. operator new �� ������ �ξ� �����ϴ�)
	*/

	//std:: ���ӽ����̽����� new_handler�� �޴� �͵� ���� ��ȯ���� ���� �Լ��� �����Ϳ� typedef�� �ɾ�� Ÿ�� ���Ǿ�
	typedef void(*new_handler) ();	
	
	//new ó���ڸ� �����ϴ� �Լ�
	new_handler set_new_handler(new_handler p) throw();	

	/*
		- New ó���� �Լ��� �ùٸ��� ����ϱ� ���ؼ��� ���� ���� �� �ϳ��� �ݵ�� �� �־�� �Ѵ�.

		1. ����� �� �ִ� �޸𸮸� �� ���� Ȯ��

		2. �ٸ� new ó���� ��ġ - 
		������ new ó���ڰ� �� �̻� ���� �޸𸮸� Ȯ���� �� ���� �ص� �ڱ� ����� �� �� �ٸ� new ó���ڸ� �˰� ���� �� �ִ�. 
		�� ��� ������ new ó���ڴ� �ٸ� new ó���ڸ� ��ġ�� ��  �ִ�.

		3. New ó������ ��ġ�� ���� - 
		set_new_handler �� �� �����͸� �ѱ��. New ó���ڰ� ��ġ�� ���� ������, 
		operator new�� �޸� �Ҵ��� ���� ���� �� ���ܸ� ������ �ȴ�.

		4. ���ܸ� ������  - 
		bad_alloc Ȥ�� bad_alloc ���� �Ļ��� Ÿ���� ���ܸ� ������. 
		���ܴ� �޸� �Ҵ��� ��û�� ������ ��ġ�� ���ĵȴ�.(propagate, ���ܸ� �ٽ� ������)

		5. �������� �ʴ´� - 
		�밳 abort Ȥ�� exit�� ȣ��
	*/
}

namespace Item49_2 {

	void outOfMem(void)
	{
		std::cerr << "Unable to satisfy request for memory\n";
		std::abort();
	}


	void func()
	{	
		//new ó���� ����
		std::set_new_handler(outOfMem);

		int *pBicDataArray = new int[499999999L];
		/*
			�޸� �Ҵ緮 �ʰ��� new ó���ڷ� ������ outOfMem�� ȣ��ȴ�
		*/
	}
}

namespace Item49_3 {

	class NewHandlerHolder
	{
	public:
		explicit NewHandlerHolder(std::new_handler p)
			: handler(p) { }

		~NewHandlerHolder() { std::set_new_handler(handler); }
	private:
		std::new_handler handler;

		//���� �� ���� ����
		NewHandlerHolder(const NewHandlerHolder&);	
		NewHandlerHolder& operator=(const NewHandlerHolder&);
	};

	class Widget
	{
	public:
		static std::new_handler set_new_handler(std::new_handler p)
		{
			std::new_handler old_new_handler = currentHandler;
			currentHandler = p;
			return old_new_handler;
		}

		void* operator new(std::size_t size) throw(std::bad_alloc())
		{
			NewHandlerHolder h(std::set_new_handler(currentHandler));
			
			return ::operator new(size);
			/*
				new ó���ڸ� �����ϸ鼭  NewHandlerHolder �ڿ� ���� ��ü�� ��´�.
				���� �Լ��� ������ NewHandlerHolder �� �Ҹ��ڰ� ȣ��Ǹ鼭, ������ new ó���ڷ� �����ȴ�.
			*/
		}
	private:
		int m_a[499999999L]; // <-- ���⼭ �޸� ����
		static std::new_handler currentHandler;
	};
	std::new_handler Widget::currentHandler = 0;

	/*
		Widget�� operator new �� ���� ���� �� ����

		1. ǥ�� set_new_handler �Լ��� Widget�� new ó���ڸ� �Ѱܼ� ȣ��.
		��, ���� new ó���ڷμ� Widget�� new ó���ڸ� ��ġ

		2. ���� operator new  �� ȣ���Ͽ� ���� �޸� �Ҵ� ����.
		���� ���⼭ �����ϸ�, �� �Լ��� Widget�� new ó���ڸ� ȣ��

		���������� ���� operator new �� �޸� �Ҵ��� �����ϸ�, bad_alloc ���ܸ� ������
		�� ��� widget�� operator new �� ���� new ó���ڸ� ������ ������ �������� ���ܸ� ���Ľ�Ų��

		3. ���� operator new �� widget ��ü �ϳ���ŭ�� �޸𸮸� �Ҵ��� �� ������,
		widget�� operator new �� �Ҵ�� �޸� ��ȯ

		���ÿ� ���� new ó���ڰ� �����ϴ� ��ü�� �Ҹ��ڰ� ȣ��Ǹ鼭
		widget�� operator new�� ȣ��Ǳ� ���� ���̰� �ִ� ���� new ó���ڰ� �ڵ� ����
	*/

	//widget Ȱ����
	void outOfMem(void)
	{
		std::cerr << "Unable to satisfy request for memory\n";
		std::abort();
	}

	void func() {
		//new ó���� ��ġ
		Widget::set_new_handler(outOfMem);

		//���⼭ �޸� �Ҵ��� �����ϸ� OutOfMem �� ȣ��
		Widget *pw1 = new Widget;

		//���⼭ �޸��Ҵ��� �����ϸ� ���� new ó���� �Լ� ȣ��
		std::string *ps = new std::string;

		//widget Ŭ������ new ó���ڸ� null�� ����
		Widget::set_new_handler(0);

		//�޸� �Ҵ��� �����ϸ� ������ �ٷ� ���ܸ� ������
		Widget *pw2 = new Widget;
	}
}

namespace Item49_4 {
	//�ڿ����� ��ü�� ���� �Ҵ翡�� ó���� �����ϴ� ����� � Ŭ������ �Ȱ��� ���� �� ����
	//�� �ڵ带 �ش� Ŭ���������� ������ �� �ֵ��� �ͽ���(mixin) ��� ���

	class NewHandlerHolder {
	public:
		explicit NewHandlerHolder(std::new_handler nh) :handler(nh) {} 
		~NewHandlerHolder()            
		{
			std::set_new_handler(handler);
		}
	private:
		std::new_handler handler;

		NewHandlerHolder(const NewHandlerHolder&); 
		NewHandlerHolder& operator=(const NewHandlerHolder&);
	};

	template<typename T>   //"mixin-style"
	class NewHandlerSupport {
	public:
		static std::new_handler set_new_handler(std::new_handler p) throw ();
		static void * operator new(std::size_t size) throw (std::bad_alloc);
	private:
		static std::new_handler currentHandler;
	};
	template<typename T>
	std::new_handler NewHandlerSupport<T>::currentHandler = 0;

	template<typename T>
	std::new_handler NewHandlerSupport<T>::set_new_handler(std::new_handler p) throw()
	{
		std::new_handler oldHandler = currentHandler;
		currentHandler = p;
		return oldHandler;
	}

	template<typename T>
	void* NewHandlerSupport<T>::operator new(std::size_t size)
		throw(std::bad_alloc)
	{
		NewHandlerHolder h(std::set_new_handler(currentHandler));
		return ::operator new(size); 
	}

	/*
		�ű��ϰ� �ݺ��Ǵ� ���ø� ����(curiously recurring template pattern : CRTP)
		: ���Ŭ������ ���ø� Ŭ�����ε� ���ø� �Ű������� �Ļ�Ŭ������ ���.
		�Ļ�Ŭ���� ������ ���� ���ø� �纻�� �������ִ� ������ �Ѵ�.

		�Ʒ��� Widget Ŭ������ ������ ������ �����ϳ�, NewHandlerSupport�� ��ӹް� �����Ƿ�
		set_new_handler, operator new �� ���� ������ �ʿ����.
	*/
	class Widget : public NewHandlerSupport<Widget> { };

	void func() {
		// ���н� bad_alloc ����
		Widget *pw1 = new Widget;            
		
		//�� if �� �˻�� �ݵ�� ���� 
		//new Widget�� ���� �� pw1 ���� �ּҰ��� �ְ�
		//���� �� bad_alloc ���ܰ� �������� new Widget�� �� �����͸� ��ȯ���� �ʴ´�
		if (pw1 == 0) {}                   
		
		//p�� �Ҵ��ϴ� �����ϸ� 0(��)�� ��ȯ�Ѵ�
		char* p = new (std::nothrow) char[1048576];

		//�� if�� �˻�� ������ �� �ִ�
		if (p == 0) {}
	}
}

namespace Item49_5 {
	//CRTP�� �����Ͽ�, �� ���� ���ܸ� ó���ϴ� ���
	template<typename T>
	class Base {};

	class Derived1 : public Base<Derived1> {};

	class Derived2 : public Base<Derived1> {};	//���⼭ ������ ������ ���� �ҷ���?



	template<typename T>
	class NBase {
	private:
		friend T; //T�� �Ļ�Ŭ������ �ƴ� �������� ������ ȣ�� ���ƹ�����
		NBase() {}
	};
}