using System;
using System.Collections.Generic;

//할당 구무보다 멤버 초기화 구문이 좋다.

namespace EffectiveCSharp
{
    public class ECSharp12
    {
        public class MyClass
        {
            //컬렉션을 선언하는 동시에 초기화
            private List<string> labels = new List<string>();   //멤버 변수를 올바르게 초기화
        }

        public struct MyValueType
        {
            public int value;

            public MyValueType(int val)
            {
                value = val;
            }
        }

        /// <summary>
        /// 객체를 0이나 null로 초기화하는 경우, 멤버 초기화 구문을 사용하지 않는 것이 좋다.
        /// 
        /// 기본 시스템 초기화 루틴은 코드를 실행하기 전에 모든 값을 0으로 설정하기 때문이다.
        /// </summary>
        public class MyClass2
        {
            MyValueType myVal1; //초기화 구문이 없어도, 0으로 초기화
            MyValueType myVal2 = new MyValueType(0); //0으로 초기화한 뒤, 반복해서 0으로 초기화 

            //이 코드의 두 문장은 모두 변수를 0으로 초기화한다.
            //첫 번째 문장은 myVal1 이 사상된 메모리 블록은 모두 0으로 설정한다.
            //두 번째 문장은 initObj라는 IL 명령을 사용하는데 박싱/언박싱 된 myVal2 변수 모두에 대해서 0으로 초기화한다.
            //이 과정으로 인해 약간의 추가 시간이 소요된다.
        }

        public class MyClass3
        {
           
            private List<string> labels = new List<string>();    //컬렉션을 선언하는 동시에 초기화

            public MyClass3() { }
            public MyClass3(int size)
            {
                labels = new List<string>(size);
                //만약 이 생성자를 호출하게 되면, 실제로 2개의 List<> 객체가 생성되며 그 중 하나는 즉각 가비지가 된다.
                //불필요한 코드가 포함된 꼴이다.

                //풀어쓰면
                //labels = new List<string>();
                //labels = new List<string>(size);
            }
        }

        /*
         * 예외 처리가 필요한 경우 역시, 멤버 초기화 구문 대신, 생성자 본문에 코드를 넣는 것이 좋다.
         * 멤버 초기화 구문은 try로 감쌀 수 없기 때문이다.
         * 
         */ 
    }
}