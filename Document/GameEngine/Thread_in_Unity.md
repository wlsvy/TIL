유니티에서는 어떤 스레드가 쓰이는지?
===

쉽지 않은 분야고 공부가 불충분하지만 차근차근 정리해본다.

## 유니티에서는 다수의 스레드가 사용된다

Unity Api가 활용되며 게임 로직이 동작하는 `main thread`

렌더링 파이프라인 관련 동작을 담당하는 `render thread`

렌더링 과정 중, 선별(culling), 그림자 계산 등의 작업을 도와주는 `worker thread`
(worker thread가 추가로 맡은 역할이 더 있는지도 확인해봐야 한다.)

그 외에 audio, loading 등 다수의 스레드가 유니티에서 열심히 일하고 있다.

## Unity Api는 스레드 안전성이 없다.

이유는 유니티가 내부(native)는 C++, 외부에서는 C#을 사용하는 구조가 그 원인.
여러가지 원인이 있겠지만, 찾아본 바로는 그 중 하나가 gc에 의해 동기화 문제가 발생할 수 있기 때문이다.

다음의 시나리오를 보자
다수의 스레드에서 unity api를 호출한다고 가정하자

1. 다수의 사용자 정의 스레드에서 대량의 GameObject를 생성한다.
2. main 스레드에서도 GameObject를 생성한다.
3. CLR 과 독립적으로 작동하는 유니티의 C++ 코드는 명령을 받는 대로 열심히 일처리한다.
4. 사용자 정의 스레드의 GameObject 생성이 아직 진행되는 동안, main 스레드의 GameObject 생성이 완료된다.
5. main 스레드에서 메모리를 확보하기 위해 GC를 호출한다.
6. 아무것도 모르는 GC는 c++ 코드가 뭐하는지 관심도 없이 가비지 메모리를 수거하고, 메모리 압축(compact)을 진행한다
7. 메모리 압축 이후 C++은 자신이 사용한 메모리가 갑자기 바뀌었고, 전부 변경되버리자 혼란에 빠진다(미정의 동작)

유니티의 네이티브 코드가 CLR과 독립되어 있고, \
네이티브 코드가 작동 중 gc의 메모리 압축 과정이 발생한다면 더 이상 메모리가 동기화 상태가 아니게 되는 셈

참조 : https://forum.unity.com/threads/why-not-make-unity-monobehavior-thread-safe-for-c-jobs.538169/


#### 렌더링 파이프라인 관련참조

https://learn.unity.com/tutorial/optimizing-graphics-in-unity
