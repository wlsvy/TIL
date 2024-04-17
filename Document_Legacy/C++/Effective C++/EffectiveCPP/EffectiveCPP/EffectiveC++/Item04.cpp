#include <iostream>
#include <vector>
#include <string>

//객체를 사용하기 전에 반드시 그 객체를 초기화 하자 
namespace Item04 {

	/*
		C++ 에서의 객체 초기화에는 규칙이 몇 가지 있다. 
		1. 어떤 컴파일러를 막론하고, 기본 클래스는 파생 클래스보다 먼저 초기화
		2. 클래스 데이터 멤버는 그들이 선언된 순서대로 초기화(아래 Widget에서는 theName이 제일 먼저 초기화)
	*/

	class Widget {
	public:
		//기본제공 타입의 객체는 직접 손으로 초기화합니다. 경우에 따라서 저절로 되기도 하고 안 되기도 하기 때문입니다.
		//직접 초기화 예시
		int x = 0;	
		const char * text = "A C-style string";

		void DoSomething() {
			double d;
			std::cin >> d;	//입력 스트림에서 읽으면서 초기화
		}

		/*
			생성자에서는, 데이터 멤버에 대한 대입문을 생성자 본문 내부에 넣는 방법으로 멤버를 초기화하지 말고 멤버 초기화 리스트를 즐겨 사용합시다. 
			그리고 초기화 리스트에 데이터 멤버를 나열할 때는 클래스에 각 데이터 멤버가 선언된 순서와 똑같이 나열합시다.
		*/

		Widget(int val, bool) {
			/*
				이 구문은 초기화가 아니라 대입이다.
				정확히는 초기화가 이루어진 변수에 값을 대입시키는 것
			*/
			x = val;
					
		}

		//제대로 된 초기화
		Widget(int val) : x(val) {}	

		//제대로 된 초기화
		Widget() :			
			theName(),		
			theAddress(),	
			Numbers(),		
			numTimesConsulted(0)	
		{}

	private:
		std::string theName;
		std::string theAddress;
		std::vector<int> Numbers;
		int numTimesConsulted;
	};


	/*
		정적객체(static object) 는 자신이 생성된 시점부터 프로그램이 끝날 때까지 살아 있는 객체를 일컫는다.(즉 스택 및 힙 기반 객체는 정적 객체가 될 수 없다)
		
		정적 객체의 범주에 들어가는 것들은 
		1. 전역 객체, 
		2. 네임스페이스 유효범위에서 정의된 객체, 
		3. 클래스 안에서 static 으로 선언된 객체, 
		4. 함수 안에서 static 으로 선언된 객체, 
		5. 그리고 파일 유효범위에서 static 으로 정의된 객체.

		이들 중 함수 안에 있는 정적 객체는 지역 정적 객체(local static object) -> 함수에 대해 지역성을 가진다.
		나머지는 비지역 정적 객체(non-local static object) 라고 한다.
		
		정적 객체는 main() 함수가 실행 종료되고 프로그램이 끝날 때 소멸자가 호출된다.
	*/


	namespace BadCase {
		//특정 라이브러리에 포함된 클래스라 가정하자.
		class FileSystem {
		public:
			std::size_t numDisks() const { return 0; }

		};

		//사용자가 쓰게 될 객체
		FileSystem tfs;

		//라이브러리의 활용하는 사용자가 만든 클래스라 가정하자.
		class Directory {
		public:
			Directory() {
				/*
					tfs 객체를 여기서 사용한다.
					하지만, tfs 를 사용할 시점에 tfs 가 초기화되지 않았을 수 있다.
					다른 번역 단위에 정의된 비지역 정적 객체.
				*/
				std::size_t disks = tfs.numDisks();
			}
		};
	}

	//여러 번역 단위에 있는 비지역 정적 객체들의 초기화 순서 문제는 피해서 설계해야 합니다. 비지역 정적 객체를 지역 정적 객체로 바꾸면 됩니다.
	namespace SolutionCase {
		class FileSystem {
		public:
			std::size_t numDisks() const { return 0; }

		};

		//해결책으로 싱글톤 패턴을 활용합니다.
		FileSystem& tfs() {
			/*
				지역 정적 객체를 정의하고 초기화 한 뒤 참조자를 반환합니다.

				지역 정적 객체는 함수가 처음 불릴 때 반드시 초기화 됩니다.
			*/
			static FileSystem fs;
			return fs;
		}

		class Directory {
		public:
			Directory() {
				std::size_t disks = tfs().numDisks();
			}
		};

		Directory& tempDir() {
			static Directory td = Directory();
			return td;
		}
	}
}

