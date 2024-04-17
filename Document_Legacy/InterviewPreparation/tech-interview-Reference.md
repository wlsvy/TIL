# tech-interview-Reference 

- 기술 면접 공부할 때 참조할 만한 링크를 작성한 문서입니다.

- 👶🏻 [신입 개발자 전공 지식 & 기술 면접 백과사전(깃허브)](https://github.com/gyoogle/tech-interview-for-developer) 📖
- 👶🏻 [신입 개발자 전공 지식 & 기술 면접 백과사전(웹페이지)](https://gyoogle.dev/blog/) 📖
- :clap:[기술면접 준비하기(블로그)](https://velog.io/@hygoogi/%EA%B8%B0%EC%88%A0%EB%A9%B4%EC%A0%91-%EC%A4%80%EB%B9%84%ED%95%98%EA%B8%B0)
- [c api 참고는 여기 블로그에서](http://blog.naver.com/PostList.nhn?blogId=sharonichoya&from=postList&categoryNo=22)
- [[번역] 개발자를 위한 면접 지침](https://blog.rhostem.com/posts/2019-01-05-developer-guide-for-interview?fbclid=IwAR08010UPAKzvEXznjC9su2wzmmq0cYWSRPigJbAHxPBFAc_PUlsurBvEPk)


- effective c++ : 2, 3, 7, 9, 13, 30, 32
- effective modern C++ : 1, 2, 3, 9, 15, 18, 19, 20, 21, 22, 23


# Quick Review

#### 가상함수를 쓰는 이유.
- 객체 지향 프로그래밍의 다형성을 보장하기 위함입니다.
- 가상함수는 기반 클래스의 메소드를 파생 클래스에서 재정의할 여지를 으로써, 클래스의 기능을 확장하거나 변경하는 것을 가능하게 해준니다.

#### 해쉬 테이블에서 키 값이 충돌할 시 어떻게 대처하는지.
 - 1. Chaining 체이닝 : 해시 충돌이 발생하면 해당 키값의 버켓에서 연결 리스트로 데이터들을 연결하는 방식.
   - c++ 의 unoredered_map 은 체이닝 방식입니다. 내부적으로 LinkedList 배열을 활용합니다.
 - 2. Open Addressing 개방 주소법 :  해시 충돌이 발생하면 다른 버켓에 값을 삽입하는 방식. 
	- 버켓 몇 개를 건너뛰어 값 삽입(선형 탐색Linear Probing), 
	- 제곱수의 값 만큼 건너뛴 버켓에 값 삽입하는 방식(제곱 탐색Quadratic Probing), 
	- 다른 해시 함수를 한번 더 적용한 결과를 키값으로 활용하는 방식(이중 해시Double Hash)

####  해쉬 테이블과 이진트리를 어떤 경우에 어떤 이유로 적용하는지.
- 특정 키값이 어떤 버켓에 삽입될 지는 해시함수로 O(1) 안에 결정할 수 있습니다. 이는 이진트리가 비교연산이 O(logN) 만큼 걸리는 것과 비교하면 빠를 수 있습니다.
  - 예외 케이스는 문자열 길이가 굉장히 긴 경우. 문자열 비교 연산은 앞 글자 1, 2 개만 보고 결과를 알 수도 있지만, 해시 함수는 문자열 전체를 전부 확인해야합니다.
- 해시 함수를 거쳐서 나온 값들이 정렬되어 있다는 보장이 없습니다. (C++ 의 UnorderedMap), 이진트리는 비교연산을 거쳐서 값들이 삽입되므로 원소들이 정렬되어 있으며 트리안의 값들을 비교 순서대로 순회할 수 있습니다.
	- 해시 충돌이 많이 발생하는 등, 해시 함수의 성능이 떨어지는 경우, 이진트리의 성능이 더 빠를 수도 있습니다.

#### C++ 참조와 포인터의 차이
> 둘다 다른 객체를 간접적으로 참조한다는 공통점을 제외하면
-	포인터는 널 값을 가질 수 있지만 참조자는 널 값을 가질 수 없습니다. 즉, 널 참조자(null reference)는 없습니다.
-	초기화 시, 참조자는 객체(변수)를 직접 입력받고, 포인터는 객체(변수)의 주소값을 입력받습니다.
-	참조자는 한번 가리킨 대상을 변경할 수 없지만, 포인터는 자신이 가리키는 대상을 언제든지 변경할 수 있습니다.
-	클래스 멤버 접근 시, 참조자는 "."을 사용하고 포인터는 "->"를 사용합니다.

#### C++의 템플릿과 C#의 제네릭의 차이
- C++의 템플릿은 템플릿 매개변수로 입력되는 타입별로 코드를 생성합니다.
- C#의 제네릭은 매개변수 타입이 '값 형식'일 때는 c++ 템플릿 처럼 타입별로 코드를 생성합니다. '참조 형식'일 때는 참조 타입의 가장 기본 클래스인 object 타입에 대해서만 코드를 생성합니다. 그리고 입력된 매개변수 타입을 object 타입으로 형변환 시키는 업 캐스팅을 수행합니다.
  - 여기서 c#은 제네릭 매개변수에 제약 조건을 설정할 수 있습니다. 이 경우 '참조 타입'은 제약 조건에 따라 object 타입이 아니라 제약 조건을 만족하는 가장 기본 클래스로 업캐스팅 시킵니다.
 
####  c++ casting 연산자
- [cpp type casting](https://github.com/wlsvy/TIL/blob/master/Document/C++/Cpp%20Type%20Casting.md)
 
#### c++ value category
- [cpp value category](https://github.com/wlsvy/TIL/blob/master/Document/C%2B%2B/C%2B%2B%20Value%20Category.md)
 
#### C++ auto_ptr은 왜 사용되지 않는지 
- auto_ptr의 대입 연산자가 원인입니다. 대입 연산자가 가지는 원래 의도와는 달리 auto_ptr에서는 소유권 이전이 발생해 버립니다. 
  - 위 특징이 가지는 대표적인 문제 사례가 퀵 정렬입니다. auto_ptr 컨테이너를 정렬할 때 내부적으로 피벗을 복사하는 동작이 존재하지요. 원래 의도는 재귀적으로 사용할 피벗을 '복사'하는 것이지만 auto_ptr을 사용할 때면 복사가 아니라 소유권을 '이전' 시켜 버립니다. 그 이후로 각종 오류가 몰아닥치는 것이고요.
  - unique_ptr은 이 문제를 해결합니다. 대입 연산자를 막아버리고 소유권을 이전시키기 위해서는 명시적으로 이동연산자를 활용해야 합니다.
- 참조 Effective STL : auto_ptr의 컨테이너는 절대로 만들지 말자

#### c++의 auto / template / decltype 타입 추론
- 컴파일 시간에 타입을 추론합니다.
- auto 와 template 타입 추론은 대부분 비슷합니다만 auto는 중괄호 초기치를 std::initialize_list로 추론하며 template은 중괄호 초기치를 추론하지 못합니다.
- decltype 은 주어진 이름이나 표현식의 형식을 알려줍니다. 템플릿 추론과 auto와는 달리 주어진 이름이나 표현식의 구체적인 형식(참조성 및 cv 형식까지)을 그대로 말해줍니다.
- 참조 : effective modern c++, item 1, 2, 3

#### C# 리플렉션에 대해서 아는가?
- Reflection 거울에 비친 상 이라는 뜻입니다. C# 에서 어셈블리, 모듈, 타입 객체에 대한 정보를 다루는 기능을 말한다. System.Reflection 네임스페이스의 기능들을 활용하여 런타임에 프로그램 메타데이터에 접근할 수 있습니다.


#### 세마포어 & 뮤텍스
- 문지기 역할을 합니다. 크리티컬 섹션에 프로세스 혹은 스레드가 한 번에 하나씩 접근하도록 제한합니다. 다수의 프로세스 혹은 스레드가 동시에 접근하여 레이스 컨디션이 발생하지 않도록 예방합니다.
  - 세마포어는 다수의 프로세스 혹은 스레드에 대해서, 뮤텍스는 다수의 스레드에 대해 적용 가능합니다.
  - 세마포어는 내부적으로 정수 값을 확인하여 상호 배제를 수행합니다. 뮤텍스는 0과 1 값만 가지는 binary semaphore 입니다. 즉 뮤텍스는 세마포어의 영역에 포함됩니다.
  - 세마포어의 예시는 DirectX 12 의 fence, 뮤텍스는 c++ 의 std::mutex를 예로 들 수 있습니다.

#### 자료구조 활용, 정렬, 탐색 알고리즘 시간복잡도
![](https://miro.medium.com/max/875/1*J8w0UxN-D5dqtWV4Dl3vXQ.png)
![](https://miro.medium.com/max/875/1*W9qHlz4sUcXZHfyiwaE5wQ.png)
![](https://he-s3.s3.amazonaws.com/media/uploads/1e0079d.JPG)
- [bigocheatsheet](https://www.bigocheatsheet.com/)
- [hackerearth](https://www.hackerearth.com/practice/notes/big-o-cheatsheet-series-data-structures-and-algorithms-with-thier-complexities-1/)

#### 정렬
> 시간 복잡도는 위의 그림 / 참조를 확인하세요.

- 거품 정렬 : 거품이 보글보글 끓듯 인접한 원소의 자리를 바꿉니다. 안정 정렬(stable-sort) 입니다.
- 선택 정렬 : (오름차순의 경우) 컨테이너의 첫 번째 자리에는 가장 작은 원소를 '선택'해 가져옵니다. 두 번째 자리에는 두 번째로 작은 원소를 '선택'해 가져옵니다. 세 번째 자리에는......,  불안정 정렬(unstable-sort) 입니다.
- 삽입 정렬 : 컨테이너의 첫 번째(0) 자리가 아닌 두 번째(1) 자리부터 확인하는 것이 특징입니다. 특정 원소를 보고 해당 원소를 삽입할 자리를 찾아 넣습니다. '넣는'다는 것은 해당 자리를 이미 차지하고 있는 원소를 옆으로 밀어버리고 자신이 들어간다는 겁니다. 필요하다면 그 옆의 원소도, 그 옆의 옆의 원소도 밀어버립니다. 최선의 경우 시간복잡도가 O(n)인 것이 특징입니다. 
  - 배열의 길이가 길어질수록 비효율적입니다. 안정 정렬입니다.
- 퀵 정렬 : 컨테이너에서 피벗을 정하고 피벗보다 큰 값과 작은 값을 분할합니다. 그 다음 피벗에 대해 작은 영역과 큰 영역에 대해 재귀적으로 이 과정을 다시 수행합니다. 불안정 정렬입니다.
  - O(nlogn)의 시간복잡도를 가지는 다른 알고리즘 보다도 퀵 정렬이 더 빠릅니다. 불필요한 데이터 이동을 줄이고 먼 거리의 데이터를 교환할 뿐만 아니라, 한번 결정된 피봇은 추후 연산에서 제외되는 성질을 가지기 때문입니다.
  - 퀵 정렬의 피봇을 컨테이너의 시작/끝 원소로 정하는 접근법은 이미 정렬된 컨테이너에 대해 좋지 못한 성능을 보입니다.
  - median of three 방식을 사용하면 위 문제를 개선할 수 있습니다만, [위키](https://en.wikipedia.org/wiki/Introsort)에 따르면 median of three 방식의 성능을 급격히 악화시키는 median of 3 killer라는 특이케이스가 존재합니다.
  - 또 위의 문제를 개선한 알고리즘도 있습니다. c++의 algorithm 헤더에서 쓰이는 introsort입니다.
- 합병 정렬 : 컨테이너 영역을 재귀적으로 분할 한 뒤, 분할된 영역을 다시 합치는 과정에서 비교 정렬을 수행합니다. 
  - 퀵 정렬이 재귀적으로 함수를 호출하는 과정에서 partition을 수행한다면 합병 정렬은 재귀 함수 호출로 쌓인 콜스택을 되감는 과정에서 순차적인 정렬을 수행하는 것이 차이입니다.
  - 또 있습니다. 퀵 정렬을 수행하기 위해서는 임의 접근이 필요하지만 합병 정렬은 순차적으로 비교하기 때문에 임의 접근기능이 요구되지 않습니다. ->> Linked List에서는 합병 정렬이 효율적입니다.
  - 안정 정렬입니다.
- 힙 정렬 : 힙을 만든 뒤 머리부터 하나씩 빼나갑니다. 참고로 힙에 원소를 넣을 때는(heapify) 꼬리에 넣습니다. 
  - [Geeks for Geeks : time-complexity-of-building-a-heap](https://www.geeksforgeeks.org/time-complexity-of-building-a-heap/) 에서 수학적으로 설명한 바에 의하면 데이터 갯수 N의 배열에 대해 힙을 만드는 시간 복잡도는 O(nlogn)이 아니라 O(n) 입니다.

- **C++ 의 Introsot : algorithm 헤더에서 가장 기본적인 정렬 알고리즘 입니다. 삽입/ 힙/ 퀵 정렬 세 가지가 결합한 정렬 알고리즘의 하이브리드 버전이라 보시면 되겠습니다.**
  - 지속적으로 퀵 정렬에서 활용되는 partition 방식으로 컨테이너를 분할합니다.
  - 이때 정렬 대상인 컨테이너의 사이즈가 일정 갯수(예를 들어 32) 이하일 때는 삽입정렬을 수행합니다.
  - 그리고 partition 횟수가 일정 갯수(예를 들어 1.5 * log(N)) 을 넘어서면 힙 정렬을 수행합니다.
  - 평균 / 최악 시간복잡도가 O(NlogN) 입니다.
  
- n개의 데이터를 포함하는 특정 컨테이너에서 m번째로 작은 데이터 찾기 
  - QuickSelect 알고리즘 활용합니다. 피벗을 기준으로 작은 값, 큰 값을 분리(partition)해버리는 퀵정렬의 특징을 활용합니다.
  - [참조](https://modoocode.com/287)
- 특정 컨테이너에서 제일 작은 m 개의 데이터만 정렬하기
  - 1. 힙 정렬 이후, m개의 데이터만 힙에서 빼냅니다. 시간복잡도는 평균 O(n + mlogn). 
  - 2. partial quicksort : QuickSelect 알고리즘으로 m 번째로 작은 데이터를 찾은 뒤, 해당 데이터보다 작은 m - 1 개의 데이터 영역만을 정렬합니다. 시간복잡도는 평균 O(n + mlogm)
  - [참조](https://www.cs.upc.edu/~conrado/research/talks/aofa04.pdf)
  
#### 동적/정적 라이브러리
- 라이브러리란 프로그램 실행에 필요한 코드들을 담고 있습니다.
- 정적static 라이브러리는 링킹 단계에서 실행 바이너리에 포함됩니다.
  - 불필요하게 실행 파일의 크기가 커질 수 있습니다.
- 동적 라이브러리는 dll 형태의 파일로 독립적으로 존재합니다. 실행파일에 포함되지 않습니다. shared libray 개념으로 하나의 dll 파일을 여러개의 실행파일에서 공유하는 것도 가능합니다.

- [stackoverflow : dll-and-lib-files-what-and-why](https://stackoverflow.com/questions/913691/dll-and-lib-files-what-and-why)