#include <iostream>
#include <vector>
#include <string>
using namespace std;

//Ÿ�Կ� ���� ������ �ʿ��ϴٸ� Ư������ Ŭ������ �������

namespace Item47 {

	//C++ ǥ�� ���̺귯������ �ݺ��� ���� ������ �ĺ��ϴµ� ���̴� "tag �±� ����ü" �� ���ǵǾ� �ִ�
	struct input_iterator_tag{};
	struct output_iterator_tag{};
	struct forward_iterator_tag : public input_iterator_tag {};
	struct bidirectional_iterator_tag : public forward_iterator_tag {};
	struct random_access_iterator_tag : public bidirectional_iterator_tag {};

	//���� �ݺ��ڸ� ������Ű�� �� ���, �ݺ����� Ư���� ���� �ٸ� ������� �����ؾ� �Ѵ�
	
	//stl �����̳��� ������ ����
	template<typename T>
	class deaue {
	public:
		class iterator {
		public:
			typedef random_access_iterator_tag iterator_category; //�ݺ��� �±׸� iterator_category �� ��Ī���� �Ű� ���´�
		};
	};

	template<typename T>
	class list {
	public:
		class iterator {
		public:
			typedef bidirectional_iterator_tag iterator_category; 
		};
	};

	//�Ʒ� ����ü�� ���ø� �Ű������� ���� Ŭ������ �±� Ÿ���� �����ش�
	template<typename IterT>
	struct iterator_traits {
		typedef typename IterT::iterator_category iterator_category;
	};
	//�ݺ����� ���� Ÿ���� �������� ���, �׿� �ش��ϴ� ó���� ���� �ʿ��ϴ�
	//�κ� ���ø� Ư��ȭ
	template<typename IterT>
	struct iterator_traits<IterT*> {
		//���� ���� �ݺ��ڿ� Ȱ�� -> �������� ���ۿ����� �������� �ݺ��ڿ� �Ȱ��� ����
		typedef typename random_access_iterator_tag iterator_category;	
	};

	template<typename IterT, typename DistT>
	void tempAdvance(IterT &iter, DistT d) {
		//���� ���� ���. Ư�������� ������ �ð��� �� �� �ִµ� ���� ��Ÿ�� �ð��� Ȯ���� ������ �ִ�.
		if (typeid(typename std::iterator_traits<IterT>::iterator_category) == typeid(std::random_access_iterator_tag))
			;
	}

	//�����ε��� Ȱ���� ���
	template<typename IterT, typename DistT>
	void doAdvance(IterT& iter, DistT d,
		random_access_iterator_tag)
	{
		iter += d;
	}
	template<typename IterT, typename DistT>
	void doAdvance(IterT& iter, DistT d,
		bidirectional_iterator_tag)
	{
		if (d >= 0) { while (d--) ++iter; }
		else { while (d++) --iter; }
	}

	template<typename IterT, typename DistT>
	void doAdvance(IterT& iter, DistT d,
		input_iterator_tag)
	{
		if (d < 0) {
			throw std::out_of_range("Negative distance");
		}
		while (d--) ++iter;
	}
	template<typename IterT, typename DistT>
	void advance(IterT& iter, DistT d)
	{
		doAdvance(iter, d,
			typename iterator_traits<IterT>::iterator_category());
	};
	/*
		�۾���(worker) ������ ���� �Լ� Ȥ�� �Լ� ���ø��� Ư������ �Ű������� �ٸ��� �Ͽ� �����ε�

		���۾���(master) ������ ���� �Լ� Ȥ�� �Լ� ���ø��� 
		Ư������ Ŭ�������� �����Ǵ� ������ �Ѱܼ� �۾��ڸ� ȣ���ϵ��� ����
	*/
}