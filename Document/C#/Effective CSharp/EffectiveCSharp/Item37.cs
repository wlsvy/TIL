using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;
using System.Threading.Tasks;

namespace EffectiveCSharp
{
    /// <summary>
    /// 쿼리를 사용할 때는 즉시 평가보다 지연 평가가 낫다
    /// </summary>
    public static class ECSharp37
    {
        /* 쿼리를 정의한다고 해서 결과 데이터나 시퀀스를 즉각적으로 얻어오는 것은 아니다
         * 실제로는 쿼리를 정의하는 작업은 수행 시에 어떤 과정으로 작업을 수행할지에 대한 절차만을 정의하는 것
         * 
         * 정의된 절차에 따라 순회를 수행해야만 결과가 수행된다. 이를 지연평가 lazy evaluation라고 한다.
         * 
         * 하지만 가끔은 이러한 동작 방식이 적절하지 않은 경우도 있다. 
         * 마치 일반 변수를 사용하는 것처럼 즉각적으로 그 값을 얻어와야 할 때도 있다.
         * 이를 즉시 평가 eager evaluation 라고 한다.
         */ 

        private static IEnumerable<TResult> Generate<TResult>(int number, Func<TResult> generator)
        {
            for(var i = 0; i < number; i++)
            {
                yield return generator();
            }
        }

        /// <summary>
        /// 지연평가 예시. 시행되는 시간에 따라 출력 결과가 바뀐다.
        /// 
        /// 시퀀스는 특정 값 그 자체를 가지고 있는 것이 아니라 시퀀스 내의 개별 요소들을 생성하는 방법을 나타내는 코드를 갖고 있기 때문이다.
        /// </summary>
        private static void LazyEvaluation()
        {
            Console.WriteLine($"Start time for Test One : {DateTime.Now:T}");
            var sequence = Generate(10, () => DateTime.Now);

            Console.WriteLine("Waiting...\tPress Return");
            Console.ReadLine();

            Console.WriteLine("Iterating...");
            foreach(var value in sequence)
            {
                Console.WriteLine($"{value:T}");
            }

            Console.WriteLine("Waiting...\tPress Return");
            Console.ReadLine();

            Console.WriteLine("Iterating...");
            foreach(var value in sequence)
            {
                Console.WriteLine($"{value:T}");
            }
        }

        private static IEnumerable<int> AllNumbers()
        {
            var number = 0;
            while(number < int.MaxValue)
            {
                yield return number++;
            }
        }

        public static void RunSample()
        {
            LazyEvaluation();

            /* 아래 sequence1과 sequence2는 데이터를 공유하는 것이 아니라 내부적으로 함수를 합성하여 수행된다.
             * 
             * sequence1이 이미 생성해둔 값을 순회하면서 개별 요소를 수정하는 것이 아니라, 
             * 순회 시점에 맞춰 sequence1에서 지정한 코드를 호출하여 그 결과를 얻은 후 세계 공용 포맷으로 변경하는 것.
             * 
             * 쿼리 표현식은 이처럼 지연 평가를 수행하기 때문에 이론적으로 무한 시퀀스를 표현하는 것이 가능하다.
             * 또한 시퀀스의 첫 번째 값부터 시작하여 중간에 적절한 값을 만나면 작업을 중단하도록 코드를 작성할 수도 있다.
             */
            var sequence1 = Generate(10, () => DateTime.Now);
            var sequence2 = from value in sequence1
                            select value.ToUniversalTime();

            /* 쿼리를 수행할 때 전체 시퀀스가 필요하지 않은 예
             * Take() 메서드를 통해 처음부터 N개의 객체를 반환하는 작업을 한다.
             */ 
            var answers = from number in AllNumbers()
                          select number;
            var smallNumbers = answers.Take(10);
            foreach(var num in smallNumbers)
            {
                Console.WriteLine(num);
            }

            /* 아래의 코드는 영원히 끝나지 않는다. (AllNumbers() 에서 오버플로우 발생)
             * 
             * 쿼리 구문을 수행하기 위해서 시퀀스 내의 모든 값을 대상으로 비교 연산을 수행해야 하기 때문이다.
             * 위의 코드와 동일한 작업을 하지만 전체 시퀀스가 필요한 경우에 해당한다.
             */
            /*
            var answers = from number in AllNumbers()
                          where number < 10
                          select number;
            */

            /* 전체 시퀀스가 필요한 메서드를 다룰 때에는 반드시 염두에 두어야 할 사항이 있다.
             * 1. 시퀀스가 무한정으로 지속될 가능성이 있다면 사용할 수 없다.
             * 2. 시퀀스가 무한이 아니더라도 시퀀스를 필터링하는 쿼리 메소드는 다른 쿼리보다 먼저 수행하는 것이 좋다.
             * - 선행 단계에서 컬렉션의 요소를 필터링하여 그 개수를 줄일 수 있다면 다음으로 수행할 쿼리의 성능을 개선할 수 있기 때문이다.
             * 
             * 아래의 경우 두번째 쿼리가 더 빠르다. 필터링된 시퀀스에 대해서만 정렬을 수행하기 때문이다.
             */

            var sortedProductsSlow = from p in Enumerable.Range(1, 100000)
                                     orderby p descending
                                     where p < 100
                                     select p;
            var sortedProductsFast = from p in Enumerable.Range(1, 100000)
                                     where p < 100
                                     orderby p descending
                                     select p;


            /* 즉시 평가를 하고 싶은 경우, ToArray() 혹은 ToList() 메서드를 활용하면 된다.
             * 
             * 즉시 평가는 크게 두 가지 경우에 유용한데
             * 1. 시퀀스를 순회하기 전에 실제 데이터의 스냅샷을 얻고자 하는 경우
             * 2. 쿼리의 결과가 변하지 않고 동일한 값을 반환할 때 결과값을 캐싱하여 반복적으로 사용하는 경우.
             */
        }
    }
}