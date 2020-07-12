#pragma once
#include <iostream>
#include <vector>
#include <string>
#include <array>
#include <set>
#include <cassert>

//보편 참조(universal reference)에 대한 중복적재 대신 사용할 수 있는 기법들을 알아 두라

namespace Item27 {
	/*
		1. 오버로딩을 포기한다.
		단순히 오버로딩을 포기하고 보편 참조(universal reference)를 매개변수로 받는 함수와 그렇지 않은 함수의 이름을 다르게 만드는 것이다. 
		하지만 생성자의 경우, 이름이 고정되어 있어서 이 방법을 적용할 수 없다.


		2. const T& 매개변수를 사용한다.	(보편참조를 포기)
		보편 참조(universal reference)를 매개변수로 받는 대신, const T&를 매개변수로 받도록 하고 오버로딩을 하는 것이다. 
		즉 효율성을 포기하는 대신, 예상치 않은 문제를 피하는 것이다.


		3. 값 전달 방식의 매개변수를 사용한다.
		이 설계는 항목 41의 조언, 즉 복사될 것이 확실한 객체는 값으로 전달하는 것을 고려하라는 조언과 일치한다.

		4. 꼬리표 배분을 사용한다.
		const 좌측값 참조 전달이나 값 전달은 완벽 전달을 지원하지 않는다.
		보편 참조(universal reference)를 사용하려는 이유가 완벽 전달이라면, 
		보편 참조(universal reference) 말고는 다른 대안이 없다. 이런 경우에는 꼬리표 배분을 사용할 수 있다.

		5. 보편 참조(universal reference)를 받는 템플릿을 제한한다.
		std::enable_if를 이용해서 템플릿의 인스턴스화를 제한함으로써 보편 참조(universal reference)와 오버로딩을 함께 사용할 수 있다. 
		std::enable_if는 컴파일러가 보편 참조(universal reference) 오버로딩을 사용하는 조건을 프로그래머가 직접 제어하는 용도로 쓰인다.
	*/

	namespace Case_Tag0 {
		std::multiset<std::string> names;

		template <typename T>
		void LogAndAddImpl(T&& name, std::false_type)
		{
			std::cout << "Called LogAndAdd(T&&) : " << name << " : " << typeid(T&&).name() << std::endl;
			names.emplace(std::forward<T>(name));
		}
		void LogAndAddImpl(int var, std::true_type)
		{
			std::cout << "Called LogAndAdd(int) : " << var << std::endl;
			names.emplace(std::to_string(var));
		}

		template <typename T>
		void LogAndAdd(T&& name)
		{
			LogAndAddImpl(std::forward<T>(name), std::is_integral<T>());  //아직 몇가지 문제점이 있다.
		}
		

		inline void RunSample() {
			std::string petName = "Darla";
			const std::string petName2 = "LuLu";

			LogAndAdd(petName);						//Called LogAndAdd(T&&)
			LogAndAdd(std::string("Persephone"));	//Called LogAndAdd(T&&)
			LogAndAdd("Patty Dog");					//Called LogAndAdd(T&&)
			LogAndAdd(petName2);					//Called LogAndAdd(T&&)

			LogAndAdd(22);							//Called LogAndAdd(int)
			LogAndAdd((short)22);					//Called LogAndAdd(int) short 타입도 문제없다!!

			const int& i = 22;
			//LogAndAdd(i);							//컴파일 에러, const int& 형은 is_integral 결과가 false이다. 참조 타입이기 때문
		}
	}

	namespace Case_Tag1 {
		std::multiset<std::string> names;

		template <typename T>
		void LogAndAddImpl(T&& name, std::false_type)
		{
			std::cout << "Called LogAndAdd(T&&) : " << name << " : " << typeid(T&&).name() << std::endl;
			names.emplace(std::forward<T>(name));
		}
		void LogAndAddImpl(int var, std::true_type)
		{
			std::cout << "Called LogAndAdd(int) : " << var << std::endl;
			names.emplace(std::to_string(var));
		}

		template <typename T>
		void LogAndAdd(T&& name)
		{
			LogAndAddImpl(std::forward<T>(name), std::is_integral<std::remove_reference_t<T>>());	
			/*
				참조성 제거

				참고로 std::is_integral 은 내부에서 자동적으로 const, volatile 속성을 떼서 타입을 확인한다.
			*/
		}


		inline void RunSample() {
			std::string petName = "Darla";
			const std::string petName2 = "LuLu";

			LogAndAdd(petName);						//Called LogAndAdd(T&&)
			LogAndAdd(std::string("Persephone"));	//Called LogAndAdd(T&&)
			LogAndAdd("Patty Dog");					//Called LogAndAdd(T&&)
			LogAndAdd(petName2);					//Called LogAndAdd(T&&)

			LogAndAdd(22);							//이하 전부 Called LogAndAdd(int)
			LogAndAdd((short)22);					

			int i0 = 22;
			const int& i1 = i0;
			LogAndAdd(i1);							
			volatile int & i2 = i0;
			LogAndAdd(i2);
			LogAndAdd(std::move(i1));
		}
	}

	namespace Case_Constructor0 {
		/*
			std::enable_if를 이용하면 컴파일러가 마치 특정 템플릿이 존재하지 않는 것처럼 행동하게 만들 수 있다. 
			그런 템플릿을 비활성화된(disabled) 템플릿이라고 부른다.
		*/
		class Person {
		public:
			template <
				typename T,
				typename = typename std::enable_if_t<!std::is_same_v<Person, typename std::decay_t<T>>>
			>
			explicit Person(T&& n) : name(n)
			{
				std::cout << name << " : " << typeid(decltype(n)).name() << std::endl;
			}
			/*
				std::decay 는 타입에서 모든 참조와 모든 cv 한정자(cv-qualifier, const/volatile)을 제거한다.
			*/

			/*explicit Person(int idx) : name(std::to_string(idx))
			{
				std::cout << name << " : " << "int" << std::endl;
			}*/

			Person(const Person & rhs) : name(rhs.name)
			{
				std::cout << name << " : " << "copy" << std::endl;
			}

			Person(Person && rhs) : name(std::move(rhs.name))
			{
				std::cout << name << " : " << "move" << std::endl;
			}


		private:
			std::string name;
		};

		inline void RunSample() {
			Person p("Nancy");					//char const[6]
			const Person p2("Puppy");			//char const[6]
			Person clone(p);					//copy
			Person clone2(p2);					//copy
			auto clone_moved(std::move(p));		//move
			auto clone_moved2(std::move(p2));	//copy
		}

		/*
			아직은 컴파일 되지 않음

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

	namespace Case_Constructor1 {
		class Person {
		public:
			explicit Person() = default;

			template <
				typename T,
				typename = typename std::enable_if_t
				<
					!std::is_base_of_v<Person, typename std::decay_t<T>> &&	//파생 클래스가 매개변수로 들어올 때 복사생성자를 호출하도록
					!std::is_integral_v<std::remove_reference_t<T>>			//정수값이 매개변수로 들어오면 정수버전 생성자를 호출하도록
				>
			>
			explicit Person(T&& n) : name(n)
			{
				static_assert(
					std::is_constructible_v<std::string, T>, 
					"Parameter n can't be used to construct a std::string");	//is_constructible 까지 활용해 만약에 std::string 생성할 수 없는 경우까지 대비

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


		private:
			std::string name;
		};

		class SpecialPerson : public Person {
		public:
			SpecialPerson() = default;
			SpecialPerson(const SpecialPerson & rhs) : Person(rhs) {		
				std::cout << "SpecialPerson copy" << std::endl;
			}
			SpecialPerson(SpecialPerson && rhs) : Person(std::move(rhs)) {	
				std::cout << "SpecialPerson move" << std::endl;
			}
		};

		inline void RunSample() {
			Person p("Nancy");					//char const[6]
			const Person p2("Puppy");			//char const[6]
			Person clone(p);					//copy
			Person clone2(p2);					//copy
			auto clone_moved(std::move(p));		//move
			auto clone_moved2(std::move(p2));	//copy
			
			Person p3(10);

			SpecialPerson sp0;
			const SpecialPerson sp1;
			SpecialPerson sp2(sp0);
			SpecialPerson sp3(sp1);
		}
	}
}