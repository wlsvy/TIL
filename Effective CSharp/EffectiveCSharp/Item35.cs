using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;
using System.Threading.Tasks;

namespace EffectiveCSharp
{
    /// <summary>
    /// 확장 메서드는 절대 오버로드하지 마라
    /// </summary>
    public static partial class ECSharp35
    {
        /* 확장 메서드를 이용하여 인터페이스에 대한 기본 구현체를 제공하는 것이 괜찮은 방법인 것은 확실하지만 
         * 타입을 확장하기 위한 용도로는 부적절하며 더 좋은 대안들이 많다.
         * 
         * 확장 메서드를 과도하게 사용하거나 잘못 사용하면 메서드 충돌로 인해 유지보수 비용이 급격히 증가하는 곤경에 처할 수 있다.
         */ 

        public sealed class Person
        {
            public string FirstName;
            public string LastName;
        }

        

        public static void RunSample()
        {

        }
    }

    //나쁜 예. 확장 메서드를 이용하여 클래스 확장
    namespace ConsoleExtension
    {
        public static class ConsoleReport
        {
            public static string Format(this ECSharp35.Person target) => $"{target.LastName,20}, {target.FirstName,15}";
        }
    }

    //점점 나빠진다. 네이스페이스를 달리하여 확장 메서드를 추가로 정의
    //Xml 기능이 현재 포함되지 않은 상태이므로 일단 주석처리
    namespace XmlExtension
    {
        //public static class XmlReport
        //{
        //    public static string Format(this ECSharp35.Person target) =>
        //        new XElement("Person",
        //            new XElement("LastName", target.LastName),
        //            new XElement("FirstName", target.FirstName)
        //            ).ToString();
        //}
    }

    /* 이제 using 문장을 바꾸면 출력 방향이 달라지게 된다.
     * 
     * 확장 메서드를 잘못 사용한 예인데 이처럼 타입의 기능을 확장하는 것은 좋지 않다.
     * 
     * 개발자가 실수로라도 네임스페이스를 잘못 참조하게 되면 프로그램의 동작 방식이 바뀌어버린다.
     * 혹은 확장 메서드가 포함된 네임스페이스를 참조하는 것을 잊어버리면 프로그램은 컴파일 되지조차 않는다.
     * 
     * 만약 2개의 네임스페이스에서 공통적으로 필요한 메서드가 있다면? 
     * 어떤 확장 메서드가 필요한지를 고려하여 클래스 정의를 담고 있는 파일을 여러 파일에 중복 정의할 수 밖에 없다.
     * 이 경우 두 네임스페이스를 함께 참조하게 되면 모호한 참조 때문에 컴파일 오류가 발생한다.
     * 
     * 앞서 구현한 새로운 기능은 사실 타입의 기능을 확장하는 것을 보기 어렵다.
     * Person 객체를 XML 로 출력하거나 콘솔로 출력하는 기능은 Person 타입 자체의 기능으로 생각하기보다는 
     * 외부에서 Preson 객체를 사용하는 방법 중 하나로 보는 것이 적절할 것 같다.
     * 
     * 확장 메서드는 추가하려는 기능이 타입과 자연스럽게 어울릴 때만 사용해야 한다.
     * 논리적으로 살폈을 때 추가하려는 기능이 타입 내에 포함되는 것이 적절할 경우에만 사용하라는 것이다.
     * 
     * 확장 메서드를 여러 네임스페이스에 걸쳐 오버로드해서는 안 된다.
     * 
     */
     
    public static partial class ECSharp35
    {
        /// <summary>
        /// 두 가지 확장 메서들르 정적 메서드로 다시 작성
        /// 
        /// 이 경우 사용자는 특별한 혼동 없이 두 메서드를 모두 사용할 수 있다.
        /// </summary>
        public static class PersonReports
        {
            public static string FormatAsText(Person target) => $"{target.LastName,20}, {target.FirstName,15}";
            //public static string FormatAsXml(this ECSharp35.Person target) =>
            //    new XElement("Person",
            //        new XElement("LastName", target.LastName),
            //        new XElement("FirstName", target.FirstName)
            //        ).ToString();
        }
    }
}