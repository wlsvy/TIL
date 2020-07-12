#pragma once
#include <iostream>
#include <vector>
#include <string>
#include <array>
#include <set>

//���� ������ ���� �ߺ����縦 ���϶�

namespace Item26 {
	/*
		���� ������ �޴� �Լ��� �Ϲ������� ������ �ͺ��� �ξ� ���� �μ� ���ĵ��� ���Ƶ��δٴ� ������,
		���� ������ �ߺ� ���縦 �����ϴ� ���� ���� �׻� ���� �����̴�.
	*/

	namespace Case0 {
		std::multiset<std::string> names;

		void LogAndAdd(const std::string & name) {
			std::cout << name << std::endl;
			names.emplace(name);
		}

		inline void RunSample() {
			std::string petName = "Darla";

			LogAndAdd(petName);						//emplace ��ɾ�� ������ �߻�
			LogAndAdd(std::string("Persephone"));	//���⼭�� ���� 1ȸ �߻�
			LogAndAdd("Patty Dog");					//const char*�� string �ӽ� ��ü ����. �׸��� multiset�� ����
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

			LogAndAdd(petName);						//����ó�� �ް��� multiset���� ����
			LogAndAdd(std::string("Persephone"));	//�������� �̵�. ����� �߻����� ����
			LogAndAdd("Patty Dog");					//�ӽ� std::string ��ü�� �����ϴ� ���, multiset �ȿ� std::string�� ����.
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

			//LogAndAdd((short)22);					//LogAndAdd(T&&) ȣ��õ� -> �����Ͽ���
		}
	}

	namespace CaseConstructor {
		/*
			�Ϻ� ���� �����ڵ��� Ư���� ������ ����. 
			��� Ŭ���� ���� �� �̵� �����ڵ鿡 ���� �Ļ� Ŭ������ ȣ����� ����ç �� �ֱ� �����̴�.
		*/

		class Person {
		public:
			explicit Person() = default;
			template <typename T>
			explicit Person(T&& n) : name(std::forward<T>(n))			//�Ϻ� ���� ������
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
				�׸� 17�� ������, �����Ϸ��� �̵�/���� �����ڸ� �ڵ����� �ۼ��ϴ� ��찡 �ִ�.
			*/

		private:
			std::string name;
		};

		

		inline void RunSample() {
			Person p("Nancy");
			const Person p2("Puppy");
			//Person clone(p);	//������ ����, ���� �����ڰ� �ƴ϶� �Ϻ����� �����ڸ� ȣ���Ѵ�.
			Person clone2(p2);
			auto clone_moved(std::move(p));
			//auto clone_moved2(std::move(p2));	//������ ����
		}

		/*
			������ �Ұ���
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
}