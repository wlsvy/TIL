using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;
using System.Threading.Tasks;

//인터페이스 메서드와 가상 메서드의 차이를 이해하라
namespace MoreEffectiveCSharp
{
    /// <summary>
    /// 인터페이스를 구현하는 것과 가상 함수를 재정의하는 것은 매우 다릅니다. 
    /// 베이스 클래스의 추상 멤버를 구현하려면 반드시 가상화가 필요하지만 인터페이스 멤버의 경우에는 항상 가상화가 필요한 것은 아닙니다.
    /// </summary>
    public static class MECSharp15
    {
        private interface IMessage
        {
            void Message();
        }

        //파생 클래스에서 기반 클래스 메서드의 인터페이스 동작을 가려버리는 경우
        private static class Case0
        {
            private class Base : IMessage
            {
                public void Message() => Console.WriteLine(nameof(Base));
            }

            private class Derived : Base
            {
                public new void Message() => Console.WriteLine(nameof(Derived));
            }

            public static void RunSample()
            {
                Derived d = new Derived();
                d.Message();    //Derived
                var m = d as IMessage;
                m.Message();    //Base
            }
        }

        //파생클래스가 기반 클래스 동작을 가리면서 생기는 불상사를 막기 위해 가상함수 활용. 
        private static class Case1
        {
            private class Base : IMessage
            {
                public virtual void Message() => Console.WriteLine(nameof(Base));
            }

            private class Derived : Base
            {
                public override void Message() => Console.WriteLine(nameof(Derived));
            }

            public static void RunSample()
            {
                Derived d = new Derived();
                d.Message();    //Derived
                var m = d as IMessage;
                m.Message();    //Derived
            }
        }

        //NVI(non virtual interface) 방식을 활용하는 방법.
        //Effective C#의 항목 26참고하기, 경우에 따라 인터페이스를 상속받을 때는 제네릭/논제네릭 버전을 둘 다 상속받는 경우가 있습니다.
        //이 경우 위의 처럼 가상 메서드를 활용하면 구조가 복잡해지는 부작용이 생길 수 있는데 이에 대한 우회책으로 NVI를 활용할 수 있습니다.
        private static class Case2
        {
            private interface IMessage<T>
            {
                void Message();
            }

            private class Base : IMessage, IMessage<Base>
            {
                protected virtual void OnMessage() => Console.WriteLine($"{nameof(Base)}");

                //인터페이스 동작 자체는 비가상메서드로 선언, 파생클래스에서 재정의할 OnMessage 메서드를 따로 작성한 뒤, 인터페이스 메서드에서 호출하도록 합니다.

                public void Message() => OnMessage();
                void IMessage.Message() => OnMessage();
            }

            private class Derived : Base
            {
                //파생 클래스는 인터페이스 메서드를 재정의할 필요가 없으며 클래스에서 제공하는 가상 메서드만 재정의하면 됩니다.
                protected override void OnMessage() => Console.WriteLine($"{nameof(Derived)}");
            }

            public static void RunSample()
            {
                Derived d = new Derived();
                d.Message();    //Derived

                (d as IMessage).Message();          //Derived
                (d as IMessage<Base>).Message();    //Derived
            }
        }

        public static void RunSample()
        {
            Case0.RunSample();
            Case1.RunSample();
            Case2.RunSample();
        }
    }
}
