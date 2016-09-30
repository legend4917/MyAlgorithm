#include<iostream>
using namespace std;

int main(){
	string s;
	cin >> s;
	int n = s.length();
	cout << n << endl;
	int minx = n;
	for(int i=1; i<n/2+1; i++){
		if(n % i != 0)		// 字符串的长度必须能整除当前子串的长度 
			continue;
		bool flag = true;
		string temp1 = s.substr(0,i);	// 截取长度为i子串 
		int j = i;
		while(j<n){
			string temp2 = s.substr(j,i); 
			if(temp2 != temp1){		// 判断连续的i长度的子串是否相等 
				flag = false;
				break;
			}
			j += i;
		}
		if(flag){
			minx = i;
			break;
		}
	}
	cout << n/minx << endl;		// 得出循环前后两次相等的个数 
	return 0;
} 
