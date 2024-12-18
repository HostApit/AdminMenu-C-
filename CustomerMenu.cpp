#include "CustomerMenu.h"
#include <iomanip> // Include for setw
#include <chrono>  // Include for time delays
#include <thread>  // Include for sleep_for()

// Declare ShowWelcomePage from Project_IMS.cpp (no longer used)
//extern void ShowWelcomePage();

// Function prototypes
void UpdateCustomerProfile(MYSQL* conn, const string& username);
void DeleteCustomerProfile(MYSQL* conn, const string& username);

void CustomerMenu(MYSQL* conn, const string& username) {
    int choice;

    do {
        cout << "\n--- Customer Menu ---\n";
        cout << "1. View Your Profile\n";
        cout << "2. View Inventory\n";
        cout << "3. Logout\n";
        cout << "Please select an option (1-3): ";
        cin >> choice;

        switch (choice) {
        case 1:
            ViewCustomerProfile(conn, username);
            break;
        case 2:
            ViewInventory(conn);
            break;
        case 3:
            // Creative logout message
            cout << "\n*****************************\n";
            cout << "*  Logging Out... Goodbye!  *\n";
            cout << "*  We'll miss you, " << username << "*\n";
            cout << "*****************************\n";
            
            // Add a bit of a delay to make it more dramatic
            for (int i = 0; i < 3; i++) {
                cout << ".";
                this_thread::sleep_for(chrono::milliseconds(500));  // Creates a slight pause between dots
            }

            // Final message
            cout << "\n\nSee you again soon, " << username << "! Take care and come back soon!\n";
            
            // Log out from the system and exit the menu
            return; // Exit the CustomerMenu loop and log out
        default:
            cout << "Invalid choice! Please try again.\n";
        }
    } while (choice != 3);
}

void ViewCustomerProfile(MYSQL* conn, const string& username) {
    string query = "SELECT * FROM customer_menu WHERE username = '" + username + "';";
    const char* q = query.c_str();

    if (mysql_query(conn, q) == 0) {
        MYSQL_RES* res = mysql_store_result(conn);
        MYSQL_ROW row;

        if ((row = mysql_fetch_row(res))) {
            cout << "\n---------------------------------------------\n";
            cout << "\n=============================================\n";
            cout << "               Your Profile                 \n";
            cout << "=============================================\n";
            cout << left << setw(15) << "Customer ID: " << row[0] << "\n";
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
            cout << "2. Delete Profile\n";
            cout << "3. Go Back to Customer Menu\n";
            cout << "Please select an option (1-3): ";
            cin >> option;

            switch (option) {
            case 1:
                UpdateCustomerProfile(conn, username); // Call the function to update the profile
                break;
            case 2:
                DeleteCustomerProfile(conn, username); // Call the function to delete the profile
                break;
            case 3:
                return; // Return to the customer menu
            default:
                cout << "Invalid option! Returning to the customer menu.\n";
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

void UpdateCustomerProfile(MYSQL* conn, const string& username) {
    string new_name, new_age, new_email, new_phone, new_address;

    cout << "\n--- Update Profile ---\n";

    //Enter New Name
    cout << "Enter new Name (or press Enter to skip): ";
    cin.ignore();
    getline(cin, new_name);

    //Enter New Age
    cout << "Enter new Age (or press Enter to skip): ";
    //cin.ignore();
    getline(cin, new_age);

    //Enter New Email
    cout << "Enter new Email (or press Enter to skip): ";
    getline(cin, new_email);

    //Enter New Phone
    cout << "Enter new Phone (or press Enter to skip): ";
    getline(cin, new_phone);

    //Enter New Address
    cout << "Enter new Address (or press Enter to skip): ";
    getline(cin, new_address);

    string update_query = "UPDATE customer_menu SET ";

    // Conditionally append fields if new data is provided
    if (!new_name.empty()) update_query += "name = '" + new_name + "', ";
    if (!new_name.empty()) update_query += "age = '" + new_age + "', ";
    if (!new_email.empty()) update_query += "email = '" + new_email + "', ";
    if (!new_phone.empty()) update_query += "phone = '" + new_phone + "', ";
    if (!new_address.empty()) update_query += "address = '" + new_address + "', ";

    // Remove the last comma and space from the query string
    update_query = update_query.substr(0, update_query.length() - 2);

    update_query += " WHERE username = '" + username + "';";

    const char* q = update_query.c_str();

    if (mysql_query(conn, q) == 0) {
        cout << "Profile updated successfully!\n";
    }
    else {
        cerr << "Error updating profile: " << mysql_error(conn) << endl;
    }
}

void DeleteCustomerProfile(MYSQL* conn, const string& username) {
    char confirm;
    cout << "\nAre you sure you want to delete your profile? (y/n): ";
    cin >> confirm;

    if (confirm == 'y' || confirm == 'Y') {
        string delete_query = "DELETE FROM customer_menu WHERE username = '" + username + "';";
        const char* q = delete_query.c_str();

        if (mysql_query(conn, q) == 0) {
            cout << "Your profile has been deleted.\n";
            // No need to call ShowWelcomePage, end session
        }
        else {
            cerr << "Error deleting profile: " << mysql_error(conn) << endl;
        }
    }
    else {
        cout << "Profile deletion canceled.\n";
    }
}

void ViewInventory(MYSQL* conn) {
    string query = "SELECT * FROM inventory;";
    const char* q = query.c_str();

    if (mysql_query(conn, q) == 0) {
        MYSQL_RES* res = mysql_store_result(conn);
        MYSQL_ROW row;

        cout << "\n--- Inventory ---\n";
        cout << left << setw(10) << "Item ID" << setw(20) << "Item Name" << setw(10) << "Stock" << setw(10) << "Price\n";
        cout << "------------------------------------------------------\n";

        while ((row = mysql_fetch_row(res))) {
            cout << left << setw(10) << row[0] << setw(20) << row[1] << setw(10) << row[2] << setw(10) << row[3] << "\n";
        }

        mysql_free_result(res);
    }
    else {
        cerr << "Error fetching inventory: " << mysql_error(conn) << endl;
    }
}
