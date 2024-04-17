using System;

//박싱과 언박싱을 최소화하라

namespace EffectiveCSharp
{
    /// <summary>
    /// 박싱이란 값 타입의 객체를 타입이 정해져 있지 않은 임의의 참조 타입 내부에 포함시키는 방법. 
    /// 이를 이용하면 참조 타입이 필요한 경우에도 값 타입을 사용할 수 있다. 
    /// 언박싱이란 반대로 박싱되어 있는 참조 타입의 객체로부터 값 타입 객체의 복사본을 가져오는 방법이다.
    /// 
    /// 때로는 박싱과 언박싱을 수행하는 과정에서 임시 객체가 생성되기도 하는데, 간혹 이로 인해 예상치 못한 버그가 발생하기도 한다. 
    /// 박싱과 언박싱은 최대한 피하는 것이 좋다.
    /// </summary>
    public class ECSharp09
    {

        /* 박싱과 언박싱은 모두 자동으로 이루어진다. 
         * 
         * System.Object 와 같은 참조 타입을 요구하는 곳에 값 타입의 객체를 사용하면 컴파일러는 자동으로 박싱과 언박싱을 수행하는 코드를 생성한다. 
         * 또한 인터페이스를 통해 값 타입의 객체를 참조하는 경우에도 박싱과 언박싱을 수행하는 코드를 생성한다. 
         * 컴파일러는 어떠한 경고 메시지도 출력하지 않으며 박싱 작업은 자연스럽게 수행된다.
         * 
         * 박싱과 언박싱을 피할 수 있는 비교적 손쉬운 규칙은 가능한 한 .NET 1.x 의 컬렉션을 사용하는 것을 피하고
         * 대신 .NET 2.0 에 추가된 제네릭 컬렉션을 사용하는 것이다.
         */

        public void DoSomething()
        {
            int firstNumber = 0, secondNumber = 1, thirdNumber = 2;

            Console.WriteLine($"A few numbers : {firstNumber}, {secondNumber}, {thirdNumber}");
            //값 타입을 '박싱'해서 보간 문자열의 매개변수로 보낸다
        }

        public void DoSomething2()
        {
            //DoSomething() 에서 벌어지는 일을 풀어보면
            int firstNumber = 0;
            object o = firstNumber; //박싱

            Console.WriteLine(o.ToString()); //박싱 후 문자열 생성하는 함수 호출
        }

        public void DoSomething3()
        {
            int firstNumber = 0, secondNumber = 1, thirdNumber = 2;

            Console.WriteLine($"A few numbers : {firstNumber.ToString()}, {secondNumber.ToString()}, {thirdNumber.ToString()}");
            //이 방식은 박싱을 피할 수 있게 한다.
        }
    }
}