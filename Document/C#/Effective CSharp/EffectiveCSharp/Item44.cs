using System;
using System.Collections.Generic;
using System.Linq;
using System.Runtime.CompilerServices;
using System.Text;
using System.Threading.Tasks;

namespace EffectiveCSharp
{
    /// <summary>
    /// 바인딩된 변수는 수정하지 말라
    /// </summary>
    public static class ECSharp44
    {
        //C# 컴파일러는 쿼리 표현식과 람다 표현식을 모두 정적 델리게이트나 인스터스 혹은 클로저로 만든다는 것을 명심합시다.
        private static IEnumerable<TResult> Generate<TResult>(int number, Func<TResult> generator)
        {
            for (var i = 0; i < number; i++)
            {
                yield return generator();
            }
        }


        /// <summary>
        /// 다음 코드는 클로저에서 캡처된 변수를 수정했을 때 무슨 일이 일어나는지 보여줍니다.
        /// </summary>
        public static void CloserTest()
        {
            int index = 0;
            Func<IEnumerable<int>> sequence = () => Generate(30, () => index++);

            index = 20;
            //20 부터 49 까지 출력합니다.
            foreach (int n in sequence())
            {
                Console.WriteLine(n);
            }
            Console.WriteLine("Done");

            index = 100;
            //100 부터 129 까지 출력합니다.
            foreach (int n in sequence())
            {
                Console.WriteLine(n);
            }
        }

        /// <summary>
        /// 클로저 변환 예시입니다.
        /// </summary>
        public static void CloserTest2()
        {
            int[] someNumbers = { 0, 1, 2, 3, 4, 5 };
            var answers = from n in someNumbers
                          select n * n;
        }

        //위의 메서드는 컴파일러에 의해 대략 아래처럼 변환됩니다.
        //예제 람다 표현식에서는 인스턴스 변수나 지역변수에 접근하지 않습니다.
        private static int HiddenFunc(int n) => (n * n);
        private static Func<int, int> HiddenDelegateDefinition;
        public static void CloserTest2_converted()
        {
            int[] someNumbers = { 0, 1, 2, 3, 4, 5 };
            if(HiddenDelegateDefinition == null)
            {
                HiddenDelegateDefinition = new Func<int, int>(HiddenFunc);
            }

            var answers = someNumbers.Select(HiddenDelegateDefinition);
        }

        /// <summary>
        /// 이번엔 객체의 멤버와 지역변수에 접근하는 클로저 예시입니다.
        /// </summary>
        public class ModFilter
        {
            private readonly int modulus;
            public ModFilter(int mod)
            {
                modulus = mod;
            }

            public IEnumerable<int> FindValues(IEnumerable<int> sequence)
            {
                int numValues = 0;
                return from n in sequence
                       where n % modulus == 0 //오브젝트 멤버에 접근합니다.
                       select n * n / ++numValues; //지역변수에 접근합니다.
            }
        }

        /// <summary>
        /// 아래와 같이 변환됩니다.
        /// </summary>
        public class ModFilter_converted
        {
            private sealed class Closure
            {
                //지역변수, 객체를 여기서 참조합니다.
                public ModFilter_converted outer;
                public int numValues;

                public int SelectClause(int n) => ((n * n) / ++this.numValues);

            }

            private readonly int modulus;

            public ModFilter_converted(int mod)
            {
                this.modulus = mod;
            }

            private bool WhereClause(int n) => ((n & this.modulus) == 0);

            public IEnumerable<int> FindValues(IEnumerable<int> sequence)
            {
                var c = new Closure();
                c.outer = this;
                c.numValues = 0;

                return sequence.Where<int>(
                    new Func<int, bool>(this.WhereClause))
                    .Select(new Func<int, int>(c.SelectClause));
            }

        }

        /* 바인딩된 변수를 변경한다면 이를 참조하는 클로져 객체의 멤버를 바꾸는 동작을 유발할 수 있습니다.
         * 
         * 따라서 여러 개의 쿼리를 연이어 수행할 때 바인딩딘 변수의 값을 수행하게 되면 
         * 지연 수행과 컴파일러의 클로져 구현 특성 때문에 예상치 못한 문제가 발생할 수 있습니다.
         * 
         * 클러저에 의해 캡처되어 바인딩된 변수는 수정하지 않는 것이 안전합니다.
         */ 
    }
}