using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;
using System.Threading.Tasks;

//예외를 염두에 두고 병렬 알고리즘을 만들라
namespace MoreEffectiveCSharp
{
    /// <summary>
    /// 예외는 어떤 알고리즘에서건 처리하기가 쉽지 않으며 병렬 작업에서 더욱 복잡해진다. 
    /// 태스크 병렬 라이브러리Task Parallel Library는 AggregateException 클래스를 사용해서 병렬 알고리즘의 어딘가에서 발생하는 모든 예외를 저장한다. 
    /// 백그라운드 스레드 중 하나라도 예외를 던지면 다른 백그라운드 연산도 모두 중지된다. 
    /// 
    /// 이상적으로는 예외를 던지지 않는 코드를 작성하는 것이지만, 항상 어딘가에서 예외는 발생할 수 있다. 
    /// 따라서 모든 백그라운드 작업을 시작한 제어 스레드는 반드시 AggregateException을 대비해야 한다.
    /// 
    /// 병렬 작업은 AggregateException 타입을 사용해서 예외를 처리한다. 
    /// AggregateException은 여러 개의 예외를 담는 컨테이너로, 병렬 연산에서 발생할 수있는 모든 예외를 InnerExceptions 속성에 담을 수 있다.
    /// 
    /// 참고 : https://docs.microsoft.com/ko-kr/dotnet/standard/parallel-programming/how-to-handle-exceptions-in-parallel-loops
    /// 
    /// 전형적인 LINQ 쿼리에서는 쿼리 결과를 사용하는 코드 주변만을 try/ catch 블록으로 감싸되 LINQ 쿼리식을 정의하는 코드 주변은 감쌀 필요가 없습니다.
    /// 쿼리 구문은 기본적으로 지연 평가되며, 다른 코드가 쿼리 구문의 결과를 요구하기 전까지는 실행되지 않기 때문입니다.
    /// 
    /// 하지만 PLINQ를 사용하려면 쿼리를 정의하는 부분도 try/catch 블록으로 감싸야 한다. 
    /// 원래 예상되는 예외가 아니라 AggregateException을 잡아야 한다. 파이프라이닝, 스톱앤고, 역열거형 알고리즘 중 어느 것을 사용하든 마찬가지다. 
    /// AggregateException 예외를 잡아야 함에는 변함이 없다.
    /// </summary>
    public static class MECSharp36
    {
        private static Dictionary<Type, Action<Exception>> errorHandler = new Dictionary<Type, Action<Exception>>()
        {
            {typeof(ArgumentException), (e)=>Console.WriteLine($"ArgumentException : {e.ToString()}")},
            {typeof(NullReferenceException), (e)=>Console.WriteLine($"NullReferenceException : {e.ToString()}")},
            {typeof(ArgumentOutOfRangeException), (e)=>Console.WriteLine($"ArgumentOutOfRangeException : {e.ToString()}")},
        };

        public static void RunSample()
        {
            try
            {
                Task.Run(() => throw new Exception("Test Exception")).Wait();
            }
            catch(AggregateException ae)
            {
                //AggregateException 내부의 innerException을 순회하며 에러를 처리합니다.
                //AggregateException.Flatten 메서드는 AggregateException 내부에 중첩된 AggregateException이 있는 경우, 내부의 예외 객체들을 하나의 AggregateException 안에 평면화시킵니다. 

                var errorsCantBeHandle = new List<Exception>();
                foreach (var e in ae.Flatten().InnerExceptions)
                {
                    var type = e.GetType();
                    if(errorHandler.TryGetValue(type, out var handler))
                    {
                        //처리할 수 있는 예외는 처리합니다.
                        handler(e);
                    }
                    else
                    {
                        errorsCantBeHandle.Add(e);
                    }
                }
                if(errorsCantBeHandle.Count != 0)
                {
                    //처리할 수 없는 예외는 다시 던집니다.
                    throw new AggregateException(errorsCantBeHandle);
                }
            }
        }
    }
}
