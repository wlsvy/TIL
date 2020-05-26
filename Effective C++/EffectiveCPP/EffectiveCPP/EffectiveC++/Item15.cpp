#include <iostream>
#include <vector>
#include <string>
using namespace std;

namespace Item15 {
	//자원 관리 클래스에서 관리되는 자원은 외부에서 접근할 수 있도록 하자

	class Investment {};

	Investment* CreateInvestment() { return new Investment(); }
	int daysHeld(const Investment *pi) {
		return 0;
	}
	int daysHeld(const Investment& pi) {
		return 0;
	}

	void func() {
		std::auto_ptr<Investment> pInv(CreateInvestment());
		//int days = daysHeld(pInv); <- 에러. 스마트 포인터 자체를 사용할 수는 없다
		int days = daysHeld(pInv.get());	//get명령어로 pInv 안의 실제 포인터를 넘긴다
		int days2 = daysHeld(*pInv);		//operator* 도 동일한 기능을 수행한다
	}



	class FontHandle{};				//폰트 핸들. C API 사용되는 예시
	void releaseFont(FontHandle fh) {};

	class Font {		//RAII 클래스
	public:
		explicit Font(FontHandle fh) : f(fh) {}		//C API로 하기때문에 참조전달이 아닌 값복사
		FontHandle get() const { return f; }
		~Font() { releaseFont(f); }

		operator FontHandle() const { return f; }
	private:
		FontHandle f;
	};

	FontHandle getFont() { return FontHandle(); };
	void changeFontSize(FontHandle f, int newSize) {} //폰트 API 일부

	void Func2() {
		Font f(getFont());
		int newFontSize = 0;

		changeFontSize(f.get(), newFontSize); //Font에서 FontHandle로 바꾼후 넘긴다
												//사용할때마다 명시적으로 변환(get())해야 하는 점이 번거로울 수 있다.

		changeFontSize(f, newFontSize);		//클래스 안에 operator()가 구현되어 있다면 암시적 변환도 가능!(편리하다)
											//하지만 암시적 변환은 실수를 저지를 여지를 만든다

		//명시적/암시적 변환에 대해서는 클래스 설계 의도에 따라 달라질 수 있다.
	}

	//RAII클래스가 자원을 관리하는 역할을 맡았으니 캡슐화에 대해서도 짚고 넘어가야 한다.
	//shared_ptr 의 경우 레퍼런스 카운팅에 관련된 자원들은 전부 은닉하지만 자신이 관리하는 자원에 대해서는 접근 경로를 제공하고 있다.
}