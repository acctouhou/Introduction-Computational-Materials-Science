#include <graphics.h>
#include <conio.h>
#include <math.h>  
#include<iostream>
using namespace std;


int main()
{
	int screenWidth = 600;        
	int screenHeight = 600;      
	double sigma = 3.405;
	double epsilon = 0.01032;
	double x[100] = { 0.0 };
	double x1[100] = { 0.0 };
	double v[100] = { 0.0 };
	double f[100] = { 0.0 };
	double temp1 = 0.0;
	double temp2 = 0.0;
	double scx = 200;
	double scy = 150;
	initgraph(screenWidth, screenHeight);



	for (int i = 0; i < 100; i++) {
		x[i] =i/ 40.0 + 0.5;
	}
	for (int i = 0; i < 100; i++) {
		x1[i] = x[i] * sigma;
	}
	for (int i = 0; i < 100; i++) {
		temp1 = pow(sigma / x1[i], 6);
		v[i] =4* epsilon*(pow(temp1,2)-temp1);
	}
	for (int i = 0; i < 100; i++) {
		temp2 = pow(sigma / x1[i], 6);
		f[i] = 24.0 *(2.0/x1[i]*(temp2*temp2)-1/x1[i]*temp2);
	}



	for (int i = 0; i < 100; i++) {
		//line(int(x[i]* scx), int(v[i]* scy+150), int(x[i + 1]* scx), int(v[i + 1]* scy + 150));
		setlinecolor(LIGHTBLUE);
		circle(int(x[i] * scx), int((v[i] * scy/ epsilon)+ 225)*-1+600,1);
		setlinecolor(LIGHTRED);
		circle(int(x[i] * scx), int((f[i] * scy + 225) )*-1+600, 1);
		//cout << int(v[i] * scy+225)<<endl;
	}
	

	_getch();	
	closegraph();

	return 0;
}