#pragma once
#include <iostream>
#include <vector>
#include <string>
#include <array>
#include <set>
#include <cassert>

//���� ����(universal reference)�� ���� �ߺ����� ��� ����� �� �ִ� ������� �˾� �ζ�

namespace Item27 {
	/*
		1. �����ε��� �����Ѵ�.
		�ܼ��� �����ε��� �����ϰ� ���� ����(universal reference)�� �Ű������� �޴� �Լ��� �׷��� ���� �Լ��� �̸��� �ٸ��� ����� ���̴�. 
		������ �������� ���, �̸��� �����Ǿ� �־ �� ����� ������ �� ����.


		2. const T& �Ű������� ����Ѵ�.	(���������� ����)
		���� ����(universal reference)�� �Ű������� �޴� ���, const T&�� �Ű������� �޵��� �ϰ� �����ε��� �ϴ� ���̴�. 
		�� ȿ������ �����ϴ� ���, ����ġ ���� ������ ���ϴ� ���̴�.


		3. �� ���� ����� �Ű������� ����Ѵ�.
		�� ����� �׸� 41�� ����, �� ����� ���� Ȯ���� ��ü�� ������ �����ϴ� ���� ����϶�� ����� ��ġ�Ѵ�.

		4. ����ǥ ����� ����Ѵ�.
		const ������ ���� �����̳� �� ������ �Ϻ� ������ �������� �ʴ´�.
		���� ����(universal reference)�� ����Ϸ��� ������ �Ϻ� �����̶��, 
		���� ����(universal reference) ����� �ٸ� ����� ����. �̷� ��쿡�� ����ǥ ����� ����� �� �ִ�.

		5. ���� ����(universal reference)�� �޴� ���ø��� �����Ѵ�.
		std::enable_if�� �̿��ؼ� ���ø��� �ν��Ͻ�ȭ�� ���������ν� ���� ����(universal reference)�� �����ε��� �Բ� ����� �� �ִ�. 
		std::enable_if�� �����Ϸ��� ���� ����(universal reference) �����ε��� ����ϴ� ������ ���α׷��Ӱ� ���� �����ϴ� �뵵�� ���δ�.
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
			LogAndAddImpl(std::forward<T>(name), std::is_integral<T>());  //���� ��� �������� �ִ�.
		}
		

		inline void RunSample() {
			std::string petName = "Darla";
			const std::string petName2 = "LuLu";

			LogAndAdd(petName);						//Called LogAndAdd(T&&)
			LogAndAdd(std::string("Persephone"));	//Called LogAndAdd(T&&)
			LogAndAdd("Patty Dog");					//Called LogAndAdd(T&&)
			LogAndAdd(petName2);					//Called LogAndAdd(T&&)

			LogAndAdd(22);							//Called LogAndAdd(int)
			LogAndAdd((short)22);					//Called LogAndAdd(int) short Ÿ�Ե� ��������!!

			const int& i = 22;
			//LogAndAdd(i);							//������ ����, const int& ���� is_integral ����� false�̴�. ���� Ÿ���̱� ����
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
				������ ����

				����� std::is_integral �� ���ο��� �ڵ������� const, volatile �Ӽ��� ���� Ÿ���� Ȯ���Ѵ�.
			*/
		}


		inline void RunSample() {
			std::string petName = "Darla";
			const std::string petName2 = "LuLu";

			LogAndAdd(petName);						//Called LogAndAdd(T&&)
			LogAndAdd(std::string("Persephone"));	//Called LogAndAdd(T&&)
			LogAndAdd("Patty Dog");					//Called LogAndAdd(T&&)
			LogAndAdd(petName2);					//Called LogAndAdd(T&&)

			LogAndAdd(22);							//���� ���� Called LogAndAdd(int)
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
			std::enable_if�� �̿��ϸ� �����Ϸ��� ��ġ Ư�� ���ø��� �������� �ʴ� ��ó�� �ൿ�ϰ� ���� �� �ִ�. 
			�׷� ���ø��� ��Ȱ��ȭ��(disabled) ���ø��̶�� �θ���.
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
				std::decay �� Ÿ�Կ��� ��� ������ ��� cv ������(cv-qualifier, const/volatile)�� �����Ѵ�.
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
			������ ������ ���� ����

		*/
		//class SpecialPerson : public Person {
		//public:
		//	SpecialPerson() = default;
		//	SpecialPerson(const SpecialPerson & rhs) : Person(rhs) {		//Person�� �Ϻ����� ������ ȣ��
		//		std::cout << "SpecialPerson copy" << std::endl;
		//	}
		//	SpecialPerson(SpecialPerson && rhs) : Person(std::move(rhs)) {	//Person�� �Ϻ����� ������ ȣ��
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
					!std::is_base_of_v<Person, typename std::decay_t<T>> &&	//�Ļ� Ŭ������ �Ű������� ���� �� ��������ڸ� ȣ���ϵ���
					!std::is_integral_v<std::remove_reference_t<T>>			//�������� �Ű������� ������ �������� �����ڸ� ȣ���ϵ���
				>
			>
			explicit Person(T&& n) : name(n)
			{
				static_assert(
					std::is_constructible_v<std::string, T>, 
					"Parameter n can't be used to construct a std::string");	//is_constructible ���� Ȱ���� ���࿡ std::string ������ �� ���� ������ ���

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