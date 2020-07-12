# const_iterator�� reverse_iterator, const_reverse_iterator�� ������ ���� ������ ���� iterator�̴�

> ������ const_iterator�� �� ������ ������ �����ϰ� �ٲ�����ϴ�.

![](http://twimgs.com/ddj/cuj/images/cuj0106smeyers/diagram1.gif)

- ��� STL ǥ�� �����̳ʴ� �� ���� Ÿ���� �ݺ��ڸ� ��� �����մϴ�. container<T>��� ���ǵ� �����̳ʰ� �ִٰ� �ϸ� iterator�� T*�� ���� �����̰� const_iterator�� const T*�� �Ȱ��� ������ �մϴ�. iterator�� const_iterator�� ������Ű��, �ش� �ݺ��ڴ� ���� ����Ű�� �ִ� ����� �� ���� ��Ҹ� ����Ű��, ��ġ�� �����̳��� ó���� �־����� ���� ��������ϴ�.

- iterator�� const_iterator�� �Ͻ���(implicit) ��ȯ�� �����ϸ�, iterator�� const_iterator�� ���� reverse_iterator�� const_reverse_iterator�� �Ͻ��� ��ȯ�� �����մϴ�.

- reverse_iterator�� const_reverse_iterator�� �Ͻ��� ��ȯ�� �����ϸ�, reverse_iterator�� const_reverse_iterator�� base()�� ���� ���� iterator�� const_iterator�� ��ȯ�� �����մϴ�.

# - const_iterator �� ������ ������ �̷����ϴ�.
  - insert�� erase�� ���� �Լ��� �Ű����� Ÿ������, �� ������ �ݺ��� Ÿ�� �߿� iterator���� �䱸�Ѵٴ� ���� �߿��մϴ�.
#####     - ����� const_iterator�� �Ű������� �ѱ� �� �ֽ��ϴ�.
  - const_iterator�� iterator�� �Ϲ���(implicit)���� ��ȯ�� ����� ������, ���� �ٲٷ��� �׸� 27���� �Ұ��ϴ� ����� ���� ������ �Ϲݼ��� �������� ȿ���� ���� ���嵵 �� �� �����ϴ�.
  - reverse_iterator�� iterator�� ��ȯ�� �� ������, ��ȯ�� �Ŀ� �ణ�� ������ �ʿ��մϴ�. ����, �׸��� �� �̷��� �ϴ����� ���ؼ��� �׸� 28���� �����ϰڽ��ϴ�.
  - ���� ������ ���� iterator�� const_iterator�� �񱳰� ���� �ʴ� ���Դϴ�.
#####     - ����� �� ������ �ݺ��ڿ� ���� �񱳸� �����ϰ� �ֽ��ϴ�.


``` c++17

	vector<int> v;
	auto it = v.begin();
	auto cit = v.cbegin();
	auto rit = v.rbegin();
	auto crit = v.crbegin();

	//_MSC_VER == 1926 ����
	//insert/erase���� const_iterator�� �Ű������� �ѱ� �� �ֽ��ϴ�.
	v.insert(cit, 3); 
	v.erase(cit);

	v.insert(crit, 5); //reverse_const_iterator�� ������ ����

	if (it == cit) ;
	if (cit == it) ;
	if (rit == crit);
	if (crit == rit);

	//������ �ݺ��ڿ� �Ϲ� �ں��ڸ� ���ϸ� ������ ������ �߻��� �� �ֽ��ϴ�.
	if (rit == it) ;	//������ ����

	//å������ �� �κ��� ������ ���� ���� �� �ִٰ� �����մϴ�.
	if (it - cit > 3);	
	//���� �׷��ٸ� �̷��� ��ȸ�մϴ�.
	if (cit + 3 <= it);

```






