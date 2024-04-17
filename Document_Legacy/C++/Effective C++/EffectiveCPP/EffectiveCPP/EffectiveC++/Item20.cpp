#include <iostream>
#include <vector>
#include <string>
using namespace std;

//'값에 의한 전달' 보다는 '상수객체 참조자에 의한 전달' 방식을 택하는 편이 대개 낫다
namespace Item20 {
	
	class Person {
	public:
		string name;
		string address;
	};
	class Student : public Person {
	public:
		string schoolName;
		string schoolAddress;
	};

	/*
		값에 의한 전달을 활용하는 경우

		student 내 존재하는 string 객체 4개, 그리고 student,person 의 생성자 소멸자 비용을 추가로 부담해야 한다.
	*/
	bool validateStudent(Student s);  

	/*
		참조에 의한 전달. 단순히 객체의 주소만 전달한다.

		원본 객체의 내용을 수정하지 않겠다는 의미에서 타입 앞에 const를 붙인다
	*/
	bool validateStudent2(const Student& s);	
												

	/*
		타입 크기만 작으면 '값에 의한 전달' 이 적절하다는 생각은 틀린 생각
		기본 제공 타입, STL 반복자, 함수 객체 타입 이 세 가지가 아니면 값에 의한 전달은 다시 생각해야 한다.

		컴파일러 중에서는 일부 기본제공 타입과 사용자 제공 타입을 완전히 다르게 다루는 경우가 있다.

		이를테면 double 타입은 레지스터에 넣어주지만, double 멤버 하나로 구성된 사용자 지정 타입은 레지스터에 넣지 않을 수 있는 것
		차라리 참조전달이 확실하다. 주솟값은 레지스터에 확실히 들어간다.
	*/

	bool validateStudent(Student s) { return false; }
	bool validateStudent2(const Student& s) { return false; }

}