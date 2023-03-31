/*

----- Automated Teller Machine -----

Programmed by: Shahad AlQarni

This program is a simulation of automated teller machine (ATM)

*/

#include "ATM_H.h"

void ATM();

int main() {
	
	ATM();
	
	return 0;
} //end of main

void ATM(){
	
	/* Customers Accounts Information */
	vector <Account> cstmrs;
//______________________________________________________________________
	//1st Customer:		ID			PIN		Name			Balance
	cstmrs.push_back( {"11008899", "1111", "Mohammad Basem", 1500.75} );
	
	//Bills info:			   Serial	ReleaseDate	 Amount	 Paid
	cstmrs[0].bills.push_back( {"12348", {1,1,2023}, 500.0, false} );
	cstmrs[0].bills.push_back( {"12999", {12,12,2022}, 1000.0, false} );
//______________________________________________________________________
	//2nd Customer:		ID			PIN		Name			Balance
	cstmrs.push_back( {"88190287", "1234", "Khalid Faisal", 8000.50} );
	
	//Bills info:			   Serial	ReleaseDate	 Amount	 Paid
	cstmrs[1].bills.push_back( {"13111", {1,1,2020}, 2000.0, true} );
//______________________________________________________________________
	//3rd Customer:		ID			PIN		Name		Balance
	cstmrs.push_back( {"99880077", "8765", "Omar Ahmad", 100.70} );
//______________________________________________________________________

	/* Rest of Variables */
	char service, cont; //for user choices
	int cstmr_index;
	
	/* Output Beginning */
	cout << "\n*-*-*-*-*-*-*-\tWelcome to ATM\t-*-*-*-*-*-*-*\n\n"
		 << "----------------------------------------------\n"
		 << "    Enter your card then press any key... ";
	cin.get();
	cout << "----------------------------------------------\n";
	cstmr_index = login(cstmrs); //get the index of current customer
	
	do{
		menu_label:
			print_menu();
			cin >> service; //to choose a service
		
		switch(service){
			case '1':
				deposit( cstmrs[cstmr_index] );
				break;
				
			case '2':
				withdrawal( cstmrs[cstmr_index] );
				break;
				
			case '3':
				transfer( cstmrs, cstmr_index );
				break;
				
			case '4':
				add_beneficiary(cstmrs, cstmr_index);
				break;
				
			case '5':
				pay( cstmrs[cstmr_index] );
				break;
				
			case '6':
				viewInfo( cstmrs[cstmr_index] );
				break;
				
			case '0':
				goto end_label;
				
			default:
				cout << " Enter a valid option\n";
				goto menu_label;
		} //end of switch
		
		cout << "\n Other service? \n"
			 << " 1. Yes	2. No \n ";
		cin >> cont;
	} //end of do-while
	while(cont == '1');
	
	end_label:
	cout << "\n----------------------------------------------\n"
		 << "\tThank you .. Take your card\n";
	
} //end of ATM