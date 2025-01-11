#include <iostream>
#include <string.h>  
#include <cmath> 
using namespace std;
int main()
{
	char num[100];
	strcpy_s(num, "2022");
	int len = strlen(num);
	int goal = 0;
	for (int i = 0; i < strlen(num); i++)
	{
		goal += (num[i]-'0') * pow(9, len-1);
		len--;
	}
	printf("%d", goal);
	return 0;
}