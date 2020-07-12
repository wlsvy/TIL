#include <iostream>
#include <vector>
#include <string>

//예외가 소멸자를 떠나지 못하도록 붙들어 놓자
namespace Item08 {
	/*
		 소멸자 안에서 호출된 함수가 예외를 던질 가능성이 있다면 소멸자에서 모두 받아낸 후에 삼켜버리던지(try/catch 문) 프로그램을 끝내든지(std::abort()) 해야 한다.
		 - 예외를 일으키는 소멸자는 프로그램의 불완전 종료 혹은 미정의 동작의 위험을 내포하고 있기 때문이다.

		어떤 클래스의 연산이 진행되다가 던진 예외에 대해 사용자가 반응해야 할 필요가 있다면, 
		해당 연산을 제공하는 함수는 반드시 보통의 함수(즉, 소멸하지 아닌 함수)이어야 한다.
	*/

	class Widget {
	public:
		~Widget() {}
		//소멸자에서 에러가 발생한다고 가정
		//c++ 은 예외를 넘기는 소멸자를 좋아하지 않는다
	};

	void DoSomething() {
		std::vector<Widget> v(10);
		//벡터에 담겨진 클래스 객체를 반환할때 그 책임은 벡터에 있다.
		//만약 벡터의 객체가 소멸될 때 에러가 터진다면?? 
	}

	class DBConnection {
	public:
		static DBConnection create() { return DBConnection(); }

		//데이터 베이스 연결 해제, 이때 동작이 실패하면 에러 발생
		void close() {}
	};

	class DBConn {
	public:
		DBConn(DBConnection target) : db(target) {}

		void close() {
			//public 으로 선언하여 프로그래머가 사용할 수 있도록
			//1차적인 연결해제의 권한은 프로그래머에게
			db.close();
			closed = true;
		}

		//예외는 소멸장가 아닌 다른 함수에서 비롯되어야 한다
		~DBConn() {	
			
			//사용자가 연결을 안 닫았으면 여기서 닫기
			if (!closed) {	
				try {
					db.close();
				}
				catch (std::exception& e) {
					//close 실패 로그 작성 - 에러 알리기
					//std::abort(); - 프로그램 종료하는 방법도 존재
				}
			}
		}

	private:
		DBConnection db;
		bool closed;
	};

	void DoSomething2() {
		DBConn dbc(DBConnection::create());
		//DBConn 객체 생성과 소멸이 이루어지도록, 동시에 DBConnection 에 대한 생성과 소멸도 발생
	}
}