using System;
using System.Collections.Generic;

namespace EffectiveCSharp
{
    /// <summary>
    /// 초기화 코드가 중복되는 것을 최소화하라
    /// </summary>
    public class ECSharp14
    {
        public class MyClass
        {
            private List<int> m_Data;

            private string name;

            //공용생성자
            public MyClass() : this(0, "") { }
            public MyClass(int initCount) : this(initCount, string.Empty) { }
            public MyClass(int initCount, string name)
            {
                m_Data = (initCount > 0) ? new List<int>(initCount) : new List<int>();
                this.name = name;
            }
        }

        public class MyClass2
        {
            private List<int> m_Data;

            private string name;

            //디폴트 매개변수 활용
            public MyClass2() : this(0, "") { } //new() 제약 조건을 만족시키려면 이 생성자가 필요하다
            public MyClass2(int initCount = 0, string name = "")
            {
                m_Data = (initCount > 0) ? new List<int>(initCount) : new List<int>();
                this.name = name;
            }
        }

        public class MyClass3
        {
            private List<int> m_Data;

            private string name;

            //C++ 과 달리 생성자 공용 메소드를 따로 구현해서 만든다면
            public MyClass3()
            {
                CommonConstructor(0, "");

                //IL 로 풀어보면
                //object(); //인스턴스 초기화 코드가 이 위치에 포함된다.
                //CommonConstructor(0, "");
            }
            public MyClass3(int initCount = 0, string name = "")
            {
                CommonConstructor(initCount, name);

                //IL 로 풀어보면
                //object(); //인스턴스 초기화 코드가 이 위치에 포함된다.
                //CommonConstructor(initCount, name);
            }
            private void CommonConstructor(int initCount, string name)
            {
                //만약 readonly 멤버가 있다면 생성자가 아닌 여기서는 초기화가 불가능하다.
                m_Data = (initCount > 0) ? new List<int>(initCount) : new List<int>();
                this.name = name;
            }
        }

        public class MyClass4
        {
            private List<int> m_Data;

            private string name;

            public MyClass4() : this(0, "")
            {
                //IL 로 풀어보면
                //변수에 대한 초기화 코드가 없다.
                //다음과 같은 생성자 호출
                //this(0, "")
            }
            public MyClass4(int initCount) : this(initCount, string.Empty)
            {
                //IL 로 풀어보면
                //변수에 대한 초기화 코드가 없다.
                //다음과 같은 생성자 호출
                // this(initCount, string.Empty)
            }
            public MyClass4(int initCount, string name)
            {
                //IL 로 풀어보면
                //object(); //인스턴스 초기화 코드가 이 위치에 포함된다.
                m_Data = (initCount > 0) ? new List<int>(initCount) : new List<int>();
                this.name = name;
            }
        }

    }
}
