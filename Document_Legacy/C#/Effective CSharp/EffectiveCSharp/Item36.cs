using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;
using System.Threading.Tasks;

namespace EffectiveCSharp
{
    /// <summary>
    /// 쿼리 표현식과 메서드 호출 구문이 어떻게 대응되는지 이해하라
    /// </summary>
    public static class ECSharp36
    {
        /* c#은 쿼리 표현식 패턴에 포함된 개별 메서드가 어떤 의미를 가지고 있는지 전혀 개의치 않는다
         * 즉 쿼리 표현식 패턴에 포함된 메서드와 완전히 동일한 원형을 가진 메서드를 정의하되 완전히 다른 작업을 수행하더라도 c#은 구현 내용에 대해 전혀 개의치 않는다.
         * 
         * 다시 말하면 컴파일러는 Where()와 같은 메서드가 쿼리 표현식의 패턴에서 의도하는 동작을 온전히 수행하는지를 확인하지 않으며, 
         * 다만 구문상의 오류가 있는지만을 확인할 뿐이다.
         * 
         * 쿼리 표현식을 메서드 호출 구문으로 변환하려면 꽤 복잡한 과정을 반복해야 한다.
         * 컴파일러는 쿼리 표현식이 완벽하게 메서드 호출 구문으로 변환될 때까지 차례차례 쿼리 표현식을 메서드 호출 구문으로 바꿔나간다.
         */

        public static void RunSample()
        {
            int[] numbers = { 0, 1, 2, 3, 4, 5, 6, 7, 8, 9 };

            /* from n in numbers 표현식은 numbers의 개별 요소들을 범위 변수 n에 바인딩한다.
             * 
             * where 절은 Where() 메서드에서 사용할 필터를 지정하는데 
             * 실제로 where n < 5는 numbers.Where(n => n < 5); 로 변환된다.
             * 
             * where는 필터 이상의 역할을 수행하지 않으며, 입력 시퀀스로부터 조건을 만족하는 요소만을 추려낸다.
             * 
             * where 표현식이 메서드 호출 구문으로 변환될 때는
             * - 컴파일러는 메서드의 오버로딩이난 타입 바인딩 과정을 처리하기에 앞서 쿼리 표현식을 메서드 호출 구문으로 변환하는 과정을 우선 수행한다.
             * - 따라서 컴파일러는 쿼리 표현식을 메서드 호출 구문으로 변환하는 동안 활용할 수 있는 다른 메서드가 있는지를 알지 못한다.
             * - 타입을 확인하지도 않고 다른 확장 메서드가 있는지도 살펴보지 않으며 매우 단순하게 쿼리 표현식을 메서드 호출 구문으로 변환할 뿐이다.
             * - 컴파일러는 이러한 절차를 완료한 이후에야 비로소 후보군이 되는 메서드를 살펴보고 가장 적합한 메서드를 호출 하도록 코드를 생성한다.
             * 
             * 
             * select절은 Select() 메서드로 변환된다. 특별한 경우이기는 하지만 간혹 Select() 메서드 호출 자체가 생략되기도 한다.
             * 아래 예시에서 사용된 select절은 입력 시퀀스로부터 출력 시퀀스로 옮겨야 할 범위 변수를 선택하기 위한 축약 select로 볼 수 있다.
             * 
             * 또한 앞의 쿼리 구문은 where절을 포함하고 있으므로 입력 시퀀스와 출력 시퀀스가 다르다. 
             * 입력 시퀀스가 출력 시퀀스와 다른 경우 select 문은 삭제될 가능성이 있다.
             */ 
            var smallNumbers = from n in numbers
                               where n < 5
                               select n;
            //위의 예시는 최종적으로 아래처럼 변환된다. select 메서드는 호출할 필요가 없어 삭제되었다.
            var smallNubers_converted = numbers.Where(n => n < 5);

            //하지만 select()메서드가 다른 표현식의 출력 시퀀스를 즉각적으로 이어받지 않는다면 삭제되지 않는다.
            var allNumbers = from n in numbers select n;
            var allNumbers_converted = numbers.Select(n => n);
            
            //쿼리 표현식에서 select는 입력값을 다른 값으로 바꾸거나 혹은 타입을 변환하는 용도로 사용된다.
            //이 때 Select() 메서드에서 입력 시퀀스 내의 요소들을 수정해서는 안 된다.
            var squares = from n in numbers
                          where n < 5
                          select n * n;

            var containers = from n in numbers
                             select new { Number = n, Square = n * n };
            var containers_converted = numbers.Select(n => new { Number = n, Square = n * n });



            /* 쿼리 구문 내에 정렬과 관련된 부분은 
             * OrderBy(), ThenBy(), OrderByDescending(), ThenByDescending() 메서드로 변환된다.
             */
            var employees = new Person[30];
            var people = from e in employees
                         where e.Age > 30
                         orderby e.LastName, e.FirstName, e.Age
                         select e;

            var people_converted = 
                employees.Where(e => e.Age > 30).
                OrderBy(e => e.LastName).
                ThenBy(e => e.FirstName).
                ThenBy(e => e.Age);

            /* OrderBy()의 결과가 ThenBy()에 의해서 처리되고 그 결과가 다시 ThenBy()에 의해 처리되고 있음에 주목하자.
             * 사전 정렬 결과에 대해서 정렬 키가 동일한 요소들 내에서만 ThenBy()를 이용하여 다시 추가 정렬을 수행한다.
             * 
             * ThenBy()는 정렬되지 않은 시퀀스에 대해서는 올바르게 작업을 수행하지 못하므로 반드시 정렬된 시퀀스를 입력으로 줘야 한다.
             * 
             * 만약 쿼리 표현식 내에서 orderby절을 각기 구분하여 쓰면 이와 같이 변환 작업이 수행되지 않는다.
             * 다음 쿼리는 시퀀스를 LastName 으로 정렬하고, FirstName으로 재정렬한 후, 마지막으로 Age로 또 다시 정렬을 수행한다.
             */
            var people_badSorting = from e in employees
                                    where e.Age > 30
                                    orderby e.LastName
                                    orderby e.FirstName
                                    orderby e.Age
                                    select e;

            //정렬 방식을 내림차순으로 지정할 수도 있다.
            var people_descending = from e in employees
                                    where e.Age > 30
                                    orderby e.LastName descending, e.FirstName, e.Age
                                    select e;

            /* 쿼리 표현식 내에 그룹핑grouping이 포함되어 있거나 혹은 여러개의 from 절이 포함된다면 
             * 여러 단계를 거쳐 메서드 호출 구문으로 변환된다.
             */ 
            var results = from e in employees
                          group e by e.Department into d
                          select new
                          {
                              Department = d.Key,
                              Size = d.Count()
                          };
            //먼저 group into 구문을 중첩 쿼리로 변경한다.
            var results_converted = from d in
                           from e in employees group e by e.Department
                           select new
                           {
                               Department = d.Key,
                               Size = d.Count()
                           };
            //그 후 메서드 호출 구문으로 변환 작업을 수행한다.
            var results_converted2 = 
                employees.GroupBy(e => e.Department).
                Select(d => new { Department = d.Key, Size = d.Count() });

            /* 쿼리 표현식 내에 정의되어 있는 GroupBy() 메서드는 그룹에 대한 시퀀스를 반환하도록 정의되어 있다.
             * GroupBy 메서드는 개별 요소로 하나의 키와 값의 리스트를 쌍으로 갖는 시퀀스를 생성한다.
             * 
             * 여기서 그룹이란 하나의 키와 값의 리스트로 구성된 타입을 일컫는다.
             */ 

            var results2 = from e in employees
                           group e by e.Department into d
                           select new
                           {
                               Department = d.Key,
                               Employees = d.AsEnumerable()
                           };
            var result2_converted = 
                employees.GroupBy(e => e.Department).
                Select(d => new { Department = d.Key, Emploeyees = d.AsEnumerable() });

            /* 여러개의 from 절을 포함하는 쿼리 표현식은 SelectMany() 메서드로 변환된다.
             * SelectMany 메서드의 첫 번째 매개변수는 첫 번재 입력 시퀀스의 각 요소에 두 번째 입력 시퀀스를 매핑하는 함수다.
             * 
             * 두번째 매개변수(출력 선택기output selector)는 두 입력 시퀀스를 이용하여 출력 시퀀스를 생성하는 함수가 온다.
             * 
             * SelectMany()는 첫 번째 시퀀스를 순회하면서 첫 번째 시퀀스 내의 개별 요소에 대해 두 번재 시퀀스를 다시 순회한다.
             * 순회 과정을 통해 쌍으로 구성된 입력값을 만들어낸다. 출력선택기에는 두 시퀀스를 조합하여 만든 단일 시퀀스가 매개변수로 전달된다.
             */ 
            int[] odds = { 1, 3, 5, 7 };
            int[] evens = { 2, 4, 6, 8 };

            var pairs = from oddNumber in odds
                        from evenNumber in evens
                        select new
                        {
                            oddNumber,
                            evenNumber,
                            Sum = oddNumber + evenNumber
                        };
            foreach (var p in pairs)
            {
                Console.WriteLine($"{p.oddNumber}, {p.evenNumber}, {p.Sum} ");
            }

            var pairs_converted = odds.SelectMany(oddNumber => evens,
                (oddNumber, evenNumber) =>
                    new {
                        oddNumber,
                        evenNumber,
                        Sum = oddNumber + evenNumber
                    });

            /* 만일 쿼리에 더 많은 수식이 포함되어서 SelectMany()가 최종 결과물을 만들어내는 경우가 아니라면
             * SelectMany() 메서드는 입력 시퀀스의 개별 항목에 대응하는 튜플tuple을 생성해 다음 시퀀스로 전달한다.
             * 
             */ 
            var values = from oddNumber in odds
                         from evenNumber in evens
                         where oddNumber > evenNumber
                         select new
                         {
                             oddNumber,
                             evenNumber,
                             Sum = oddNumber + evenNumber
                         };

            var values_converted = 
                odds.SelectMany(oddNumber => evens,
                (oddNumber, evenNumber) =>
                new { oddNumber, evenNumber }).
                Where(pair => pair.oddNumber > pair.evenNumber).
                Select(pair => new
                {
                    pair.oddNumber,
                    pair.evenNumber,
                    Sum = pair.oddNumber + pair.evenNumber
                });

            //3개의 from 절을 사용하는 경우. SelectMany를 두 번 사용한다.
            var triples = from n in new int[] { 1, 2, 3 }
                          from s in new string[] { "one", "two", "three" }
                          from r in new string[] { "I", "II", "III" }
                          select new { Arabic = n, Word = s, Roman = r };

            //해당 구문은 아래와 같이 변환된다.
            var intergers = new int[] { 1, 2, 3 };
            var words = new string[] { "one", "two", "three" };
            var romanNumerals = new string[] { "I", "II", "III" };
            var triples_converted = 
                intergers.SelectMany(n => words,
                (n, s) => new { n, s }).
                SelectMany(pair => romanNumerals,
                (pair, n) =>
                new { Arabic = pair.n, Word = pair.s, Roman = n });




            /* Join과 GroupJoin 메서드는 모두 조인join 표현식에서 사용된다.
             * 
             * GroupJoin은 조인 표현식에서 into 절이 포함된 경우 사용되며, Join은 조인 표현식에 into 절이 표함되지 않은 경우 사용된다.
             * 
             * 바로 아래는 조인 표현식에 into 절이 없는 경우
             */

            var numArr = new int[] { 0, 1, 2, 3, 4, 5, 6, 7, 8, 9 };
            var labels = new string[] { "0", "1", "2", "3", "4", "5" };
            var query = from num in numArr
                        join label in labels on num.ToString() equals label
                        select new { num, label };
            var query_converted = numbers.Join(labels, num => num.ToString(),
                label => label, (num, label) => new { num, label });

            foreach(var q in query)
            {
                Console.WriteLine($"{q.num} {q.label}");
            }

            //into 절 사용
            var projects = new Project[5];
            var tasks = new Task[10];
            var groups = from p in projects
                         join t in tasks on p equals t.Parent
                         into projTasks
                         select new { Project = p, projTasks };

            var groups_converted = projects.GroupJoin(tasks,
                p => p, t => t.Parent, (p, projTasks) =>
                new { Project = p, TaskList = projTasks });
        }

        public class Person
        {
            public string LastName;
            public string FirstName;
            public int Age;
            public string Department;
        }

        public class Project
        {
        }
        public class Task
        {
            public Project Parent;
        }

        /// <summary>
        /// SelectMany 메서드는 아래와 같이 구현할 수도 있다.
        /// </summary>
        static IEnumerable<TOutput> SelectMany<T1, T2, TOutput> (
            this IEnumerable<T1> src, 
            Func<T1, IEnumerable<T2>> inputSelector, 
            Func<T1, T2, TOutput> outputSelector)
        {
            foreach(T1 first in src)
            {
                foreach(T2 second in inputSelector(first))
                {
                    yield return outputSelector(first, second);
                }
            }
        }
    }
}