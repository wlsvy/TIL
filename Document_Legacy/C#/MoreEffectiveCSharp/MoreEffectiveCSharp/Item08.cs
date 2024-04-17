using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;
using System.Threading.Tasks;

//익명 타입은 함수를 벗어나지 않게 사용하라
namespace MoreEffectiveCSharp
{
    public static class MECSharp08
    {
        //아래는 특정 메서드의 반환 타입으로 튜플을 사용하는 케이스입니다.
        //메서드의 반환 타입으로 튜플을 활용하기는 쉽습니다.
        private static (T sought, int index) FindFirstOccurrence<T>(IEnumerable<T> enumerable, T value)
        {
            int index = 0;
            foreach(T element in enumerable)
            {
                if (element.Equals(value))
                {
                    return (value, index);
                }
                index++;
            }
            return (default(T), -1); //튜플을 생성해 반환합니다.
        }

        private static void RunTupleSample()
        {
            var list = new List<int>() { 1, 2, 3, 4, 5, 6, 7, 8, 9, 10, 42 };

            //결과를 튜플 변수에 할당
            var result = FindFirstOccurrence(list, 42);
            Console.WriteLine($"First {result.sought.ToString()} is at {result.index.ToString()}");

            //결과를 각기 다른 변수에 할당
            (int number, int index) = FindFirstOccurrence(list, 42);
            Console.WriteLine($"First {number} is at {index}");
        }

        private static IEnumerable<T> FindValue<T>(IEnumerable<T> enumerable, T value)
        {
            foreach(T element in enumerable)
            {
                if (element.Equals(value))
                {
                    yield return element;
                }
            }
        }

        /// <summary>
        /// 익명 타입을 활용하는 예제
        /// 
        /// 익명 타입은 이름을 코드로 입력할 수 없기 때문에 메서드의 반환 타입으로 활용하기 쉽지 않습니다.
        /// 
        /// 고차함수(higher-order function, 함수를 매개변수로 취하거나 반환하는 함수)를 작성하는 경우, 익명타입을 다루기가 유용합니다.
        /// </summary>
        private static void RunAnonymousTypeSample()
        {
            IDictionary<int, string> numberDescriptionDictionary = new Dictionary<int, string>()
            {
                {1, "one" },
                {2, "two" },
                {3, "three" },
                {4, "four" },
                {5, "five" },
                {6, "six" },
                {7, "seven" },
                {8, "eight" },
                {9, "nine" },
                {10, "ten" },
            };
            List<int> numbers = new List<int>() { 1, 2, 3, 4, 5, 6, 7, 8, 9, 10 };

            var result = from n in numbers
                    where n % 2 == 0
                    select new
                    {
                        Number = n,
                        Description = numberDescriptionDictionary[n]
                    };

            result = from n in FindValue(result, new { Number = 2, Description = "two" })
                select n;
        }

        private static void RunAnonymousTypeSample2()
        {
            var randomNumber = new Random();
            var doubleList = new List<double>();
            for (int i = 0; i < 100; i++)
            {
                doubleList.Add(randomNumber.NextDouble() * 100);
            }


            var sequence = from x in doubleList
                           let y = randomNumber.NextDouble() * 100
                           select new { x, y };
            sequence = sequence.TakeWhile(point => point.x < 75);

            var scaled = from p in sequence
                         select new { x = p.x * 5, y = p.y * 5 };
            var translated = from p in scaled
                             select new { x = p.x - 20, y = p.y - 20 };
            var distances = from p in translated
                            let distance = Math.Sqrt(p.x * p.x + p.y * p.y)
                            where distance < 500.0
                            select new { p.x, p.y, distance };
        }

        //위의 코드에서 반복되는 코드는 아래의 방법으로 묶을 수 있습니다.
        //익명 타입에 대한 최소한의 정보만을 가지고도 수행될 수 있도록 알고리즘을 분리하는 것이 중요합니다.
        private static IEnumerable<TResult> Map<TSource, TResult>(this IEnumerable<TSource> source, Func<TSource, TResult> mapFunc)
        {
            foreach(TSource s in source)
            {
                yield return mapFunc(s);
            }
        }
        private static void RunAnonymousTypeSample3()
        {
            var randomNumber = new Random();
            var doubleList = new List<double>();
            for (int i = 0; i < 100; i++)
            {
                doubleList.Add(randomNumber.NextDouble() * 100);
            }

            var sequence = (from x in doubleList
                            let y = randomNumber.NextDouble() * 100
                            select new { x, y }).
                            TakeWhile(point => point.x < 75);
            
            var scaled = sequence.Map(
                p => new {
                    x = p.x * 5,
                    y = p.y * 5
                });
            var translated = scaled.Map(
                p => new {
                    x = p.x - 20,
                    y = p.y - 20
                });
            var distances = translated.Map(
                p => new {
                    p.x,
                    p.y,
                    distance = Math.Sqrt(p.x * p.x + p.y * p.y)
                });
            var filtered = from location in distances
                           where location.distance < 500.0
                           select location;
        }


        public static void RunSample()
        {
            RunTupleSample();
            RunAnonymousTypeSample();
            RunAnonymousTypeSample2();
            RunAnonymousTypeSample3();
        }
    }
}
