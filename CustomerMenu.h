#pragma once

#ifndef CUSTOMER_MENU_H
#define CUSTOMER_MENU_H

#include <iostream>
#include <string>
#include <mysql.h>

using namespace std;

// Function prototypes
void CustomerMenu(MYSQL* conn, const std::string& username);
void ViewCustomerProfile(MYSQL* conn, const string& username);
void ViewInventory(MYSQL* conn);

// Declared with the parameter
//extern void ShowWelcomePage();

//cout << "Logging out...\n";
//ShowWelcomePage(); // Redirect to ShowWelcomePage from Project_IMS.cpp on logout
//return; // Exit the CustomerMenu loop


#endif

