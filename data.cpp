#include "data.h"
#include "settings.h"
#include "start.h"
#include <fstream>
#include <iostream>


//конструкторы и методы GameSession
GameSession::GameSession(const Student& student, const std::vector<int>& deck)
    : student(student), scheduleDeck(deck), currentDay(1), totalLessons(deck.size()), sessionName("new_save") {
}

GameSession::GameSession()
    : student("", ""), currentDay(1), totalLessons(0), sessionName("empty") {
}

Student& GameSession::getStudent() {
    return student;
}

bool GameSession::isDeckEmpty() const {
    return scheduleDeck.empty();
}

size_t GameSession::getDeckSize() const {
    return scheduleDeck.size();
}

int GameSession::getCurrentDay() const {
    return currentDay;
}

int GameSession::getTotalLessons() const {
    return totalLessons;
}

std::string GameSession::getSessionName() const {
    return sessionName;
}

bool GameSession::isMidtermPassed() const {
    return midtermPassed;
}

void GameSession::setSessionName(const std::string& name) {
    sessionName = name;
}

void GameSession::setMidtermPassed(bool passed) {
    midtermPassed = passed;
}

void GameSession::incrementDay() {
    currentDay++;
}

int GameSession::popLesson() {
    if (scheduleDeck.empty()) return -1;
    int lesson = scheduleDeck.back();
    scheduleDeck.pop_back();
    return lesson;
}

//метод сохранения
bool GameSession::saveGame(const std::string& filename) {
    std::ofstream out(filename);
    if (!out.is_open()) return false;

    out << sessionName << "\n" << currentDay << "\n" << totalLessons << "\n";

    out << midtermPassed << "\n";

    out << student.getName() << "\n" << student.getSpecialty() << "\n"
        << student.getEnergy() << "\n" << student.getBrainPower() << "\n"
        << student.getMoney() << "\n";

    auto& subjs = student.getSubjects();
    out << subjs.size() << "\n";
    for (const auto& s : subjs) {
        out << s.getName() << "\n";
        out << s.getAttendance() << "\n";
        out << s.getKnowledge() << "\n";
    }

    out << scheduleDeck.size() << "\n";
    for (int lessonId : scheduleDeck) { out << lessonId << " "; }
    out << "\n";

    out.close();
    return true;
}

bool GameSession::loadGame(const std::string& filename) {
    std::ifstream in(filename);
    if (!in.is_open()) return false;

    std::getline(in, sessionName);
    in >> currentDay >> totalLessons;
    in >> midtermPassed;
    in.ignore();

    std::string sName, sSpecialty;
    int sEnergy, sBrain, sMoney;
    std::getline(in, sName);
    std::getline(in, sSpecialty);
    in >> sEnergy >> sBrain >> sMoney;

    student = Student(sName, sSpecialty);
    student.changeEnergy(sEnergy - student.getEnergy());
    student.changeBrainPower(sBrain - student.getBrainPower());
    student.changeMoney(sMoney - student.getMoney());

    size_t subjCount;
    in >> subjCount;
    in.ignore();
    student.getSubjects().clear();

    std::ifstream resFile("subjects.txt");

    for (size_t i = 0; i < subjCount; ++i) {

        std::string subjName;
        int att, know;
        std::getline(in, subjName);
        in >> att >> know;
        in.ignore();

        std::string resName, q, a1, a2;
        int correct = 1;

        if (resFile.is_open() && std::getline(resFile, resName)) {
            std::getline(resFile, q);
            std::getline(resFile, a1);
            std::getline(resFile, a2);
            resFile >> correct;
            resFile.ignore();
        }

        student.addSubject(Subject(subjName, att, know, q, a1, a2, correct));
    }
    if (resFile.is_open()) resFile.close();

    size_t deckSize;
    in >> deckSize;
    scheduleDeck.resize(deckSize);
    for (size_t i = 0; i < deckSize; ++i) { in >> scheduleDeck[i]; }

    in.close();
    return true;
}

void GameSettings::save() {
    std::ofstream saveFile("player_settings.txt");

    if (!saveFile.is_open()) {
        std::cout << "Ошибка! Не удалось сохранить данные игрока в player_settings.txt" << std::endl;
        system("pause");
        return;
    }

    saveFile << studentName << "\n";
    saveFile << studentSpecialty << "\n";
    saveFile << subjectsCount << "\n";
    saveFile << maxnumofsubj << "\n";

    saveFile.close();
}
