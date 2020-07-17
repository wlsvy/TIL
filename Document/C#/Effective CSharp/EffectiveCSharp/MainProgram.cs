using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;
using System.Threading.Tasks;
using EffectiveCSharp;

namespace EffectiveCSharp
{
    class MainProgram
    {
        static void Main(string[] args)
        {
            System.Console.WriteLine("Hello ECS");

            //ECSharp02.RunSample();
            //ECSharp15.Case0.RunSample0();
            //ECSharp15.Case0.RunSample1();
            //ECSharp16.Case0.RunSample();
            //ECSharp18.RunSample();
            //ECSharp22.RunSample();
            //ECSharp24.RunSample();
            //ECSharp27.RunSample();
            //ECSharp30.RunSample();
            //ECSharp31.RunSample();
            //ECSharp34.RunSample();
            //ECSharp36.RunSample();
            //ECSharp37.RunSample();
            //ECSharp41.RunSample();
            ECSharp43.RunSample();
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

