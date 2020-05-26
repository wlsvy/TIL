#include <iostream>
#include <vector>
#include <string>

namespace Item11 {
	//operator= 에서는 자기 대입에 대한 처리가 빠지지 않도록 하자.

	class Bitmap {};
	class Widget0 {
	public:
		Widget0& operator= (const Widget0& rhs) {	//안전하지 않게 구현된 operator=
			delete pb;
			pb = new Bitmap(*rhs.pb); //자기 대입을 하는 경우, 스스로의 데이터를 지워버리는 문제 발생
			return *this;
		}
	private:
		Bitmap *pb;
	}; 

	class Widget1 {
	public:
		Widget1& operator= (const Widget1& rhs) {	//자기 대입의 경우 방지
			if (this == &rhs) return *this; // 먼저 자기 자신인지 검사.

			delete pb;
			pb = new Bitmap(*rhs.pb);	//그래도 이 부분은 불안. 여기서 에러가 터지면, pb는 댕글링 포인터로 남는다.
			return *this;
		}
	private:
		Bitmap *pb;
	}; 
	
	class Widget2{
	public:
		Widget2& operator= (const Widget2& rhs) {	//new 명령어 에러 방지
			if (this == &rhs) return *this;		// <== 자기 대입 검사는 코드가 늘어나고 오버헤드가 존재하는 점 주목.

			Bitmap *pOrig = pb;			//pb 주솟값을 다른곳에 저장시켜놓고,
			pb = new Bitmap(*rhs.pb);	//pb의 사본을 생성한 뒤 기존값을 삭제
			delete pOrig;
			return *this;
		}
	private:
		Bitmap *pb;
	};

	class Widget {
	public:
		void swap(Widget& rhs);	//*this 와 rhs의 데이터 교체
		Widget& operator= (const Widget& rhs) {	//swap and copy 기법으로 예외/자기대입 안전성 보장
			Widget temp(rhs);
			swap(temp);	//rhs의 사본을 만들고 *this와 데이터 교환
			return *this;
		}
		Widget& operator= (Widget rhs) {	//값에 의한 전달을 하면 복사가 이루어 지는 점 활용.
			swap(rhs);	//사본 복사를 함수 본문이 아닌 매개변수에서 담당
			return *this;
		}
	private:
		Bitmap *pb;
	};
}
