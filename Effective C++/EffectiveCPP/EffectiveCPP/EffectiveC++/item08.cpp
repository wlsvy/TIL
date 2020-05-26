/*

#include <iostream>
#include <vector>
#include <string>

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
	void close();	//연결을 닫기, 이때 연결이 실패하면 에러 발생
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
	~DBConn() {	//예외는 소멸장가 아닌 다른 함수에서 비롯되어야 한다

		if (!closed) {	//사용자가 연결을 안 닫았으면 여기서 닫기
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

*/