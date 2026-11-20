#ifndef OUTPUT_H
#define OUTPUT_H

#include <iostream>
#include <fstream>
#include <iomanip>
#include <string>

#include "book.h"

using namespace std;

void showAll(); // Читает файл и выводит все книги в виде таблицы.
void printHeader(); // Выводит названия столбцов таблицы.
void printBook(const Book& book); // Выводит одну запись книги; book передаётся без копирования и изменения.

void showAll() {
    Book book; // Текущая запись книги для ввода, чтения или вывода.

    ifstream file("books.dat", ios::binary); // Поток двоичного чтения записей из файла books.dat.

    if (!file) {
        cout << "Error file read" << endl;
    }
    else {
        printHeader();

        while (file.read(reinterpret_cast<char*>(&book), sizeof(Book))) {
            printBook(book);
        }

        file.close();
    }
}

void printHeader() {
    cout << left
        << setw(31) << "Title"
        << setw(31) << "Author"
        << setw(21) << "Genre"
        << setw(11) << "Lang"
        << setw(8) << "Year"
        << setw(14) << "Price"
        << endl;

    cout << string(116, '-') << endl;
}

void printBook(const Book& book) {
    cout << left
        << setw(31) << book.title
        << setw(31) << book.author
        << setw(21) << book.genre
        << setw(11) << book.lang
        << setw(8) << book.year
        << setw(14) << book.price
        << endl;
}

#endif
