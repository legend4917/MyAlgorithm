#include <iostream>
#include <algorithm>
#include <cmath>
using namespace std;

int n;
double X[100001];
double Y[100001];


double getMedian(int startX, int endX, int startY, int endY){
	if (endX - startX == 1){	// 若数组X，Y都只剩下两个数 ，则合并后的4个数的中位数就是所求的中位数 
		double temp[4] = {X[startX], X[endX], Y[startY], Y[endY]};
		sort(temp, temp+4);
		return (temp[1] + temp[2]) / 2;
	}
	
	float midX = (startX + endX) / 2.0;
	float midY = (startY + endY) / 2.0;
	double medianX;
	double medianY;
	float flag = 0;
	if ((endX - startX + 1) & 1){	// 若当前数组长度为奇数 
		flag = 0;
		medianX = X[int(midX)];
		medianY = Y[int(midY)];
	} else {						// 若当前数组长度为偶数 
		flag = 1;
		medianX = (X[int(midX)] + X[int(midX+1)]) / 2.0;
		medianY = (Y[int(midY)] + Y[int(midY+1)]) / 2.0;
	}
	if (medianX == medianY)
		return medianX;
	else if (medianX < medianY)
		return getMedian(int(midX), endX, startY, int(midY+flag));	// 去掉数组X较小的一般和数组Y较大的一般 
	else
		return getMedian(startX, int(midX+flag), int(midY), endY); 	// 去掉数组X较大的一般和数组Y较小的一般 
}

int main(){
	cin >> n;		// 输入数组的长度n 
	for (int i=0; i<n; i++)		// 输入数组X和Y 
		cin >> X[i];
	for (int i=0; i<n; i++)
		cin >> Y[i];
	cout << getMedian(0,n-1,0,n-1);
	return 0;
}