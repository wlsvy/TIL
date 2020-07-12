using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;
using System.Threading.Tasks;

namespace EffectiveCSharp
{
    /// <summary>
    /// 생성자 내에서는 절대로 가상 함수를 호출하지 말라
    /// </summary>
    public static class ECSharp16
    {
        public static class Case0
        {
            public class Base
            {
                protected Base()
                {
                    VFunc();
                }

                protected virtual void VFunc()
                {
                    Console.WriteLine("VFunc in B");
                }
            }

            public class Derived : Base
            {
                private readonly string msg = "Set by initializer";

                public Derived(string msg)
                {
                    this.msg = msg;
                }

                protected override void VFunc()
                {
                    Console.WriteLine(msg);
                }
            }

            /// <summary>
            /// 실행 결과는 Set By Initializer
            /// (C++ 이었다면 VFunc in B 가 출력되었겠지만)
            /// 
            /// C# 의 경우, 생성자의 본문에 들어서는 순간 해당 객체는 초기화가 완료된 것으로 간주한다.
            /// 하지만 이때, 모든 멤버 변수가 이 시점에 초기화되었다고 단정하기는 어렵다. 
            /// -> 멤버 변수 초기화 구문을 완료했을 뿐이며, 파생 클래스의 생성자 본문은 수행하지 않았기 때문이다.
            /// 
            /// 즉, Set By Initializer 가 출력된 이후, 파생 클래스의 msg 변수가 Constructed in Main으로 초기화 되는 것.
            /// 
            /// 생성자에서 가상함수를 호출하는 것은 굉장히 위험하다. 
            /// 위의 예시에서 파생클래스의 msg 변수는 readonly 선언이 되어있지만, 객체가 생성되는 잠깐의 순간, 초기화가 되어있지 않은 상태로 활용된다.
            /// </summary>
            public static void RunSample()
            {
                var d = new Derived("Constructed in Main");
            }

        }
        
    }


    
}