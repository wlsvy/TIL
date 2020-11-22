using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;
using System.Threading.Tasks;

//상태 전달을 위한 이벤트 패턴을 구현하라
namespace MoreEffectiveCSharp
{
    /// <summary>
    /// 이벤트는 이벤트를 수신하는 구독자가 시스템에 종속되지 않도록 도와주는데 C#에서 event를 사용하게 되면 이벤트를 전달하는 측과 수신하는 측을 분리할 수 있습니다.
    /// </summary>
    public static class MECSharp16
    {
        private class Logger
        {
            public static Logger I { get; } = new Logger();
            public event Action<string> Log;
            public void AddMsg(string message) => Log?.Invoke(message);
        }

        //위의 클래스는 대략 아래와 유사합니다.
        //이때 이벤트의 add, remove 접근자는 thread safe 입니다.
        private class Logger1
        {
            public static Logger1 I { get; } = new Logger1();

            private Action<string> m_Log;

            public event Action<string> Log
            {
                add { m_Log = m_Log + value; }
                remove { m_Log = m_Log - value; }
            }
            public void AddMsg(string message) => m_Log?.Invoke(message);
        }

        public static void RunSample()
        {
            Logger.I.AddMsg("Null event Log");

            Logger.I.Log += (msg) => Console.WriteLine(msg);
            Logger.I.AddMsg("First Message");
        }
    }
}
