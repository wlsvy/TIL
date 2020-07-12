using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;
using System.Threading.Tasks;

namespace EffectiveCSharp
{
    /// <summary>
    /// 루프보다 쿼리 구문이 낫다
    /// </summary>
    public static class ECSharp30
    {
        /* C#의 흐름을 제어하는 for, while, do/while, foreach 등 다양한 반복 구문을 활용할 수 있지만, 
         * 이런 반복문 보다 쿼리 구문을 사용하는 것이 더 나은 경우가 꽤 있다.
         * 
         * 쿼리 구문을 사용하면 프로그램의 논리를 명령형 방식에서 선언적인 방식으로 전환할 수 있다.
         * 쿼리 구문을 이용하면 질의의 내용을 구성할 수 있을 뿐 아니라 개별 항목에 대해 수행하려는 작업의 수행 시기를 연기할 수 있다.
         * 
         * 뿐만 아니라 쿼리 구문이나 메서드 호출 구문을 확장하여 사용하면 루프를 이용하는 것보다 사용자의 의도를 더 명확하게 드러낼 수 있는 부가적인 장점도 있다.
         */ 

        /// <summary>
        /// IEnumerable에 대한 간단한 확장 메서드
        /// </summary>
        public static void ForAll<T>(this IEnumerable<T> sequence, Action<T> action)
        {
            foreach(T item in sequence)
            {
                action(item);
            }
        }

        public static void RunSample()
        {
            {
                var foo = new int[5];

                for (var num = 0; num < foo.Length; num++)
                {
                    foo[num] = num * num;
                }

                foreach (int i in foo)
                {
                    Console.WriteLine(i.ToString());
                }
            }

            /* 위의 코드를 아래와 같은 방식으로 바꿀 수 있다.
             * 
             */
            {
                var foo = from n in Enumerable.Range(0, 5)
                           select n * n;

                foo.ForAll((n) => Console.WriteLine(n.ToString()));
            }
        }

        /// <summary>
        /// 0~99 까지 좌표를 생성하는 예시를 보자
        /// 명령형으로 구현한 코드
        /// </summary>
        private static IEnumerable<Tuple<int, int>> ProduceIndices()
        {
            for(var x= 0; x < 100; x++)
            {
                for(var y = 0; y < 100; y++)
                {
                    yield return Tuple.Create(x, y);
                }
            }
        }

        /// <summary>
        /// 쿼리 구문을 활용한 예시
        /// 
        /// 둘은 유사해 보이지만 쿼리 구문은 문제의 유형이 복잡해지더라도 단순함은 그대로 유지할 수 있는 장점이 있다.
        /// </summary>
        private static IEnumerable<Tuple<int, int>> QueryIndices()
        {
            return from x in Enumerable.Range(0, 100)
                   from y in Enumerable.Range(0, 100)
                   select Tuple.Create(x, y);
        }

        //X, Y 의 합이 100보다 작은 경우에 해당하는 쌍만을 반환하도록 고쳐보자.

        private static IEnumerable<Tuple<int, int>> ProduceIndices2()
        {
            for (var x = 0; x < 100; x++)
            {
                for (var y = 0; y < 100; y++)
                {
                    if(x + y < 100)
                    {
                        yield return Tuple.Create(x, y);
                    }
                }
            }
        }

        private static IEnumerable<Tuple<int, int>> QueryIndices2()
        {
            return from x in Enumerable.Range(0, 100)
                   from y in Enumerable.Range(0, 100)
                   where x + y < 100
                   select Tuple.Create(x, y);
        }

        //또 바꿔서 이번에는 ( 0, 0 ) 에서 떨어진 거리 순으로 정렬하여 객체를 반환해 보자.

        /// <summary>
        /// 어우야....
        /// </summary>
        private static IEnumerable<Tuple<int, int>> ProduceIndices3()
        {
            var storage = new List<Tuple<int, int>>();

            for (var x = 0; x < 100; x++)
            {
                for (var y = 0; y < 100; y++)
                {
                    if (x + y < 100)
                    {
                        storage.Add(Tuple.Create(x, y));
                    }
                }
            }

            storage.Sort((p1, p2) =>
                (p2.Item1 * p2.Item1 + p2.Item2 * p2.Item2).CompareTo(p1.Item1 * p1.Item1 + p1.Item2 * p1.Item2)
            );
            return storage;
        }

        /// <summary>
        /// 쿼리의 장점이 드러나고 있다. 
        /// </summary>
        private static IEnumerable<Tuple<int, int>> QueryIndices3()
        {
            return from x in Enumerable.Range(0, 100)
                   from y in Enumerable.Range(0, 100)
                   where x + y < 100
                   orderby (x * x + y * y) descending
                   select Tuple.Create(x, y);

            //위의 방식은 메소드 호출 방식으로 바꿔서 표현할 수도 있다.

            return Enumerable.Range(0, 100).
                SelectMany(val => Enumerable.Range(0, 100), (x, y) => Tuple.Create(x, y)).
                Where(pt => pt.Item1 + pt.Item2 < 100).
                OrderByDescending(pt => pt.Item1 * pt.Item1 + pt.Item2 * pt.Item2);
        }
    }
}