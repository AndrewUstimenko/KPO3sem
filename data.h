#pragma once

#include <string>
#include <list>
#include <set>
#include <vector>
#include "GameObjects.h"

class GameSettings {
public:
    int subjectsCount;
    std::string studentName = "";
    std::string studentSpecialty = "";

    int maxnumofsubj;
    std::list<std::string> allStudentNames;
    std::set<std::string> allSpecialties;

    void save();
};

class GameSession {
private:
    Student student;
    std::vector<int> scheduleDeck; //колода расписания
    int currentDay;
    int totalLessons;              //было пар изначально
    std::string sessionName;
    bool midtermPassed;

public:
    //конструкторы
    GameSession(const Student& student, const std::vector<int>& deck);
    GameSession();

    //гетеры
    Student& getStudent();
    bool isDeckEmpty() const;
    size_t getDeckSize() const;
    int getCurrentDay() const;
    int getTotalLessons() const;
    std::string getSessionName() const;
    bool isMidtermPassed() const;
    //сетер для сессии
    void setSessionName(const std::string& name);
    void setMidtermPassed(bool passed);

    //методы изменения состояния игры
    void incrementDay();
    int popLesson(); //взять следующий предмет

    //сохранения
    bool saveGame(const std::string& filename);
    bool loadGame(const std::string& filename);
};