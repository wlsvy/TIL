using System;

namespace EffectiveCSharp
{
    public class ECSharp13
    {
        public class MySingleton
        {
            //멤버 초기화 구문 사용 예
            private static readonly MySingleton s_Instance = new MySingleton();
            public static MySingleton Instance => s_Instance;

            private MySingleton() { }
        }

        public class MySingleton2
        {
            //정적 생성자 사용 예
            private static readonly MySingleton2 s_Instance;
            public static MySingleton2 Instance => s_Instance;

            static MySingleton2()
            {
                s_Instance = new MySingleton2();
            }
            private MySingleton2() { }
        }
    }
}