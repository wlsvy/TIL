using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;
using System.Threading.Tasks;
//using static System.Linq.Enumerable;

namespace EffectiveCSharp
{
    /// <summary>
    /// 확장 메서드를 이용하여 구제화된 제네릭 타입을 개선하라
    /// </summary>
    public static class ECSharp28
    {
        public class Customer
        {
            public DateTime LastOrderDate;
        }

        /* 확장 메서드를 활용하는 방법.
         * 
         * 1. 고객에게 쿠폰을 보내는 메서드
         * 2. 지난 일주일 간 주문을 하지 않을 고객을 찾는 메서드
         */

        public static void SendEmailCoupons(this IEnumerable<Customer> customers, uint couponId)
        {
            //...
        }

        public static IEnumerable<Customer> LostProspect(this IEnumerable<Customer> targetList)
        {
            return
                from c in targetList
                where DateTime.Now - c.LastOrderDate > TimeSpan.FromDays(7)
                select c;
        }

        /// <summary>
        /// 확장 메서드를 활용하지 않고 구체화된 제네릭 타입을 상속하여 새로운 타입을 만든 방법.
        /// 
        /// 코드를 이처럼 작성해도 동작하는 데는 문제가 없지만, IEnumerable<Customer> 에 대하여 확장 메서드를 구현한 것에 비해서는 제약이 많다.
        /// 
        /// 메서드 원형의 차이만 보더라도, 확장 메서드는 IEnumerable<Customer> 를 기반으로 작성됐지만, 
        /// 파생 클래스에 메서드를 추가하는 방식은 List<Customer> 를 기반으로 한다.
        /// 
        /// 결국 새롭게 구성한 CustomerList에 대해서는 더 이상 이터레이터 메서드를 사용할 수가 없다. 
        /// => 상속을 잘못 사용한 예. 제네릭 타입을 상속하여 메서드를 추가하기보다는 확장 메서드를 구현하자.
        /// </summary>
        public class CustomerList : List<Customer>
        {
            public void SendEmailCoupons(uint couponId)
            {
                //...
            }
            public IEnumerable<Customer> LostProspect()
            {
                return
                    from c in this
                    where DateTime.Now - c.LastOrderDate > TimeSpan.FromDays(7)
                    select c;
            }
        }
    }
}