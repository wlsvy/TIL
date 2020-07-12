#pragma once
#include <iostream>
#include <vector>
#include <list>
#include <algorithm>
#include <map>
#include <string>
#include <array>
#include <set>
#include <memory>
#include <fstream>

//문자 단위의 입력에는 istreambuf_iterator의 사용도 적절하다

namespace Item29 {
	using namespace std;


	inline void RunSample() {
		{
			ifstream inputFile("FileReadSample.txt");

			string fileData((istream_iterator<char>(inputFile)), istream_iterator<char>());
		}
		
		/*
			위 방법은 공백(whitespace) 문자를 string 객체에 복사하지 못합니다.
 
			왜냐!? istream_iterator는 실제 스트림 읽기를 수행할 때에 operator<< 함수를 사용하며, 
			기본적으로 이 연산자 함수는 공백 문자를 건너뛰기 때문이죠.

			공백 문자를 건너뛰지 않게 하려면 입력 스트림의 skipws 플래그를 설정해제(unset)합니다.
		*/

		{
			ifstream inputFile("FileReadSample.txt");

			inputFile.unsetf(ios::skipws);
			string fileData2((istream_iterator<char>(inputFile)), istream_iterator<char>());
		}

		/*
			하지만 위의 방법은 데이터 복사 시간이 그리 빠르지 않습니다. 
			istream_iterator 가 사용하는 operator>> 함수는 서식화 입력(formatted input)을 수행합니다.
			이 말은 여러분이 해야 하는 여러 가지 자질구레한 뒷처리를 알아서 미리 해준다는 뜻입니다.

			이러한 동작들은 여러분이 서식화 입력을 할 때에는 매우 소중하고 값진 것이지만,
			그냥 입력 스트림으로부터 다음 문자를 뽑아내는 일만이 목적이라면 엄청난 손실이요 낭비가 아닐 수 없습니다.
		*/
		

		/*
			여기서 STL의 비장의 무기를 하나 소개하고자 합니다. 바로 istreambuf_iterator 라고 하는 것입니다.
			이 반복자는 istream_iterator처럼 쓸 수 있습니다. 
			istreambuf_iterator<char> 객체는 스트림 자체의 버퍼를 직접 건드려서 다음 문자들을 바로 읽어 들입니다.
		*/

		{
			ifstream inputFile("FileReadSample.txt");

			/*
				skipws 플래그를 "설정해제"할 필요도 없습니다.
				스트림 버퍼 안에서 다음 위치에 있는 문자는 어느 것이든 가지고 오는 것이 이 반복자의 특성입니다.
			*/
			string fileData((istreambuf_iterator<char>(inputFile)), istreambuf_iterator<char>());

			//istream_iterator와 비교할 때 이 반복자의 속도는 무척 빠릅니다. 간단하게 해본 벤치마크에서 무려 40%나 빨랐습니다.
		}
	}
}