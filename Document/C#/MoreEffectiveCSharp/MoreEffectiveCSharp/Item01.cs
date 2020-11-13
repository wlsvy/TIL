using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;
using System.Threading.Tasks;

//접근 가능한 데이터 멤버 대신 속성을 사용하라
namespace MoreEffectiveCSharp
{
    /// <summary>
    /// 속성은 내부 데이터에 접근하거나 그 값을 수정하기 위해서 메서드의 기능을 확장한 C#의 기본 요소입니다.
    /// 멤버 함수로 할 수 있는 작업이라면 속성으로도 할 수 있습니다.
    /// 
    /// 속성property은 C# 초기부터 지원하였으며 시간이 지나면서 더 풍부한 표현력을 가지도록 발전하였습니다.
    /// 
    /// 또한 속성을 이용하면, ref나 out키워드를 사용하는 메서드에 속성을 직접 전달할 수 없으므로, 필드를 사용할 때 내부 데이터가 외부로 노출되는 중요한 결점을 해결합니다.
    /// 
    /// 속성을 사용하는 코드는 마치 데이터 필드에 직접 접근하는 것처럼 보이므로 성능 면에서도 큰 차이를 보여서는 안 될 것입니다. 
    /// 따라서 속성 접근자 내에서 오래 걸리는 연산(데이터 베이스 쿼리 등)은 자제해야 합니다.
    /// </summary>
    public static class MECSharp01
    {
        public class Customer
        {
            //속성을 통해 게터getter, 세터setter 메서드를 다른 표현식으로 나타낼 수 있습니다.
            private string m_Name;
            public string Name
            {
                get => m_Name;
                set
                {
                    if (string.IsNullOrWhiteSpace(value))
                    {
                        throw new ArgumentException("Name cannot be blank", nameof(Name));
                    }
                    m_Name = value;
                }
            }

            //auto property 자동 속성은 명시적으로 데이터 멤버를 선언하지 않아도 컴파일러가 자동적으로 선언합니다.
            //초기값을 지정하는 것도 가능합니다.
            public string Address { get; set; } = "No Address";

            //getter/setter 에 서로 다른 접근한정자를 지정할 수 있습니다.
            public long ID { get; private set; }

            //속성은 virtual 로도 설정 가능합니다.
            public virtual string PhoneNumber { get; set; }
        }

        //속성은 메서드로 구현되므로 멀티스레드도 쉽게 지원할 수 있습니다.
        public class Customer_WithMultiThreading
        {
            private object m_SyncHandle = new object();

            private string m_Name;
            public string Name
            {
                get
                {
                    lock (m_SyncHandle)
                    {
                        return m_Name;
                    }
                }
                set
                {
                    if (string.IsNullOrWhiteSpace(value))
                    {
                        throw new ArgumentException("Name cannot be blank", nameof(Name));
                    }
                    lock (m_SyncHandle)
                    {
                        m_Name = value;
                    }
                }
            }
        }

        //인터페이스를 정의할 때에도 속성을 사용할 수 있습니다.
        public interface INameValuePair<T>
        {
            string Name { get; }
            T Value { get; set; }
        }

        //속성은 인덱서에 사용할 수 있습니다.
        public class Widget
        {
            private int[] m_IntergerArray = null;
            public int this[int index]
            {
                get => m_IntergerArray[index];
                set => m_IntergerArray[index] = value;
            }

            private Dictionary<string, string> m_AddressDic = null;
            public string this[string name]
            {
                get => m_AddressDic[name];
                set => m_AddressDic[name] = value;
            }

            private int[,] m_MultipleIntergerArray = null;
            public int this[int x, int y]
            {
                get => m_MultipleIntergerArray[x, y];
                set => m_MultipleIntergerArray[x, y] = value;
            }
        }

        private static void TestRefMethod(ref string refStr) 
        {
        }
        private static void TestOutMethod(out string outStr)
        {
            outStr = string.Empty;
        }

        public static void RunSample()
        {
            Customer c = new Customer();
            string cName = c.Name;

            TestRefMethod(ref cName);
            TestOutMethod(out cName);

            //속성은 ref/out 키워드와 함께 전달할 수 없습니다.
            //TestRefMethod(ref c.Name); //error
            //TestOutMethod(out c.Name); //error
        }
    }
}
