#include<stdio.h>
#include<iostream>
#include<math.h>
#include<string>
using namespace std;

/*string format(int c) {
	string res = "";
	int len=1;
	char ch;
	while ((c / pow(10, len)) >= 1)
		len++;
	int top = len % 3;
	if (top == 0)
		top = 3;
	for (int i = 1; i <= len; i++) {
		int temp = c / pow(10, len - i);
		ch = '0' + temp;
		res += ch;
		c = c - temp*pow(10, len - i);
		top--;
		if (len == i)
			continue;
		if (top == 0) {
			top = 3;
			res += ",";
		}
	}
	return res;
}

int main() {
	int a, b;
	cin >> a >> b;
	int c = a + b;
	if (c < 0) {
		c = -c;
		cout << "-" << format(c) << endl;
	}
	else
		cout << format(c) << endl;
	system("pause");
}*/

//LIU
int main() {
	int a, b;
	cin >> a >> b;
	string s = to_string(a + b);
	int len = s.length();
	int comma = len % 3;

	for (int i = 0; i < s.length(); i++) {
		cout << s[i];
		if (s[i] == '-')
			continue;
		if ((i + 1) % 3 == comma&&i != len - 1) cout << ',';
	}
	system("pause");
}