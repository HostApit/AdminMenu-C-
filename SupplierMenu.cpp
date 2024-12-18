#include "SupplierMenu.h"
#include <iomanip> // For output formatting

void SupplierMenu(MYSQL* conn) {
    int choice;

    do {
        cout << "\n--- Supplier Management ---\n";
        cout << "1. View All Suppliers\n";
        cout << "2. Add New Supplier\n";
        cout << "3. Update Supplier Details\n";
        cout << "4. Delete Supplier\n";
        cout << "5. Return to Admin Menu\n";
        cout << "Please select an option (1-5): ";
        cin >> choice;

        switch (choice) {
        case 1:
            ViewAllSuppliers(conn);
            break;
        case 2:
            AddSupplier(conn);
            break;
        case 3:
            UpdateSupplier(conn);
            break;
        case 4:
            DeleteSupplier(conn);
            break;
        case 5:
            cout << "Returning to Admin Menu...\n";
            return;
        default:
            cout << "Invalid choice! Please try again.\n";
        }
    } while (choice != 5);
}

void ViewAllSuppliers(MYSQL* conn) {
    string query = "SELECT * FROM supplier_menu;";
    if (mysql_query(conn, query.c_str()) == 0) {
        MYSQL_RES* res = mysql_store_result(conn);
        MYSQL_ROW row;

        cout << "\n--- Suppliers ---\n";
        cout << left << setw(10) << "ID"
            << setw(25) << "Name"
            << setw(15) << "Phone"
            << setw(25) << "Email"
            << setw(30) << "Address"
            << setw(10) << "Discount Rate\n";
        cout << string(115, '-') << endl;

        while ((row = mysql_fetch_row(res))) {
            cout << left << setw(10) << row[0]
                << setw(25) << row[1]
                << setw(15) << row[2]
                << setw(25) << row[3]
                << setw(30) << row[4]
                << setw(10) << row[5] << "\n";
        }
        mysql_free_result(res);
    }
    else {
        cerr << "Error fetching suppliers: " << mysql_error(conn) << endl;
    }
}

void AddSupplier(MYSQL* conn) {
    string name, phone, email, address;
    double discount_rate;

    cout << "\n--- Add New Supplier ---\n";
    cout << "Enter Supplier Name: ";
    cin.ignore();
    getline(cin, name);
    cout << "Enter Phone Number: ";
    getline(cin, phone);
    cout << "Enter Email: ";
    getline(cin, email);
    cout << "Enter Address: ";
    getline(cin, address);
    cout << "Enter Discount Rate (%): ";
    cin >> discount_rate;

    string query = "INSERT INTO supplier_menu (name_supplier, phone_supplier, email_supplier, address_supplier, discount_rate) VALUES ('"
        + name + "', '" + phone + "', '" + email + "', '" + address + "', " + to_string(discount_rate) + ");";

    if (mysql_query(conn, query.c_str()) == 0) {
        cout << "Supplier added successfully!\n";
    }
    else {
        cerr << "Error adding supplier: " << mysql_error(conn) << endl;
    }
}

void UpdateSupplier(MYSQL* conn) {
    string supplier_id, field, new_value;

    cout << "\n--- Update Supplier Details ---\n";
    cout << "Enter Supplier ID: ";
    cin >> supplier_id;
    cout << "Enter the field to update (name_supplier, phone_supplier, email_supplier, address_supplier, discount_rate): ";
    cin >> field;
    cin.ignore();
    cout << "Enter the new value: ";
    getline(cin, new_value);

    string query = "UPDATE supplier_menu SET " + field + " = '" + new_value + "' WHERE supplier_id = " + supplier_id + ";";

    if (mysql_query(conn, query.c_str()) == 0) {
        cout << "Supplier details updated successfully!\n";
    }
    else {
        cerr << "Error updating supplier: " << mysql_error(conn) << endl;
    }
}

void DeleteSupplier(MYSQL* conn) {
    string supplier_id;

    cout << "\n--- Delete Supplier ---\n";
    cout << "Enter Supplier ID: ";
    cin >> supplier_id;

    string query = "DELETE FROM supplier_menu WHERE supplier_id = " + supplier_id + ";";

    if (mysql_query(conn, query.c_str()) == 0) {
        cout << "Supplier deleted successfully!\n";
    }
    else {
        cerr << "Error deleting supplier: " << mysql_error(conn) << endl;
    }
}
