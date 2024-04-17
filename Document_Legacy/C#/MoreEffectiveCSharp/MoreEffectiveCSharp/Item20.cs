using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;
using System.Threading.Tasks;

//이벤트 런타임 시 객체 간의 결합도를 증가시킨다는 것을 이해하라
namespace MoreEffectiveCSharp
{
    /// <summary>
    /// 이벤트 기반 API에는 타입 간의 정적 결합도는 낮추지만 동적 결합도는 증가시키는 문제가 있습니다.
    /// 
    /// 이벤트에 등록된 모든 이벤트 핸들러가 참조상태로 있다는 점이 그것입니다. 한번 이벤트를 호출할 때 다수의 핸들러를 호출하는 방식이다보니(Multicast 멀티캐스트)
    /// 이벤트 핸들러의 경우 메서드의 반환값은 이벤트를 통해 다루기가 어려워지는 문제가 있으며, 이벤트 호출 객체의 생명주기가 핸들러 객체에 영향을 미치기 때문에
    /// 이벤트 핸들러가 자신의 역할을 마치면 등록된 이벤트 호출 객체와 연결을 끊어야 할 것입니다.
    /// 
    /// 반대의 경우 역시 이벤트 호출 객체가 자신의 역할을 마쳤다면 등록된 이벤트 핸들러와 연결을 끊고 난 뒤에 삭제되어야 합니다.
    /// </summary>
    public static class MECSharp20
    {
        public class WidgetEventArgs : EventArgs
        {
            public int Percent { get; set; }
            public bool Cancel { get; set; } = false;
        }

        public class Widget
        {
            public static Widget I { get; } = new Widget();

            public event Action<WidgetEventArgs> OnProgress;

            public void DoSomething()
            {
                for(int i = 0; i < 100; i++)
                {
                    //하나의 WidgetEventArgs 객체를 이벤트에 등록된 모든 이벤트 핸들러가 참조하게 됩니다.
                    var arg = new WidgetEventArgs();
                    arg.Percent = i;
                    OnProgress?.Invoke(arg);

                    if (arg.Cancel)
                    {
                        return;
                    }
                }
            }
        }
        public static void RunSample()
        {
            Widget.I.OnProgress += (arg) =>
            {
                Console.WriteLine($"handle 0 : {arg.Percent.ToString()}");
                if(arg.Percent > 50)
                {
                    arg.Cancel = true;
                }
            };
            Widget.I.OnProgress += (arg) =>
            {
                Console.WriteLine($"handle 1 : {arg.Percent.ToString()}");
                arg.Cancel = false;
            };


            //위의 경우, 진행도가 50이 넘어가면 멈추도록 의도된 것이겠지만, WidgetEventArg의 값이 다른 이벤트 핸들러에 의해 바뀌는 문제 때문에 멈추지 않습니다.
            Widget.I.DoSomething();
        }
    }
}
