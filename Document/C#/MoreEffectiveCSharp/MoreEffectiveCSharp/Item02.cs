using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;
using System.Threading.Tasks;

//변경 가능한 데이터에는 암묵적 속성을 사용하는 것이 낫다
namespace MoreEffectiveCSharp
{
    /// <summary>
    /// 암묵적 속성implicit property 를 이용한다면 컴파일러는 속성의 값을 저장한 뒷단 필드backing field를 추가하고 임의의 필드명을 부여합니다.
    /// 
    /// 암묵적 속성은 사용자가 뒷단 필드를 직접 타이핑해야 하는 수고를 줄이며 생산성을 높이고 클래스의 가독성을 높일 수 있습니다.
    /// 
    /// Serializable 애트리뷰트을 사용한 타입에 대해서는 암묵적 속성을 사용할 수 없습니다.
    /// </summary>
    public static class MECSharp02
    {
        //암묵적 속성은 명시적 속성과 동일한 접근 한정자를 지원하며 필요하다면 set 접근자의 접근 권한을 제한할 수 있습니다.
        public class Customer
        {
            public long ID { get; private set; }
            public string Name { get; protected set; }
            public string PhoneNumber { get; internal set; }
            public string Address { get; protected internal set; }
        }

        /// <summary>
        /// 암묵적 속성을 사용하면 향후 데이터 검증 등을 위해서 암묵적 속성을 명시적 속성으로 구현부를 추가해도 클래스의 바이너리 호환성이 유지됩니다.
        /// 추가적으로 여전히 속성을 사용하고 있으므로 데이터 검증코드를 한 군데만 두면 됩니다.
        /// </summary>
        
        //검증코드를 추가하기 전 Person 클래스
        public class Person
        {
            public string FirstName { get; set; }
            public string LastName { get; set; }
            public override string ToString() => $"{FirstName} {LastName}";
        }

        //검증코드를 추가한 뒤 Person클래스
        public class NewPerson
        {
            private string m_FirstName;
            public string FirstName 
            { 
                get => m_FirstName;
                set
                {
                    if (string.IsNullOrEmpty(value))
                    {
                        throw new ArgumentException("First name cannot benull or empty");
                    }
                    m_FirstName = value;
                } 
            }
            private string m_LastName;

            public string LastName
            {
                get => m_LastName;
                set
                {
                    if (string.IsNullOrEmpty(value))
                    {
                        throw new ArgumentException("Last name cannot benull or empty");
                    }
                    m_LastName = value;
                }
            }
            public NewPerson(string firstName, string lastName)
            {
                this.FirstName = firstName;
                this.LastName = lastName;
            }

            public override string ToString() => $"{FirstName} {LastName}";
        }

        public static void RunSample()
        {

        }
    }
}
