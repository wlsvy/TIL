using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;
using System.Threading.Tasks;

//설계 선택지를 제한하는 ICloneable은 사용을 피하라
namespace MoreEffectiveCSharp
{
    /// <summary>
    /// ICloneable의 공식정인 정의를 보면 깊은 복사 또는 얕은 복사를 지원한다고 애매하게 정의하고 있습니다.
    /// ICloneable에도 나름의 쓰임이 있지만 어떤 규칙이 있다기보다는 예외적인 상황에 대응하기 위한 것으로 보는 편이 낫습니다.
    /// 닷넷에서 제네릭 지원을 추가했을 때에도 ICloneable의 제네릭 버전은 추가되지 않았습니다.
    /// 
    /// 값 타입에는 ICloneable을 추가하지 맙시다. 할당 연산자로 충분합니다.
    /// ICloneable 은 해당 타입이 복사 연산을 반드시 지원해야 하는 경우에만 사용하되, 최말단 클래스에만 추가하는 것이 좋습니다.
    /// 파생클래스에서 ICloneable을 사용할 가능성이 크다면 protected 복사 생성자를 만들어야 합니다. 그 외의 경우에는 ICloneable을 쓰지 않는 것이 좋습니다.
    /// </summary>
    public static class MECSharp24
    {
        private static class Case0
        {
            //기반 클래스의 Clone 메서드를 재정의하지 않는 경우 Clone 호출 시 파생 클래스 부분은 제외하고 복사하는 문제가 발생할 수 있습니다.
            //ICloneable을 기반 클래스에 추가하면 이후 파생 타입이 너무 큰 짐을 지게 됩니다.
            private class BaseType : ICloneable
            {
                private string label = "class name";
                private int[] values = new int[10];

                public object Clone()
                {
                    BaseType rVal = new BaseType();
                    rVal.label = label;
                    for(int i = 0; i < values.Length; i++)
                    {
                        rVal.values[i] = values[i];
                    }
                    return rVal;
                }
            }

            private class Derived : BaseType
            {
                private double[] dValues = new double[10];
            }

            public static void RunSample()
            {
                var d = new Derived();
                var d2 = d.Clone() as Derived;  //파생 클래스 부분은 복사되지 않습니다.

                Console.WriteLine(d2 == null);  //true
            }
        }

        private static class Case1
        {
            //ICloneable 은 최말단 클래스에만 추가합시다. 
            //이 경우 기반 클래스에서는 protected 복사 생성자를 추가합시다. 
            //파생클래스가 기반 클래스의 멤버를 수월하게 복사할 수 있도록 돕는 수단을 제공할 수 있습니다. 
            private class BaseType
            {
                private string label;
                private int[] values;

                public BaseType()
                {
                    label = "class name";
                    values = new int[10];
                }

                //복제를 위해 파생클래스에서 사용합니다.
                protected BaseType(BaseType right)
                {
                    label = right.label;    //string은 불변객체이니 얕은 복사를 해도 좋습니다.
                    values = right.values.Clone() as int[];
                }

                
            }

            //ICloneable은 최말단 클래스에 추가합니다.
            private sealed class Derived : BaseType, ICloneable
            {
                private double[] dValues = new double[10];

                public Derived() { }
                private Derived(Derived right) : base(right)
                {
                    dValues = right.dValues.Clone() as double[];
                }

                public object Clone()
                {
                    return new Derived(this);
                }
            }

            public static void RunSample()
            {
                var d = new Derived();
                var d2 = d.Clone() as Derived;

                Console.WriteLine(d2 == null);  //false
            }
        }

        public static void RunSample()
        {
            Case0.RunSample();
            Case1.RunSample();
        }
    }
}
