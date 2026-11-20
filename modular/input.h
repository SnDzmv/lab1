#ifndef INPUT_H
#define INPUT_H

#include <iostream>
#include <fstream>
#include <cstring>
#include <limits>

#include "book.h"

using namespace std;

void addBook(); // Вводит данные книги с проверками и добавляет запись в файл.

void addBook() {
    Book book; // Текущая запись книги для ввода, чтения или вывода.

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
}

#endif
