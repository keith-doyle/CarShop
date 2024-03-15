//Keith Doyle
//C22415964
//14/03/24 Start date for Project
#define _CRT_SECURE_NO_WARNINGS 1 // No warnings
// Include necessary header files
#include <stdio.h>

// Main function
int main() {
    int choice; // Variable to store user's choice

    // Start of do-while loop to display menu and get user input
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
    } while (choice != 7); // End of do-while loop, exit loop if choice is 7 (exit)

    return 0; // Return 0 to indicate successful execution
}
//This comment is to check if pushing to remote repo is working as intended 
//This is just one more test just to see if it is finally working 