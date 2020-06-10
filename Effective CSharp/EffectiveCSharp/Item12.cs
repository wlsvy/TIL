using System;
using System.Collections.Generic;

namespace EffectiveCSharp
{
    public class ECSharp12
    {
        public class MyClass
        {
            //컬렉션을 선언하는 동시에 초기화
            private List<string> labels = new List<string>();   //멤버 변수를 올바르게 초기화
        }

        public struct MyValue
        {
            public int value;

            public MyValue(int val) { value = val; }
        }

        public class MyClass2
        {
            MyValue myVal1; //0으로 초기화
            MyValue myVal2 = new MyValue(); //반복해서 0으로 초기화 

            //이 코드의 두 문장은 모두 변수를 0으로 초기화한다.
            //첫 번째 문장은 myVal1 이 사상된 메모리 블록은 모두 0으로 설정한다.
            //두 번째 문장은 initObj라는 IL 명령을 사용하는데 박싱/언박싱 된 myVal2 변수 모두에 대해서 0으로 초기화한다.
            //이 과정으로 인해 약간의 추가 시간이 소요된다.
        }

        public class MyClass3
        {
            //컬렉션을 선언하는 동시에 초기화
            private List<string> labels = new List<string>();   //멤버 변수를 올바르게 초기화

            public MyClass3() { }
            public MyClass3(int size)
            {
                labels = new List<string>(size);
                //만약 이 생성자를 호출하게 되면, 실제로 2갱의 List<> 객체가 생성되며 그 중 하나는 즉각 가비지가 된다.
                //불필요한 코드가 포함된 꼴이다.

                //풀어쓰면
                //labels = new List<string>();
                //labels = new List<string>(size);
            }
        }
    }
}