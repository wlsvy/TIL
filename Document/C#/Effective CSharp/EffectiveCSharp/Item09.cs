using System;

//박싱과 언박싱을 최소화하라

namespace EffectiveCSharp
{
    public class ECSharp09
    {
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