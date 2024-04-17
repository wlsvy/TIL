using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;
using System.Threading.Tasks;
using System.Threading;

//지역 함수를 사용해서 반복자와 비동기 메서드의 오류를 즉시 보고하라
namespace MoreEffectiveCSharp
{
    public static class MECSharp26
    {
        //이상적이라면 발생되는 오류는 즉시 보고되어야 합니다. 잘못 사용하였다면 즉각 파악할 수 있어야 실수를 쉽게 수정할 수 있습니다.
        //아래는 메서드의 특징에 의해 오류 보고가 지연되는 예시입니다.
        private static class Case0
        {
            public static IEnumerable<T> GenerateSample<T>(IEnumerable<T> sequence, int sampleFrequency )
            {
                if(sequence == null)
                {
                    throw new ArgumentException("null sequence");
                }
                if(sampleFrequency < 1)
                {
                    throw new ArgumentException("Sample Frequency must be a positive integer");
                }

                int index = 0;
                foreach(T item in sequence)
                {
                    if(index % sampleFrequency == 0)
                    {
                        yield return item;
                    }
                }
            }

            //async 한정자는 컴파일러에게 메서드 안의 코드를 재구성하여 비동기 작업의 상태를 관리하는 태스크 객체를 반환하라고 지시합니다.
            //해당 태스크가 대기 상태일 때만 해당 메서드에서 발생하는 예외를 감지할 수 있습니다.
            public static async Task<string> LoadMessage(string userName)
            {
                if (string.IsNullOrWhiteSpace(userName))
                {
                    throw new ArgumentException("this must be a valid user");
                }

                return await Task.Run(() => "user");
            }

            public static void RunSample()
            {
                //반복자 메서드가 호출될 때는 잘못된 인수로 인한 예외가 발생하지 않습니다. 해당 시퀀스를 순회할 때 예외가 발생합니다.
                //코드 규모가 커질 때 오류가 발생한 원인을 찾기 어려울 수 있습니다.
                var samples = GenerateSample(new int[]{ 1, 2, 3, 4, 5}, -1);
                Console.WriteLine("Exception is not thrown yet");

                try
                {
                    foreach (var item in samples)   //여기서 예외가 발생합니다.
                    {
                        Console.WriteLine(item);
                    }
                }
                catch
                {
                    Console.WriteLine("Error Catched");
                }
            }
        }

        //위의 문제는 메서드를 두 개로 분리함으로써 해결할 수 있습니다.
        private static class Case1
        {
            public static IEnumerable<T> GenerateSample<T>(IEnumerable<T> sequence, int sampleFrequency)
            {
                if (sequence == null)
                {
                    throw new ArgumentException("null sequence");
                }
                if (sampleFrequency < 1)
                {
                    throw new ArgumentException("Sample Frequency must be a positive integer");
                }
                return generateSampleImpl();

                //지역메서드입니다. wrapper 메서드에서만 호출할 수 있으며 외부에서는 접근 불가능합니다.
                IEnumerable<T> generateSampleImpl()
                {
                    int index = 0;
                    foreach (T item in sequence)
                    {
                        if (index % sampleFrequency == 0)
                        {
                            yield return item;
                        }
                    }
                }
            }

            //비동기 메서드의 경우에도 아래처럼 적용 가능합니다.
            public static Task<string> LoadMessageFinal(string userName)
            {
                if (string.IsNullOrWhiteSpace(userName))
                {
                    throw new ArgumentException("this must be a valid user");
                }
                return loadMessageImpl();

                async Task<string> loadMessageImpl()
                {
                    var message = await Task.Run(() => "user");
                    return message;
                }
            }

            public static void RunSample()
            {
                try
                {
                    //이제 오류는 곧장 보고됩니다.
                    var samples = GenerateSample(new int[] { 1, 2, 3, 4, 5 }, -1);
                }
                catch
                {
                    Console.WriteLine("Error Catched");
                }
            }
        }

        //지역 메서드는 람다와 비슷해보일 수도 있습니다. 하지만 구현 방식이 다르고 지역함수를 선택하는 것이 더 나은 선택입니다.
        //람다 표현식을 사용하면 컴파일러가 지역함수를 사용할 때보다 더 복잡한 구조를 생성하게 됩니다.
        //람다 표현식은 델리게이트 객체를 인스턴스화하는 반면, 지역 함수는 종종 private 메서드로도 구현될 수 있습니다.

        public static void RunSample()
        {
            Case0.RunSample();
            Case1.RunSample();
        }
    }
}
