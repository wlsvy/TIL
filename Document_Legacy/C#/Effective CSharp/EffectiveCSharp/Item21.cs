using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;
using System.Threading.Tasks;

namespace EffectiveCSharp
{
    /// <summary>
    /// 타입 매개변수가 IDisposable을 구현한 경우를 대비하여 제네릭 클래스를 작성하라
    /// </summary>
    public static class ECSharp21
    {
        /* 제약 조건은 두 가지 역할을 한다.
         * 1. 런타임 오류가 발생할 가능성이 있는 부분을 컴파일 타임 오류로 대체할 수 있다.
         * 2. 타입 매개변수로 사용할 수 있는 타입을 명확히 규정하여 사용자에게도 도움을 준다.
         * 
         * 하지만 제약 조건은 타입 매개변수가 무엇을 해야 한느지만을 규정할 수 있고, 무엇을 해서는 안 되는지를 정의할 수 없다. 
         * 대부분의 경우 타입 매개변수로 지정 한느 타입이 제약 조건을 통해 요구하는 작업 외에 다른 작업을 추가로 수행할 수 있는지에 대해서 신경쓰지 않지만
         * 해당 타입이 IDisposable을 구현하고 있다면 이 경우 만큼은 특별히 신경 써야 한다.
         */ 

        public interface IEngine
        {
            void DoWork();
        }

        public class EngineDriverOne<T> where T : IEngine, new()
        {
            /// <summary>
            /// 이 예에서 T가 IDisposable을 구현한 타입일 경우 리소스 누수가 발생할 수 있다.
            /// 따라서 반드시 추가적인 작업이 필요하다.
            /// </summary>
            public void GetThingsDone()
            {
                T driver = new T();
                driver.DoWork();
            }

            /// <summary>
            /// 아래처럼 코드를 작성하면 컴파일러는 IDisposable로 형변화노딘 객체를 저장하기 위해서 숨겨진 지역변수를 생성한다.
            /// 만약 T가 IDisposable을 구현하지 않았다면 이 지역변수의 값은 null이 된다.
            /// 
            /// C#컴파일러는 이 지역변수의 값이 null 인지를 검사한 후 Dispose()를 호출하도록 코드를 생성하기 때문에 
            /// 지역변수의 값이 null인 경우 Dispose()가 호출되지 않는다.
            /// 반대로 T가 IDisposable을 구현했다면 using 블록을 빠져나올 때 Dispose() 메소드가 호출된다.
            /// </summary>
            public void GetThingsDone2()
            {
                T driver = new T();
                using (driver as IDisposable)
                {
                    driver.DoWork();
                }
            }
        }

        /// <summary>
        /// 타입 매개변수로 전달한 타입의 멤버 변수를 선언한 경우에는 좀 더 복잡하다.
        /// 1.sealed 추가. 파생 클래스를 만들 가능성이 있는 타입이라면 표준 Dispose 패턴 전체를 구현해야 한다.
        /// 2.IDisposable을 구현한 타입일 경우를 대비해 Dispose 메서드를 구현해둬야 한다.
        /// </summary>
        public sealed class EngineDireverTwo<T> : IDisposable where T : IEngine, new()
        {
            private Lazy<T> driver = new Lazy<T>(() => new T());

            public void GetThingsDone() => driver.Value.DoWork();

            /// <summary>
            /// dispose를 여러번 호출하는 경우를 충분히 대비해두자.
            /// 일반적인 방법으로 dispose를 호출하면서 driver에 null을 할당하는 방법이 있겠다.
            /// </summary>
            public void Dispose()
            {
                if (driver.IsValueCreated)
                {
                    var resource = driver.Value as IDisposable;
                    resource?.Dispose();
                }
            }
        }

        /* 제네릭을 다룰 때 타입 매개변수가 IDisposable을 구현하고 있는 경우에 대비하자.
         * 항상 방어적으로 코드를 작성하고 객체가 삭제될 때 리소스가 누수되지 않도록 주의해야 한다.
         */ 
    }
}
