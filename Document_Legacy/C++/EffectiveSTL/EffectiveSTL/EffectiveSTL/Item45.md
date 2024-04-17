# count, find, binary_search, lower_bound, upper_bound, �׸��� equal_range�� ����� �ľ��� ����

#### �����̳ʿ��� � ���� ã�� ���� ��, cout, count_if, find, find_if, binary_search, lower_bound, upper_bound�� ����� �� �ֽ��ϴ�.

���ĺ��ʹ� count�� find ���� _if�� ������ ���� �˰������� _if�� �����ϰڽ��ϴ�. ���� ������ �޾Ƶ��̴� binary_search, lower_bound�� upper_bound, equal_range�� ������ �����ϰڽ��ϴ�.



#### Ž�� ������ ������ �ݺ��ڰ� ���ĵ� ������ �����ϰ� �ִ��Ŀ� ��� �κ��� �ɷ� �ֽ��ϴ�. ���� �׷��ٸ� binary_search, lower_bound, upper_bound, equal_range ���� �˰�����(�밳 �α� �ð��� ����˴ϴ�. �׸� 34�� �����ϼ���)�� �Ἥ ���� �ӵ��� ���� �� �ֽ��ϴ�.

���ĵ��� ���� ������ ���ĵȴٴ� ���� ���� �̿��� �� �ϳ��� ��ȭ�� ���մϴ�. �� ���� ���� �������� ���� �� ���Ǵ� ��(equality) ������ ���(equivalence)���� �ٲ�ٴ� ������(�׸�19 ����).



- count�� find �˰������� ���� ������ Ž���ϴ� �ݸ�, binary_search, lower_bound, upper_bound, equal_range�� ����� ����Ѵٴ� ��Ǹ� �����Ͻø� �˴ϴ�.

#### ������ ���ĵ� ������ �ƴ϶�� ���� �ð��� �˰������� count�� find �ۿ� ����� �� �����ϴ�.

���� ���� ���θ� �����ϴ� �������δ� count�� ����� �ڵ尡 �ణ �� �����մϴ�. �׿� ���ÿ� Ž���� �������� �� ȿ���� ���� �ʾƼ� ������.

�ֳ��ϸ�, find�� Ž���� �����ϸ� �ٷ� ��������, count�� ���� ���� �� �ִ����� ã�� ���� ������ ������ ���ϴ�.(����Ž��)



#### ���ĵ� �������� � ���� �ִ����� �˾� ���µ����� binary_search�� �׸��Դϴ�. ǥ�� C ���̺귯���� bsearch�� �޸�, binary_search�� ���� �ִ���, �������� ��Ÿ���� bool ������ ��ȯ�մϴ�.

```c++
//���ĵ� ���� �Դϴ�.
		vector<int> vi;
		generate_n(back_inserter(vi), 100, [count = 0]() mutable {return count++ / 3; });

		if (binary_search(vi.begin(), vi.end(), 10)) {
			//10 �� �����̳� �ȿ� �ֽ��ϴ�.
		}
		else {
			//�����ϴ�.
		}
```



#### ���ĵ� ������ �ְ� �� �ȿ��� Ư�� ���� ���� ��ü�� ��ġ�� ã�� �ʹٸ�, equal_range�� �켱���� ���Դϴٸ�, lower_bound�� ������ ���� ���� �����ϴ�.

���� ã�� ���� lower_bound�� ȣ���ϸ�, �� �˰������� ���ϴ� ���� ���� ��ü�� ù° �纻(ã���� ��) �ƴϸ� �� ���� ���Ե� ������ ��ġ(ã�� ������ ��)�� ����Ű�� �ݺ��ڸ� ��ȯ�մϴ�.

find�� ����������, lower_bound�� ���(�ݺ���)�� �������� ���ϴ� ���� ����� ����Ű�� �ִ��� �����ؾ� �ϴµ���, �� ��쿡�� �ݺ��ڰ� ����Ű�� ��ü�� �������� ���ϴ� ���� ����Ű�� �ִ����� �����ϸ� �˴ϴ�.

�� �� ���� �е��� �� �˻縦 �ؼ� ������ �ϴ�����. ���� ��� �� �˻縦 �ص� ������ ������, �׸� 19���� �� �� �ֵ��� �� �˻�� ��� �˻��� ����� �󸶵��� �޶��� �� �ֽ��ϴ�.

���� �� �˻� ��� ��� �˻縦 �ϴ� ���� �´ٰ� �� �� �ֽ��ϴ�(�׸� 19���� �� �����, �׸� 24���� �׷��� �ص� ������ ���� �����Ǿ� �ֽ��ϴ�).

```c++
auto iter = lower_bound(vi.begin(), vi.end(), 10);
		/*
			i�� ��ü�� ����Ű�� �ִ��� Ȯ���մϴ� 
			Ȯ���ؾ� ����. �� �ڵ忣 ���װ� �ֽ��ϴ�!

			*iter = 10 �� �� �˻縦 �����մϴ�. 
			������ binary_search�� ��� �˻縦 ������� �����ϱ� ������ ������ �ʴ� ������ �� ���ɼ��� �����մϴ�.
		*/
		if (iter != vi.end() && *iter == 10) {      
			//���ϴ� ���� �տ� ���� ���� ���� ���� ù° ��ü�� ����ŵ�ϴ�.
		}
		else {
			//�� ã�ҽ��ϴ�.                              
		}

		//�Ʒ��� �� ��Ȯ�մϴ�. ��� �˻縦 �����մϴ�.
		if (iter != vi.end() && !(less<int>()(10, *iter))) {}
```

```c++
//20 ���� ū ������ ���� �����մϴ�.
vi.erase(upper_bound(vi.begin(), vi.end(), 20), vi.end());

//10���� ���� ������ ���� �����մϴ�.
vi.erase(vi.begin(), lower_bound(vi.begin(), vi.end(), 10));
```



#### lower_bound���� �� �� ���� ����� equal_range�� ���� ���Դϴ�. equal_range�� �ݺ��� ������ ������ pair ��ü�� ��ȯ�ϴµ�, ù° �ݺ��ڴ� lower_bound�� ��ȯ�ϴ� �װͰ� ����, ��° �ݺ��ڴ� upper_bound�� ��ȯ�ϴ� �װ�(ã�����ϴ� �Ͱ� ������ ���� ���� ������ ���� �ٷ� ����)�� �����ϴ�.

```c++
auto iterPair = equal_range(vi.begin(), vi.end(), 10);
		if (iterPair.first != iterPair.second) {
			cout << "There are " << distance(iterPair.first, iterPair.second)
				<< " elements in vw equivalent to 10.";
		}
```



#### ǥ�� ������ �����̳�(vector, string, deque, list)�� ���ؼ��� ���ݱ��� ������ ������ �״�� �����ص� �����մϴ�. ������, ǥ�� ���� �����̳�(set, multiset, map, multimap)�� ���ٸ� �̾߱Ⱑ �޶����ϴ�. �̵��� STL �˰����򺸴� �Ϲ������� �� �� ���̴� Ž���� ��� �Լ��� ������ �ֱ� ��������.

�̷� ������, ���� �����̳ʿ��� Ž���� ������ count, find, equal_range, lower_bound, upper_bound�� ���ؼ��� �Ȱ��� �̸��� ��� �Լ��� ����ϴ� ���� ���ٴ� ����� ����������?

binary_search�� �����ε�, �� �˰������ ����� ��� �Լ��� �����ϴ�. ��·�� set�̳� map���� � ���� �ִ����� �˾Ƴ� �� count�� �� �� �ֽ��ϴ�.

multiset�̳� multimap���� � ���� �ִ��� �˾ƺ��� ������ count���� find�� �Ϲ������� �����ϴ�. find�� ���� ã���� �ٷ� ���ߴ� �ݸ鿡, count�� �־��� ��쿡 �����̳� ���� ��� ��ü�� ������ ã�� �˴ϴ�.

������ ���� �����̳ʿ��� count�� ��ü ����(counting)�� �ſ� �������Դϴ�. Ư�� equal_range�� ��ȯ�ϴ� �� �ݺ����� �Ÿ��� ���ϴ� �ͺ��� �� �����ϴ�.

ù°��, count�� �� ��Ȯ�մϴ�. ��°��, �� �����ϴ�. ��°��, �Ƹ��� count�� �� ���� ���Դϴ�.

|                    �츮�� �ñ��� �ϴ� ��                     |    ����� �˰�����     |                 | ����� ��� �Լ� |                       |
| :----------------------------------------------------------: | :--------------------: | --------------- | ---------------- | --------------------- |
|                         ����/������                          | ���ĵ��� ���� �������� | ���ĵ� �������� | set/map          | multiset/multimap     |
|                     ���ϴ� ���� �ֳ���?                      |          find          | binary_search   | count            | find                  |
| ���ϴ� ���� �ֳ���? �׷� �� ���� ���� ù° ��ü�� ��� �ֳ���? |          find          | equal_range     | find             | find �Ǵ� lower_bound |
| ���ϴ� ���� �տ� ���� ���� ���� ���� ù° ��ü�� ��� �ֳ���? |        find_if         | lower_bound     | lower_bound      | lower_bound           |
| ���ϴ� ���� �ڿ� �ִ� ���� ���� ù ���� ��ü�� ��� �ֳ���? |        find_if         | upper_bound     | upper_bound      | upper_bound           |
|             ���ϴ� ���� ���� ��ü�� �� ���ΰ���?             |         count          | equal_range     | count            | count                 |
|         ���ϴ� ���� ���� ��ü�� ��� ��� �ֳ���?          |    find(���� ȣ��)     | equal_range     | equal_range      | equal_range           |