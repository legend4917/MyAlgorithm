#include<iostream>
using namespace std;

int main(){
	string s;
	cin >> s;
	int n = s.length();
	cout << n << endl;
	int minx = n;
	for(int i=1; i<n/2+1; i++){
		if(n % i != 0)		// �ַ����ĳ��ȱ�����������ǰ�Ӵ��ĳ��� 
			continue;
		bool flag = true;
		string temp1 = s.substr(0,i);	// ��ȡ����Ϊi�Ӵ� 
		int j = i;
		while(j<n){
			string temp2 = s.substr(j,i); 
			if(temp2 != temp1){		// �ж�������i���ȵ��Ӵ��Ƿ���� 
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
	cout << n/minx << endl;		// �ó�ѭ��ǰ��������ȵĸ��� 
	return 0;
} 
