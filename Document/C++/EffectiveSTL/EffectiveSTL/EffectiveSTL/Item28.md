# reverse_iterator�� �����Ǵ� ���� �ݺ���(base_iterator)�� ����ϴ� ����� ��Ȯ�ϰ� ��������


- � �����̳� ��� �Լ��� ��� �ݺ��� �Ű� ������ iterator���� �����ϱ� ������ ri�� ����Ű�� ��ġ�� ��Ҹ� ���� ����(insert)�ϰ� �ʹٵ簡 �� �� ��ĩ! �� ���ۿ� �����ϴ�. ri�� ����Ű�� ��Ҹ� ����(erase)�� ���� ��������������. �̷� ��� ��·�� �� reverse_iterator�� iterator�� �ٲپ�� �մϴ�. �̶� ����ϴ� ���� base��� ��� �Լ��Դϴ�.

- reverse_iterator ri�� ����Ű�� vector<int>���� ��ġ���ٰ� ���� 99�� �־� ���� �ʹٰ� Ĩ�ô�. ri�� �����ʿ��� �������� �̵��ϴ� ��ο� ������, STL ���迡�� ��� ������ �ݺ��ڰ� ����Ű�� ��ġ�� �ٷ� �տ��� �̷�����ٴ� ����� ������ �ȵ˴ϴ�.

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
	//4, 5 ���̿� 99�� ���Ե˴ϴ�.
	tmp0.insert(it0, 99);

	//reverse_iterator�� base() �Լ��� ���� iterator�� ��ȯ�մϴ�.
	auto it1 = find(tmp1.rbegin(), tmp1.rend(), 5).base();
	//5, 6 ���̿� 99�� ���Ե˴ϴ�.
	tmp1.insert(it1, 99);

```

```c++

	auto tmp0 = v;
	auto tmp1 = v;

	auto it0 = find(tmp0.begin(), tmp0.end(), 5);
	//5�� �����˴ϴ�.
	tmp0.erase(it0);

	//reverse_iterator�� base() �Լ��� ���� iterator�� ��ȯ�մϴ�.
	auto it1 = find(tmp1.rbegin(), tmp1.rend(), 5).base();
	//6�� �����˴ϴ�.
	tmp1.erase(it1);

```

- reverse_iterator�� iterator�� �ٲ� ��(��, base�� ȣ���� ��)����, �������� �� �ݺ��ڷ� ������ �� �������� ��Ȯ�� ��ȹ�ϰ� �־�� �մϴ�. �ֽἭ �ٲ� iterator�� ���� �������� ���� ���� �ƴ� ���� �ֱ� ��������.