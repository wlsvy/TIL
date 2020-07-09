# Paging

- 페이징(paging) 은 segmentation과 마찬가지로 프로세스를 여러 조각으로 나누는 메모리 관리 기법입니다. 하지만 segmentation은 프로세스를 논리적 단위로 나누지만 paging은 단순히 크기를 기준으로 나누기 때문에 논리적으로 동일하게 분류되는 요소라도 메모리 공간에 연속적으로 할당되지 있습니다. 컴퓨터 입장에서는 해석하기 쉽지만 사람이 직접 관리하기는 어렵울 수 있습니다.
  - 프로세스를 동일한 크기로 (page) 나눔으로써 외부 단편화를 방지하고 이에 따른 메모리 압축 작업이 필요하지 않습니다.
  
  
![](https://www.cs.uic.edu/~jbell/CourseNotes/OperatingSystems/images/Chapter8/8_11_PagingModel.jpg)
![](https://www.cs.uic.edu/~jbell/CourseNotes/OperatingSystems/images/Chapter8/8_11A_PageNumberOffset.jpg)

- paging에서는 physical memory의 각 블록을 frame이라고 하고, logical memory의 각 블록을 page라고 칭합니다. frame을 작게 나눌수록 단편화가 적게 생기며, 실제로 외부 단편화external fragmentation를 방지할 수 있습니다. logical address를 physical address로 변환하는 page table이 필요합니다.

- CPU에 의해 만들어진 주소는 page number(p)와 page offset(d) 두 부분으로 나뉘어 집니다. page number는 page table의 index로써 page table에 접근할 때 사용되며 page offset은 physical address를 얻을 때 쓰이며, page table의 base address에 page offset을 더하면 physical address를 구할 수 있습니다.

![](https://www.cs.uic.edu/~jbell/CourseNotes/OperatingSystems/images/Chapter8/8_14_PagingHardware.jpg)

page table은 메모리에 저장되어 있습니다. PTBR(Page-Table Base Register)가 page table을 가리키고, PTLR(Page-Table Length Register)가 page table의 크기를 가집니다. 따라서 매번 데이터에 접근할 때마다 한 번은 데이터에, 한 번은 page table에 총 두번 메모리 접근을 시도합니다. 메모리 접근은 cpu관점에서 비용이 비싸기 때문에 캐시와 비슷한 역할을 수행하는 TLB를 활용합니다.

TLB(Translation Look-aside Buffer)는 참조했던 페이지 정보를 포함하는 일종의 캐시 역할을 합니다. TLB는 key-value pair로 데이터를 관리하는 acssociative memory이며, CPU는 page table보다 TLB을 먼저 참조합니다.

##### Reference
- [parksb](https://parksb.github.io/article/12.html)
- [OperatingSystems CourseNotes](https://www.cs.uic.edu/~jbell/CourseNotes/OperatingSystems/8_MainMemory.html)
