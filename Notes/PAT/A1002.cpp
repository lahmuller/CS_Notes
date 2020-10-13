#include<stdio.h>
#include<iostream>
#include<iomanip>
using namespace std;
int main() {
	int num1,num2,exp;
	float coe;
	float c[1001] = { 0 };
	cin >> num1;
	for (int i = 0; i < num1; i++) {
		cin >> exp >> coe;
		c[exp] += coe;
	}
	cin >> num2;
	for (int i = 0; i < num2; i++) {
		cin >> exp >> coe;
		c[exp] += coe;
	}
	int num3 = 0;
	for (int i = 0; i < 1001; i++) {
		if (c[i] != 0)	num3++;
	}
	//cout << num3;
	printf("%d", num3);
	for (int i = 1000; i >= 0; i--) {
		if (c[i] != 0) {
			//cout << i << ' ' << c[i];
			printf(" %d %.1f", i, c[i]);
		}
	}
	system("pause");
	return 0;
}
