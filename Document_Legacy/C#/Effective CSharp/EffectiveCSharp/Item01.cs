using System;

namespace EffectiveCSharp
{
    //지역변수를 선언할 때는 var 를 사용하는 것이 낫다

    /// <summary>
    /// var를 사용하면 개발자 입장에서는 변수의 타입과 같은 부차적인 부분보다 변수의 의미 파악에 더 집중할 수 있게 된다. 
    /// 컴파일러 관점에서는 개발자가 특정 객체의 타입을 명시적으로 지정하지 않더라도 객체 생성에 문제가 있을 경우 오류를 보고할 수 있다.
    /// </summary>
    namespace ECSharp01
    {
        /*
         * 타입을 명시적으로 지정할 경우 타입 안전성이 향상될 것이라 생각하지만 이는 사실이 아니다. 
         * IQueryable<T> 와 Ienumerable<T> 의 예와 같이 개발자가 올바르게 타입을 지정하지 않으면 오히려 타입 안정성을 해치는 꼴이 될 수 있다. 
         * (IQueryable<T> 를 IEnumerable<T> 로 변환해버리면 IQueryable<T>의 장점을 잃어버리게 됩니다)
         */

        class MyType { }
        class AccountFactory
        {
            public static int CreateSavingsAccount() { return 0; }
        }
        class Factory
        {
            static public object GetObject() { return null; }
        }

        public class Sample
        {
            /// <summary>
            ///  c#에서 특정 변수를 var로 선언하면 동적 타이핑(dynamic typing) 이 수행되는 것이 아니라 오른쪽의 타입을 확인하여 왼쪽 변수의 타입을 결정하게 된다. 
            /// </summary>
            private void DoSomething()
            {
                var foo = new MyType();
                var thing = AccountFactory.CreateSavingsAccount();
            }

            private int GetMagicNumber() { return 0; }

            /// <summary>
            /// 다만 내장 숫자 타입(int, float, double 등)을 선언할 때는 명시적으로 타입을 선언하는 편이 낫다.
            /// 
            /// 아래에서 값 형식 var는 f의 타입에 따라 달라질 수 있다. 
            /// 이 경우는 명시적으로 타입을 선언하는 것이 추후에 발생할 수 있는 위험성을 사전에 방지할 수 있게 한다.
            /// </summary>
            private void DoCal()
            {
                var f = GetMagicNumber();
                var total = 100 * f / 6; 
                                         
            }
        }
    }
}
