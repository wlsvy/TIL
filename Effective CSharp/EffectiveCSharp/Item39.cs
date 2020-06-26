using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;
using System.Threading.Tasks;

namespace EffectiveCSharp
{
    /// <summary>
    /// function 과 action 내에서는 예외가 발생하지 않도록 해라.
    /// </summary>
    public static class ECSharp39
    {
        public enum EmployeeType { Active, Salary }

        public class Employee
        {
            public EmployeeType Classification;
            public int YearsOfService;
            public int MonthlySalary;
        }

        public static void RunSample()
        {
            /* 만약 아래 문장에서 예외가 발생한다면
             * 
             * 순회중에 문제가 발생했을 것이 분명하기 때문에, 일부 직원의 월급은 인상했지만, 다른 지원의 월급은 인상하지 못했을 수도 있다.
             * 이 경우 모든 직원의 월급을 이 루틴 수행 이전으로 복구시키기란 어렵다.
             * 
             * 람다 표현식의 경우 그 내부에서 예외가 발생하면 문제의 원인을 찾기가 굉장히 어려워진다
             */ 
            var allEmployees = new List<Employee>(10);
            allEmployees.ForEach(e => e.MonthlySalary *= 2);


            /* 예외 발생 가능성을 염두해 두고 코드를 작성하자
             * 원본 시퀀스의 복사본을 마련해두고 필요한 절차를 수행한 뒤 원본 시퀀스를 대체하는 방법이 있다.
             * 이 경우 중간에 예외가 발생해도 원본 데이터에는 영향이 없다.
             * 
             * 단점은 유지보수해야할 코드가 길어지며, 가독성이 떨어지는 것은 물론, 프로그램 성능에도 영향을 끼친다는 것이다.
             */
            var updates = (from e in allEmployees
                           select new Employee
                           {
                               Classification = e.Classification,
                               YearsOfService = e.YearsOfService,
                               MonthlySalary = e.MonthlySalary
                           }).ToList();

            allEmployees = updates;
        }

    }
}