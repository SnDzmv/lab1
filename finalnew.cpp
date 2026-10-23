#include <iostream>
#include <fstream>
#include <cstring>
#include <limits>
#include <iomanip>
#include <string>

using namespace std;

// Структура одной записи каталога книг.
struct Book {
    char title[30]; // Название
    char author[30]; // Автор
    int year; // Год выпуска.
    int price; // Цена.
    char genre[20]; //Жанр 
    char lang[10]; //Язык
};

// Точка входа: повторяет меню до выбора пункта 0.
int main() {
    Book book; // Текущая запись книги для ввода, чтения или вывода.
    int choice; // Выбранный пункт основного меню: 0 — выход, 1–3 — операции.

    do {
        cout << "1 - Add book" << endl;
        cout << "2 - Show all" << endl;
        cout << "3 - Search" << endl;
        cout << "0 - Exit" << endl;

        while (!(cin >> choice) || choice < 0 || choice > 3) {
            cout << "Enter a number: ";

            cin.clear();
            cin.ignore(numeric_limits<streamsize>::max(), '\n');
        }
        switch (choice) {
        case 1: {
            cin.ignore(numeric_limits<streamsize>::max(), '\n');

            cout << "Title: ";
            cin.getline(book.title, 30);

            while (cin.fail() || strlen(book.title) == 0) {
                if (cin.fail()) {
                    cin.clear();
                    cin.ignore(numeric_limits<streamsize>::max(), '\n');

                    cout << "Title is too long. Maximum 29 characters: ";
                }
                else {
                    cout << "Title cannot be empty" << endl;
                }

                cin.getline(book.title, 30);
            }

            cout << "Author: ";
            cin.getline(book.author, 30);

            while (cin.fail() || strlen(book.author) == 0) {
                if (cin.fail()) {
                    cin.clear();
                    cin.ignore(numeric_limits<streamsize>::max(), '\n');

                    cout << "Author is too long. Maximum 29 characters" << endl;
                }
                else {
                    cout << "Author cannot be empty" << endl;
                }

                cin.getline(book.author, 30);

            }

            cout << "Year: ";
            while (!(cin >> book.year) || book.year < 0 || book.year > 2026) {
                cout << "Wrong year. Enter year from 0 to 2026" << endl;

                cin.clear();
                cin.ignore(numeric_limits<streamsize>::max(), '\n');
            }

            cout << "Price: ";
            while (!(cin >> book.price) || book.price <= 0) {
                cout << "Wrong price. Enter positive number: ";

                cin.clear();
                cin.ignore(numeric_limits<streamsize>::max(), '\n');
            }
            cin.ignore(numeric_limits<streamsize>::max(), '\n');

            cout << "Genre: ";
            cin.getline(book.genre, 20);

            while (cin.fail() || strlen(book.genre) == 0) {
                if (cin.fail()) {
                    cin.clear();
                    cin.ignore(numeric_limits<streamsize>::max(), '\n');

                    cout << "Genre book is too long. Maximum 19 characters" << endl;
                }
                else {
                    cout << "Genre book cannot be empty" << endl;
                }
                cin.getline(book.genre, 20);
            }

            cout << "Lang: ";
            cin.getline(book.lang, 10);

            while (cin.fail() || strlen(book.lang) == 0) {
                if (cin.fail()) {
                    cin.clear();
                    cin.ignore(numeric_limits<streamsize>::max(), '\n');

                    cout << "Lang is too long. Maximum 9 characters" << endl;
                }
                else {
                    cout << "Lang cannot be empty" << endl;
                }
                cin.getline(book.lang, 10);
            }

            ofstream file("books.dat", ios::binary | ios::app); // Поток двоичной записи: новые данные добавляются в конец файла.
            if (!file) {
                cout << "File open error" << endl;
            }
            else {
                file.write(reinterpret_cast<char*>(&book), sizeof(Book));

                file.close();

                cout << "Book added." << endl;
            }

            break;
        }
        case 2: {
            ifstream file("books.dat", ios::binary); // Поток двоичного чтения записей из файла books.dat.

            if (!file) {
                cout << "Error file read" << endl;
            }
            else {
                cout << left
                    << setw(31) << "Title"
                    << setw(31) << "Author"
                    << setw(21) << "Genre"
                    << setw(11) << "Lang"
                    << setw(8) << "Year"
                    << setw(14) << "Price"
                    << endl;
                cout << string(116, '-') << endl;
                while (file.read(reinterpret_cast<char*>(&book), sizeof(Book))) {
                    cout << left
                        << setw(31) << book.title
                        << setw(31) << book.author
                        << setw(21) << book.genre
                        << setw(11) << book.lang
                        << setw(8) << book.year
                        << setw(14) << book.price
                        << endl;
                }

                file.close();
            }
            break;
        }
        case 3: {
            int searchChoice; // Поле поиска: 1–6; значение 0 возвращает в основное меню.

            cout << "search by: " << endl;
            cout << "1 - title" << endl;
            cout << "2 - author" << endl;
            cout << "3 - year" << endl;
            cout << "4 - price" << endl;
            cout << "5 - genre" << endl;
            cout << "6 - lang " << endl;
            cout << "0 - back" << endl;

            while (!(cin >> searchChoice) || searchChoice < 0 || searchChoice > 6) {
                cout << "Wrong choice. Enter 0-6: ";

                cin.clear();
                cin.ignore(numeric_limits<streamsize>::max(), '\n');

            }

            if (searchChoice == 1) {
                char searchTitle[30]; // Подстрока для поиска по названию.

                cin.ignore(numeric_limits<streamsize>::max(), '\n');

                cout << "Enter Title: ";
                cin.getline(searchTitle, 30);

                while (cin.fail() || strlen(searchTitle) == 0) {
                    if (cin.fail()) {
                        cin.clear();
                        cin.ignore(numeric_limits<streamsize>::max(), '\n');

                        cout << "Title is too long. Maximum 29 characters" << endl;
                    }
                    else {
                        cout << "Title cannot be empty" << endl;
                    }
                    cin.getline(searchTitle, 30);
                }

                ifstream file("books.dat", ios::binary); // Поток двоичного чтения записей из файла books.dat.

                if (!file) {
                    cout << "File open error" << endl;
                }
                else {
                    cout << left
                        << setw(31) << "Title"
                        << setw(31) << "Author"
                        << setw(21) << "Genre"
                        << setw(11) << "Lang"
                        << setw(8) << "Year"
                        << setw(14) << "Price"
                        << endl;
                    cout << string(116, '-') << endl;
                    while (file.read(reinterpret_cast<char*>(&book), sizeof(Book))) {
                        if (strstr(book.title, searchTitle) != nullptr) {

                            cout << left
                                << setw(31) << book.title
                                << setw(31) << book.author
                                << setw(21) << book.genre
                                << setw(11) << book.lang
                                << setw(8) << book.year
                                << setw(14) << book.price
                                << endl;
                        }
                    }
                    file.close();
                }
            }
            if (searchChoice == 2) {
                char searchAuthor[30]; // Подстрока для поиска по модели.

                cin.ignore(numeric_limits<streamsize>::max(), '\n');

                cout << "Enter author: " << endl;

                cin.getline(searchAuthor, 30);
                while (cin.fail() || strlen(searchAuthor) == 0) {
                    if (cin.fail()) {
                        cin.clear();
                        cin.ignore(numeric_limits<streamsize>::max(), '\n');

                        cout << "Author is too long. Maximum characters 29" << endl;
                    }
                    else {
                        cout << "Author cannot be empty" << endl;
                    }
                    cin.getline(searchAuthor, 30);
                }

                ifstream file("books.dat", ios::binary); // Поток двоичного чтения записей из файла books.dat.

                if (!file) {
                    cout << "File open error" << endl;
                }
                else {
                    cout << left
                        << setw(31) << "Title"
                        << setw(31) << "Author"
                        << setw(21) << "Genre"
                        << setw(11) << "Lang"
                        << setw(8) << "Year"
                        << setw(14) << "Price"
                        << endl;
                    cout << string(116, '-') << endl;
                    while (file.read(reinterpret_cast<char*>(&book), sizeof(Book))) {
                        if (strstr(book.author, searchAuthor) != nullptr) {

                            cout << left
                                << setw(31) << book.title
                                << setw(31) << book.author
                                << setw(21) << book.genre
                                << setw(11) << book.lang
                                << setw(8) << book.year
                                << setw(14) << book.price
                                << endl;
                        }
                    }
                    file.close();
                }
            }
            if (searchChoice == 3) {
                int minYear; // Нижняя граница диапазона годов.
                int maxYear; // Верхняя граница диапазона годов; не меньше нижней.
                cout << "From year: " << endl;
                while (!(cin >> minYear) || minYear < 1886 || minYear > 2026) {
                    cout << "Wrong year. Enter year from 1886 to 2026" << endl;

                    cin.clear();
                    cin.ignore(numeric_limits<streamsize>::max(), '\n');
                }
                cout << "To year: " << endl;
                while (!(cin >> maxYear) || maxYear < 1886 || maxYear > 2026 || maxYear < minYear) {
                    cout << "Wrong year. Enter year from " << minYear << " to 2026: ";

                    cin.clear();
                    cin.ignore(numeric_limits<streamsize>::max(), '\n');
                }

                ifstream file("books.dat", ios::binary); // Поток двоичного чтения записей из файла books.dat.
                if (!file) {
                    cout << "File open error" << endl;
                }
                else {
                    cout << left
                        << setw(31) << "Title"
                        << setw(31) << "Author"
                        << setw(21) << "Genre"
                        << setw(11) << "Lang"
                        << setw(8) << "Year"
                        << setw(14) << "Price"
                        << endl;
                    cout << string(116, '-') << endl;
                    while (file.read(reinterpret_cast<char*>(&book), sizeof(Book))) {
                        if (book.year >= minYear && book.year <= maxYear) {

                            cout << left
                                << setw(31) << book.title
                                << setw(31) << book.author
                                << setw(21) << book.genre
                                << setw(11) << book.lang
                                << setw(8) << book.year
                                << setw(14) << book.price
                                << endl;
                        }
                    }
                    file.close();
                }
            }
            if (searchChoice == 4) {
                int minPrice; // Нижняя граница диапазона цен.
                int maxPrice; // Верхняя граница диапазона цен; не меньше нижней.
                cout << "From price" << endl;
                while (!(cin >> minPrice) || minPrice < 1) {
                    cout << "Wrong price. Enter correct price." << endl;

                    cin.clear();
                    cin.ignore(numeric_limits<streamsize>::max(), '\n');
                }
                cout << "To price" << endl;
                while (!(cin >> maxPrice) || maxPrice < 1 || maxPrice < minPrice) {
                    cout << "Wrong price. Enter correct price." << endl;

                    cin.clear();
                    cin.ignore(numeric_limits<streamsize>::max(), '\n');
                }

                ifstream file("books.dat", ios::binary); // Поток двоичного чтения записей из файла books.dat.

                if (!file) {
                    cout << "File open error" << endl;
                }
                else {
                    cout << left
                        << setw(31) << "Title"
                        << setw(31) << "Author"
                        << setw(21) << "Genre"
                        << setw(11) << "Lang"
                        << setw(8) << "Year"
                        << setw(14) << "Price"
                        << endl;
                    cout << string(116, '-') << endl;
                    while (file.read(reinterpret_cast<char*>(&book), sizeof(Book))) {
                        if (book.price >= minPrice && book.price <= maxPrice) {

                            cout << left
                                << setw(31) << book.title
                                << setw(31) << book.author
                                << setw(21) << book.genre
                                << setw(11) << book.lang
                                << setw(8) << book.year
                                << setw(14) << book.price
                                << endl;
                        }
                    }
                    file.close();
                }
            }
            if (searchChoice == 5) {
                char searchGenre[20]; // Подстрока для поиска по типу жанра.

                cin.ignore(numeric_limits<streamsize>::max(), '\n');

                cout << "Enter genre: " << endl;
                cin.getline(searchGenre, 20);
                while (cin.fail() || strlen(searchGenre) == 0) {
                    if (cin.fail()) {
                        cin.clear();
                        cin.ignore(numeric_limits<streamsize>::max(), '\n');

                        cout << "Genre is too long. Maximum characters 19" << endl;
                    }
                    else {
                        cout << "Genre cannot be empty" << endl;
                    }
                    cin.getline(searchGenre, 20);
                }

                ifstream file("books.dat", ios::binary); // Поток двоичного чтения записей из файла books.dat.

                if (!file) {
                    cout << "File open error" << endl;
                }
                else {
                    cout << left
                        << setw(31) << "Title"
                        << setw(31) << "Author"
                        << setw(21) << "Genre"
                        << setw(11) << "Lang"
                        << setw(8) << "Year"
                        << setw(14) << "Price"
                        << endl;
                    cout << string(116, '-') << endl;

                    while (file.read(reinterpret_cast<char*>(&book), sizeof(Book))) {
                        if (strstr(book.genre, searchGenre) != nullptr) {

                            cout << left
                                << setw(31) << book.title
                                << setw(31) << book.author
                                << setw(21) << book.genre
                                << setw(11) << book.lang
                                << setw(8) << book.year
                                << setw(14) << book.price
                                << endl;
                        }
                    }
                    file.close();
                }
            }
            if (searchChoice == 6) {
                char searchLang[10]; // Подстрока для поиска по языку.

                cin.ignore(numeric_limits<streamsize>::max(), '\n');

                cout << "Enter lang: " << endl;
                cin.getline(searchLang, 10);

                while (cin.fail() || strlen(searchLang) == 0) {
                    if (cin.fail()) {
                        cin.clear();
                        cin.ignore(numeric_limits<streamsize>::max(), '\n');

                        cout << "Lang is too long. Maximum characters 9" << endl;
                    }
                    else {
                        cout << "Lang cannot be empty" << endl;
                    }
                    cin.getline(searchLang, 10);
                }

                ifstream file("books.dat", ios::binary); // Поток двоичного чтения записей из файла books.dat.

                if (!file) {
                    cout << "File open error" << endl;
                }
                else {
                    cout << left
                        << setw(31) << "Title"
                        << setw(31) << "Author"
                        << setw(21) << "Genre"
                        << setw(11) << "Lang"
                        << setw(8) << "Year"
                        << setw(14) << "Price"
                        << endl;
                    cout << string(116, '-') << endl;
                    while (file.read(reinterpret_cast<char*>(&book), sizeof(Book))) {
                        if (strstr(book.lang, searchLang) != nullptr) {
                            cout << left
                                << setw(31) << book.title
                                << setw(31) << book.author
                                << setw(21) << book.genre
                                << setw(11) << book.lang
                                << setw(8) << book.year
                                << setw(14) << book.price
                                << endl;
                        }
                    }
                    file.close();
                }

            }
            break;
        }
        case 0:
        {
            cout << "Exit" << endl;
            break;
        }

        default:
            cout << "Wrong choise" << endl;
            break;
        }

    } while (choice != 0);

    return 0;
}
