using System;
using System.Collections.Generic;
using System.Linq;
using System.Runtime.Serialization;
using System.Text;
using System.Threading.Tasks;

namespace EffectiveCSharp
{
    /// <summary>
    /// 사용자 지정 예외 클래스를 완벽하게 작성하라
    /// </summary>
    public static class ECSharp47
    {

        /* 예외는 오류를 보고하기 위한 매커니즘이며 예외가 발생한 위치로부터 상당히 떨어진 위치에서조차 발생한 예외를 처리할 수 있는 방법을 제공해야 합니다.
         * 오류가 발생한 원인을 나타내기 위한 정보는 반드시 예외 객체 내에 포함돼야 합니다.
         * 
         * 서로 다른 예외 클래스를 활용하여 예외를 발생시키는 유일한 이유는 
         * catch문을 사용하여 예외를 다루는 코드를 작성할 개발자가 그 각각을 구분하여 서로 다른 작업을 수행할 수 있도록 해주기 위함입니다.
         */ 

        /// <summary>
        /// 사용자 정의 예외 클래스를 작성할 때는
        /// 1. 우선 예외 클래스를 작성하면서 개별 예외 클래스의 고유한 책임을 명확하게 규정해야 합니다.
        /// 2. 모든 예외 클래스의 이름을 Exception으로 끝나야 합니다.
        /// 3. System.Exception 클래스나 혹은 더 적절한 예외 클래스를 상속해서 구현해야 합니다.
        /// 베이스 클래스에서 직접 기능을 추가해야 하는 경우는 거의 없습니다.
        /// 서로 다른 예외 클래스를 만드는 이유는 catch문 내에서 예외가 발생한 원인을 서로 구분하기 위함입니다.
        /// 
        /// 아래처럼 새로운 예외 클래스를 구현할 때는 4개의 생성자를 작성해야 합니다.
        /// 마지막 생성자는 예외 클래스가 serialize 가능함을 의미합니다.
        /// </summary>
        [Serializable]
        public class MyAssemblyException : Exception
        {
            public MyAssemblyException() : base() { }
            public MyAssemblyException(string s) : base(s) { }
            public MyAssemblyException(string s, Exception e) : base(s, e) { }
            protected MyAssemblyException(SerializationInfo info, StreamingContext cxt) : base(info, cxt) { }
        }

        public class ThirdPartyException : Exception
        {
            public ThirdPartyException() : base() { }
            public ThirdPartyException(string s) : base(s) { }
            public ThirdPartyException(string s, Exception e) : base(s, e) { }
            protected ThirdPartyException(SerializationInfo info, StreamingContext cxt) : base(info, cxt) { }
        }

        /// <summary>
        /// 매개변수로 Exception을 취하는 생성자에 대해서는 좀 더 살펴볼 필요가 있습니다. 
        /// 때때로 외부 라이브러리가 예외를 유발하는 경우가 있습니다.
        /// 
        /// 라이브러리 사용자 관점에서는 외부 라이브러리의 예외에 대해서는 복구 작업을 위한 세부정보를 확인하기 어려우므로,
        /// 발생한 예외를 단순히 전달해야 하는 경우가 있습니다.
        /// 
        /// 예외 객체를 생성할 때는 오류 상황을 세부적으로 나타내는 고유한 정보를 포함시키는 것이 좋습니다.
        /// 따라서 이 경우 새로운 예외 객체를 이용하여 관련 정보를 채우되, 앞서 발생한 예외가 있다면 InnerException 속성에 저장하는 것이 좋습니다.
        /// 이렇게 하면 기존 예외에 더항 추가적인 정보를 제공할 수 있습니다.
        /// </summary>
        public static void DoSomeWork()
        {
            try
            {
                //외부 라이브러리에서 예외를 던질 가능성이 있는 특정 작업을 수행합니다.
            }
            catch(ThirdPartyException e)
            {
                //외부 라이브러리의 예외를 InnerException에 포함시킨 새로운 예외 객체를 생성합니다.
                //예외 변환Exception Translation : 저수준의 예외를 보다 세부적인 상태 정보를 포함하는 고수준의 예외로 변경하는 작업.
                var msg = $"Problem with {e.ToString()} using library";
                throw new MyAssemblyException(msg, e);
            }
        }
    }
}