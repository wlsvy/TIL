using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;
using System.Threading.Tasks;

namespace EffectiveCSharp
{
    /// <summary>
    /// 메서드가 실패했음을 알리기 위해서 예외를 이용하라
    /// </summary>
    public static class ECSharp45
    {
        /* 런타임에 발생하는 예외는 상당히 비용이 클뿐만 아니라 이에 대응하는 코드를 작성하는 것이 쉽지 않습니다.
         * 개발자가 try/catch 블록을 작성하지 않고도 정상적으로 메서드가 수행될 수 있는지를 확인할 수 있는 API제공하는 것이 좋습니다.
         * 
         * 오류를 보고하는 매커니즘의 관점에서 보자면 반환 코들르 이용하여 오류를 보고하는 방식보다 예외를 이용하는 방식이 장점이 더 많습니다.
         * 반환 코드를 이용한다면 메서드의 원형에 영향을 미치며 보통 반환 코드는 계산의 결과를 나타내는 용도로 주로 사용됩니다.
         * 그 탓에 오류가 발생했다는 사실 이외에 추가적인 정보를 전달하기 어렵습니다.
         * 
         * 이에 비해 예외는 클래스 타입이므로 개발자가 자신만의 예외 타입을 파생시킬 수 있으며 오류에 대한 추가적인 정보를 제공할 수 있습니다.
         * 
         * 특정 메서드가 작업을 온전히 완료할 수 없을 경우 예외를 발생시킬지를 결정하는 것은 개발자의 몫입니다. 
         * 하지만 오류가 발생하면 항상 예외를 발생시키도록 코드를 작성하는 것이 좋습니다.
         * 
         * 다만 예외는 일반적인 흐름 제어 매커니즘으로 사용해서는 안됩니다. 
         * 그리고 요청된 작업이 성공적으로 수행될 수 있는지를 사전에 테스트할 수 있는 메서드를 같이 제공하는 것이 좋습니다.
         */ 

        public class DoesWorkThatMightFail
        {
            public void DoWork()
            {
                //여기서 작업을 수행하는데 실패하면 큰 문제가 발생합니다.
                Work();
            }

            public bool TryDoWork()
            {
                if (TestConditions())
                {
                    return false;
                }

                //조건을 검사하고 작업을 수행합니다. 여전히 오류가 발생할 가능성이 있지만 사전에 검사를 진행하여 훨씬 안전합니다.
                Work();
                return true;
            }

            private bool TestConditions()
            {
                //여기서 수행 조건을 검사합니다.
                return true;
            }

            private void Work()
            {
                //여기서 오류가 발생할 수 있는 임의의 작업을 수행합니다.
            }
        }

        public static void ReportErrorToUser(string msg)
        {
            Console.WriteLine(msg);
        }

        public static void RunSample()
        {
            DoesWorkThatMightFail worker = new DoesWorkThatMightFail();

            //위의 클래스를 활용하는 사용자는 아래처럼 코드를 작성할 수 있습니다.
            //이런 패턴은 외부 코드로부터 전달된 매개변수를 사용해야 하는 경우 상당히 도움이 됩니다.
            if (!worker.TryDoWork())
            {
                ReportErrorToUser("Test Conditions Failed. Please Check widgets");
            }
        }
    }
}