
#include <iostream>
#include <fstream>
#include <cstring>
#include <limits>
#include <iomanip>
#include <string>

using namespace std;

struct Car {
    char brand[30];   // Название книги
    char model[30];   // Автор книги
    int year;         // Год издания
    int price;        // Цена книги
    char body[20];    // Жанр книги
    char segment[10]; // Язык книги
};

void inputText(char field[], int size, const char message[]) {
    cout << message;
    cin.getline(field, size);

    // Повтор ввода при ошибке или пустой строке.
    while (cin.fail() || strlen(field) == 0) {
        if (cin.fail()) {
            cin.clear();
            cin.ignore(numeric_limits<streamsize>::max(), '\n');
            cout << "Text is too long. Try again: ";
        }
        else {
            cout << "Field cannot be empty. Try again: ";
        }

        cin.getline(field, size);
    }
}

void printHeader() {
    cout << left
        << setw(31) << "Title"
        << setw(31) << "Author"
        << setw(21) << "Genre"
        << setw(11) << "Language"
        << setw(8) << "Year"
        << setw(10) << "Price"
        << endl;

    cout << string(112, '-') << endl;
}

void printBook(const Car& book) {
    cout << left
        << setw(31) << book.brand
        << setw(31) << book.model
        << setw(21) << book.body
        << setw(11) << book.segment
        << setw(8) << book.year
        << setw(10) << book.price
        << endl;
}

void searchText(int fieldChoice, const char filename[]) {
    char searchText[30]; // Поисковая строка
    Car book;             // Текущая книга
    bool found = false;   // Найдена ли книга

    cin.ignore(numeric_limits<streamsize>::max(), '\n');

    cout << "Enter search text: ";
    cin.getline(searchText, 30);

    // Повтор ввода при ошибке или пустой строке.
    while (cin.fail() || strlen(searchText) == 0) {
        if (cin.fail()) {
            cin.clear();
            cin.ignore(numeric_limits<streamsize>::max(), '\n');
            cout << "Text is too long. Maximum 29 characters: ";
        }
        else {
            cout << "Search text cannot be empty: ";
        }

        cin.getline(searchText, 30);
    }

    ifstream file(filename, ios::binary); // Файл каталога

    if (!file) {
        cout << "File open error" << endl;
        return;
    }

    printHeader();

    // Чтение книг до конца файла.
    while (file.read(reinterpret_cast<char*>(&book), sizeof(Car))) {
        bool match = false; // Совпадает ли поле поиска

        if (fieldChoice == 1 &&
            strstr(book.brand, searchText) != nullptr) {
            match = true;
        }

        if (fieldChoice == 2 &&
            strstr(book.model, searchText) != nullptr) {
            match = true;
        }

        if (fieldChoice == 5 &&
            strstr(book.body, searchText) != nullptr) {
            match = true;
        }

        if (fieldChoice == 6 &&
            strstr(book.segment, searchText) != nullptr) {
            match = true;
        }

        if (match) {
            printBook(book);
            found = true;
        }
    }

    if (!found) {
        cout << "No books found." << endl;
    }

    file.close();
}

void searchRange(int fieldChoice, const char filename[]) {
    int minValue, maxValue; // Границы диапазона
    Car book;                // Текущая книга
    bool found = false;      // Найдена ли книга

    if (fieldChoice == 3) {
        cout << "From year: ";

        while (!(cin >> minValue) ||
            minValue < 1 || minValue > 2026) {
            cout << "Enter a year from 1 to 2026: ";
            cin.clear();
            cin.ignore(numeric_limits<streamsize>::max(), '\n');
        }

        cout << "To year: ";

        while (!(cin >> maxValue) ||
            maxValue < minValue || maxValue > 2026) {
            cout << "Enter a year from " << minValue
                << " to 2026: ";
            cin.clear();
            cin.ignore(numeric_limits<streamsize>::max(), '\n');
        }
    }
    else {
        cout << "From price: ";

        while (!(cin >> minValue) || minValue < 1) {
            cout << "Enter a positive price: ";
            cin.clear();
            cin.ignore(numeric_limits<streamsize>::max(), '\n');
        }

        cout << "To price: ";

        while (!(cin >> maxValue) || maxValue < minValue) {
            cout << "Enter a price greater than or equal to "
                << minValue << ": ";
            cin.clear();
            cin.ignore(numeric_limits<streamsize>::max(), '\n');
        }
    }

    ifstream file(filename, ios::binary); // Файл каталога

    if (!file) {
        cout << "File open error" << endl;
        return;
    }

    printHeader();

    // Чтение книг до конца файла.
    while (file.read(reinterpret_cast<char*>(&book), sizeof(Car))) {
        int value; // Год или цена книги

        if (fieldChoice == 3) {
            value = book.year;
        }
        else {
            value = book.price;
        }

        if (value >= minValue && value <= maxValue) {
            printBook(book);
            found = true;
        }
    }

    if (!found) {
        cout << "No books found." << endl;
    }

    file.close();
}

int main() {

    // ============================================================
 // GENERATE BOOKS — START
 // ОДНОРАЗОВЫЙ КОД: ЗАПУСТИ ОДИН РАЗ, ЗАТЕМ УДАЛИ ЭТОТ БЛОК
 // ============================================================

    Car sampleBooks[10] = {
        { "War and Peace", "Leo Tolstoy", 1869, 25, "Novel", "Russian" },
        { "Crime and Punishment", "Fyodor Dostoevsky", 1866, 20, "Novel", "Russian" },
        { "The Master and Margarita", "Mikhail Bulgakov", 1967, 22, "Fantasy", "Russian" },
        { "Dead Souls", "Nikolai Gogol", 1842, 15, "Satire", "Russian" },
        { "Eugene Onegin", "Alexander Pushkin", 1833, 18, "Poetry", "Russian" },
        { "Fathers and Sons", "Ivan Turgenev", 1862, 16, "Novel", "Russian" },
        { "The Cherry Orchard", "Anton Chekhov", 1904, 12, "Drama", "Russian" },
        { "Doctor Zhivago", "Boris Pasternak", 1957, 24, "Novel", "Russian" },
        { "The Idiot", "Fyodor Dostoevsky", 1869, 19, "Novel", "Russian" },
        { "Heart of a Dog", "Mikhail Bulgakov", 1925, 14, "Satire", "Russian" }
    };

    ofstream generateFile("books.dat", ios::binary | ios::trunc);

    if (!generateFile) {
        cout << "File creation error" << endl;
        return 1;
    }

    // Запись десяти книг в файл.
    for (int i = 0; i < 10; i++) {
        generateFile.write(
            reinterpret_cast<char*>(&sampleBooks[i]),
            sizeof(Car)
        );
    }

    generateFile.close();

    cout << "books.dat generated with 10 Russian books." << endl;

    // ============================================================
    // GENERATE BOOKS — END
    // УДАЛИ ВЕСЬ КОД ОТ START ДО END ВКЛЮЧИТЕЛЬНО
    // ============================================================
    Car car;      // Книга для добавления
    int choice;   // Пункт главного меню
    const char filename[] = "books.dat"; // Имя файла каталога

    do {
        cout << "\n===== BOOK CATALOG =====" << endl;
        cout << "1 - Add book" << endl;
        cout << "2 - Show all books" << endl;
        cout << "3 - Search books" << endl;
        cout << "0 - Exit" << endl;
        cout << "Your choice: ";

        // Проверка выбора пункта меню.
        while (!(cin >> choice) || choice < 0 || choice > 3) {
            cout << "Enter a number from 0 to 3: ";
            cin.clear();
            cin.ignore(numeric_limits<streamsize>::max(), '\n');
        }

        switch (choice) {
        case 1: {
            cin.ignore(numeric_limits<streamsize>::max(), '\n');

            inputText(car.brand, 30, "Book title: ");
            inputText(car.model, 30, "Author: ");

            cout << "Publication year: ";

            while (!(cin >> car.year) ||
                car.year < 1 || car.year > 2026) {
                cout << "Enter a year from 1 to 2026: ";
                cin.clear();
                cin.ignore(numeric_limits<streamsize>::max(), '\n');
            }

            cout << "Price: ";

            while (!(cin >> car.price) || car.price <= 0) {
                cout << "Enter a positive price: ";
                cin.clear();
                cin.ignore(numeric_limits<streamsize>::max(), '\n');
            }

            cin.ignore(numeric_limits<streamsize>::max(), '\n');

            inputText(car.body, 20, "Genre: ");
            inputText(car.segment, 10, "Language: ");

            ofstream file(filename, ios::binary | ios::app);

            if (!file) {
                cout << "File open error" << endl;
            }
            else {
                file.write(reinterpret_cast<char*>(&car), sizeof(Car));

                if (file) {
                    cout << "Book added successfully!" << endl;
                }
                else {
                    cout << "Error writing to file." << endl;
                }

                file.close();
            }

            break;
        }

        case 2: {
            ifstream file(filename, ios::binary); // Файл каталога

            if (!file) {
                cout << "File open error." << endl;
            }
            else {
                Car book;          // Текущая книга
                bool found = false; // Есть ли записи

                printHeader();

                // Вывод книг до конца файла.
                while (file.read(reinterpret_cast<char*>(&book), sizeof(Car))) {
                    printBook(book);
                    found = true;
                }

                if (!found) {
                    cout << "The catalog is empty." << endl;
                }

                file.close();
            }

            break;
        }

        case 3: {
            int searchChoice; // Выбранное поле поиска

            cout << "\n===== SEARCH BOOKS =====" << endl;
            cout << "1 - By title" << endl;
            cout << "2 - By author" << endl;
            cout << "3 - By publication year" << endl;
            cout << "4 - By price" << endl;
            cout << "5 - By genre" << endl;
            cout << "6 - By language" << endl;
            cout << "0 - Back" << endl;
            cout << "Your choice: ";

            // Проверка выбора поля поиска.
            while (!(cin >> searchChoice) ||
                searchChoice < 0 || searchChoice > 6) {
                cout << "Enter a number from 0 to 6: ";
                cin.clear();
                cin.ignore(numeric_limits<streamsize>::max(), '\n');
            }

            if (searchChoice == 1 ||
                searchChoice == 2 ||
                searchChoice == 5 ||
                searchChoice == 6) {
                searchText(searchChoice, filename);
            }
            else if (searchChoice == 3 || searchChoice == 4) {
                searchRange(searchChoice, filename);
            }

            break;
        }

        case 0:
            cout << "Exit" << endl;
            break;
        }

    } while (choice != 0); // Повтор меню до выхода

    return 0;
}
