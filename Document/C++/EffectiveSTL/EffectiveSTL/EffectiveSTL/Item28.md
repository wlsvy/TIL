# reverse_iterator에 대응되는 기점 반복자(base_iterator)를 사용하는 방법을 정확하게 이해하자


- 어떤 컨테이너 멤버 함수의 경우 반복자 매개 변수로 iterator만을 고집하기 때문에 ri가 가리키는 위치에 요소를 새로 삽입(insert)하고 싶다든가 할 때 멈칫! 할 수밖에 없습니다. ri가 가리키는 요소를 삭제(erase)할 때도 마찬가지이지요. 이런 경우 어쨌든 이 reverse_iterator를 iterator로 바꾸어야 합니다. 이때 사용하는 것이 base라는 멤버 함수입니다.

- reverse_iterator ri가 가리키는 vector<int>내의 위치에다가 숫자 99를 넣어 보고 싶다고 칩시다. ri는 오른쪽에서 왼쪽으로 이동하는 경로에 있으며, STL 세계에서 요소 삽입은 반복자가 가리키는 위치의 바로 앞에서 이루어진다는 사실을 잊으면 안됩니다.

![](http://twimgs.com/ddj/cuj/images/cuj0106smeyers/diagram2.gif)
![](http://twimgs.com/ddj/cuj/images/cuj0106smeyers/diagram3.gif)

```c++

	auto v = vector<int>(10);
	for (int i = 0; i < 10; i++) {
		v[i] = i;
	}

```

```c++

	auto tmp0 = v;
	auto tmp1 = v;

	auto it0 = find(tmp0.begin(), tmp0.end(), 5);
	//4, 5 사이에 99가 삽입됩니다.
	tmp0.insert(it0, 99);

	//reverse_iterator를 base() 함수를 통해 iterator로 변환합니다.
	auto it1 = find(tmp1.rbegin(), tmp1.rend(), 5).base();
	//5, 6 사이에 99가 삽입됩니다.
	tmp1.insert(it1, 99);

```

```c++

	auto tmp0 = v;
	auto tmp1 = v;

	auto it0 = find(tmp0.begin(), tmp0.end(), 5);
	//5가 삭제됩니다.
	tmp0.erase(it0);

	//reverse_iterator를 base() 함수를 통해 iterator로 변환합니다.
	auto it1 = find(tmp1.rbegin(), tmp1.rend(), 5).base();
	//6이 삭제됩니다.
	tmp1.erase(it1);

```

- reverse_iterator를 iterator로 바꿀 때(즉, base를 호출할 때)에는, 여러분이 그 반복자로 무엇을 할 것인지를 정확히 계획하고 있어야 합니다. 애써서 바꾼 iterator가 실은 여러분이 원한 것이 아닐 수도 있기 때문이죠.