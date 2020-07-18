using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;
using System.Threading.Tasks;

namespace EffectiveCSharp
{
    /// <summary>
    /// 예외 필터의 다른 활용 예를 살펴보라
    /// </summary>
    public static class ECSharp50
    {
        public static string MayThrowError()
        {
            switch (System.DateTime.Now.Second % 5)
            {
                case 0: break; //성공
                case 1: throw new System.ArithmeticException($"Random {nameof(ArithmeticException)} Occurred");
                case 2: throw new System.InvalidOperationException($"Random {nameof(InvalidOperationException)} Occurred");
                case 3: throw new System.ApplicationException($"Random {nameof(ApplicationException)} Occurred");
                case 4: throw new System.ArgumentException($"Random {nameof(ArgumentException)} Occurred");
            }
            return "Success";
        }

        public static bool ConsoleLogException(Exception e)
        {
            Console.WriteLine($"Error : {e.ToString()}");
            return false;
        }

        /// <summary>
        /// 에러 필터을 활용한 몇가지 유용한 패턴 입니다.
        /// 
        /// ConsoleLogException은 항상 false만 반환합니다. 
        /// 따라서 더 이상 예외는 전파되지 않으며 catch문은 Exception 예외 타입으로 catch를 수행하기 때문에 모든 예외를 catch 하게 됩니다.
        /// 
        /// 첫번째 catch 문의 예외 필터는 Exception타입을 확인하는데 일반적으로 Exception 타입을 catch하는 블록을 가장 앞쪽에 배치하는 경우는 없습니다.
        /// 하지만 이 경우, 어떤 경우에도 예외 처리문 안으로 진입하는 일이 없기 때문에 가장 앞에 위치해도 무방하며, 런타임은 계속해서 다음 catch 문을 확인해 나갈 것입니다.
        /// 
        /// 이러한 패턴은 모든 예외에 대해 공통적으로 수행해야할 작업이 있는 경우 활용할 수 있습니다.
        /// </summary>
        public static void Example0()
        {
            var count = 0;
            try
            {
                MayThrowError();
            }
            catch (Exception e) when(ConsoleLogException(e)) { }
            catch (ArithmeticException e)
            {
                Console.WriteLine("Catched ArithmeticException Error");
                count++;
            }
            catch (InvalidOperationException e)
            {
                Console.WriteLine("Catched Invalid Operation Error");
                count++;
            }
            finally
            {
                Console.WriteLine("Finally Block");
            }

        }

        /// <summary>
        /// 반대로 Exception catch 블록을 맨 마지막에 위치시키는 방법도 있습니다. 
        /// 이 경우 처리되지 않은 예외에 대해서 특정 작업을 수행하게 할 수 있습니다.
        /// </summary>
        public static void Example1()
        {
            var count = 0;
            try
            {
                MayThrowError();
            }
            catch (ArithmeticException e)
            {
                Console.WriteLine("Catched ArithmeticException Error");
                count++;
            }
            catch (InvalidOperationException e)
            {
                Console.WriteLine("Catched Invalid Operation Error");
                count++;
            }
            catch (Exception e) when (ConsoleLogException(e)) { }
            finally
            {
                Console.WriteLine("Finally Block");
            }
        }

        /// <summary>
        /// System.Diagnostics.Debugger.IsAttached 속성 값을 활용해 디버깅 붙어 있지 않은 경우를 확인합니다.
        /// 이 경우 디버깅 상태에서는 예외처리를 수행하지 않으며, 그 외에는 예외필터를 통과하여 예외 처리기가 수행되도록 합니다.
        /// </summary>
        public static void Example2()
        {
            var count = 0;
            try
            {
                MayThrowError();
            }
            catch (ArithmeticException e) when (!System.Diagnostics.Debugger.IsAttached)
            {
                Console.WriteLine("Catched ArithmeticException Error");
                count++;
            }
            catch (InvalidOperationException e) when (!System.Diagnostics.Debugger.IsAttached)
            {
                Console.WriteLine("Catched Invalid Operation Error");
                count++;
            }
        }

        public static void RunSample()
        {
            Example0();
            Example1();
            Example2();
        }
    }
}