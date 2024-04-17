#include <iostream>
#include <vector>
#include <string>
using namespace std;

//��ġ���� new�� �ۼ��Ѵٸ� ��ġ���� delete�� ���� �غ�����

namespace Item52 {

	namespace StandardCase {
		class Widget{};

		inline void RunSample() {
			/*
				�� ��� ���� operator new �Լ��� �޸𸮸� �Ҵ��� �� Widget�� �����ڰ� ȣ��˴ϴ�.

				�׷��� Widget�� �����ڿ��� ���ܰ� �߻��� ��� ���α׷��Ӵ� �޸� ������ �ذ��� �� �����ϴ�.

				���� �Ҵ� ���� �޸��� ���� �ּҰ� pw�� ���⵵ ���� ���ܰ� �������� ��������.
				�� ��� �޸��� ������ C++ ��Ÿ�� �ý��۲��� ���� �ֽð� �˴ϴ�.

				������ C++ ��Ÿ�� �ý����� �˾Ƽ� �޸𸮸� �����Ϸ��� new�� ¦�� �´� delete�� �˾ƾ� �մϴ�.
			*/
			Widget *pw = new Widget;
			delete pw;
		}
	}

	/*
		�Ϲ����� ��� �̰��� ū ������ ���� �ʽ��ϴ�. �ֳ��ϸ� �⺻�� operator new��
		���� �⺻�� operator delete�� ¦�� ���߱� �����Դϴ�.

		void* operator new(std::size_t) throw(std::bad_alloc);

		//���� ��ȿ���������� �⺻�� �ñ׳�ó
		void operator delete(void *rawMemory) throw();

		//Ŭ���� ��ȿ���������� �������� �⺻�� �ñ׳�ó
		void operator delete(void *rawMemory, std::size_t size) throw();
	*/
	
		
					
	/*
		���� ǥ�� ������ new �� delete�� ����ϴ� ��, ��Ÿ�� �ý����� new�� ������ �ǵ��� ����� �˰� �ִ� delete�� �������� ã�Ƴ� �� �ֽ��ϴ�.
		������ operator new�� �⺻���� �ƴ� ���¸� �����ϱ� �����ϸ� new�� delete¦�� ���ߴ� �� ������ �ǼۻǼ� �Ǿ�� �˴ϴ�.

		��⺻���̶� �ٷ� �ٸ� �Ű������� �߰��� ���� operator new�� ���մϴ�.
		(�̷� operator new�� ��ġ���� (placement) new ��� �մϴ�.)

		�޸� �Ҵ��� ���������� �����ڿ��� ���ܰ� �߻��ϴ� ���, �޸� �Ҵ��� �ǵ����� ���� c++ ��Ÿ�� �ý����� å���Դϴ�. 
		�׷��� ��Ÿ�� �ý��� �ʿ����� ȣ��� operator new �� ��� �����ϴ����� �˾Ƴ� ����� �����Ƿ� �Ҵ� ��ü�� �ǵ��� ����� �����ϴ�.
		��� ��Ÿ�� �ý����� operator new�� �޾Ƶ��̴� �Ű������� ���� �� Ÿ���� �Ȱ��� operator delete�� ã��, ã�Ƴ����� �� �༮�� ȣ���մϴ�.

		���� ���࿡ ��ġ���� new�� ����� �� ��, �׿� �����ϴ� ��ġ���� delete�� ����� ���� �ʴ´ٸ�, 
		��Ÿ�� �ý����� ���� ��Ȳ�� ��� ��ó�ؾ� �ϴ��� ���� �ƹ��͵� ���� �ʽ��ϴ�.
	*/

	namespace BadCase {

		class Widget {
		public:
			// ��ǥ�� ������ operator new
			static void* operator new(std::size_t size, std::ostream& logStream) throw(std::bad_alloc) {}

			// Ŭ���� ���� operator delete�� ǥ�� ����
			static void operator delete(void *pMemory, size_t size) throw() {}
		};

		inline void RunSample() {
			/*
				operator new�� ȣ���ϸ� cerr�� ostream ���ڷ� �ѱ�µ�, �̶� Widget �����ڿ��� ���ܰ� �߻��ϸ� �޸𸮰� ����˴ϴ�.
			*/
			Widget *pw = new(std::cerr) Widget;
		}
	}
										
	/*
		������ ȣ��� new�� ostream& Ÿ���� �Ű������� �߰��� �޾Ƶ��̹Ƿ�, 
		�̰Ͱ� ¦�� �̷�� operator delete ���� �Ȱ��� �ñ׳�ó�� ���� ���� ���õǾ� �־�� �մϴ�.

		void operator delete(void *, std::ostream&) throw();
	*/

	namespace GoodCase {
		/*
			�̷��� operator delete�� ��ġ���� delete��� �մϴ�.
			���� �������� ��ġ���� delete�� �߰��� �ָ� �޸� ���� ������ ������ϴ�.
		*/
		class Widget {
		public:
			static void* operator new(std::size_t size, std::ostream& logStream) throw(std::bad_alloc) {}

			static void operator delete(void *pMemory) throw() {}
			static void operator delete(void *pMemory, std::ostream& logStream) throw() {}

		};

		inline void RunSample() {


			//������ ���� �ڵ������� �޸� ������ �����ϴ�.
			Widget *pw = new(std::cerr) Widget;

			// �⺻���� operator delete�� ȣ��˴ϴ�.
			delete pw;

			// �Ϲ����� ��쿡�� ��ġ���� delete ��� �⺻���� operator delete �� ȣ��˴ϴ�.
		}
	}

	//new �� delete�� ��ġ���� ������ ������ ����, �ǵ��� �ٵ� �ƴѵ� �̵��� ǥ�� ������ �������� ���� ������ �ʵ��� ������ �ּ���.
	namespace DerivedClassCase {

		class Base {
		public:
			//�� new�� ǥ�� ������ ���� new�� �����ϴ�.
			static void* operator new(std::size_t size, std::ostream& logStream) throw(std::bad_alloc) {}
		};

		inline void RunSample() {
			// ����! ǥ�� ������ ���� operator new�� �������ŵ��.
			//Base *pb = new Base;               

			//�̰� ���������ϴ�. Base�� ��ġ���� new�� ȣ���մϴ�.
			Base *pb = new(std::cerr) Base;

			// �Ļ� Ŭ������ ���� operator new�� �����̰� �ڽ��� ��ӹ޴� �⺻ Ŭ������ operator new���� ���� �����ϴ�.

			// ���� Base�κ��� ��ӹ��� Ŭ����
			class Derived : public Base {
			public:
				//�⺻�� new�� Ŭ���� �������� �ٽ� �����մϴ�.
				static void* operator new(std::size_t size) throw(std::bad_alloc) {}
			};

			// ����! Base�� ��ġ���� new�� ������ �ֱ� �����Դϴ�.
			//Derived *pd = new(std::cerr) Derived;    

			// ���������ϴ�. Derived�� operator new�� ȣ���մϴ�.
			Derived *pd = new Derived;
		}

		/*
			C++�� ���� ��ȿ �������� �����ϴ� operator new�� ���´� ���� �� ������ ǥ���Դϴ�.

			// �⺻�� new
			void* operator new(std::size_t) throw(std::bad_alloc);
			// ��ġ���� new
			void* operator new(std::size_t, void*) throw();
			// ���ܺҰ� new (�׸� 49 ����)
			void* operator new(std::size_t, const std::nothrow_t&) throw();
		*/


		/*
			� ���µ� ���� operator new�� Ŭ���� �ȿ� ����Ǵ� ����, ���� ����ó�� ���� ǥ�� ���µ��� ���� �������� ���Դϴ�.

			������ ���� �� ���� �ذ�å�� �ֽ��ϴ�. �⺻ Ŭ���� �ϳ��� �����, �� �ȿ� new �� delete�� �⺻ ���¸� ���� �־�νʽÿ�.
		*/
		class StandardNewDeleteForms {
		public:
			// �⺻�� new/delete
			static void* operator new(std::size_t size) throw(std::bad_alloc)
			{
				return ::operator new(size);
			}
			static void operator delete(void *pMemory) throw()
			{
				::operator delete(pMemory);
			}

			// ��ġ���� new/delete
			static void* operator new(std::size_t size, void *ptr) throw()
			{
				return ::operator new(size, ptr);
			}
			static void operator delete(void *pMemory, void *ptr) throw()
			{
				::operator delete(pMemory, ptr);
			}

			// ���ܺҰ� new/delete
			static void* operator new(std::size_t size, const std::nothrow_t& nt) throw()
			{
				return ::operator new(size, nt);
			}
			static void operator delete(void *pMemory, const std::nothrow_t&) throw()
			{
				::operator delete(pMemory);
			}
		};

		/*
			ǥ�� ���¿� ���ٿ� ����� ���� ���¸� �߰��ϰ� �ʹٸ�, ������ �� �⺻ Ŭ������ ������ ���� ���� �˴ϴ�.

			��Ӱ� using ������ 2�� �޺��� ����ؼ� ǥ�� ���¸� �Ļ� Ŭ���� ������ ����� �ܺο��� ����� �� �ְ� ���� �Ŀ�, ���ϴ� ����� ���� ���¸� ������ �ּ���.
		*/
		class Widget : public StandardNewDeleteForms {
		public:
			// ǥ�� ���°� (Widget ���ο�) ���̵��� ����ϴ�.
			using StandardNewDeleteForms::operator new;
			using StandardNewDeleteForms::operator delete;

			// ����� ���� ��ġ����  new�� �߰��մϴ�.
			static void* operator new(std::size_t size, std::ostream& logStream) throw(std::bad_alloc) {}

			// ���� �Ͱ� ¦�� �Ǵ� ��ġ ���� delete�� �߰��մϴ�.
			static void operator delete(void *pMemory, std::ostream& logStream) throw() {}
		};
	}
	
}