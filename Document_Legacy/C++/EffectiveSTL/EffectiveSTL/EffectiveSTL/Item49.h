#pragma once
#include <iostream>
#include <vector>
#include <list>
#include <algorithm>
#include <map>
#include <string>
#include <array>
#include <set>
#include <memory>
#include <numeric>

//STL�� ���õ� �����Ϸ� ���� �޽����� �ؼ��ϴ� �ɷ��� ������

namespace Item49 {
	using namespace std;

	/*
		å���� �ٸ��� c++ 11 ���ķδ� SFINAE ������ ���ϴ�.
	*/

	inline void RunSample() {
		//�Ʒ��� �ڵ�� �� �Ʒ��� �����޼����� ����մϴ�.
		//string s(10);
		/*
			�ɰ���	�ڵ�	����	������Ʈ	����	��	��ǥ�� ����(Suppression) ����

			����(Ȱ��)	E0289	�μ� ����� ��ġ�ϴ� ������ 
			"std::basic_string<_Elem, _Traits, _Alloc>::basic_string 
			[��� _Elem=char, _Traits=std::char_traits<char>, _Alloc=std::allocator<char>]"�� �ν��Ͻ��� �����ϴ�.
			EffectiveSTL	C:\Users\USER\Documents\TIL\Document\C++\EffectiveSTL\EffectiveSTL\EffectiveSTL\Item49.h	19	

			�ɰ���	�ڵ�	����	������Ʈ	����	��	��ǥ�� ����(Suppression) ����

			����	C2664	
			'std::basic_string<char,std::char_traits<char>,std::allocator<char>>::basic_string(const std::basic_string<char,std::char_traits<char>,std::allocator<char>> &)': �μ� 1��(��) 'int'���� 'std::initializer_list<_Elem>'(��)�� ��ȯ�� �� �����ϴ�.	
			EffectiveSTL	C:\Users\USER\Documents\TIL\Document\C++\EffectiveSTL\EffectiveSTL\EffectiveSTL\Item49.h	19
		*/

		/*
			std::basic_string<char,std::char_traits<char>,std::allocator<char>> �� string ���� ���ĺ���

			std::basic_string<char,std::char_traits<char>,std::allocator<char>>::basic_string(const std::basic_string<char,std::char_traits<char>,std::allocator<char>> &)': �μ� 1��(��) 'int'���� 'std::initializer_list<_Elem>'(��)�� ��ȯ�� �� �����ϴ�.

			=>

			string::string(const string&)': �μ� 1��(��) 'int'���� 'std::initializer_list<_Elem>'(��)�� ��ȯ�� �� �����ϴ�.
			�� �����ϰ� ����� �� �ֽ��ϴ�. ��, �����ڿ� ���޵Ǵ� ���ڰ� �߸��Ǿ��ٴ� ���Դϴ�.
		*/







		/*
			�Ʒ��� ����ü�� ���ϰ� �� �����޽����� ����մϴ�.
			struct {
				map<string, string> m;
				void showValue(const string& key) const
				{
					if (map<string, string>::iterator i = m.find(key); i != m.end()) { <= �� ���ο��� ������ �߻��մϴ�.
						//... ã�� ���
					}
					//... �� ã�� ���
				}
			};
		*/
		



		/*
			�ɰ���	�ڵ�	����	������Ʈ	����	��	��ǥ�� ����(Suppression) ����
			����(Ȱ��)	E0312	
			"std::_Tree_const_iterator<std::_Tree_val<std::conditional_t<true, std::_Tree_simple_types<std::pair<const std::string, std::string>>, std::_Tree_iter_types<std::pair<const std::string, std::string>, size_t, ptrdiff_t, std::pair<const std::string, std::string> *, const std::pair<const std::string, std::string> *, std::pair<const std::string, std::string> &, const std::pair<const std::string, std::string> &, std::_Tree_node<std::pair<const std::string, std::string>, void *> *>>>>"
			���� "std::conditional_t<false, std::_Tree_const_iterator<std::_Tree_val<std::conditional_t<true, std::_Tree_simple_types<std::pair<const std::string, std::string>>, std::_Tree_iter_types<std::pair<const std::string, std::string>, size_t, ptrdiff_t, std::pair<const std::string, std::string> *, const std::pair<const std::string, std::string> *, std::pair<const std::string, std::string> &, const std::pair<const std::string, std::string> &, std::_Tree_node<std::pair<const std::string, std::string>, void *> *>>>>, std::_Tree_iterator<std::_Tree_val<std::conditional_t<true, std::_Tree_simple_types<std::pair<const std::string, std::string>>, std::_Tree_iter_types<std::pair<const std::string, std::string>, size_t, ptrdiff_t, std::pair<const std::string, std::string> *, const std::pair<const std::string, std::string> *, std::pair<const std::string, std::string> &, const std::pair<const std::string, std::string> &, std::_Tree_node<std::pair<const std::string, std::string>, void *> *>>>>>"(��)���� ����� ���� ��ȯ�� �������� �ʽ��ϴ�.	EffectiveSTL	
			
			C:\Users\USER\Documents\TIL\Document\C++\EffectiveSTL\EffectiveSTL\EffectiveSTL\Item49.h	51	

			�ʹ� �� �̸� ���ĺ��� �Ʒ��� �����ϴ�.






		"std::_Tree_const_iterator
		<
			std::_Tree_val
			<
				std::conditional_t
				<
					true, 
					std::_Tree_simple_types
					<
						std::pair<const std::string, std::string>>, 
						std::_Tree_iter_types
						<
							std::pair<const std::string, std::string>, 
							size_t, 
							ptrdiff_t, 
							std::pair<const std::string, std::string> *, 
							const std::pair<const std::string, std::string> *, 
							std::pair<const std::string, std::string> &, 
							const std::pair<const std::string, std::string> &, 
							std::_Tree_node
							<
								std::pair<const std::string, std::string>, 
								void *
							> *
						>
					>
				>
			>"

			
			���� 
			"std::conditional_t
			<false, 
				std::_Tree_const_iterator<std::_Tree_val
				<
					std::conditional_t
					<
						true, 
						std::_Tree_simple_types
						<
							std::pair<const std::string, std::string>>, 
							std::_Tree_iter_types
							<
								std::pair<const std::string, std::string>, 
								size_t, 
								ptrdiff_t, 
								std::pair<const std::string, std::string> *, 
								const std::pair<const std::string, std::string> *, 
								std::pair<const std::string, std::string> &, 
								const std::pair<const std::string, std::string> &, 
								std::_Tree_node<std::pair<const std::string, std::string>, void *> *
							>
						>
					>
				>, 
				std::_Tree_iterator
				<
					std::_Tree_val
					<
						std::conditional_t
						<
							true, 
							std::_Tree_simple_types
							<
								std::pair<const std::string, std::string>>, 
								std::_Tree_iter_types
								<
									std::pair<const std::string, std::string>, 
									size_t, 
									ptrdiff_t, 
									std::pair<const std::string, std::string> *, 
									const std::pair<const std::string, std::string> *, 
									std::pair<const std::string, std::string> &, 
									const std::pair<const std::string, std::string> &, 
									std::_Tree_node<std::pair<const std::string, std::string>, 
									void *
								> *
							>
						>
					>
				>
			>"(��)���� ����� ���� ��ȯ�� �������� �ʽ��ϴ�.	EffectiveSTL







			���� �޽����� �ٿ����ô�. å���� �ٸ��� c++ 11 ���ķδ� SFINAE ������ ���ϴ�.(conditional_t)
			std::conditional_t<bool B, class T, class F> �� B�� true�̸� type�� T�� ����Ű��, false�̸� F�� ����ŵ�ϴ�.

			���ø� Ŭ���� std::_Tree_const_iterator/ _Tree_iterator�� Ÿ�� �Ű������� ���� �ܰ迡�� ũ�� �߿����� �ʽ��ϴ�. 
			SOMETHING���� �ٿ����ô�.

			�Ʒ��� ���� ���� �� �ֽ��ϴ�.





			"std::_Tree_const_iterator<SOMETHING>

			����

			"std::conditional_t
			<
				false,
				std::_Tree_const_iterator<SOMETHING>
				std::_Tree_iterator<SOMETHING>
			>"
			(��)���� ����� ���� ��ȯ�� �������� �ʽ��ϴ�.	EffectiveSTL





			conditional_t �κп��� bool Ÿ���� false�̹Ƿ� ���� Ÿ���� std::_Tree_iterator Ÿ���� ����Ű�� �˴ϴ�.
			�� const_iterator Ÿ���� iterator Ÿ������ ��ȯ�� �� ��� ���� ���� (��û ��) �����޽����� ����� ���Դϴ�.

		*/

		/*
			���������� STL�� �ź񽺷��� ������ �����Ϸ� �޽����� �����ϴµ� ������ �� ��Ʈ�� �� �� ������ ���ҽ��ϴ�.

			1. vector�� string�� ���, �ݺ��ڴ� �����Ϳ� �Ȱ����ϴ�. 
			����, iterator�� ������ �Ǽ��� �ߴٸ� �����Ϸ� ���� �޽����� ������ Ÿ���� ����� ���ɼ��� �����ϴ�.

			2. back_insert_iterator, insert_iterator ���� ����ϴ� �޽����� ���� �׻� back_inserter��, inserter�� ȣ���� �� �Ǽ��� �������ٴ� ���Դϴ�
		
			3. ��� �ݺ���(���� ���, ostream_iterator �׸��� back_inserter���� ��ȯ�� �ݺ��ڵ�)�� 
			���� ������(operator=)�� ���ο��� ��� Ȥ�� ���� ������ ���ϱ� ������, 
			�̷� �ݺ��ڿ� ���� �Ǽ����� ������ ���� �������� ������ ���� ���� �����ڸ� ����̴� �κ��� ���� �޽������� ã�� �� �ֽ��ϴ�.

			4. STL �˰����� ���ΰ� �߸� �Ǿ��ٰ� �����ϴ� �޽������(��, ������ ����Ų �ҽ� �ڵ尡 <algorithm>�� �־��ٸ�), 
			�� �˰���� �Բ� ����� Ÿ�Կ� ������ �־��ٴ� ������ �˾Ƶ�������.

			5. vector�� string, for_each�� ���� ���� ���̴� STL ������Ʈ�� ����ϰ� �ִµ� 
			�����Ϸ� �ʿ��� �������� �ǵ��� �ٸ� �ľ����� ���ϰڴٴ� ���� �޽����� ����, �����ȱ��� �ʿ��� ����� #include���� ���� ����Դϴ�.
		*/
	}
}