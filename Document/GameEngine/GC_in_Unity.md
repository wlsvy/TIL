## <span class="fontColorRed">번역문서입니다.</span>

## 유니티의 GC

유니티의 가비지 컬렉터는 Mark/Sweep 이라는 알고리즘을 사용합니다.

이 알고리즘의 아이디어는 GC가 일어날때 GC Root로부터 시작해서 도달할 수 있는 객체들을 따로 마킹해 내려가면서 마지막까지 마킹되지 않은 객체들은 회수됩니다.

유니티의 가비지 컬렉터는 Boehm-Demers-Weiser 가비지 컬렉터라고 부르는데요, 위와 같은 알고리즘으로 동작하며 다음과 같은 특징이 있습니다.

*   **Stop The World :** GC 발생시 프로그램의 모든 스레드가 중단되고 GC가 완료될때까지 기다립니다. 유니티는 멀티스레드 GC를 지원하지 않습니다. 유니티 2019 이후부터는 Incremental GC가 도입되긴 했지만 시분할로 GC될 뿐 여전히 모든 스레드는 중단됩니다.
     
*   **Generation을 나누지 않음 :** 닷넷에서는 각 객체들을 세대로 나누어 최근에 생성된 낮은 세대의 객체들을 집중적으로 GC하게 되는데요. GC 속도를 빠르게 하기 위함입니다. 그러나 유니티에서는 이런 세대를 나누지 않습니다. GC가 발생하면 모든 Managed Heap에 대해 GC를 하게 됩니다. (Full GC)
     
*   **압축하지 않음 :** 힙에서 파편화되면 파편화 된 대로 놔두고 처리하지 않습니다. 
    ![](Image\2021-05-24-11-04-20.png)
    당연하지만 실제 메모리 사용 영역보다 많은 메모리를 잡게 됩니다.
     

## 박싱/언박싱

*   struct가 인터페이스를 구현하게 되면, 해당 struct를 인터페이스로 접근할 경우 박싱됩니다.
    모든 interface 구현체를 ReferenceType으로 보기 때문입니다.
     
*   ValueType 인스턴스에 대고 GetType()를 호출하면 박싱이 일어납니다.
     
*   Struct에 대고 ToString(), GetHashCode()를 호출할 경우 Mono에서는 박싱되지 않으나 IL2CPP에서는 박싱이 일어납니다.
    만일 두 메서드를 재정의했다면 박싱이 일어나지 않습니다.
    그러나 base.ToString(), base.GetHashCode()를 호출하고 있다면 여전히 박싱됩니다.
     

## Conditional 애트리뷰트

개발과정중에 Debug.Log를 많이 쓸겁니다.

![](Image\2021-05-24-11-04-37.png)

위 같은 호출은 unityLogger.logEnabled나 unityLogger.filterLogType 으로 활성화를 끄더라도 문자열 합성 본연의 GC Alloc은 막지를 못하는데요

![](Image\2021-05-24-11-04-50.png)

그래서 보통 위와 같이 빌드에는 타지 않게 전처리문을 넣기도 합니다.

다만 이렇게 #if #endif이 많아지면 코드 가독성이 떨어지는 문제가 있죠.

![](Image\2021-05-24-11-05-05.png)

![](Image\2021-05-24-11-05-33.png)

이때 위처럼 \[Conditional\] 애트리뷰트를 사용하면 해결할 수 있습니다.

위 코드는 GC Alloc이 발생하지 않습니다.

(역주: 참고로 Debug.Log는 Release 빌드에서도 Stripping 되지 않습니다)

## 오브젝트풀

[https://bitbucket.org/Unity-Technologies/ui/src/2019.1/UnityEngine.UI/UI/Core/Utility/ObjectPool.cs](https://bitbucket.org/Unity-Technologies/ui/src/2019.1/UnityEngine.UI/UI/Core/Utility/ObjectPool.cs)

UGUI 구현중에는 내부적으로 사용되는 오브젝트 풀이 있습니다. 

보통 1회용으로 반복적으로 생성되는 버퍼가 있는 경우 사용합니다.

다만 만일 이런식으로 버퍼를 만드는 객체가 동시에 많이 존재할 경우 적은 크기의 버퍼가 여러개 만들어져서 오히려 메모리가 더 낭비되는 경우가 있을 수 있으니 주의합시다.

![](Image\2021-05-24-11-05-50.png)

[https://bitbucket.org/Unity-Technologies/ui/src/2019.1/UnityEngine.UI/UI/Core/Utility/ListPool.cs](https://bitbucket.org/Unity-Technologies/ui/src/2019.1/UnityEngine.UI/UI/Core/Utility/ListPool.cs)

UGUI에는 ObjectPool을 사용한 특수한 ListPool 클래스가 있습니다.

주의: 리스트 풀이 유효한 경우는 원소가 밸류타입이거나 임시 버퍼 역할만 하는 경우입니다. 엘리먼트가 모두 새로 생성된 객체면 의미 없습니다.

(역주: 여기서 링크에 달린 클래스들은 internal이라 밖에서 쓸수 없던걸로 기억하는데요. 현재 MM에서도 커스텀 오브젝트풀이 있긴 한데 콜렉션을 풀링할 수는 없는 상태라 만일 필요하다면 별도 ListPool 구현이 필요해 보입니다.)

**+TMI**

unsafe 구문중에 stackalloc이란게 있습니다. 이 키워드를 쓰면 배열을 스택에 할당하여 임시 버퍼를 쉽게 만들었다 부수는게 가능합니다.

## 문자열

C#에서 string은 Immutable입니다. 그래서 문자열 합성을 하는 경우 항상 새 문자열을 만들고, 항상 GC Alloc 대상이 됩니다.

\---생략

원문은 Intern Pool에 대한 설명과 커스텀 string pool을 사용하라고 되어있는데

이에 대한 더 좋은 아티클이 있어서 링크합니다.

[http://taeyo.net/Columns/View.aspx?SEQ=253&PSEQ=23&IDX=5](http://taeyo.net/Columns/View.aspx?SEQ=253&PSEQ=23&IDX=5)

요약하면 C#에서는 이미 만들어진 string에 대해서는 유일한 객체임을 보장해줍니다.

“ABCDEF”와 “ABC”+”DEF” 해서 만들어진 문자열은 완전히 같아서 주소까지 같습니다.

다만 생성된 문자열에 대한 참조가 사라질 경우 GC 대상에 포함되버리는데, 그 경우 결국 가비지가 되버립니다.

이걸 막으려면 **Internpool** 이라 불리는 닷넷 내부의 문자열을 저장하는 풀에 집어넣을 수 있는데

IsInterned 검사 및 String.Intern()을 호출하여 그게 가능합니다. 

원문 저자는 이런식으로 미리 사용될 문자열에 대해 풀링을 해놓고, 필요없을때 해제하라고 합니다.

## 람다함수

![](Image\2021-05-24-11-06-16.png)

![](Image\2021-05-24-11-06-29.png)

![](Image\2021-05-24-11-06-37.png)

위 세가지 케이스는 모두 가비지를 생성합니다.

캡쳐된 값이 있으면 무조건 가비지가 생성됩니다.

![](Image\2021-05-24-11-07-11.png)

![](Image\2021-05-24-11-07-26.png)

위처럼 아예 캡쳐된 값이 없거나, 정적 변수에 접근하는 경우 가비지가 생성되지 않습니다.

**하지만 함정이 있는데 IL2CPP에선 위 두 방법조차도 가비지가 생성됩니다**

그러므로 람다를 사용해야 한다면 항상 delegate를 캐싱해두고 쓰도록 합시다.

![](Image\2021-05-24-11-07-36.png)

위 메서드는 Mono와 IL2CPP 모두에서 가비지를 만들지 않습니다.

<span class="fontColorRed"><strong>+추가테스트</strong></span>

![](Image\2021-05-24-11-07-49.png)

위와 같은 로컬펑션은 가비지를 만들까요?

→ 만듭니다. Mono/IL2CPP 모두에서 가비지를 만듭니다.

![](Image\2021-05-24-11-08-00.png)

이 값은 멤버메서드를 호출할때에도 동일합니다.

![](Image\2021-05-24-11-08-54.png)

위 코드의 IL을 까보면

![](Image\2021-05-24-11-09-01.png)

어느쪽이든 newobj를 호출하고 있음을 볼 수 있습니다.

매번 Call(new Action(Func))을 하고 있는것과 같습니다.

자세한 설명은 [https://jacksondunstan.com/articles/3765](https://jacksondunstan.com/articles/3765) 여기에도 있습니다.

## UnityAPI

**배열을 리턴하는 모든 유니티 API는 가비지를 만듭니다**

![](Image\2021-05-24-11-09-12.png)

흔히 볼 수 있는건 위와 같은 코드입니다.

![](Image\2021-05-24-11-09-19.png)

이 경우 위에서 말했던 ListPool으로 최적화 할 수 있습니다.

![](Image\2021-05-24-11-09-28.png)

또 흔한 실수는 위와 같은 코드인데요.

흔히들 이게 그냥 참조만 한다고 착각하는데 사실은 매번 호출마다 새 material 배열을 만들어냅니다.

![](Image\2021-05-24-11-09-36.png)

이것도 위처럼 처리할 수 있습니다.

(역주 : 띠용….)

## UGUI

이것도 흔히 잘 모르고 넘어갈 수 있는 부분인데, 프리팹 인스턴시에이트시 만일 내부에 빈 Text가 많이 존재한다면 심각한 GC Alloc이 발생합니다.

이것의 원인은 TextGenerator가 인스턴시에이트될때 만일 내부의 Text가 비어있다면 문자 50개를 초기화 값으로 넣어버리고, 50개 문자분의 UIVertex와 UICharInfo가 생성됩니다. 

이 문제는 Text에 값을 채워넣거나 공백 하나 넣음으로서 해결할 수 있습니다.