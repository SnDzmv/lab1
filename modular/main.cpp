#include <iostream>
#include <limits>

#include "input.h"
#include "output.h"
#include "search.h"

using namespace std;

// Точка входа: повторяет меню до выбора пункта 0.
int main() {
    int choice; // Выбранный пункт основного меню: 0 — выход, 1–3 — операции.

    // ============================================================
// GENERATE BOOKS — START
// ОДНОРАЗОВЫЙ КОД: ЗАПУСТИ ОДИН РАЗ, ЗАТЕМ УДАЛИ ЭТОТ БЛОК
// ============================================================

    Book sampleBooks[10] = {
        { "War and Peace", "Leo Tolstoy", 1869, 2500, "Novel", "Russian" },
        { "Crime and Punishment", "Fyodor Dostoevsky", 1866, 2000, "Novel", "Russian" },
        { "The Master and Margarita", "Mikhail Bulgakov", 1967, 2200, "Fantasy", "Russian" },
        { "Dead Souls", "Nikolai Gogol", 1842, 1500, "Satire", "Russian" },
        { "Eugene Onegin", "Alexander Pushkin", 1833, 1800, "Poetry", "Russian" },
        { "Fathers and Sons", "Ivan Turgenev", 1862, 1600, "Novel", "Russian" },
        { "The Cherry Orchard", "Anton Chekhov", 1904, 1200, "Drama", "Russian" },
        { "Doctor Zhivago", "Boris Pasternak", 1957, 2400, "Novel", "Russian" },
        { "The Idiot", "Fyodor Dostoevsky", 1869, 1900, "Novel", "Russian" },
        { "Heart of a Dog", "Mikhail Bulgakov", 1925, 1400, "Satire", "Russian" }
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
            sizeof(Book)
        );
    }

    generateFile.close();

    cout << "books.dat generated with 10 Russian books." << endl;

    // ============================================================
    // GENERATE BOOKS — END
    // УДАЛИ ВЕСЬ КОД ОТ START ДО END ВКЛЮЧИТЕЛЬНО
    // ============================================================

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
        case 1:
            addBook();
            break;

        case 2:
            showAll();
            break;

        case 3:
            findBook();
            break;

        case 0:
            cout << "Exit" << endl;
            break;

        default:
            cout << "Wrong choice" << endl;
            break;
        }

    } while (choice != 0);

    return 0;
}
