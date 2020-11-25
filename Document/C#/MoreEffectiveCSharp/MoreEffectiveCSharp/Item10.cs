using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;
using System.Threading.Tasks;

//GetHashCode()의 위험성을 이해하라
namespace MoreEffectiveCSharp
{
    /// <summary>
    /// GetHashCode 의 기본구현은 비효율적입니다. 
    /// 참조 타입의 경우 겨우 동작은 하지만 효율을 기대할 수 없고 값 타입에서는 베이스 클래스의 버전이 정확하지 않을 때가 있습니다.
    /// 
    /// 되도록이면 GetHashCode를 사용하지 않는 것이 좋습니다. 그러나 필요하다면 아래의 규칙을 준수합시다. 
    /// 
    /// 1. 두 객체가 같다면(Equals() 인스턴스 메서드로 비교 시) 동일한 해시값을 생성해야 합니다. 그렇지 않으면 컬렉션에서 객체를 찾는 데 해시 코드를 사용할 수 없습니다.
    /// -> 만약에 특정 타입이 Equals를 재정의했다면 첫 번째 규칙을 어기지 않기 위해 GetHashCode 역시 재정의해야 할 것입니다.
    /// -> 즉 동일성 검사를 위해 사용한 속성들을 해시 코드 생성에서도 사용하는 것이 좋습니다.
    /// 
    /// 2. 모든 객체 a에 대해 a.GetHashCode() 는 인스턴스 불변이어야 합니다. 
    /// a의 어떤 메서드를 호출하였든 a.GetHashCode()는 항상 같은 값을 반환해야 합니다. 그래야 객체가 올바른 버킷에 담겨 있다는 것을 보장 할 수 있습니다.
    /// 
    /// 3. 해시 함수는 자주 사용되는 입력값들에 대해서 균일하게 분포된 정수값을 생성해야 합니다. 
    /// 이상적으로라면 값이 널리 분포되어야 하며, 특정 값 주위로 비슷한 값이 여러 번 반환되어서는 안 됩니다. 
    /// 그래야 컬렉션의 효율이 높아집니다. 쉽게 말하자면 각 버킷에 적은 수의 객체만 담겨 있습니다.
    /// 
    /// </summary>
    public static class MECSharp10
    {
        private static class Case0
        {
            public class Customer
            {
                public string Name { get; set; }
                public Customer(string name) => this.Name = name;
                public override int GetHashCode() => Name.GetHashCode();
            }
        }
        private static class Case1
        {
            public class Customer
            {
                public string Name { get; }
                public Customer(string name) => this.Name = name;
                public override int GetHashCode() => Name.GetHashCode();
            }
        }

        public static void RunSample()
        {
            //GetHashCode의 반환값은 불변이어야 합니다. 해쉬 코드 생성 시 객체의 변경할 수 없는 속성이나 값에 기초하여 해시 코드를 생성하도록 합시다.

            HashSet<Case0.Customer> cmap0 = new HashSet<Case0.Customer>();

            var c0 = new Case0.Customer("Acme Software");
            cmap0.Add(c0);
            c0.Name = "Acme Product";
            //이후 해쉬 코드가 바뀌었으니, 더 이상 해쉬 맵에서 c0을 찾을 수 없습니다.

            Console.WriteLine($"{cmap0.Contains(c0)}"); //false

            HashSet<Case1.Customer> cmap1 = new HashSet<Case1.Customer>();

            var c1 = new Case1.Customer("Acme Software");
            cmap1.Add(c1);
            //c1.Name = "Acme Product"; 값을 변경할 수 없습니다. 따라서 해쉬 값도 바뀔 일이 없습니다.
            Console.WriteLine($"{cmap1.Contains(c1)}"); //true, 


        }
    }
}
