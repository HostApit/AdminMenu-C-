#pragma once

#ifndef ADMIN_MENU_H
#define ADMIN_MENU_H

#include <iostream>
#include <string>
#include <mysql.h>

using namespace std;

// Function prototypes for Admin Menu
void AdminMenu(MYSQL* conn, const std::string& username);
void ViewAdminProfile(MYSQL* conn, const string& username);
void UpdateAdminProfile(MYSQL* conn, const string& username);

// Function Manage Inventory
void ViewInventory(MYSQL* conn);
void ManageInventory(MYSQL* conn);

// Function Manage Customer
void ManageCustomerProfiles(MYSQL* conn);

// Function Manage Staff
void ManageStaffProfiles(MYSQL* conn);

// Function Manage Supplier
void ManageSuppliers(MYSQL* conn);
void CompareSuppliers(MYSQL* conn);

// Function Generate Sales Report
//void GenerateSalesReport(MYSQL* conn);
void GenerateDetailedReports(MYSQL* conn);

// Function prototypes for updating the admin profile
void UpdateAdminProfile(MYSQL* conn, const string& username);

#endif
