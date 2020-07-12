#pragma once
#include <iostream>
#include <vector>
#include <string>
#include <array>
#include <set>

//보편 참조에 대한 중복적재를 피하라

namespace Item26 {
	/*
		보편 참조를 받는 함수는 일반적으로 예상한 것보다 훨씬 많은 인수 형식들을 빨아들인다는 점에서,
		보편 참조와 중복 적재를 결합하는 것은 거의 항상 나쁜 선택이다.
	*/

	namespace Case0 {
		std::multiset<std::string> names;

		void LogAndAdd(const std::string & name) {
			std::cout << name << std::endl;
			names.emplace(name);
		}

		inline void RunSample() {
			std::string petName = "Darla";

			LogAndAdd(petName);						//emplace 명령어에서 값복사 발생
			LogAndAdd(std::string("Persephone"));	//여기서도 복사 1회 발생
			LogAndAdd("Patty Dog");					//const char*는 string 임시 객체 생성. 그리고 multiset에 복사
		}
	}

	namespace Case1 {
		std::multiset<std::string> names;

		template <typename T>
		void LogAndAdd(T&& name)
		{
			std::cout << name << std::endl;
			names.emplace(std::forward<T>(name));
		}

		inline void RunSample() {
			std::string petName = "Darla";

			LogAndAdd(petName);						//이전처럼 왼값이 multiset으로 복사
			LogAndAdd(std::string("Persephone"));	//오른값을 이동. 복사는 발생하지 않음
			LogAndAdd("Patty Dog");					//임시 std::string 객체를 복사하는 대식, multiset 안에 std::string을 생성.
		}
	}

	namespace Case2 {
		std::multiset<std::string> names;

		template <typename T>
		void LogAndAdd(T&& name)
		{
			std::cout << "Called LogAndAdd(T&&) : " << name << " : " << typeid(T&&).name() << std::endl;
			names.emplace(std::forward<T>(name));
		}
		void LogAndAdd(int var)
		{
			std::cout << "Called LogAndAdd(int) : " << var << std::endl;
			names.emplace(std::to_string(var));
		}

		inline void RunSample() {
			std::string petName = "Darla";
			const std::string petName2 = "LuLu";

			LogAndAdd(petName);						//Called LogAndAdd(T&&)
			LogAndAdd(std::string("Persephone"));	//Called LogAndAdd(T&&)
			LogAndAdd("Patty Dog");					//Called LogAndAdd(T&&)
			LogAndAdd(petName2);					//Called LogAndAdd(T&&)

			LogAndAdd(22);							//Called LogAndAdd(int)

			//LogAndAdd((short)22);					//LogAndAdd(T&&) 호출시도 -> 컴파일에러
		}
	}

	namespace CaseConstructor {
		/*
			완벽 전달 생성자들은 특히나 문제가 많다. 
			기반 클래스 복사 및 이동 생성자들에 대한 파생 클래스의 호출들을 가로챌 수 있기 때문이다.
		*/

		class Person {
		public:
			explicit Person() = default;
			template <typename T>
			explicit Person(T&& n) : name(std::forward<T>(n))			//완벽 전달 생성자
			{
				std::cout << name << " : " << typeid(decltype(n)).name() << std::endl;
			}

			explicit Person(int idx) : name(std::to_string(idx))
			{
				std::cout << name << " : " << "int" << std::endl;
			}

			Person(const Person & rhs) : name(rhs.name)
			{
				std::cout << name << " : " << "copy" << std::endl;
			}

			Person(Person && rhs) : name(std::move(rhs.name))
			{
				std::cout << name << " : " << "move" << std::endl;
			}

			/*
				항목 17의 설명대로, 컴파일러는 이동/복사 생성자를 자동으로 작성하는 경우가 있다.
			*/

		private:
			std::string name;
		};

		

		inline void RunSample() {
			Person p("Nancy");
			const Person p2("Puppy");
			//Person clone(p);	//컴파일 에러, 복사 생성자가 아니라 완벽전달 생성자를 호출한다.
			Person clone2(p2);
			auto clone_moved(std::move(p));
			//auto clone_moved2(std::move(p2));	//컴파일 에러
		}

		/*
			컴파일 불가능
		*/
		//class SpecialPerson : public Person {
		//public:
		//	SpecialPerson() = default;
		//	SpecialPerson(const SpecialPerson & rhs) : Person(rhs) {		//Person의 완벽전달 생성자 호출
		//		std::cout << "SpecialPerson copy" << std::endl;
		//	}
		//	SpecialPerson(SpecialPerson && rhs) : Person(std::move(rhs)) {	//Person의 완벽전달 생성자 호출
		//		std::cout << "SpecialPerson move" << std::endl;
		//	}
		//};
	}
}