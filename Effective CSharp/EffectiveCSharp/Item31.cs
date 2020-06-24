using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;
using System.Threading.Tasks;

namespace EffectiveCSharp
{
    /// <summary>
    /// 시퀀스에 사용할 수 있는 조합 가능한 API를 작성하라
    /// </summary>
    public static class ECSharp31
    {
        /// <summary>
        /// 중복된 값을 제외한 시퀀스 원소를 출력하는 메서드
        /// </summary>
        public static void WriteUnique(IEnumerable<int> nums)
        {
            var uniqueVals = new HashSet<int>();

            foreach(var num in nums)
            {
                if (!uniqueVals.Contains(num))
                {
                    uniqueVals.Add(num);
                    Console.WriteLine(num);
                }
            }
        }

        /// <summary>
        /// IEnumerable  을 반환하는 메서드
        /// </summary>
        public static IEnumerable<int> Unique(IEnumerable<int> nums)
        {
            var uniqueVals = new HashSet<int>();

            foreach(var num in nums)
            {
                if (!uniqueVals.Contains(num))
                {
                    uniqueVals.Add(num);
                    yield return num;
                }
            }
        }

        /// <summary>
        /// 현재 동작 상태를 나타내는 메세지 추가
        /// 
        /// yield return 문의 경우, 값을 반환한 후 내부적으로 사용하는 이터레이터의 형재 위치와 상태 정보를 저장한다.
        /// 전체 시퀀스에 대하여 수행해야 할 메서드는 입력과 출력이 모두 이터레이터이다. 
        /// 
        /// 순회 과정은 내부적으로 입력 시퀀스의 현재 위치를 계속 갱신해가면서 출력 시퀀스에 차례차례 그 결과를 반환하는 과정이다.
        /// 
        /// 이러한 메서드를 컨티뉴어블 메서드 continuable method 라고도 한다.
        /// 컨티뉴어블 메서드란 현재의 수행 상태를 보전하고 있어서 메서드로 재진입 시 이전에 수행한 코드 이후부터 수행을 이어갈 수 있는 메서드를 말한다.
        /// </summary>
        public static IEnumerable<int> Unique2(IEnumerable<int> nums)
        {
            var uniqueVals = new HashSet<int>();
            Console.WriteLine("\tEntering Unique");

            foreach (var num in nums)
            {
                Console.WriteLine($"\tTesting {num.ToString()}");
                if (!uniqueVals.Contains(num))
                {
                    Console.WriteLine($"\tAdding {num.ToString()}");
                    uniqueVals.Add(num);

                    yield return num;
                    Console.WriteLine($"\tRe-entering after yield return");
                }
            }

            Console.WriteLine("\tExiting Unique");
        }

        public static IEnumerable<int> Square(IEnumerable<int> nums)
        {
            foreach(var num in nums)
            {
                yield return num * num;
            }
        }

        public static void RunSample()
        {
            var numbers = new List<int>() { 1, 2, 3, 3, 4, 4, 4, 5, 6, 7, 7, 7, 7 };

            WriteUnique(numbers);

            foreach(var n in Unique2(numbers))
            {
                Console.WriteLine(n);
            }

            /* 이터레이터 메서드의 진정한 힘은 여러 단계를 거쳐서 처리돼야 하는 작업을 수행하는 경우에 빛을 발한다.
             * 아래의 경우 다수의 이터레이터를 조합해서 사용한다.
             * 
             * 여러 개의 이터레이터가 사용됐지만 단 한번의 순회 과정을 통해 여러 작업이 단번에 수행된다.
             */
            foreach (var n in Square(Unique(numbers)))
            {
                Console.WriteLine($"Number returned from Unique : {n.ToString()}");
            }
        }

        /// <summary>
        /// Zip은 두 개의 문자열 시퀀스를 전달받아 이를 결합한 후 단일의 출력 시퀀스로 내보낸다.
        /// 
        /// 다수의 입력 시퀀스를 활용하는 또 다른 예
        /// </summary>
        public static IEnumerable<string> Zip<T>(IEnumerable<string> first, IEnumerable<string> second)
        {
            using(var firstSequence = first.GetEnumerator())
            {
                using (var secondSequence = second.GetEnumerator())
                {
                    while(firstSequence.MoveNext() && secondSequence.MoveNext())
                    {
                        yield return $"{firstSequence.Current} {secondSequence.Current}";
                    }
                }
            }
        }
    }
}