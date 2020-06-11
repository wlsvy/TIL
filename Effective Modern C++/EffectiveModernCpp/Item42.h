#pragma once
#include <iostream>
#include <vector>
#include <string>
#include <array>
#include <set>
#include <list>
#include <regex>

//���� ��� ���� ������ ����϶�

namespace Item42 {
	using namespace std;

	class Widget {
	public:
		Widget() { std::cout << "default ctor" << std::endl; }
		Widget(int i) : val(i) { std::cout << "default ctor(int)" << std::endl; }
		Widget(const Widget& rhs) : val(rhs.val) { std::cout << "copy ctor" << std::endl; }
		Widget(Widget&& rhs) noexcept : val(rhs.val) { std::cout << "move ctor" << std::endl; }
		~Widget() { std::cout << "dtor" << std::endl; }
		Widget& operator= (const Widget & rhs) = default;
		int val = 0;
	};
	bool operator== (const Widget& lhs, const Widget& rhs) noexcept { return lhs.val == rhs.val; }
	bool operator< (const Widget& lhs, const Widget& rhs) noexcept { return lhs.val < rhs.val; }
	bool operator> (const Widget& lhs, const Widget& rhs) noexcept { return lhs.val > rhs.val; }

	/*
		���� ���� �Լ����� ���� �Լ����� �ϴ� ��� ���� �� �� �ִ�.
		�Դٰ� �� �� ȿ�������� ����� �� �ִ� ��찡 ������, ��� �̷������δ�, �� ȿ�������� ����Ǵ� ���� ���� ����.
	*/
	namespace Case0 {
		inline void RunSample() {
			std::vector<std::string> vs;

			vs.push_back("xyzzy");

			// ���ڿ� ���ͷ��� std::string�� Ÿ����
			// �ٸ��Ƿ�, push_back�� ȣ���ϴ� ������
			// ������ ���� �ؼ��ȴ�.

			vs.push_back(std::string("xyzzy"));

			// �� ��� �ӽ� std::string ��ü�� �����ǰ�
			// �� �ӽ� ��ü(������)�� std::vector ����
			// ���ڿ��� �̵��Ѵ�.

			// ������ emplace_back ��� �Լ���
			// ����ϸ� �� ȿ�������� ���� �� �ִ�.

			vs.emplace_back("xyzzy");

			// emplace_back�� �Ϻ� ������ �̿��ϹǷ�
			// ���ڿ� ���ͷ��� std::vector ����
			// std::string �����ڿ��� �״�� ���޵ȴ�.

			// ���� �ӽ� ��ü�� ������ �Ҹ� �����
			// ���� �ʴ´�.
		}
	}

	/*
		����������, ���� 
		
		(1) �߰��ϴ� ���� �����̳ʷ� ���ԵǴ� ���� �ƴ϶� �����ǰ�, 
		(2) �μ� Ÿ��(��)�� �����̳ʰ� ��� Ÿ�԰� �ٸ���, 
		(3) �� ���� �ߺ��� ���̾ �����̳ʰ� �ź����� �ʴ´ٸ�, 
		
		���� ���� �Լ��� ���� �Լ����� ���� ���ɼ��� ���� ũ��.
	*/

	//(1) �߰��� ���� �����̳ʿ� ���ԵǴ� ���� �ƴ϶� �����̳� �ȿ��� �����ȴ�
	namespace Case1 {
		inline void RunSample() {

			std::vector<std::string> vs;
			vs.emplace(vs.begin(), "xyzzy");	//���� ������ �߰��ϴ� ���
			
			std::vector<Widget> vec(3, Widget(3)); 
			vec.reserve(40); 
			//vec.push_back(Widget(1));		//��� push_back �� �ӽ� ��ü�� ����� �� ����. �ӽ� ��ü ����/�ı�, �̵� ���� 1ȸ
			//vec.push_back(Widget(2));
			cout << "========" << endl << endl;
			vec.emplace(vec.begin(), 3);	//�ӽ� ��ü ����/�ı�, �̵� ���� 1ȸ
			cout << "========" << endl << endl;
			vec.emplace_back(2);			//���� 1ȸ
			cout << "========" << endl << endl;


			/*
				�̷� ��쿡, ������ ��ü�� �����ϰ� �ִ� �޸� ��ҿ� 
				�� ��ü�� �����ϴ� ǥ�� ���̺귯�� ������ �幰��. ��� �������� �� ���� �ش� ��ҷ� �̵� �����Ѵ�.	

				�׷��� �̵� ������ �����Ϸ��� �̵��� ������ �ʿ��ϸ�, 
				���� �̵� ������ �� �ӽ� ��ü�� �����ؾ� �Ѵ�. 
				
				���Կ� ���� ���� ������ �ֵ� ������ �ӽ� ��ü�� ����, �ı��ϴ� ���� ���ٴ� ���̹Ƿ�, 
				��ó�� ���� ������ ���ؼ� �����̳� �ȿ� ���� ������ ���� ������ ������ ������� ������ �����.
			*/
		}

		/*
			��� ��� �����̳ʵ��� ���� �׻� ������ ���ؼ� �� ���� �߰��ϸ�, ǥ�� �����̳ʵ��� ��κ� ��� ����̴�. 
			��� ����� �ƴ� ǥ�� �����̳ʴ� std::vector�� std::deque, std::string ���̴�
			(std::array�� �ƴ�����, �� �����̳ʴ� ���԰� ���� ������ �� �� �������� �ʴ´�).

			��� ����� �ƴ� �����̳ʿ����� emplace_back�� �׻� ���� ��� ������ �̿��ؼ� �� ���� �����̳ʿ� �ִ´ٰ� �����ص� �����ϴ�. 
			�׸��� std::deque�� ��쿡�� emplace_front ���� ���������̴�.
		*/
	}

	//(2)�߰��� �μ� Ÿ��(��)�� �����̳ʰ� ��� Ÿ�԰� �ٸ���.
	/*
		�Ϲ������� ���Կ� ���� ���� ������ ������ 
		������ �������̽� ���п� ���޵� �μ� Ÿ�Ե��� �����̳ʰ� ��� Ÿ�԰� �޶� �ӽ� ��ü�� ������ �ı��� �Ͼ�� �ʴ´ٴ� ���̴�. 
		
		� �����̳�<T>�� T Ÿ���� ��ü�� �߰��� ������ ���� ������ ���Ժ��� ���� ������ ����. 
		
		�׷� ������ ���� �������̽������� �ӽ� ��ü�� ������ �ʿ䰡 ���� �����̴�.
	*/
	
	//(3)�����̳ʰ� ���� ������ �ߺ� ������ �� ���� �ź��� ����� ���� ����. 
	namespace Case2 {
		

		inline void RunSample() {
			set<Widget> s;

			cout << "Emplace =====================" << endl;
			s.emplace(1);
			s.emplace(2);
			s.emplace(3);
			s.emplace(1);	//�ߺ� ���� ���θ� Ȯ���ϱ� ���� �ӽ� ��ü ����/ �׸��� �ߺ��ȴٸ� �ı�
			cout << "Clear =====================" << endl;
			s.clear();


			cout << "Create Object =====================" << endl;
			Widget w1(1);
			Widget w2(2);
			Widget w3(3);
			Widget w4(1);

			cout << "Insert =====================" << endl;
			s.insert(w1);
			s.insert(w2);
			s.insert(w3);
			s.insert(w4); //Insert�� ��� �ߺ� ���� Ȯ���� ���� �ӽ� ��ü�� �������� �ʴ´�.
			cout << "Clear =====================" << endl;
			s.clear();
		}
		/*
		�̴� �����̳ʰ� �ߺ��� ����ϰų�, �Ǵ� �߰��� ������ ��κ� ������ ��쿡 �ش��Ѵ�.
		�� ������ �߿��� ������, �ߺ� ������ �ִ� ��� �Ϲ������� ���� ���� ������ �� ������ ��带 �����ؼ� �װ��� ���� �����̳� ����� ���Ѵٴ� ���̴�.

		���� �߰��� ���� �����̳ʿ� ������ �� ��带 �����̳ʿ� �����Ѵ�(link). �׷��� ���� �̹� ������ ���� ������ ��ҵǰ� �� ��尡 �ı��ȴ�.
		���� ������ �ı� ����� ����ǰ� ����. �̷� ������ ���� �Լ����� ���� ���� �Լ����� �� ���� �����ȴ�.

		Ex) set�� �����ϸ� �ȴ�. set�� �ߺ� ���Ҹ� ������� ������, emplace�� �ߺ��Ǵ� ���� �����Ϸ� �� �� ���� ������ �ӽ� ��ü�� ���� �� �ı��Ѵ�.
	*/
	}
	

	/*
		�ڿ� ���� ��ü�� �����̳ʿ� �߰��Ѵٸ�, 
		�׸��� �ڿ� ȹ��� �� �ڿ��� �ڿ� ���� ��ü�� ��ȯ�ϴ� ���� ���̿� �ƹ��͵� ������� ���ϰ� �϶�� ����(�׸� 21 ����)�� ����� �����ٸ�, 
		���� ������ ���� �Լ����� �� ���� ������ ���� ���ɼ��� ���� ����.
	*/
	namespace Case3 {
		auto killWidget = [](Widget* pWidget) 
		{
			cout << "Delete With CustomDeleter" << endl;
			delete pWidget;
		};

		inline void RunSample() {
			std::list<std::shared_ptr<Widget>> ptrs;


			//��ü ���� ��� �� ���� 
			ptrs.push_back(std::shared_ptr<Widget>(new Widget(0), killWidget));
			ptrs.push_back({ new Widget, killWidget });

			/*
				1. �� ȣ�� ���, "new Widget"���� ������� �� �����͸� ��� �ӽ� std::shared_ptr<Widget> ��ü�� �����ȴ�.

				 2. push_back�� �� �ӽ� ��ü�� ������ �޴´�.
				 ���纻�� ���� ����Ʈ ��带 �Ҵ��ϴ� ���߿� �޸� ����(out-of-memory) ���ܰ� �߻��Ѵ�.

				 3. ���ܰ� push_back �ٱ����� ���ĵǸ鼭 �ӽ� ��ü�� �����ϰ� �ı��ȴ�. �Ҵ��� �޸𸮵� �����ϰ� ��ȯ�ȴ�.

				 ��������
			*/

			//��ü ���� ����
			ptrs.push_back({ new Widget, killWidget });
			/*
				1. "new Widget"���� ������� �� �����Ͱ� emplace_back���� �Ϻ� ���޵ȴ�.
				emplace_back�� �� ���� ���� ����Ʈ ��带 �Ҵ��Ѵ�.

				2. ����Ʈ ��带 ���� �� �޸� ����(out-of-memory) ���ܰ� �߻��Ѵ�.

				3. ���ܰ� emplace_back ������ ���ĵǸ鼭, ���� �ִ� Widget ��ü�� �����ϴ� ������ ������ �� �����Ͱ� �������.

				 �ڿ� ����
			*/

			/*
				�Ʒ��� ����� �����ϴ�.
			*/
			std::shared_ptr<Widget> spw(new Widget, killWidget); 
			ptrs.push_back(std::move(spw));
			//or
			ptrs.emplace_back(std::move(spw));
		}
	}

	
	/*
		�ʱ�ȭ ����� �� ������ �ִ�. �ϳ��� ���� �ʱ�ȭ(copy initialization)�̰�, �ٸ� �ϳ��� ���� �ʱ�ȭ(direct initialization)�̴�.

		explicit �����ڿ����� ���� �ʱ�ȭ�� ����� �� ������ ���� �ʱ�ȭ�� ����� �� �ִ�. 
		std::regex��, const char* Ÿ���� �μ��� �ް� explicit���� ����� �����ڸ� �����Ѵ�.

		���� ���� �Լ��� �ٷ� ���� Ȥ�� �� ������ �����ϱ� ���� �Ű������� �ѱ� �� �Ű澵 ��.
	*/
	//�ʱ�ȭ ��Ŀ� ���� ����
	namespace Case4 {
		inline void RunSample() {
			//std::regex r1 = nullptr;
			// ���� �ʱ�ȭ; ����! ������ �� ��

			std::regex r2(nullptr);
			// ���� �ʱ�ȭ; �����ϵ�



			//���� ������ �ڵ�� �Ѵ� ���͸����� ���� ���� �Լ��� ������ ������ ���� �ʴ´�.

			std::vector<std::regex> regexes;

			regexes.emplace_back(nullptr);
			// �����ϵ�; ���� �ʱ�ȭ������ �����͸� �޴�, explicit����
			// ����� std::regex �����ڸ� ����� �� �ִ�.

			//regexes.push_back(nullptr);
			// ����! ���� �ʱ�ȭ������  �׷� �����ڸ� ����� �� ����.

		}
	}
}