#include <iostream>
#include <sstream>
#include <fstream>
#include <string>
#include <vector>
#include <regex>

using namespace std;

 vector<int> PrimeGenerator(int amount) {
    vector<int> primes;
    int num = 1;
    int finds = 0;
    while (finds < amount) {
        num++;
        int i = 0;
        for (; i < finds; i++) {
            if (num % primes[i] == 0) { break; }
        }
        if (i == finds) {
            primes.push_back(num);
            finds++;
        }
    }
    primes.shrink_to_fit();
    return primes;
}

 void ExportToTXT(string content) {
     string name = "";
     regex nameValidation(R"((?!^(CON|PRN|AUX|NUL|COM[1-9]|LPT[1-9])(\..*)?$)^[^<>:"/\\|?*]+$)");
     bool validName = false;
     do {
         cout << "Input export filename: ";
         getline(cin, name);
         if (!regex_match(name, nameValidation)) {
             cout << "Invalid filename!\n";
             cin.clear();
             cin.ignore(numeric_limits<streamsize>::max(), '\n');
         }
         else { validName = true; }
     } while (!validName);

     ofstream file(name + ".txt");
     file << content;
     file.close();
 }

int main()
{
    while (true) {
        system("cls");
        int amount = 0;
        bool validAmount = false;
        do {
            cout << "How many prime numbers should be generated? ";
            cin >> amount;
            if (cin.fail()) {
                cout << "Invalid input!\n";
                cin.clear();
                cin.ignore(numeric_limits<streamsize>::max(), '\n');
            }
            else { validAmount = true; }
        } while (!validAmount);

        vector<int> primes = PrimeGenerator(amount);

        char choice = 'n';
        bool validChoice = false;

        string output = "";
        for (int prime : primes) {
            output += to_string(prime) + ", ";
        }
        cout << output << "\n";

        do {
            cout << "Do you want to export the output into a txt file? (y/n) ";
            cin >> choice;
            if (cin.fail()) {
                cin.clear();
                cin.ignore(numeric_limits<streamsize>::max(), '\n');
            }
            else {
                switch (tolower(choice)) {
                case 'y': ExportToTXT(output); break;
                case 'n': break;
                default: cout << "Please input y or n!\n"; continue;
                }
                validChoice = true;
            }
        } while (!validChoice);
    }
    return 0;
}
