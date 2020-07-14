using System;

//nameof() 연산자를 적극 활용하라

namespace EffectiveCSharp
{
    /// <summary>
    /// nameof 연산자를 사용하면 이름을 완전히 바꾸거나 수정할 경우에도 손쉽게 그 변경 사항을 반영할 수 있다. 
    /// 인자의 이름을 매개변수로 취하는 메서드를 사용할 때 저지르는 실수를 미연에 방지할 수 있다.
    /// 
    /// 이질적인 플랫폼과 서로 다른 언어로 개발된 프로그램 사이에서 데이터를 주고 받아야 하는 일이 많아졌으므로, 
    /// 언어적 차이를 극복하기 위해 문자열 식별자에 의존하는 간단한 라이브러리들이 많이 사용된다. 
    /// 하지만 문자열은 (오타가 있을 수 있고) 타입 정보를 알 수 없기 때문에 문제가 발생하기도 한다.
    /// </summary>
    public class ECSharp06
    {
        private Action<object, PropertyChangedEventArgs> PropertyChanged;
        public class PropertyChangedEventArgs
        {
            public PropertyChangedEventArgs(string val) { }
        }

        private string m_Value;
        public string Name  //nameof 사용예시
        {
            get
            {
                return m_Value;
            }
            set
            {
                if (value != m_Value)
                {
                    m_Value = value;
                    //Nameof 연산자를 활용하면 속성이름을 문자열로 쉽게 변경할 수 있다.
                    PropertyChanged?.Invoke(this, new PropertyChangedEventArgs(nameof(Name)));
                }
            }
        }

        /* 
	     * Nameof는 심볼의 이름을 평가하며 타입, 변수, 인터페이스, 네임스페이스에 대하여 사용할 수 있다. 
	     * 완전히 정규화된 이름(fully qualified name : 예 - System.Int.MaxValue) 을 사용할 수도 있지만 정규화되지 않은 이름도 제한 없이 사용할 수 있다. 
	     * 다만 제네릭 타입을 사용할 경우에는 부분적으로 제약이 있어서 모든 타입 매개변수를 지정한 닫힌 제네릭 타입만을 사용할 수 있다.
	     * 
	     * Nameof 항상 로컬 이름을 문자열로 반환하는 역할을 수행한다. 
	     * 완전히 정규화된 이름을 사용하더라도 항상 로컬 이름을 반환한다.( nameof(System.Int.MaxValue) -> "MaxValue")
	     * 
         * 대부분의 예외타입은 매개변수의 이름 자체를 생성자의 매개변수로 취한다. 
         * 문자열을 하드코딩 하는 대신 nameof() 를 사용하면 이름 바꾸기 작업을 할 때도 실수를 줄일 수 있다.
         * 
         * Exception 타입의 생성자는 2개의 문자열을 취하기 때문에 매개변수의 순서를 혼돈하기 쉽다. 
         * 정적 분석 도구를 이용하면 인자의 이름을 전달해야 하는 매개변수에 정확히 그 값을 전달 했는지 확인할 수 있다.
         * 
         * 특성attribute 의 매개변수로 문자열을 전달해야 하는 경우에도 nameof() 연산자를 (위치 인자, 명명된 인자 모두에 대해서) 사용할 수 있다. 
         * 이는 MVC 응용프로그램이나 Web API 응용프로그램 개발 시에 경로 route를 지정할 때 특히 유용하다. 
         * 경로 이름으로 네임스페이스 이름을 사용하는 것을 고려해보는 것도 좋다.
         */
    }
}