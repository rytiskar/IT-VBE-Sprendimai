#include <iostream>
#include <fstream>
#include <vector>

#define MAX_DAYS 31
#define ROW_SIZE 9

using namespace std;

void Read(vector<int>& data);
int Calculate(const vector<int>& data, int days[], int& numberOfDays);
void Write(int minTime, const int days[], int numberOfDays);

int main()
{
	vector<int> data;
	int days[MAX_DAYS];
	int numberOfDays = 0;

	Read(data);
	int minTime = Calculate(data, days, numberOfDays);
	Write(minTime, days, numberOfDays);
	
	return 0;
}

void Read(vector<int>& data)
{
	int d;
	ifstream fin("U1.txt");
	fin >> d;
	for (int i = 0; i < d * ROW_SIZE; i++)
	{
		int temp;
		fin >> temp;
		data.push_back(temp);
	}
	fin.close();
}

int Calculate(const vector<int>& data, int days[], int& numberOfDays)
{
	int minTime = numeric_limits<int>::max();
	int temp = data.size();
	for (int i = 0; i < data.size(); i++)
	{
		int day = data[i++];
		int morningTime = abs((data[i++] * 60 + data[i++]) - (data[i++] * 60 + data[i++]));
		int eveningTime = abs((data[i++] * 60 + data[i++]) - (data[i++] * 60 + data[i]));
		if (morningTime == 0 || eveningTime == 0) { continue; }

		int AllTime = morningTime + eveningTime;
		if (AllTime < minTime)
		{
			minTime = AllTime;
			numberOfDays = 0;
			days[numberOfDays++] = day;
		}
		else if (AllTime == minTime)
		{
			days[numberOfDays++] = day;
		}
	}
	return minTime;
}

void Write(int minTime, const int days[], int numberOfDays)
{
	ofstream fout("U1_rez.txt");
	fout << "Minimalus laikas" << endl;
	fout << minTime << endl;
	fout << "Dienos" << endl;
	for (int i = 0; i < numberOfDays; i++)
	{
		fout << days[i] << " ";
	}
	fout.close();
}