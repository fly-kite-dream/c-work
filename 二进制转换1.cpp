#include <iostream>
#include <string.h>  
#include <cmath> //把十进制1478转为9进制
using namespace std;
int main()
{
	int num = 1478;
	int arr[100];
	int index = 0;
	while (num != 0)
	{
		arr[index] = num % 9;
		num = num / 9;
		index++;
	}
	for (int i = index-1; i >= 0; i--)
	{
		cout << arr[i];
	}
	return 0;
}