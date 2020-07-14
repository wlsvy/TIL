using System;

//이벤트 호출 시에는 null 조건 연산자를 사용하라

namespace EffectiveCSharp
{
    /// <summary>
    /// Null 조건 연산자의 동작 방식은 연산자의 왼쪽을 평가하여 이 값이 null 이 아닌 경우에만 연산자 오른쪽의 표현식을 실행한다. 
    /// 만약 연산자 왼쪽이 null이면 아무 작업도 수행하지 않고 다음 단락으로 이동한다.
    ///
    /// If 문과 비슷해 보이지만 null 연산자는 ? 연산자의 왼쪽을 평가하고 메서드를 수행하는 과정이 원자적으로 수행된다는 점이 다르다.
    /// </summary>
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