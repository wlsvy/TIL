using System;

//.NET 리소스 관리에 대한 이해

namespace EffectiveCSharp
{
    /// <summary>
    /// 닷넷 환경에서 가비지 수집기는 managed memory를 관장하며 네이티브 환경과는 다르게 
    /// 메모리 누수, 댕글링 포인터, 초기화되지 않는 포인터, 여타의 메모리 관리 문제를 개발자들이 직접 다루지 않도록 자동화해준다. 
    /// 
    /// 다만 데이터베이스 연결, GDI+ 객체, COM 객체, 시스템 객체 등과 같은 비관리 리소스는 여전히 개발자가 직접 관리해야 한다. 
    /// 추가적으로 이벤트 핸들러나 델리게이트 등도 잘못 사용하면 이들이 참조하는 객체들이 불필요하게 오랫동안 메모리에 남게 된다. 
    /// 결과를 반환하는 쿼리 등도 자칫 잘못하면 예상 보다 더 오랫동안 메모리를 점유하곤 한다.
    /// 
    /// 가비지 수집기는 COM의 경우 처럼 Mark/Compact 알고리즘을 통해 가비지 대상 메모리를 수거한다. 
    /// (최상위 루트 오브젝트로 부터 참조되지 않는 메모리는 가비지라고 판단하는 알고리즘). 
    /// EntitySet 클래스는 이러한 알고리즘을 활용. -> 레퍼런스 카운트의 경우 발생하는 순환 참조 문제를 해결한다.
    /// 
    /// 가비지 수집기가 수행되면 관리 힙에 대해서 콤팩트compact 작업을 수행한다. 
    /// -> 콤팩트 작업이란 사용 중인(혹은 도달 가능한) 객체들을 한쪽으로 차곡차곡 옮겨서 조각난 가용 메모리를 단일의 큰 메모리 공간으로 만드는 과정
    /// 
    /// Finalizer(C++의 소멸자)와 Idisposable 메소드는 C# 이 관리하지 않는 비관리 리소스에 대해 제공하는 매커니즘이다. 
    /// Finalizer 보다는 Idisposable을 활용하는 것이 더 나은 대안이 될 수 있다.
    /// 
    /// Finalizer 를 가지고 있는 객체는 단점이 있는데, 가비지로 간주된 이후에도 꽤 긴 시간 메모리를 점유하게 된다. 
    /// 사용자가 구현한 finalizer는 상당히 긴 시간이 경과한 다음에야 비로소 가비지 수집기에 의해서 호출된다. 
    /// 
    /// 불편하게도 finalizer는 어느 시점에 호출될지 알 수 없으며 단지 객체가 가비지가 되면 언제가는 호출되리라는 사실만 확실할 뿐이다.
    /// 
    /// </summary>
    public class ECSharp11
    {
        //C++ 에서는 좋지만, C# 에서는 나쁜 코드의 예
        public class CriticalSection
        {
            public CriticalSection()
            {
                EnterCriticalSection();
            }
            /// <summary>
            /// C#에서 finalizer는 C++과 동일한 방식으로 작동하지 않는다.
            /// C#에서 finalizer는 언젠가 호출되리라는 보장이 있을뿐(GC가 수거할때)
            /// 아래 예시에서 함수를 빠져나오는 시점에 호출되지는 않는다.
            /// 
            /// Finalizer를 가진 객체는 가비지로 간주된 즉시 해제되지 않고 가비지 수집 과정이 한번 더 수행될 때까지 메모리에 남아 있게 된다.(GC 세대 개념 참고)
            /// 
            /// 여기서 0세대에서 살아남은 finalizer 객체는 1세대로 이동된다.
            /// 0세대에서 10번 가비지가 수집될 때 한번 꼴로 1세대에서 가비지가 수집되니, 따라서 그만큼 오랫동안 살아남게 된다는 말이 된다.
            /// </summary>
            ~CriticalSection()
            {
                ExitCriticalSection();
            }

            private void EnterCriticalSection() { }
            private void ExitCriticalSection() { }
        }

        public void Func()
        {
            CriticalSection s = new CriticalSection();

            //작업 수행....

            //컴파일러는 소멸자를 호출하는 코드를 생성하며
            //이를 통해 CriticalSection 에서 벗어난다.
        }
    }
}
