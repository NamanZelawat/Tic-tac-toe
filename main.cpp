#include<bits/stdc++.h>
#include <termios.h>
#include <unistd.h>
#include "ansi.cpp"
#include "getch.cpp"

using namespace std;

map<int,pair<int,int>> numpad_to_mat;
map<pair<int,int>,int> mat_to_numpad;
string error_string;

void print_mat(vector<vector<char>> mat)
{
	cout<<"\n";
	for(int i = 0;i<3;i++)
	{
		cout<<"\t";
		for(int j = 0;j<3;j++)
		{
			cout<<mat[i][j]<<" ";
			if(j < 2)
			{
				cout<<"| ";
			}
		}
		cout<<"\n";
		if(i < 2)
		{
			cout<<"\t";
			for(int i = 0;i<9;i++)
			{
				cout<<"-";
			}
			cout<<"\n";
		}
	}
	cout<<"\n";
}

bool mover(vector<vector<char>> &mat)
{
	cout<<"Give in a move : ";
	string s;
	cin>>s;
	if(s.size() == 1)
	{
		char temp = s[0];
		if(temp - '0' >= 1 && temp - '0' <=9)
		{
			int val = temp-'0';
			char init = mat[numpad_to_mat[val].first][numpad_to_mat[val].second];
			if(init == 'X' || init == 'O')
			{
				return false;
				error_string = "Place not empty try some other move";
			}
			else
			{
				mat[numpad_to_mat[val].first][numpad_to_mat[val].second] = 'X';
				error_string = ":)";
			}
		}
		else
		{
			return false;
			error_string = "Invalid Move";
		}
		return true;
	}
	error_string = "Invalid Move";
	return false;
}


int score_checker(vector<vector<char>> v)
{
	for(int i = 0;i<3;i++)
	{
		int temp = 0;
		for(int j = 0;j<3;j++)
		{
			if(v[i][j] == 'O')
			{
				temp++;
			}
		}
		if(temp == 3)
		{
			return 10;
		}
	}	
	for(int i = 0;i<3;i++)
	{
		int temp = 0;
		for(int j = 0;j<3;j++)
		{
			if(v[j][i] == 'O')
			{
				temp++;
			}
		}
		if(temp == 3)
		{
			return 10;
		}
	}	
	for(int i = 0;i<3;i++)
	{
		int temp = 0;
		for(int j = 0;j<3;j++)
		{
			if(v[i][j] == 'X')
			{
				temp++;
			}
		}
		if(temp == 3)
		{
			return -10;
		}
	}	
	for(int i = 0;i<3;i++)
	{
		int temp = 0;
		for(int j = 0;j<3;j++)
		{
			if(v[j][i] == 'X')
			{
				temp++;
			}
		}
		if(temp == 3)
		{
			return -10;
		}
	}	
	int temp = 0;
	for(int i = 0;i<3;i++)
	{
		if(v[i][i] == 'O')
		{
			temp++;
		}
	}	
	if(temp == 3)
	{
		return 10;
	}
	temp = 0;
	for(int i = 0;i<3;i++)
	{
		if(v[i][2-i] == 'O')
		{
			temp++;
		}
	}	
	if(temp == 3)
	{
		return 10;
	}
	temp = 0;
	for(int i = 0;i<3;i++)
	{
		if(v[i][i] == 'X')
		{
			temp++;
		}
	}	
	if(temp == 3)
	{
		return -10;
	}
	temp = 0;
	for(int i = 0;i<3;i++)
	{
		if(v[i][2-i] == 'X')
		{
			temp++;
		}
	}	
	if(temp == 3)
	{
		return -10;
	}
	return 0;
}

bool is_full(vector<vector<char>> v)
{
	int temp = 0;
	for(int i = 0;i<3;i++)
	{
		for(int j = 0;j<3;j++)
		{
			if(v[i][j] == 'O' || v[i][j] == 'X')
			{
				temp++;
			}
		}
	}
	return (temp == 9);
}

int solver(vector<vector<char>> v,int tm)
{
	int score = score_checker(v);
	if(score == 10 || score == -10)
	{
		return score;
	}
	if(is_full(v))
	{
		return 0;
	}
	vector<vector<char>> temp;
	temp = v;
	if(tm%2 == 0)
	{
		score = INT_MAX;
		for(int i = 0;i<3;i++)
		{
			for(int j = 0;j<3;j++)
			{
				if(temp[i][j] == '-')
				{
					temp[i][j] = 'X';
					score = min(score,solver(temp,tm+1));
					temp[i][j] = '-';
				}
			}
		}
		return score;
	}
	else
	{
		score = INT_MIN;
		for(int i = 0;i<3;i++)
		{
			for(int j = 0;j<3;j++)
			{
				if(temp[i][j] == '-')
				{
					temp[i][j] = 'O';
					score = max(score,solver(temp,tm+1));
					temp[i][j] = '-';
				}
			}
		}
		return score;
	}
}

void AI(vector<vector<char>> &v)
{
	cout<<"Computer is thinking ...\n";
	vector<vector<char>> temp;
	temp = v;
	int bestScore = INT_MIN;
	for(int i = 0;i<3;i++)
	{
		for(int j = 0;j<3;j++)
		{
			if(temp[i][j] == '-')
			{
				temp[i][j] = 'O';
				int movScore = solver(temp,0);
				if(movScore > bestScore)
				{
					v = temp;
					bestScore = movScore;
				}
				temp[i][j] = '-';
			}
		}
	}
}

int main()
{
	system("clear");

	vector<vector<char>> mat;

	for(int i = 0;i<3;i++)
	{
		mat.push_back(vector<char>(3,'-'));
	}

	numpad_to_mat[7] = {0,0};
	numpad_to_mat[8] = {0,1};
	numpad_to_mat[9] = {0,2};
	numpad_to_mat[4] = {1,0};
	numpad_to_mat[5] = {1,1};
	numpad_to_mat[6] = {1,2};
	numpad_to_mat[1] = {2,0};
	numpad_to_mat[2] = {2,1};
	numpad_to_mat[3] = {2,2};

	mat_to_numpad[{0,0}] = 7;
	mat_to_numpad[{0,1}] = 8;
	mat_to_numpad[{0,2}] = 9;
	mat_to_numpad[{1,0}] = 4;
	mat_to_numpad[{1,1}] = 5;
	mat_to_numpad[{1,2}] = 6;
	mat_to_numpad[{2,0}] = 1;
	mat_to_numpad[{2,1}] = 2;
	mat_to_numpad[{2,2}] = 3;

	Ansi ansi;

	cout << ansi.get_code(ansi.FOREGROUND_RED);
 	cout << "-------------------------------------------\n";
 	cout << ansi.get_code(ansi.RESET);
 	cout << ansi.get_code(ansi.FOREGROUND_GREEN);
	cout<<"Games-Z\n";
	cout << ansi.get_code(ansi.RESET);
	cout << ansi.get_code(ansi.FOREGROUND_RED);
 	cout << "-------------------------------------------\n";
 	cout << ansi.get_code(ansi.RESET);
 	cout << ansi.get_code(ansi.FOREGROUND_GREEN);
	cout<<"Tic-Tac-toe\n";
	cout << ansi.get_code(ansi.RESET);
	cout << ansi.get_code(ansi.FOREGROUND_RED);
 	cout << "-------------------------------------------\n";
 	cout << ansi.get_code(ansi.RESET);
 	cout << ansi.get_code(ansi.FOREGROUND_GREEN);
	cout<<"You can't win from me\n";
	cout << ansi.get_code(ansi.RESET);
	cout << ansi.get_code(ansi.FOREGROUND_RED);
 	cout << "-------------------------------------------\n\n\n";
 	cout << ansi.get_code(ansi.RESET);

 	cout << ansi.get_code(ansi.FOREGROUND_RED);
	cout<<"~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~\n";
	cout << ansi.get_code(ansi.RESET);
	cout << ansi.get_code(ansi.FOREGROUND_GREEN);
	cout<<"You are X and it's your turn\n";
	cout << ansi.get_code(ansi.RESET);
	cout << ansi.get_code(ansi.FOREGROUND_RED);
	cout<<"~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~\n";
	cout << ansi.get_code(ansi.RESET);
	cout << ansi.get_code(ansi.FOREGROUND_GREEN);
	cout<<"Use the numpad to select the box\n";
	cout << ansi.get_code(ansi.RESET);
	cout << ansi.get_code(ansi.FOREGROUND_RED);
	cout<<"~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~\n\n";
	cout << ansi.get_code(ansi.RESET);


	cout << ansi.get_code(ansi.FOREGROUND_BLUE);
	for(int i = 0;i<3;i++)
	{
		cout<<"\t";
		for(int j = 0;j<3;j++)
		{
			cout<<mat_to_numpad[{i,j}]<<" ";
			if(j < 2)
			{
				cout<<"| ";
			}
		}
		cout<<"\n";
		if(i < 2)
		{
			cout<<"\t";
			for(int i = 0;i<9;i++)
			{
				cout<<"-";
			}
			cout<<"\n";
		}
	}
	cout << ansi.get_code(ansi.RESET);
	cout<<"\n";

	cout << ansi.get_code(ansi.FOREGROUND_RED);
	cout<<"~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~\n";
	cout << ansi.get_code(ansi.RESET);
	cout << ansi.get_code(ansi.FOREGROUND_GREEN);
	cout<<"Press any key to begin\n";
	cout << ansi.get_code(ansi.FOREGROUND_RED);
	cout<<"~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~\n";
	cout << ansi.get_code(ansi.RESET);
	cout << ansi.get_code(ansi.FOREGROUND_GREEN);
	cout<<"Press q to exit\n";
	cout << ansi.get_code(ansi.FOREGROUND_RED);
	cout<<"~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~\n";
	cout << ansi.get_code(ansi.RESET);

	char t;
	t = getch();
	if(t == 'q')
	{
		return 0;
	}

	bool tie = true;

	int i = 0;
	//Game loop
	while(true)
	{
		if(score_checker(mat) == 10)
		{
			system("clear");
			cout<<"~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~\n";
			cout<<"message : Game over!"<<"\n";
			cout<<"~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~\n";
			print_mat(mat);
			cout<<"Computer Wins !\n";
			tie = false;
			break;
		}
		if(is_full(mat))
		{
			system("clear");
			cout<<"~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~\n";
			cout<<"message : Game over!"<<"\n";
			cout<<"~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~\n";
			print_mat(mat);
			break;
		}
		system("clear");
		cout<<"~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~\n";
		cout<<"message : "<<error_string<<"\n";
		cout<<"~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~\n";
		print_mat(mat);
		if(i%2 == 0 && mover(mat))
		{
			i++;
		}
		else
		{
			continue;
		}
		if(i%2 == 1)
		{
			AI(mat);
			i++;
		}
	}
	if(tie)
	{
		system("clear");
		cout<<"~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~\n";
		cout<<"message : Game over!"<<"\n";
		cout<<"~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~\n";
		print_mat(mat);
		cout<<"Tie !\n";
	}
}