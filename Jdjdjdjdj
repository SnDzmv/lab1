
#include <iostream>
#include <string>
#include <Windows.h>
#include <locale>
#include <algorithm>

using namespace std;

const int MAX_BOOKS = 100;


struct Book {
    string title;       
    string author;     
    int year;        
    int pages;       
    bool isActive;     
};


Book library[MAX_BOOKS]; 
int bookCount = 0;        


void initializeTestBooks() {
    library[0] = { "Война и мир", "Лев Толстой", 1869, 1274, true };
    library[1] = { "Преступление и наказание", "Фёдор Достоевский", 1866, 671, true };
    library[2] = { "Мастер и Маргарита", "Михаил Булгаков", 1967, 480, true };
    library[3] = { "1984", "Джордж Оруэлл", 1949, 328, true };
    library[4] = { "Гарри Поттер и философский камень", "Джоан Роулинг", 1997, 432, true };
    library[5] = { "Три товарища", "Эрих Мария Ремарк", 1936, 480, true };
    library[6] = { "Маленький принц", "Антуан де Сент-Экзюпери", 1943, 96, true };
    library[7] = { "Анна Каренина", "Лев Толстой", 1877, 864, true };
    library[8] = { "Граф Монте-Кристо", "Александр Дюма", 1844, 1276, true };
    library[9] = { "Сто лет одиночества", "Габриэль Гарсиа Маркес", 1967, 422, true };
    bookCount = 10;
}

string toLowerCase(string str) {
    for (size_t i = 0; i < str.length(); i++) {

        if (str[i] >= 'A' && str[i] <= 'Z') {
            str[i] = str[i] + 32;
        }
        else if ((unsigned char)str[i] >= 192 && (unsigned char)str[i] <= 223) {
            str[i] = (unsigned char)str[i] + 32;
        }

        else if ((unsigned char)str[i] == 168) {
            str[i] = (unsigned char)184;
        }
    }
    return str;
}


bool containsSubstring(const string& text, const string& search) {
    if (search.empty()) return true;
    if (text.length() < search.length()) return false;


    string textLower = toLowerCase(text);
    string searchLower = toLowerCase(search);

    for (size_t i = 0; i <= textLower.length() - searchLower.length(); i++) {
        bool match = true;
        for (size_t j = 0; j < searchLower.length(); j++) {
            if (textLower[i + j] != searchLower[j]) {
                match = false;
                break;
            }
        }
        if (match) return true;
    }
    return false;
}


void clearScreen() {
    system("cls");
}


void clearInputBuffer() {
    cin.clear();
    while (cin.get() != '\n' && cin.good());
}


void addBook() {
    clearScreen();
    cout << "=== ДОБАВЛЕНИЕ КНИГИ ===" << endl << endl;

    if (bookCount >= MAX_BOOKS) {
        cout << "Ошибка: Библиотека заполнена! Максимум " << MAX_BOOKS << " книг." << endl;
        system("pause");
        return;
    }

    Book newBook;
    newBook.isActive = true;

    clearInputBuffer();

    cout << "Введите название книги: ";
    getline(cin, newBook.title);

    cout << "Введите автора: ";
    getline(cin, newBook.author);

    cout << "Введите год выпуска: ";
    cin >> newBook.year;

    cout << "Введите количество страниц: ";
    cin >> newBook.pages;

    library[bookCount] = newBook;
    bookCount++;

    cout << endl << "Книга успешно добавлена! Всего книг: " << bookCount << endl;
    system("pause");
}


void displayAllBooks() {
    clearScreen();
    cout << "=== ВСЕ КНИГИ В БИБЛИОТЕКЕ ===" << endl << endl;

    int activeCount = 0;
    for (int i = 0; i < bookCount; i++) {
        if (library[i].isActive) {
            cout << "Книга #" << (i + 1) << endl;
            cout << "  Название: " << library[i].title << endl;
            cout << "  Автор: " << library[i].author << endl;
            cout << "  Год: " << library[i].year << endl;
            cout << "  Страниц: " << library[i].pages << endl;
            cout << "-------------------" << endl;
            activeCount++;
        }
    }

    if (activeCount == 0) {
        cout << "Библиотека пуста." << endl;
    }

    cout << endl;
    system("pause");
}


void searchByTitle() {
    clearScreen();
    cout << "=== ПОИСК ПО НАЗВАНИЮ ===" << endl << endl;

    string searchQuery;
    cout << "Введите название книги (или часть): ";

    clearInputBuffer();
    getline(cin, searchQuery);

    bool found = false;
    cout << endl << "Результаты поиска:" << endl << endl;

    for (int i = 0; i < bookCount; i++) {
        if (library[i].isActive && containsSubstring(library[i].title, searchQuery)) {
            cout << "Книга #" << (i + 1) << endl;
            cout << "  Название: " << library[i].title << endl;
            cout << "  Автор: " << library[i].author << endl;
            cout << "  Год: " << library[i].year << endl;
            cout << "  Страниц: " << library[i].pages << endl;
            cout << "-------------------" << endl;
            found = true;
        }
    }

    if (!found) {
        cout << "Книги не найдены." << endl;
    }

    cout << endl;
    system("pause");
}


void searchByAuthor() {
    clearScreen();
    cout << "=== ПОИСК ПО АВТОРУ ===" << endl << endl;

    string searchQuery;
    cout << "Введите имя автора (или часть): ";

    clearInputBuffer();
    getline(cin, searchQuery);

    bool found = false;
    cout << endl << "Результаты поиска:" << endl << endl;

    for (int i = 0; i < bookCount; i++) {
        if (library[i].isActive && containsSubstring(library[i].author, searchQuery)) {
            cout << "Книга #" << (i + 1) << endl;
            cout << "  Название: " << library[i].title << endl;
            cout << "  Автор: " << library[i].author << endl;
            cout << "  Год: " << library[i].year << endl;
            cout << "  Страниц: " << library[i].pages << endl;
            cout << "-------------------" << endl;
            found = true;
        }
    }

    if (!found) {
        cout << "Книги не найдены." << endl;
    }

    cout << endl;
    system("pause");
}


void searchByYear() {
    clearScreen();
    cout << "=== ПОИСК ПО ГОДУ ===" << endl << endl;

    int searchYear;
    cout << "Введите год выпуска: ";
    cin >> searchYear;

    bool found = false;
    cout << endl << "Результаты поиска:" << endl << endl;

    for (int i = 0; i < bookCount; i++) {
        if (library[i].isActive && library[i].year == searchYear) {
            cout << "Книга #" << (i + 1) << endl;
            cout << "  Название: " << library[i].title << endl;
            cout << "  Автор: " << library[i].author << endl;
            cout << "  Год: " << library[i].year << endl;
            cout << "  Страниц: " << library[i].pages << endl;
            cout << "-------------------" << endl;
            found = true;
        }
    }

    if (!found) {
        cout << "Книги не найдены." << endl;
    }

    cout << endl;
    system("pause");
}


void searchByPages() {
    clearScreen();
    cout << "=== ПОИСК ПО КОЛИЧЕСТВУ СТРАНИЦ ===" << endl << endl;

    int minPages, maxPages;
    cout << "Введите минимальное количество страниц: ";
    cin >> minPages;
    cout << "Введите максимальное количество страниц: ";
    cin >> maxPages;

    bool found = false;
    cout << endl << "Результаты поиска в диапазоне от " << minPages << " до " << maxPages << " страниц:" << endl << endl;

    for (int i = 0; i < bookCount; i++) {
        if (library[i].isActive && library[i].pages >= minPages && library[i].pages <= maxPages) {
            cout << "Книга #" << (i + 1) << endl;
            cout << "  Название: " << library[i].title << endl;
            cout << "  Автор: " << library[i].author << endl;
            cout << "  Год: " << library[i].year << endl;
            cout << "  Страниц: " << library[i].pages << endl;
            cout << "-------------------" << endl;
            found = true;
        }
    }

    if (!found) {
        cout << "Книги с таким количеством страниц не найдены." << endl;
    }

    cout << endl;
    system("pause");
}

int main() {
    SetConsoleCP(1251);
    SetConsoleOutputCP(1251);
    setlocale(LC_ALL, "Russian");


    initializeTestBooks();

    int choice = 0;
    do {
        clearScreen();
        cout << "====== ГЛАВНОЕ МЕНЮ БИБЛИОТЕКИ ======" << endl;
        cout << "1. Просмотреть все книги" << endl;
        cout << "2. Добавить новую книгу" << endl;
        cout << "3. Поиск по названию" << endl;
        cout << "4. Поиск по автору" << endl;
        cout << "5. Поиск по году издания" << endl;
        cout << "6. Поиск по диапазону страниц" << endl;
        cout << "0. Выход из программы" << endl;
        cout << "=====================================" << endl;
        cout << "Выберите действие: ";

        cin >> choice;

        switch (choice) {
        case 1: displayAllBooks(); break;
        case 2: addBook(); break;
        case 3: searchByTitle(); break;
        case 4: searchByAuthor(); break;
        case 5: searchByYear(); break;
        case 6: searchByPages(); break;
        case 0:
            clearScreen();
            cout << "Программа завершена. До свидания!" << endl;
            break;
        default:
            cout << "Неверный пункт меню! Попробуйте снова." << endl;
            system("pause");
            break;
        }
    } while (choice != 0);
    return 0;
}
