#include "AdminMenu.h"
#include <iomanip> // Include for setw
#include <chrono>  // Include for time delays
#include <thread>  // Include for sleep_for()
#include <iostream>
#include <string>
#include <vector>

void AdminMenu(MYSQL* conn, const string& username) {
    int choice;

    do {
        cout << "\n--- Admin Menu ---\n";
        cout << "1. View Your Profile\n";
        cout << "2. Manage Inventory\n";
        cout << "3. Manage Staff Profiles\n";
        cout << "4. Manage Customer Profiles\n";
        cout << "5. Manage Suppliers\n";
        cout << "6. Compare Suppliers\n";
        cout << "7. Generate Detailed Reports\n";
        cout << "8. Logout\n";
        cout << "Please select an option (1-7): ";
        cin >> choice;

        switch (choice) {
        case 1:
            ViewAdminProfile(conn, username);
            break;
        case 2:
            ManageInventory(conn);
            break;
        case 3:
            ManageStaffProfiles(conn);
            break;
        case 4:
            ManageCustomerProfiles(conn);
            break;
        case 5:
            ManageSuppliers(conn);
            break;
        case 6:
            CompareSuppliers(conn);
            break;
        case 7:
            GenerateDetailedReports(conn);
            break;
        case 8:
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
            return; // Exit the AdminMenu loop and log out
        default:
            cout << "Invalid choice! Please try again.\n";
        }
    } while (choice != 7);
}

void ViewAdminProfile(MYSQL* conn, const string& username) {
    string query = "SELECT * FROM admin_menu WHERE username_admin = '" + username + "';";
    const char* q = query.c_str();

    if (mysql_query(conn, q) == 0) {
        MYSQL_RES* res = mysql_store_result(conn);
        MYSQL_ROW row;

        if ((row = mysql_fetch_row(res))) {
            cout << "\n---------------------------------------------\n";

            cout << "\n=============================================\n";
            cout << "               Your Profile                 \n";
            cout << "=============================================\n";
            cout << left << setw(15) << "Admin ID: " << row[0] << "\n";
            cout << left << setw(15) << "UsernameAdmin: " << row[1] << "\n";
            cout << left << setw(15) << "Password: " << row[2] << "\n";
            cout << left << setw(15) << "Name: " << row[3] << "\n";
            cout << left << setw(15) << "EmailAdmin: " << row[4] << "\n";
            cout << "=============================================\n";

            cout << "\n---------------------------------------------\n";

            // Options for updating the profile
            int option;
            cout << "\nWould you like to:\n";
            cout << "1. Update Profile\n";
            cout << "2. Go Back to Admin Menu\n";
            cout << "Please select an option (1-2): ";
            cin >> option;

            switch (option) {
            case 1:
                UpdateAdminProfile(conn, username); // Call the function to update the profile
                break;
            case 2:
                return; // Return to the admin menu
            default:
                cout << "Invalid option! Returning to the admin menu.\n";
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

void UpdateAdminProfile(MYSQL* conn, const string& username) {
    string new_name, new_username, new_password, new_email;

    cout << "\n--- Update Profile ---\n";

    // Enter new Name
    cout << "Enter new Name (or press Enter to skip): ";
    cin.ignore();
    getline(cin, new_name);

    // Enter new Username
    cout << "Enter new Username (or press Enter to skip): ";
    getline(cin, new_username);

    // Enter new Password
    cout << "Enter new Password (or press Enter to skip): ";
    getline(cin, new_password);

    // Enter new Email
    cout << "Enter new Email (or press Enter to skip): ";
    getline(cin, new_email);


    // Build the update query
    string update_query = "UPDATE admin_menu SET ";
    bool is_first = true; // Track if it's the first field being updated

    if (!new_name.empty()) {
        if (!is_first) update_query += ", ";
        update_query += "name = '" + new_name + "'";
        is_first = false;
    }
    if (!new_username.empty()) {
        if (!is_first) update_query += ", ";
        update_query += "username_admin = '" + new_username + "'";
        is_first = false;
    }
    if (!new_password.empty()) {
        if (!is_first) update_query += ", ";
        update_query += "password = '" + new_password + "'";
        is_first = false;
    }
    if (!new_email.empty()) {
        if (!is_first) update_query += ", ";
        update_query += "email_admin = '" + new_email + "'";
        is_first = false;
    }
    
    // Ensure something to update
    if (is_first) {
        cout << "No updates were made as no fields were provided.\n";
        return;
    }

    update_query += " WHERE username_admin = '" + username + "';";

    const char* q = update_query.c_str();

    // Execute the query
    if (mysql_query(conn, q) == 0) {
        cout << "Profile updated successfully!\n";
    }
    else {
        cerr << "Error updating profile: " << mysql_error(conn) << endl;
    }
}

// Additional placeholder functions for Manage Inventory, Manage Staff, etc.
void ManageInventory(MYSQL* conn) {
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
            cout << "Returning to Admin Menu...\n";
            return;
        default:
            cout << "Invalid choice! Please try again.\n";
        }
    } while (choice != 5);
}


void ManageStaffProfiles(MYSQL* conn) {
        int choice;

        do {
            cout << "\n--- Manage Staff Profiles ---\n";
            cout << "1. View All Staff Profiles\n";
            cout << "2. Update Staff Profile\n";
            cout << "3. Delete Staff Profile\n";
            cout << "4. Return to Admin Menu\n";
            cout << "Please select an option (1-4): ";
            cin >> choice;

            switch (choice) {
            case 1: {
                // View all staff profiles
                string query = "SELECT * FROM staff_menu";
                if (mysql_query(conn, query.c_str()) == 0) {
                    MYSQL_RES* res = mysql_store_result(conn);
                    MYSQL_ROW row;

                    cout << "\n--- Staff Profiles ---\n";
                    while ((row = mysql_fetch_row(res))) {
                        cout << "Staff ID: " << row[0] << "\n"
                            << "Username: " << row[1] << "\n"
                            << "Password: " << row[2] << "\n"
                            << "Name: " << row[3] << "\n"
                            << "Age: " << row[4] << "\n"
                            << "Email: " << row[5] << "\n"
                            << "Phone: " << row[6] << "\n"
                            << "Address: " << row[7] << "\n";
                        cout << "----------------------\n";
                    }

                    mysql_free_result(res);
                }
                else {
                    cerr << "Error retrieving staff profiles: " << mysql_error(conn) << endl;
                }
                break;
            }
            case 2: {
                // Update staff profile
                string staff_id, field, new_value;
                cout << "Enter Staff ID to update: ";
                cin >> staff_id;
                cout << "Enter the field to update (username_staff, password_staff, name_staff, age_staff, email_staff, phone_staff, address_staff): ";
                cin >> field;
                cout << "Enter the new value: ";
                cin.ignore();
                getline(cin, new_value);

                string query = "UPDATE staff_menu SET " + field + " = '" + new_value + "' WHERE staff_id = '" + staff_id + "';";
                if (mysql_query(conn, query.c_str()) == 0) {
                    cout << "Staff profile updated successfully!\n";
                }
                else {
                    cerr << "Error updating staff profile: " << mysql_error(conn) << endl;
                }
                break;
            }
            case 3: {
                // Delete staff profile
                string staff_id;
                cout << "Enter Staff ID to delete: ";
                cin >> staff_id;

                string query = "DELETE FROM staff_menu WHERE staff_id = '" + staff_id + "';";
                if (mysql_query(conn, query.c_str()) == 0) {
                    cout << "Staff profile deleted successfully!\n";
                }
                else {
                    cerr << "Error deleting staff profile: " << mysql_error(conn) << endl;
                }
                break;
            }
            case 4:
                // Return to Admin Menu
                cout << "Returning to Admin Menu...\n";
                return;
            default:
                cout << "Invalid choice! Please try again.\n";
            }
        } while (choice != 4);
    }

void ManageCustomerProfiles(MYSQL* conn) {
        int choice;

        do {
            cout << "\n--- Manage Customer Profiles ---\n";
            cout << "1. View All Customer Profiles\n";
            cout << "2. Update Customer Profile\n";
            cout << "3. Delete Customer Profile\n";
            cout << "4. Return to Admin Menu\n";
            cout << "Please select an option (1-4): ";
            cin >> choice;

            switch (choice) {
            case 1: {
                // View all customer profiles
                string query = "SELECT * FROM customer_menu";
                if (mysql_query(conn, query.c_str()) == 0) {
                    MYSQL_RES* res = mysql_store_result(conn);
                    MYSQL_ROW row;

                    cout << "\n--- Customer Profiles ---\n";
                    while ((row = mysql_fetch_row(res))) {
                        cout << "Customer ID: " << row[0] << "\n"
                            << "Username: " << row[1] << "\n"
                            << "Password: " << row[2] << "\n"
                            << "Name: " << row[3] << "\n"
                            << "Email: " << row[4] << "\n"
                            << "Phone: " << row[5] << "\n"
                            << "Address: " << row[6] << "\n";
                        cout << "----------------------\n";
                    }

                    mysql_free_result(res);
                }
                else {
                    cerr << "Error retrieving customer profiles: " << mysql_error(conn) << endl;
                }
                break;
            }
            case 2: {
                // Update customer profile
                string customer_id, field, new_value;
                cout << "Enter Customer ID to update: ";
                cin >> customer_id;
                cout << "Enter the field to update (name, email, phone, address): ";
                cin >> field;
                cout << "Enter the new value: ";
                cin.ignore();
                getline(cin, new_value);

                string query = "UPDATE customer_menu SET " + field + " = '" + new_value + "' WHERE customer_id = '" + customer_id + "';";
                if (mysql_query(conn, query.c_str()) == 0) {
                    cout << "Customer profile updated successfully!\n";
                }
                else {
                    cerr << "Error updating customer profile: " << mysql_error(conn) << endl;
                }
                break;
            }
            case 3: {
                // Delete customer profile
                string customer_id;
                cout << "Enter Customer ID to delete: ";
                cin >> customer_id;

                string query = "DELETE FROM customer_menu WHERE customer_id = '" + customer_id + "';";
                if (mysql_query(conn, query.c_str()) == 0) {
                    cout << "Customer profile deleted successfully!\n";
                }
                else {
                    cerr << "Error deleting customer profile: " << mysql_error(conn) << endl;
                }
                break;
            }
            case 4:
                // Return to Admin Menu
                cout << "Returning to Admin Menu...\n";
                return;
            default:
                cout << "Invalid choice! Please try again.\n";
            }
        } while (choice != 4);
    }

void ManageSuppliers(MYSQL* conn) {
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
            cout << "Returning to Admin Menu...\n";
            return;
        default:
            cout << "Invalid choice! Please try again.\n";
        }
    } while (choice != 5);
}

void CompareSuppliers(MYSQL* conn) {
    // Can you help me to make coding for comparing supplier which who given most discounted price. Here my coding below:
}

void GenerateDetailedReports(MYSQL* conn) {
    // Placeholder for detailed reports generation
}
