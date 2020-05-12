// ConsoleApplication7.cpp : 此檔案包含 'main' 函式。程式會於該處開始執行及結束執行。
//

#include <iostream>
#include<fstream>
using namespace std;

int main()
{	
	double lc = 5.256;
	double fcc[4][3] ={{0,0,0},
	{0,0.5,0.5},
	{0.5,0,0.5},
	{0.5,0.5,0}
	};
	double loc[256][3] = { 0.0 };

	int duplicate = 4;
	int count = 0;
	for (int x = 0; x < duplicate; x++) {
		for (int y = 0; y< duplicate; y++) {
			for (int z = 0; z < duplicate; z++) {
				for (int i = 0; i < 4; i++) {
					count++;
					printf("location %d: [%.4f ,%.4f ,%.4f ]\n", count, (fcc[i][0] + x) * lc, (fcc[i][1] + y) * lc, (fcc[i][2] + z) * lc);
					loc[count-1][0]= (fcc[i][0] + x) * lc;
					loc[count - 1][1] = (fcc[i][1] + y) * lc;
					loc[count - 1][2] = (fcc[i][2] + z) * lc;
				};
			};
		};
	};


	char filename[] = "fcc.dump";
	fstream fp;
	fp.open(filename, ios::out);
	fp << "ITEM: TIMESTEP " << endl;
	fp << "0 " << endl;
	fp << "ITEM: NUMBER OF ATOMS " << endl;
	fp << count << endl;
	fp << "ITEM: BOX BOUNDS pp pp pp " << endl;
	fp << 0*lc<<' '<< duplicate *lc << endl;
	fp << 0*lc<<' '<< duplicate *lc << endl;
	fp << 0 * lc << ' ' << duplicate * lc << endl;
	fp << "ITEM: ATOMS id type x y z " << endl;

	for (int i = 0; i < count; i++) {
		fp << i + 1 <<' '<< 0 << ' ' << loc[i][0]  << ' ' << loc[i][1]  << ' ' << loc[i][2] << ' ' << endl;
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
