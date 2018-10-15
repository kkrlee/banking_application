#include <iostream>
#include <fstream>
#include <list>
#include <string>
#include <iterator>
#include <vector>
#include <cstdio>
#include <algorithm>
using namespace std;
struct customer
{
    string my_name;
    string account_number;
    int my_pin;
    double my_money;
    customer(string name, string number, int pin, double money);
};
customer::customer(string name, string number, int pin, double money)
{
    my_name = name;
    account_number = number;
    my_pin = pin;
    my_money = money;
}
class bank_system
{

    string tmp_number;
    string tmp_name;
    string error;
    int tmp_pin;
    int number_of_accounts;
    int n;
    double tmp_money;
    list<customer> customer_base;

  public:
    bank_system();
    void add_customer(string name);
    void delete_customer(string name, string number);
    void show_all_base();
    void transfer_money(string name1, string name2, string number1, string number2, double sum);
    void saving();
    void help();
};
bank_system::bank_system()
{
    number_of_accounts = 0;
    ifstream inf("base.txt");
    do
    {
        inf >> n;
        if (n == 0)
        {
            return;
        }
        inf >> tmp_name;
        inf >> tmp_number;
        inf >> tmp_pin;
        inf >> tmp_money;
        if (n > number_of_accounts)
            number_of_accounts = n;
        customer_base.push_back(customer(tmp_name, tmp_number, tmp_pin, tmp_money));
        tmp_name = "";
        tmp_number = "";

    } while (n);
    inf.close();
}
void bank_system::help()
{
    cout << "Welcome to transfering system!" << endl;
    cout << "To add a customer to system, press 1." << endl;
    cout << "Here you have to insert a name of customer, the bank account and pin will be generated automatically." << endl;
    cout << "To delete a customer from system, press 2." << endl;
    cout << "Here you have to enter a name, and the customer with such name and account will be removed from the system." << endl;
    cout << "To display all base on the screen, press 3." << endl;
    cout << "To transfer money from one account to another, you have to enter this information:" << endl;
    cout << "Name of customer who tranfers," << endl;
    cout << "Name of customer who receives," << endl;
    cout << "Account number of customer who transfers," << endl;
    cout << "Account number of customer who receives," << endl;
    cout << "Sum you want to transfer." << endl;
    cout << "Notice! If it's not enough money on transfer customer's account, error will be displayed!" << endl;
    cout << "How does the system work" << endl;
    cout << "Each time you launch the programm, the file base.txt is loaded automatically, so you always can get access to base." << endl;
    cout << "After you have done all the changes, you can press either 6 or 7." << endl;
    cout << "If you want to save changes press 6, if not press 7.";
    cout << "All transaction are recorded in transfer.txt with all info about transaction e.g. names, sum, time." << endl;
    cout << "If you get errors while displaying the base first time you launched the programm, try to write 0 to the file base.txt and re-launch the programm." << endl;
}
void bank_system::add_customer(string name)
{
    srand(time(NULL));
    tmp_pin = rand() % 9000 + 1000;
    tmp_number = to_string(rand() % 9000 + 1000) + to_string(rand() % 9000 + 1000) + to_string(rand() % 9000 + 1000) + to_string(rand() % 9000 + 1000);

    cout << "How much money would you like to put on this account?\n";
    cin >> tmp_money;
    customer_base.push_back(customer(name, tmp_number, tmp_pin, tmp_money));
    number_of_accounts++;
    tmp_number = "";
    tmp_pin = 0;
}
void bank_system::delete_customer(string name, string number)
{
    if (!number_of_accounts)
    {
        cout << "No customers yet" << endl;
        return;
    }
    auto list_it = customer_base.begin();
    bool is_deleted = false;
    bool is_found = false;
    for (list_it; list_it != customer_base.end();)
    {
        if (name == list_it->my_name)
        {
            is_found = true;
            if (list_it->account_number == number)
            {
                list_it = customer_base.erase(list_it);
                is_deleted = true;
            }
        }
        else
            ++list_it;
    }
    if(!is_found)
    {
          cout<<"No such name!"<<endl;
          if(!is_deleted)
          {
              cout<<"No such account number"<<endl;
              return;
          }
    }
    number_of_accounts--;
}
void bank_system::show_all_base()
{
    auto list_it = customer_base.begin();
    if (number_of_accounts)
    {
        for (list_it; list_it != customer_base.end(); ++list_it)
        {
            cout << "Name: " << list_it->my_name << endl;
            cout << "Account number: " << list_it->account_number << endl;
            cout << "PIN " << list_it->my_pin << endl;
            cout << "Bankroll " << list_it->my_money << endl;
            cout << endl;
        }
    }
    else
    {
        cout << "No customers yet" << endl;
    }
    cout << "Total customers: " << number_of_accounts << endl;
}
void bank_system::saving()
{
    auto list_it = customer_base.begin();
    n = 0;
    if (number_of_accounts)
    {
        ofstream outfile("base.txt", ios_base::trunc);
        for (list_it; list_it != customer_base.end(); ++list_it)
        {
            n++;
            outfile << n << "\n";
            outfile << list_it->my_name << "\n";
            outfile << list_it->account_number << "\n";
            outfile << list_it->my_pin << "\n";
            outfile << list_it->my_money << "\n";
        }
        outfile << 0;
        outfile.close();
    }
}
void bank_system::transfer_money(string name1, string name2, string number1, string number2, double sum)
{
    auto list_it = customer_base.begin();
    n = 0;
    bool check1, check2 = false;
    if (number_of_accounts)
    {
        if (number1 == number2)
        {
            error = "Numbers shouldn't be the same!\n";
            cout << error << endl;
            return;
        }
        for (list_it; list_it != customer_base.end(); ++list_it)
        {
            if ((list_it->my_name) == name1)
            {
                if ((list_it->account_number) == number1)
                {
                    if ((list_it->my_money) >= sum)
                        check1 = true;
                    else
                        error += "Not enough money on transfer's account!\n";
                }
                else
                {
                    error += "Incorrect account(1) number!\n";
                }
            }
            if (list_it->my_name == name2)
            {
                if (list_it->account_number == number2)
                {
                    check2 = true;
                }
                else
                {
                    error += "Incorrect account(2) number!\n";
                }
            }
        }
        if (!check1)
            error += "No such name(1) in base!\n";
        if (!check2)
            error += "No such name(2) in base!\n";
        if (check1 && check2)
        {
            auto it = customer_base.begin();
            for (it; it != customer_base.end(); ++it)
            {
                if (it->account_number == number1)
                {
                    it->my_money -= sum;
                }
                if (it->account_number == number2)
                {
                    it->my_money += sum;
                }
            }
            string date;

            struct tm *cur_time;
            time_t tt;
            time(&tt);
            cur_time = localtime(&tt);
            int year, month, day, hour, minute, sec;
            string res_date;

            year = cur_time->tm_year + 1900;
            month = 1 + (cur_time->tm_mon);
            day = cur_time->tm_wday;
            hour = cur_time->tm_hour;
            minute = cur_time->tm_min;
            sec = cur_time->tm_sec;

            date = to_string(year) + "/" + to_string(month) + "/" + to_string(day) + "/" + to_string(hour) + ":" + to_string(minute) + ":" + to_string(sec) + "\n";

            ofstream out("transfers.txt", ios_base::app);
            out << "Transfer from: " << name1 << endl;
            out << "Transfer to: " << name2 << endl;
            out << "Sum: " << sum << endl;
            out << "Date: " << date << endl;
            out.close();
            cout << "Transfered succesfully!" << endl;
        }
        else cout<<error;
    }
}
int main()
{
    bank_system my_system;
    string number1, number2, name, name1, name2;
    double sum;
    bool correct_input = true;
    int choice = 0;
    do
    {
        cout << "1. Add customer" << endl;
        cout << "2. Delete customer" << endl;
        cout << "3. Show all base" << endl;
        cout << "4. Transfer money" << endl;
        cout << "5. HELP" << endl;
        cout << "6. Exit (save everything)" << endl;
        cout << "7. Exit (without saving)" << endl;

        cin >> choice;
        cin.ignore(7777, '\n');

        switch (choice)
        {
        case 1:
        {
            cout << "Enter name, please" << endl;
            getline(cin, name);
            my_system.add_customer(name);
            cin.clear();
            break;
        }
        case 2:
        {
            cout << "Enter customer's account name and number you want to delete, please" << endl;
            getline(cin, name);
            getline(cin, number1);
            my_system.delete_customer(name, number1);
            cin.clear();
            break;
        }
        case 3:
        {
            my_system.show_all_base();
            cin.clear();
            break;
        }
        case 4:
        {
            cout << "Enter name of customer you want transfer money from,\n";
            cout << "Enter a name of customer you want transfer money to\n";
            cout << "Enter account number of customer you want transfer money from,\n";
            cout << "Enter account number of customer you want transer mone to\n";
            cout << "Enter sum\n";
            cin >> name1 >> name2 >> number1 >> number2 >> sum;
            my_system.transfer_money(name1, name2, number1, number2, sum);
            break;
        }
        case 5:
        {
            my_system.help();
            break;
        }
        case 6:
        {
            my_system.saving();
            return 0;
        }
        case 7:
            return 0;
        default:
        {
            cout << "INVALID INPUT!" << endl;
            break;
        }
        }
    } while (choice < 8);
}