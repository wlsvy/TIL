using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;
using System.Threading.Tasks;

namespace MoreEffectiveCSharp
{
    class MainProgram
    {
        static void Main(string[] args)
        {
            System.Console.WriteLine("Hello ECS");
        }
    }
}

/*
 * 항목 Template
 

using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;
using System.Threading.Tasks;

namespace EffectiveCSharp
{
    /// <summary>
    /// 
    /// </summary>
    public static class ECSharp00
    {
        public static void RunSample()
        {

        }
    }
}

*/

/*
 * 클래스 템플릿

public class Widget
{
    public Widget() { }
}

public struct MyValueType
{
    public int value;

    public MyValueType(int val)
    {
        value = val;
    }
}

public class MyRefType : IDisposable
{
    public void Dispose()
    {
        System.Console.WriteLine("On Dispose");
    }
}

*/