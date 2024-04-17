using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;
using System.Threading.Tasks;

//명확하고 간결하며 완결된 메서드 그룹을 생성하라
namespace MoreEffectiveCSharp
{
    /// <summary>
    /// 메서드를 많이 오버로드 할수록 코드가 모호해질 가능성이 높습니다. 대부분의 경우 오버로딩을 적게 만드는 편이 다루기에 더 수월합니다.
    /// </summary>
    public static class MECSharp22
    {
        //C#의 제네릭은 C++ 템플릿과는 다르게 동작합니다. c# 제네릭에서는 타입의 매개변수로 임의의 메서드나 연산자가 올 수 있다고 가정을 못하므로 제약조건을 설정해야 합니다.
        //c#의 제네릭으로 오버로딩을 해결해보려는 생각은 좋지 않습니다.
        public class Vector
        {
            private List<double> m_Value = new List<double>();


            //아래와 같은 예시는 좋지 않습니다. 오버로딩 메서드 간의 동작이 다릅니다.
            public void Add(double number) => m_Value.Add(number);
            public void Add(IEnumerable<double> sequence)
            {
                int index = 0;
                foreach(double d in sequence)
                {
                    if(index == m_Value.Count)
                    {
                        return;
                    }
                    m_Value[index++] += d;
                }
            }

            //아래는 메서드의 매개변수가 하나인 경우입니다. 가능한 오버로드들을 생성함으로써 모호성을 피할 수 있습니다.
            //(decimal을 double 로 변환하려면 명시적 변환이 필요하므로 여기에서 생략합니다.)
            public void Scale(short s)
            {
                for(int i = 0; i < m_Value.Count; i++)
                {
                    m_Value[i] *= s;
                }
            }
            public void Scale(int s)
            {
                for (int i = 0; i < m_Value.Count; i++)
                {
                    m_Value[i] *= s;
                }
            }
            public void Scale(float s)
            {
                for (int i = 0; i < m_Value.Count; i++)
                {
                    m_Value[i] *= s;
                }
            }
            public void Scale(double s)
            {
                for (int i = 0; i < m_Value.Count; i++)
                {
                    m_Value[i] *= s;
                }
            }
        }

        public class Point
        {
            public double X, Y;
            public void Scale(int x, int y)
            {
                Console.WriteLine($"int Version");
                X *= x;
                Y *= y;
            }
            public void Scale(double x, double y)
            {
                Console.WriteLine($"double Version");
                X *= x;
                Y *= y;
            }
        }

        private static double Max(double lhs, double rhs)
        {
            Console.WriteLine($"version : Double");
            return Math.Max(lhs, rhs);
        }
        private static T Max<T>(T lhs, T rhs) where T : IComparable<T>
        {
            Console.WriteLine($"version : {lhs.GetType().ToString()}");
            return lhs.CompareTo(rhs) > 0 ? lhs : rhs;
        }

        public static void RunSample()
        {
            var p = new Point { X = 5, Y = 7 };
            p.Scale(5, 7L); //double 버전이 호출됩니다. 

            //두번째 매개변수가 long이므로 int에 대한 암묵적 형변환을 제공하지 않습니다.
            //하지만 int/long/float 에서 double로 암묵적 형변환은 가능하니 컴파일러는 double 버전 메서드를 호출합니다.


            //컴파일러는 제네릭 메서드를 이용할 때 매개변수의 타입을 좀 더 정확히 일치시킬 수 있다면 해당 메서드를 선택합니다.

            var r1 = Max(1, 3);         //int
            var r2 = Max(5.3, 12.7f);   //double,  =======> float이 아닙니다.
            var r3 = Max(5, 12.7f);     //float


            //추가적으로 확장 메서드를 고려해야 할 수 있습니다. 그래도 컴파일러는 접근 가능한 멤버함수를 전부 검사한 뒤에야 확장메서드를 확인합니다.
        }
    }
}
