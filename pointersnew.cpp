
#include <iostream>
#include <fstream>
#include <cstring>
#include <limits>
#include <iomanip>
#include <string>

using namespace std;

struct Book {
    char title[30];   // Название книги
    char author[30];   // Автор книги
    int year;         // Год издания
    int price;        // Цена книги
    char genre[20];    // Жанр книги
    char lang[10]; // Язык книги
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

void printBook(const Book* book) {
    cout << left
        << setw(31) << book->title
        << setw(31) << book->author
        << setw(21) << book->genre
        << setw(11) << book->lang
        << setw(8) << book->year
        << setw(10) << book->price
        << endl;
}

void searchText(int fieldChoice, const char filename[]) {
    char searchText[30]; // Поисковая строка
    Book* book = new Book; // Динамическая запись книги
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
    while (file.read(reinterpret_cast<char*>(book), sizeof(Book))) {
        bool match = false; // Совпадение с запросом

        if (fieldChoice == 1 &&
            strstr(book->title, searchText) != nullptr) {
            match = true;
        }

        if (fieldChoice == 2 &&
            strstr(book->author, searchText) != nullptr) {
            match = true;
        }

        if (fieldChoice == 5 &&
            strstr(book->genre, searchText) != nullptr) {
            match = true;
        }

        if (fieldChoice == 6 &&
            strstr(book->lang, searchText) != nullptr) {
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
    Book* book = new Book;    // Динамическая запись книги
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
    while (file.read(reinterpret_cast<char*>(book), sizeof(Book))) {
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
        Book* sampleBooks = new Book[10]; // Динамический массив книг

        strcpy_s(sampleBooks[0].title, "War and Peace");
        strcpy_s(sampleBooks[0].author, "Leo Tolstoy");
        sampleBooks[0].year = 1869;
        sampleBooks[0].price = 25;
        strcpy_s(sampleBooks[0].genre, "Novel");
        strcpy_s(sampleBooks[0].lang, "Russian");

        strcpy_s(sampleBooks[1].title, "Crime and Punishment");
        strcpy_s(sampleBooks[1].author, "Fyodor Dostoevsky");
        sampleBooks[1].year = 1866;
        sampleBooks[1].price = 20;
        strcpy_s(sampleBooks[1].genre, "Novel");
        strcpy_s(sampleBooks[1].lang, "Russian");

        strcpy_s(sampleBooks[2].title, "The Master and Margarita");
        strcpy_s(sampleBooks[2].author, "Mikhail Bulgakov");
        sampleBooks[2].year = 1967;
        sampleBooks[2].price = 22;
        strcpy_s(sampleBooks[2].genre, "Fantasy");
        strcpy_s(sampleBooks[2].lang, "Russian");

        strcpy_s(sampleBooks[3].title, "Dead Souls");
        strcpy_s(sampleBooks[3].author, "Nikolai Gogol");
        sampleBooks[3].year = 1842;
        sampleBooks[3].price = 15;
        strcpy_s(sampleBooks[3].genre, "Satire");
        strcpy_s(sampleBooks[3].lang, "Russian");

        strcpy_s(sampleBooks[4].title, "Eugene Onegin");
        strcpy_s(sampleBooks[4].author, "Alexander Pushkin");
        sampleBooks[4].year = 1833;
        sampleBooks[4].price = 18;
        strcpy_s(sampleBooks[4].genre, "Poetry");
        strcpy_s(sampleBooks[4].lang, "Russian");

        strcpy_s(sampleBooks[5].title, "Fathers and Sons");
        strcpy_s(sampleBooks[5].author, "Ivan Turgenev");
        sampleBooks[5].year = 1862;
        sampleBooks[5].price = 16;
        strcpy_s(sampleBooks[5].genre, "Novel");
        strcpy_s(sampleBooks[5].lang, "Russian");

        strcpy_s(sampleBooks[6].title, "The Cherry Orchard");
        strcpy_s(sampleBooks[6].author, "Anton Chekhov");
        sampleBooks[6].year = 1904;
        sampleBooks[6].price = 12;
        strcpy_s(sampleBooks[6].genre, "Drama");
        strcpy_s(sampleBooks[6].lang, "Russian");

        strcpy_s(sampleBooks[7].title, "Doctor Zhivago");
        strcpy_s(sampleBooks[7].author, "Boris Pasternak");
        sampleBooks[7].year = 1957;
        sampleBooks[7].price = 24;
        strcpy_s(sampleBooks[7].genre, "Novel");
        strcpy_s(sampleBooks[7].lang, "Russian");

        strcpy_s(sampleBooks[8].title, "The Idiot");
        strcpy_s(sampleBooks[8].author, "Fyodor Dostoevsky");
        sampleBooks[8].year = 1869;
        sampleBooks[8].price = 19;
        strcpy_s(sampleBooks[8].genre, "Novel");
        strcpy_s(sampleBooks[8].lang, "Russian");

        strcpy_s(sampleBooks[9].title, "Heart of a Dog");
        strcpy_s(sampleBooks[9].author, "Mikhail Bulgakov");
        sampleBooks[9].year = 1925;
        sampleBooks[9].price = 14;
        strcpy_s(sampleBooks[9].genre, "Satire");
        strcpy_s(sampleBooks[9].lang, "Russian");

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
                sizeof(Book)
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

    Book* book = new Book; // Динамическая запись книги
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

            inputText(book->title, 30, "Book title: ");
            inputText(book->author, 30, "Author: ");

            cout << "Publication year: ";

            while (!(cin >> book->year) ||
                book->year < 1 || book->year > 2026) {
                cout << "Enter a year from 1 to 2026: ";
                cin.clear();
                cin.ignore(numeric_limits<streamsize>::max(), '\n');
            }

            cout << "Price: ";

            while (!(cin >> book->price) || book->price <= 0) {
                cout << "Enter a positive price: ";
                cin.clear();
                cin.ignore(numeric_limits<streamsize>::max(), '\n');
            }

            cin.ignore(numeric_limits<streamsize>::max(), '\n');

            inputText(book->genre, 20, "Genre: ");
            inputText(book->lang, 10, "Language: ");

            ofstream file(filename, ios::binary | ios::app);

            if (!file) {
                cout << "File open error" << endl;
            }
            else {
                file.write(reinterpret_cast<char*>(book), sizeof(Book));

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
                Book* book = new Book; // Динамическая запись для чтения
                bool found = false;  // Есть ли книги

                printHeader();

                // Чтение и вывод всех книг.
                while (file.read(reinterpret_cast<char*>(book), sizeof(Book))) {
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

    delete book; // Освобождение динамической памяти

    return 0;
}
