using System;
using System.Collections.Generic;
using System.Diagnostics.Contracts;
using System.Linq;
using System.Text;
using System.Threading.Tasks;

namespace EffectiveCSharp
{
    /// <summary>
    /// IEnumerable[T] 데이터 소스와 IQueryable[T] 데이터 소스를 구분하라
    /// </summary>
    public static class ECSharp42
    {
        /* IQueryable<T>와 IEnumerable<T>는 동일한 기능을 제공하는 것처럼 보이지만 이 둘은 매우 다릅니다.
         * 특히 쿼리 패턴을 구현하는 방식이 매우 상이하기 때문에 데이터 원본이 어떤 인터페이스를 제공하느냐에 따라서 올바르게 쿼리를 작성해야 합니다.
         */ 


        /// <summary>
        /// DB와 연동하여 데이터를 가져오는 클래스가 있다고 가정합시다.
        /// </summary>
        public class DataBaseContext
        {
            public IQueryable<Customer> Customers; 
        }

        public class Customer
        {
            public string Name;
            public string City;
        }

        public static bool IsCityLondon(Customer c) => c.City == "London";

        public static void RunSample()
        {
            DataBaseContext dbContext = new DataBaseContext();

            {
                //첫 번째 예, IQueryable을 반환합니다.
                var q = from c in dbContext.Customers
                        where c.City == "London"
                        select c;

                //두 번째 예, IEnumerable을 반환합니다.
                var q2 = (from c in dbContext.Customers
                          where c.City == "London"
                          select c).AsEnumerable();

                var finalAnswer = from c in q2
                                  orderby c.Name
                                  select c;

                /* 두 예시의 결과값은 동일합니다.
                 * 
                 * 하지만 첫 번째 예시는 IQueryable을 활용하며, 이는 LINQ to SQL을 통해 쿼리문으로 변환해 데이터베이스에 전달할 수 있습니다.
                 * 
                 * 반면에 두 번째 예시는 IEnumerable을 활용하며, 
                 * LINQ to SQL이 아닌 LINQ to Object와 델리게이트를 활용해 로컬 시스템에서 작업을 수행하게 됩니다.
                 * 이때 작업을 처리하기 위해 필요한 데이터를 전부 로컬 머신으로 가져오게 되며 상대적으로 더 많은 메모리가 필요하게 됩니다.
                 * 
                 * IQueryable을 활용하는 예시가 더 효율적인 것을 알 수 있는데 
                 * 이는 델리게이트 대신 표현식 트리(쿼리 내의 동작들을 표현하기 위한 일종의 데이터 구조)를 이용하기 때문입니다.
                 */
            }

            {
                //안전하게 동작합니다.
                var q1 = from c in dbContext.Customers.AsEnumerable()
                         where IsCityLondon(c)
                         select c;

                //컬렉션을 순환할 때 오류를 유발합니다.
                var q2 = from c in dbContext.Customers
                         where IsCityLondon(c)
                         select c;

                /* 첫 번째 쿼리문은 문제없습니다. LINQ to Objects는 델리게이트를 이용하여 쿼리를 메서드 호출로 변경하기 때문입니다.
                 * AsEnumerable()을 통해 로컬 머신에서 동작을 수행하게 됩니다.
                 * 
                 * 반면에 두번째 쿼리문은 예외를 유발합니다. 
                 * LINQ to SQL은 쿼리문을 T-SQL로 변환하는데 이때 호출 메서드를 제대로 반영할 수 없기 때문입니다.
                 * (대신 람다를 사용합시다. 항목 38 참조)
                 */ 
            }
        }

        //간혹 특정 메서드가 동일한 T 타입에 대해서 IEnumerable과 IQueryable을 이용한 쿼리를 모두 지원해야 하는 경우가 있다고 해봅시다.
        //여기서 LastIndexOf 메서드는 LINQ to SQL을 통해 올바르게 해석 가능한 메서드 중 하나입니다. sql쿼리문에서 그대로 사용할 수 있습니다.
        public static IEnumerable<Customer> ValidCustomer(this IEnumerable<Customer> customers)
            => from c in customers
               where c.City.LastIndexOf('n') == 0
               select c;

        public static IQueryable<Customer> ValidCustomers(this IQueryable<Customer> customers)
            => from c in customers
               where c.City.LastIndexOf('n') == 0
               select c;

        //위의 예시는 코드 중복이 발생할 여지가 있으니 아래처럼 고쳐봅시다.

        /// <summary>
        /// 위의 예시는 코드 중복이 발생할 여지가 있으니 아래처럼 고쳐봅시다.
        /// AsQueryable()을 사용하여 코드 중복을 제거할 수 있습니다.
        /// 
        /// AsQueryable()은 시퀀스의 런타임 타입을 확인합니다. 
        /// 만약 시퀀스의 런타임 타입이 IQueryable이라면 IQueryable을 반환할 것이고 
        /// IEnumerable이라면 LINQ to Object 를 사용하여 IQueryable을 구현한 래퍼를 생성하여 반환합니다.
        ///   이 경우 Enumerable 객체를 얻기는 하겠지만 IQueryable 타입으로 래핑된 객체를 얻게 됩니다.
        ///   
        /// AsQueryable()을 사용하면 최대한 이점을 얻을 수 있습니다. 시퀀스가 이미 IQueryable을 구현하고 있는 경우 그 구현체를 사용하면 되고
        /// IEnumerable 만을 사용하고 있는 경우 IEnumerable 구현체를 그대로 사용할 수 있습니다.
        /// </summary>
        public static IEnumerable<Customer> ValidCustomers(this IEnumerable<Customer> customers)
            => from c in customers.AsQueryable()
               where c.City.LastIndexOf('n') == 0
               select c;
    }
}