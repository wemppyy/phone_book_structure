#include <iostream>
#include <fstream>
#include <string>

using namespace std;

struct Phone_book {
private:
    int contact_count = 0;
    struct Contact {
        string name;
        string surname;
        string phone_number;
    };

    void set_default(Contact* contact) {
        contact->name = "Unknown";
        contact->surname = "Unknown";
        contact->phone_number = "Unknown";
    }

    bool is_name_exceeded(string name) {
        return name.length() > 10;
    }

    bool is_surname_exceeded(string surname) {
        return surname.length() > 20;
    }

    bool is_phone_number_exceeded(string phone_number) {
        return phone_number.length() > 12;
    }

    Contact contact_list[20];
public:
    Phone_book() {
        for (int i = 0; i < 20; i++) {
            set_default(&contact_list[i]);
        }
    }

    void add_contact(string name, string surname, string phone_number) {
        do {
            contact_list[contact_count].name = name;
        } while (is_name_exceeded(name));

        do {
            contact_list[contact_count].surname = surname;
        } while (is_surname_exceeded(surname));

        do {
            contact_list[contact_count].phone_number = phone_number;
        } while (is_phone_number_exceeded(phone_number));

        contact_count++;
#ifdef DEBUG
        cout << "count: " << contact_count << endl;
#endif // DEBUG
    }

    void show_contacts() {
        for (int i = 0; i < contact_count; i++) {
            show_contact(i);
        }
    }

    string get_contact(int index) const {
        if (index < 0 || index >= contact_count) {
            cout << "Invalid index" << endl;
            return "";
        }

        return contact_list[index].name + " " + contact_list[index].surname + " - " + contact_list[index].phone_number;
    }

    string get_contacts() const {
        string contacts = "";
        for (int i = 0; i < contact_count; i++) {
            contacts += get_contact(i) + "\n";
        }
        return contacts;
    }

    void show_contact(int index) {
        if (index < 0 || index >= contact_count) {
            cout << "Invalid index" << endl;
            return;
        }

        cout << contact_list[index].name << " " << contact_list[index].surname << " - " << contact_list[index].phone_number << endl;
    }

    int get_count() { return contact_count; }

    void delete_contact(int index) {
#ifdef DEBUG
        cout << "count: " << contact_count << endl;
#endif // DEBUG
        if (index < 0 || index >= contact_count) {
            cout << "Invalid index" << endl;
            return;
        }

        for (int i = index; i < contact_count - 1; i++) {
            contact_list[i] = contact_list[i + 1];
        }

        contact_count--;
    }

    ~Phone_book() {}
};

void write_struct_to_file(const Phone_book& book) {
    // Write the struct to a file
    ofstream file("phone_book.txt", ios::binary);
    string contacts = book.get_contacts();
    file.write(contacts.c_str(), contacts.size());
    file.close();
}

void add_contact_to_file(Phone_book& book, string name, string surname, string phone_number) {
    book.add_contact(name, surname, phone_number);
    write_struct_to_file(book);
}

void delete_contact_from_file(Phone_book& book, int index) {
    book.delete_contact(index);
    write_struct_to_file(book);
}

void show_contacts_from_file() {
    // Read the struct from a file
    ifstream file("phone_book.txt", ios::binary);
    string line;
    while (getline(file, line)) {
        cout << line << endl;
    }
    file.close();
}

void close_program(Phone_book& book) {
    write_struct_to_file(book);
    exit(0);
}

void menu(int choice, Phone_book& phone_book) {
    switch (choice) {
    case 1: {
        string name, surname, phone_number;
        system("cls");
        cout << "Enter name: ";
        cin >> name;
        cout << "Enter surname: ";
        cin >> surname;
        cout << "Enter phone number: ";
        cin >> phone_number;
        add_contact_to_file(phone_book, name, surname, phone_number);
        system("pause");
        break;
    }
    case 2: {
        int index;
        system("cls");
        cout << "Enter index: ";
        cin >> index;
        delete_contact_from_file(phone_book, index);
        system("pause");
        break;
    }
    case 3: {
        system("cls");
        show_contacts_from_file();
        system("pause");
        break;
    }
    case 4:
        system("cls");
        cout << phone_book.get_count() << endl;
        system("pause");
        break;
    case 5: {
        close_program(phone_book);
        break;
    }
    }
}

int menu_choice() {
    int choice;
    system("cls");
    cout << "Menu" << endl;
    cout << "1. Add contact" << endl;
    cout << "2. Delete contact" << endl;
    cout << "3. Show contacts" << endl;
    cout << "4. Show count" << endl;
    cout << "5. Exit" << endl;
    cout << "Enter your choice: ";
    while (!(cin >> choice) || choice < 1 || choice > 5) {
        cout << "Invalid choice. Enter again: ";
        cin.clear();
        cin.ignore(numeric_limits<streamsize>::max(), '\n');
    }
    return choice;
}

int main() {
    Phone_book phone_book;
    while (true) {
        int choice = menu_choice();
        menu(choice, phone_book);
    }
    return 0;
}
