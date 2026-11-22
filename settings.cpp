#include "settings.h"
#include <conio.h>
#include "Input.h"

void settings(GameSettings& settings) {

    enum MenuOption {
        OptionName = 1,
        OptionSpecialty,
        OptionSubjects,
        OptionBack
    };

    for (;;) {
        system("cls");
        std::cout << "----НАСТРОЙКИ----" << std::endl;
        std::cout << "1 - Выбрать имя студента (Текущее: " << (settings.studentName.empty() ? "Не выбрано" : settings.studentName) << ")" << std::endl;
        std::cout << "2 - Выбрать специальность (Текущая: " << (settings.studentSpecialty.empty() ? "Не выбрана" : settings.studentSpecialty) << ")" << std::endl;
        std::cout << "3 - Задать количество предметов (Текущее: " << settings.subjectsCount << ")" << std::endl;
        std::cout << "4 - Назад" << std::endl;
        std::cout << "-----------------------------" << std::endl;

        int choice = safeInputInt();

        switch (choice) {
        case OptionName: {
            if (settings.allStudentNames.empty()) {
                system("cls");
                std::cout << "Список имен пуст!" << std::endl;
                system("pause");
                break;
            }

            std::list<std::string>::const_iterator it = settings.allStudentNames.begin();

            if (!settings.studentName.empty()) {
                std::list<std::string>::const_iterator findIt;
                for (findIt = settings.allStudentNames.begin(); findIt != settings.allStudentNames.end(); ++findIt) {
                    if (*findIt == settings.studentName) {
                        it = findIt;
                        break;
                    }
                }

                //если текущего имени нет в файле конфигов
                if (findIt == settings.allStudentNames.end()) {
                    it = settings.allStudentNames.begin();
                }
            }

            for (;;) {
                system("cls");
                std::cout << "--- Выбор имени студента [W - Вверх, S - Вниз, Enter - Подтвердить] ---" << std::endl;

                std::cout << "Текущий выбор: >> " << *it << " <<" << std::endl;
                std::cout << "----------------------------------------------------------------" << std::endl;

                char ch = _getch();

                if (ch == 'w' || ch == 'W' || ch == 'ц' || ch == 'Ц') {
                    if (it == settings.allStudentNames.begin()) {
                        it = settings.allStudentNames.end();
                    }
                    --it;
                }
                else if (ch == 's' || ch == 'S' || ch == 'ы' || ch == 'Ы') {
                    ++it;
                    if (it == settings.allStudentNames.end()) {
                        it = settings.allStudentNames.begin();
                    }
                }
                else if (ch == 13) {
                    settings.studentName = *it;

                    std::cout << "\nИмя успешно сохранено: " << settings.studentName << std::endl;
                    system("pause");
                    break;
                }
            }
            break;
        }

        case OptionSpecialty: {
            if (settings.allSpecialties.empty()) {
                system("cls");
                std::cout << "Список специальностей пуст!" << std::endl;
                system("pause");
                break;
            }

            std::set<std::string>::const_iterator it = settings.allSpecialties.begin();

            if (!settings.studentSpecialty.empty()) {
                std::set<std::string>::const_iterator findIt;
                for (findIt = settings.allSpecialties.begin(); findIt != settings.allSpecialties.end(); ++findIt) {
                    if (*findIt == settings.studentSpecialty) {
                        it = findIt;
                        break;
                    }
                }

                //если текущей специальности нет в файле конфигов
                if (findIt == settings.allSpecialties.end()) {
                    it = settings.allSpecialties.begin();
                }
            }

            for (;;) {
                system("cls");
                std::cout << "--- Выбор специальности [W - Вверх, S - Вниз, Enter - Подтвердить] ---" << std::endl;

                std::cout << "Текущий выбор: >> " << *it << " <<" << std::endl;
                std::cout << "-----------------------------------------------------------------" << std::endl;

                char ch = _getch();

                if (ch == 'w' || ch == 'W' || ch == 'ц' || ch == 'Ц') {
                    if (it == settings.allSpecialties.begin()) {
                        it = settings.allSpecialties.end();
                    }
                    
                    --it;
                }
                else if (ch == 's' || ch == 'S' || ch == 'ы' || ch == 'Ы') {
                    ++it;
                    if (it == settings.allSpecialties.end()) {
                        it = settings.allSpecialties.begin();
                    }
                }
                else if (ch == 13) {
                    settings.studentSpecialty = *it;

                    std::cout << "\nСпециальность успешно сохранена: " << settings.studentSpecialty << std::endl;
                    system("pause");
                    break;
                }
            }
            break;
        }

        case OptionSubjects: {
            system("cls");
            std::cout << "--- Настройка количества предметов ---" << std::endl;
            std::cout << "Введите количество предметов (максимум " << settings.maxnumofsubj << " ):";
            int count = safeInputInt();

            if (std::cin.fail() || count < 0  || count > settings.maxnumofsubj) {
                std::cout << "Ошибка! Введено некорректное число." << std::endl;
                std::cin.clear();
                std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
            }
            else {
                settings.subjectsCount = count;
                std::cout << "Количество предметов сохранено!" << std::endl;
            }
            system("pause");
            break;
        }
        case OptionBack: {
            settings.save();
            return;
        }
            return;

        default:
            std::cout << "Неверный пункт меню! Попробуйте еще раз." << std::endl;
            system("pause");
            break;
        }
    }
}

