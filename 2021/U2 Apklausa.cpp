#include <iostream>
#include <fstream>
#include <vector>
#include <algorithm>
#include <string>

using namespace std;

struct Student
{
public:
    Student(string loc_name, string loc_bestSubject, int loc_numberOfMarks)
        :
        name(loc_name), bestSubject(loc_bestSubject), numberOfMarks(loc_numberOfMarks)
    {}

    int Average()
    {
        int sum = 0;
        for (int i = 0; i < numberOfMarks; i++) { sum += marks[i]; }
        if (numberOfMarks != 0) { return sum / numberOfMarks; }
        return 0;
    }

public:
    string name;
    string bestSubject;
    int numberOfMarks = 0;
    vector<int> marks;
 };

struct Subject
{
public:
    Subject(string loc_title, string loc_name, int loc_n)
        :
        title(loc_title)
    {
        students[loc_n] = loc_name;
    }

public:
    string title;
    int numberOfStudents = 0;
    string students[50];
};

void Read(vector<Subject>& subjects);
bool Difference(Subject a, Subject b);
void Sort(vector<Subject>& subjects);
void Write(const vector<Subject>& subjects);

int main()
{
    vector<Subject> subjects;

    Read(subjects);
    Sort(subjects);
    Write(subjects);
    
    return 0;
}

void Read(vector<Subject>& subjects)
{
    constexpr int MIN_AVERAGE = 9;
    int m, n = 0;
    int number = 0;
    vector<Student> students;

    ifstream fin("U2.txt");
    fin >> m;

    for (int i = 0; i < m; i++)
    {
        string name, bestSubject; fin >> name >> bestSubject;
        int numberOfMarks; fin >> numberOfMarks;
        students.push_back({ name, bestSubject, numberOfMarks });

        for (int j = 0; j < students[i].numberOfMarks; j++)
        { 
            int mark; fin >> mark;
            students[i].marks.push_back(mark);
        }

        if (students[i].Average() >= MIN_AVERAGE)
        {
            bool duplicate = false;
            for (int j = 0; j < n; j++)
            {
                if (students[i].bestSubject == subjects[j].title)
                {
                    duplicate = true;
                    subjects[j].students[subjects[j].numberOfStudents++] = students[i].name;
                }
            }
            if (!duplicate)
            {
                subjects.push_back({ students[i].bestSubject, students[i].name, number });
                number = subjects[n++].numberOfStudents++;
            }
        }
    }
    fin.close();
}

bool Difference(Subject a, Subject b)
{
    if (a.numberOfStudents == b.numberOfStudents)
    {
        return a.title < b.title;
    }
    return a.numberOfStudents > b.numberOfStudents;
}

void Sort(vector<Subject>& subjects)
{
    sort(subjects.begin(), subjects.end(), Difference);
}

void Write(const vector<Subject>& subjects)
{
    ofstream fout("U2_rez.txt");
    if (subjects.size() != 0)
    {
        for (int i = 0; i < subjects.size(); i++)
        {
            fout << subjects[i].title << " " << subjects[i].numberOfStudents << endl;
            for (int j = 0; j < subjects[i].numberOfStudents; j++)
            {
                fout << subjects[i].students[j] << endl;
            }
        }
    }
    else
    {
        fout << "Neatitinka vidurkis" << endl;
    }
    fout.close();
}
