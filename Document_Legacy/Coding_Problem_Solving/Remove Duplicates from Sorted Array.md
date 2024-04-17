Qusetion
=============

[LeetCode][googlelink]

[googlelink]: https://leetcode.com/problems/remove-duplicates-from-sorted-array/

정렬된 배열에서 중복되는 원소 삭제하기

 Answer
 --------

```
class Solution {
public:
    int removeDuplicates(vector<int>& nums) {
        if(nums.size() == 0) return 0;
        
        int prev = nums[0];
        for(int i = 1; i < nums.size(); i++){
            if(nums[i] != prev){
                prev =nums[i];
            }else{
                nums.erase(nums.begin() + i);
                i--;
            }
        }
        
        return nums.size();
    }
};
```

`std::unique()` 를 사용하면 더 간단하게 만들 수 있다.

```
class Solution {
public:
    int removeDuplicates(vector<int>& nums) {
        nums.erase(std::unique(nums.begin(), nums.end()), nums.end());
        return nums.size();
    }
};
```

`std::unique` 참조 : http://www.cplusplus.com/reference/algorithm/unique/
