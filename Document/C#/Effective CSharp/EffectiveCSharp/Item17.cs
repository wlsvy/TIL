using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;
using System.Threading.Tasks;

namespace EffectiveCSharp
{
    /// <summary>
    /// 표준 dispose 패턴을 구현하라
    /// </summary>
    public static class ECSharp17
    {
        /* 비관리 리소스를 포함하는 객체는 정리 작업이 매우 중요하다.
         * .Net framework 내부에서는  비관리 리소스를 정리하는 표준화된 방식, dispose 패턴을 사용한다.
         * 
         * 
         * 상속 계통상 최상위의 베이스 클래스는 다음과 같은 작업을 수행해야 한다.
         * 1. 리소스를 정리하기 위해서 IDisposable 인터페이스 구현
         * 2. 멤버 필드로 비관리 리소스를 포함하는 경우에 한해 방어적으로 동작할 수 있도록 finalizer 추가, 만약에 비관리 리소스가 없다면 finalizer를 구현하지 말 것.
         * 3. Dispose와 finalizer(존재하는 경우)는 실제 리소스 정리 작업을 수행하는 다른 가상 메서드에 작업을 위임하도록 작성해야 한다. 
         * 파생 클래스가 고유의 리소스 정리 작업이 필요한 경우 이 가상 메소드를 재정의할 수 있도록 하기 위함이다.
         * 
         * 파생 클래스는 다음과 같은 작업을 수행해야 한다.
         * 1. 파생 클래스가 고유의 리소스 정리 작업을 수행해야 한다면 베이스 클래스에서 정의한 가상 메서드를 재정의한다.
         * 2. 멤버 필드로 비관리 리소스를 포함하는 경우에만 finalizer를 추가해야 한다.
         * 3. 베이스 클래스에서 정의하고 있는 가상 함수를 반드시 재호출해야 한다.
         * 
         */

        /* 
         * 비관리 리소스를 포함하는 클래스는 반드시 finalizer를 구현해야 한다.
         * finalizer도 없고 dispoes()를 호출하는 겻조차 잊어버리면 자원 누수가 발생한다.
         * 
         * 가비지 수집 작업이 수행되면 finalizer가 없는 가비지 객체는 즉각 메모리에서 제거하지만, 
         * finalizer를 가진 객체는 finalizer 큐에 참조를 삽입시켜두고, finalizer 스레드라는 특별한 스레드를 통해 이 큐에 포함된 객체들의 finalizer를 호출한다.
         * 이후 finalizer를 호출한 객체에 대해 더 이상 finalizer를 호출시킬 필요가 없다는 flag를 설정하고 메모리 해제 대상으로 간주한다.
         * (그러나 해당 객체들은 1차 적인 가비지 수집 작업에서 정리되지 못했으므로, 자연스럽게 한 세대가 높아진다. 즉 다른 객체에 비해 상대적으로 메모리에 오래 살아남는다.)
         */

        /* IDisposable.Dispose() 메서드는 다음 네 가지 작업을 수행해야 한다.
         * 1. 모든 비관리 리소스를 정리한다.
         * 2. 모든 관리 리소스를 정리한다.
         * 3. 객체가 이미 정리되었음을 나타내기 위한 상태 플래그를 설정한다. 이미 앞서 정리된 객체에 대하여 다시 한번 Dispose() 호출된 경우, 이 플래그를 확인해 ObjectDisposed 예외를 발생시킨다.
         * 4. finalizer 호출 회피, 이를 위해 GC.SuppressFinalize(this)를 호출한다.
         * 
         */


        public class Widget : IDisposable
        {
            //dispose 되었는지를 나타내는 플래그
            private bool alreadyDisposed = false;

            /// <summary>
            /// Dispose 메소드,
            /// Dispose 내에서는 절대 자원 관리를 제외한 다른 작업을 수행해선 안 된다. 객체의 생명주기의 영향을 끼치는 위험한 문제를 발생시킬 수 있다.
            /// </summary>
            public void Dispose()
            {
                Dispose(true);
                GC.SuppressFinalize(this);
            }

            /// <summary>
            /// IDisposable를 상속받은 기반클래스를 상속받은 파생클래스가 있다고 해보자.
            /// IDisposable.Dispose() 자체는 가상함수가 아니기 때문에 이를 재정의할 수는 없다.
            /// 
            /// 파생클래스의 자원을 정리하기 위해서는
            /// protected virtual void Dispose(bool)을 이용한 추가적인 작업이 필요하다. (가상헬퍼 함수 구현)
            /// 이를 통해 파생클래스에서 Dispose()나 finalizer를 구현할 때 도움을 줄 수 있다.
            /// </summary>
            /// <param name="isDisposing">true면 관리 리소스와 비관리 리소스 모두 정리, false면 비관리 리소스만 정리</param>
            protected virtual void Dispose(bool isDisposing)
            {
                //Dispose는 한 번만 수행되도록 한다.
                if (alreadyDisposed)
                {
                    return;
                }

                if (isDisposing)
                {
                    //여기서 관리 리소스를 정리
                }

                //여기서 비관리 리소스를 정리

                alreadyDisposed = true;
            }
        }

        public class DerivedWidget : Widget
        {
            /// <summary>
            /// 파생클래스의 dispose 플래그, 기반클래스와 파생클래스 따로 플래그를 가진 점이 주목할 부분인데, 이는 순전히 방어적인 코드를 작성하기 위함
            /// </summary>
            private bool disposed = false;

            protected override void Dispose(bool isDisposing)
            {
                if (disposed)
                {
                    return;
                }

                if (isDisposing)
                {
                    //여기서 관리 리소스를 정리
                }

                //여기서 비관리 리소스를 정리

                //베이스 클래스의 Dispose(bool)을 호출해. 기반클래스의 자원을 정리한다.
                //베이스 클래스는 GC.SuppressFinalize()를 호출해야 한다.
                base.Dispose(isDisposing);

                disposed = true;
            }
        }

        /// <summary>
        /// finalizer를 잘못 사용한 예시
        /// </summary>
        public class BadClass
        {
            private static readonly List<BadClass> finalizerList = new List<BadClass>();

            private string msg;

            public BadClass(string msg)
            {
                this.msg = (string)msg.Clone(); //참조를 캐싱한다.
            }

            /// <summary>
            /// 가비지에 수집 대상이 되어야 할 객체를 finalizer에서 다시 살려내는 상황.
            /// 이미 한번 finalizer가 호출되었기 때문에 GC는 두번 다시 이 객체에 대해서 finalizer를 호출하지 않을 것이다.
            /// 되살아난 객체를 정말로 삭제해려 해도 finalizer를 호출할 수 없다.
            /// </summary>
            ~BadClass()
            {
                finalizerList.Add(this);
            }
        }
    }
}