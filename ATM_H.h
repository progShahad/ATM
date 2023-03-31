#ifndef ATM_H
#define ATM_H

// Include Directives:
#include <iostream>
#include <string>
#include <vector>
#include <chrono>
#include <thread>
using namespace std;

// Global Variables & Constants:
const double MAX_TRANSFER = 50000.0;

// Structs:
struct Beneficiary{
	int serial;
	string account_ID, short_name, full_name;
};

struct Date{
	int day, month, year;
};

struct Bill{
	string serial_num;
	Date release_date;
	double amount;
	bool paid;
};

struct Account{
	string account_ID, PIN, name;
	double balance;
	vector <Beneficiary> bene;
	vector <Bill> bills;
};

// Functions Prototypes / Declarations:
int search(vector <Account> cstmrs, string id);
int search(Account cstmr, string id);
void add_beneficiary(vector <Account> & cstmrs, int cstmr_index);
bool check_balance(Account cstmr, double & amount);
bool confirm(Account cstmr);
void deposit(Account & cstmr);
void withdrawal(Account & cstmr);
void transfer(vector <Account> & cstmrs, int cstmr_index);
bool viewBills(Account cstmr);
void pay(Account & cstmr);
int login(vector <Account> cstmr);
void viewInfo(Account cstmr);
void print_menu();

#endif