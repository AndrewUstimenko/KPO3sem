#include "Input.h"

int safeInputInt() {
    int value;
    while (!(std::cin >> value)) {
        std::cout << "Ошибка! Введите целое число: ";
        std::cin.clear();
        std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
    }
    std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
    return value;
}
