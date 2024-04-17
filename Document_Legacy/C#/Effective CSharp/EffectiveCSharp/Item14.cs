using System;
using System.Collections.Generic;

namespace EffectiveCSharp
{
    /// <summary>
    /// 초기화 코드가 중복되는 것을 최소화하라
    /// </summary>
    public class ECSharp14
    {
        /// <summary>
        /// 생성자 코드가 중복될 때, C++ 에서는 private 헬퍼 메소드를 작성하여 공용으로 사용하지만, C#에서는 공용 생성자를 이용하는 방법이 있다.
        /// 
        /// C# 컴파일러는 공용 생성자를 이용하는 초기화 방식을 매우 특별한 문법으로 인식한다. 
        /// 변수에 대한 중복 초기화 코드를 제거해줄 뿐 아니라 베이스 클래스의 생성자가 반복적으로 호출되는 것도 막아준다. 
        /// 즉 객체 초기화를 위해 수행해야 하는 코드를 최적화해준다.
        /// </summary>
        public class MyClass
        {
            private List<int> m_Data;

            private string name;

            //공용생성자
            public MyClass() : this(0, "") { }  //name의 기본값으로 string.Empty를 사용하지 않았는데 이는 string.Empty가 컴파일 타임 상수가 아니기 때문.
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
            //new() 제약 조건을 만족시키려면 이 생성자가 필요하다
            public MyClass2() : this(0, "") { } 
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

        /*
         * C#에서 특정 타입으로 첫 번째 인스턴스를 생성할 때 수행되는 과정
         * 
         * 1. 정적 변수의 저장 공간을 0으로 초기화
         * 2. 정적 변수에 대한 초기화 구문 수행
         * 3. 베이스 클래스의 정적 생성자 수행
         * 4. 정적 생성자 수행
         * 5. 인스턴스 변수의 저장 공간을 0으로 초기화
         * 6. 인스턴스 변수에 대한 초기화 구문 수행
         * 7. 적절한 베이스 클래스의 인스턴스 생성자 수행
         * 8. 인스턴스 생성자 수행
         * 
         * 클래스 자체에 대한 초기화 작업은 단 한 번만 이뤄지기 때문에 동일한 타입으로 추가 인스턴스를 생성하면 앞의 단계 중 5 단계에서부터 수행된다. 
         * 또한 컴파일러가 생성자 내에 중복된 멤버 초기화 코드를 생성하지 않도록 6단계와 7단계는 최적화되어 있다.
         * 
         * C#은 객체가 생성될 때 어떤 식으로든 모든 객체가 초기화될 것임을 보장한다. 
         * 인스턴스를 생성하면 인스턴스 내의 모든 멤버들이 (정적 멤버, 인스턴스 멤버를 가리지 않고) 최소한 0으로 초기화된다. 
         * 생성자를 작성할 때 유념할 부분은 멤버들을 원하는 값으로 초기화할 때 가능한 한 번만 초기화가 이뤄지도록 해야한다는 것이다.
         */
    }
}
