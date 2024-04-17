
# 요소를 정말로 제거하고자 한다면 remove 류의 알고리즘에는 꼭 erase를 붙여 사용하자

##### `remove`는 어느것도 "진짜로" 없애지 않습니다. 없앨 수 없기 때문입니다. `remove` 알고리즘은 단지 "제거되지 않는" 요소를 범위의 앞쪽에 가져다 놓는 일을 할 뿐입니다(원래의 상대적인 위치는 그대로 보존하구요). 그리고 "제거되지 않은" 요소 중 마지막 것의 바로 뒤를 가리키는 반복자를 반환하는 것으로 자신의 동작을 마칩니다.
- 어떤 컨테이너에서 특정 요소를 제거하는 방법은 그 컨테이너의 멤버 함수를 호출하는 것 뿐입니다. (대개 `erase`라는 이름을 가지고 있죠. list의 경우는 이름이 다릅니다)
		

- remove 알고리즘은 자신이 조작할 데이터 요소의 범위를 나타내는 한 쌍의 반복자를 받아들일 뿐, 컨테이너를 받아들이지 않기 때문에, 어떤 컨테이너가 요소를 가지고 있는지는 알 방법이 없습니다. 또한 컨테이너의 정체를 밝혀 내는 것 자체도 불가능합니다.
		


```c++
template< class ForwardIt, class T >
ForwardIt remove(ForwardIt first, ForwardIt last, const T& value)
{
	first = std::find(first, last, value);
	if (first != last)
		for (ForwardIt i = first; ++i != last; )
			if (!(*i == value))
				*first++ = std::move(*i);
	return first;
}

```

### remove 알고리즘이 호출되기 직전의 상황을 시각화 해 보았습니다.

![](http://ajwmain.iptime.org/programming/book_summary/%5B02%5Deffective_stl/BS2/BS2-4.PNG)

### 그리고 다음과 같이 remove의 반환 값을 newEnd라고 불리는 새 반복자에 저장하면,

![](http://ajwmain.iptime.org/programming/book_summary/%5B02%5Deffective_stl/BS2/BS2-5.PNG)

### 큰 오해가 없었다면, "제거되지 않은" 요소는 v.begin()와, remove가 반환한 반복자(newEnd) 사이에 들어 있고, "제거된" 요소는 newEnd와 v.end() 사이에 있을 것이라고 보는 것이 논리적일 테지요. 그런데, 문제는 그렇지가 않다는 것입니다!
- "제거된" 요소는 벡터에 더 이상 남아 있을 필요가 없습니다. 그래서 remove는 제거된 요소를 주어진 범위의 끝 부분에 옮기는 식으로 동작하지 않습니다.
- 표준안에서는 굳이 요구하고 있지 않으나, 새로운 논리적 끝의 뒷부분에 있던 요소들은 대개 원래의 값을 유지하고 있습니다.
  - 여러분은 remove에게 값을 제거해 달라고 요청했지, 제거된 값을 특별한 장소에 따로 모아 달라고는 하지 않았습니다. 그렇기 때문에 제거된 값들이 벡터의 뒷쪽 끝에 모여 있으리라는 기대를 하면 안 됩니다.

![](https://github.com/wlsvy/TIL/blob/master/Document/C%2B%2B/EffectiveSTL/EffectiveSTL/EffectiveSTL/EffectiveSTL_Item32_Photo.png)

  - 위의 동작과정을 나타내자면
    1. 제거 대상이 아닌 v[0], v[1], v[2]는 확인 후 지나갑니다.
	2. v[3]은 제거 대상이므로, v[3]이 덮어 쓰일 것이라고 표시해 둔 뒤 v[4]로 갑니다. 즉 v[3]은 나중에 채워질 구멍입니다.
	3. v[4]의 값은 유지되어야 하는 것으로 판단한 뒤 v[4]를 v[3]으로 이동시킵니다. 이제 v[3]는 채워지고 v[4]는 새로운 구멍이 됩니다.
	4. v[5]를 점검합니다. 제거될 값으로 판단하면 곧 v[6]로 넘어갑니다.
	5. v[6]는 제거되지 않는 값이므로, v[6]를 v[4]에 이동시킵니다. 이제 새로운 구멍은 v[5]가 되고 v[7]로 넘어갑니다.
	6. 이런 방식으로 컨테이너의 원소를 전부 검사합니다.
	  - 그 결과 remove는 v[7]을 v[5]에 대입하고, v[8]을 v[6]에 대입합니다. v[9]는 제거될 값이므로 추가적인 동작 없이 무시됩니다.
	7. 마지막으로 덮어 쓰여질 다음 요소(이 경우 v[7])를 가리키는 반복자를 반환합니다.


![](http://ajwmain.iptime.org/programming/book_summary/%5B02%5Deffective_stl/BS2/BS2-6.PNG)

```c++

vector<int> v;                        
for (int i = 1; i <= 10; ++i) {       
	v.push_back(i);
}

// 10을 출력합니다.
cout << v.size();                    

// 3개의 요소를 99로 세팅합니다.
v[3] = v[5] = v[9] = 99;            

// 99란 값을 가진 요소를 모두 remove 합니다.
remove(v.begin(), v.end(), 99);        

// 앗, 여전히 10입니다!
cout << v.size();               

//remove를 수행해서 얻어낸 주어진 범위의 "새로운 논리적 끝"부터 그 범위의 진짜 끝 사이에 있는 요소들은, erase를 써서 "진짜"로 제거하면 됩니다.
v.erase(remove(v.begin(), v.end(), 99), v.end());   

// 이제 7이 나옵니다.
cout << v.size();    

```

- list에서는 remove와 erase가 하나로 합쳐진 remove라는 멤버 함수가 제공되고 있습니다. STL에서 컨테이너의 요소를 없애는 역할을 하는 함수로 remove라는 이름을 가진 것은 이것 하나 뿐입니다.
- 리스트의 경우에는 erase와 remove를 함께 사용하는 것 보다, list::remove를 사용하는 것이 훨씬 더 효율이 좋습니다.(항목 44 참고)
- remove와 비슷한 알고리즘 두 가지가 더 있는데, 각각 remove_if와 unique입니다. 이 두 알고리즘 역시 remove와 비슷한 이유로 erase와 함께 사용해야 합니다.
- list::unique는 인접한 중복 요소를 진짜로 없앱니다. 그리고 erase와 unique를 함께 쓰는 것보다 list::unique가 더욱 효율적이라는 점도 똑같지요.