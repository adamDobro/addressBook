#include <iostream>
#include <windows.h>
#include <string>
#include <sstream>
#include <fstream>
#include <cstdlib>
#include <vector>
#include <iterator>
#include <algorithm>
#include <cstdio>

using namespace std;

struct User
{
    int id;
    string name = "", surname = "", phone_number = "", email = "", address = "";
};

string inputLine()
{
    string input = "";
    cin.sync();
    getline(cin, input);
    return input;
}

int getInteger()
{
    string input = "";
    int number = 0;

    while(true)
    {
        getline(cin, input);

        stringstream myStream(input);
        if(myStream >> number)
            break;
        cout << "To nie jest liczba. Wpisz ponownie." << endl;
    }
    return number;
}

char inputSign()
{
    string input = "";
    char sign = {0};

    while(true)
    {
        getline(cin, input);

        if(input.length() == 1)
        {
            sign = input[0];
            break;
        }
        else if(!(input.length() == 1))
        {
            cout << "Wpisz pojedynczy znak!" << endl;
        }

    }
    return sign;
}

void addUser(vector <User> &users)
{
    User temporary;

    string name, surname, phone_number, email, address;

    int userQty = users.size();

    //temporary.id = users.back().id + 1;

    temporary.id = userQty + 1;

    cout << "Podaj imie: ";
    temporary.name = inputLine();

    cout << "Podaj nazwisko: ";
    temporary.surname = inputLine();

    cout << "Podaj nr telefonu: ";
    temporary.phone_number = inputLine();

    cout << "Podaj email: ";
    temporary.email = inputLine();

    cout << "Podaj adres: ";
    temporary.address = inputLine();

    users.push_back(temporary);

    cout << "Adresat dodany" << endl;
    Sleep(1000);

    fstream file;
    file.open("ksiazka_adresowa.txt", ios::out | ios::app);
    if(file.good())
    {
        file << users[userQty].id << "|";
        file << users[userQty].name << "|";
        file << users[userQty].surname << "|";
        file << users[userQty].phone_number << "|";
        file << users[userQty].email << "|";
        file << users[userQty].address << "|";
        file << endl;
        file.close();
    }
    else
    {
        cout << "Nie udalo sie otworzyc pliku i zapisac do niego danych." << endl;
        system("pause");
    }
}

void searchUserByName(vector <User> &users) //dodaj opcjê brak osób w bazie
{
    cout << "Podaj imie: ";
    string inputName = inputLine();

    for(unsigned int i = 0; i < users.size(); i++)
    {
        if (users[i].name == inputName)
        {
            cout << "ID:             " << users[i].id << endl;
            cout << "Imie:           " << users[i].name << endl;
            cout << "Nazwisko:       " << users[i].surname << endl;
            cout << "Numer telefonu: " << users[i].phone_number << endl;
            cout << "Email:          " << users[i].email << endl;
            cout << "Adres:          " << users[i].address << endl;
        }
    }
    system ("pause");
    system ("cls");
}

void searchUserBySurname(vector <User> &users) // dodaj opcjê brak osób w bazie
{
    cout << "Podaj nazwisko: ";
    string inputSurname = inputLine();

    for(unsigned int i = 0; i < users.size(); i++)
    {
        if (users[i].surname == inputSurname)
        {
            cout << "ID:             " << users[i].id << endl;
            cout << "Imie:           " << users[i].name << endl;
            cout << "Nazwisko:       " << users[i].surname << endl;
            cout << "Numer telefonu: " << users[i].phone_number << endl;
            cout << "Email:          " << users[i].email << endl;
            cout << "Adres:          " << users[i].address << endl;
        }
    }
    system ("pause");
    system ("cls");
}

void showAll(vector <User> &users)
{
    for(unsigned int i = 0; i < users.size(); i++)
    {
        cout << "ID:             " << users[i].id << endl;
        cout << "Imie:           " << users[i].name << endl;
        cout << "Nazwisko:       " << users[i].surname << endl;
        cout << "Numer telefonu: " << users[i].phone_number << endl;
        cout << "Email:          " << users[i].email << endl;
        cout << "Adres:          " << users[i].address << endl;
    }

    system ("pause");
    system ("cls");
}

void saveAfterDeletion (vector <User> users)
{
    vector <User> ::iterator itr = users.begin();
    fstream fileAfterDeletion;
    fileAfterDeletion.open("ksiazka_adresowa.txt", ios::out | ios::trunc);
    if (fileAfterDeletion.good())
    {
        for (unsigned int i = 0; i < users.size(); i++)
        {
            fileAfterDeletion << itr->id << "|" << itr->name << "|" << itr->surname << "|" << itr->phone_number << "|" << itr->email << "|" << itr->address << endl;
        }
        fileAfterDeletion.close();
    }
    users.clear();
}

void deleteUser(vector <User> &users)
{
    User temporary1;
    vector <string> temp;
    string lineToDelete = "";
    vector <User> ::iterator itr = users.begin();

    cout << "Podaj numer ID adresata, ktorego chcesz usunac: ";
    int inputID = getInteger();

    for(unsigned int i = 0; i < users.size(); ++i)
    {
        if (users[i].id == inputID)
        {
            cout << "Wcisnij 't' jesli chcesz usunac uzytkownika: ";
            char input = inputSign();

            if(input == 't')
            {
                users.erase(users.begin() + i);
                cout << "Kontakt zostal usuniety" << endl;
                saveAfterDeletion(users);
            }
            else if (input != 't')
            {
                cout << "Wcisnales inny klawisz!";
            }
        }
    }
    system ("pause");
    system ("cls");
}

void overWriteFile (vector<User> users, vector<User>::iterator itr)
{
    fstream file, fileTemp;
    file.open("ksiazka_adresowa.txt", ios::in);
    fileTemp.open("temp.txt", ios::out);

    string line, userID;
    while(!file.eof())
    {
        getline(file,userID,'|');
        getline(file,line);
        if (itr -> id == atoi(userID.c_str()))
        {

            fileTemp << itr -> id << "|";
            fileTemp << itr -> name << "|";
            fileTemp << itr -> surname << "|";
            fileTemp << itr -> phone_number << "|";
            fileTemp << itr -> email << "|";
            fileTemp << itr -> address << endl;
        }

        else if (itr -> id == atoi(userID.c_str()))
        {
            continue;
        }
        else if (atoi(userID.c_str()))
        {
            fileTemp << userID + "|" + line << endl;
        }
    }
    file.close();
    fileTemp.close();

    remove("ksiazka_adresowa.txt");
    rename("temp.txt","ksiazka_adresowa.txt");
}


void editUser(vector <User> &users)
{
    int inputID;
    char option;
    string newData;
    cout << "Podaj ID kontaktu do edycji: ";
    cin >> inputID;

    for (vector<User>::iterator itr = users.begin(); itr != users.end(); itr++)
    {
        if (itr -> id == inputID)
        {
            while(true)
            {
                system("cls");
                cout << ">> WYBIERZ OPCJE EDYCJI <<" << endl;
                cout << "1. Edytuj imie" << endl;
                cout << "2. Edytuj nazwisko" << endl;
                cout << "3. Edytuj numer telefonu." << endl;
                cout << "4. Edytuj email" << endl;
                cout << "5. Edytuj adres" << endl;
                cout << "6. Powrot do Menu" << endl << endl;
                cout << "Twoj wybor: ";
                option = inputSign();

                switch (option)
                {
                case '1':
                {
                    cout << "Podaj nowe imie: ";
                    getline(cin, newData);
                    itr -> name = newData;
                    overWriteFile(users, itr);
                    cout << "Dane zostaly edytowane" << endl;
                    Sleep(1000);
                    continue;
                }

                case '2':
                {
                    cout << "Wprowadz nowe nazwisko: ";
                    getline(cin, newData);
                    itr -> surname = newData;
                    overWriteFile(users, itr);
                    cout << "Dane zostaly edytowane" << endl;
                    Sleep(1000);
                    continue;
                }

                case '3':
                {
                    cout << "Wprowadz nowy numer telefonu: ";
                    getline(cin, newData);
                    itr -> phone_number = newData;
                    overWriteFile(users, itr);
                    cout << "Dane zostaly edytowane" << endl;
                    Sleep(1000);
                    continue;
                }


                case '4':
                {
                    cout << "Wprowadz nowy email: ";
                    getline(cin, newData);
                    itr -> email = newData;
                    overWriteFile(users, itr);
                    cout << "Dane zostaly edytowane" << endl;
                    Sleep(1000);
                    continue;
                }

                case '5':
                {
                    cout << "Wprowadz nowy adres: ";
                    getline(cin, newData);
                    itr -> address = newData;
                    overWriteFile(users, itr);
                    cout << "Dane zostaly edytowane" << endl;
                    Sleep(1000);
                    continue;
                    break;
                }

                case '6':
                {
                    break;
                }
                }
                break;
            }
        }
    }
}

string getDataFromLine(string line, size_t previousPosition)
{
    string dataFromLine = "";
    size_t position = 0;
    position = line.find('|', previousPosition + 1);
    dataFromLine = line.substr(previousPosition + 1, position - previousPosition - 1);

    return dataFromLine;
}

void uploadAll(vector <User> &users)
{
    size_t position;
    fstream file;
    string line, dataFromLine = "";
    User userFromFile;

    file.open("ksiazka_adresowa.txt", ios::in);

    if(!file.good()) // tworzy plik nawet kiedy plik nie istnieje
    {
        file.open("ksiazka_adresowa.txt", ios::app);
        file.close();
    }

    while(getline(file, line))
    {
        position = -1;

        dataFromLine = getDataFromLine(line, position);
        userFromFile.id = stoi(dataFromLine);
        position += dataFromLine.length() + 1;

        dataFromLine = getDataFromLine(line, position);
        userFromFile.name = dataFromLine;
        position += dataFromLine.length() + 1;

        dataFromLine = getDataFromLine(line, position);
        userFromFile.surname = dataFromLine;
        position += dataFromLine.length() + 1;

        dataFromLine = getDataFromLine(line, position);
        userFromFile.phone_number = dataFromLine;
        position += dataFromLine.length() + 1;

        dataFromLine = getDataFromLine(line, position);
        userFromFile.email = dataFromLine;
        position += dataFromLine.length() + 1;

        dataFromLine = getDataFromLine(line, position);
        userFromFile.address = dataFromLine;
        position += dataFromLine.length() + 2;

        users.push_back(userFromFile);
    }

    file.close();
}

int main()
{
    vector <User> users;
    char option;
    uploadAll(users);

    while(true)
    {
        system("cls");
        cout << ">>> KSIAZKA ADRESOWA <<<" << endl << endl;
        cout << "1. Dodaj adresata" << endl;
        cout << "2. Wyszukaj po imieniu" << endl;
        cout << "3. Wyszukaj po nazwisku" << endl;
        cout << "4. Wyswietl wszystkich adresatow" << endl;
        cout << "5. Usun adresata" << endl;
        cout << "6. Edytuj adresata" << endl;
        cout << "9. Zakoncz program" << endl << endl;
        cout << "Twoj wybor: ";
        option = inputSign();

        switch (option)
        {
        case '1':
            addUser(users);
            break;

        case '2':
            searchUserByName(users);
            break;

        case '3':
            searchUserBySurname(users);
            break;

        case '4':
            showAll(users);
            break;

        case '5':
            deleteUser(users);
            break;

        case '6':
            editUser(users);
            break;

        case '9':
            cout << ">> Program zakonczyl prace <<" << endl;
            exit(0);
            break;
        }
    }
    return 0;
}

