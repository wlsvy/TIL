using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;
using System.Threading.Tasks;

namespace EffectiveCSharp
{
    /// <summary>
    /// 타입 매개변수로 인스턴스 필드를 만들 필요가 없다면 제네릭 메서드를 정의하라
    /// </summary>
    public static class ECSharp25
    {
        /// <summary>
        /// 제네릭 클래스를 선언해버리면, 클래스 타입 매개변수에 따라 클래스 내부의 메서드들의 타입까지 전부 결정되어 버린다.
        /// </summary>
        public static class GenericUtil<T>
        {
            public static T Max(T left, T right) => Comparer<T>.Default.Compare(left, right) < 0 ? right : left;
            public static T Min(T left, T right) => Comparer<T>.Default.Compare(left, right) < 0 ? left : right;
        }
        /// <summary>
        /// 제네릭 메서드를 활용하자. 이 경우, 메서드마다 제약조건을 따로 설정할 수 있으며, 경우에 따라서는 제네릭 특화specialization도 활용할 수 있다.
        /// 
        /// 활용할 때에도 명시적인 타입 매개변수 지정이 필요없으니 코드 작성이 간편해진다
        /// 특히 이 점은 API를 작성할 때 유리한데 우선 사용하기 편하며, 타입 매개변수를 명시적으로 지정하지 않아도 컴파일러가 최적의 메서드를 찾아주기 때문이다.
        /// 
        /// 만약에 기존에 코드에서 특정 타입에 대해 더욱 효율적인 메서드를 추가한다면 컴파일러가 자동으로 그 메서드를 사용하도록 코드를 생성해주는 것.
        /// </summary>
        public static class Util
        {
            public static T Max<T>(T left, T right) => Comparer<T>.Default.Compare(left, right) < 0 ? right : left;
            public static double Max(double left, double right) => Math.Max(left, right);
            public static T Min<T>(T left, T right) => Comparer<T>.Default.Compare(left, right) < 0 ? left : right;
            public static double Min(double left, double right) => Math.Min(left, right);
        }

        public static void RunSample()
        {
            double d1 = 4;
            double d2 = 5;
            double dmax1 = GenericUtil<double>.Max(d1, d2);
            double dmax2 = Util.Max(d1, d2);

            string s1 = "foo";
            string s2 = "bar";
            string smax1 = GenericUtil<string>.Max(s1, s2);
            string smax2 = Util.Max(s1, s2);

            double? d3 = 12;
            double? d4 = null;
            var dmax3 = GenericUtil<double?>.Max(d3, d4);
            var dmax4 = Util.Max(d3, d4);
        }

        /// <summary>
        /// 제네릭 메서드를 활용한 두번째 예시
        /// 
        /// 만약 아래 클래스를 제네릭 클래스로 만들어버렸다면, Add 함수는 하나의 타입 매개변수에 대해서만 활용할 수 있었겠지만
        /// 제네릭 메서드를 활용했기 때문에, 다양한 타입에 대해 적용이 가능하다.
        /// </summary>
        public class CommaSeparatedListBuilder
        {
            private StringBuilder storage = new StringBuilder();

            public void Add<T>(IEnumerable<T> items)
            {
                foreach(T item in items)
                {
                    if (storage.Length > 0)
                    {
                        storage.Append(", ");
                    }
                    storage.Append("\"");
                    storage.Append(item.ToString());
                    storage.Append("\"");
                }
            }
        }
    }
}