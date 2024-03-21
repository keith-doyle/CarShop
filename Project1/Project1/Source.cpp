//Keith Doyle
//C22415964
//14/03/24 Start date for Project
#define _CRT_SECURE_NO_WARNINGS 1 // No warnings
#include <ctype.h>
#include <stdio.h>
#include <stdlib.h> // For dynamic memory allocation
#include <string.h> // For string manipulation functions
#define MAX_CARS 5
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
// Function prototypes
int isValidRegistration(const char* registration);
void addCar(struct Car** head, int* numCars);
void sellCar(struct Car** head, const char* registration);
void reserveCar(struct Car* head, const char* registration);
void viewAllCars(struct Car* head);
void viewAllCarsDetails(struct Car* head);
void viewReservedCars(struct Car* head);
void viewUnreservedCars(struct Car* head);
void viewCarsByMake(struct Car* head);
void viewCarsByModel(struct Car* head);
void viewCarsByColor(struct Car* head);
void viewCarsByYear(struct Car* head);
void viewCarsByOwners(struct Car* head);

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

// Function to add a new car to the showroom
void addCar(struct Car** head, int* numCars) {
    if (*numCars >= MAX_CARS) {
        printf("Error: The showroom is full. Cannot add more cars.\n");
        return;
    }

    struct Car* newCar = (struct Car*)malloc(sizeof(struct Car));
    if (newCar == NULL) {
        printf("Memory allocation failed.\n");
        return;
    }

    printf("Enter car registration: ");
    scanf("%s", newCar->registration);
    if (!isValidRegistration(newCar->registration)) {
        printf("Invalid registration format!\n");
        free(newCar);
        return;
    }

    // Check if registration is already used
    struct Car* current = *head;
    while (current != NULL) {
        if (strcmp(current->registration, newCar->registration) == 0) {
            printf("Error: Registration already exists for another car.\n");
            free(newCar);
            return;
        }
        current = current->next;
    }

    printf("Enter car make: ");
    scanf("%s", newCar->make);

    printf("Enter car model: ");
    scanf("%s", newCar->model);

    printf("Enter car color: ");
    scanf("%s", newCar->color);

    printf("Enter car year: ");
    scanf("%d", &newCar->year);

    printf("Enter number of previous owners (0 to 3): ");
    scanf("%d", &newCar->num_owners);
    if (newCar->num_owners < 0 || newCar->num_owners > 3) {
        printf("Invalid number of previous owners!\n");
        free(newCar);
        return;
    }

    newCar->reserved = 0; // Initially not reserved
    newCar->reserve_amount = 0.0; // Initially reserve amount is 0

    newCar->next = *head;
    *head = newCar;

    (*numCars)++;

    printf("New car added to the showroom.\n");
}

// Function to sell a car from the showroom
void sellCar(struct Car** head, const char* registration) {
    struct Car* current = *head;
    struct Car* prev = NULL;

    while (current != NULL) {
        if (strcmp(current->registration, registration) == 0) {
            if (current->reserved) {
                // Car is reserved, so it can be sold
                if (prev == NULL) {
                    // Car to be sold is the first in the list
                    *head = current->next;
                }
                else {
                    // Car to be sold is not the first in the list
                    prev->next = current->next;
                }
                free(current);
                printf("Car with registration %s sold.\n", registration);
                return;
            }
            else {
                printf("Error: Car with registration %s is not reserved.\n", registration);
                return;
            }
        }
        prev = current;
        current = current->next;
    }

    printf("Error: Car with registration %s not found.\n", registration);
}

// Function to reserve or unreserve a car
void reserveCar(struct Car* head, const char* registration) {
    struct Car* current = head;

    while (current != NULL) {
        if (strcmp(current->registration, registration) == 0) {
            if (current->reserved) {
                // Car is already reserved, so unreserve it
                current->reserved = 0;
                current->reserve_amount = 0.0;
                printf("Car with registration %s has been unreserved.\n", registration);
            }
            else {
                // Car is not reserved, so reserve it
                printf("Enter deposit amount (more than 500 and less than 1500): ");
                float deposit;
                scanf("%f", &deposit);
                if (deposit < 500 || deposit > 1500) {
                    printf("Invalid deposit amount.\n");
                    return;
                }
                current->reserved = 1;
                current->reserve_amount = deposit;
                printf("Car with registration %s has been reserved with a deposit of %.2f.\n", registration, deposit);
            }
            return;
        }
        current = current->next;
    }

    printf("Error: Car with registration %s not found.\n", registration);
}

// New implementation this menu is used to view any car you like
void viewCarsMenu(struct Car* head) {
    int choice;
    do {
        printf("\nView cars based on:\n");
        printf("1. All cars\n");
        printf("2. Reserved cars\n");
        printf("3. Unreserved cars\n");
        printf("4. Cars by make\n");
        printf("5. Cars by model\n");
        printf("6. Cars by color\n");
        printf("7. Cars by year\n");
        printf("8. Cars by number of previous owners\n");
        printf("9. Back to main menu\n");
        printf("Enter your choice: ");
        scanf("%d", &choice);

        switch (choice) {
        case 1:
            printf("\nViewing all cars in the showroom:\n");
            viewAllCarsDetails(head);
            break;
        case 2:
            printf("\nViewing reserved cars:\n");
            viewReservedCars(head);
            break;
        case 3:
            printf("\nViewing unreserved cars:\n");
            viewUnreservedCars(head);
            break;
        case 4:
            printf("\nViewing cars by make:\n");
            viewCarsByMake(head);
            break;
        case 5:
            printf("\nViewing cars by model:\n");
            viewCarsByModel(head);
            break;
        case 6:
            printf("\nViewing cars by color:\n");
            viewCarsByColor(head);
            break;
        case 7:
            printf("\nViewing cars by year:\n");
            viewCarsByYear(head);
            break;
        case 8:
            printf("\nViewing cars by number of previous owners:\n");
            viewCarsByOwners(head);
            break;
        case 9:
            return; // Return to main menu
        default:
            printf("Invalid choice! Please enter a number between 1 and 9.\n");
        }
    } while (choice != 9);
}

// Function to view all car details
void viewAllCarsDetails(struct Car* head) {
    struct Car* current = head;
    while (current != NULL) {
        printf("Registration: %s, Make: %s, Model: %s, Color: %s, Year: %d, Owners: %d, Reserved: %s, Reserve Amount: %.2f\n",
            current->registration, current->make, current->model, current->color, current->year, current->num_owners,
            current->reserved ? "Yes" : "No", current->reserve_amount);
        current = current->next;
    }
}

// Function to view reserved cars
void viewReservedCars(struct Car* head) {
    struct Car* current = head;
    int found = 0;
    while (current != NULL) {
        if (current->reserved) {
            printf("Registration: %s, Make: %s, Model: %s, Color: %s, Year: %d, Owners: %d\n",
                current->registration, current->make, current->model, current->color, current->year, current->num_owners);
            found = 1;
        }
        current = current->next;
    }
    if (!found)
        printf("No reserved cars found.\n");
}

// Function to view unreserved cars
void viewUnreservedCars(struct Car* head) {
    struct Car* current = head;
    int found = 0;
    while (current != NULL) {
        if (!current->reserved) {
            printf("Registration: %s, Make: %s, Model: %s, Color: %s, Year: %d, Owners: %d\n",
                current->registration, current->make, current->model, current->color, current->year, current->num_owners);
            found = 1;
        }
        current = current->next;
    }
    if (!found)
        printf("No unreserved cars found.\n");
}
// Function to view cars based on make
void viewCarsByMake(struct Car* head) {
    char makeFilter[50];
    printf("Enter make to filter: ");
    scanf("%s", makeFilter);
    struct Car* current = head;
    int found = 0;
    while (current != NULL) {
        if (strcmp(current->make, makeFilter) == 0) {
            printf("Registration: %s, Model: %s, Color: %s, Year: %d, Owners: %d\n",
                current->registration, current->model, current->color, current->year, current->num_owners);
            found = 1;
        }
        current = current->next;
    }
    if (!found)
        printf("No cars found with make '%s'.\n", makeFilter);
}

// Function to view cars based on model
void viewCarsByModel(struct Car* head) {
    char modelFilter[50];
    printf("Enter model to filter: ");
    scanf("%s", modelFilter);
    struct Car* current = head;
    int found = 0;
    while (current != NULL) {
        if (strcmp(current->model, modelFilter) == 0) {
            printf("Registration: %s, Make: %s, Color: %s, Year: %d, Owners: %d\n",
                current->registration, current->make, current->color, current->year, current->num_owners);
            found = 1;
        }
        current = current->next;
    }
    if (!found)
        printf("No cars found with model '%s'.\n", modelFilter);
}

// Function to view cars based on color
void viewCarsByColor(struct Car* head) {
    char colorFilter[20];
    printf("Enter color to filter: ");
    scanf("%s", colorFilter);
    struct Car* current = head;
    int found = 0;
    while (current != NULL) {
        if (strcmp(current->color, colorFilter) == 0) {
            printf("Registration: %s, Make: %s, Model: %s, Year: %d, Owners: %d\n",
                current->registration, current->make, current->model, current->year, current->num_owners);
            found = 1;
        }
        current = current->next;
    }
    if (!found)
        printf("No cars found with color '%s'.\n", colorFilter);
}

// Function to view cars based on year
void viewCarsByYear(struct Car* head) {
    int yearFilter;
    printf("Enter year to filter: ");
    scanf("%d", &yearFilter);
    struct Car* current = head;
    int found = 0;
    while (current != NULL) {
        if (current->year == yearFilter) {
            printf("Registration: %s, Make: %s, Model: %s, Color: %s, Owners: %d\n",
                current->registration, current->make, current->model, current->color, current->num_owners);
            found = 1;
        }
        current = current->next;
    }
    if (!found)
        printf("No cars found with year '%d'.\n", yearFilter);
}

// Function to view cars based on number of previous owners
void viewCarsByOwners(struct Car* head) {
    int ownersFilter;
    printf("Enter number of previous owners to filter (0 to 3): ");
    scanf("%d", &ownersFilter);
    struct Car* current = head;
    int found = 0;
    while (current != NULL) {
        if (current->num_owners == ownersFilter) {
            printf("Registration: %s, Make: %s, Model: %s, Color: %s, Year: %d\n",
                current->registration, current->make, current->model, current->color, current->year);
            found = 1;
        }
        current = current->next;
    }
    if (!found)
        printf("No cars found with %d previous owners.\n", ownersFilter);
}
void customizeCarColor(struct Car* head) {
    char reg[10];
    printf("Enter the registration number of the car you want to customize: ");
    scanf("%s", reg);

    struct Car* current = head;
    while (current != NULL) {
        if (strcmp(current->registration, reg) == 0) {
            printf("Car found!\n");
            printf("Select a new color for the car:\n");
            printf("1. Blue\n");
            printf("2. Red\n");
            printf("3. Black\n");
            printf("4. Silver\n");
            printf("5. White\n");
            printf("6. Green\n");
            printf("Enter your choice: ");

            int choice;
            scanf("%d", &choice);

            switch (choice) {
            case 1:
                strcpy(current->color, "Blue");
                break;
            case 2:
                strcpy(current->color, "Red");
                break;
            case 3:
                strcpy(current->color, "Black");
                break;
            case 4:
                strcpy(current->color, "Silver");
                break;
            case 5:
                strcpy(current->color, "White");
                break;
            case 6:
                strcpy(current->color, "Green");
                break;
            default:
                printf("Invalid choice!\n");
                return;
            }
            printf("Car color updated successfully!\n");
            return;
        }
        current = current->next;
    }
    printf("Car not found!\n");
}


int main() {
    int choice;
    int numCars = 0; // Declare and initialize numCars
    // Initialize the head of the linked list
    struct Car* head = NULL;

    do {
        // Displaying the menu
        printf("Car Showroom Management System\n");
        printf("1. Add a new car to the showroom\n");
        printf("2. Sell a car from the showroom\n");
        printf("3. Reserve/Unreserve a car in the showroom\n");
        printf("4. View any car in the showroom\n");
        printf("5. Change car color\n");
        printf("6. Exit the system\n");
        printf("Enter your choice: ");

        // Getting user choice
        scanf("%d", &choice);

        // Switch case to perform action based on user choice
        switch (choice) {
        case 1:
            printf("\nAdding a new car to the showroom...\n");
            addCar(&head, &numCars);
            break;
        case 2:
            printf("\nSelling a car from the showroom...\n");
            char reg[10];
            printf("Enter car registration to sell: ");
            scanf("%s", reg);
            sellCar(&head, reg);
            break;
        case 3:
            printf("\nReserving/Unreserving a car in the showroom...\n");
            char regReserve[10];
            printf("Enter car registration to reserve/unreserve: ");
            scanf("%s", regReserve);
            reserveCar(head, regReserve);
            break;
        case 4:
            printf("\nChoose any car to view...\n");
            viewCarsMenu(head);
            break;
        case 5:
            printf("\nCustomize Car Color:\n");
            customizeCarColor(head);
            break;
        case 6:
            printf("Exiting the system. Goodbye!\n");
            exit(1); // Terminates the program with exit code 0
            break;
        default:
            printf("Invalid choice! Please enter a number between 1 and 6.\n");
        }
    } while (choice != 6); // Exit loop if choice is 6 

    // Free memory allocated for linked list nodes
    struct Car* current = head;
    while (current != NULL) {
        struct Car* temp = current;
        current = current->next;
        free(temp);
    }
    return 0;
}

