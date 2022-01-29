#include <iostream>
#include <fstream>
#include <string>
#include <map>
#include <vector>
#include <algorithm>

using namespace std;

struct Info
{
    string name;
    int number = 0;
    string fish_name[30];
    int mass[30] = { 0 };
    int points = 0;
};

void Read(int& n, Info info[], map<string, int>& rating);
void AddPoints(int n, Info info[], const map<string, int>& rating);
void AddMass(int n, const Info info[], map<string, int>& rating);
void Write(int n, const Info info[], const vector<pair<string, int>>& mapcopy);

int main()
{
    int n;
    Info info[30];
    map<string, int> rating;
    Read(n, info, rating);
    AddPoints(n, info, rating);
    AddMass(n, info, rating);
    
    sort(info, info + n, [](Info a, Info b)
        {
            if (a.points != b.points)
                return a.points > b.points;
            return a.name < b.name;
        }
    );

    vector<pair<string, int>> mapcopy(rating.begin(), rating.end());
    sort(mapcopy.begin(), mapcopy.end(), [](pair<string, int> a, pair<string, int> b)
        {
            if (a.second != b.second)
                return a.second > b.second;
            return a.first < b.first;
        }
    );

    Write(n, info, mapcopy);

    return 0;
}


void Read(int& n, Info info[], map<string, int>& rating)
{
    ifstream fin("U2.txt"); 
    fin >> n;
    for (int i = 0; i < n; i++)
    {
        char temp[21];
        fin.ignore(numeric_limits<int>::max(), '\n');
        fin.get(temp, 20);
        info[i].name = temp;
        fin >> info[i].number;
        for (int j = 0; j < info[i].number; j++)
        {
            fin.ignore(numeric_limits<int>::max(), '\n');
            fin.get(temp, 20);
            info[i].fish_name[j] = temp;
            fin >> info[i].mass[j];
            if (info[i].mass[j] < 200)
                info[i].points += 10;
            else
                info[i].points += 30;
        }
    }
    int k; fin >> k;
    for (int i = 0; i < k; i++)
    {
        char temp[21];
        int rate;
        fin.ignore(numeric_limits<int>::max(), '\n');
        fin.get(temp, 20);
        fin >> rate;
        rating[string(temp)] = rate;
    }
    fin.close();
}

void AddPoints(int n, Info info[], const map<string, int>& rating)
{
    for (int i = 0; i < n; i++)
        for (int j = 0; j < info[i].number; j++)
            info[i].points += rating.find(info[i].fish_name[j])->second;
}

void AddMass(int n, const Info info[], map<string, int>& rating)
{
    for (auto& x : rating)
        x.second = 0;
    for (int i = 0; i < n; i++)
        for (int j = 0; j < info[i].number; j++)
            rating.find(info[i].fish_name[j])->second += info[i].mass[j];
}

void Write(int n, const Info info[], const vector<pair<string, int>>& mapcopy)
{
    ofstream fout("U2rez.txt");
    fout << "Dalyviai" << endl;
    for (int i = 0; i < n; i++)
        fout << info[i].name << " " << info[i].points << endl;
    fout << "Laimikiai" << endl;
    for (const auto& x : mapcopy)
        fout << x.first << " " << x.second << endl;
    fout.close();
}