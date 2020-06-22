using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;
using System.Threading.Tasks;
using static System.Console;

namespace EffectiveCSharp
{
    /// <summary>
    /// 베이스 클래스나 인터페이스에 대해서 제네릭을 특화하지 말라
    /// </summary>
    public static class ECSharp24
    {
        public interface IMessageWriter
        {
            void WriteMessage();
        }

        public class Base { }
        public class Derived : Base, IMessageWriter
        {
            public void WriteMessage() => WriteLine("Inside Derived.WriteMessage");
        }
        public class AnotherType : IMessageWriter
        {
            public void WriteMessage() => WriteLine("Inside AnotherType.WriteMessage");
        }

        /// <summary>
        ///  Base 클래스에 대한 제네릭 메소드 특화(specialization)
        /// </summary>
        static void WriteMessage(Base b) => WriteLine("Inside WriteMessage(Base)");
        static void WriteMessage<T>(T obj) => WriteLine($"Inside WriteMessage<T>(T) : {obj.ToString()}");
        static void WriteMessage(IMessageWriter obj)
        {
            Write($"Inside WriteMessage(IMessageWriter): ");
            obj.WriteMessage();
        }

        public static void RunSample()
        {
            /* Derived 클래스는 
             * WriteMessage(Base b) 보다 WriteMessage<T>(T obj) 에 더 정확히 일치한다. 
             * 
             * 왜냐하면 제네릭 메서드의 타입 매개변수인 T를 Derived로 대체하면 
             * 컴파일러 입장에서는 요청한 메서드와 정확히 일치하는 메서드를 찾을 수 있기 때문이다.
             * 
             * 반면에 WriteMessage(Base b)의 경우는 암시적 형변환이 필요하다.
             */
            Derived d = new Derived();
            WriteLine("Calling ECSharp24.WriteMessage");
            WriteMessage(d);                    //WriteMessage<T>(T obj) 호출
            WriteLine();

            /* 명시적/암시적 형변환에 따라 어떤 오버로딩 메서드를 선택하는지 확인해두자
             */ 

            WriteLine("Calling through IMessageWriter interface");
            WriteMessage((IMessageWriter)d);    //WriteMessage(IMessageWriter obj) 호출
            WriteLine();

            WriteLine("Cast to base object");
            WriteMessage((Base)d);              // WriteMessage(Base b) 호출
            WriteLine();

            AnotherType anObject = new AnotherType();
            WriteLine("Another Type text:");
            WriteMessage(anObject);             //WriteMessage<T>(T obj) 호출
            WriteLine();

            WriteLine("Cast to IMessageWriter:");
            WriteMessage((IMessageWriter)anObject); //WriteMessage(IMessageWriter obj) 호출
        }

        /* 위의 예시에서 봤듯이 베이스 클래스와 이로부터 파생된 클래스에 대해서 모두 수행 가능하도록 하기 위해 제네릭을 특화specialization하려는 시도는 바람직하지 않다.
         * 특히 인터페이스에 대해 제네릭을 특화하게 되면 오류가 발생할 가능성이 너무 높다. 
         * 예외적으로 숫자 타입에 대해서는 괜찮은데 사실 정수 타입과 실수 타입 사이에는 아무런 상속 관계도 없다.
         * 
         * 제네릭 메서드의 타입 매개변수로 특정 타입이 주어질 경우 그에 부합하도록 제네릭 특화를 수행하기로 결정했다면, 
         * 해당 타입뿐 아니라 이 타입을 상속한 모든 파생 타입에 대해서도 특화를 수행해야 한다.
         * 
         * 인터페이스에 대해 특화를 수행하기로 결정했다면 이 인터페이스를 구현하고 있는 모든 타입에 대해서도 특화를 수행해야 한다.
         */ 

        /// <summary>
        /// 아래와 같이 제네릭 메서드 Foo에 대해 Base 클래스 타입을 특화시키려 한다면
        /// 
        /// Base 뿐만 아니라 Base를 상속받는 모든 타입 (여기서는 Derived)에 대해서도 특화해야 된다는 이야기가 된다.
        /// </summary>
        static void Foo<T>(T obj) { }
        static void Foo(Base b) { }
        static void Foo(Derived d) { }
    }
}