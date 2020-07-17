using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;
using System.Threading.Tasks;

namespace EffectiveCSharp
{
    /// <summary>
    /// 쿼리 결과의 의미를 명확히 강제하고, Single()과 First()를 사용하라
    /// </summary>
    public static class ECSharp43
    {
        /* LINQ가 제공하는 메서드 중에서는 단일 결과값을 반환하는 메서드도 존재합니다.
         * 
         * Single()은 1개의 요소만 반환하며, 정확히 하나의 값만이 반환될 것으로 가정합니다.
         * single을 활용하면 개발자의 의도를 정확히 드러낼 수 있으며, 
         * 어떤 요소도 포함하지 않거나 다수의 요소를 포함하면 Single은 에러를 유발하니 개발자의 가정이 틀렸다면 즉각적으로 확인할 수 있기도 합니다.
         * 
         */

        public class Widget
        {
            public Widget() { }
            
            public string name;
            public uint Priority = 0;
        }

        public static void RunSample()
        {
            var widgets = new Widget[]
            {
                new Widget{ name = "Widget", Priority = 0 },
                new Widget{ name = "Widget", Priority = 1 },
                new Widget{ name = "Widget", Priority = 2 },
                new Widget{ name = "Other", Priority = 3 },
                new Widget{ name = "Other", Priority = 4 }

            };

            //다수의 요소가 포함되므로, 아래 동작은 예외를 일으킵니다.
            //var answer = (from w in widgets
            //              where w.name == "Widget"
            //              select w).Single();

            //아무 요소도 없거나 하나의 요소를 포함하는 경우라면 SingleOrDefault을 활용할 수 있습니다.
            var noneOrSingle = (from w in widgets
                                where w.name == "None"
                                select w).SingleOrDefault();

            //다수의 요소에서 하나의 값만을 반환하는 경우라면 First() 혹은 FirstOrDefulat()를 활용하면 됩니다.
            var first = (from w in widgets
                         where w.name == "Widget"
                         select w).First();

            //Skip을 활용한다면 시퀀스상 n번째의 요소를 가져오도록 작성할 수 있습니다.
            //아래의 코드는 세번째 우선순위에 해당하는 Widget을 반환합니다. 단 하나의 요소를 가져올 수 있도록, FirstOrDefault()를 사용하였습니다.
            var thirdPrioirtyWidget = (from w in widgets
                         select w).Skip(2).FirstOrDefault();

            //Take를 사용해서 우선순위 3번째, 네번째에 해당하는 요소를 반환하게 합니다.
            var WidgetList = (from w in widgets
                              select w).Skip(2).Take(2).ToList();
        }
    }
}


