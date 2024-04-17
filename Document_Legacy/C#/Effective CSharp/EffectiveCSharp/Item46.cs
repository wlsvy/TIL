using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;
using System.Threading.Tasks;

namespace EffectiveCSharp
{
    /// <summary>
    /// 리소스 정리를 위해 using과 try/finally를 활용하라
    /// </summary>
    public static class ECSharp46
    {
        /* 관리되지 않는 unmanaged 시스템 리소스를 사용하는 타입의 경우,
         * IDisposable 인터페이스를 제공하는 Dispose() 메서드를 이용하여 명시적으로 리소스를 해제해야 합니다.
         * 
         * .NET 환경에서 이러한 규칙을 준수해야 할 책임은 
         * 해당 타입을 개발한 개발자의 몫이거나 하부 시스템의 역할이 아니라 해당 타입을 사용하는 사용자의 의무입니다.
         * 
         * 이런 이유로 Dispose() 메서드가 항상 호출되도록 코드를 작성하기 위한 최선의 방법은 using 문이나 try/finally 블록을 활용하는 것입니다.
         * finalizer의 경우 수행성능에 영향을 미치니 최대한 방어적인 코드가 필요한 경우에만 작성합시다.
         */ 

        public class DatabaseContext : IDisposable
        {
            public DatabaseContext(string connectString) { }
            public void ExecuteQuery(string command) { }

            public void Dispose() { }
        }

        /// <summary>
        /// 이런 메서드가 있다고 해봅시다. 이 경우, 사용자가 dbContext의 자원을 안전하게 해제해줘야할 책임이 있습니다.
        /// </summary>
        public static void ExecuteCommand(string connString, string commandString)
        {
            DatabaseContext dbContext = new DatabaseContext(connString);
            dbContext.ExecuteQuery(commandString);
        }

        /// <summary>
        /// using 문을 활용해 Disposse가 호출되도록 작성해 줍니다.
        /// IDispose 인터페이스를 지원하지 않는 타입에 대해서 using 문을 사용하면 컴파일 에러가 발생하는 사실도 명심합시다.
        /// 
        /// c# 컴파일러는 using 문을 발견하면 IL 코드 안에서 try/catch 블럭을 자동으로 생성해 줍니다.
        /// </summary>
        public static void SafelyExecuteCommand(string connString, string commandString)
        {
            using (var dbContext = new DatabaseContext(connString))
            {
                dbContext.ExecuteQuery(commandString);
            }
        }

        /// <summary>
        /// 위의 코드는 컴파일러에 의해 아래처럼 변환됩니다.
        /// </summary>
        public static void SafelyExecuteCommand_converted(string connString, string commandString)
        {
            DatabaseContext dbContext = null;
            try
            {
                dbContext = new DatabaseContext(connString);
                dbContext.ExecuteQuery(commandString);
            }
            finally
            {
                dbContext.Dispose();
            }
        }


        public static object CreateResource()
        {
            return new DatabaseContext(string.Empty);
        }

        public static void UsingObject()
        {
            //using문은 아래처럼 IDiposable을 지원하지 않는 타입에 대해서는 컴파일 오류를 던집니다.
            //using(object obj = CreateResource())
            //{

            //}

            //이 경우 as를 이용하면 IDisposable 을 실제로 구현했는지와 상관없이 더 안전하게 코드를 작성할 수 있습니다.
            //obj 가 IDiposable을 지원한다면 이전처럼 try/finally 블록이 생성되지만,
            //그렇지 않은 경우 런타임에 이 코드는 using(null)로 해석되어 (안전하게)아무 동작도 수행하지 않습니다.
            object obj = CreateResource();
            using (obj as IDisposable)
            {
                Console.WriteLine(obj.ToString());
            }
        }


        public static void NestedUsing()
        {
            {
                using (var dc = new DatabaseContext(""))
                using (var dc2 = new DatabaseContext(""))
                {

                }
            }
            

            //위의 경우처럼 using이 중첩되어 사용하는 경우 컴파일러도 역시 try/finally 문을 중첩해서 생성합니다.
            {
                DatabaseContext dc = null;
                DatabaseContext dc2 = null;
                try
                {
                    dc = new DatabaseContext("");
                    try
                    {
                        dc2 = new DatabaseContext("");
                    }
                    finally
                    {
                        dc2.Dispose();
                    }
                }
                finally
                {
                    dc.Dispose();
                }
            }

            //이는 최적화된 코드 구성이 아니기 때문에 아래와 같이 작성하는 것도 좋은 방법입니다.
            {
                DatabaseContext dc = null;
                DatabaseContext dc2 = null;
                try
                {
                    dc = new DatabaseContext("");
                    dc2 = new DatabaseContext("");
                }
                finally
                {
                    dc.Dispose();
                    dc2.Dispose();
                }
            }
        }

        /* 추가 : 
         * IDisposable.Dispose() 가 수행하는 역할 중에 하나는 GC.SuppressFinalize()를 호출하는 것입니다.
         * 이를 통해서 Dispose() 수행하면서 가비지 컬렉터에게 해당 객체는 finalizer를 호출할 필요가 없음을 알립니다.
         * 
         * 만약에 Dispose()를 호출하지 않고 임의로 객체를 정리한다면, 
         * 이 객체에 대해 finalizer를 호출할 필요가 없음에도 여전히 finalizer 큐에 보내져 객체가 더 오래 살아남게 됩니다.
         * 
         */ 
    }
}