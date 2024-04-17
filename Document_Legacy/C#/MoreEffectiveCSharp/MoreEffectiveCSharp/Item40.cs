using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;
using System.Threading.Tasks;
using System.Threading;

//동기화에는 lock()을 최우선으로 사용하라
namespace MoreEffectiveCSharp
{
    /// <summary>
    /// 멀티스레딩 환경에서 공유데이터에 대한 접근을 관리할 때 동기화 요소synchronization primitives를 사용
    /// 
    /// Monitor.Enter(), Monitor.Exit() 혹은 lock을 활용할 수 있다.
    /// 
    /// C#에는 멀티스레드 프로그램에서 동기화를 올바르게 제어할 수 있도록 lock 키워드를 추가했다.
    /// lock()은 Monitor.Enter()와 Monitor.Exit()를 올바르게 사용했을 때와 유사 한 코드를 생성해주며, 예외로부터 안전한exception-safe 코드를 만들어 주기도 한다.
    /// 
    /// 
    /// 참조 : https://docs.microsoft.com/ko-kr/dotnet/csharp/language-reference/keywords/lock-statement
    /// </summary>
    public static class MECSharp40
    {
        /// <summary>
        /// 코드에서 try...finally 블록을 사용하므로 lock 문의 본문 내에서 예외가 throw되더라도 잠금이 해제됩니다.
        /// lock 문의 본문에서 await 연산자를 사용할 수 없습니다.
        /// </summary>
        private static void UseMoniter()
        {
            object lockObject = new object(); ;
            if (Monitor.TryEnter(lockObject, 300))
            {
                try
                {
                    // Place code protected by the Monitor here.  
                }
                finally
                {
                    Monitor.Exit(lockObject);
                }
            }
            else
            {
                // Code to execute if the attempt times out.  
            }
        }

        /// <summary>
        /// lock()은 사용자가 저지르곤 하는 일반적인 실수를 줄여주는 다양한 검증 기능을 수행한다. 
        /// 예를 들어 우선 잠글 타입이 (값 타입이 아니라) 참조 타입인지 확인한다. 
        /// Monitor.Enter() 메서드는 이런 안전 장치를 갖고 있지 않다.
        /// 
        /// Monitor의 경우 Enter()와 Exit()는 따로 호출해야 하므로 서로 다른 객체의 락을 가져오거나 해제하는 실수를 저지르기 쉽지만 lock을 사용할 시 이런 실수를 방지할 수 있다. 
        /// 
        /// lock() 문은 또한 (사람이라면 깜빡하기 쉬운) 예외로부터 안전한 코드를 자동으로 만들어준다. 
        /// 또한 lock()은 대상 객체를 한 번만 평가하므로, Monitor.Enter()와 Monitor.Exit()보다 효율적인 코드를 생성해준다. 
        /// 이런 여러 가지 이유로 C#으로 프로그램을 작성할 때에는 동 기화가 필요할 때 lock()문을 최우선으로 고려해야 한다.
        /// 
        /// </summary>
        private static void UseLock()
        {
            object x = new object();

            //lock은 참조 타입만 잠금 수 있습니다.
            lock (x)
            {
                // Your code...
            }

            //Monitor문으로 바꾸면 아래와 같습니다.
            object lockObject = new object(); ;
            bool __lockWasTaken = false;
            try
            {
                System.Threading.Monitor.Enter(lockObject, ref __lockWasTaken);
                // Your code...
            }
            finally
            {
                if (__lockWasTaken) System.Threading.Monitor.Exit(lockObject);
            }
        }

        /// <summary>
        /// lock()이 Monitor.Enter()와 동일한 MSIL을 생성한다는 점 때문에 한 가지 제약이 생긴다. 
        /// Monitor.Enter()는 락을 얻을 때까지 영원히 대기하기 때문에 교착상태에 빠질 수 있다. 
        /// 
        /// 큰 규모의 기업 시스템에서는 중요한 리소스에 접근할 때 더욱 방어적일 필요가 있는데
        /// Monitor.TryEnter()을 이용하면 타임아웃을 설정할 수 있어서 중요 리소스에 접근할 수 없을 때 다른 방법을 시도할 수 있다.
        /// </summary>
        public sealed class LockHolder<T> : IDisposable where T : class
        {
            private T handle; 
            private bool holdsLock; 
            
            public LockHolder(T handle, int milliSecondTimeout) 
            { 
                this.handle = handle; 
                holdsLock = System.Threading.Monitor.TryEnter(handle, milliSecondTimeout); //일정시간동안 대기. 교착상태여서 잠금자원을 가져오지 못하면 false 반환
            }
            public bool LockSuccessful => holdsLock;
            public void Dispose()
            {
                if (holdsLock)
                {
                    System.Threading.Monitor.Exit(handle); // 두 번 해제하지 말라. 
                }
                
                holdsLock = false; 
            } 
        }

        /// <summary>
        /// 하지만 동기화가 필요한 곳에 꼭 lock()만을 써야 하는것은 아니다. 
        /// 사실 수치타입에 접근하거나 참조를 변경할 때는 System.Threading.Interlocked 클래스를 사용해서 동기화하는 것이 낫다.
        /// </summary>
        private static void IncrementValue(ref int val) => System.Threading.Interlocked.Increment(ref val);

    }
}
