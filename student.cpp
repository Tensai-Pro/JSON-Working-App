#include "student.h"

Student::Student()
{
}

Student::Student(QString _name, int _age, double _averScore, bool _isSuspended)
{
    name = _name;
    age =_age;
    averScore = _averScore;
    isSuspended = _isSuspended;
}


void Student::setName(QString _name)
{
    name = _name;
}
QString Student::getName()
{
    return name;
}

void Student::setAge(int _age)
{
    age = _age;
}
int Student::getAge()
{
    return age;
}

void Student::setAverScore(double _averScore)
{
    averScore = _averScore;
}
double Student::getAverScore()
{
    return averScore;
}

void Student::setIsSuspended(bool _isSuspended)
{
    isSuspended = _isSuspended;
}
bool Student::getIsSuspended()
{
    return isSuspended;
}
