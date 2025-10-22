// COMSC 210 | Oct 21 2025 | Lab 23
// IDE: VS Code

#include <iostream>
#include <fstream>
#include <iomanip>
#include <list>
#include "Goat.h"
using namespace std;

const int SZ_NAMES = 200, SZ_COLORS = 25, MAX_AGE = 20;

// FN PROTOTYPES
int select_goat(list<Goat> trip);
void delete_goat(list<Goat> &trip);
void add_goat(list<Goat> &trip, string [], string []);
void display_trip(list<Goat> trip);
int main_menu();

// MAIN
int main() {
    srand(time(0));
    bool again;

    // read & populate arrays for names and colors
    ifstream fin("names.txt");
    string names[SZ_NAMES];
    int i = 0;
    while (fin >> names[i++]);
    fin.close();
    ifstream fin1("colors.txt");
    string colors[SZ_COLORS];
    i = 0;
    while (fin1 >> colors[i++]);
    fin1.close();

    // menu loop
    list<Goat> trip;
    int choice;

    while (true) {
        choice = main_menu();
        switch (choice) {
            case 1:
                add_goat(trip, names, colors);
                break;
            case 2:
                delete_goat(trip);
                break;
            case 3:
                display_trip(trip);
                break;
            case 4:
                return 0;
        }
    }
}

// PROGRAMMER FUNCTIONS
void add_goat(list<Goat> &trip, string names[], string colors[]) {
    // Adds a goat with random traits
    // Args:
    //   trip - reference to list of goats
    //   names - array of possible names
    //   colors - array of possible colors

    string name = names[rand() % SZ_NAMES];
    int age = rand() % (MAX_AGE + 1); // age 0 to MAX_AGE
    string color = colors[rand() % SZ_COLORS];
    trip.push_back(Goat(name, age, color));
}

void display_trip(list<Goat> trip) {
    // Displays goats in the trip; numbered "index"
    // Arg: reference to list of goats

    list<Goat>::iterator it;
    int index = 0;
    for (it = trip.begin(); it != trip.end(); ++it) {
        cout << "[" << index << "] ";
        cout << it->get_name() << " ";
        cout << "(" << it->get_age() << ", ";
        cout << it->get_color() << ")" << endl;
        index++;
    }
    cout << endl;
}

int select_goat(list<Goat> trip) {
    // Displays goats and prompts user to select one
    // Arg: list of goats
    // Returns: index of selected goat (0 indexed)

    display_trip(trip);
    int input;
    do {
        cout << "Select goat to delete: ";
        cin >> input;

        // Validation
        if (input < 0 || input >= trip.size()) {
            cout << "Please enter a valid goat." << endl;
        }

    } while (input < 0 || input >= trip.size());

    return input;
}

void delete_goat(list<Goat> &trip) {
    // Deletes a goat from the trip via iterator; calls select_goat()
    // Arg: reference to list of goats

    int index = select_goat(trip);
    list<Goat>::iterator it = trip.begin();
    for (int i = 0; i < index; i++) {
        ++it;
    }
    trip.erase(it);
}

int main_menu() {
    // Returns user input for menu; with validation
    // Note: does not implement actual actions

    int input;
    do {
        cout << "*** GOAT MANAGER 3001 ***" << endl;
        cout << "[1] Add a goat" << endl;
        cout << "[2] Delete a goat" << endl;
        cout << "[3] List goats" << endl;
        cout << "[4] Quit" << endl;
        cout << "Choice --> ";
        cin >> input;
        cin.ignore();
        cout << endl;

        // Validation
        if (input <= 0 || input >= 5) {
            cout << "Please enter 1-4." << endl;
        }

    } while (input <= 0 || input >= 5);

    return input;
}

