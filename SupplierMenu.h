#pragma once

#ifndef SUPPLIER_MENU_H
#define SUPPLIER_MENU_H

#include <iostream>
#include <string>
#include <mysql.h>

using namespace std;

// Function prototypes for Supplier Menu
void SupplierMenu(MYSQL* conn);
void ViewAllSuppliers(MYSQL* conn);
void AddSupplier(MYSQL* conn);
void UpdateSupplier(MYSQL* conn);
void DeleteSupplier(MYSQL* conn);

#endif
