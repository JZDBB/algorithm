#include <iostream>
#include <vector>
using namespace std;


class Solution {
	public:
	//给出一串n个数的序列nums，要求将每个0都移动到序列末尾，但是要保持非零数字的相对顺序不变
	void moveZeroes(vector<int>& nums) 
	{
		int j = 0;
		for (int i = 0; i < nums.size(); i++) {
				if (nums[i] != 0) {
						nums[j++] = nums[i];
			
			}
		
		}
			for (int j; j < nums.size(); j++) {
				nums[j] = 0;
			
		}
	
	}
	/*给出一个长度为n + 1的数组，其中每个数字的范围是[1, n]，其中只有一个重复的数，
	  现在要求找出这个重复的数，并且满足以下条件：
		不能改动原始数组
		除了原始数组，只能另外开辟O(1)的空间
		算法复杂度一定要小于O(n ^ 2)
		重复的那个数可能重复不止一次*/
	int findDuplicate(vector<int>& nums) 
	{
		int n = nums.size();
		int l = 1, r = n;
		while (l < r) 
		{
		    int m = (l + r) >> 1, cnt = 0;
			for (int i = 0; i < n; i++)
			{
				if (nums[i] <= m) cnt++;

			}			   
			if (cnt > m) r = m;
			else l = m + 1;
			
		}
		    return l;	
	}

};

//int main()
//{
//	int arr[10] = { 1, 0, 2, 4, 0, 2, 5, 10, 4, 0};
//	Solution solution;
//	int num[10];
//	solution.moveZeroes(arr);
//	for (int i = 0; i < 10; i++)
//	{
//		printf("%d", arr[i]);
//	}
//	
//}