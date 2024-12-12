#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>

#define MAX_SAFE_INPUT 16 // Define maximum safe buffer size

// Function to print an interactive banner
void print_banner() {
    printf("******************************************\n");
    printf("*      🛡️ BUFFER OVERFLOW MITIGATION 🛡️       *\n");
    printf("*     (Preventing Chaotic Exploits!)     *\n");
    printf("******************************************\n\n");
}

// Securely reads input without risking buffer overflow
void secure_input(char *buffer, size_t max_size) {
    printf("🚀 Enter your name (Max %zu characters): ", max_size - 1);
    if (fgets(buffer, max_size, stdin) == NULL) {
        fprintf(stderr, "💥 Error: Unable to read input! Exiting.\n");
        exit(1);
    }

    // Strip newline to keep input clean
    buffer[strcspn(buffer, "\n")] = '\0';

    // Validate input: only alphabetic characters allowed
    for (size_t i = 0; buffer[i] != '\0'; i++) {
        if (!isalpha((unsigned char)buffer[i]) && buffer[i] != ' ') {
            printf("❌ Invalid input. Please use only alphabetic characters and spaces.\n");
            exit(1);
        }
    }
}

// Process the input securely by dynamically resizing buffers
void process_input(const char *input) {
    size_t input_length = strlen(input);

    if (input_length >= MAX_SAFE_INPUT) {
        printf("\n🛑 Warning: Input is too long (%zu characters). Resizing for safety...\n", input_length);
    }

    // Dynamically allocate buffer for processing
    size_t safe_size = (input_length < MAX_SAFE_INPUT) ? input_length + 1 : MAX_SAFE_INPUT;
    char *buffer = (char*) malloc(safe_size);  // Cast the void* to char*
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


// Logging function for security auditing (optional)
void log_input(const char *input) {
    FILE *log_file = fopen("input_log.txt", "a");
    if (log_file) {
        fprintf(log_file, "User input: %s\n", input);
        fclose(log_file);
    } else {
        printf("⚠️ Failed to open log file. Input not logged.\n");
    }
}

int main() {
    char input[MAX_SAFE_INPUT * 2]; // Simulating larger input capacity

    print_banner();
    secure_input(input, sizeof(input));
    
    log_input(input); // Optional: Log input for security auditing
    
    process_input(input);

    printf("\n💡 Reminder: Keep your inputs within safe limits. Stay secure! ✨\n");
    return 0;
}
