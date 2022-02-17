#ifndef STUDENT_H
#define STUDENT_H

#include <QString>

class Student
{
private:
    QString name;
    int age;
    double averScore;
    bool isSuspended;

public:
    Student();
    Student(QString _name, int _age, double _averScore, bool _isSuspended);

    void setName(QString _name);
    QString getName();

    void setAge(int _age);
    int getAge();

    void setAverScore(double _averScore);
    double getAverScore();

    void setIsSuspended(bool _isSuspended);
    bool getIsSuspended();
};

#endif // STUDENT_H
