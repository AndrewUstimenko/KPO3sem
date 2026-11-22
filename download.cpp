#include "download.h"
#include "start.h"
#include <iostream>
#include <vector>
#include <string>
#include <filesystem>

std::vector<std::string> getSaveFilesList() {
    std::vector<std::string> saves;

    //перебираем файлы в текущей папке
    for (const std::filesystem::directory_entry& entry : std::filesystem::directory_iterator(".")) {
        //проверяем файл ли это сохранения
        if (entry.is_regular_file() && entry.path().extension() == ".s") {
            saves.push_back(entry.path().filename().string());
        }
    }

    return saves;
}

bool download(GameSession& session) {

    std::vector<std::string> saves = getSaveFilesList();

    if (saves.empty()) {
        system("cls");
        std::cout << "================================================\n";
        std::cout << "Файлов сохранений (*.s) не обнаружено!\n";
        std::cout << "================================================\n";
        system("pause");
        return false;
    }

    saves.push_back("Назад в главное меню");

    int saveChoice = runScrollMenu("ВЫБЕРИТЕ СОХРАНЕНИЕ ДЛЯ ЗАГРУЗКИ PROGRESS:", saves);

    if (saveChoice == static_cast<int>(saves.size() - 1)) {
        return false;
    }

    std::string selectedSaveFile = saves[saveChoice];

    system("cls");
    std::cout << "Чтение файла сохранения " << selectedSaveFile << "...\n";

    //загружаем сессию
    if (session.loadGame(selectedSaveFile)) {
        std::cout << "Прогресс успешно восстановлен!\n";
        std::cout << "Игрок: " << session.getStudent().getName() << " | День: " << session.getCurrentDay() << "\n";
        system("pause");
        return true;
    }
    else {
        std::cout << "Ошибка: не удалось загрузить файл сохранения\n";
        system("pause");
        return false;
    }
}
