using System;

//이벤트 호출 시에는 null 조건 연산자를 사용하라

namespace EffectiveCSharp
{
    public class ECSharp08
    {
        int counter = 0;
        Action<object, int> Updated = null;

        /// <summary>
        /// Updated 델리게이트의 null 검사 후 실행
        /// 
        /// 하지만 멀티스레드 환경에서는 문제의 소지가 있는 코드
        /// 널 체크를 한 뒤 델리게이트를 실행하기 전에, 다른 스레드에서 델리게이트를 null로 만들 수 있다.
        /// </summary>
        public void RaiseUpdates()
        {
            counter++;
            if (Updated != null)
            {
                Updated(this, counter); 
            }
        }

        public void SafeRaiseUpdates()
        {
            counter++;
            var handler = Updated;
            if (handler != null)
            {
                handler(this, counter); //안전하게 명령을 수행하는 코드, 하지만 가독성이 떨어진다
            }
        }

        public void SimpleRaiseUpdates()
        {
            counter++;
            Updated?.Invoke(this, counter); //null 조건 연산자를 활용한 안전하고 간단한 코드. 
        }
    }
}