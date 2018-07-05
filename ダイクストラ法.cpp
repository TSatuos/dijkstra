#include<iostream>
#include<algorithm>
#include<vector>

using namespace std;

void print(vector<vector<int>>ans,int n) {
	cout << "\n\nS	A	B	C	D	E	F	G	H	I	" << endl;//���_�̐��͓��̓f�[�^�ŕς�����A�����ł�10���_
	for (int i = 0; i < n; i++) {
		for (int j = 0; j < n; j++) {
			if (ans[i][j] == -1)
				cout << "��	";
			else
				cout << ans[i][j] << "	";
		}
		cout << endl;
	}
}

int main() {
	int n, k;//���_�̐�=n;�o�H�{��=k
	cout << "���_�̐�=";
	cin >> n;
	cout << "�o�H�{��=";
	cin >> k;


	//�����Ɍo�H�R�X�g�����
	vector<vector<int>>d(n, vector<int>(n, -1));//dictionary
	vector<vector<int>>ans(n, vector<int>(n, -1));
	vector<bool>done(n, 1);

	int a, b;	//�o�H�ڑ����_�̓���

	for (int i = 0; i < k; i++) {
		//cout << "d[a][b]:" << endl;
		//cout << "from(a)=";
		cin >> a;
		//cout << "to(b)=";
		cin >> b;
		//cout << "d[" << a << "][" << b << "]=";
		cin >> d[a][b];	//�o�Hcost�̓���
		d[b][a] = d[a][b];
		//cout << endl;
	}



	//�ړ��Ȃ�->cost=0
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
					cout << "��	";
				else
					cout << "s	";
			}
		}
		cout << endl;
	}


	//�X�^�[�g�n�_�̐ݒu
	cout << "where is the start?\n	input:";
	int now;
	cin >> now;

	//�X�^�[�g�n�_���O�ŏ�����
	for (int i = 0; i < n; i++) {
		ans[i][now] = 0;
	}

	done[now] = 0;//cost�m��
	

	//�T��
	for (int row = 0; row < n; row++) {

		b = 0;//������
		int min = -1;
		for (int column = 0; column < n; column++) {
			if (column != now) {
				if (d[now][column] != -1) {//�A�����_������ꍇ
					if (row == 0) {
						b = ans[row][now] + d[now][column];
					}
					else {
						b = ans[row-1][now] + d[now][column];
					}
					if (ans[row][column] < 0 || ans[row][column]>b) {
						ans[row][column] = b;
						for (int j = row+1; j < n; j++) {//�����_�̍ŐV�����X�V
							ans[j][column] =b;
						}
						b = 0;
					}
				}
			}
			
			//print(ans, n);//�񂲂Ƃɕω�
		}
		
		//print(ans, n);//�s���Ƃɕω�


		//�s�Ԃ̖��m�蒸�_���ŏ����m��
		for (int column = 0; column < n; column++) {
			if (column != now && ans[row][column] != -1) {
				if (done[column]) {
					if (min == -1 || ans[row][min] > ans[row][column])
						min = column;
				}
			}
		}

		//�s�Ԃɖ��m�蒸�_�ŏ������邩���f
		if (min != -1) {
			now = min;//���m�蒸�_���ŏ��l���Ƃ�
			done[now] = 0;//���̒��_���m���Ԃɂ���
		}
	}
	
	print(ans, n);//�񓚏o��

	return 0;

}



/*���̓f�[�^

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