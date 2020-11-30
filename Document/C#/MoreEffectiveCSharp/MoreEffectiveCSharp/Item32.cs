using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;
using System.Threading.Tasks;
using System.Threading;

//비동기 작업은 태스크 객체를 사용해 구현하라
namespace MoreEffectiveCSharp
{
    /// <summary>
    /// 태스크는 다른 리소스(주로 스레드)에 작업을 위임할 수 있도록 추상화한 개념입니다.
    /// 관련된 풍부한 API를 제공하므로, 다른 곳으로 위임한 태스크와 수행할 작업을 손쉽게 다룰 수 있습니다. 
    /// 
    /// 태스크 또한 객체이며 여러 태스크를 모아서 거대한 태스크로 묶을 수도 있습니다. 
    /// 거대한 태스크에 속한 작은 태스크들은 순서대로 혹은 병렬로 실행할 수 있습니다. 
    /// 
    /// await 구문으로는 순서를 강제할 수 있습니다. 즉, await 구문을 만난 코드는 기다리는 태스크가 완료될 때까지 실행이 멈추게 됩니다. 
    /// 따라서 이전 태스크의 수행이 완료된 이후에 수행되는 태스크를 만들 수도 있습니다.
    /// </summary>
    /// 
    public static class MECSharp32
    {
        private class Widget { }
        private static async Task<Widget> CreateWidget(string symbol)
        {
            for(decimal d = 0; d < 1000000000; d++) { }

            return await Task.Run(() => new Widget());
        }

        private static class Case0
        {
            //이 태스크들은 독립적이므로 각 태스크가 끝나기를 기다렸다가 다음 태스크를 실행할 필요가 없습니다. 
            //따라서 모든 태스크를 동시에 시작한 후 태스크들이 모두 끝나기를 기다렸다가 컨티뉴에 이션이 실행되도록 수정할 수 있을 것입니다.
            public static async Task<IEnumerable<Widget>> DoSomething(IEnumerable<string> symbols) 
            { 
                var results = new List<Widget>(); 
                foreach (var symbol in symbols) 
                { 
                    var result = await CreateWidget(symbol); 
                    results.Add(result); 
                } 
                return results; 
            }

            //WhenAll은 매개변수로 넘어간 모든 Task가 완료되야 끝나는 새로운 Task를 만듭니다. 그리고 완료된(실패한 태스크 포함) 모든 태스크를 배열에 담아 반환합니다.
            public static async Task<IEnumerable<Widget>> DoSomething2(IEnumerable<string> symbols)
            {
                var resultTasks = new List<Task<Widget>>();
                foreach (var symbol in symbols)
                {
                    resultTasks.Add(CreateWidget(symbol));
                }
                return await Task.WhenAll(resultTasks);
            }
            //WhenAny는 매개변수로 넘어간 Task 중 하나가 완료될 시 실행을 완료하는 태스크를 반환합니다.
            public static async Task<Widget> DoSomething3(IEnumerable<string> symbols)
            {
                var resultTasks = new List<Task<Widget>>();
                foreach (var symbol in symbols)
                {
                    resultTasks.Add(CreateWidget(symbol));
                }
                return await await Task.WhenAny(resultTasks);
            }
        }

        private static class Case1
        {
            //태스크가 완료된 순서대로 해당 결과가 목적지 배열에 차례차레 할당되게 됩니다.
            public static Task<T>[] OrderByCompletion<T>(IEnumerable<Task<T>> tasks)
            {
                // 여러 번 열거되기 때문에 리스트에 복사. 
                var sourceTasks = tasks.ToList(); //출발지 태스크

                // 각 목적지 태스크는 각 TaskCompletionSource와 연결됩니다. 
                var completionSources = new TaskCompletionSource<T>[sourceTasks.Count];
                var outputTasks = new Task<T>[completionSources.Length];    //목적지 태스크

                for (int i = 0; i < completionSources.Length; i++)
                {
                    completionSources[i] = new TaskCompletionSource<T>();
                    outputTasks[i] = completionSources[i].Task;
                }

                // 각 태스크가 가지고 있는 컨티뉴에이션은 자신의 결과를 completionSources 배열의 다음 위치에 저장합니다. 
                int nextTaskIndex = -1;
                Action<Task<T>> continuation = completed =>
                {
                    var bucket = completionSources[Interlocked.Increment(ref nextTaskIndex)];
                    if (completed.IsCompleted)
                    {
                        bucket.TrySetResult(completed.Result);
                    }
                    else if (completed.IsFaulted)
                    {
                        bucket.TrySetException(completed.Exception);
                    }
                };

                // 각 입력 태스크에 컨티뉴에이션을 설정하여 결과 태스크와 연결한다. 
                // 각 태스크가 끝나면 다음 빈 공간을 사용한다. 
                foreach (var inputTask in sourceTasks)
                {
                    inputTask.ContinueWith(continuation, CancellationToken.None, TaskContinuationOptions.ExecuteSynchronously, TaskScheduler.Default);
                }
                return outputTasks;
            }
        }
    }
}
