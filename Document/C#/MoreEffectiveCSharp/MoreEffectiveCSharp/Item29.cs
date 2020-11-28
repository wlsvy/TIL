using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;
using System.Threading.Tasks;

//동기, 비동기 메서드를 함께 사용해서는 안된다
namespace MoreEffectiveCSharp
{
    /// <summary>
    /// async 한정자를 사용해 선언한 메서드는 작업을 마치기전에 객체를 반환할 수 있음을 나타내며, 이렇게 반환된 객체는 요청한 작업의 상태를 나타냅니다. 
    /// 작업 완료, 실패, 혹은 대기 중등 다양한 상태가 될 수 있습니다. 
    /// 
    /// 또한 비동기 메서드를 사용한다는 것은 작업이 오래 걸릴 수 있으니 호출자는 그동안 다른 일을 할 수 있습니다.
    /// 
    /// 메서드를 동기로 선언한다는 것은, 메서드가 반환되기만 하면 모든 사후 조건을 충족한다는 것을 의미합니다.
    /// 동기 메서드는 작업을 수행하는 시간에 상관없이 호출자와 같은 리소스를 사용해서 모든 작업을 완료합니다. 그리고 호출자는 작업이 끝날 때까지 멈춥니다.
    /// 
    /// 
    /// 서로 다른 두 방식을 섞어 사용하면 교착상태와 같은 오류로 이어질 수 있습니다. 이런 가능성을 피하기위해서
    /// 첫째, 비동기작업이 완료될 때까지 기다리는 동기 메서드를 만들지 말것
    /// 단, 한 가지 예외가 있는데 진입점 Main() 메서드는 반드시 동기 메서드여야 합니다. Main()이 끝나면 프로그램이 종료되기 때문입니다.
    /// 
    /// 둘째, 수행 시간이 오래 걸리는 CPU 중심 작업을 비동기로 수행하지 말것
    /// CPU 중심작업이 동기로 수행될 때 사용자는 이를 그저 동기적으로 진행시킬 지 아니면 중간에 다른 스레드를 활용해 비동기로 수행할지 결정할 수 있습니다.
    /// 하지만 중심작업을 비동기로 진행한다면 이런 선택을 할 수가 없습니다.
    /// 
    /// </summary>
    public static class MECSharp29
    {
        private static async Task SimulatedWorkAsync()
        {
            //오랫동안 수행되는 작업을 흉내 내기 위해서 Thread. Sleep() 대신에 Task.Delay()를 사용했습니다. 
            //Thread.Sleep()은 스레드가 유휴 상태idle가 되면 리소스를 소비하기 때문에 Task.Delay()를 사용하는 것이 좋습니다.
            //Task.Delay()는 비동기로 동작하기 때문에, 오랫동안 수행되는 작업을 흉내 낸다고 하더라도, 호출 측에서 다른 작업을 수행할 수 있게 해줍니다.
            await Task.Delay(1000);
        }

        // 이 메서드는 ASP.NET이나 GUI에서는 교착상태에 빠질 수 있습니다. 
        private static void SyncOverAsyncDeadlock()
        {
            // 태스크 시작 
            var delayTask = SimulatedWorkAsync(); 
            // delay가 끝날 때까지 동기식으로 기다립니다. 
            delayTask.Wait();
        }

        public static void RunSample()
        {
            //SyncOverAsyncDeadlock ( )은 콘솔 애플리케이션에서라면 제대로 실행되지만 GUI 나 웹 환경에서는 교착상태에 빠질 것입니다.
            //콘솔 애플리케이션용 SynchronizationContext는 스레드 풀에서 여러 스레드를 사용하지만, GUI와 ASP.NET용 SynchronizationContext는 스레드를 하나만 가질 수 있기 때문입니다.
            SyncOverAsyncDeadlock();
        }
    }
}
