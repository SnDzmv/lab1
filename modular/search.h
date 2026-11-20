#ifndef SEARCH_H
#define SEARCH_H

#include <iostream>
#include <fstream>
#include <cstring>
#include <limits>

#include "book.h"
#include "output.h"

using namespace std;

void findBook(); // Выводит меню поиска и вызывает поиск по выбранному полю.
void searchByTitle(); // Ищет книги по подстроке названия с учётом регистра.
void searchByAuthor(); // Ищет книги по подстроке автора с учётом регистра.
void searchByYear(); // Ищет книги в заданном диапазоне годов, включая границы.
void searchByPrice(); // Ищет книги в заданном диапазоне цен, включая границы.
void searchByGenre(); // Ищет книги по подстроке автора с учётом регистра.
void searchByLang(); // Ищет книги по подстроке языка с учётом регистра.

void findBook() {
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

    switch (searchChoice) {
    case 1:
        searchByTitle();
        break;

    case 2:
        searchByAuthor();
        break;

    case 3:
        searchByYear();
        break;

    case 4:
        searchByPrice();
        break;

    case 5:
        searchByGenre();
        break;

    case 6:
        searchByLang();
        break;

    case 0:
        break;

    default:
        break;
    }
}

void searchByTitle() {
    Book book; // Текущая запись книги для ввода, чтения или вывода.
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
        printHeader();

        while (file.read(reinterpret_cast<char*>(&book), sizeof(Book))) {
            if (strstr(book.title, searchTitle) != nullptr) {
                printBook(book);
            }
        }

        file.close();
    }
}

void searchByAuthor() {
    Book book; // Текущая запись книги для ввода, чтения или вывода.
    char searchAuthor[30]; // Подстрока для поиска по автору.

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
        printHeader();

        while (file.read(reinterpret_cast<char*>(&book), sizeof(Book))) {
            if (strstr(book.author, searchAuthor) != nullptr) {
                printBook(book);
            }
        }

        file.close();
    }
}

void searchByYear() {
    Book book; // Текущая запись книги для ввода, чтения или вывода.
    int minYear; // Нижняя граница диапазона годов.
    int maxYear; // Верхняя граница диапазона годов; не меньше нижней.

    cout << "From year: " << endl;

    while (!(cin >> minYear) || minYear < 0 || minYear > 2026) {
        cout << "Wrong year. Enter year from 0 to 2026" << endl;

        cin.clear();
        cin.ignore(numeric_limits<streamsize>::max(), '\n');
    }

    cout << "To year: " << endl;

    while (!(cin >> maxYear) || maxYear < 0 ||
        maxYear > 2026 || maxYear < minYear) {
        cout << "Wrong year. Enter year from " << minYear << " to 2026: ";

        cin.clear();
        cin.ignore(numeric_limits<streamsize>::max(), '\n');
    }

    ifstream file("books.dat", ios::binary); // Поток двоичного чтения записей из файла books.dat.

    if (!file) {
        cout << "File open error" << endl;
    }
    else {
        printHeader();

        while (file.read(reinterpret_cast<char*>(&book), sizeof(Book))) {
            if (book.year >= minYear && book.year <= maxYear) {
                printBook(book);
            }
        }

        file.close();
    }
}

void searchByPrice() {
    Book book; // Текущая запись книги для ввода, чтения или вывода.
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
        printHeader();

        while (file.read(reinterpret_cast<char*>(&book), sizeof(Book))) {
            if (book.price >= minPrice && book.price <= maxPrice) {
                printBook(book);
            }
        }

        file.close();
    }
}

void searchByGenre() {
    Book book; // Текущая запись книги для ввода, чтения или вывода.
    char searchGenre[20]; // Подстрока для поиска по жанру.

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
        printHeader();

        while (file.read(reinterpret_cast<char*>(&book), sizeof(Book))) {
            if (strstr(book.genre, searchGenre) != nullptr) {
                printBook(book);
            }
        }

        file.close();
    }
}

void searchByLang() {
    Book book; // Текущая запись книги для ввода, чтения или вывода.
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
        printHeader();

        while (file.read(reinterpret_cast<char*>(&book), sizeof(Book))) {
            if (strstr(book.lang, searchLang) != nullptr) {
                printBook(book);
            }
        }

        file.close();
    }
}

#endif
