#include <iostream>
#include <cstring>
#include <string>

using namespace std;

// Unsafe function for integer buffer overflow
void unsafeFunctionInt(int input) {
    int buffer[2]; // Small fixed-size buffer

    // Potentially dangerous: writing out of bounds
    buffer[3] = input; // This writes beyond the allocated array

    cout << "[Unsafe Function Int] Buffer values: " << buffer[0] << ", " << buffer[1] << endl;
}

// Safe function for integers
void safeFunctionInt(int input) {
    int buffer[2]; // Small fixed-size buffer

    // Mitigation: Ensuring safe index
    if (input >= 0 && input < 2) {
        buffer[input] = 42; // Assign safely
    } else {
        cout << "[Safe Function Int] Invalid index." << endl;
        return;
    }

    cout << "[Safe Function Int] Buffer values: " << buffer[0] << ", " << buffer[1] << endl;
}

// Unsafe function for strings
void unsafeFunctionString(const char *input) {
    char buffer[10]; // Small fixed-size buffer

    // Potentially dangerous: no bounds checking
    strcpy(buffer, input);

    cout << "[Unsafe Function String] Buffer contains: " << buffer << endl;
}

// Safe function for strings
void safeFunctionString(const string &input) {
    char buffer[10]; // Small fixed-size buffer

    // Mitigation: Copy only up to the size of the buffer
    strncpy(buffer, input.c_str(), sizeof(buffer) - 1);
    buffer[sizeof(buffer) - 1] = '\0'; // Ensure null termination

    cout << "[Safe Function String] Buffer contains: " << buffer << endl;
}

// Unsafe function for arrays
void unsafeFunctionArray(int *input, size_t size) {
    int buffer[5]; // Small fixed-size buffer

    // Potentially dangerous: copying without bounds checking
    for (size_t i = 0; i < size; ++i) {
        buffer[i] = input[i];
    }

    cout << "[Unsafe Function Array] Buffer values: ";
    for (int i = 0; i < 5; ++i) {
        cout << buffer[i] << " ";
    }
    cout << endl;
}

// Safe function for arrays
void safeFunctionArray(int *input, size_t size) {
    int buffer[5]; // Small fixed-size buffer

    // Mitigation: Only copy up to the size of the buffer
    for (size_t i = 0; i < min(size, sizeof(buffer) / sizeof(buffer[0])); ++i) {
        buffer[i] = input[i];
    }

    cout << "[Safe Function Array] Buffer values: ";
    for (int i = 0; i < 5; ++i) {
        cout << buffer[i] << " ";
    }
    cout << endl;
}

int main() {
    cout << "Choose an option:\n1. Integer\n2. String\n3. Array\nEnter your choice: ";
    int choice;
    cin >> choice;

    switch (choice) {
        case 1: {
            cout << "Do you want to run the safe or unsafe function? (1 for unsafe, 2 for safe): ";
            int subChoice;
            cin >> subChoice;
            if (subChoice == 1) {
                int unsafeInt = 999;
                cout << "\nDemonstrating Unsafe Function for Integer:" << endl;
                unsafeFunctionInt(unsafeInt);
            } else if (subChoice == 2) {
                int safeInt = 1;
                cout << "\nDemonstrating Safe Function for Integer:" << endl;
                safeFunctionInt(safeInt);
            } else {
                cout << "Invalid choice." << endl;
            }
            break;
        }
        case 2: {
            cout << "Do you want to run the safe or unsafe function? (1 for unsafe, 2 for safe): ";
            int subChoice;
            cin >> subChoice;
            if (subChoice == 1) {
                const char *unsafeInput = "ThisIsAVeryLongInputThatWillOverflow";
                cout << "\nDemonstrating Unsafe Function for String:" << endl;
                unsafeFunctionString(unsafeInput);
            } else if (subChoice == 2) {
                const string safeInput = "SafeInput";
                cout << "\nDemonstrating Safe Function for String:" << endl;
                safeFunctionString(safeInput);
            } else {
                cout << "Invalid choice." << endl;
            }
            break;
        }
        case 3: {
            cout << "Do you want to run the safe or unsafe function? (1 for unsafe, 2 for safe): ";
            int subChoice;
            cin >> subChoice;
            if (subChoice == 1) {
                int unsafeArray[] = {1, 2, 3, 4, 5, 6};
                size_t unsafeSize = sizeof(unsafeArray) / sizeof(unsafeArray[0]);
                cout << "\nDemonstrating Unsafe Function for Array:" << endl;
                unsafeFunctionArray(unsafeArray, unsafeSize);
            } else if (subChoice == 2) {
                int safeArray[] = {1, 2, 3};
                size_t safeSize = sizeof(safeArray) / sizeof(safeArray[0]);
                cout << "\nDemonstrating Safe Function for Array:" << endl;
                safeFunctionArray(safeArray, safeSize);
            } else {
                cout << "Invalid choice." << endl;
            }
            break;
        }
        default:
            cout << "Invalid choice." << endl;
    }

    return 0;
}
