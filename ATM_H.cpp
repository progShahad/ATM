#include "ATM_H.h"

// Functions Definitions:
int search(vector <Account> cstmrs, string id){ //to search for the account in the bank system
	for(int i=0 ; i < cstmrs.size() ; i++)
		if(cstmrs[i].account_ID == id)
			return i;
	return -1;
}

int search(Account cstmr, string id){ //to search in the customer's beneficiaries
	for(int i=0 ; i < cstmr.bene.size() ; i++)
		if(cstmr.bene[i].account_ID == id)
			return cstmr.bene[i].serial;
	return -1;
}

void add_beneficiary(vector <Account> & cstmrs, int cstmr_index){ //to add a new beneficiary to a particular customer
	string id, name;
	int benef_index;
	char activate, trans;
	
	cout << "\n Enter the beneficiary information:\n"
		 << "- Account number:  ";
	cin >> id;
	cout << "- Beneficiary name:  ";
	cin.ignore();
	getline(cin, name);
	
	// search
	check_label:
		if(id == cstmrs[cstmr_index].account_ID){ //matches the current user's ID
			cout << "\n You cannot add yourself as a beneficiary!";
			goto id_label; //skip 8 lines next
		}
		else if( search(cstmrs[cstmr_index], id) >= 0 ){ //matches existing beneficiary
			cout << "\n The beneficiary already exists";
			goto id_label; //skip 4 lines next
		}
		//when ID passes the tests, the search is performed
		benef_index = search(cstmrs, id);
		if( benef_index < 0 ){
			cout << "\n There is no account with the entered ID number";
			id_label:
			cout << "\n Enter a correct number or x to exit\n\n";
			
			cout << "- Account number:  ";
			cin >> id;
			cout << "- Beneficiary name:  ";
			cin.ignore();
			getline(cin, name);
			
			if(id == "x" || id == "X")
				return;
			goto check_label;
		}
	
	cout << "\n ----- Beneficiary Info -----\n"
		 << " ID Number:\t" << cstmrs[benef_index].account_ID << '\n'
		 << " Full Name:\t" << cstmrs[benef_index].name << '\n'
		 << " Short Name:\t" << name << '\n';
	
	cstmrs[cstmr_index].bene.push_back( {(int)cstmrs[cstmr_index].bene.size()+1 , id, name, cstmrs[benef_index].name} );
	
	cout << "\n Added, enter 1 to activate the beneficiary:  ";
	cin >> activate;
	
	while(activate != '1'){
		cout << "Enter 1 to activate:  ";
		cin >> activate;
	}
	cout << "\n-------- Activated succssfully --------\n";
	
	cout << " If you want to transfer to this beneficiary, enter 1:  ";
	cin >> trans;
	if(trans == '1')
		transfer(cstmrs, cstmr_index);
	
} //end of add_beneficiary

bool check_balance(Account cstmr, double & amount){ //to check whether the balance of a particular customer is enough
	if(amount <= cstmr.balance && amount > 0) //enough
		return true; //pass
	else{
		if(amount <= 0)
			cout << "\n The entered amount is invalid..";
		else
			cout << "\n Your balance is not enough..";
		
		cout << "\n\n Enter another amount, or negaive number to cancel:  ";
		cin >> amount;
		if(amount < 0)
			return false; //cancel
		return check_balance(cstmr, amount); //re-check
	}
} //end of check_balance

bool confirm(Account cstmr){ //to confirm a process using confirmation option and PIN verification
	short confirmed, attempt = 0;
	string pin;
	
	// Transaction confirmation
	cout << "\n If you are sure, enter 1\n";
	cin >> confirmed;
	
	if(confirmed == 1){
		// PIN verification
		cout << "\n Confirm the PIN to continue:\n";
		cin >> pin;
		while( pin != cstmr.PIN ){
			if(++attempt == 3)
				return false;
			cout << "\n Wrong PIN, try again:  ";
			cin >> pin;
		}
		return true;
	}
	else{
		return false;
	}
} //end of confirm

void deposit(Account & cstmr){ //perform a deposit into the customer's account
	char option;
	int depAmount;
	
	amount_label:
		cout << "\n The amount to deposit: \n"
			 << " 1. 50\t\t2. 100 \n"
			 << " 3. 1000\t4. Other \n"
			 << " 0. Exit (back to menu)\n ";
		cin >> option;
	
	if(option < '4' && option > '0'){
		cin.ignore();
		cout << "\n Enter the money then press any key...";
		cin.get();
	}
	
	switch(option){
		case '0':
			return;
		case '1':
			cstmr.balance += 50;
			break;
		case '2':
			cstmr.balance += 100;
			break;
		case '3':
			cstmr.balance += 1000;
			break;
		case '4':
			cout << "\n Enter the amount:  ";
			cin >> depAmount;
			
			while(depAmount % 50 != 0){ //valid amount must be divisible by 5
				cout << depAmount << " cannot be deposited, try again or enter 0 to exit:  ";
				cin >> depAmount;
				if(depAmount == 0)
					return;
			}
			entering_label:
				cin.ignore();
				cout << "\n Enter the money then press any key...";
				cin.get();
			
			cstmr.balance += depAmount;
			break;
			
		default:
			cout << " Invalid option, try again..\n ";
			goto amount_label;
	}
	
	cout << "\n-------- Deposited --------\n ";
	
} //end of deposit

void withdrawal(Account & cstmr){ //perform a withdrawal from the customer's account
	char option;
	int amount;
	
	amount_label:
	cout << "\n Amount to be withdrawn:\n"
		 << "   1. 50\t 2. 100 \n"
		 << "   3. 1000\t 4. Other \n"
		 << "   0. Exit (back to menu)\n";
	cin >> option;
	
	switch(option){
		case '0':
			cout << "\n-------- Canceled --------\n";
			return;
			
		case '1':
			amount = 50;
			break;
			
		case '2':
			amount = 100;
			break;
			
		case '3':
			amount = 1000;
			break;
			
		case '4':
			cout << " Enter the amount:  ";
			cin >> amount;
			
			while(amount % 50 != 0 || amount < 50){
				cout << " It must be divisible by 50, enter again:  ";
				cin >> amount;
			}
			break;
			
		default:
			cout << " Invalid option, try again\n ";
			goto amount_label;
	} //end of switch
	
	if(cstmr.balance < amount){
		cout << "\n Your balance is not enough..\n";
		goto amount_label;
	}
	
	// Transaction confirmation
	if( !confirm(cstmr) ){
		cout << "\n-------- Process is canceled --------\n";
		return;
	}
	
	//if we have reached here, so the amount is valid, complete the process
	cstmr.balance -= amount;
	cout << "------ Success, you can take your money ------\n ";
	
} //end of withdrawal

void transfer(vector <Account> & cstmrs, int cstmr_index){ //perform a transfer to another account
	string serial_num;
	bool found = false;
	int add, benef_index;
	double amount;
	
	// to
	cout << "\n Enter the serial number of the account transferred to:\n ";
	cin >> serial_num;
	
	while( serial_num == cstmrs[cstmr_index].account_ID ){
		cout << "\n You cannot transfer to yourself!"
			 << "\n Enter another number:\n";
		cin >> serial_num;
	}
	// Search for the beneficiary in the customer account
	benef_index = search(cstmrs[cstmr_index], serial_num);
	
	if( benef_index >= 0 ){
		amount_label:
		cout << "\n Enter the amount:  ";
		cin >> amount;
		
		if(amount > MAX_TRANSFER){
			cout << "\n The limit of transferred amount is " << MAX_TRANSFER << " SR\n";
			goto amount_label; //re-enter
		}
		
		if( !check_balance(cstmrs[cstmr_index], amount) ){ //transfer canceled
			cout << "\n-------- Process is canceled --------\n";
			return;
		}
		
		// Transaction confirmation
		if( !confirm(cstmrs[cstmr_index]) ){
			cout << "\n-------- Process is canceled --------\n";
			return;
		}
		
		/* process of transfer */
		cstmrs.at(cstmr_index).balance -= amount;
		cstmrs.at(benef_index).balance += amount;
		cout << "\n-------- Transferred successfully --------\n";
	} //end if
	else{
		cout << "\n xx You do not have a beneficiary with this number..\n"
			 << " Do you want to add it ? Enter 1:\n";
		cin >> add;
		if(add == 1)
			add_beneficiary(cstmrs, cstmr_index);
	}
	
} //end of transfer

bool viewBills(Account cstmr){ //view a particular customer bills
	cout << "\n ___________  Your Bills  ___________\n";
	
	if(cstmr.bills.size() == 0){
		cout << "\n You have no bills yet \n";
		return false;
	}
	
	for(int i=0 ; i < cstmr.bills.size() ; i++){
		cout << "\n _____________ Bill " << (i+1) << " _____________\n\n"
			 << " Serial number:\t\t" << cstmr.bills.at(i).serial_num << '\n'
			 << " Date of release:\t" << cstmr.bills.at(i).release_date.day << '/'
			 						 << cstmr.bills.at(i).release_date.month << '/'
									 << cstmr.bills.at(i).release_date.year << '\n'
			 << " Amount to be paid:\t" << cstmr.bills.at(i).amount << '\n'
			 << " Status:\t\t" << (cstmr.bills.at(i).paid ? "Paid" : "Not paid") << '\n';
	}
	cout << "\n __________________________________\n";
	return true;
} //end of viewBills

void pay(Account & cstmr){ //pay customer bills
	if( !viewBills(cstmr) )
		return; //no bills
	
	int bill_no;
	double amount;
	short pay_whole;
	
	cout << "Enter bill number to pay:  ";
	cin >> bill_no;
	
	while( bill_no <= 0 || bill_no > cstmr.bills.size() ){
		cout << "\nInvalid number, enter again or negative number to cancel:  ";
		cin >> bill_no;
		if(bill_no < 0)
			return;
	}
	bill_no -= 1;
	
	if(cstmr.bills.at(bill_no).amount == 0){
		cout << "\nThis bill is paid completely \n";
		return;
	}
	
	cout << "\nEnter the amount to pay:  ";
	cin >> amount;
	
	while(true){
		if(cstmr.balance < amount){
			cout << "\nYour balance is not enough\n"
				 << "Enter another amount";
		}
		else if(amount > cstmr.bills.at(bill_no).amount){
			cout << "\nThe entered amount is greater than the bill amount\n"
				 << "Do you want to pay the whole amount of bill (" << cstmr.bills.at(bill_no).amount << " SR) ? Enter 1 \n";
			cin >> pay_whole;
			
			if(pay_whole == 1){
				amount = cstmr.bills.at(bill_no).amount;
				break;
			}
			else{
				cout << "Enter another amount";
			}
		}
		else if(amount <= 0)
			cout << "\nEnter a valid amount";
		else //valid amount, go to the next
			break;
		
		cout << ", or negative number to cancel:\n";
		cin >> amount;
		
		if(amount < 0)
			return;
	} //end of while loop
	
	// Transaction confirmation
	if( !confirm(cstmr) ){
		cout << "\n-------- Process is canceled --------\n";
		return;
	}
	
	// Perform
	cstmr.balance -= amount;
	cstmr.bills.at(bill_no).amount -= amount;
	
	if(cstmr.bills.at(bill_no).amount == 0)
		cstmr.bills.at(bill_no).paid = true;
	
	cout << "\n-------- Paid successfully --------\n";
	
} //end of pay

int login(vector <Account> cstmr){ //login to the customer account
	string id, pin;
	bool found = false;
	int attempt = 0, cstmr_index;
	
	cout << "\n  Please enter account ID:  ";
	cin >> id;
	cout << "  PIN: ";
	cin >> pin;
	
	do{
		for(int i=0 ; i < cstmr.size() ; i++)
			if( id == cstmr[i].account_ID && pin == cstmr[i].PIN ){
				found = true;
				cstmr_index = i;
				break;
			}
		
		if( !found ){
			if( ++attempt == 3 ){
				cout << "\n You have exceeded the number of attempts allowed, wait a minute and try again..\n\n";
				this_thread::sleep_for(chrono::milliseconds(60*1000)); //wait a minute
				attempt = 0;
				goto re_enter;
			}
			cout << "\n Wrong ID/PIN, try again:\n";
			re_enter:
			cout << "  ID: ";
			cin >> id;
			cout << "  PIN: ";
			cin >> pin;
		}
		
	}
	while(!found);
	
	cout << " \n----------------------------------------------\n"
		 << "  Welcome " << cstmr[cstmr_index].name << '\n';
	
	return cstmr_index;
} //end of login

void viewInfo(Account cstmr){ //information about a particular account
	cout << "\n-------- Account Information ---------\n"
		 << " Account ID:\t" << cstmr.account_ID << '\n'
		 << " Name:\t\t" << cstmr.name << '\n'
		 << " Balance:\t" << cstmr.balance << " SR \n"
		 << "--------------------------------------\n";
} //end of viewInfo

void print_menu(){ //the home menu
	cout << "\n  Select a service:\n"
		 << "   1. Deposit \t 2. Withdrawal \n"
		 << "   3. Transfer \t 4. Add a beneficiary \n"
		 << "   5. Pay your bills \n"
		 << "   6. View account information \n"
		 << "   0. Exit \n ";
} //end of print_menu