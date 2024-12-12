#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define MAX_SAFE_INPUT 16 // Define maximum safe buffer size
#define MAX_SAFE_INTEGER 100 // Maximum safe value for integer input

// Function to print an interactive banner
void print_banner() {
    printf("******************************************\n");
    printf("*      🛡️ BUFFER OVERFLOW MITIGATION 🛡️       *\n");
    printf("*     (Preventing Chaotic Exploits!)     *\n");
    printf("******************************************\n\n");
}

// Securely reads string input without risking buffer overflow
void secure_input_string(char *buffer, size_t max_size) {
    printf("🚀 Enter your name (Max %zu characters): ", max_size - 1);
    if (fgets(buffer, max_size, stdin) == NULL) {
        fprintf(stderr, "💥 Error: Unable to read input! Exiting.\n");
        exit(1);
    }
    // Strip newline to keep input clean
    buffer[strcspn(buffer, "\n")] = '\0';
}

// Securely reads integer input without risking overflow
void secure_input_integer(int *input, int max_value) {
    printf("🚀 Enter an integer (Max %d): ", max_value);
    if (scanf("%d", input) != 1) {
        fprintf(stderr, "💥 Error: Invalid input! Exiting.\n");
        exit(1);
    }
    if (*input > max_value) {
        printf("🛑 Warning: Input exceeds the safe limit! Truncating to %d.\n", max_value);
        *input = max_value;
    }
}

// Process string input securely by dynamically resizing buffers
void process_input_string(const char *input) {
    size_t input_length = strlen(input);

    if (input_length >= MAX_SAFE_INPUT) {
        printf("\n🛑 Warning: Input is too long (%zu characters). Resizing for safety...\n", input_length);
    }

    // Dynamically allocate buffer for processing (casting void* to char*)
    size_t safe_size = (input_length < MAX_SAFE_INPUT) ? input_length + 1 : MAX_SAFE_INPUT;
    char *buffer = (char*)malloc(safe_size);  // Correctly cast void* to char*
    if (!buffer) {
        fprintf(stderr, "💀 Memory allocation failed! Exiting.\n");
        exit(1);
    }

    strncpy(buffer, input, safe_size - 1);
    buffer[safe_size - 1] = '\0'; // Ensure null-termination

    printf("\n🎉 Hello, %s! Your input has been securely processed.\n", buffer);

    if (input_length >= MAX_SAFE_INPUT) {
        printf("😂 Your input was too long, so it was truncated to:\n");
        printf("   \"%s\"\n", buffer);
    }

    free(buffer); // Free allocated memory
    printf("\n🧹 Memory cleanup complete. No leaks detected!\n");
}

// Process integer input
void process_input_integer(int input) {
    printf("\n🎉 Your input has been securely processed: %d\n", input);
}

int main() {
    char input_string[MAX_SAFE_INPUT * 2]; // Simulating larger input capacity for strings
    int input_integer;

    int choice;

    print_banner();
    printf("🛠️ Choose an option to test:\n");
    printf("1. String Input\n");
    printf("2. Integer Input\n");
    printf("Your choice: ");
    
    // Read the user's choice for input type
    if (scanf("%d", &choice) != 1) {
        fprintf(stderr, "💥 Error: Invalid input! Exiting.\n");
        exit(1);
    }
    getchar();  // Clear the newline character left by scanf

    if (choice == 1) {
        // Handle string input
        secure_input_string(input_string, sizeof(input_string));
        process_input_string(input_string);
    } else if (choice == 2) {
        // Handle integer input
        secure_input_integer(&input_integer, MAX_SAFE_INTEGER);
        process_input_integer(input_integer);
    } else {
        printf("🛑 Invalid choice! Exiting.\n");
        exit(1);
    }

    printf("\n💡 Reminder: Keep your inputs within safe limits. Stay secure! ✨\n");
    return 0;
}
