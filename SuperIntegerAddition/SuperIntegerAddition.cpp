// SuperIntegerAddition.cpp : Defines the entry point for the application.
//

#include "SuperIntegerAddition.h"

using namespace std;
int string2vector(string s, int in_radix, vector<int>& v)
{
	int temp;
	auto len = s.size();
	int flag = 0;
	for (int i = 0;i < len;i++)
	{
		temp = static_cast<int>(tolower(s[i]));
		if (temp > 47 && temp < 58)
		{
			temp = temp - 48;
		}
		else if (temp > 96 && temp < 123)
		{
			temp = temp - 87;
		}
		else if (i != 0)
		{
			cout << "ERROR: '" << s[i] << "' is a Illegal character!" << endl;
			return 1;
			break;
		}
		if (temp >= in_radix && temp != 43 && temp != 45)
		{
			cout << "ERROR: '" << s[i] << "' is not a " << in_radix << " radix number!" << endl;
			return 1;
			break;
		}
		switch (i)
		{
			case 0:
			{
				if (temp != 43 && temp != 0)
				{
					v.push_back(temp);
					if (temp != 45)
					{
						flag = 1;
					}
				}
			}; break;
			default:
			{
				if (flag == 1)
				{
					goto label;
				}
				else if (temp != 0)
				{
					flag = 1;
				}
			label:
				if (flag == 1)
				{
					v.push_back(temp);
				}
			}
		}
	}
	return 0;
}
int addition(int* p1, size_t len1, int* p2, size_t len2, vector<int>& sum, int in_radix)
{
	vector<int> sum_rev;
	size_t max_num = max(len1, len2);
	size_t min_num = min(len1, len2);
	int carry = 0;
	if (p1[0] == 45)
	{
		max_num -= 1;
		min_num -= 1;
		sum.push_back(45);
	}
	int cur_pos;
	for (int i = 0; i < max_num; i++)
	{
		if (i < min_num)
		{
			cur_pos = p1[len1 - i - 1] + p2[len2 - i - 1] + carry;
			if (cur_pos >= in_radix)
			{
				carry = cur_pos / in_radix;
				cur_pos %= in_radix;
			}
			else
			{
				carry = 0;
			}
			sum_rev.push_back(cur_pos);
		}
		else if (len1 >= max_num)
		{
			sum_rev.push_back(p1[len1 - i - 1] + carry);
			carry = 0;
		}
		else
		{
			sum_rev.push_back(p2[len2 - i - 1] + carry);
			carry = 0;
		}	
	}
	if (carry)
	{
		sum_rev.push_back(carry);
	}
	size_t num = sum_rev.size();
	for (int i = 0;i < num;i++)
	{
		sum.push_back(sum_rev[num - i - 1]);
	}
	return 0;
}
int compare(int* p1, size_t len1, int* p2, size_t len2)
{
	int n = len1;
	int m = len2;
	if (p1[0] == 45)
	{
		n -= 1;
	}
	if (p2[0] == 45)
	{
		m -= 1;
	}
	if (n > m)
	{
		return 1;
	}
	else if (n < m)
	{
		return 2;
	}
	else
	{
		for (int i = 0; i < m; i++)
		{
			if (p1[i + len1 - n] > p2[i + len2 - m])
			{
				return 1;
			}
			else if (p1[i + len1 - n] < p2[i + len2 - m])
			{
				return 2;
			}
		}
	}
	return 0;
}
int minus_operation(int* p1, size_t len1, int* p2, size_t len2, vector<int>& sum, int in_radix)
{
	vector<int> remain_rev;
	int n = len1;
	int m = len2;
	if (p1[0] == 45)
	{
		n = len1 - 1;
	}
	if (p2[0] == 45)
	{
		m = len2 - 1;
	}
	int max_num = max(m, n);
	int min_num = min(m, n);
	int cmp_res;
	cmp_res = compare(p1, len1, p2, len2);
	if (cmp_res == 1 && p1[0] == 45 || cmp_res == 2 && p2[0] == 45)
	{
		sum.push_back(45);
	}
	if (cmp_res == 0)
	{
		remain_rev.push_back(0);
		return 0;
	}
	int cur_pos;
	int carry = 0;
	for (int i = 0; i < max_num; i++)
	{
		if (i < min_num)
		{
			if (cmp_res == 1)
			{ 
				cur_pos = p1[len1 - i - 1] - p2[len2 - i - 1] - carry;
			}
			else
			{
				cur_pos = - p1[len1 - i - 1] + p2[len2 - i - 1] - carry;
			}
			if (cur_pos < 0)
			{
				carry = cur_pos / in_radix;
				cur_pos %= in_radix;
			}
			else
			{
				carry = 0;
			}
			remain_rev.push_back(cur_pos);
		}
		else
		{
			if (cmp_res == 1)
			{
				remain_rev.push_back(p1[len1 - i - 1] - carry);
			}
			else
			{
				remain_rev.push_back(p2[len2 - i - 1] - carry);
			}
			carry = 0;
		}		
	}
	size_t num = remain_rev.size();
	for (int i = 0; i < num; i++)
	{
		sum.push_back(remain_rev[num - i - 1]);
	}
	return 0;
}
int radix_exchange(int* p, int len, int origin_radix, int tar_radix, vector<int>& res)
{
	int idx = 0;
	int x = 0;
	int y = 0;
	int sum = 1;
	vector<int> res_rev;
	if (p[0] == 45)
	{
		res.push_back(45);
		idx += 1;
	}
	while (sum != 0)
	{
		y = 0;
		sum = 0;
		for (int i = idx; i < len; i++)
		{
			x = (y * origin_radix + p[i]) / tar_radix;
			y = (y * origin_radix + p[i]) % tar_radix;
			p[i] = x;
			sum += p[i];
		}
		res_rev.push_back(y);
	}
	size_t num = res_rev.size();
	for (int i = 0; i < num; i++)
	{
		res.push_back(res_rev[num - i - 1]);
	}
	return 0;
}
int main(int argc, char * argv[])
{
	// read file
	ifstream fin;
	fin.open(argv[1], ios::in);
	if (!fin.is_open())
	{
		cout << argv[1] << " " << "Not Found!" << endl;
		return 1;
	}
	// input radix and output radix
	int in_radix = 0;
	for (int i = 0; i < strlen(argv[2]); i++)
	{
		int temp = static_cast<int>(argv[2][i]) - 48;
		in_radix += static_cast<int>(temp * pow(10, strlen(argv[2]) - i -1));
	}
	int out_radix = 0;
	for (int i = 0; i < strlen(argv[3]); i++)
	{
		int temp = static_cast<int>(argv[3][i]) - 48;
		out_radix += static_cast<int>(temp * pow(10, strlen(argv[3]) - i -1));
	}
	// string to vector
	string buff;
	string s1;
	string s2;
	vector<int> num_1st = {};
	vector<int> num_2nd = {};
	int str2vec_res1 = 0;
	int str2vec_res2 = 0;
	int i = 0;
	while (getline(fin, buff) && i < 2)
	{
		i++;
		switch (i)
		{
			case 1: str2vec_res1 = string2vector(buff, in_radix, num_1st); s1 = buff; break;
			case 2: str2vec_res2 = string2vector(buff, in_radix, num_2nd); s2 = buff; break;
		}
	}
	if (str2vec_res1 || str2vec_res2)
	{
		cout << "Program Terminated!" << endl;
		return 1;
	}
	// addition and minus_operation
	vector<int> in_result;
	vector<int> out_result;
	if (num_1st[0] == 45 && num_2nd[0] == 45 || num_1st[0] != 45 && num_2nd[0] != 45)
	{
		addition(&num_1st[0], num_1st.size(), &num_2nd[0], num_2nd.size(), in_result, in_radix);
	}
	else
	{
		minus_operation(&num_1st[0], num_1st.size(), &num_2nd[0], num_2nd.size(), in_result, in_radix);
	}
	radix_exchange(&in_result[0], in_result.size(), in_radix, out_radix, out_result);
	// output
	cout << in_radix << " radix input:\n" << s1 << "\n" << s2 <<endl;
	cout << out_radix << " radix Result :";
	int temp;
	char ch = 0;
	for (int i = 0; i < out_result.size(); i++)
	{
		temp = out_result[i];
		if (temp > -1 && temp < 10)
		{
			ch = temp + 48;
		}
		else if (temp > 9 && temp < 32)
		{
			ch = temp + 87;
		}
		else
		{
			ch = temp;
		}
		cout << ch;
	}
	return 0;
}
