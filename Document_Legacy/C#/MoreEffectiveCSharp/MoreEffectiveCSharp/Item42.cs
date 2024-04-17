using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;
using System.Threading.Tasks;

//잠긴 영역에서는 외부 코드 호출을 삼가라
namespace MoreEffectiveCSharp
{
    /// <summary>
    /// 교착상태는 첫 번째 스레드가 두 번째 스레드가 종료될 때까지 대기하고 있는 상태에서, 
    /// 두 번째 스레드가 다시 첫 번째 스레드가 종료될 때를 기다리는 상황을 말한다. 
    /// 
    /// .NET Framework에서는 스레드 간 호출이 동기식 호출을 흉내내는 방식으로 마셜링되는 특수한 경우가 있다. 
    /// 이 경우 두 스레드가 사용하는 리소스에 락이 걸려 있으면 두 개의 스레드가 교착상태에 빠질 수 있다
    /// 
    /// 보호받는 코드에서 외부 코드unknown code를 호출하는 경우, 다른 스레드가 애플리케이션을 교착 상태에 빠트릴 가능성이 있다.
    /// </summary>
    public static class MECSharp42
    {
        public class WorkerClass
        {
            public event Action RaiseProgress;
            private object syncHandle = new object();
            public void DoWork()
            {
                for (int count = 0; count < 100; count++)
                {
                    lock (syncHandle)
                    {
                        System.Threading.Thread.Sleep(100);
                        RaiseProgress?.Invoke();    //이벤트에 등록된 외부 코드 호출
                    }
                }
            }
        }

        public static void RunSample()
        {

            var worker = new WorkerClass();
            worker.RaiseProgress += () => worker.DoWork();

            //worker의 락이 걸려있는 상태에서 이벤트 호출로 인해 또다시 DoWork 수행 -> 교착상태 발생
            worker.DoWork();
        }
    }
}
