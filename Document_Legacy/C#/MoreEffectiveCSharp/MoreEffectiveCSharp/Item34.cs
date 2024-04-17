using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;
using System.Threading.Tasks;
using System.Threading;

//비동기 메서드의 반환값을 캐시하는 경우 ValueTask<T>를 사용하라
namespace MoreEffectiveCSharp
{
    //.NET Framework 4.8에서는 ValueTask를 지원하지 않습니다. 
    /// <summary>
    /// 보통 비동기 코드의 반환 타입으로 Task나 Task<T>를 사용했습니다. 
    /// 하지만 때에 따라 Task 타입 때문에 성능이 떨어지기도 합니다. 과도한 Task 객체 생성 비용은 부담이 될 수 있습니다.
    /// 
    /// C#7이후부터는 비동기 메서드의 반환 타입으로 Task나 Task<T> 를 사용하도록 강제하지 않는다. 
    /// 대신 async 한정자를 사용하는 메서드라면 대기(Awaiter) 패턴을 따르는 타입을 반환하길 요구한다. 
    /// 이 패턴은 GetAwaiter() 메서드를 제공해야 하며, 이 메서드는 INotifyCompletion과 ICriticalNotifyCompletion 인터페이스를 구현한 객체를 반환한다. 
    /// 
    /// 최신 .NET Framework에서는 ValueTask<T>라는 새로운 타입을 제공하는데 이는 기존 Task보다 효율이 더 높다.
    /// 이 타입은 값 타입이어서 추가로 메모리를 할당할 필요가 없다(회수 비용을 줄여준다).
    /// 
    /// ValueTask<T> 타입은 비동기 메서드의 결과를 캐시해 놓고 나중에 사 용할 경우 최고의 효율을 보여준다.
    /// </summary>
    /// 

    /*
    public ValueTask<IEnumerable<WeatherData>> RetrieveHistoricalData()
    {
        if (DateTime.Now - lastReading > TimeSpan.FromMinutes(5))
        {
            return new ValueTask<IEnumerable<WeatherData>>(recentObservations);
        }
        else
        {
            async Task<IEnumerable<WeatherData>> loadCache()
            {
                recentObservations = new List<WeatherData>();
                var observationDate = this.startDate;
                while (observationDate < this.endDate)
                {
                    var observation = await RetrieveObservationData(observationDate);
                    recentObservations.Add(observation);
                    observationDate += TimeSpan.FromDays(1);
                }
                lastReading = DateTime.Now;
                return recentObservations;
            }
            return new ValueTask<IEnumerable<WeatherData>>(loadCache());
        }
    }

    */

    //ValueTask를 적용할 때
    //첫째, 이 메서드는 비동기 메서드가 아니며, 대신 ValueTask를 반환합니다. 비동기작업을 하는 지역함수는 async 한정자에 의존합니다. 
    //캐시가 유효하다면 추가적으로 상태머신관리나 객체할당을 하지 않습니다.

    //둘째, ValueTask는 Task를 인수로 받는 생성자를 제공합니다. 이를 통해 대기작업을 내부적으로 처리합니다.

}
