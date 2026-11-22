#include "init.h"

void createResourceFilesIfMissing() {

    std::ifstream checkNames("names.txt");
    if (!checkNames.is_open()) {
        std::ofstream outNames("names.txt");
        if (outNames.is_open()) {
            outNames << "Александр\nДмитрий\nЕлена\nМаксим\nСветлана\n";
            outNames.close();
        }
    }
    else {
        checkNames.close();
    }

    std::ifstream checkSpecs("specialties.txt");
    if (!checkSpecs.is_open()) {
        std::ofstream outSpecs("specialties.txt");
        if (outSpecs.is_open()) {
            outSpecs << "Компьютерная безопасность\nИнформационные технологии\nАрхитектура систем\n";
            outSpecs.close();
        }
    }
    else {
        checkSpecs.close();
    }
}


void init(GameSettings& settings) {
    
    createResourceFilesIfMissing();

    settings.allStudentNames.clear();
    settings.allSpecialties.clear();

    std::ifstream namesFile("names.txt");
    if (namesFile.is_open()) {
        std::string name;
        while (std::getline(namesFile, name)) {
            if (!name.empty()) {
                settings.allStudentNames.push_back(name);
            }
        }
        namesFile.close();
    }

    std::ifstream specsFile("specialties.txt");
    if (specsFile.is_open()) {
        std::string spec;
        while (std::getline(specsFile, spec)) {
            if (!spec.empty()) {
                settings.allSpecialties.insert(spec);
            }
        }
        specsFile.close();
    }

    //дефолтные значения
    settings.studentName = "Алекснадр";
    settings.studentSpecialty = "Компьютерная безопасность";
    settings.subjectsCount = 5;
    settings.maxnumofsubj = 8;

    //загрузка из файла сохранения
    std::ifstream saveFile("player_settings.txt");
    if (saveFile.is_open()) {
        std::getline(saveFile, settings.studentName);
        std::getline(saveFile, settings.studentSpecialty);
        saveFile >> settings.subjectsCount;
        saveFile >> settings.maxnumofsubj;
        saveFile.close();
    }
}