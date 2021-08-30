#include <bits/stdc++.h>
using namespace std;
int main()
{
	string str;
	getline(cin, str);
	cout << str << endl;
	for (int i = 0; i < str.size(); i++)
	{
		if (str[i] >= '0' && str[i] <= '9')
		{
			int sum = 0;
			while (str[i] >= '0' && str[i] <= '9' && i < str.size())
			{
				sum = (sum * 10) + str[i] - 48;
				i++;
			}
			if (i < str.size())
			{
				for (int j = 0; j < sum; j++)
				{
					cout << str[i];
				}
			}
			
		}
		else cout << str[i];
	}
}