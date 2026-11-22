#include "GameObjects.h"

//реализация методов класса предмет
Subject::Subject(std::string name, int att, int know, std::string q, std::string a1, std::string a2, int correct)
    : name(name), attendance(att), knowledge(know), questionText(q), ans1(a1), ans2(a2), correctAnswerNum(correct) {
}

Subject::Subject(std::string name, std::string q, std::string a1, std::string a2, int correct)
    : name(name), attendance(0), knowledge(0), questionText(q), ans1(a1), ans2(a2), correctAnswerNum(correct) {
}

std::string Subject::getName() const {
    return name;
}

int Subject::getAttendance() const {
    return attendance;
}

int Subject::getKnowledge() const {
    return knowledge;
}

std::string Subject::getQ() const {
    return questionText; 
}

std::string Subject::getAns1() const { 
    return ans1; 
}

std::string Subject::getAns2() const { 
    return ans2; 
}

char Subject::getCorrectNum() const {
    return correctAnswerNum; 
}

void Subject::visit() {
    attendance = std::min(100, attendance + 20);
}

void Subject::study(int basePoints, double specialtyMultiplier, int brainPower) {
    //десять очков интеллекта +10 процентов к эффективности учебы
    double brainMultiplier = 1.0 + (brainPower / 100.0);

    int totalGain = static_cast<int>(basePoints * specialtyMultiplier * brainMultiplier);

    //обновляем знания, но не даем им перешагнуть порог в 100%
    knowledge = std::min(100, knowledge + totalGain);

    std::cout << "  -> Знания по предмету \"" << name << "\" выросли на +" << totalGain << "%\n";
    std::cout << "     [Модификаторы]: Специальность: x" << specialtyMultiplier
        << " | Множитель интеллекта: x" << brainMultiplier << "\n";
    std::cout << "      Текущий уровень знаний по предмету: " << knowledge << "/100%\n";
}

//реализация методов класса студент
Student::Student(std::string name, std::string specialty)
    : name(name), specialty(specialty), energy(100), brainPower(10), money(0) {
}

void Student::addSubject(const Subject& subj) {
    subjects.push_back(subj);
}

std::vector<Subject>& Student::getSubjects() {
    return subjects;
}

size_t Student::getSubjectsCount() const {
    return subjects.size();
}

int Student::getEnergy() const {
    return energy;
}

void Student::changeEnergy(int val) {
    energy = std::max(0, std::min(100, energy + val));
}

int Student::getBrainPower() const {
    return brainPower;
}

void Student::changeBrainPower(int val) {
    brainPower = std::max(0, brainPower + val);
}

int Student::getMoney() const {
    return money;
}

void Student::changeMoney(int val) {
    money = std::max(0, money + val);
}

std::string Student::getName() const {
    return name; 
}

std::string Student::getSpecialty() const {
    return specialty; 
}

double Student::getSpecialtyMultiplier(const std::string& subjectName) const {
    if (specialty == "Информационные технологии" && subjectName == "КПО") return 1.5;
    if (specialty == "Компьютерная безопасность" && subjectName == "ОС") return 1.5;
    if (specialty == "Архитектура систем" && subjectName == "Конструирование БД") return 1.5;
    return 1.0; //для остальных скорость базовая
}

void Student::printStatus() const {
    std::cout << "\n================================================\n";
    std::cout << " СТУДЕНТ: " << name << " | СПЕЦИАЛЬНОСТЬ: " << specialty << "\n";
    std::cout << " Энергия: " << energy << "/100 | Интеллект (BrainPower): " << brainPower << " | Деньги: " << money << " руб.\n";
    std::cout << "------------------------------------------------\n";
    std::cout << " Текущая успеваемость по предметам:\n";
    for (const auto& subj : subjects) {
        std::cout << "  * " << subj.getName()
            << " -> Посещаемость: " << subj.getAttendance() << "%"
            << " | Знания: " << subj.getKnowledge() << "%\n";
    }
    std::cout << "================================================\n";
}