#include <iostream>
#include <vector>
#include <string>
using namespace std;

//typename �� �� ���� �ǹ̸� ����� �ľ�����

namespace Item42 {

	int x = 1;

	template<typename C>
	void print(const C& container) {
		C::const_iterator * x;
		/*
			������ ������ �ٺ��� �ڵ�, C::const_iterator�� ���� ������ ���� �����μ� x�� �����ϴ� �� ������
			�����Ϸ� ���忡���� C::const_iterator�� Ÿ���� ���ϴ� ���� C�� const_iterator��� ���� �������� �� �� �� ����.

			���࿡ C::const_iterator�� ���� ������� �ش� ������ �� ������ ���� ������ �����϶�� �ǹ̸� ������
		*/
	}
	
	template<typename C>
	void print_2(const C& container) {
		if (container.size() >= 2) {
			typename C::const_iterator iter(container.begin());
			/*
				����� ������ �ڵ�. �����Ϸ����� C::const_iterator�� Ÿ������ �˷��ش�
			*/
		}
	}

	template<typename C>	//typename �� �� ����, class�� ���� �ǹ�
	void f(const C& container,	//typename ���̸� �ȵȴ�
		typename C::const_iterator iter);	//typename�� �ٿ��� �Ѵ�
	/*
		C::const_iterator ���� C�� ���ø� �Ű������̸�, const_iterator�� C�� ���ӵ� ���� �̸��̶� �� �� �ִ�.
		C ���� typename �� �ٿ��� �ȵǰ�, C�� �����ϴ� C::const_iterator �տ��� typename�� �ٿ��� �Ѵ�
	*/


	template<typename T>
	class Base {
	public:
		class Nested{
		public:
			Nested() {}
			Nested(int x) {}
		};
	};

	template<typename T>
	class Derived : public Base<T>::Nested {	//��ӵǴ� �⺻ Ŭ���� ����Ʈ, typename �� ���̸� �ȵȴ�
	public:
		explicit Derived(int x) : 
			Base<T>::Nested(x) {	//��� �ʱ�ȭ ����Ʈ�� �ִ� �⺻ Ŭ���� �ĺ���, typename�� ���� �ȵȴ�
			
			typename Base<T>::Nested temp;	//typename �ʿ�
		}
	};
	/*
		template �Ű������� �����ϸ鼭 typename Ű���带 ������ �ʴ� ���� ���
	*/

	template<typename IterT>
	void workWithIterator(IterT iter) {
		typedef typename std::iterator_traits<IterT>::value_type value_type;
		
		value_type temp(*iter);

		//�����Ϸ����� Ÿ�������� �˸��鼭 typedef Ű����� ��Ī�� ���� �� �ִ�.
	}

	/*
		���ø� �Ű������� ������ ��, class �� typename�� ���� �ٲپ� �ᵵ �����ϴ�.
		��ø ���� Ÿ�� �̸��� �ĺ��ϴ� �뵵���� �ݵ�� typename�� ����Ѵ�. 
		�� ��ø ���� �̸��� �⺻ Ŭ���� ����Ʈ�� �ְų� ��� �ʱ�ȭ ����Ʈ ���� �⺻ Ŭ���� �ĺ��ڷ� �ִ� ��쿡�� ����
	*/
}