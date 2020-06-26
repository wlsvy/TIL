using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;
using System.Threading.Tasks;

namespace EffectiveCSharp
{
    /// <summary>
    /// 메서드보다 람다 표현식이 낫다
    /// </summary>
    public static class ECSharp38
    {
        public enum EmployeeType { Salary }

        public class Employee
        {
            public EmployeeType Classification;
            public int YearsOfService;
            public int MonthlySalary;
        }

        private static bool LowPaidSalaried(Employee e) => e.MonthlySalary < 4000 && e.Classification == EmployeeType.Salary;
        private static IQueryable<Employee> LowPaidSalariedFilter(this IQueryable<Employee> sequence) =>
            from s in sequence
            where s.Classification == EmployeeType.Salary && s.MonthlySalary < 4000
            select s;

        public static void RunSample()
        {
            var allEmployees = new Employee[10];

            var earlyFolks = from e in allEmployees
                             where e.Classification == EmployeeType.Salary
                             where e.YearsOfService >= 20
                             where e.MonthlySalary < 4000
                             select e;
            var newest = from e in allEmployees
                         where e.Classification == EmployeeType.Salary
                         where e.YearsOfService < 20
                         where e.MonthlySalary < 4000
                         select e;

            //단순한 조문의 경우 전부 인라인화될 가능성이 높기 때문에, 아래와 같이 where절을 합친다고 해도 성능이 개선되기를 기대하긴 어렵다.

            var earlyFolks2 = from e in allEmployees
                             where e.Classification == EmployeeType.Salary && e.YearsOfService >= 20 && e.MonthlySalary < 4000
                             select e;
            var newest2 = from e in allEmployees
                         where e.Classification == EmployeeType.Salary && e.YearsOfService < 20 && e.MonthlySalary < 4000
                         select e;



            /* 동일한 where절을 메서드로 묶는다면 공통된 부분을 하나로 묶을 수 있기는 하다.
             * 하지만 이 방법은 쿼리 표현식 안에서는 좋은 방법이 아니다.
             * 
             * 통상 쿼리 표현식 내의 람다 표현식은 델리게이트로 변환되어 수행된다. (Linq to Objects)
             * 
             * 다른 경우에는 람다 표현식을 활용하여 표현식 트리를 만들고, 
             * 향후 이를 파싱하여 완전히 다른 구문을 생성한 후, 그 결과를 다른 환경에서 수행하기도 한다. (Linq to SQL)
             *  - 표현식 트리는 쿼리를 나타내기 위한 논리적인 구성을 포함하고 있다. 
             *  - Linq to SQL은 이 표현식 트리를 파싱하여 적절한 T-SQL 쿼리를 생성한 후 이를 데이터베이스에 전달한다.
             * 
             *  이때 쿼리 구문 내에서 메서드를 호출하는 부분은 적절한 T-SQL 표현식으로 변경하지 못하는 것이 문제이다.
             *  - 다양한 데이터 소스에 대해 적용되는 라이브러리를 만드는 경우라면 이러한 상황은 반드시 고려돼야 한다.
             *  - 올바른 동작을 위해서는 람다 표현식을 각각 구분하여 작성하되 인라인으로 해석될 수 있도록 놔둬야 한다.
             */

            var earlyFolks3 = from e in allEmployees
                              where LowPaidSalaried(e) && e.YearsOfService >= 20
                              select e;
            var newest3 = from e in allEmployees
                              where LowPaidSalaried(e) && e.YearsOfService < 20
                              select e;

            //쿼리 표현식의 경우, 기존과는 조금 다른 형태의 빌딩 블록을 만들어서 사용하자.

            //IQueryable을 사용하는 메서드를 이용하면 여러 단계에 걸쳐 쿼리를 수행하더라도 
            //결과적으로 원격지에서 쿼리가 수행돼야 할 시점에 단일의 표현식 트리로 결합된다.
            var salaried = allEmployees.AsQueryable().LowPaidSalariedFilter();
            var earlyFolks4 = salaried.Where(e => e.YearsOfService >= 20);
            var newest4 = salaried.Where(e => e.YearsOfService < 20);
        }
    }
}