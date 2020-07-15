using System;
using System.Collections.Generic;
using System.IO;
using System.Linq;
using System.Runtime.InteropServices;
using System.Text;
using System.Threading.Tasks;

namespace EffectiveCSharp
{
    /// <summary>
    /// 값비싼 리소스를 캡처하지 말라
    /// </summary>
    public static class ECSharp41
    {
        /* 클로저 Closure는 클로저에 바인된된 변수를 포함하는 객체를 생성합니다. 
         * 이때 클로저 객체를 잘못 사용하면 바인딩된 변수의 수명이 굉장히 길어질 수 있으니 주의해야 합니다.
         * Ienumerable 클로저 객체가 꼬리를 물듯이 참조로 전해지면, 해당 객체와 연관된 델리게이트, 캡쳐 변수들의 수명이 늘어납니다. 
         * 
         * 클로저 내에서 변수를 캡처하면 캡처된 변수를 사용하는 마지막 델리게이트가 가비지화될 때까지 해당 변수는 가비지로 간주되지 않습니다.
         * 캡쳐된 리소스가 가벼운 경우 특별히 여기에 대해 신경쓸 필요는 없습니다. 하지만 일부는 무거운 리소스를 참조하고 있을 수 있습니다.
         * 
         * 
         */ 

        static public class Extension
        {
            public static IEnumerable<int> Generate(int count, Func<int> func)
            {
                for(int i = 0; i < count; i++)
                {
                    yield return func();
                }
            }
        }

        //컴파일러는 ClosureExample 를 바탕으로 아래의 클로저 객체를 생성하며 해당 Closure 객체는 Generate가 사용하는 델리게이트에 바인딩 됩니다.
        public static void ClosureExample()
        {
            var counter = 0;
            var numbers = Extension.Generate(30, () => counter++);
        }

        private class Closure
        {
            public int generatedCounter = 0;
            public int generatorFunc() => generatedCounter++;
        }


        public static void RunSampleClosure()
        {
            var c = new Closure();
            var sequence = Extension.Generate(30, new Func<int>(c.generatorFunc));
        }

        /// <summary>
        /// 여기서 반환 객체는 클로저 객체에 결합된 델리게이트를 사용합니다.
        /// 반환 객체가 도달 가능한 상태이므로 델리게이트도, 델리게이트가 참조하는 내부 객체도, 그리고 내부 객체 안에 캡처된 객체도 모두 도달 가능 상태가 됩니다.
        /// 
        /// 따라서 바인딩된 변수를 포함하는 객체의 수명도 덩달아 늘어나게 됩니다.
        /// </summary>
        public static IEnumerable<int> MakeSequence()
        {
            var counter = 0;
            var numbers = Extension.Generate(30, () => counter++);
            return numbers;
        }

        /// <summary>
        /// 위의 MakeSequence() 를 컴파일러는 아래와 같이 바꿉니다.
        /// </summary>
        public static IEnumerable<int> MakeSequence_Converted()
        {
            var c = new Closure();
            c.generatedCounter = 0;
            var sequence = Extension.Generate(30, new Func<int>(c.generatorFunc));

            return sequence;
        }

        public static IEnumerable<string> ReadLines(this TextReader reader)
        {
            var txt = reader.ReadLine();

            while(txt != null)
            {
                yield return txt;
                txt = reader.ReadLine();
            }
        }

        public static int DefaultParse(this string input, int defaultValue = default)
        {
            return (int.TryParse(input, out var answer)) ? answer : defaultValue;
        }

        public static IEnumerable<IEnumerable<int>> ReadNumbersFromStream(TextReader t)
        {
            var allLiines = from line in t.ReadLines()
                            select line.Split(',');

            var matrixOfValues = from line in allLiines
                                 select from item in line
                                        select item.DefaultParse();
            return matrixOfValues;
        }


        /// <summary>
        /// 위의 메서드에서 쿼리 구문은 해당 값에 실제로 접근할 때 비로소 값을 생성한다는 것을 기억합시다.
        /// </summary>
        public static void RunSampleReadStream()
        {
            IEnumerable<IEnumerable<int>> rowOfNumbers;
            using (TextReader t = new StreamReader(File.OpenRead("WriteTest.txt")))
            {
                rowOfNumbers = ReadNumbersFromStream(t);
            }


            /* System.ObjectDisposedException 이 발생합니다.
             * TextReader t 가 참조하는 파일은 이미 닫혔는데, rowOfNumbers 가 참조하는 델리게이트 ReadLines에서 닫힌 파일을 읽으려 하기 때문입니다.
             */
            foreach (var line in rowOfNumbers)
            {
                foreach(int num in line)
                {
                    Console.WriteLine($"{num}, ");
                }
                Console.WriteLine();
            }
        }
        /// <summary>
        /// 아래의 방법으로 해결할 수 있긴 하지만, 대부분의 문제가 이렇게 간단한 방식으로 풀리지 않습니다.
        /// 
        /// 예를 들면 rowOfNumbers시퀀스 를 함수 밖으로 반환해야 하는 경우가 필요할 수도 있습니다.
        /// </summary>
        public static void RunSampleReadStream2()
        {
            using (TextReader t = new StreamReader(File.OpenRead("WriteTest.txt")))
            {
                var rowOfNumbers = ReadNumbersFromStream(t);
                foreach (var line in rowOfNumbers)
                {
                    foreach (int num in line)
                    {
                        Console.WriteLine($"{num}, ");
                    }
                    Console.WriteLine();
                }
            }
        }
        
        /// <summary>
        /// 파일을 읽고, 델리게이트를 이용하여 각 라인을 처리합니다.
        /// 
        /// 해당 코드에서는 파일 스트림을 사용하는 코드가 ProcessFile 메서드 안에 완전히 캡슐화 되어있습니다.
        /// 또한 람다식을 통해서 값을 반환하므로 메서드 내에서 값비싼 메서드를 할당/삭제 가 가능하고 리소스가 클로저 객체로 캡처되는 것을 방지합니다.
        /// </summary>
        public static TResult ProcessFile<TResult> (
            string filePath, 
            Func<IEnumerable<IEnumerable<int>>, TResult> action)
        {
            using (TextReader t = new StreamReader(File.OpenRead(filePath)))
            {
                var allLiines = from line in t.ReadLines()
                                select line.Split(',');

                var matrixOfValues = from line in allLiines
                                     select from item in line
                                            select item.DefaultParse();
                return action(matrixOfValues);
            }
        }

        private class ExpensiveFilter
        {
            private int[] ExpensiveResources = new int[100000];
            public bool PassesFilter(int num) => num % 100 == 0;
        }

        /// <summary>
        /// 아래의 경우, 반환값은 ExpensiveFilter의 참조를 포함한 상태로 외부로 반환됩니다.
        /// 의도치 않은 자원의 누수가 발생할 수 있습니다.
        /// 
        /// 메소드를 분리해 NotLeakingClosure 형태로 수정할 수 있습니다.
        /// 분리된 메서드 GenerateImportantStatistic는 double(값 타입)을 반환해 ExpensiveFilter 참조가 노출되는 것을 차단합니다.
        /// </summary>
        private static IEnumerable<int> LeakingClosure()
        {
            var filter = new ExpensiveFilter();
            var source = Enumerable.Range(10, 100);
            var result = Enumerable.Range(100, 200);
            var importantStatistic = (from num in source
                                     where filter.PassesFilter(num)
                                     select num).Average();
            return from num in result
                   where num > importantStatistic
                   select num;
        }

        
        private static IEnumerable<int> NotLeakingClosure()
        {
            var importantStatistic = GenerateImportantStatistic();
            var result = Enumerable.Range(1, 100);
            return from num in result
                   where num > importantStatistic
                   select num;
        }
        private static double GenerateImportantStatistic()
        {
            var filter = new ExpensiveFilter();
            var source = Enumerable.Range(10, 100);
            return (from num in source
                    where filter.PassesFilter(num)
                    select num).Average();
        }

        public static void RunSample()
        {
            //RunSampleReadStream(); 오류 발생 예시
            ProcessFile("WriteTest.txt",
                (arrayOfNums) => (from line in arrayOfNums
                                  select line.Max()).Max());
            var resources = NotLeakingClosure();
        }
    }
}