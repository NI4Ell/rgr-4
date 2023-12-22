#include <iostream>
#include <vector>
#include <algorithm>
#include <map>
#include <fstream>
#include <iomanip>
using namespace std;
struct SMark
{
    string Subject; //предмет
    int Mark; //оценка
};
struct SStudData
{
    string Name; //фамилия, инициалы
    int Number; //номер зачетки
    vector <SMark> Marks; //рез-ты сессии
};
// Функция для сортировки по номеру зачетки
bool sortByNumber(const pair<int, SStudData>& a, const pair<int, SStudData>& b) {
    return a.first < b.first;
}

// Функция для вычисления среднего балла по студенту
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
        cout << "Невозможно открыть данный файл";
        return 1;
    }
    int numberOfStudents;
    inputFile >> numberOfStudents;
    
    for (int i = 0; i < numberOfStudents; ++i) {//вывод
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

    vector<pair<int, SStudData>> sortedStudents(students.begin(), students.end());//сортировка по номеру
    sort(sortedStudents.begin(), sortedStudents.end(), sortByNumber);

    cout << "Сортировка по номеру:" << endl;
    for (const auto& student : sortedStudents) {
        cout << "Number: " << student.first << ", Name: " << student.second.Name << endl;
    }

    cout << "Средний балл::" << endl;
    for (const auto& student : students) {
        double average = calculateAverage(student.second);
        cout << "Number: " << student.first << ", Name: " << student.second.Name
            << ", Average Mark: " << fixed << setprecision(2) << average << endl;
    }

}