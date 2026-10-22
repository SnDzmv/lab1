
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

void printBook(const Car* book) {
    cout << left
         << setw(31) << book->brand
         << setw(31) << book->model
         << setw(21) << book->body
         << setw(11) << book->segment
         << setw(8) << book->year
         << setw(10) << book->price
         << endl;
}

void searchText(int fieldChoice, const char filename[]) {
    char searchText[30]; // Поисковая строка
    Car* book = new Car; // Динамическая запись книги
    bool found = false;  // Найдена ли книга

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

    ifstream file(filename, ios::binary);

    if (!file) {
        cout << "File open error" << endl;
        delete book;
        return;
    }

    printHeader();

    // Чтение записей до конца файла.
    while (file.read(reinterpret_cast<char*>(book), sizeof(Car))) {
        bool match = false; // Совпадение с запросом

        if (fieldChoice == 1 &&
            strstr(book->brand, searchText) != nullptr) {
            match = true;
        }

        if (fieldChoice == 2 &&
            strstr(book->model, searchText) != nullptr) {
            match = true;
        }

        if (fieldChoice == 5 &&
            strstr(book->body, searchText) != nullptr) {
            match = true;
        }

        if (fieldChoice == 6 &&
            strstr(book->segment, searchText) != nullptr) {
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
    delete book;
}

void searchRange(int fieldChoice, const char filename[]) {
    int minValue, maxValue; // Границы поиска
    Car* book = new Car;    // Динамическая запись книги
    bool found = false;     // Найдена ли книга

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

    ifstream file(filename, ios::binary);

    if (!file) {
        cout << "File open error" << endl;
        delete book;
        return;
    }

    printHeader();

    // Чтение записей до конца файла.
    while (file.read(reinterpret_cast<char*>(book), sizeof(Car))) {
        int value; // Год или цена

        if (fieldChoice == 3) {
            value = book->year;
        }
        else {
            value = book->price;
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
    delete book;
}

int main() {
    const char filename[] = "books.dat"; // Файл каталога

    // ============================================================
    // GENERATE BOOKS — START
    // ОДНОРАЗОВЫЙ БЛОК: СОЗДАЁТ ФАЙЛ, ЕСЛИ ЕГО ЕЩЁ НЕТ
    // После создания books.dat этот блок можно удалить.
    // ============================================================

    ifstream checkFile(filename);

    if (!checkFile) {
        Car* sampleBooks = new Car[10]; // Динамический массив книг

        strcpy_s(sampleBooks[0].brand, "War and Peace");
        strcpy_s(sampleBooks[0].model, "Leo Tolstoy");
        sampleBooks[0].year = 1869;
        sampleBooks[0].price = 25;
        strcpy_s(sampleBooks[0].body, "Novel");
        strcpy_s(sampleBooks[0].segment, "Russian");

        strcpy_s(sampleBooks[1].brand, "Crime and Punishment");
        strcpy_s(sampleBooks[1].model, "Fyodor Dostoevsky");
        sampleBooks[1].year = 1866;
        sampleBooks[1].price = 20;
        strcpy_s(sampleBooks[1].body, "Novel");
        strcpy_s(sampleBooks[1].segment, "Russian");

        strcpy_s(sampleBooks[2].brand, "The Master and Margarita");
        strcpy_s(sampleBooks[2].model, "Mikhail Bulgakov");
        sampleBooks[2].year = 1967;
        sampleBooks[2].price = 22;
        strcpy_s(sampleBooks[2].body, "Fantasy");
        strcpy_s(sampleBooks[2].segment, "Russian");

        strcpy_s(sampleBooks[3].brand, "Dead Souls");
        strcpy_s(sampleBooks[3].model, "Nikolai Gogol");
        sampleBooks[3].year = 1842;
        sampleBooks[3].price = 15;
        strcpy_s(sampleBooks[3].body, "Satire");
        strcpy_s(sampleBooks[3].segment, "Russian");

        strcpy_s(sampleBooks[4].brand, "Eugene Onegin");
        strcpy_s(sampleBooks[4].model, "Alexander Pushkin");
        sampleBooks[4].year = 1833;
        sampleBooks[4].price = 18;
        strcpy_s(sampleBooks[4].body, "Poetry");
        strcpy_s(sampleBooks[4].segment, "Russian");

        strcpy_s(sampleBooks[5].brand, "Fathers and Sons");
        strcpy_s(sampleBooks[5].model, "Ivan Turgenev");
        sampleBooks[5].year = 1862;
        sampleBooks[5].price = 16;
        strcpy_s(sampleBooks[5].body, "Novel");
        strcpy_s(sampleBooks[5].segment, "Russian");

        strcpy_s(sampleBooks[6].brand, "The Cherry Orchard");
        strcpy_s(sampleBooks[6].model, "Anton Chekhov");
        sampleBooks[6].year = 1904;
        sampleBooks[6].price = 12;
        strcpy_s(sampleBooks[6].body, "Drama");
        strcpy_s(sampleBooks[6].segment, "Russian");

        strcpy_s(sampleBooks[7].brand, "Doctor Zhivago");
        strcpy_s(sampleBooks[7].model, "Boris Pasternak");
        sampleBooks[7].year = 1957;
        sampleBooks[7].price = 24;
        strcpy_s(sampleBooks[7].body, "Novel");
        strcpy_s(sampleBooks[7].segment, "Russian");

        strcpy_s(sampleBooks[8].brand, "The Idiot");
        strcpy_s(sampleBooks[8].model, "Fyodor Dostoevsky");
        sampleBooks[8].year = 1869;
        sampleBooks[8].price = 19;
        strcpy_s(sampleBooks[8].body, "Novel");
        strcpy_s(sampleBooks[8].segment, "Russian");

        strcpy_s(sampleBooks[9].brand, "Heart of a Dog");
        strcpy_s(sampleBooks[9].model, "Mikhail Bulgakov");
        sampleBooks[9].year = 1925;
        sampleBooks[9].price = 14;
        strcpy_s(sampleBooks[9].body, "Satire");
        strcpy_s(sampleBooks[9].segment, "Russian");

        ofstream generateFile(filename, ios::binary | ios::trunc);

        if (!generateFile) {
            cout << "File creation error" << endl;
            delete[] sampleBooks;
            return 1;
        }

        // Запись десяти книг в бинарный файл.
        for (int i = 0; i < 10; i++) {
            generateFile.write(
                reinterpret_cast<char*>(&sampleBooks[i]),
                sizeof(Car)
            );
        }

        generateFile.close();
        delete[] sampleBooks;

        cout << "books.dat generated with 10 books." << endl;
    }

    checkFile.close();

    // ============================================================
    // GENERATE BOOKS — END
    // ============================================================

    Car* car = new Car; // Динамическая запись книги
    int choice;         // Пункт главного меню

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

            inputText(car->brand, 30, "Book title: ");
            inputText(car->model, 30, "Author: ");

            cout << "Publication year: ";

            while (!(cin >> car->year) ||
                   car->year < 1 || car->year > 2026) {
                cout << "Enter a year from 1 to 2026: ";
                cin.clear();
                cin.ignore(numeric_limits<streamsize>::max(), '\n');
            }

            cout << "Price: ";

            while (!(cin >> car->price) || car->price <= 0) {
                cout << "Enter a positive price: ";
                cin.clear();
                cin.ignore(numeric_limits<streamsize>::max(), '\n');
            }

            cin.ignore(numeric_limits<streamsize>::max(), '\n');

            inputText(car->body, 20, "Genre: ");
            inputText(car->segment, 10, "Language: ");

            ofstream file(filename, ios::binary | ios::app);

            if (!file) {
                cout << "File open error" << endl;
            }
            else {
                file.write(reinterpret_cast<char*>(car), sizeof(Car));

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
            ifstream file(filename, ios::binary);

            if (!file) {
                cout << "Error reading file." << endl;
            }
            else {
                Car* book = new Car; // Динамическая запись для чтения
                bool found = false;  // Есть ли книги

                printHeader();

                // Чтение и вывод всех книг.
                while (file.read(reinterpret_cast<char*>(book), sizeof(Car))) {
                    printBook(book);
                    found = true;
                }

                if (!found) {
                    cout << "The catalog is empty." << endl;
                }

                delete book;
                file.close();
            }

            break;
        }

        case 3: {
            int searchChoice; // Поле поиска

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

    delete car; // Освобождение динамической памяти

    return 0;
}
