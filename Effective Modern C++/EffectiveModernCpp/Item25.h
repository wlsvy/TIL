#pragma once
#include <iostream>
#include <vector>
#include <string>
#include <array>

//오른값 참조에는 std::move를 보편 참조에는 std::forward를 사용하라

namespace Item25 {

	namespace Case0 {
		/*
		우측값 참조나 보편 참조(universal reference)가 마지막으로 쓰이는 지점에서,
		우측값 참조에는 std::move를, 보편 참조(universal reference)에는 std::forward를 적용하라.

		경우에 따라서는, 우측값 참조나 보편 참조(universal reference)에 묶인 객체를 한 함수 안에서 여러 번 사용하는 경우,
		객체를 다 사용하기 전에 다른 객체로 이동하는 일은 피해야 한다.
		*/
		template <typename T>
		void setSignText(T&& text)  // text는 보편 참조(universal reference)
		{
			sign.setText1(text);		// text를 사용하되 수정하지는 않는다.
			sign.setText2(std::forward<T>(text));		// text를 우측값으로
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
		보편참조를 오버로딩으로 구현하는 경우
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
			보편참조가 오버로딩에 비해 여러가지로 유리하다.
			1. 유지보수해야 할 코드의 양이 늘어난다.
			2. setName("Temporary Name"); 와 같은 경우, 보편참조는 타입을 유추해 추가적인 형변환 없이 넘기지만, 명시적으로 선언한 경우 추가비용이 발생할 수 있다.
			3. 매개변수가 아주 많은 경우 Ex) std::make_shared의 경우, 오버로딩으로 감당하기 어렵다.
			
		*/
	}

	namespace Case2 {
		/*
			결과를 값 전달 방식(return by value)으로 돌려주는 함수가 우측값 참조나 보편 참조(universal reference)를 돌려줄 때에도 
			각각 std::move나 std::forward를 적용하라.
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
			Widget이 복사보다 효율적인 이동생성을 지원한다고 하면 반환값을 우측값으로 전달해 성능상으로 효율적인 코드를 만들 수 있다.
			반환값에 std::move 호출이 없다면 lhs 가 왼값이므로 반환값 장소로 '복사' 해야 한다.

			Widget이 이동을 지원하지 않는다고 해도 복사생성자가 호출되기 때문에, 우측값을 반환한다고 해도 해가 될 것은 없다.
		*/
	}

	namespace CopyElison {
		/*
			반환값 최적화의 대상(return value optimization)이 될 수 있는 지역 객체에는 절대로 std::move나 std::forward를 적용하지 말아야 한다.

			 반환값 최적화가 적용되려면 두 가지 조건을 만족해야 한다. 
			 (1) 그 지역 객체의 타입이 함수의 반환 타입과 같아야 하고 
			 (2) 그 지역 객체가 바로 함수의 반환값이어야 한다
			 (반환값 최적화를 적용할 수 있는 지역 객체는 지역 변수는 물론 return 문의 일부로 생성된 임시 객체도 포함된다. 함수 매개변수는 포함되지 않는다).

			 만약에 반환값 최적화의 대상이 될 수 있는 지역 객체를 std::move나 std::forward를 적용하여 반환하면, 
			 (2) 번의 조건을 불만족하여 반환값 최적화의 혜택을 받을 수 없다. 
			 std::move나 std::forward를 적용한 후에는, 그 지역 객체 자체가 아니라 지역 객체의 참조자를 반환하게 되기 때문이다.
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
			이 경우 컴파일러는 반드시 w의 복사 제거(copy elision)를 수행하거나, 아래처럼 수행하지 않는다면 반환할 지역변수를 우측값으로 취급한다.
		*/

		Widget makeWidget1(void)
		{
			Widget w;
			//...
			return std::move(w);        // 복사 제거를 수행하지 않을 때에는 w를 우측값으로 취급한다.
		}                                

		/*
			즉 반환값 최적화 과정에서 컴파일러가 필요하다면 복사제거를 수행하거나 반환값을 우측값으로 바꿔주기 때문에

			프로그래머가 직접 반환값에 std::move나 std::forward를 적용하는 행위는 불필요하며 때로는 최적화에 도움이 되지 않는다.
		*/
	}
}