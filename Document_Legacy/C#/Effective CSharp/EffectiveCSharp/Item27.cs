using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;
using System.Threading.Tasks;
using static System.Linq.Enumerable;

namespace EffectiveCSharp
{
    /// <summary>
    /// 인터페이스는 간략히 정의하고 기능의 확장은 확장 메서드를 사용하라
    /// </summary>
    public static class ECSharp27
    {
        /* 확장 메서드를 이용하면 인터페이스에 새로운 동작을 추가할 수 있다.
         * 인터페이스에는 가능한 한 최소한의 기능만을 정의하고, 확장 메서드를 세트로 함께 구현하면 손쉽게 기능을 확장할 수 있다.
         * 
         * 특히 API를 추가적으로 정의하지 않고도 새로운 기능을 추가할 수 있다.
         * 
         * 확장 메서드를 작성하는 이유로는
         * 1. 인터페이스에 기본 구현 추가.
         * 2. 닫힌 제네릭 타입에 동작 추가.
         * 3. 조합 가능한 인터페이스 작성.
         * 
         * 대표적인 예로는 정적 클래스 System.Linq.Enumerable 가 있다.
         */

        public static bool LessThan<T>(this T left, T right) where T : IComparable<T> => left.CompareTo(right) < 0;
        public static bool GreaterThan<T>(this T left, T right) where T : IComparable<T> => left.CompareTo(right) > 0;
        public static bool LessThanEqual<T>(this T left, T right) where T : IComparable<T> => left.CompareTo(right) <= 0;
        public static bool GreaterThanEqual<T>(this T left, T right) where T : IComparable<T> => left.CompareTo(right) >= 0;

        /* 새로운 인터페이스를 작성하는 경우에도 동일한 패턴을 사용할 수 있다.
         * 즉 다양한 기능을 제공하도록 인터페이스를 정의하지 말고 반드시 필요한 기능만을 포함하도록 간단히 인터페이스를 작성하자.
         * 그리고 사용자 편의를 위해 다양하게 제공하려는 기능은 확장 메서드 방식으로 작성하는 것이다.
         * 
         * 이러한 방법으로 인터페이스를 구현할 때 반드시 작성해야 하는 코드의 양을 줄일 수 있고, 확장 메서드를 통해 풍부한 기능을 제공할 수 있다.
         */ 

        public static void RunSample()
        {
            int i0 = 10;
            int i1 = 32;
            var res = i0.LessThan(i1);
            res = i0.GreaterThan(i1);
            res = i0.LessThanEqual(i1);
            res = i0.GreaterThanEqual(i1);
        }
    }
}