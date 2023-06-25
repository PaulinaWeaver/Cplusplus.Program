// Paulina Weaver
// CS-210 Project 3
// 6-21-2023

#include <iostream>
#include <fstream>
#include <string>
#include <map>

using namespace std;

class ItemFrequency {
// Private data
private:
    map<string, int> itemFrequencyMap; // Declare and create map named itemFrequencyMap 
// Public data
public:
    void readInputFile(string fileName);  // Reads input file and stores frequency of items
    void userItemFrequency(string item);  // Prints frequency of item the user searches
    void totalItemsFrequency();  // Prints frequency of all items
    void totalItemsHistogram();  // // Prints histogram of all items
    void createFrequencyFile(string fileName);  // Creates backup file to store frequency of all items
};

/* Forward declaring functions for a more readable code */
void printMenu();
void readInputFile(string);
void userItemFrequency(string);
void totalItemsFrequency();
void totalItemsHistogram();
void createFrequencyFile(string);

int main() {  // Main function
    int userChoice;  // Integer varible to hold users menu choice
    string itemName;  // Sting varible to hold item user wishes to search for
    cin.exceptions(ios::failbit);  // Set exception mask for cin stream

    ItemFrequency dailyFrequency;  // Create ItemFrequency object named dailyFrequency
    dailyFrequency.readInputFile("CS210_Project_Three_Input_File.txt");  // Read input file
    dailyFrequency.createFrequencyFile("frequency.dat");  // Create data file for backing up accumulated data

    do {  // Do while loop that exits when user inputs 4
        printMenu(); // Print menu
        try {  // Try statement to catch the exception.  
            cin >> userChoice;  // Get users choice

            switch (userChoice) {  // Switch case statement to handle users input
            case 1:
                cout << "\nSearch item: ";  // Prompt user to input the item they wish to look for
                cin >> itemName;  // Get item name
                dailyFrequency.userItemFrequency(itemName);  // Return a numeric value for the frequency of the specific word
                system("PAUSE");  // Pause console window so user can read output
                break;
            case 2:
                dailyFrequency.totalItemsFrequency();  //Print the list with numbers that represent the frequency of all items purchased
                system("PAUSE");  // Pause console window so user can read output
                break;
            case 3:
                dailyFrequency.totalItemsHistogram();  //Print the same frequency information for all the items in the form of a histogram
                system("PAUSE");  // Pause console window so user can read output
                break;
            case 4:
                cout << "\nGoodbye!" << endl;
                break;
            default:
                cout << "\nInvalid choice!" << endl;  // Print invalid choice for invalid numbers
                break;
            }
        }
        catch (ios_base::failure& e) {  // Catch statement to catch the exception
            cout << "\nPlease enter a number!" << endl; // Print error message if input is not an integer
            cin.clear();  // Clear cin's failbit to put cin in a useable state.
            cin.ignore(100, '\n');  // Ignores rest of the line
        }
    } while (userChoice != 4);  // Exit loop if user inputs 4

    return 0;
}

/* Print main menu */
void printMenu() {
    cout << "\n*********************Main Menu*********************" << endl;
    cout << "1. Print frequency a specific item was purchased" << endl;
    cout << "2. Print frequency of all items purchased" << endl;
    cout << "3. Print a histogram of all items purchased" << endl;
    cout << "4. Exit" << endl;
    cout << "***************************************************" << endl;
    cout << "Please enter choice: ";
}

/* Defining readInputFile function that reads the input file and stores the frequency of the items in map */
void ItemFrequency::readInputFile(string fileName) {
    string item;
    ifstream inFS(fileName);  // Input file stream
    while (inFS >> item) {
        itemFrequencyMap[item]++;
    }
    inFS.close();  // Close input file when done reading
}

/* Defining userItemFrequency function that prints the frequency of the item the user is searching for */
void ItemFrequency::userItemFrequency(string item) {
    if (itemFrequencyMap.count(item) > 0) {  // If item appears more than 0 times
        cout << item << " " << itemFrequencyMap[item] << endl;  // Print frequency
    }
    else {  // If item appears 0 times
        cout << item << " 0" << endl;  // Print 0
    }
}

/* Defining totalItemsFrequency function that prints the frequency of all items */
void ItemFrequency::totalItemsFrequency() {
    for (auto it = itemFrequencyMap.begin(); it != itemFrequencyMap.end(); it++) {
        cout << it->first << " " << it->second << endl;
    }
}

/* Defining totalItemsHistogram function that prints the frequency of all items with a star representing the frequency */
void ItemFrequency::totalItemsHistogram() {
    for (auto it = itemFrequencyMap.begin(); it != itemFrequencyMap.end(); it++) {
        cout << it->first << " ";
        for (int i = 0; i < it->second; i++) {  // Print a star the number of times the item appears in the input file
            cout << "*";
        }
        cout << endl;
    }
}

/* Defining createFrequencyFile function that creates a backup file that stores the frequency of all items */
void ItemFrequency::createFrequencyFile(string fileName) {
    ofstream outFS(fileName);  // Output file stream
    for (auto it = itemFrequencyMap.begin(); it != itemFrequencyMap.end(); it++) {
        outFS << it->first << " " << it->second << endl;
    }
    outFS.close();  // Close file when done reading
}
