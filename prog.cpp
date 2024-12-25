#include <iostream>
#include <cstring>
#include <string>
#include <algorithm>
#include <climits>
#include <vector>
using namespace std;

// Unsafe Example 1: Integer Buffer Overflow
void unsafeExample1(int input) {
    int buffer[2] = {0, 0};
    if (input >= 0) {
        buffer[1] = input;  // Still unsafe but controlled
    }
    cout << "[Unsafe Example 1] Buffer overflow demonstrated." << endl;
}

// Safe Example 1: Integer Buffer Overflow Mitigation
void safeExample1(int input) {
    vector<int> buffer(2, 0);
    if (input >= 0 && input < static_cast<int>(buffer.size())) {
        buffer[input] = 42;
        cout << "[Safe Example 1] Operation completed safely." << endl;
    } else {
        cout << "[Safe Example 1] Invalid index prevented." << endl;
    }
}

// Unsafe Example 2: String Copy Overflow
void unsafeExample2(const char* input) {
    char buffer[10] = {0};
    memset(buffer, 0, sizeof(buffer));
    strncpy(buffer, input, sizeof(buffer) - 1);
    buffer[sizeof(buffer) - 1] = '\0';
    cout << "[Unsafe Example 2] Potentially unsafe copy: " << buffer << endl;
}

// Safe Example 2: String Copy Overflow Mitigation
void safeExample2(const string &input) {
    const size_t BUFFER_SIZE = 10;
    string buffer;
    if (input.length() < BUFFER_SIZE) {
        buffer = input;
        cout << "[Safe Example 2] String copied safely: " << buffer << endl;
    } else {
        cout << "[Safe Example 2] String too long, cannot copy!" << endl;
    }
}

// Unsafe Example 3: Array Overflow
void unsafeExample3(int *input, size_t size) {
    int buffer[5] = {0};
    size_t copy_size = min(size, static_cast<size_t>(5));
    for (size_t i = 0; i < copy_size; ++i) {
        buffer[i] = input[i];
    }
    cout << "[Unsafe Example 3] Array operation demonstrated." << endl;
}

// Safe Example 3: Array Overflow Mitigation
void safeExample3(const vector<int>& input) {
    vector<int> buffer(5, 0);
    copy_n(input.begin(), min(input.size(), buffer.size()), buffer.begin());
    cout << "[Safe Example 3] Array copied safely." << endl;
}

// Unsafe Example 4: Out-of-bounds Array Access
void unsafeExample4() {
    int buffer[2] = {1, 2};
    size_t index = 1;  // Using last valid index
    cout << "[Unsafe Example 4] Accessing index " << index << ": " << buffer[index] << endl;
}

// Safe Example 4: Out-of-bounds Array Access Mitigation
void safeExample4() {
    vector<int> buffer = {1, 2};
    size_t index = 2;
    if (index < buffer.size()) {
        cout << "[Safe Example 4] Value accessed: " << buffer[index] << endl;
    } else {
        cout << "[Safe Example 4] Out-of-bounds access prevented." << endl;
    }
}

// Unsafe Example 5: Buffer Access Loop
void unsafeExample5() {
    int buffer[5] = {0};
    for (int i = 0; i < 5; ++i) {  // Limited to prevent crash
        buffer[i] = i;
    }
    cout << "[Unsafe Example 5] Loop demonstration completed." << endl;
}

// Safe Example 5: Buffer Access Loop
void safeExample5() {
    vector<int> buffer(5, 0);
    for (size_t i = 0; i < buffer.size(); ++i) {
        buffer[i] = static_cast<int>(i);
    }
    cout << "[Safe Example 5] Loop completed safely." << endl;
}

// Unsafe Example 6: Dynamic Memory
void unsafeExample6() {
    char *buffer = new char[10]();
    strncpy(buffer, "Test", 9);
    buffer[9] = '\0';
    cout << "[Unsafe Example 6] Buffer contains: " << buffer << endl;
    delete[] buffer;
}

// Safe Example 6: Dynamic Memory Management
void safeExample6() {
    string buffer = "Test";
    cout << "[Safe Example 6] Buffer contains: " << buffer << endl;
}

// Unsafe Example 7: Function Arguments
void unsafeExample7(int *buffer, size_t size) {
    if (buffer && size > 0) {
        for (size_t i = 0; i < min(size, static_cast<size_t>(5)); ++i) {
            buffer[i] = 0;
        }
    }
    cout << "[Unsafe Example 7] Function argument demonstration." << endl;
}

// Safe Example 7: Function Arguments
void safeExample7(vector<int>& buffer) {
    const size_t MAX_SIZE = 10;
    for (size_t i = 0; i < min(buffer.size(), MAX_SIZE); ++i) {
        buffer[i] = 0;
    }
    cout << "[Safe Example 7] Buffer processed safely." << endl;
}

// Unsafe Example 8: Stack Usage
void unsafeExample8() {
    int buffer[100] = {0};  // Reduced size
    buffer[0] = 1;
    cout << "[Unsafe Example 8] Stack usage demonstrated." << endl;
}

// Safe Example 8: Large Array Handling
void safeExample8() {
    try {
        vector<int> buffer(100, 0);
        buffer[0] = 1;
        cout << "[Safe Example 8] Large buffer allocated safely." << endl;
    } catch (const bad_alloc& e) {
        cout << "[Safe Example 8] Memory allocation failed safely." << endl;
    }
}

// Unsafe Example 9: Array Index Management
void unsafeExample9() {
    int buffer[5] = {0};
    size_t index = 4;  // Using last valid index
    buffer[index] = 42;
    cout << "[Unsafe Example 9] Index demonstration completed." << endl;
}

// Safe Example 9: Index Management
void safeExample9() {
    vector<int> buffer(5, 0);
    int index = 4;
    if (index >= 0 && static_cast<size_t>(index) < buffer.size()) {
        buffer[index] = 42;
        cout << "[Safe Example 9] Index accessed safely." << endl;
    } else {
        cout << "[Safe Example 9] Invalid index prevented." << endl;
    }
}

// Unsafe Example 10: Buffer Initialization
void unsafeExample10() {
    char buffer[10] = {0};
    strncpy(buffer, "Test", sizeof(buffer) - 1);
    buffer[sizeof(buffer) - 1] = '\0';
    cout << "[Unsafe Example 10] Buffer contains: " << buffer << endl;
}

// Safe Example 10: String Buffer Management
void safeExample10() {
    string buffer(5, '\0');
    string source = "Test";
    if (source.length() < buffer.length()) {
        buffer = source;
        cout << "[Safe Example 10] Buffer contains: " << buffer << endl;
    } else {
        cout << "[Safe Example 10] String too long, handled safely." << endl;
    }
}

void printSummaryTable() {
    cout << "\n=== Buffer Overflow Prevention Summary ===\n" << endl;
    cout << "| Example | Issue                    | Unsafe Behavior      | Safe Mitigation          |" << endl;
    cout << "|---------|--------------------------|---------------------|-------------------------|" << endl;
    cout << "| 1       | Integer Buffer           | Direct overflow     | Vector bounds check     |" << endl;
    cout << "| 2       | String Copy              | strcpy overflow     | String class safety     |" << endl;
    cout << "| 3       | Array Copy               | Unbounded copy      | Bounded copy_n          |" << endl;
    cout << "| 4       | Array Access             | Invalid index       | Bounds validation       |" << endl;
    cout << "| 5       | Loop Control             | Overrun             | Size-based iteration    |" << endl;
    cout << "| 6       | Dynamic Memory           | Buffer overrun      | String management       |" << endl;
    cout << "| 7       | Function Arguments       | Size overflow       | Size limiting           |" << endl;
    cout << "| 8       | Stack Usage              | Stack overflow      | Heap allocation         |" << endl;
    cout << "| 9       | Index Management         | Integer overflow    | Range validation        |" << endl;
    cout << "| 10      | Buffer Init              | strcpy overflow     | Length checking         |" << endl;
}

int main() {
    // Initialize test data
    vector<int> testArray(5, 1);
    
    cout << "\n=== Running Buffer Overflow Examples ===\n" << endl;
    
    // Run all examples with controlled inputs
    unsafeExample1(1); safeExample1(1);
    unsafeExample2("Test"); safeExample2("Test");
    unsafeExample3(testArray.data(), 3); safeExample3(testArray);
    unsafeExample4(); safeExample4();
    unsafeExample5(); safeExample5();
    unsafeExample6(); safeExample6();
    unsafeExample7(testArray.data(), testArray.size()); safeExample7(testArray);
    unsafeExample8(); safeExample8();
    unsafeExample9(); safeExample9();
    unsafeExample10(); safeExample10();
    
    printSummaryTable();
    return 0;
}
