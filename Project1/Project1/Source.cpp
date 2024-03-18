//Keith Doyle
//C22415964
//14/03/24 Start date for Project
#define _CRT_SECURE_NO_WARNINGS 1 // No warnings
#include <stdio.h>
#include <stdlib.h> // For dynamic memory allocation
#include <string.h> // For string manipulation functions

// Structure to represent a car
struct Car {
    char registration[10]; // Car registration number
    char make[50]; // Make of the car
    char model[50]; // Model of the car
    char color[20]; // Color of the car
    int year; // Year of the car
    int num_owners; // Number of previous owners (0 to 3)
    int reserved; // Boolean value indicating if the car is reserved (1 for reserved, 0 for not reserved)
    float reserve_amount; // Reserve amount (deposit paid by the customer)
    struct Car* next; // Pointer to the next car node in the linked list
};

// Function to validate car registration format
int isValidRegistration(const char* registration) {
    // Check if registration has 8 characters
    if (strlen(registration) != 8)
        return 0;

    // Validate year (14 to 24)
    int year = (registration[0] - '0') * 10 + (registration[1] - '0');
    if (year < 14 || year > 24)
        return 0;

    // Validate Dublin identifier
    if (registration[2] != 'D')
        return 0;

    // Validate half-year indicator (1 or 2)
    if (registration[3] != '1' && registration[3] != '2')
        return 0;

    // Validate last 4 digits
    for (int i = 4; i < 8; i++) {
        if (!isdigit(registration[i]))
            return 0;
    }

    // Registration format is valid
    return 1;
}

int main() {
    int choice;

    // Initialize the head of the linked list
    struct Car* head = NULL;

    do {
        // Displaying the menu
        printf("Car Showroom Management System\n");
        printf("1. Add a new car to the showroom\n");
        printf("2. Sell a car from the showroom\n");
        printf("3. Reserve/Unreserve a car in the showroom\n");
        printf("4. View all cars in the showroom\n");
        printf("5. View a specific car in the showroom\n");
        printf("6. Your custom option\n");
        printf("7. Exit the system\n");
        printf("Enter your choice: ");

        // Getting user choice
        scanf("%d", &choice);

        // Switch case to perform action based on user choice
        switch (choice) {
        case 1:
            printf("Adding a new car to the showroom...\n");
            
            printf("Functionality to add a new car will be implemented here.\n");

            
            char registration[10];
            printf("Enter car registration: ");
            scanf("%s", registration);
            if (isValidRegistration(registration))
                printf("Valid registration!\n");
            else
                printf("Invalid registration format!\n");
            break;
        case 2:
            printf("Selling a car from the showroom...\n");
            
            break;
        case 3:
            printf("Reserving/Unreserving a car in the showroom...\n");
            
            break;
        case 4:
            printf("Viewing all cars in the showroom...\n");
            
            break;
        case 5:
            printf("Viewing a specific car in the showroom...\n");
           
            break;
        case 6:
            printf("Your custom option...\n");
           
            break;
        case 7:
            printf("Exiting the system. Goodbye!\n");
            break;
        default:
            printf("Invalid choice! Please enter a number between 1 and 7.\n");
        }
    } while (choice != 7);

    return 0;
}
}