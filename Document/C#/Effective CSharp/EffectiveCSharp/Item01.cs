using System;

namespace EffectiveCSharp
{
    //지역변수를 선언할 때는 var 를 사용하는 것이 낫다
    namespace ECSharp01
    {
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
            private void DoSomething()
            {
                var foo = new MyType();
                var thing = AccountFactory.CreateSavingsAccount();
            }

            private int GetMagicNumber() { return 0; }

            private void DoCal()
            {
                var f = GetMagicNumber();
                var total = 100 * f / 6; // 여기서 값 형식 var는 f의 타입에 따라 달라질 수 있다. 
                                         //이 경우는 명시적으로 타입을 선언하는 것이 추후에 발생할 수 있는 위험성을 사전에 방지할 수 있게 한다.
            }
        }
    }
}
