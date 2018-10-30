#include <iostream>
#include <vector>
using namespace std;


class Solution {
	public:
	//����һ��n����������nums��Ҫ��ÿ��0���ƶ�������ĩβ������Ҫ���ַ������ֵ����˳�򲻱�
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
	/*����һ������Ϊn + 1�����飬����ÿ�����ֵķ�Χ��[1, n]������ֻ��һ���ظ�������
	  ����Ҫ���ҳ�����ظ�������������������������
		���ܸĶ�ԭʼ����
		����ԭʼ���飬ֻ�����⿪��O(1)�Ŀռ�
		�㷨���Ӷ�һ��ҪС��O(n ^ 2)
		�ظ����Ǹ��������ظ���ֹһ��*/
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