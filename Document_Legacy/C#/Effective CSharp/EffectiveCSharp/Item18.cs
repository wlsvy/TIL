using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;
using System.Threading.Tasks;

namespace EffectiveCSharp
{
    /* 타입을 제네릭의 형태로 정의하는 것을 제네릭 타입 정의(generic type definition)라고 한다.
     * 
     * 타입 매개변수에 구체적인 타입을 지정한 경우를 닫힌 제네릭 타입 Closed Generic Type 이라고 한다.
     * 여러 타입 매개변수 중 일부만 구체적인 타입을 지정한 경우 이를 열린 제네릭 타입 Open Generic Type 이라고 한다.
     * 
     * 닫힌 제네릭 타입을 만들 때 타입 매개변수에 값 타입 혹은 참조 타입이 지정될 때 다른 규칙이 적용된다.
     * - 참조 타입의 경우 항상 동일한 머신 코드가 생성되어 이를 공유하게 된다.
     * - JIT 컴파일러는 값 타입이 주어지는 경우 서로 다른 머신 코드를 생성한다.
     * 
     * 값 타입이 주어지는 경우 JIT 컴파일러는 두 단계를 거친다.
     * 1. 닫힌 제네릭 타입을 표현하기 위한 새로운 IL 클래스를 생성
     * 2. 대체가 완료된 타입을 이용하여 실제로 머신 코드를 생성.
     * 
     *  - 두 단계가 필요한 이유는 어셈블리가 로드되는 시점에 JIT 컴파일러가 클래스의 머신 코드를 생성하는 것이 아니라, 
     *  로드된 타입 내의 특정 메서드가 최초로 호출되는 시점에 호출된 메서드만을 JIT 컴파일하기 때문이다.
     *  
     *  - 타입별로 서로 다른 코드가 생성된다는 것은 런타임에 메모리의 풋프린트가 커진다는 것을 의미한다.
     *  타입 매개변수가 값 타입인 경우 제네릭 타입은 개별적인 IL 코드를 가진다.
     *  -> 값 타입의 유형에 따라 서로 다른 머신코드를 생성해야 하기 때문.
     *  -> 하지만 이 방식 덕분에 값 타입을 지정했을 때의 박싱과 언박싱을 피할 수 있다.
     *  -> 또한 컴파일러가 타입 매개변수에 대한 타입 안정성을 보장해주므로 런타임에 타입의 유형을 매번 확인할 필요가 없다.
     * 
     */

    /// <summary>
    /// 반드시 필요한 제약 조건만 설정하라
    /// </summary>
    public static class ECSharp18
    {

        public static bool AreEqual<T>(T left, T right) where T : IEquatable<T>
            => left.Equals(right);

        /// <summary>
        /// 위의 메소드와의 차이, 만약 T 타입이 IEquatable 을 상속받았더라도 System.Object.Equals()를 호출하도록 코드를 생성한다.
        /// 
        /// C++ 의 템플릿과, C# 의 제네릭의 차이를 보여주기도 하는데, C# 컴파일러는 제약 조건에 설정된 정보만을 이용하여 IL을 생성한다.
        /// 타입 매개변수로 지정된 타입이 설사 인스턴스화되었을 때 더 나은 메서드를 가졌다 하더라도 제네릭 타입을 컴파일할 때 알려진 내용이 아니라면 사용하지 않는다.
        /// </summary>
        public static bool AreEqual2<T>(T left, T right)
            => left.Equals(right);

        public class Widget : IEquatable<Widget>
        {
            public bool Equals(Widget rhs)
            {
                System.Console.WriteLine("Use IEquatable.Equals()");
                return true;
            }
        }
        public class Gadget
        {
        }

        public static void RunSample()
        {
            Widget w0 = new Widget();
            Widget w1 = new Widget();
            Gadget g0 = new Gadget();
            Gadget g1 = new Gadget();

            System.Console.WriteLine("=====AreEquals");

            AreEqual(w0, w1);       // IEquatable.Equals() 호출
            //AreEqual(g0, g1);

            System.Console.WriteLine("=====AreEquals2");

            AreEqual2(w0, w1);      //System.Object.Equals()  호출
            AreEqual2(g0, g1);      //System.Object.Equals()  호출

            var i = MakeDefault<int>();
            var w = MakeDefault<Widget>();
        }

        /*
         * 기본 생성자 제약 조건을 설정할 때는 new() 대신 default()를 활용하는 방안도 고려해보자.
         * 
         * C#의 default() 연산자는 특정 타입의 기본값을 가져오는데, 값 타입에 대해서는 0, 참조 타입에 대해서는 null을 가져온다.
         * 따라서 new()를 default()로 바꾸면 값 타입과 참조 타입에 대해서 모두 사용할 수 있다.
         * 하지만 참조 타입에 대해서 new() 와 default()의 의미는 매우 다른 것을 기억할 것
         * 
         */

        public static T MakeTypeByRandom<T>() where T : new()
        {
            if(System.DateTime.Now.Second % 2 == 0)
            {
                return new T();
            }
            return default(T);
        }

        /// <summary>
        /// new() 제약조건을 필요로 하는 경우가 있다.
        /// 
        /// 이 경우 참조타임에 경우 null여부를 테스트해야 하기 때문에 값 타입과는 동작방식이 다르다.
        /// 하지만 값 타입인 경우에도 이 메서드를 사용할 수 있는데
        /// T가 값 타입인 경우, JIT 컴파일러가 null 테스트 코드를 제거해주기 때문이다.
        /// </summary>
        public static T MakeDefault<T>() where T : new()
        {
            var v = MakeTypeByRandom<T>();
            if(v == null)
            {
                return new T();
            }
            return v;
        }
    }
}