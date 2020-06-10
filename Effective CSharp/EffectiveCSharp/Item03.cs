using System;

namespace EffectiveCSharp
{
    namespace ECSharp03
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

        public class ECSharp03
        {
            public void DoSomeThing()
            {
                object o = Factory.GetObject();

                MyType t = o as MyType; //o가 MyType이 아니면 t 는 null
                if (t != null)
                {
                    //MyType 타입 객체 일때   
                }
                else
                {
                    //오류 보고
                }
            }

            public void DoSomeThing2()
            {
                object o = Factory.GetObject();

                try
                {
                    MyType t;
                    t = (MyType)o;  //o가 MyType이 아니면 실패
                                    //MyType 타입 객체 사용  
                }
                catch (InvalidCastException)
                {
                    //오류 보고
                }
            }

            public class CastType { }
            public class SecondType
            {
                private CastType _value;
                public static implicit operator CastType(SecondType t)  //형변환 연산자 오버로딩
                {
                    return t._value;
                }

            }

            public void DoSomeThing3()
            {
                object o = Factory.GetObject(); //o 가 SecondType 이라고 가정

                //첫 번째 버전
                CastType t = o as CastType; //o가 CastType이 아니면 null
                if (t != null)
                {
                    //CastType 타입의 t 객체 사용
                }
                else
                {
                    //오류보고
                }

                //두 번째 버전
                try
                {
                    CastType t1;
                    t1 = (CastType)o; //o가 CastType 이 아니면 실패
                                      //CastType 타입의 t1 객체 사용
                }
                catch (InvalidCastException)
                {
                    //형변환 오류보고
                }
            }

            public void DoSomeThing4()
            {
                object o = Factory.GetObject();

                //int i = o as int;   //컴파일 오류. 값 타입은 null이 될 수 없다. o가 null일때는 int에 어떤 값을 저쟝해야 할지 알 수 없다

                var ival = o as int?;  //컴파일 가능. nullable 값 타입


            }
        }
    }
}