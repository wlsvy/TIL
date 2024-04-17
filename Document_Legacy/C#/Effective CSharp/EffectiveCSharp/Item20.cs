using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;
using System.Threading.Tasks;

namespace EffectiveCSharp
{
    /// <summary>
    /// IComparable<T> 와 IComparer<T>를 이용하여 객체의 선후 관계를 정의하라
    /// </summary>
    public static class ECSharp20
    {
        public struct Customer : IComparable<Customer>, IComparable
        {
            private readonly string name;
            private double revenue;

            public Customer(string name, double revenue)
            {
                this.name = name;
                this.revenue = revenue;
            }

            public int CompareTo(Customer other) => name.CompareTo(other.name);
            /// <summary>
            /// IComparable.CompareTo 을 명시적으로 작성하고 있음에 주목. 이전 인터페이스용으로 작성된 것임을 명확히 하고 있다.
            /// 명시적인 방법으로 인터페이스 메서드를 구현했기 때문에 IComparable타입의 참조를 통해서만 이 메서드를 호출할 수 있다.
            /// 따라서 Customer 구조체를 직접 사용한다면 타입 안정적으로 비교를 수행할 수 있으며, 안전하지 않은 CompareTo() 메서드에는 접근조차 불가능하다.
            /// 
            /// 박싱/언박싱에 위험이 있는데도 왜 제네릭 버전인 아닌 IComparable 을 구현해야 하는 이유는
            /// 하위 호환성을 위해서 -> 닷넷 프레임워크 2.0 이전에 개발된 코드에서 이 타입을 사용하려면 반드시 이 인터페이스가 필요하기 때문
            /// </summary>
            int IComparable.CompareTo(object obj)
            {
                if(!(obj is Customer))
                {
                    throw new ArgumentException("Argument is not a Customer", "obj");
                }

                Customer otherCustomer = (Customer)obj;
                return this.CompareTo(otherCustomer);
            }

            public static bool operator <(Customer left, Customer right) => left.CompareTo(right) < 0;
            public static bool operator <=(Customer left, Customer right) => left.CompareTo(right) <= 0;
            public static bool operator >(Customer left, Customer right) => left.CompareTo(right) > 0;
            public static bool operator >=(Customer left, Customer right) => left.CompareTo(right) >= 0;

            private class RevenueComparer : IComparer<Customer>
            {
                int IComparer<Customer>.Compare(Customer x, Customer y) => x.revenue.CompareTo(y.revenue);
            }

            public static IComparer<Customer> RevenueCompare => revComp.Value;
            /// <summary>
            /// Lazy 는 스레드 환경에서 자원 초기화 지연에 대한 델리게이트
            /// </summary>
            private static Lazy<RevenueComparer> revComp = new Lazy<RevenueComparer>(() => new RevenueComparer());
            public static Comparison<Customer> CompareByRevenue => (left, right) => left.revenue.CompareTo(right.revenue);
        }
    }
}