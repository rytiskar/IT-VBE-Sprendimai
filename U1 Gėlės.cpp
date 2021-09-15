#include <iostream>
#include <fstream>

using namespace std;

constexpr int MAX_DAYS = 92;
constexpr int JUNE = 6, JULY = 7, AUGUST = 8;
constexpr int JUNE_DAYS = 30, JULY_DAYS = 31;

void Read(int days[]);
int Find(int& start, int& end, const int days[]);
int ToDay(int month, int monthDay);
int ToMonth(int& day);
void Write(int numberOfFlowers, int startMonth, int startDay, int endMonth, int endDay);

int main()
{
	int days[MAX_DAYS] = { 0 };
	int startDay = 0, endDay = 0;

	Read(days);
	int numberOfFlowers = Find(startDay, endDay, days);
	int startMonth = ToMonth(startDay);
	int endMonth = ToMonth(endDay);
	Write(numberOfFlowers, startMonth, startDay, endMonth, endDay);

	return 0;
}

void Read(int days[])
{
	int n;
	int number;
	int startMonth, startDay, endMonth, endDay;
	ifstream fin("U1.txt");
	fin >> n;
	for (int i = 0; i < n; i++)
	{
		fin >> number >> startMonth >> startDay >> endMonth >> endDay;

		int start = ToDay(startMonth, startDay);
		int end = ToDay(endMonth, endDay);

		for (int j = (start - 1); j <= (end - 1); j++) { days[j]++; }
	}
	fin.close();
}

int Find(int& start, int& end, const int days[])
{
	int numberOfFlowers = 0;
	for (int i = 0; i <= (MAX_DAYS - 1); i++)
	{
		if (numberOfFlowers < days[i]) { numberOfFlowers = days[i]; }
	}

	for (int i = 0; i <= (MAX_DAYS - 1); i++)
	{
		if (days[i] == numberOfFlowers)
		{ 
			start = i + 1;
			while (days[i] == numberOfFlowers) { end = ++i; }
			break;
		}
	}
	return numberOfFlowers;
}

int ToDay(int month, int monthDay)
{
	if (month == JULY) { return JUNE_DAYS + monthDay; }
	else if (month == AUGUST) { return JUNE_DAYS + JULY_DAYS + monthDay; }
	return monthDay;
}

int ToMonth(int& day)
{
	if (day > JUNE_DAYS && day <= JUNE_DAYS + JULY_DAYS) { day -= JUNE_DAYS; return JULY; }
	else if (day > JUNE_DAYS + JULY_DAYS) { day -= JUNE_DAYS + JULY_DAYS; return AUGUST; }
	return JUNE;
}

void Write(int numberOfFlowers, int startMonth, int startDay, int endMonth, int endDay)
{
	ofstream fout("U1rez.txt");
	fout << numberOfFlowers << endl;
	fout << startMonth << " " << startDay << endl;
	fout << endMonth << " " << endDay << endl;
	fout.close();
}