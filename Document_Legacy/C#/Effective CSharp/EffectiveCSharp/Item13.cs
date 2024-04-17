using System;

//정적 클래스 멤버를 올바르게 초기화하라

namespace EffectiveCSharp
{
    /// <summary>
    /// 정적 멤버 변수를 포함하는 타입이 있다면 인스턴스를 생성하기 전에 반드시 정적 멤버 변수를 초기화해야 한다. 
    /// 이를 위해 C# 에서는 정적 멤버 초기화 구문과 정적 생성자라는 두 가지 기능을 제공한다. 
    /// 정적 생성자는 타입 내에 정의된 모든 메서드, 변수, 속성에 최초로 접근하기 전에 자동으로 호출되는 특이한 메서드다.
    /// 
    /// 인스턴스 멤버 초기화와 마찬가지로 정적 멤버를 간단히 초기화하는 경우라면 정적 생성자를 사용하기 보다는 멤버 초기화 구문을 사용하는 것이 좋다. 
    /// 하지만 초기화 과정이 복잡하다면 정적 생성자를 사용하는 것도 나쁘지 않다.(생성자 안에 try catch 문은 넣을 수도 있다.)
    /// </summary>
    public class ECSharp13
    {
        public class MySingleton
        {
            //멤버 초기화 구문 사용 예
            private static readonly MySingleton s_Instance = new MySingleton();
            public static MySingleton Instance => s_Instance;

            private MySingleton() { }
        }

        public class MySingleton2
        {
            //정적 생성자 사용 예
            private static readonly MySingleton2 s_Instance;
            public static MySingleton2 Instance => s_Instance;

            /// <summary>
            /// 앱도메인app domain 내에서 CLR 이 특정 타입에 접근해야 하는 경우 정적 생성자를 우선적으로 호출한다. 
            /// 모든 타입은 정적 생성자를 하나만 가질 수 있으며 어떠한 인자도 넘길 수 없다. 
            /// 정적 생성자는 CLR에 의해서 호출되기 때문에 예외가 발생할 가능성이 있는 경우라면 매우 조심스럽게 다뤄줘야 한다. 
            /// 정적 생성자 내에서 예외가 발생하면 CLR은 TypeInitializationException 을 던지고 응용프로그램을 종료해 버린다.
            /// </summary>
            static MySingleton2()
            {
                s_Instance = new MySingleton2();
            }
            private MySingleton2() { }
        }
    }
}