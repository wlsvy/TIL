#include <iostream>
#include <vector>
#include <string>

//��ü�� ����ϱ� ���� �ݵ�� �� ��ü�� �ʱ�ȭ ���� 
namespace Item04 {

	/*
		C++ ������ ��ü �ʱ�ȭ���� ��Ģ�� �� ���� �ִ�. 
		1. � �����Ϸ��� �����ϰ�, �⺻ Ŭ������ �Ļ� Ŭ�������� ���� �ʱ�ȭ
		2. Ŭ���� ������ ����� �׵��� ����� ������� �ʱ�ȭ(�Ʒ� Widget������ theName�� ���� ���� �ʱ�ȭ)
	*/

	class Widget {
	public:
		//�⺻���� Ÿ���� ��ü�� ���� ������ �ʱ�ȭ�մϴ�. ��쿡 ���� ������ �Ǳ⵵ �ϰ� �� �Ǳ⵵ �ϱ� �����Դϴ�.
		//���� �ʱ�ȭ ����
		int x = 0;	
		const char * text = "A C-style string";

		void DoSomething() {
			double d;
			std::cin >> d;	//�Է� ��Ʈ������ �����鼭 �ʱ�ȭ
		}

		/*
			�����ڿ�����, ������ ����� ���� ���Թ��� ������ ���� ���ο� �ִ� ������� ����� �ʱ�ȭ���� ���� ��� �ʱ�ȭ ����Ʈ�� ��� ����սô�. 
			�׸��� �ʱ�ȭ ����Ʈ�� ������ ����� ������ ���� Ŭ������ �� ������ ����� ����� ������ �Ȱ��� �����սô�.
		*/

		Widget(int val, bool) {
			/*
				�� ������ �ʱ�ȭ�� �ƴ϶� �����̴�.
				��Ȯ���� �ʱ�ȭ�� �̷���� ������ ���� ���Խ�Ű�� ��
			*/
			x = val;
					
		}

		//����� �� �ʱ�ȭ
		Widget(int val) : x(val) {}	

		//����� �� �ʱ�ȭ
		Widget() :			
			theName(),		
			theAddress(),	
			Numbers(),		
			numTimesConsulted(0)	
		{}

	private:
		std::string theName;
		std::string theAddress;
		std::vector<int> Numbers;
		int numTimesConsulted;
	};


	/*
		������ü(static object) �� �ڽ��� ������ �������� ���α׷��� ���� ������ ��� �ִ� ��ü�� ���´´�.(�� ���� �� �� ��� ��ü�� ���� ��ü�� �� �� ����)
		
		���� ��ü�� ���ֿ� ���� �͵��� 
		1. ���� ��ü, 
		2. ���ӽ����̽� ��ȿ�������� ���ǵ� ��ü, 
		3. Ŭ���� �ȿ��� static ���� ����� ��ü, 
		4. �Լ� �ȿ��� static ���� ����� ��ü, 
		5. �׸��� ���� ��ȿ�������� static ���� ���ǵ� ��ü.

		�̵� �� �Լ� �ȿ� �ִ� ���� ��ü�� ���� ���� ��ü(local static object) -> �Լ��� ���� �������� ������.
		�������� ������ ���� ��ü(non-local static object) ��� �Ѵ�.
		
		���� ��ü�� main() �Լ��� ���� ����ǰ� ���α׷��� ���� �� �Ҹ��ڰ� ȣ��ȴ�.
	*/


	namespace BadCase {
		//Ư�� ���̺귯���� ���Ե� Ŭ������ ��������.
		class FileSystem {
		public:
			std::size_t numDisks() const { return 0; }

		};

		//����ڰ� ���� �� ��ü
		FileSystem tfs;

		//���̺귯���� Ȱ���ϴ� ����ڰ� ���� Ŭ������ ��������.
		class Directory {
		public:
			Directory() {
				/*
					tfs ��ü�� ���⼭ ����Ѵ�.
					������, tfs �� ����� ������ tfs �� �ʱ�ȭ���� �ʾ��� �� �ִ�.
					�ٸ� ���� ������ ���ǵ� ������ ���� ��ü.
				*/
				std::size_t disks = tfs.numDisks();
			}
		};
	}

	//���� ���� ������ �ִ� ������ ���� ��ü���� �ʱ�ȭ ���� ������ ���ؼ� �����ؾ� �մϴ�. ������ ���� ��ü�� ���� ���� ��ü�� �ٲٸ� �˴ϴ�.
	namespace SolutionCase {
		class FileSystem {
		public:
			std::size_t numDisks() const { return 0; }

		};

		//�ذ�å���� �̱��� ������ Ȱ���մϴ�.
		FileSystem& tfs() {
			/*
				���� ���� ��ü�� �����ϰ� �ʱ�ȭ �� �� �����ڸ� ��ȯ�մϴ�.

				���� ���� ��ü�� �Լ��� ó�� �Ҹ� �� �ݵ�� �ʱ�ȭ �˴ϴ�.
			*/
			static FileSystem fs;
			return fs;
		}

		class Directory {
		public:
			Directory() {
				std::size_t disks = tfs().numDisks();
			}
		};

		Directory& tempDir() {
			static Directory td = Directory();
			return td;
		}
	}
}

