#include "StaffMenu.h"
#include <iomanip> // Include for setw
#include <chrono>  // Include for time delays
#include <thread>  // Include for sleep_for()
#include <vector>

// Function prototypes
void UpdateStaffProfile(MYSQL* conn, const string& username);
//void ManageInventory(MYSQL* conn);
//void ManageSuppliers(MYSQL* conn);

void StaffMenu(MYSQL* conn, const string& username) {
    int choice;

    do {
        cout << "\n--- Staff Menu ---\n";
        cout << "1. View Your Profile\n";
        cout << "2. Manage Inventory\n";
        cout << "3. Manage Suppliers\n";
        cout << "4. Generate Sales Report\n";
        cout << "5. Logout\n";
        cout << "Please select an option (1-4): ";
        cin >> choice;

        switch (choice) {
        case 1:
            ViewStaffProfile(conn, username);
            break;
        case 2:
            ManageInventoryStaff(conn);
            break;
        case 3:
            ManageSuppliersStaff(conn);
            break;
        case 4:
            GenerateSalesReport(conn);
            break;
        case 5:
            // Creative logout message
            cout << "\n*****************************\n";
            cout << "*  Logging Out... Goodbye!  *\n";
            cout << "*  We'll miss you, " << username << " *\n";
            cout << "*****************************\n";

            // Add a bit of a delay to make it more dramatic
            for (int i = 0; i < 3; i++) {
                cout << ".";
                this_thread::sleep_for(chrono::milliseconds(500));  // Creates a slight pause between dots
            }

            // Final message
            cout << "\n\nSee you again soon, " << username << "! Take care and come back soon!\n";

            // Log out from the system and exit the menu
            return; // Exit the StaffMenu loop and log out
        default:
            cout << "Invalid choice! Please try again.\n";
        }
    } while (choice != 4);
}

void ViewStaffProfile(MYSQL* conn, const string& username) {
    string query = "SELECT * FROM staff_menu WHERE username_staff = '" + username + "';";
    const char* q = query.c_str();

    if (mysql_query(conn, q) == 0) {
        MYSQL_RES* res = mysql_store_result(conn);
        MYSQL_ROW row;

        if ((row = mysql_fetch_row(res))) {
            cout << "\n---------------------------------------------\n";
            cout << "\n=============================================\n";
            cout << "               Your Profile                 \n";
            cout << "=============================================\n";
            cout << left << setw(15) << "Staff ID: " << row[0] << "\n";
            cout << left << setw(15) << "Username: " << row[1] << "\n";
            cout << left << setw(15) << "Password: " << row[2] << "\n";
            cout << left << setw(15) << "Name: " << row[3] << "\n";
            cout << left << setw(15) << "Age: " << row[4] << "\n";
            cout << left << setw(15) << "Email: " << row[5] << "\n";
            cout << left << setw(15) << "Phone: " << row[6] << "\n";
            cout << left << setw(15) << "Address: " << row[7] << "\n";
            cout << "=============================================\n";
            cout << "\n---------------------------------------------\n";

            // Options for updating or deleting the profile
            int option;
            cout << "\nWould you like to:\n";
            cout << "1. Update Profile\n";
            cout << "2. Go Back to Staff Menu\n";
            cout << "Please select an option (1-2): ";
            cin >> option;

            switch (option) {
            case 1:
                UpdateStaffProfile(conn, username); // Call the function to update the profile
                break;
            case 2:
                return; // Return to the staff menu
            default:
                cout << "Invalid option! Returning to the staff menu.\n";
                break;
            }
        }
        else {
            cout << "\nProfile not found. Please contact support.\n";
        }

        mysql_free_result(res);
    }
    else {
        cerr << "Error fetching profile: " << mysql_error(conn) << endl;    // Giving Output Error On Terminal
    }
}

void UpdateStaffProfile(MYSQL* conn, const string& username) {
    string new_name, new_age, new_email, new_phone, new_address;

    cout << "\n--- Update Profile ---\n";

    // Enter new Name
    cout << "Enter new Name (or press Enter to skip): ";
    cin.ignore();
    getline(cin, new_name);

    // Enter new Age
    cout << "Enter new Age (or press Enter to skip): ";
    getline(cin, new_age);

    // Enter new Email
    cout << "Enter new Email (or press Enter to skip): ";
    getline(cin, new_email);

    // Enter new Phone
    cout << "Enter new Phone (or press Enter to skip): ";
    getline(cin, new_phone);

    // Enter new Address
    cout << "Enter new Address (or press Enter to skip): ";
    getline(cin, new_address);

    // Build the update query
    string update_query = "UPDATE staff_menu SET ";
    bool is_first = true; // Track if it's the first field being updated

    if (!new_name.empty()) {
        if (!is_first) update_query += ", ";
        update_query += "name_staff = '" + new_name + "'";
        is_first = false;
    }
    if (!new_age.empty()) {
        if (!is_first) update_query += ", ";
        update_query += "age_staff = '" + new_age + "'";
        is_first = false;
    }
    if (!new_email.empty()) {
        if (!is_first) update_query += ", ";
        update_query += "email_staff = '" + new_email + "'";
        is_first = false;
    }
    if (!new_phone.empty()) {
        if (!is_first) update_query += ", ";
        update_query += "phone_staff = '" + new_phone + "'";
        is_first = false;
    }
    if (!new_address.empty()) {
        if (!is_first) update_query += ", ";
        update_query += "address_staff = '" + new_address + "'";
    }

    // Ensure there's something to update
    if (is_first) {
        cout << "No updates were made as no fields were provided.\n";
        return;
    }

    update_query += " WHERE username_staff = '" + username + "';";

    const char* q = update_query.c_str();

    // Execute the query
    if (mysql_query(conn, q) == 0) {
        cout << "Profile updated successfully!\n";
    }
    else {
        cerr << "Error updating profile: " << mysql_error(conn) << endl;
    }
}

void ManageInventoryStaff(MYSQL* conn) {
    int choice;

    do {
        cout << "\n--- Manage Inventory ---\n";
        cout << "1. View Inventory\n";
        cout << "2. Add New Inventory Item\n";
        cout << "3. Update Existing Inventory Item\n";
        cout << "4. Delete Inventory Item\n";
        cout << "5. Return to Admin Menu\n";
        cout << "Please select an option (1-5): ";
        cin >> choice;

        switch (choice) {
        case 1: {
            // View inventory
            string query = "SELECT * FROM inventory_menu";
            if (mysql_query(conn, query.c_str()) == 0) {
                MYSQL_RES* res = mysql_store_result(conn);
                MYSQL_ROW row;

                cout << "\n--- Inventory ---\n";
                cout << left << setw(15) << "Inventory ID" << setw(20) << "Name"
                    << setw(30) << "Description" << setw(10) << "Quantity"
                    << setw(10) << "Price" << setw(15) << "Type" << endl;
                cout << string(100, '-') << endl;

                while ((row = mysql_fetch_row(res))) {
                    cout << left << setw(15) << row[0] << setw(20) << row[1]
                        << setw(30) << row[2] << setw(10) << row[3]
                        << setw(10) << row[4] << setw(15) << row[5] << endl;
                }

                mysql_free_result(res);
            }
            else {
                cerr << "Error retrieving inventory: " << mysql_error(conn) << endl;
            }
            break;
        }
        case 2: {
            // Add new inventory item
            string name, description, type;
            int quantity;
            double price;
            int type_choice;

            cout << "\nEnter Inventory Name: ";
            cin.ignore();
            getline(cin, name);
            cout << "Enter Description: ";
            getline(cin, description);
            cout << "Enter Quantity: ";
            cin >> quantity;
            cout << "Enter Price: ";
            cin >> price;

            // Type selection using numbers
            cout << "Select Type of Inventory:\n";
            cout << "1. Electronics\n";
            cout << "2. Clothing\n";
            cout << "3. Furniture\n";
            cout << "4. Food Products\n";
            cout << "Enter your choice (1-4): ";
            cin >> type_choice;

            switch (type_choice) {
            case 1:
                type = "Electronics";
                break;
            case 2:
                type = "Clothing";
                break;
            case 3:
                type = "Furniture";
                break;
            case 4:
                type = "Food Products";
                break;
            default:
                cout << "Invalid choice. Aborting addition of new inventory item.\n";
                return; // Exit if invalid type is selected
            }

            string query = "INSERT INTO inventory_menu (name_inventory, description_inventory, quantity_inventory, price_inventory, type_inventory) VALUES ('" +
                name + "', '" + description + "', " + to_string(quantity) + ", " + to_string(price) + ", '" + type + "');";

            if (mysql_query(conn, query.c_str()) == 0) {
                cout << "New inventory item added successfully!\n";
            }
            else {
                cerr << "Error adding inventory item: " << mysql_error(conn) << endl;
            }
            break;
        }

        case 3: {
            // Update existing inventory item
            string inventory_id, field, new_value;
            cout << "\nEnter Inventory ID to update: ";
            cin >> inventory_id;
            cout << "Enter the field to update (name_inventory, description_inventory, quantity_inventory, price_inventory, type_inventory): ";
            cin >> field;
            cout << "Enter the new value: ";
            cin.ignore();
            getline(cin, new_value);

            string query = "UPDATE inventory_menu SET " + field + " = '" + new_value + "' WHERE inventory_id = '" + inventory_id + "';";

            if (mysql_query(conn, query.c_str()) == 0) {
                cout << "Inventory item updated successfully!\n";
            }
            else {
                cerr << "Error updating inventory item: " << mysql_error(conn) << endl;
            }
            break;
        }
        case 4: {
            // Delete inventory item
            string inventory_id;
            cout << "\nEnter Inventory ID to delete: ";
            cin >> inventory_id;

            string query = "DELETE FROM inventory_menu WHERE inventory_id = '" + inventory_id + "';";

            if (mysql_query(conn, query.c_str()) == 0) {
                cout << "Inventory item deleted successfully!\n";
            }
            else {
                cerr << "Error deleting inventory item: " << mysql_error(conn) << endl;
            }
            break;
        }
        case 5:
            // Return to Admin Menu
            cout << "Returning to Staff Menu...\n";
            return;
        default:
            cout << "Invalid choice! Please try again.\n";
        }
    } while (choice != 5);
}

void ManageSuppliersStaff(MYSQL* conn) {
    int choice;

    do {
        cout << "\n--- Manage Suppliers ---\n";
        cout << "1. View All Suppliers\n";
        cout << "2. Add New Supplier\n";
        cout << "3. Update Supplier Information\n";
        cout << "4. Delete Supplier\n";
        cout << "5. Return to Admin Menu\n";
        cout << "Please select an option (1-5): ";
        cin >> choice;

        switch (choice) {
        case 1: {
            // View all suppliers
            string query = "SELECT * FROM supplier_menu;";
            if (mysql_query(conn, query.c_str()) == 0) {
                MYSQL_RES* res = mysql_store_result(conn);
                MYSQL_ROW row;

                cout << "\n--- Supplier List ---\n";
                while ((row = mysql_fetch_row(res))) {
                    cout << "Supplier ID: " << row[0] << "\n"
                        << "Name: " << row[1] << "\n"
                        << "Phone: " << row[2] << "\n"
                        << "Email: " << row[3] << "\n"
                        << "Address: " << row[4] << "\n"
                        << "Discount Rate: " << row[5] << "%\n"
                        << "Type: " << row[6] << "\n";
                    cout << "----------------------\n";
                }
                mysql_free_result(res);
            }
            else {
                cerr << "Error retrieving suppliers: " << mysql_error(conn) << endl;
            }
            break;
        }
        case 2: {
            // Add a new supplier
            string name, phone, email, address, type;
            float discount_rate;
            int type_choice;

            cout << "\n--- Add New Supplier ---\n";
            cin.ignore();
            cout << "Enter Supplier Name: ";
            getline(cin, name);
            cout << "Enter Phone Number: ";
            getline(cin, phone);
            cout << "Enter Email Address: ";
            getline(cin, email);
            cout << "Enter Address: ";
            getline(cin, address);
            cout << "Enter Discount Rate (%): ";
            cin >> discount_rate;

            // Type selection using numbers
            cout << "Select Supplier Type:\n";
            cout << "1. Electronics\n";
            cout << "2. Clothing\n";
            cout << "3. Furniture\n";
            cout << "4. Food Products\n";
            cout << "Enter your choice (1-4): ";
            cin >> type_choice;

            switch (type_choice) {
            case 1:
                type = "Electronics";
                break;
            case 2:
                type = "Clothing";
                break;
            case 3:
                type = "Furniture";
                break;
            case 4:
                type = "Food Products";
                break;
            default:
                cout << "Invalid choice. Supplier not added.\n";
                return; // Exit if invalid type is selected
            }

            // Insert supplier into the database
            string query = "INSERT INTO supplier_menu (name_supplier, phone_supplier, email_supplier, address_supplier, discount_rate, type_supplier) VALUES ('" +
                name + "', '" + phone + "', '" + email + "', '" + address + "', " + to_string(discount_rate) + ", '" + type + "');";

            if (mysql_query(conn, query.c_str()) == 0) {
                cout << "Supplier added successfully!\n";
            }
            else {
                cerr << "Error adding supplier: " << mysql_error(conn) << endl;
            }
            break;
        }

        case 3: {
            // Update supplier information
            string supplier_id, field, new_value;

            cout << "Enter Supplier ID to update: ";
            cin >> supplier_id;
            cout << "Enter the field to update (name_supplier, phone_supplier, email_supplier, address_supplier, discount_rate, type_supplier): ";
            cin >> field;
            cin.ignore();
            cout << "Enter the new value: ";
            getline(cin, new_value);

            // Update supplier query
            string query = "UPDATE supplier_menu SET " + field + " = '" + new_value + "' WHERE supplier_id = " + supplier_id + ";";
            if (mysql_query(conn, query.c_str()) == 0) {
                cout << "Supplier updated successfully!\n";
            }
            else {
                cerr << "Error updating supplier: " << mysql_error(conn) << endl;
            }
            break;
        }
        case 4: {
            // Delete supplier
            string supplier_id;

            cout << "Enter Supplier ID to delete: ";
            cin >> supplier_id;

            string query = "DELETE FROM supplier_menu WHERE supplier_id = " + supplier_id + ";";
            if (mysql_query(conn, query.c_str()) == 0) {
                cout << "Supplier deleted successfully!\n";
            }
            else {
                cerr << "Error deleting supplier: " << mysql_error(conn) << endl;
            }
            break;
        }
        case 5:
            // Return to Admin Menu
            cout << "Returning to Staff Menu...\n";
            return;
        default:
            cout << "Invalid choice! Please try again.\n";
        }
    } while (choice != 5);
}

void GenerateSalesReport(MYSQL* conn) {
    // Example of a simple query for generating a sales report
    string query = "SELECT item_name, SUM(quantity_sold) AS total_sold, SUM(total_price) AS total_revenue "
        "FROM sales "
        "GROUP BY item_name;";
    const char* q = query.c_str();

    if (mysql_query(conn, q) == 0) {
        MYSQL_RES* res = mysql_store_result(conn);
        MYSQL_ROW row;

        cout << "\n--- Sales Report ---\n";
        cout << left << setw(20) << "Item Name" << setw(15) << "Total Sold" << setw(15) << "Total Revenue\n";
        cout << "------------------------------------------------------\n";

        while ((row = mysql_fetch_row(res))) {
            cout << left << setw(20) << row[0] << setw(15) << row[1] << setw(15) << row[2] << "\n";
        }

        mysql_free_result(res);
    }
    else {
        cerr << "Error fetching sales report: " << mysql_error(conn) << endl;
    }
}
