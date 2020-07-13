using System;

//캐스트보다는 is, as 가 좋다.

namespace EffectiveCSharp
{
    /// <summary>
    ///형변환을 수행하는 경우 캐스팅을 사용하기보다 as 연산자를 사용하는 것이 좋다. 
    ///As를 사용하는 편이 더 안전하거니와 런타임에 더 효율적으로 동작한다. 
    ///
    /// 다만 as나 is 연산자를 사용하면 사용자 정의 형변환은 수행되지 않는다. => 
    /// 런타임에 객체의 타입이 변환하려는 타입과 정확히 일치할 경우에만 형변환이 성공적으로 수행된다. 
    /// 
    /// 형변환 과정에서 새로운 객체가 생성되는 경우는 거의 없다.
    /// </summary>
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
            /// <summary>
            ///예외적으로 as 연산자를 이용하여 박싱된 값 타입의 객체를 nullable 값 타입의 객체로 변환하는 경우 새로운 객체가 생성된다.
            ///
            /// 아래 2 개의 예시 코드를 비교해보면 첫 번째 예시가 읽기도 편하고 try/catch 문이 없어 더 빠르다.
            /// As, is는 런타임에 객체의 타입을 확인하고 필요에 따라 박싱을 수행하는 것을 제외하고는 어떤 작업도 수행하지 않는다.
            /// </summary>
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

            /// <summary>
            /// 임의의 객체가 형변환되기 위해서는 이 객체는 지정한 타입이거나 혹은 그 타입을 상속한 타입이어야 한다. 
            /// 반면 캐스팅의 경우는 객체를 지정한 타입으로 변환하기 위해서 형변환 연산자가 개입될 수 있다. (형변환 실패시 바로 에러를 던지는)
            /// </summary>
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

            /* 첫 번째, 두 번째 형변환 코드는 전부 실패. 
             * 첫 번째 경우는 o가 CastType이 아니기 때문
             * 두 번째 경우는 SecondType 에서 CastType으로 변환하는 연산자가 있더라도, 형변환 연산자를 통해 객체가 런타임에 어떤 타입일지 알 수 없기 때문. 컴파일러는 단순히 컴파일 타임에 객체가 어떤 타입으로 선언됐는지만 추적한다. 따라서 형변환 연산자는 런타임에 object 타입의 o 객체가 CastType으로 변환이 가능한지 고려하지 않는다.
             * 
             */

            /// <summary>
            /// 값 형식을 변환할 때
            /// 때로는 임의의 객체를 다른 타입으로 형변환 가능한지뿐 아니라 객체의 정확한 타입을 알고 싶을 때도 있다. 
            /// Is 연산자는 다형성polymorphism 규칙을 준수하기 때문에 특정 객체가 상속한 타입에 대해서 확인할 때도 true를 반환한다. 
	        /// 
            /// 이에 반해 GetType() 메서드는 런타임에 객체의 타입을 정확히 가져온다.
            /// 이 메서드는 is 나 as 문장이 제공하는 수준 이상으로 엄격히 검사할 때 사용한다.
            /// </summary>
            public void DoSomeThing4()
            {
                object o = Factory.GetObject();

                //int i = o as int;   //컴파일 오류. 값 타입은 null이 될 수 없다. o가 null일때는 int에 어떤 값을 저쟝해야 할지 알 수 없다

                var ival = o as int?;  //컴파일 가능. nullable 값 타입


            }
        }
    }
}