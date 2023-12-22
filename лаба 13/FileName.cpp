#include <iostream>
#include <vector>
#include <algorithm>
#include <map>
#include <fstream>
#include <iomanip>
using namespace std;
struct SMark
{
    string Subject; //�������
    int Mark; //������
};
struct SStudData
{
    string Name; //�������, ��������
    int Number; //����� �������
    vector <SMark> Marks; //���-�� ������
};
// ������� ��� ���������� �� ������ �������
bool sortByNumber(const pair<int, SStudData>& a, const pair<int, SStudData>& b) {
    return a.first < b.first;
}

// ������� ��� ���������� �������� ����� �� ��������
double calculateAverage(const SStudData& student) {
    if (student.Marks.empty()) {
        return 0.0;
    }

    int sum = 0;
    for (const auto& mark : student.Marks) {
        sum += mark.Mark;
    }

    return static_cast<double>(sum) / student.Marks.size();
}

int main() {
    setlocale(LC_ALL, "rus");

    map<int, SStudData> students;
    ifstream inputFile("students.txt");
    if (!inputFile.is_open()) {
        cout << "���������� ������� ������ ����";
        return 1;
    }
    int numberOfStudents;
    inputFile >> numberOfStudents;
    
    for (int i = 0; i < numberOfStudents; ++i) {//�����
        SStudData student;
        inputFile >> student.Name >> student.Number;

        int numberOfMarks;
        inputFile >> numberOfMarks;

        for (int j = 0; j < numberOfMarks; ++j) {
            SMark mark;
            inputFile >> mark.Subject >> mark.Mark;
            student.Marks.push_back(mark);
        }

        students[student.Number] = student;
    }

    inputFile.close();

    vector<pair<int, SStudData>> sortedStudents(students.begin(), students.end());//���������� �� ������
    sort(sortedStudents.begin(), sortedStudents.end(), sortByNumber);

    cout << "���������� �� ������:" << endl;
    for (const auto& student : sortedStudents) {
        cout << "Number: " << student.first << ", Name: " << student.second.Name << endl;
    }

    cout << "������� ����::" << endl;
    for (const auto& student : students) {
        double average = calculateAverage(student.second);
        cout << "Number: " << student.first << ", Name: " << student.second.Name
            << ", Average Mark: " << fixed << setprecision(2) << average << endl;
    }

}