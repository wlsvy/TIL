using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;
using System.Threading.Tasks;

namespace EffectiveCSharp
{
    /// <summary>
    /// 공변성과 반공변성을 지원하라
    /// </summary>
    public static class ECSharp22
    {
        /* 타입의 가변성 variance, 즉 공변covariance과 반공변contravariance은 특정 타입의 객체를 다른 타입의 객체로 반환할 수 있는 성격을 일컫는다.
         * 이러한 변환을 지원하려면 제네릭 인터페이스나 델리게이트의 정의 부분에 제네릭 공변/반공변을 지원한다는 의미의 데코레이터decorator를 추가해야 한다.
         * 
         * 가변성의 반대는 불변성invariant이다.
         * 
         * 제네릭이 처음 소개됐을 당시에는 공변/반공변이 지원되지 않았고, 따라서 컴파일러는 다소 엄밀하게 제네릭 타입을 다뤘다.
         * 제네릭은 모두 불변이었으며 타입 매개변수가 다른 경우 대체가 불가능했다. 
         * 하지만 C# 4.0 이후부터는 공변과 반공변을 통해서 제네릭 타입의 대체 가능성을 지정할 수 있도록 개선되었다.
         * 
         * 공변성 -> 타입 매개변수 간 다형성이 허용되는 범위 내 제네릭 클래스 형변환 가능, (업캐스팅)
         * 반공변성 -> 타입 매개변수 간 타입 안전성이 허용되는 범위 내 제네릭 클래스 형변환 가능 (다운캐스팅) (이 설명이 틀릴 수도 있다.)
         */
         
        public abstract class CelestialBody
        {
            public double Mass;
            public string Name;
        }
        public class Planet : CelestialBody { }
        public class Moon : CelestialBody { }
        public class Asteroid : CelestialBody { }

        /// <summary>
        /// 아래 메서드는 CelestialBody 배열을 공변적으로 다루고 있으며 이 작업은 안전하게 수행된다.
        /// </summary>
        public static void CoVariantArray(CelestialBody[] baseItems)
        {
            foreach(var thing in baseItems)
            {
                Console.WriteLine($"{thing.Name} has a mass of {thing.Mass} kg");
            }
        }

        /// <summary>
        /// 아래 메서드 역시 배열을 공변적으로 다루지만 이 작업은 안전하지 않다. 할당구문은 예외를 일으킬 것이다.
        /// </summary>
        public static void UnsafeVariantArray(CelestialBody[] baseItems)
        {
            baseItems[0] = new Asteroid { Name = "Hygiea", Mass = 8.85e19 };
        }

        public delegate void DelegateNoDeco<T>(T arg);
        public delegate void DelegateIn<in T>(T arg);
        //public delegate void DelegateOut<out T>(T arg);

        public static void RunSample()
        {
            //파생 클래스의 객체를 베이스 클래스의 배열에 할당하면 동일한 문제가 발생한다.
            CelestialBody[] spaceJunk = new Asteroid[5];
            spaceJunk[0] = new Planet();
        }

        /* 컬렉션에 대한 공변성은 컬렉션에 저장할 타이들이 상속 관계에 있을 때 고려 대상이 된다.
         * CelestialBody 타입이 매개변수를 취하는 메서드에는 Planet 타입의 객체를 넘겨줄 수 있다.
         * 유사하게 CelestialBody[] 타입의 매개변수를 취하는 메서드에는 Planet[] 타입의 객체를 넘겨줄 수 있다.
         */

        /// <summary>
        /// 다음 메서드에는 List<Planet> 타입의 객체를 인자로 전달할 수 있다.
        /// 
        /// 이것이 가능한 이유는 IEnumerable<T> 의 T가 out으로 선언되어 있기 때문이다.
        /// IEnmerator<T> 의 T 역시 out으로 선언되어 있다.
        /// 
        /// 이는 타입 매개변수 T를 출력output 위치에서만 사용하겠다고 컴파일러에게 알려주는 것이다.
        /// 출력 위치란 함수의 반환값, 속성의 get 접근자, 그리고 델리게이트의 일부 위치에서만 T를 사용할 수 있음을 말한다.
        /// 
        /// IEnumerable<out T> 라고 선언했기 때문에 컴파일러는 시퀀스 내에서 T의 내용을 조회는 하겠지만 내용을 수정하지는 않을 것이라고 생각한다.
        /// 이 경우 모든 Planet을 CelestialBody로 다뤄도 올바르게 작동한다.
        /// 
        /// IEnumerator<T> 가 공변이므로 IEnumerable<T> 역시 공변이 될 수 있다.
        /// 만약 IEnumerable<T> 가 공변이 아닌 인터페이스를 반환한다면 컴파일러가 에러를 일으킬 것이다.
        /// </summary>
        public static void CovariantGeneric(IEnumerable<CelestialBody> baseItems)
        {
            foreach(var thing in baseItems)
            {
                Console.WriteLine($"{thing.Name} has a mass of {thing.Mass} kg");
            }
        }

        /// <summary>
        /// 다음과 같이 IList 컬렉션을 매개변수로 받아서 첫 번째 항목을 수정하는 메서드의 경우 이 인자는 공변이 아니라 불변이 된다.
        /// 왜냐하면 IList<T> 의 T는 in/out 어떤 데코레이터도 사용되지 않았기 때문이다. 
        /// 따라서 이 경우 정확히 타입을 일치시켜야 한다.
        /// </summary>
        public static void InvariantGeneric(IList<CelestialBody> baseItems)
        {
            baseItems[0] = new Asteroid { Name = "Hygiea", Mass = 8.85e19 };
        }

        /* in 데코레이터를 통해 반공변 제네릭 인터페이스를 만들 수 있다.
         * 
         * in 데코레이터를 사용하면 컴파일러에게 타입 매개변수를 입력 위치에서만 사용할 것이라고 알려주게 된다.
         * IComparable<T> 의 경우 in T 로 선언되어 있다.
         * 
         * 이는 CelestialBody에서 mass 속성 등을 이용하여 IComparable<T>를 구현할 수 있음을 의미한다. 
         * 즉 2개의 Planet 객체를 비교하거나, Planet과 Moon객체 등 어떤 조합으로도 두 객체를 비교할 수 있다.
         * 
         * IEquatable<T> 의 경우는 불변이므로 주의해야 한다. 정의에 따라 Planet은 Moon과 같을 수 없다. 설상 이 둘은 다른 타입이다.
         */

        //델리게이트 활용 예시
        public delegate TResult Func<out TResult>();
        public delegate TResult Func<in T, out TResult>(T arg);
        public delegate TResult Func<in T1, T2, out TResult>(T1 arg1, T2 arg2); //책 예제에서는 T2 를 선언할 때 데코레이터를 지정하지 않았다. 실제 System.Func에는 in 이 붙어 있다.
        public delegate void Action<in T>(T arg);
        public delegate void Action<in T1, in T2>(T1 arg1, T2 arg2);
        public delegate void Action<in T1, in T2, T3>(T1 arg1, T2 arg2, T3 arg3); //책 예제에서는 T3 를 선언할 때 데코레이터를 지정하지 않았다.실제 System.Action에는 in 이 붙어 있다.

        //인터페이스 활용 예시
        public interface ICovariantDelegates<out T>
        {
            T GetAnItem();
            Func<T> GetAnItemLater();
            void GiveAnItemLater(Action<T> whatToDo);   //인터페이스 입장에서 공변
        }

        public interface IContravariantDelegates<in T>{
            void ActOnAnItem(T item);
            void GetAnItemLater(Func<T> item);
            Action<T> ActOnAnItemLater();           //인터페이스 입장에서 반공변
        }

        public class A { }
        public class B : A { }
        public class C : B { }

        /// <summary>
        /// 공변 반공변 예시
        /// </summary>
        static void Test()
        {
            Action<A> actionA = (A arg) => { };
            Action<B> actionB = actionA;  //반공변성, 파생 타입 매개변수의 Action으로 대입 가능
            Action<C> actionC = actionB;  //반공변성, 파생 타입 매개변수의 Action으로 대입 가능

            //actionA = actionB;  //컴파일 오류, 기반 타입 매개변수의 Action에는 대입 불가능

            Func<B> funcB = () => { return null; };
            Func<A> funcA = funcB; //공변성, 기반 타입 매개변수의 Func에는 대입 가능
            //Func<C> funcA = funcB; //컴파일 오류, 파생 타입 매개변수의 Func에는 대입 불가능

            Func<B, B> funcBB = (B arg) => { return null; };
            Func<C, A> funcCA = funcBB; //공변성, 반공변성 동시에 적용
        }
    }
}
