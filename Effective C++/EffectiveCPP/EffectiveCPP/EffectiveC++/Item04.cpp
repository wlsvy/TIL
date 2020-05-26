#include <iostream>
#include <vector>
#include <string>

class Item3 {	
public:
	//기본타입 객체는 경우에 따라 저절로 초기화가 되기도 하고 그렇지 않기도 한다.
	int x = 0;	//직접 초기화
	const char * text = "A C-style string";	//포인터의 직접 초기화

	void DoSomething() {
		double d;
		std::cin >> d;	//입력 스트림에서 읽으면서 초기화
	}

	Item3(int val, bool) {
		x = val;	//이 구문은 초기화가 아니라 대입. 
					//정확히는 초기화가 이루어진 변수에 값을 대입시키는 것
	}
	Item3(int val) : x(val) {}	//제대로 된 초기화

	Item3() :			//생성자 호출
		theName(),		//string 생성자 호출
		theAddress(),	//마찬가지
		Numbers(),		//마찬가지
		numTimesConsulted(0)	//0으로 초기화
	{}

private:
	std::string theName;
	std::string theAddress;
	std::vector<int> Numbers;
	int numTimesConsulted;
};

class FileSystem {	//특정 라이브러리에 포함된 클래스라 가정.
public:
	std::size_t numDisks() const { return 0; }

};

FileSystem tfs;	//사용자가 쓰게 될 객체

class Directory {	//라이브러리의 사용자가 만든 클래스라 가정
public:
	Directory() {
		std::size_t disks = tfs.numDisks(); //tfs 객체를 여기서 사용함.
											//하지만, tfs 를 사용할 시점에 tfs 가 초기화되지 않았을 수 있음.
											//다른 번역 단위에 정의된 비지역 정적 객체.
	}
};


//////////////////////////해결책////////
//싱글톤 패턴 활용
FileSystem& tfs2() {
	static FileSystem fs;
	return fs;
}
Directory& tempDir() {
	static Directory td = Directory();
	return td;
}