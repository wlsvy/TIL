#pragma once
#include <iostream>
#include <vector>
#include <string>
#include <array>

//������ �������� std::move�� ���� �������� std::forward�� ����϶�

namespace Item25 {

	namespace Case0 {
		/*
		������ ������ ���� ����(universal reference)�� ���������� ���̴� ��������,
		������ �������� std::move��, ���� ����(universal reference)���� std::forward�� �����϶�.

		��쿡 ���󼭴�, ������ ������ ���� ����(universal reference)�� ���� ��ü�� �� �Լ� �ȿ��� ���� �� ����ϴ� ���,
		��ü�� �� ����ϱ� ���� �ٸ� ��ü�� �̵��ϴ� ���� ���ؾ� �Ѵ�.
		*/
		template <typename T>
		void setSignText(T&& text)  // text�� ���� ����(universal reference)
		{
			sign.setText1(text);		// text�� ����ϵ� ���������� �ʴ´�.
			sign.setText2(std::forward<T>(text));		// text�� ����������
		}

		class Widget {
		public:
			Widget(Widget&& rhs) :
				text1(std::move(rhs.text1)),
				text2(std::move(rhs.text2))
			{}
			void SetText1(const std::string & text) {
				this->text1 = text;
			}
			void SetText2(const std::string & text) {
				this->text2 = text;
			}

		private:
			std::string text1;
			std::string text2;
		};
	}
	
	namespace Case1 {
		/*
		���������� �����ε����� �����ϴ� ���
		*/

		class Gadget {
		public:
			template<typename T>
			void setName(T&& name) {
				this->name = std::forward<T>(name);
			}
		private:
			std::string name;
		};

		class Widget {
		public:
			void setName(const std::string& newName)   
			{
				name = newName;
			}                            

			void setName(std::string&& newName)         
			{
				name = std::move(newName);
			}                

		private:
			std::string name;
		};

		/*
			���������� �����ε��� ���� ���������� �����ϴ�.
			1. ���������ؾ� �� �ڵ��� ���� �þ��.
			2. setName("Temporary Name"); �� ���� ���, ���������� Ÿ���� ������ �߰����� ����ȯ ���� �ѱ�����, ��������� ������ ��� �߰������ �߻��� �� �ִ�.
			3. �Ű������� ���� ���� ��� Ex) std::make_shared�� ���, �����ε����� �����ϱ� ��ƴ�.
			
		*/
	}

	namespace Case2 {
		/*
			����� �� ���� ���(return by value)���� �����ִ� �Լ��� ������ ������ ���� ����(universal reference)�� ������ ������ 
			���� std::move�� std::forward�� �����϶�.
		*/

		class Widget{
		public:
			int val = 0;
		};

		Widget operator+(Widget&& lhs, const Widget& rhs)                                      
		{
			lhs.val += rhs.val;
			return std::move(lhs);                        
		}
		/*
			Widget�� ���纸�� ȿ������ �̵������� �����Ѵٰ� �ϸ� ��ȯ���� ���������� ������ ���ɻ����� ȿ������ �ڵ带 ���� �� �ִ�.
			��ȯ���� std::move ȣ���� ���ٸ� lhs �� �ް��̹Ƿ� ��ȯ�� ��ҷ� '����' �ؾ� �Ѵ�.

			Widget�� �̵��� �������� �ʴ´ٰ� �ص� ��������ڰ� ȣ��Ǳ� ������, �������� ��ȯ�Ѵٰ� �ص� �ذ� �� ���� ����.
		*/
	}

	namespace CopyElison {
		/*
			��ȯ�� ����ȭ�� ���(return value optimization)�� �� �� �ִ� ���� ��ü���� ����� std::move�� std::forward�� �������� ���ƾ� �Ѵ�.

			 ��ȯ�� ����ȭ�� ����Ƿ��� �� ���� ������ �����ؾ� �Ѵ�. 
			 (1) �� ���� ��ü�� Ÿ���� �Լ��� ��ȯ Ÿ�԰� ���ƾ� �ϰ� 
			 (2) �� ���� ��ü�� �ٷ� �Լ��� ��ȯ���̾�� �Ѵ�
			 (��ȯ�� ����ȭ�� ������ �� �ִ� ���� ��ü�� ���� ������ ���� return ���� �Ϻη� ������ �ӽ� ��ü�� ���Եȴ�. �Լ� �Ű������� ���Ե��� �ʴ´�).

			 ���࿡ ��ȯ�� ����ȭ�� ����� �� �� �ִ� ���� ��ü�� std::move�� std::forward�� �����Ͽ� ��ȯ�ϸ�, 
			 (2) ���� ������ �Ҹ����Ͽ� ��ȯ�� ����ȭ�� ������ ���� �� ����. 
			 std::move�� std::forward�� ������ �Ŀ���, �� ���� ��ü ��ü�� �ƴ϶� ���� ��ü�� �����ڸ� ��ȯ�ϰ� �Ǳ� �����̴�.
		*/

		class Widget {

		};
		Widget makeWidget0(void)
		{
			Widget w;
			//...
			return w;
		}
		/*
			�� ��� �����Ϸ��� �ݵ�� w�� ���� ����(copy elision)�� �����ϰų�, �Ʒ�ó�� �������� �ʴ´ٸ� ��ȯ�� ���������� ���������� ����Ѵ�.
		*/

		Widget makeWidget1(void)
		{
			Widget w;
			//...
			return std::move(w);        // ���� ���Ÿ� �������� ���� ������ w�� ���������� ����Ѵ�.
		}                                

		/*
			�� ��ȯ�� ����ȭ �������� �����Ϸ��� �ʿ��ϴٸ� �������Ÿ� �����ϰų� ��ȯ���� ���������� �ٲ��ֱ� ������

			���α׷��Ӱ� ���� ��ȯ���� std::move�� std::forward�� �����ϴ� ������ ���ʿ��ϸ� ���δ� ����ȭ�� ������ ���� �ʴ´�.
		*/
	}
}