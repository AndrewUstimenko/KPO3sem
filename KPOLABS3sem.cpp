#include <iostream>
#include <vector>
#include <string>
#include <ctime>
#include <fstream>

#include "data.h"     
#include "start.h"    
#include "download.h" 
#include "settings.h" 
#include "version.h"
#include "init.h"
#include "Input.h"

int main()
{
    enum Menu {
        Start = 1,
        Download,
        Settings,
        Version,
        Exit
    };

    setlocale(LC_ALL, "Russian");
    srand(static_cast<unsigned int>(time(NULL)));

    GameSettings config;
    init(config);

    //объект сессии по умолчанию
    GameSession session;

    int choice = 0;
    while (choice != Exit) {
        system("cls");
        std::cout << "----Моя жизнь в университете----" << std::endl;
        std::cout << "1 - Начать игру" << std::endl;
        std::cout << "2 - Загрузить игру" << std::endl;
        std::cout << "3 - Настройки" << std::endl;
        std::cout << "4 - О программе" << std::endl;
        std::cout << "5 - Выход" << std::endl;
        std::cout << "--------------------------------" << std::endl;

        choice = safeInputInt();

        switch (choice) {
        case Start: {
            system("cls");
            std::string sessionName;
            std::cout << "=== НАЧАЛО НОВОЙ СЕССИИ ===" << std::endl;
            std::cout << "Введите имя файла сохранения (латиницей, без пробелов): ";
            std::cin >> sessionName;

            Student newStudent(config.studentName, config.studentSpecialty);

            std::ifstream subjectsFile("subjects.txt");
            if (!subjectsFile.is_open()) {
                std::cout << "Файл ресурсов 'subjects.txt' не найден!\n";
                system("pause");
                break;
            }

            std::string currentSubjectName;
            int loadedSubjectsCount = 0;

            //по блокам заполняем предметы
            std::string qText, a1, a2;
            int correctNum;

            while (std::getline(subjectsFile, currentSubjectName)) {
                if (currentSubjectName.empty()) continue;

                std::getline(subjectsFile, qText);
                std::getline(subjectsFile, a1);
                std::getline(subjectsFile, a2);
                subjectsFile >> correctNum;
                subjectsFile.ignore(); //очистка буфера после ввода числа

                //создание предмета через конструктор
                newStudent.addSubject(Subject(currentSubjectName, qText, a1, a2, correctNum));
                loadedSubjectsCount++;

                if (loadedSubjectsCount == config.subjectsCount) {
                    break;
                }
            }
            subjectsFile.close();

            //если предметов в файле меньше
            if (loadedSubjectsCount < config.subjectsCount) {
                std::cout << "Файл ресурсов 'subjects.txt' содержит недостаточно предметов!\n";
                system("pause");
                break;
            }

            //колода расписания
            size_t actualCount = newStudent.getSubjectsCount();
            if (actualCount == 0) {
                std::cout << "Ошибка! 0 предметов" << std::endl;
                system("pause");
                break;
            }

            std::vector<int> initialDeck;
            const int lessonsPerSubject = 5; //5 пар за семестр

            for (int i = 0; i < static_cast<int>(actualCount); ++i) {
                for (int j = 0; j < lessonsPerSubject; ++j) {
                    initialDeck.push_back(i);
                }
            }

            //перемешиваем колоду для случайного расписания
            if (!initialDeck.empty()) {
                for (size_t i = initialDeck.size() - 1; i > 0; --i) {
                    size_t j = rand() % (i + 1);
                    std::swap(initialDeck[i], initialDeck[j]);
                }
            }

            //инициаизация сесии создаными данными
            session = GameSession(newStudent, initialDeck);
            session.setSessionName(sessionName);

            std::cout << "\nСессия \"" << sessionName << "\" успешно создана!\n";
            system("pause");

            //запуск самой игровой функции
            startGame(session);
            break;
        }
        case Download: {
            //передаем в функцию загрузки
            bool isLoaded = download(session);
            if (isLoaded) {
                startGame(session);
            }
            break;
        }
        case Settings:
            settings(config);
            break;

        case Version:
            version();
            break;

        case Exit:
            break;

        default:
            std::cout << "Неверный пункт меню! Попробуйте еще раз." << std::endl;
            system("pause");
            break;
        }
    }
    return 0;
}
