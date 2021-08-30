//ปาริตา นาวารี 64010522
#include <bits/stdc++.h>
using namespace std;

bool isPrime(int num)
{
	int sum = 0;
	for (int i = 1; i <= sqrt(num); i++)
	{
		if (num % i == 0 && num != i) sum++;
	}
	if (sum == 1) return 1;
	else return 0;
}
int main()
{	int number;
	cout << "Input Number : ";
	cin >> number;
	if (isPrime(number)) cout << "Prime Number";
	else cout << "Not Prime Number";
	
}