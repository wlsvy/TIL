using System;

//.NET 리소스 관리에 대한 이해

namespace EffectiveCSharp
{
    public class ECSharp11
    {
        //C++ 에서는 좋지만, C# 에서는 나쁜 코드의 예
        public class CriticalSection
        {
            public CriticalSection()
            {
                EnterCriticalSection();
            }
            ~CriticalSection()
            {
                ExitCriticalSection();
                //C#에서 finalizer는 C++과 동일한 방식으로 작동하지 않는다.
                //C#에서 finalizer는 언젠가 호출되리라는 보장이 있을뿐(GC가 수거할때)
                //아래 예시에서 함수를 빠져나오는 시점에 호출되지는 않는다.
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
