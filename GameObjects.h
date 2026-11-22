#pragma once

#include <string>
#include <vector>
#include <iostream>
#include <algorithm>

class Subject {
private:
    std::string name;
    int attendance;
    int knowledge;

    //поля для экзамена
    std::string questionText;
    std::string ans1;
    std::string ans2;
    char correctAnswerNum;

public:
    //конструктор для загрузки
    Subject(std::string name, int att, int know, std::string q, std::string a1, std::string a2, int correct);

    //коснтруктор для создания с нуля
    Subject(std::string name, std::string q, std::string a1, std::string a2, int correct);

    std::string getName() const;
    int getAttendance() const;
    int getKnowledge() const;

    std::string getQ() const;
    std::string getAns1() const;
    std::string getAns2() const;
    char getCorrectNum() const;

    void visit();
    void study(int basePoints, double specialtyMultiplier, int brainPower);
};

enum class ActionType {
    Rest,         //отдых
    BrainStorm,   //решать задачи
    StudySubject,  //зубрежка предмета
    SpendMoney
};

struct Action {
    std::string description;
    ActionType type;    //тип действия (как обрабатывать)
    int energyCost;   //сколько тратит энергии (или восстанавливает, если < 0)
    int brainGain;    //сколько дает интеллекта
};

class Student {
private:
    std::string name;
    std::string specialty;
    int energy;
    int brainPower;
    int money;
    std::vector<Subject> subjects;

public:
    Student(std::string name, std::string specialty);

    void addSubject(const Subject& subj);

    std::vector<Subject>& getSubjects();

    size_t getSubjectsCount() const;

    int getEnergy() const;
    void changeEnergy(int val);

    int getBrainPower() const;
    void changeBrainPower(int val);

    int getMoney() const;
    void changeMoney(int val);

    std::string getName() const;
    std::string getSpecialty() const;

    double getSpecialtyMultiplier(const std::string& subjectName) const;

    void printStatus() const;
};
