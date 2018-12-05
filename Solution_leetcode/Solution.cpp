#include <iostream>
#include <vector>
#include <math.h>
#include<algorithm>
using namespace std;

//#define min(a,b)  (((a)<(b))?(a):(b))



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


	/*
	��һ��������n���ҵ�һϵ�е���ȫƽ���������磬1,4,9,16,...����
	���ǵĺ�Ϊn��������Щ��ȫƽ�������������٣�������ȫƽ����������������
	״̬ת�Ʒ��̣�
	dp[i]��ʾ����i����ȫƽ����������������
	dp[i]=min{ dp[i-j*j] + 1 | j >= 1 and j*j <= i }��
	*/
	int numSquares(int n) 
	{
		static vector<int> cntPerfectSquares{ 0 };//n=0ʱ������Ϊ0���䵱��ʼֵ��
		while (cntPerfectSquares.size() <= n) //cntPerfectSquares.size()==n+1ʱ��˵��������n�Ľ���Ѿ��ҵ���
		{
		    int cur = cntPerfectSquares.size();//��ǰ��������
			int cur_count = INT_MAX;//��ǰ�������Ľ��
			for (int i = 1; i*i <= cur; i++) //��������С�ڻ���ڵ�ǰ����������ȫƽ����
			{
				cur_count = min(cur_count, cntPerfectSquares[cur - i * i] + 1);//������Сֵ
				
			}
			cntPerfectSquares.emplace_back(cur_count);//��ǰ�������Ľ���Ѿ��ҵ�����¼����
			
		}
		    return cntPerfectSquares[n];
		
	}


	// ������ת��ΪӢ��д����
	string get(int num)
	{
		string ge[20] = { "","One","Two","Three","Four","Five","Six","Seven","Eight","Nine","Ten","Eleven","Twelve","Thirteen","Fourteen","Fifteen","Sixteen","Seventeen","Eighteen","Nineteen" };//������19�����������
		string shi[10] = { "","","Twenty","Thirty","Forty","Fifty","Sixty","Seventy","Eighty","Ninety" };//ʮλ��С��2�ı��
		string ans = "";
		int gewei = num % 10, shiwei = (num / 10) % 10, baiwei = num / 100;//�����ֳɸ�λ��ʮλ����λ
		int pre = 0;//��ǰ�Ƿ��з�0���ı��
		if (baiwei != 0)//��λ��Ϊ0
		{
			pre = 1;
			ans = ans + ge[baiwei] + " Hundred";
		}
		if (shiwei > 1)//ʮλ����1���������
		{
			if (pre)ans = ans + " ";//��ǰ���з�0������ӿո�
			pre = 1;
			ans = ans + shi[shiwei];
		}
		if (shiwei == 1 || gewei != 0)//ʮλ�͸�λ��ɵ���ΪС��20������ʱ��һ����
		{
			if (shiwei == 1)gewei = gewei + 10;
			if (pre)ans = ans + " ";//��ǰ���з�0������ӿո�
			ans = ans + ge[gewei];
		}
		return ans;
	}
	string numberToWords(int num)
	{
		if (num == 0)return "Zero";//��Ϊ0��ֱ�ӷ���
		string rear[4] = { ""," Thousand"," Million"," Billion" };//ÿһ����ĩβ��λ
		int nums[4];
		for (int i = 0; i < 4; i++)//�����ּ�
		{
			nums[i] = num % 1000;
			num = num / 1000;
		}
		string ans = "";
		int pre = 0;//��ǰ�Ƿ��з�0���ı��
		for (int i = 3; i >= 0; i--)
		{
			if (!nums[i])continue;//�ü�Ϊ0
			if (pre)ans = ans + " ";//��ǰ���з�0������ӿո�
			pre = 1;
			ans = ans + get(nums[i]) + rear[i];//��Ӹü��ı���Լ�ĩβ��λ
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