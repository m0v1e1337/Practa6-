#include <iostream>
#include <vector>
#include <cstdlib>
#include <ctime>
#include <string>
#include <limits>

using namespace std;

// Класс для представления персонажа
class Character {
public:
    string name;
    int rarity;
    int id;

    Character(string n, int r, int i) : name(n), rarity(r), id(i) {}
};

// Класс для представления инвентаря игрока
class Inventory {
public:
    int primogems;
    int genesis_crystals;
    int mora;
    vector<Character> characters;

    Inventory() : primogems(2000000), genesis_crystals(0), mora(0) {}

    void addCharacter(Character c) {
        characters.push_back(c);
    }

    void removeCharacter(int index) {
        characters.erase(characters.begin() + index);
    }

    void displayCharacters() {
        cout << "Персонажи в инвентаре:" << endl;
        for (int i = 0; i < characters.size(); i++) {
            cout << i + 1 << ". " << characters[i].name << " (Редкость: " << characters[i].rarity << ", ID: " << characters[i].id << ")" << endl;
        }
    }
};

// Класс для представления магазина
class Shop {
public:
    void buyPrimogems(Inventory& inventory, int amount) {
        if (inventory.mora >= amount * 100) {
            inventory.primogems += amount;
            inventory.mora -= amount * 100;
            cout << "Вы успешно купили " << amount << " примогемов." << endl;
        }
        else {
            cout << "Недостаточно мора для покупки." << endl;
        }
    }

    void buyGenesisCrystals(Inventory& inventory, int amount) {
        if (inventory.mora >= amount * 1000) {
            inventory.genesis_crystals += amount;
            inventory.mora -= amount * 1000;
            cout << "Вы успешно купили " << amount << " камней истока." << endl;
        }
        else {
            cout << "Недостаточно мора для покупки." << endl;
        }
    }

    void sellItems(Inventory& inventory, int amount) {
        if (amount <= inventory.mora) {
            inventory.mora += amount;
            cout << "Вы успешно продали личные вещи и получили " << amount << " мора." << endl;
        }
        else {
            cout << "Недостаточно мора для продажи." << endl;
        }
    }
};

// Функция для выпадения персонажа
void drawCharacter(Inventory& inventory, vector<Character>& characterPool, int& character_id) {
    if (characterPool.empty()) {
        cout << "Пул персонажей пуст." << endl;
        return;
    }

    int randomIndex = rand() % characterPool.size();
    Character drawnCharacter = characterPool[randomIndex];
    drawnCharacter.id = character_id++;
    inventory.addCharacter(drawnCharacter);
    cout << "Вы получили персонажа: " << drawnCharacter.name << " (Редкость: " << drawnCharacter.rarity << ", ID: " << drawnCharacter.id << ")" << endl;
}

// Функция для крутки за примогемы
void wishWithPrimogems(Inventory& inventory, vector<Character>& characterPool, int& character_id) {
    int amount;
    cout << "Введите количество примогемов для крутки: ";
    cin >> amount;
    if (cin.fail() || amount <= 0) {
        cout << "Неверный ввод. Попробуйте снова." << endl;
        cin.clear();
        cin.ignore(numeric_limits<streamsize>::max(), '\n');
        return;
    }
    if (inventory.primogems >= amount) {
        inventory.primogems -= amount;
        cout << "Вы потратили " << amount << " примогемов на крутку." << endl;
        drawCharacter(inventory, characterPool, character_id);
    }
    else {
        cout << "Недостаточно примогемов для крутки." << endl;
    }
}

// Функция для крутки за камни истока
void wishWithGenesisCrystals(Inventory& inventory, vector<Character>& characterPool, int& character_id) {
    int amount;
    cout << "Введите количество камней истока для крутки: ";
    cin >> amount;
    if (cin.fail() || amount <= 0) {
        cout << "Неверный ввод. Попробуйте снова." << endl;
        cin.clear();
        cin.ignore(numeric_limits<streamsize>::max(), '\n');
        return;
    }
    if (inventory.genesis_crystals >= amount) {
        inventory.genesis_crystals -= amount;
        cout << "Вы потратили " << amount << " камней истока на крутку." << endl;
        drawCharacter(inventory, characterPool, character_id);
    }
    else {
        cout << "Недостаточно камней истока для крутки." << endl;
    }
}

int main() {

    srand(time(NULL)); // Инициализация генератора случайных чисел

    // Создание пула персонажей
    vector<Character> characterPool = {
            Character("Дилюк", 5, 0),
            Character("Чичи", 5, 1),
            Character("Мона", 5, 2),
            Character("Ке Цин", 5, 3),
            Character("Сахароза", 4, 5),
            Character("Рейзор", 4, 6),
            Character("Ноэль", 4, 7),
            Character("Кейа", 4, 8),
            Character("Лиза", 4, 9)
    };

    Inventory playerInventory;
    Shop shop;
    int character_id = 1;

    int choice;
    do {
        cout << "Текущие ресурсы:" << endl;
        cout << "Примогемы: " << playerInventory.primogems << endl;
        cout << "Камни истока: " << playerInventory.genesis_crystals << endl;
        cout << "Мора: " << playerInventory.mora << endl;
        cout << endl;
        cout << "Выберите действие:" << endl;
        cout << "1. Купить примогемы" << endl;
        cout << "2. Купить камни истока" << endl;
        cout << "3. Продать личные вещи" << endl;
        cout << "4. Крутка за примогемы" << endl;
        cout << "5. Крутка за камни истока" << endl;
        cout << "6. Просмотреть персонажей" << endl;
        cout << "7. Удалить персонажа" << endl;
        cout << "0. Выход" << endl;
        cout << "Ваш выбор: ";
        cin >> choice;

        if (cin.fail() || choice < 0 || choice > 7) {
            cout << "Неверный ввод. Попробуйте снова." << endl;
            cin.clear();
            cin.ignore(numeric_limits<streamsize>::max(), '\n');
            continue;
        }

        switch (choice) {
        case 1:
            int primogems;
            cout << "Введите количество примогемов для покупки: ";
            cin >> primogems;
            if (cin.fail() || primogems <= 0) {
                cout << "Неверный ввод. Попробуйте снова." << endl;
                cin.clear();
                cin.ignore(numeric_limits<streamsize>::max(), '\n');
                break;
            }
            shop.buyPrimogems(playerInventory, primogems);
            break;
        case 2:
            int crystals;
            cout << "Введите количество камней истока для покупки: ";
            cin >> crystals;
            if (cin.fail() || crystals <= 0) {
                cout << "Неверный ввод. Попробуйте снова." << endl;
                cin.clear();
                cin.ignore(numeric_limits<streamsize>::max(), '\n');
                break;
            }
            shop.buyGenesisCrystals(playerInventory, crystals);
            break;
        case 3:
            int mora;
            cout << "Введите количество мора, полученное от продажи личных вещей: ";
            cin >> mora;
            if (cin.fail() || mora <= 0) {
                cout << "Неверный ввод. Попробуйте снова." << endl;
                cin.clear();
                cin.ignore(numeric_limits<streamsize>::max(), '\n');
                break;
            }
            shop.sellItems(playerInventory, mora);
            break;
        case 4:
            wishWithPrimogems(playerInventory, characterPool, character_id);
            break;
        case 5:
            wishWithGenesisCrystals(playerInventory, characterPool, character_id);
            break;
        case 6:
            playerInventory.displayCharacters();
            break;
        case 7:
            int index;
            cout << "Введите индекс персонажа для удаления: ";
            cin >> index;
            if (cin.fail() || index <= 0 || index > playerInventory.characters.size()) {
                cout << "Неверный ввод. Попробуйте снова." << endl;
                cin.clear();
                cin.ignore(numeric_limits<streamsize>::max(), '\n');
                break;
            }
            playerInventory.removeCharacter(index - 1);
            cout << "Персонаж успешно удален." << endl;
            break;
        case 0:
            cout << "Выход из программы." << endl;
            break;
        }
        cout << endl;
    } while (choice != 0);

    return 0;
}
