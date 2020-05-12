// ConsoleApplication7.cpp : 此檔案包含 'main' 函式。程式會於該處開始執行及結束執行。
//

#include <iostream>
#include<fstream>
#include <random>
#include <chrono>
#include <stdio.h>
#include <math.h>


using namespace std;
const double lc = 5.256;
const int duplicate = 4;
const double temp = 300;
const double k = 1.380*pow(10,-23);
const double m = 39.948/6.02*pow(10, -23);

const double mu = pow(k*temp/ m,0.5);
const double sigma = 10;
const double timestep = pow(10, -1);


void dump(int timea,int count, double loc[256][3]) {

	char filename[50];

	snprintf(filename, sizeof(filename),"fcc%d.dump", timea);


	fstream fp;
	fp.open(filename, ios::out);
	fp << "ITEM: TIMESTEP " << endl;
	fp << "0 " << endl;
	fp << "ITEM: NUMBER OF ATOMS " << endl;
	fp << count << endl;
	fp << "ITEM: BOX BOUNDS pp pp pp " << endl;
	fp << 0 * lc << ' ' << duplicate * lc << endl;
	fp << 0 * lc << ' ' << duplicate * lc << endl;
	fp << 0 * lc << ' ' << duplicate * lc << endl;
	fp << "ITEM: ATOMS id type x y z " << endl;

	for (int i = 0; i < count; i++) {
		fp << i + 1 << ' ' << 0 << ' ' << loc[i][0] << ' ' << loc[i][1] << ' ' << loc[i][2] << ' ' << endl;
	}
}

double *create_speed(double v[256][3]) {
	std::default_random_engine gen;
	std::normal_distribution<double> dis(mu, sigma);

	std::normal_distribution<double> si(0, sigma);
	for (int i = 0; i < 256; i++) {
		for (int d = 0; d < 3; d++) {
			(si(gen) > 0) ? v[i][d] = dis(gen) : v[i][d] = -dis(gen);
		}
	}
	return *v;
}

double *run(double v[256][3], double loc[256][3]) {
	for (int i = 0; i < 256; i++) {
		for (int d = 0; d < 3; d++) {
			loc[i][d] += timestep * v[i][d];
		}
	}
	return *loc;
}
double *periodic(double loc[256][3]) {
	for (int i = 0; i < 256; i++) {
		for (int d = 0; d < 3; d++) {
			loc[i][d] = (loc[i][d] > duplicate * lc) ? loc[i][d] - duplicate * lc : loc[i][d];
			loc[i][d] = (loc[i][d] < 0) ? loc[i][d] + duplicate * lc : loc[i][d];
		}
	}
	return *loc;
}

int main(){
	double fcc[4][3] = { {0,0,0},
	{0,0.5,0.5},
	{0.5,0,0.5},
	{0.5,0.5,0}
	};
	double loc[256][3] = { 0.0 };
	double v[256][3] = { 0.0 };

	int count = 0;
	for (int x = 0; x < duplicate; x++) {
		for (int y = 0; y < duplicate; y++) {
			for (int z = 0; z < duplicate; z++) {
				for (int i = 0; i < 4; i++) {
					count++;
					printf("location %d: [%.4f ,%.4f ,%.4f ]\n", count, (fcc[i][0] + x) * lc, (fcc[i][1] + y) * lc, (fcc[i][2] + z) * lc);
					loc[count - 1][0] = (fcc[i][0] + x) * lc;
					loc[count - 1][1] = (fcc[i][1] + y) * lc;
					loc[count - 1][2] = (fcc[i][2] + z) * lc;
				};
			};
		};
	};

	create_speed(v);
	for (int i = 0; i < 10; i++) {
		dump(i, count, loc);
		run(v, loc);
		periodic(loc);
	}

	
}

// 執行程式: Ctrl + F5 或 [偵錯] > [啟動但不偵錯] 功能表
// 偵錯程式: F5 或 [偵錯] > [啟動偵錯] 功能表

// 開始使用的提示: 
//   1. 使用 [方案總管] 視窗，新增/管理檔案
//   2. 使用 [Team Explorer] 視窗，連線到原始檔控制
//   3. 使用 [輸出] 視窗，參閱組建輸出與其他訊息
//   4. 使用 [錯誤清單] 視窗，檢視錯誤
//   5. 前往 [專案] > [新增項目]，建立新的程式碼檔案，或是前往 [專案] > [新增現有項目]，將現有程式碼檔案新增至專案
//   6. 之後要再次開啟此專案時，請前往 [檔案] > [開啟] > [專案]，然後選取 .sln 檔案
