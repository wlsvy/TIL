#pragma once
#include <iostream>
#include <vector>
#include <list>
#include <algorithm>
#include <map>
#include <string>
#include <array>
#include <set>
#include <memory>

//map::operator[]�� map::insert�� ȿ�� ������ �����Ͽ� ��������

namespace Item24 {
	using namespace std;
	/*
		c++ 11�� move semantic�� ���ԵǱ� ������ �������� �����սô�.
		C++ 11���� map�� emplace/emplace_hint ����� �߰��Ǿ����ϴ�. insert�� �޸� ���Խ� �ӽð�ü�� �������� �ʽ��ϴ�.
		c++ 17���� insert_or_assign ����� �߰��Ǿ����ϴ�.

		å�� ���� ���ķ� map�� ����� ����ȭ �� �� �����ϴ�. �̹� �׸��� ������ ���� �´ٰ� ���� ��ƽ��ϴ�.
	*/

	class Widget {
	public:
		Widget()						{ std::cout << "default ctor" << std::endl; }
		Widget(double)					{ std::cout << "double ctor" << std::endl; }
		~Widget()						{ std::cout << "dtor" << std::endl; }

		Widget(const Widget& rhs)		{ std::cout << "copy ctor" << std::endl; }
		Widget(Widget&& rhs) noexcept	{ std::cout << "move ctor" << std::endl; }
		//Widget(const Widget& rhs) = delete;
		//Widget(Widget&& rhs) noexcept = delete;

		Widget& operator=(double) {
			std::cout << "double operator =" << std::endl;
			return *this;
		}
		Widget& operator=(Widget&& rhs) noexcept {
			std::cout << "move operator =" << std::endl;
			return *this;
		}
	};

	/*
		�ʿ� ���ο� ��Ҹ� "�߰�"�� ��쿡�� operator[]���� insert�� ȿ�������� �����ϴ�.
		(����� ���� �׷��ٰ� ���� ��ƽ��ϴ�.)
	*/
	inline void AddElement() {
		map<int, Widget> m;
		/*
			������ ǥ����
			m[k] = v;

			�� �켱 �ش� �ʿ� Ű k�� ��� �ִ��� �����մϴ�. 
			�׷��� �ʴٸ� k�� v�� ���� ������ �ʿ� ���� '�߰�'�˴ϴ�. 
			k�� �ʿ� ��� �ִ� ��쿡�� k�� ����(����)�� ��(value)�� v�� ���ŵ˴ϴ�.

			���࿡ �����̳� �ȿ� �ش� Ű�� �����ϴ� pair���� ���ٰ� �غ��ô�.
			operator[]�� �ش� map�� ������ �� Ÿ��(value_type)�� �⺻ �����ڸ� ����Ͽ� pair ��ü�� ���� �����, �� ��ü�� �����ڸ� ��ȯ�մϴ�. 
			���������, ��ȯ�� Widget ��ü�� �����ڸ� ���� operator=������ �Լ��� ȣ��Ǿ� Widget ��ü�� ���� ���Ե˴ϴ�.

			�Ʒ��� ��� operator[]�� ȣ���� �� ���ο� pair�� ����� �⺻ �����ڰ� ȣ��ǰ�, �� ���� double �� 1.50�� ���� ���Կ����ڰ� ȣ��˴ϴ�.
			�⺻ ������ -> double ���� ������
			(copy elision�� ����Ǹ鼭 �� �߰� ������ �ξ� ����ȭ �� �� �����ϴ�.)
		*/
		cout << "============ operator[] =================" << endl;
		m[1] = 1.50;

		/*
			å������ insert�� Ȱ���ϴ� ���� �Լ� ȣ�� ����� ũ�� ���� �� �ִٰ� ����Ǿ� �ְ� operator[]�� �ӽð�ü�� �����ϴ� ���� �� ������� �����մϴ�.
			
			���� �����غ��� operator[]�� �ӽ� ��ü�� ���� �������� ������ ������ insertȣ���� �ӽð�ü�� �����մϴ�.

			�Ʒ��� ��� ������ Widget�ȿ� �̵������ڰ� �����Ǿ� ������
			double ������(�ӽð�ü) -> �̵� ������ -> �Ҹ���(�ӽð�ü) ������ ȣ��Ǹ�

			�̵������ڰ� �����Ǿ� ���� �ʴٸ�
			double ������(�ӽð�ü) -> ���� ������ -> �Ҹ���(�ӽð�ü) ������ ȣ��˴ϴ�.

			insert�� �� ȿ�����̶�� ���� ��ƽ��ϴ�. 
		*/
		cout << "============ Insert =================" << endl;
		m.insert({ 2, 3.0 });

		
		//C++ 11���� map�� emplace / emplace_hint ����� �߰��Ǿ����ϴ�.insert�� �޸� ���Խ� �ӽð�ü�� �������� �ʽ��ϴ�.
		//double �����ڸ� �� �ѹ� ȣ���մϴ�.
		cout << "============ emplace =================" << endl;
		m.emplace(make_pair( 3, 3.0 ));

		cout << "============ Function End =================" << endl;
	}

	/*
		�ݸ鿡, �ʿ� ����� ��ҿ� ���� "����"�� �� ��쿡�� insert���� operator[]�� ȿ�������γ� ��(ڸ)�����γ� �����ϴ�.
	*/
	inline void UpdateElement() {
		map<int, int> m;
		m[1] = 10;
		m[2] = 10;

		// operator[]�� ���� 1�� ���ε� ���� 11�� �����մϴ�.
		m[1] = 11;
		
		//insert�� ���� 2�� ���ε� ���� 11�� �����մϴ�. �ӽð�ü�� �����ϴ� ����� �����ؾ� �մϴ�.
		auto iter = m.insert(map<int, int>::value_type(2, 9));	
		iter.first->second = 11;
	}

	template <typename MapType, typename _Key, typename _Value>  
	decltype(auto) efficientAddOrUpdate(MapType& m, const _Key& k, const _Value& v)
	{
		// k�� ��ġ Ȥ�� ���� ��ġ�� ã���ϴ�. lower_bound �� �׸� 45 ����
		auto lb = m.lower_bound(k);          

		//���� �����մϴ�. 
		//lower_bound�� �� ���� ������ ������ ȣ���� �˰����̱� ������ ������ ���ϴ� Ű ���� ã�Ҵ��� üũ�ϴ� ������ �ѹ� �� �ʿ��մϴ�.(��� �˻� ����)
		if (lb != m.end() &&                 
			!(m.key_comp()(k, lb->first))) { 
			lb->second = v;                  
			return lb;                       
		}                                    
		else {
			//lb�� ����Ű�� ��ġ�� pair(k, v)�� �����մϴ�. 
			//insert���� �̸� ��ġ�� �������شٸ� �α� �ð��� �ƴ� ��� �ð��� ���� ������ �����մϴ�.
			
			//return m.insert(lb, {k, v});        

			//c++ 11���� emplace_hint�� �߰��Ǿ����ϴ�. ���� ȿ�������� ���� ������ �����մϴ�.
			return m.emplace_hint(lb, k, v);
		}                                       
	}

	inline void AddOrUpdate() {
		map<int, Widget> m;
		cout << "============ efficientAddOrUpdate =================" << endl;
		cout << "============ Add =================" << endl;

		efficientAddOrUpdate(m, 1, 0.5);

		cout << "============ Update =================" << endl;

		efficientAddOrUpdate(m, 1, 1.5);

		cout << "============ Function End =================" << endl;
	}

	inline void RunSample() {
		AddElement();
		UpdateElement();
		AddOrUpdate();
	}
}
