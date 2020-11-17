using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;
using System.Threading.Tasks;

//다양한 동일성 개념들 사이의 상관관계를 이해하라
namespace MoreEffectiveCSharp
{
    /// <summary>
    /// C#에서 동일성Equality 확인하는 방법으 6가지가 존재합니다.
    /// 
    /// public static bool Equals(Object objA, Object objB);
    /// public static bool ReferenceEquals(Object objA, Object objB);
    /// public virtual bool Equals(Object obj);
    /// public static bool operator ==(MyClass left, MyClass right);
    /// IEquatable<T> 인터페이스를 상속받고 Equals() 재정의
    /// IStructuralEquality를 구현하여 값에 고유한 의미체계 구현
    /// 
    /// </summary>
    public static class MECSharp09
    {
        //동일성을 비교할 때 아래 규칙을 생각합시다.
        //1. 어떤 객체든 자기 자신과는 동일해야 합니다. (a == a, 는 반드시 True)
        //2. 동일성의 비교 결과가 비교 순서와는 무관해야 합니다. (a == b 가 True 이면, b == a 도 True)
        //3. 추이관계transitive property를 만족해야 합니다. (a == b 이고 b == c 이면, a == c 이다)

        public static void RunSample()
        {
            //Object.ReferenceEquals는 두 개의 참조 타입 객체가 동일한 객체를 참조하는 경우 true를 반환합니다.
            //이 함수의 목적은 객체 ID를 비교하는 것이며 목표에 맞게 동작하므로 절대로 재정의해선 안됩니다.
            //이는 두 참조 타입 객체가 동일한 ID를 가지고 있다는 것을 뜻합니다. 참조타입이든 값 타입이든 객체 내용에는 신경쓰지 않고 그저 ID만을 비교합니다.
            object o1 = new object(), o2 = new object();
            Console.WriteLine($"{ReferenceEquals(o1, o1)}");    //true
            Console.WriteLine($"{ReferenceEquals(o1, o2)}");    //false

            //박싱으로 인해, 값 타입을 비교하면 무조건 false 입니다.
            int i1 = 0, i2 = 1;
            Console.WriteLine($"{ReferenceEquals(i1, i1)}");    //false
            Console.WriteLine($"{ReferenceEquals(i1, i2)}");    //false

            //static으로 선언된 Object.Equals. 비교하려는 두 객체의 런타임 객체를 알 수 없을때 사용합니다.
            //런타임 타입을 알 수 없는 두 객체를 비교하는 것이 목적이며 목적대로 잘 동작합니다. 해당 메서드도 오버로드하거나 재정의해선 안됩니다.

            //Equals() 메서드의 기본 동작은 객체의 ID를 비교하는 것입니다. Object.ReferenceEquals과 동일합니다.
            //
            //System.ValueType의 경우 Equals 메서드를 재정의하고 있습니다. 
            //하지만 ValueType의 Equals는 구현방식이 비효율적인데, 런타임에 파생타입을 사전에 파악할 방법이 없어서 Reflection을 활용하기 때문입니다.
            //
            //Equals를 재정의할 때, 베이스 클래스가 System.Object, System.ValueType이 기본 제공하는 Equals()가 아니라 Eqauls()를 재정의하는 경우에만 이를 호출해야 합니다.
            //Equals를 재정의할 때, GetHashCode() 도 반드시 재정의해야 합니다.

            RunTestSample();

            //값 타입을 만들면 operator==()을 재정의하는 것이 좋습니다. 비정적 Equals를 재정의하는 것과 비슷한 이유입니다.
        }

        //static으로 선언된 Object.Equals는 아래 처럼 구현돼 있다고 보면 됩니다. 내부에서 멤버 Equals를 호출해 동일성 비교 작업을 위임합니다.
        private static bool Equals(object lhs, object rhs)
        {
            if (object.ReferenceEquals(lhs, rhs))
            {
                return true;
            }
            if (object.ReferenceEquals(lhs, null) ||
               object.ReferenceEquals(rhs, null))
            {
                return false;
            }
            return lhs.Equals(rhs);
        }

        private class Widget : IEquatable<Widget>
        {
            public override bool Equals(object rhs)
            {
                //null 확인
                //c# 메서드 내에서 this는 절대 null 이 될 수 없습니다.
                if (ReferenceEquals(rhs, null))
                {
                    return false;
                }
                if (ReferenceEquals(this, rhs))
                {
                    return true;
                }
                //rhs가 Widget타입에서 파생된 클래스일 수 있기 때문에 실제 타입 정보를 비교합니다.
                //기본 클래스 부분의 멤버만을 비교하고, 파생클래스 멤버를 비교하지 않은채 동일성을 판단하면 문제가 생길 수 있습니다.
                if (this.GetType() != rhs.GetType())
                {
                    return false;
                }
                return this.Equals(rhs as Widget);
            }
            public bool Equals(Widget rhs)
            {
                Console.WriteLine("Compare Widget Equality");
                return true;
            }
        }

        private class DerivedWidget : Widget, IEquatable<DerivedWidget>
        {
            public override bool Equals(object rhs)
            {
                //null 확인
                if (ReferenceEquals(rhs, null))
                {
                    return false;
                }
                if (ReferenceEquals(this, rhs))
                {
                    return true;
                }

                DerivedWidget dw = rhs as DerivedWidget;
                if (dw == null)
                {
                    return false;
                }
                if (base.Equals(dw) == false)
                {
                    return false;
                }
                return this.Equals(dw);
            }
            public bool Equals(DerivedWidget rhs)
            {
                Console.WriteLine("Compare Derived Widget Equality");
                return true;
            }
        }

        private static void RunTestSample()
        {
            Widget w = new Widget();
            DerivedWidget dw = new DerivedWidget();

            Console.WriteLine($"Widget Compare1 : {w.Equals(dw)}"); //true, Widget.Equals(Widget rhs) 수행
            Console.WriteLine($"Widget Compare2 : {dw.Equals(w)}"); //true, Widget.Equals(Widget rhs) 수행


        }
    }
}
