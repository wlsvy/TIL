#pragma once
#include <iostream>
#include <vector>
#include <list>
#include <algorithm>
#include <map>
#include <string>
#include <array>

//new�� ������ �������� �����̳ʸ� ����� ������ �����̳ʰ� �Ҹ�Ǳ� ���� �����͸� delete�ϴ� ���� ���� ����

namespace Item07 {
	using namespace std;

	//c++11 ����Ʈ �����Ͱ� �Ұ��Ǳ� ������ ����
	/*
		�����̳ʴ� �ڽ��� �Ҹ�� �� �� ��� ��ü�� ���� �ֱ�� �մϴ�. 
		������ ����� Ÿ���� �������� ��쿣 �������� �Ҹ��ڰ� �ƹ��� �ϵ� ���� �ʱ� ������, 
		new�� �����Ҵ��� ��ü�� �����͸� ��� �����̳ʰ� �Ҹ�� ���� �� ��Ҹ� delete �� ���� ������ �޸� ������ �Ͼ�ϴ�.
	*/

	class Widget{};

	namespace BadCase {
		inline void RunSample() {
			static unsigned int SOME_MAGIC_NUMBER = 100;

			{
				vector<Widget*> vwp;
				for (int i = 0; i < SOME_MAGIC_NUMBER; ++i)
				{
					vwp.push_back(new Widget);
				}
			}// Widget�� ���⼭ ���ϴ�!!

			{
				vector<Widget*> vwp;
				for (auto i = vwp.begin(); i != vwp.end(); ++i) {
					delete *i;
				}

				// �� �ڵ�� ���������� ������ ������ ���� �ֽ��ϴ�.
				/*
					�� ���� ������ for_each�� �ϴ� ���� for ������ ����ϰ� �ִµ�, �̰��� for_each ��ŭ ��Ȯ���� ���ϴ�(�׸� 43�� ����)�� ���Դϴ�.

					�� �� ������ ������ �� �ڵ�� ���� ������(exception safety)�� ���߰� ���� �ʴٴ� ���Դϴ�.
					delete�� �����ϴ� for�� ������ ���ܰ� �߻��ϸ�, �ҽ��� �޸𸮴� �ٽ� ���ϴ�.
				*/
			}
		}
	}

	namespace UsingFunctionObject {
		template<typename T>
		struct DeleteObject : public unary_function<const T*, void> {
			void operator()(const T* ptr) const {
				delete ptr;
			}
		};
		//unary_function�� �׸� 40���� ����

		struct DeleteObject2 {

			// ���ø��� ���⼭ ����˴ϴ�.
			template<typename T>
			void operator()(const T* ptr) const {
				delete ptr;
			}
		};

		inline void RunSample() {
			{
				vector<Widget*> vwp;
				for_each(vwp.begin(), vwp.end(), DeleteObject<Widget>());

				/*
					���⼭�� DeleteObject�� �����Ϸ��� �ϴ� ��ü�� Ÿ���� ���� ������ �־�� �մϴ�.
					�̴� ������ ���� ���׸� ����ų �� �ֽ��ϴ�.
					-> ���� �Ҹ��ڸ� �������� ���� ��ü�� ���ؼ� ��� Ŭ���� �����ͷ� delete�ϴ� ���(���� ��� string�� ����� Ŭ����)
				*/
			}
			{
				vector<Widget*> vwp;
				for_each(vwp.begin(), vwp.end(), DeleteObject2());
				/*
					���� ������ ��� �����մϴ�!
					
					������ ���� �������� ���ٴ� ���� ������ ������ ���� �ֽ��ϴ�.
					for_each�� ȣ��Ǳ� ���� ������ �߻��Ѵٸ� �ڿ��� �״�� �����Ǿ�����ϴ�.
				*/
			}
			
		}

		/*
			���� �������� ���ߴ� ���� ������ ����� �Ƹ���, �������� �����̳� ��ſ� ����Ʈ �������� �����̳ʸ� ����ϴ� ���Դϴ�.
		*/

	}
}

