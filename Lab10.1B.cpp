// Lab 10.1
// Послідовний пошук в масиві структур
// Варіант 28
#include <iostream>
#include <iomanip>
#include <string>
#include <limits>
using namespace std;

// Перелік спеціальностей
enum Specialty { COMPUTER_SCIENCE, INFORMATICS, MATH_ECONOMICS, PHYSICS_INFORMATICS, LABOR_TRAINING };

// Назви спеціальностей для виведення
const string specialtyStr[] = {
    "Computer Science", "Informatics", "Math and Economics", "Physics and Informatics", "Labor Training"
};

// Структура студента з об'єднанням для третьої оцінки
struct Student
{
    string surname;
    int course;
    Specialty specialty;
    int physics;
    int math;
    union
    {
        int programming;     // для "Комп'ютерні науки"
        int numericMethods;  // для "Інформатика"
        int pedagogy;        // для інших спеціальностей
    };
};

void Create(Student* p, const int N);
void Print(Student* p, const int N);
double AverageThird(Student* p, const int N, const Specialty s);
double AveragePhysics(Student* p, const int N);
double AverageMath(Student* p, const int N);
double AverageProgramming(Student* p, const int N);
double AverageNumericMethods(Student* p, const int N);
double AveragePedagogy(Student* p, const int N);
int CountPhysics5or4(Student* p, const int N);

int main()
{
    int N;
    // Введення кількості студентів з контролем помилок
    while (true)
    {
        cout << "Enter number of students: ";
        if (cin >> N && N > 0)
            break;
        if (cin.eof())
            return 0;
        cin.clear();
        cin.ignore(numeric_limits<streamsize>::max(), '\n');
        cout << "Invalid input, try again." << endl;
    }

    Student* p = new Student[N];

    Create(p, N);
    Print(p, N);

    cout << fixed << setprecision(2);
    cout << "Average physics: " << AveragePhysics(p, N) << endl;
    cout << "Average math: " << AverageMath(p, N) << endl;
    cout << "Average programming: " << AverageProgramming(p, N) << endl;
    cout << "Average numerical methods: " << AverageNumericMethods(p, N) << endl;
    cout << "Average pedagogy: " << AveragePedagogy(p, N) << endl;
    cout << "Students with physics grade 5 or 4: " << CountPhysics5or4(p, N) << endl;

    delete[] p;
    return 0;
}

// Формування масиву структур з клавіатури
void Create(Student* p, const int N)
{
    for (int i = 0; i < N; i++)
    {
        cout << "Student #" << i + 1 << ":" << endl;
        cin.ignore(numeric_limits<streamsize>::max(), '\n');
        cin.clear();

        // Прізвище
        while (true)
        {
            cout << "  Surname: ";
            if (getline(cin, p[i].surname) && !p[i].surname.empty())
                break;
            if (cin.eof())
            {
                p[i].surname = "";
                break;
            }
            cin.clear();
        }

        // Курс
        while (true)
        {
            cout << "  Course (1-6): ";
            if (cin >> p[i].course && p[i].course >= 1 && p[i].course <= 6)
                break;
            if (cin.eof())
            {
                p[i].course = 1;
                break;
            }
            cin.clear();
            cin.ignore(numeric_limits<streamsize>::max(), '\n');
            cout << "  Invalid input." << endl;
        }

        // Спеціальність
        int sp;
        while (true)
        {
            cout << "  Specialty (0 - Computer Science, 1 - Informatics, 2 - Math and Economics, 3 - Physics and Informatics, 4 - Labor Training): ";
            if (cin >> sp && sp >= 0 && sp <= 4)
                break;
            if (cin.eof())
            {
                sp = 0;
                break;
            }
            cin.clear();
            cin.ignore(numeric_limits<streamsize>::max(), '\n');
            cout << "  Invalid input." << endl;
        }
        p[i].specialty = (Specialty)sp;

        // Оцінка з фізики
        while (true)
        {
            cout << "  Physics grade (1-5): ";
            if (cin >> p[i].physics && p[i].physics >= 1 && p[i].physics <= 5)
                break;
            if (cin.eof())
            {
                p[i].physics = 1;
                break;
            }
            cin.clear();
            cin.ignore(numeric_limits<streamsize>::max(), '\n');
            cout << "  Invalid input." << endl;
        }

        // Оцінка з математики
        while (true)
        {
            cout << "  Math grade (1-5): ";
            if (cin >> p[i].math && p[i].math >= 1 && p[i].math <= 5)
                break;
            if (cin.eof())
            {
                p[i].math = 1;
                break;
            }
            cin.clear();
            cin.ignore(numeric_limits<streamsize>::max(), '\n');
            cout << "  Invalid input." << endl;
        }

        // Третя оцінка залежно від спеціальності
        int g;
        while (true)
        {
            switch (p[i].specialty)
            {
            case COMPUTER_SCIENCE:
                cout << "  Programming grade (1-5): ";
                break;
            case INFORMATICS:
                cout << "  Numerical methods grade (1-5): ";
                break;
            default:
                cout << "  Pedagogy grade (1-5): ";
                break;
            }
            if (cin >> g && g >= 1 && g <= 5)
                break;
            if (cin.eof())
            {
                g = 1;
                break;
            }
            cin.clear();
            cin.ignore(numeric_limits<streamsize>::max(), '\n');
            cout << "  Invalid input." << endl;
        }
        switch (p[i].specialty)
        {
        case COMPUTER_SCIENCE:
            p[i].programming = g;
            break;
        case INFORMATICS:
            p[i].numericMethods = g;
            break;
        default:
            p[i].pedagogy = g;
            break;
        }
    }
}

// Виведення масиву у вигляді таблиці
void Print(Student* p, const int N)
{
    cout << "Table of students" << endl;
    cout << string(113, '=') << endl;
    cout << "| " << setw(3) << left << "No"
        << "| " << setw(15) << left << "Surname"
        << "| " << setw(7) << left << "Course"
        << "| " << setw(25) << left << "Specialty"
        << "| " << setw(8) << left << "Physics"
        << "| " << setw(6) << left << "Math"
        << "| " << setw(12) << left << "Programming"
        << "| " << setw(10) << left << "Num.meth."
        << "| " << setw(9) << left << "Pedagogy" << "|" << endl;
    cout << string(113, '=') << endl;
    for (int i = 0; i < N; i++)
    {
        cout << "| " << setw(3) << left << i + 1
            << "| " << setw(15) << left << p[i].surname
            << "| " << setw(7) << left << p[i].course
            << "| " << setw(25) << left << specialtyStr[p[i].specialty]
            << "| " << setw(8) << left << p[i].physics
            << "| " << setw(6) << left << p[i].math;
        switch (p[i].specialty)
        {
        case COMPUTER_SCIENCE:
            cout << "| " << setw(12) << left << p[i].programming
                << "| " << setw(10) << left << ""
                << "| " << setw(9) << left << "" << "|" << endl;
            break;
        case INFORMATICS:
            cout << "| " << setw(12) << left << ""
                << "| " << setw(10) << left << p[i].numericMethods
                << "| " << setw(9) << left << "" << "|" << endl;
            break;
        default:
            cout << "| " << setw(12) << left << ""
                << "| " << setw(10) << left << ""
                << "| " << setw(9) << left << p[i].pedagogy << "|" << endl;
            break;
        }
    }
    cout << string(113, '=') << endl;
}

// Середній бал з фізики
double AveragePhysics(Student* p, const int N)
{
    double sum = 0;
    for (int i = 0; i < N; i++)
        sum += p[i].physics;
    return sum / N;
}

// Середній бал з математики
double AverageMath(Student* p, const int N)
{
    double sum = 0;
    for (int i = 0; i < N; i++)
        sum += p[i].math;
    return sum / N;
}

// Середній бал з третього предмету для студентів заданої спеціальності
// (для "інших" спеціальностей педагогіка береться для всіх трьох)
double AverageThird(Student* p, const int N, const Specialty s)
{
    double sum = 0;
    int k = 0;
    for (int i = 0; i < N; i++)
    {
        bool match;
        if (s == COMPUTER_SCIENCE || s == INFORMATICS)
            match = (p[i].specialty == s);
        else
            match = (p[i].specialty != COMPUTER_SCIENCE && p[i].specialty != INFORMATICS);
        if (!match)
            continue;
        switch (p[i].specialty)
        {
        case COMPUTER_SCIENCE:
            sum += p[i].programming;
            break;
        case INFORMATICS:
            sum += p[i].numericMethods;
            break;
        default:
            sum += p[i].pedagogy;
            break;
        }
        k++;
    }
    if (k == 0)
        return 0;
    return sum / k;
}

// Середній бал з програмування
double AverageProgramming(Student* p, const int N)
{
    return AverageThird(p, N, COMPUTER_SCIENCE);
}

// Середній бал з чисельних методів
double AverageNumericMethods(Student* p, const int N)
{
    return AverageThird(p, N, INFORMATICS);
}

// Середній бал з педагогіки
double AveragePedagogy(Student* p, const int N)
{
    return AverageThird(p, N, LABOR_TRAINING);
}

// Кількість студентів з оцінкою "5" або "4" з фізики
int CountPhysics5or4(Student* p, const int N)
{
    int k = 0;
    for (int i = 0; i < N; i++)
        if (p[i].physics == 5 || p[i].physics == 4)
            k++;
    return k;
}