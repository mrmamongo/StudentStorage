//
// Created by MrMam on 12.05.2022.
//

#include "Database/DB.h"
#include <iostream>
#include <regex>

void handle_choice(short& choice, short min, short max) {
    while (!(std::cin >> choice && choice >= min && choice <= max)) {
        std::cout << "Enter correct value\n";
        std::cin.clear();
        std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
    }
}

int main() {
    Container database{};
    try {
        std::cout << "Choose Database:\n\t0. RAM\n\t1. JSON\n\t2. SQL\n";
        short choice = 0;
        handle_choice(choice, 0, 2);

        // Database choice
        switch (choice) {
            case 0: {
                database.changeDatabase(new RAM_DB());
                std::cout << "Ram database created successfully\n";
            } break;
            case 1:
            case 2: {
                database.changeDatabase(new RAM_DB());
                std::cout << "UNDER CONSTRUCTION\n";
            } break;
        }

        // Menus
        bool stop = false;
        while (!stop) {
            std::cout << "Commands:\n\t1. Show\n\t2. Insert\n\t3. Delete\n\t4.Drop All\n\t5. Exit\n";
            handle_choice(choice, 1, 5);

            switch (choice) {
                case 1: {
                    handle_choice(choice, 1, 2);
                    switch (choice) {
                        case 1: {
                            for (const auto& s: database->Select()) {
                                std::cout << s.ToString() << '\n';
                            }
                        } break;
                        case 2: {} break;
                    }
                } break;
                case 2: {
                    bool insert_stop = true;
                    while (insert_stop) {
                        std::cout << "Enter student: <name> <group> [<subject>:<mark>, ...]\n";
                        try {
                            std::string input;
                            std::getline(std::cin, input);
                            std::cin >> input;
                            auto s = Student::FromString(std::move(input));
                            std::cout << "Validated student: " << s.ToString() << '\n';
                            database->Insert(std::move(s));
                            insert_stop = false;
                        } catch (std::runtime_error& e) {
                            std::cout << "Please, enter correct student data:\nExample: Max first [Maths:5 Programming:4 Web:3]\n";
                        } catch (std::exception& e) {
                            std::cout << "Program stopped unexpectedly: " << e.what() << '\n';
                            insert_stop = false;
                        }
                    }
                }
                case 3:
                case 4:
                case 5: { stop = true;} break;
            }
        }
    } catch (const std::exception& e) {
        std::cout << "Exception: " << e.what() << std::endl;
    } catch (...) {
        std::cout << "Unexpected exception" << std::endl;
    }
}

#ifdef DEBUG
int main() {
    std::string input;
    std::getline(std::cin, input);
    try {
        Student stud = Student::FromString(std::move(input));
        std::cout << "Student validated: " << stud.ToString();
    } catch (std::exception& e) {
        std::cout << "Bad input: " << e.what() << '\n';
    }

}
#endif