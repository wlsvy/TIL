using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;
using System.Threading.Tasks;

namespace EffectiveCSharp
{
    /// <summary>
    /// 지연 수행과 즉시 수행을 구분하라
    /// </summary>
    public static class ECSharp40
    {
        /* 데이터는 사용하기 전에 반드시 그 값이 확정돼야 하는 반면 메서드는 지연 평가가 가능하다는 점을 염두하자.
         * 
         * 변경 불가 메서드란 메서드 내에서 I/O 작업을 수행하거나, 전역변수의 값을 변경하거나, 
         * 혹은 다른 프로세스와 통신하는 등의 작업을 수행하지 않으며 전역적인 상태를 변경하지 않는 메서드를 의미한다.
         * 
         * 계산 비용과 공간 비용을 고려하여, 특정 메서드의 반환값을 데이터 테이블에 캐싱해 사용할 수 있다.
         */ 
    }
}