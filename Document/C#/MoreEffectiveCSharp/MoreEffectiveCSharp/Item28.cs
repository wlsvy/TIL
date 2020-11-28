using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;
using System.Threading.Tasks;

//async void 메서드는 절대 작성하지 말라
namespace MoreEffectiveCSharp
{
    /// <summary>
    /// async void 로 메서드를 작성하면 이 메서드가 던지는 예외를 호출 측에서 잡지 못합니다. 
    /// 
    /// 비동기 메서드는 예외를 태스크 객체를 통해 보고합니다. 
    /// 비동기 메서드가 예외를 던지면 태스크 객체가 오류 상태가 되고 await 구문은 태스크 객체가 오류 상태이면 예외를 던집니다.
    /// 
    /// 비동기 메서드가 작업을 수행하다 예외를 던져서 task가 오류 상태가 되면, await를 호출한 코드가 다시 스케쥴링될 때 예외가 발생합니다.
    /// 
    /// 
    /// 이때 async void 로 선언된 메서드는 대기할 수가 없습니다. 기다릴 수 없으므로 async void 메서드를 호출한 코드에서 예외를 잡거나 전파할 방법이 없습니다.
    /// 이런 이유로 예외가 호출 측으로 전달되지 않기 때문에 async void 로 메서드를 작성하면 안됩니다.
    /// 
    /// 어쩔 수 없이 async void를 사용하는 경우(특정 라이브러리 안에 포함되어 있어서)AppDomain.UnhandledException이나 혹은 이와 유사한 형태의 핸들러를 예외를 처리할 수 있습니다.
    /// 하지만 AppDomain.UnhandledException 핸들러를 이용하면 예외를 처리한 후 애플리케이션을 정상상태로 복구할 수 없습니다. 
    /// 발생한 예외를 기록하고 데이터를 저장할 수는 있 지만 프로그램이 종료되는 것은 막을 수 없습니다.
    /// 
    /// 
    /// async void 메서드가 초래하는 다른 문제도 있습니다. 대부분의 async 메서드에서는 비동기작업을 요청하고, 작업이 완료될 때까지 기다린 후, 다른 작업을 수행합니다. 
    /// 하지만 앞서 언급하였듯이 async void로 메서드를 작성하면 작업이 완료될 때까지 대기할 방법이 없다. 
    /// 따라서 async void 메서드를 사용하는개발자는 언제 작업이 완료되는지 판단하기 어렵습니다. 결국에는 async 태스크를 쉽게 만들 수가 없습니다. 
    /// 
    /// async void 메서드가 허용되는 경우는 비동기 이벤트 핸들러를 만들 때입니다. 
    /// 이벤트 핸들러(반환형 void)는 C#이 async와 await를 도입하기 전에 확립 되었으므로 비동기 이벤트 핸들러를 c# 초기 버전에서 정의한 이벤트와 연결하려면 여전히 async void 메서드가 필요합니다.
    /// </summary>
    public static class MECSharp28
    {
        private static async void DoVoidAsync()
        {
            await Task.Run(() => Console.WriteLine("Void Async"));
        }


        public static async void RunSample()
        {

            //async void 의 오류를 로깅하고 싶다면 처리되지 않은 예외를 unhandled exception 잡을 수 있도록 핸들러를 추가해둬야 합니다.
            AppDomain.CurrentDomain.UnhandledException += (sender, e) => 
            { 
                Console.ForegroundColor = ConsoleColor.Cyan; 
                Console.WriteLine(e.ExceptionObject.ToString()); 
                //어차피 콘솔 애플리케이션이 종료될 것이므로 ForegroundColor를 원래 색으로 다시 되돌릴 필요는 없습니다.
            };

            //아래 방식은 좋지 않습니다. 가끔은 실패할 수도 있습니다. Task.Delay로 대기하는 시간이 비동기 메서드가 완료될 때까지 충분하지 않을 수 있습니다.
            //async void를 await로 받을 수 없는 특징을 기억합시다.
            DoVoidAsync();
            await Task.Delay(1000); //잠시 대기합니다.
        }
    }
}
