using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;
using System.Threading.Tasks;

//PLINQ가 병렬 알고리즘을 구현하는 방법을 이해하라(ebook에 메모한 것 봅시다)
namespace MoreEffectiveCSharp
{
    /// <summary>
    /// 모든 병렬 쿼리는 분할partitioning 과정부터 시작한다. PLINQ는 입력 요소를 분할한 후, 쿼리를 실행하기 위해 생성한 태스크들에 분할된 요소들을 분배해야 한다.
    /// 
    /// PLINQ는 입력 소스와 쿼리의 종류에 따라 다음 네가지 분할 중 하나를 사용한다. 
    /// ● 범위 분할range partitioning 
    /// ● 덩어리 분할chunk Partitioning 
    /// ● 줄 단위 분할striped partitioning 
    /// ● 해시 분할hash partitioning
    /// 
    /// 가장 단순한 알고리즘은 범위 분할이다. 입력값의 범위를 태스크 수로 나누고, 나눈 집합을 각 태스크에 할당하는 것이다.
    /// 덩어리 분할 알고리즘은 태스크가 추가작업을 요구할 때마다 입력값의 덩어리, 즉 청크chunk를 할당하는 방식이다.
    /// 나머지 두 분할 방식은 특정 쿼리 연산에 최적화돼 있다. 줄 단위 분할은 범위 분할의 특수한 형태로, 시퀀스에서 첫 번째 요소를 찾아내는 처리하는 방법을 최적화한다.
    /// 해시 분할은Join, GroupJoin, GroupBy, Distinct, Except, Union, Intersect를 사용하 는 쿼리를 위해 특별히 설계된 알고리즘이다.
    /// </summary>
}
