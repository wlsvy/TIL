using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;
using System.Threading.Tasks;

namespace EffectiveCSharp
{
    /// <summary>
    /// 필요한 시점에 필요한 요소를 생성하라
    /// </summary>
    public static class ECSharp33
    {
        /* 이터레이터 메서드가 입력 매개변수로 반드시 시퀀스를 전달받아야 할 필요는 없다.
         * 
         * 이터레이터 메서드에서 yield return 을 사용하는 과정에서 입력 시퀀스를 활용하는 대신 새로운 요소를 생성하는 팩토리 메서드를 사용할 수도 있다.
         * 작업을 수행하기 전에 필요한 요소를 모두 생성해서 컬렉션에 저장해두는 대신 필요할 때마다 개별 요소를 생성하는 식이다.
         * 
         */

        /// <summary>
        /// 단점이 많은 코드 
        /// 
        /// 결과를 반드시 List<int> 에 저장한다고 가정하고 있다.
        /// 
        /// 또한 클라이언트가 중간에 작업을 중단할 수 없기 때문에 CreateList() 메서드는 항상 요청된 개수만큼 요소를 생성한다.
        /// 사용자가 페이징이나 혹은 다른 이유로 작업을 중단하고 싶어도 방법이 없다.
        /// 
        /// 시퀀스 내의 요소들을 모두 생성할 때까지 다음 단계를 진행할 수 없기 때문에 전체 파이프라인의 병목 구간이 된다.
        /// </summary>
        public static IList<int> CreateList(int numberOfElements, int startAt, int stepBy)
        {
            var collection = new List<int>(numberOfElements);
            for(int i = 0; i < numberOfElements; i++)
            {
                collection.Add((startAt + i * stepBy));
            }

            return collection;
        }
        /// <summary>
        /// 시퀀스를 생성하는 기능을 이터레이터 메서드로 만들면 이런 문제들을 피할 수 있다.
        /// 
        /// 이 코드를 실행하면 시퀀스 내의 개별 요소가 요청 시마다 하나씩 생성된다.
        /// 클라이언트가 값을 어떤 컬렉션에 저장하더라도 문제없이 동작하며, 
        /// 만약 클라이언트가 생성된 시퀀스를 List<int> 에 저장하고 싶다면 IEnumerable<int>를 매개변수로 취하는 생성자를 사용하면 된다.
        /// </summary>
        public static IEnumerable<int> CreateSequence(int numberOfElements, int startAt, int stepBy)
        {
            for(var i = 0; i < numberOfElements; i++)
            {
                yield return startAt + i * stepBy;
            }
        }

        public static void RunSample()
        {
            var storage = new List<int>(CreateSequence(100, 0, 5));

            /* 다음과 같이 코드를 작성하면 시퀀스에 대한 순회 과정을 쉽게 중단할 수도 있다.
             * CreateList를 사용했다면 호출 측에서 리스트에 대한 생성을 언제 멈출지와 상관없이 항상 1,000개의 요소가 모두 생성된다.
             * 하지만 CreateSequence를 사용한다면 조건에 부합하지 않는 상황이 됐을 때 추가로 숫자를 생성하지 않으므로 성능상에 이점이 있다.
             * 
             * 지연 실행deferred execution 이라고 볼 수 있으며, 즉 필요한 시점에 필요한 요소를 생성하는 것이다.
             * 
             */ 
            var sequence = CreateSequence(10000, 0, 7).
                TakeWhile((num) => num < 1000);
        }
    }
}
