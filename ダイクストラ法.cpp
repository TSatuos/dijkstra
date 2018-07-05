#include<iostream>
#include<algorithm>
#include<vector>

using namespace std;

void print(vector<vector<int>>ans,int n) {
	cout << "\n\nS	A	B	C	D	E	F	G	H	I	" << endl;//頂点の数は入力データで変えられる、ここでは10頂点
	for (int i = 0; i < n; i++) {
		for (int j = 0; j < n; j++) {
			if (ans[i][j] == -1)
				cout << "∞	";
			else
				cout << ans[i][j] << "	";
		}
		cout << endl;
	}
}

int main() {
	int n, k;//頂点の数=n;経路本数=k
	cout << "頂点の数=";
	cin >> n;
	cout << "経路本数=";
	cin >> k;


	//辞書に経路コストを入力
	vector<vector<int>>d(n, vector<int>(n, -1));//dictionary
	vector<vector<int>>ans(n, vector<int>(n, -1));
	vector<bool>done(n, 1);

	int a, b;	//経路接続頂点の入力

	for (int i = 0; i < k; i++) {
		//cout << "d[a][b]:" << endl;
		//cout << "from(a)=";
		cin >> a;
		//cout << "to(b)=";
		cin >> b;
		//cout << "d[" << a << "][" << b << "]=";
		cin >> d[a][b];	//経路costの入力
		d[b][a] = d[a][b];
		//cout << endl;
	}



	//移動なし->cost=0
	for (int i = 0; i < n; i++) {
		d[i][i] = 0;
	}


	//test: output dictionary
	cout << "\nd[][]:\n" << endl;
	for (int i = 0; i < n; i++) {
		for (int j = 0; j < n; j++) {
			if (d[i][j] != -1 && d[i][j] != -2)
				cout << d[i][j] << "	";
			else {
				if (d[i][j] == -1)
					cout << "∞	";
				else
					cout << "s	";
			}
		}
		cout << endl;
	}


	//スタート地点の設置
	cout << "where is the start?\n	input:";
	int now;
	cin >> now;

	//スタート地点を０で初期化
	for (int i = 0; i < n; i++) {
		ans[i][now] = 0;
	}

	done[now] = 0;//cost確定
	

	//探索
	for (int row = 0; row < n; row++) {

		b = 0;//初期化
		int min = -1;
		for (int column = 0; column < n; column++) {
			if (column != now) {
				if (d[now][column] != -1) {//連結頂点がある場合
					if (row == 0) {
						b = ans[row][now] + d[now][column];
					}
					else {
						b = ans[row-1][now] + d[now][column];
					}
					if (ans[row][column] < 0 || ans[row][column]>b) {
						ans[row][column] = b;
						for (int j = row+1; j < n; j++) {//現時点の最新情報を更新
							ans[j][column] =b;
						}
						b = 0;
					}
				}
			}
			
			//print(ans, n);//列ごとに変化
		}
		
		//print(ans, n);//行ごとに変化


		//行間の未確定頂点中最小を確定
		for (int column = 0; column < n; column++) {
			if (column != now && ans[row][column] != -1) {
				if (done[column]) {
					if (min == -1 || ans[row][min] > ans[row][column])
						min = column;
				}
			}
		}

		//行間に未確定頂点最小があるか判断
		if (min != -1) {
			now = min;//未確定頂点中最小値をとる
			done[now] = 0;//その頂点を確定状態にする
		}
	}
	
	print(ans, n);//回答出力

	return 0;

}



/*入力データ

10
19
0
1
1
0
4
9
0
7
7
1
4
1
4
7
5
1
2
12
2
4
10
4
5
5
4
8
2
7
8
1
2
5
5
5
8
2
2
3
1
3
5
4
5
6
4
6
8
10
8
9
3
3
6
1
6
9
2

*/