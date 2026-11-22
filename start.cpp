#include "start.h"
#include <vector>
#include <string>
#include <conio.h>
#include <filesystem>

#include "settings.h"


int runScrollMenu(const std::string& title, const std::vector<std::string>& options) {
    int cursor = 0;
    while (true) {
        system("cls");

        std::cout << title << "\n";
        std::cout << "================================================\n";
        for (size_t i = 0; i < options.size(); ++i) {
            if (i == cursor) {
                std::cout << " -> [ " << options[i] << " ]\n";
            }
            else {
                std::cout << "    " << options[i] << "\n";
            }
        }
        std::cout << "================================================\n";
        std::cout << "(W/S — перемещение, Enter — выбор)\n";

        int key = _getch();
        if (key == 'w' || key == 'W') {
            if (cursor > 0) cursor--;
            else cursor = options.size() - 1;
        }
        else if (key == 's' || key == 'S') {
            if (cursor < options.size() - 1) cursor++;
            else cursor = 0;
        }
        else if (key == 13) {
            return cursor;
        }
    }
}

void runMidtermAttestation(Student& student) {
    system("cls");
    std::cout << "   РУБЕЖНАЯ АТТЕСТАЦИЯ (СЕРЕДИНА СЕМЕСТРА)!\n";

    int totalAttestationScore = 0;

    for (const auto& subj : student.getSubjects()) {
        //в середине семестра максимум знаний/посещаемости около 40-50%, поэтому умножаем на 0.12
        int rawScore = static_cast<int>((subj.getAttendance() + subj.getKnowledge()) * 0.12) + (student.getBrainPower() / 15);
        int mark = std::min(10, std::max(1, rawScore)); //оценка от 1 до 10

        std::cout << "  * " << subj.getName() << " -> Оценка за аттестацию: " << mark << "/10\n";
        totalAttestationScore += mark;
    }

    double avgMark = static_cast<double>(totalAttestationScore) / student.getSubjectsCount();
    std::cout << "\n------------------------------------------------\n";
    std::cout << "Средний балл по итогам аттестации: " << avgMark << " из 10\n\n";

    int stipend = 0;
    if (avgMark < 4.0) {
        stipend = 0;
        std::cout << "Лишение стипендии!!!" << stipend << " руб.\n";
    }
    else if (avgMark < 8.0) {
        stipend = 150;
        std::cout << "Хорошие результаты! Начислена стандартная стипендия: +" << stipend << " руб.\n";
    }
    else {
        stipend = 300;
        std::cout << "Отличная успеваемость! Начислена повышенная стипендия: +" << stipend << " руб.\n";
    }

    student.changeMoney(stipend);
    std::cout << "Текущий баланс: " << student.getMoney() << " руб.\n";
    std::cout << "================================================\n";
    system("pause");
}

//сессиия (в плане экзамен)
void runSession(Student& student) {
    system("cls");
    std::cout << "НАЧАЛАСЬ СЕССИЯ! СДАЧА ЭКЗАМЕНОВ\n\n";
    system("pause");

    int totalScore = 0;

    for (auto& subj : student.getSubjects()) {
        system("cls");
        std::cout << "== Экзамен по предмету: " << subj.getName() << " ==\n";

        double baseMark = (subj.getAttendance() * 0.04) + (subj.getKnowledge() * 0.04);
        int finalMark = static_cast<int>(baseMark);
        if (finalMark < 1) finalMark = 1;
        if (finalMark > 8) finalMark = 8;

        std::cout << "Ваша успеваемость за семестр даёт вам: " << finalMark << " баллов.\n\n";
        std::cout << "Дополнительный вопрос от профессора:\n";

        std::vector<std::string> options = { subj.getAns1(), subj.getAns2() };

        int choiceIndex = runScrollMenu(subj.getQ(), options);

        system("cls");
        if ((choiceIndex + 1) == subj.getCorrectNum()) {
            finalMark = std::min(10, finalMark + 2);
            std::cout << "Правильно! Преподаватель хвалит вас за глубокие знания.\n";
        }
        else {
            finalMark = std::max(1, finalMark - 1);
            std::cout << "Неверно. Преподаватель разочарован вашим ответом.\n";
        }

        std::cout << "Итоговая оценка по предмету \"" << subj.getName() << "\": " << finalMark << " из 10\n\n";
        totalScore += finalMark;
        system("pause");
    }

    system("cls");
    std::cout << "=== ИТОГИ СЕССИИ ===\n";
    double average = static_cast<double>(totalScore) / student.getSubjectsCount();
    std::cout << "Ваш средний балл: " << average << " из 10\n";

    if (average >= 4.0) {
        std::cout << " Вы успешно сдали сессию! \n";
    }
    else {
        std::cout << " Вы отчислены за неуспеваемость. \n";
    }
    system("pause");
}

void startGame(GameSession& session) {

    //главнй цикл семестра
    while (!session.isDeckEmpty()) {

        //автосохранение в начале каждого дня
        std::string saveFileName = session.getSessionName() + ".s";
        bool saveSuccess = session.saveGame(saveFileName);

        system("cls");
        if (saveSuccess) {
            std::cout << "[Автосохранение]: Прогресс успешно перезаписан в \"" << saveFileName << "\"\n";
        }
        else {
            std::cout << "Не удалось выполнить автосохранение!\n";
        }
        system("pause");
        system("cls");

        int total = session.getTotalLessons();
        size_t currentSize = session.getDeckSize();

        if (currentSize <= total / 2 && currentSize > total / 4 + 2) {
            std::cout << "Половина семестра позади!\n";
            system("pause");

            if (!session.isMidtermPassed()) {
                runMidtermAttestation(session.getStudent());
                session.setMidtermPassed(true);
            }
        }
        else if (currentSize <= 3) {
            std::cout << "Сессия на носу!\n";
            system("pause");
        }

        //количество предметов сегодня
        int lessonsToday = rand() % 3 + 1;
        if (lessonsToday > currentSize) {
            lessonsToday = currentSize;
        }

        //дневная часть университета
        for (int l = 0; l < lessonsToday; ++l) {
            int currentSubjIndex = session.popLesson();
            if (currentSubjIndex == -1) break;

            if (currentSubjIndex < 0 || currentSubjIndex >= static_cast<int>(session.getStudent().getSubjects().size())) {
                std::cout << "Беда!!!Индекс предмета вышел за границы вектора.\n";
                system("pause");
                continue;
            }

            Subject& currentSubject = session.getStudent().getSubjects()[currentSubjIndex];

            std::string dayTitle = "--- ДЕНЬ " + std::to_string(session.getCurrentDay()) + " | ПАРА " + std::to_string(l + 1) + " из " + std::to_string(lessonsToday) + " ---\n";
            dayTitle += "Дисциплина: " + currentSubject.getName() + "\n";
            dayTitle += "Энергия студента: " + std::to_string(session.getStudent().getEnergy()) + "/100\n\n";
            dayTitle += "Ваш выбор:";

            std::vector<std::string> dayOptions = {
                "Посетить пару (-15 энергии)",
                "Прогулять пару"
            };

            int dayChoice = runScrollMenu(dayTitle, dayOptions);

            system("cls");
            if (dayChoice == 0) {
                if (session.getStudent().getEnergy() >= 15) {
                    currentSubject.visit();
                    session.getStudent().changeEnergy(-15);

                    std::cout << "Вы посетили пару по предмету \"" << currentSubject.getName() << "\".\n";
                    double specMult = session.getStudent().getSpecialtyMultiplier(currentSubject.getName());
                    currentSubject.study(6, specMult, session.getStudent().getBrainPower());
                }
                else {
                    std::cout << "Нет энергии. Вы прогуляли пару по \"" << currentSubject.getName() << "\".\n";
                }
            }
            else {
                std::cout << "Вы прогуляли пару по предмету \"" << currentSubject.getName() << "\".\n";
            }
            system("pause");
        }

        //фаза два. Вечер. Выбор действия
        std::vector<Action> homeActions = {
            {"Лечь пораньше поспать (Восстановить +60 энергии)", ActionType::Rest, -60, 0},
            {"Порешать олимпиадные задачки (-10 энергии, +15 к Интеллекту)", ActionType::BrainStorm, 10, 15},
            {"Позубрить конспекты по конкретному предмету (-10 энергии)", ActionType::StudySubject, 10, 0},
            {"Сходить в кофейню и вкусно поесть (-40 руб., +100 энергии)", ActionType::SpendMoney, -100, 0}
        };

        std::vector<std::string> homeMenuText;
        for (const auto& act : homeActions) {
            homeMenuText.push_back(act.description);
        }

        system("cls");
        session.getStudent().printStatus();
        std::cout << "\nВы вернулись домой.\n";
        system("pause");

        int eveningChoice = runScrollMenu("ЧЕМ ЗАНЯТЬСЯ ВЕЧЕРОМ ДОМА?", homeMenuText);
        Action selectedAction = homeActions[eveningChoice];

        system("cls");
        if (selectedAction.type == ActionType::Rest) {
            session.getStudent().changeEnergy(-selectedAction.energyCost);
            std::cout << "Вы отлично выспались!\n";
            system("pause");
        }
        else if (selectedAction.type == ActionType::BrainStorm) {
            if (session.getStudent().getEnergy() >= selectedAction.energyCost) {
                session.getStudent().changeEnergy(-selectedAction.energyCost);
                session.getStudent().changeBrainPower(selectedAction.brainGain);
                std::cout << "Интеллект вырос на " << selectedAction.brainGain <<" %\n";
            }
            else {
                std::cout << "Вы слишком устали. Пришлось просто лечь спать.\n";
                session.getStudent().changeEnergy(60);
            }
            system("pause");
        }
        else if (selectedAction.type == ActionType::StudySubject) {
            if (session.getStudent().getEnergy() >= selectedAction.energyCost) {
                std::vector<std::string> subjectMenuText;
                for (const auto& sub : session.getStudent().getSubjects()) {
                    subjectMenuText.push_back(sub.getName() + " (Знания: " + std::to_string(sub.getKnowledge()) + "%)");
                }

                int chosenSubjIndex = runScrollMenu("КАКОЙ ПРЕДМЕТ БУДЕМ ЗУБРИТЬ ДОМА?", subjectMenuText);
                session.getStudent().changeEnergy(-selectedAction.energyCost);

                system("cls");
                Subject& targetSubject = session.getStudent().getSubjects()[chosenSubjIndex];
                double specMult = session.getStudent().getSpecialtyMultiplier(targetSubject.getName());

                std::cout << "Вы учите предмет \"" << targetSubject.getName() << "\".\n";
                targetSubject.study(12, specMult, session.getStudent().getBrainPower());
            }
            else {
                std::cout << "Нет сил. Вы мгновенно уснули.\n";
                session.getStudent().changeEnergy(60);
            }
            system("pause");
        }
        else if (selectedAction.type == ActionType::SpendMoney) {
            const int coffeeCost = 40;
            if (session.getStudent().getMoney() >= coffeeCost) {
                session.getStudent().changeMoney(-coffeeCost);
                session.getStudent().changeEnergy(-selectedAction.energyCost);
                std::cout << "Вы вкусно покушали. Энергия восстановлена. Осталось  " << session.getStudent().getMoney() << " руб.\n"; 
            }                                         
            else {                                              
                std::cout << "Недостаточно денег (нужно " << coffeeCost << " руб.)! Пришлось просто лечь спать.\n";
                session.getStudent().changeEnergy(60);
            }
            system("pause");
        }

        // следующий день
        session.incrementDay();
    }

    //фаза 3 сессия
    runSession(session.getStudent());

    std::string saveFileName = session.getSessionName() + ".s";

    //стандартная функция удаления файла
    std::filesystem::remove(saveFileName.c_str());
    std::cout << "\nИгровая сессия \"" << saveFileName << "\" успешно завершена\n";

    system("pause");
}