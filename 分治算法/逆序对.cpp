#include <iostream>
#include <stdlib.h> 
#include <ctime>
using namespace std;

#define Random(x) (rand() % x)
int a[1000000];
int cnt = 0;

void mergesort(int start, int end){
	if (start == end)
		return;
		
	int midx = (start+end)/2;
	mergesort(start, midx);
	mergesort(midx+1, end);
	
	int temp[end-start+1];
	int j=0,l=start,r=midx+1;
	while((l<=midx) && (r<=end)){
		if (a[l] <= a[r]){
			temp[j++] = a[l++];
		} else {
			temp[j++] = a[r++];
			cnt += midx + 1 - l;	// 统计逆序对的个数 
		}
	}
	while(l<=midx){
		temp[j++] = a[l++];
	}
	while(r<=end){
		temp[j++] = a[r++];
	}
	for (int i=0; i<j; i++){
		a[i+start] = temp[i];
	}
	return;
}

int main(){
	int n;
	cin >> n;
	srand((int)time(0));	// 设置随机数种子 
	for(int i=0; i<n; i++){		// 生成n个10000以内的随机数 
		a[i] = Random(10000);
		cout << a[i] << " ";
	}
	cout << endl;
	mergesort(0, n-1);		// 归并排序，并统计逆序对的个数 
	cout << cnt << endl;
	return 0;
} 
