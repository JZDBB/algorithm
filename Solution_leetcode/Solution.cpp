#include <iostream>
#include <vector>
#include <math.h>
#include<algorithm>
using namespace std;

//#define min(a,b)  (((a)<(b))?(a):(b))



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


	/*
	有一个正整数n，找到一系列的完全平方数（比如，1,4,9,16,...），
	它们的和为n，并且这些完全平方数的数量最少，返回完全平方数的最少数量。
	状态转移方程：
	dp[i]表示整数i的完全平方数的最少数量。
	dp[i]=min{ dp[i-j*j] + 1 | j >= 1 and j*j <= i }。
	*/
	int numSquares(int n) 
	{
		static vector<int> cntPerfectSquares{ 0 };//n=0时，数量为0，充当初始值。
		while (cntPerfectSquares.size() <= n) //cntPerfectSquares.size()==n+1时，说明正整数n的结果已经找到。
		{
		    int cur = cntPerfectSquares.size();//当前的正整数
			int cur_count = INT_MAX;//当前正整数的结果
			for (int i = 1; i*i <= cur; i++) //遍历所有小于或等于当前正整数的完全平方数
			{
				cur_count = min(cur_count, cntPerfectSquares[cur - i * i] + 1);//更新最小值
				
			}
			cntPerfectSquares.emplace_back(cur_count);//当前正整数的结果已经找到，记录下来
			
		}
		    return cntPerfectSquares[n];
		
	}


	// 将数字转变为英文写法。
	string get(int num)
	{
		string ge[20] = { "","One","Two","Three","Four","Five","Six","Seven","Eight","Nine","Ten","Eleven","Twelve","Thirteen","Fourteen","Fifteen","Sixteen","Seventeen","Eighteen","Nineteen" };//不超过19的正整数表达
		string shi[10] = { "","","Twenty","Thirty","Forty","Fifty","Sixty","Seventy","Eighty","Ninety" };//十位不小于2的表达
		string ans = "";
		int gewei = num % 10, shiwei = (num / 10) % 10, baiwei = num / 100;//把数分成个位、十位、百位
		int pre = 0;//先前是否有非0数的标记
		if (baiwei != 0)//百位不为0
		{
			pre = 1;
			ans = ans + ge[baiwei] + " Hundred";
		}
		if (shiwei > 1)//十位大于1，单独表达
		{
			if (pre)ans = ans + " ";//先前已有非0数，添加空格
			pre = 1;
			ans = ans + shi[shiwei];
		}
		if (shiwei == 1 || gewei != 0)//十位和个位组成的数为小于20的正数时，一起表达
		{
			if (shiwei == 1)gewei = gewei + 10;
			if (pre)ans = ans + " ";//先前已有非0数，添加空格
			ans = ans + ge[gewei];
		}
		return ans;
	}
	string numberToWords(int num)
	{
		if (num == 0)return "Zero";//数为0，直接返回
		string rear[4] = { ""," Thousand"," Million"," Billion" };//每一级的末尾单位
		int nums[4];
		for (int i = 0; i < 4; i++)//给数分级
		{
			nums[i] = num % 1000;
			num = num / 1000;
		}
		string ans = "";
		int pre = 0;//先前是否有非0数的标记
		for (int i = 3; i >= 0; i--)
		{
			if (!nums[i])continue;//该级为0
			if (pre)ans = ans + " ";//先前已有非0数，添加空格
			pre = 1;
			ans = ans + get(nums[i]) + rear[i];//添加该级的表达以及末尾单位
		}
		return ans;
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