using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;
using System.Threading.Tasks;

namespace EffectiveCSharp
{
    /// <summary>
    /// 불필요한 객체를 만들지 말라.
    /// </summary>
    public static class ECSharp15
    {
        /*
         * 1. 자주 사용되는 지역변수(값 타입 말고 참조 타입)을 사용할때 마다 new로 생성하지 말고, 멤버 변수로 캐싱하는 것.
         * 2. 종속성 삽입(dependency injection)을 활용해 자주 사용되는 객체를 생성했다가 이를 활용하는 것. (<= 책 설명 ?? 이건 의존성 주입이 아닐텐데??)
         * 3. 변경 불가능한(immutable) 타입을 다룰 때 주의(ex : string)
         */

        //1번 방법 스킵. (예제가 너무 간단)
        //2번 방법 스킵. (객체가 없을 때만 생성 및 캐싱)

        public static class Case0
        {
            /// <summary>
            /// 변경 불가능한(immutable) 타입을 다룰 때 주의(ex : string)
            /// 
            /// string의 경우 한번 값이 정해지면 문자열의 내용은 수정이 불가능하다.
            /// 문자열의 값을 바꾸는 것은 사실 새로운 string을 생성하고, 이전 string을 가비지로 만들어버리는 것이다.
            /// 
            /// 따라서 해당 함수는 굉장히 비효율적이다. 
            /// += 연산자는 기존 문자열의 새로운 문자열을 더하는 것이 아닌 string 객체를 새로 생성한다.
            /// </summary>
            public static void RunSample0()
            {
                string msg = "Hello, ";
                msg += s_UserName;
                msg += ", Today is ";
                msg += System.DateTime.Now.ToString();
                Console.WriteLine(msg);
            }

            /// <summary>
            /// 위의 방법을 보안
            /// 
            /// 문자열 보간, 혹은 string builder 활용
            /// 특히 여러 단계를 거쳐 객체를 구성해야 하는 경우 stringbuilder와 같은 빌더 클래스를 활용하는 것을 고려해보자. 
            /// </summary>
            public static void RunSample1()
            {
                string msg = $@"Hello, {s_UserName}. Today is {System.DateTime.Now.ToString()}";

                Console.WriteLine(msg);

                StringBuilder sb = new StringBuilder("Hello, ");
                sb.Append(s_UserName);
                sb.Append(". Today is ");
                sb.Append(System.DateTime.Now.ToString());

                msg = sb.ToString();
                Console.WriteLine(msg);
            }

            public static readonly string s_UserName = "Tom";
        }
    }
}