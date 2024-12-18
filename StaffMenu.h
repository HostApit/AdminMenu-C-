#pragma once

#ifndef STAFF_MENU_H
#define STAFF_MENU_H

#include <iostream>
#include <string>
#include <mysql.h>

using namespace std;

// Function prototypes
void StaffMenu(MYSQL* conn, const std::string& username);
void ViewStaffProfile(MYSQL* conn, const string& username);
void ManageInventoryStaff(MYSQL* conn);
void ManageSuppliersStaff(MYSQL* conn);
void GenerateSalesReport(MYSQL* conn);

// Function prototypes for updating and deleting the staff profile
void UpdateStaffProfile(MYSQL* conn, const string& username);


#endif
