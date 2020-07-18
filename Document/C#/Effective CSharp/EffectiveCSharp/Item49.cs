using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;
using System.Threading.Tasks;

namespace EffectiveCSharp
{
    /// <summary>
    /// catch 후 예외를 다시 발생시키는 것보다 예외 필터가 낫다
    /// </summary>
    public static class ECSharp49
    {
        /* 표준 catch 절은 예외 타입에 따라 그에 부합하는 예외만을 잡으면서 다른 타입의 예외에 대해서는 신경쓰지 않습니다.
         * 이 점은 특정 예외 객체가 가진 속성을 다루는 코드는 반드시 해당 catch 문 안에 작성해야하는 한계점을 가집니다.
         * 따라서 우선 예외를 잡은 뒤 분석 작업을 수행한 다음 그 내용을 기반으로 예외를 다시 발생시키는 코드를 작성하곤 합니다.
         * 
         * 이 방식은 분명 비효율적이고 분석을 어렵게 합니다.
         * 또한 해당 예외 객체를 처리하는 catch 문을 만날때까지 스택 되감기(stack unwinding)를 수행하는 비용을 지불해야 합니다.
         * 
         * 이에 대해서 예외 필터를 사용하는 다른 대안이 존재합니다.
         */
        
        public static string MayThrowError()
        {
            Console.WriteLine("Try MayThrowError");
            var tmp = System.DateTime.Now.Second % 1;
            switch (tmp)
            {
                case 0: throw new System.InvalidOperationException($"Random {nameof(InvalidOperationException)} Occurred");
            }
            return "Success";
        }

        /// <summary>
        /// 예외 필터는 catch 문 이후에 when 키워드를 이용하여 구성합니다.
        /// catch문에 지정한 예외 타입에 대해서만 필터가 수행됩니다.
        /// 
        /// 컴파일러는 스택 되감기 stack unwinding을 구행하기 이전에 예외 필터를 수행하도록 코드를 생성합니다.
        /// when 절에서는 예외에 대한 위치를 알고 있기 때문에 호출 스택이나 지역변수 등에 대한 모든 정보에 접근 가능합니다.
        /// 
        /// 만약 예외 필터가 false를 반환하면 런타임은 콜 스택을 따라 올라가면서 앞서 발생한 예외에 타입에 부합하는 catch문을 계속 찾아나갑니다.
        /// 이 과정에서 응용 프로그램의 상태는 변경되지 않고 그대로 유지됩니다.
        /// </summary>
        public static void TryErrorWithFilter()
        {
            var retryCount = 0;
            string resultString = string.Empty;

            while (string.IsNullOrEmpty(resultString))
            {
                try
                {
                    resultString = MayThrowError();
                }
                catch (InvalidOperationException e) when (retryCount++ < 3)
                {
                    Console.WriteLine($"{nameof(InvalidOperationException)} occurred");
                    //재시도 이전에 잠깐 멈춥니다.
                    Task.Delay(1000 * retryCount); 
                }
            }
        }

        /// <summary>
        /// 아래의 방식은 우선 예외를 catch하고 처리할 수 있는지 판별한 후, 처리 불가능하면 다시 예외를 발생시킵니다.
        /// 이 방식에서 런타임은 예외를 처리할 catch문을 찾고 즉각 스택 되감기를 수행합니다. 
        /// 
        /// 따라서 예외를 일으킨 메서드 내에서 선언된 지역변수의 대부분은 도달 불가능합니다.(만약 변수가 클로저 객체에 의해 참조되고 있다면 도달 가능합니다.)
        /// 이로 인해 분석을 위한 주요 정보들에 접근할 수 없을 수 있으며 상태 정보의 일부는 소실됩니다.
        /// 
        /// catch 문 내에서 오류가 복구 불가능하다고 판단되면 빈 throw; 를 호출해 다시 예외를 발생시킵니다. 
        /// 명시적으로 새로운 예외 객체를 생성한 후 이 예외를 발생시키면 예외 발생 위치가 바뀌므로 좋은 방법이 아닙니다.
        /// </summary>
        public static void TryErrorWithoutFilter()
        {
            var retryCount = 0;
            string resultString = string.Empty;
            
            while(string.IsNullOrEmpty(resultString)){
                try
                {
                    resultString = MayThrowError();
                }
                catch (InvalidOperationException e)
                {
                    if (retryCount++ < 3)
                    {
                        Console.WriteLine($"{nameof(InvalidOperationException)} occurred");
                        //재시도 이전에 잠깐 멈춥니다.
                        Task.Delay(1000 * retryCount); 
                    }
                    else
                        throw;
                }
            }
        }

        /* throw 문을 사용하는 경우, 호출 스택상에 빈 throw를 호출한 위치가 나타나게 됩니다.
         * 따라서 catch 문 내에서 throw를 호출하면 예외를 일으킨 메서드의 위치가 호출 스택에 나타나는 것이 아니라 catch문 내의 throw 호출 위치가 나타납니다.
         * 또한 try 블록 내에 포함된 오류 발생 메서드에 대한 함수 호출 정보는 모두 소실됩니다.
         * 
         * 하지만 예외 필터를 활용하는 경우 예외를 발생시켰던 메서드의 호출 정보를 호출 스택에 온전히 보존할 수 있습니다.
         * 코드가 길어지면 길어질수록 첫 번째 예를 이용하는 경우에는 예외 발생 위치를 찾아내는 것이 점점 더 어려워질 수 밖에 없습니다.
         * 
         * 또한 성능면에서도 에러 필터쪽이 더 긍정적입니다. .NET CLR은 코드상에 try/catch 문이 있더라도 
         * catch 문 내부로 진입할 가능성이 없는 경우 최적화를 수행하여 성능을 개선합니다. 
         * 스택 되감기 작업/ catch문으로의 진입 과정은 수행 성능에 상당한 영향을 끼칩니다.
         * 
         * 예외 필터를 사용하면 스택 되감기나 catch 문으로의 진입 자체가 제한적으로 이뤄지기 때문에 성능이 개선됩니다. 최소한 더 나빠지는 경우는 없습니다.
         * 
         * 예외 필터는 대표적으로 
         * - 태스크task 기반의 비동기 프로그램을 작성할 때
         * - COMException에서 HResult 속성 확인
         * - HTTPException에서 HTTP 응답 코드 확인
         * 와 같은 경우에 필터를 적용할 수 있습니다.
         */

        public static void TreeOfErrors()
        {
            try
            {
                MayThrowError();
            }
            catch(Exception e)
            {
                throw; // 이 위치가 호출 스택에 나타납니다.
            }
        }

        public static void TreeOfErrors2()
        {
            try
            {
                MayThrowError(); // 이 위치가 호출 스택에 나타납니다.
            }
            catch (Exception e) when(false)
            {
                Console.WriteLine("Error Catched");
            }
        }

        public static void RunSample()
        {
            //TryErrorWithFilter();
            TryErrorWithoutFilter();
            //TreeOfErrors();
            //TreeOfErrors2();
        }
    }
}