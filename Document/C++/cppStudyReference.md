> ### cpp 공부를 위한 참고 링크를 정리해 봅시다.
> 대충 개념을 다 정리하는게 힘들어서 링크만 올리는 페이지

## c++ 컴파일 과정

<details>
<summary>expand </summary> <br>

![](http://faculty.cs.niu.edu/~mcmahon/CS241/Notes/Images/build.png)

#### Reference
- [faculty](http://faculty.cs.niu.edu/~mcmahon/CS241/Notes/build.html)
- [dummies : the-compilation-process-in-c](https://www.dummies.com/programming/cpp/the-compilation-process-in-c/)
- [컴파일 옵션은 여기서 참고, northstar dartmouth](https://northstar-www.dartmouth.edu/doc/solaris-forte/manuals/c++/user_guide/Rev.html)

</details>

## Static/ dynamic library
<details>
<summary>expand </summary> <br>

- static-link lib : link 단계에서 라이브러리(*.lib 파일)를 실행 바이너리에 포함합니다.
  - 정적 빌드 단계에서 라이브러리 파일이 포함되므로 실행파일 크기가 커질 수 있습니다.
  
- dynamic-link lib : 실행 바이너리에서 필요시 사용할 수 있도록 최소한의 정보만 포함하여 링크하거나, 아예 빌드독립적으로 DLL을 로드/사용/해제할 수 있습니다.

### Reference 
- [간단 요점 -> luyin 개인 블로그](https://luyin.tistory.com/201)
- [wiki : Library](https://en.wikipedia.org/wiki/Library_(computing))
- [wiki : Dynamic-link_library](https://en.wikipedia.org/wiki/Dynamic-link_library)
- [wiki : Static_library](https://en.wikipedia.org/wiki/Static_library)

</details>

### 콜백 함수 callback functioni
- 함수를 담는 그릇입니다. 다른 함수를 전달받아 매개변수 형태로 저장합니다. 콜백함수 자체는 콜백함수는 자신이 사용되는 로직에 따라 호출이 되며 호출될때 처음부터 결정된 내용이 아니라, 매개변수로 넘겨받은 다른 함수를 사용합니다.
