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

            //MECSharp01.RunSample();
            //MECSharp03.RunSample();
            //MECSharp05.RunSample();
            //MECSharp07.RunSample();
            //MECSharp08.RunSample();
            //MECSharp10.RunSample();
            //MECSharp11.RunSample();
            //MECSharp12.RunSample();
            //MECSharp15.RunSample();
            //MECSharp16.RunSample();
            //MECSharp20.RunSample();
            //MECSharp22.RunSample();
            //MECSharp24.RunSample();
            //MECSharp25.RunSample();
            //MECSharp26.RunSample();
            //MECSharp28.RunSample();
            MECSharp36.RunSample();
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

namespace MoreEffectiveCSharp
{
    /// <summary>
    /// 
    /// </summary>
    public static class MECSharp00
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