// BANK PROGRAM.cpp : Defines the entry point for the console application.
//
// for skiping the strcat warnings 

#define _CRT_SECURE_NO_WARNINGS
#ifdef _MSC_VER
#define _CRT_SECURE_NO_WARNINGS
#endif
#include "stdafx.h"
#include <iostream>
using namespace std;
#include <boost\timer.hpp>
using namespace boost;
#include <string>
#include <mysql.h>
#include "admin.h"
#include "client.h"
#include "account.h"
#include "employee.h"

// connections deatails
char *server = "localhost";
char *username = "root";
char *password = "toor";
char *database = "bank";

MYSQL *conn;
MYSQL_RES *res;
MYSQL_ROW  row;

//*****************************

// we declare class for each table

class admin : public account
{
public:
	char id[15];

	void withdraw() {}
	void check() {}
	void transfare() {}
	void show() {

		     // select statment


		if (mysql_query(conn, "select * from account")) {
			cout << stderr << endl << mysql_errno(conn);
			return;
		}

		res = mysql_use_result(conn);
		cout << "\t id:" << "\taccount type:" << "\tmoney" << endl;
		while ((row = mysql_fetch_row(res)) != NULL) {
			cout << "\t" << row[0] << "\t" << row[1] << "\t" << row[2] << endl;
		}


	}

	// under development
	void createAccount(char accounttype[], char money[]) {

		char q[300] = "insert into account('accountid' , 'accounttype' , 'money')values('";
		strcat(q, accountid);
		strcat(q, "','");
		strcat(q, accounttype);
		strcat(q, "'");
		strcat(q, ",'");
		strcat(q, money);
		strcat(q, "')");
		mysql_query(conn, q);

	}
	void DeleteAccount() {}
};

int main()
{

	// initail connectionn to mysql server
	conn = mysql_init(NULL);

	if (! mysql_real_connect(conn, server, username, password, database, 0, NULL, 0)) {
		cout << stderr << "\n" << mysql_errno(conn);
		return -1;
	}


	// the menue of the program

	int index = 0;

	while (index != 5) {
		cout << "WELCOME TO THE BANK DEVELOPER EMPLOYEE\nIN THIS SYSTEM YOU ARE ALLOWED ONLY TO ADD ACCOUNTS AND SEE THE LIST OF ACCOUNTS";
		cout << endl<<"\n ENTER 1 FOR ADDING ACCOUNT \n ENTER 2 FOR LISTING THE ACCOUNTS\n";
		cin >> index;

		switch (index) {
		case 1: {
			
			char accounttype[15];
			char money[100];

			cout << "\n ENTER THE TYPE\n";
			cin >> accounttype;
			cout << "\n ENTER THE MONEY\n";
			cin >> money;
			admin adm;
			adm.createAccount(accounttype, money); break; }
		case 2: {
			admin ad;
			ad.show();
			break;
		}
		default: cout << "EXIT"; break;
		}
	}
	system("pause");
    return 0;
}

