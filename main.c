/*
NAME:VIJAYALAXMI SHANKARGOUDA BIRADAR
DATE:20-08-2025
DESCRIPTION:This program is about  an address book system project.
            It can create contacts with validated Name,Phone,and Email.
            It can list all contacts sorted by name,phone or email.
            It can search contacts by any field.
            It can edit selected contact details.
            It can delete contacts which is selected.
            save all changes to a file before exit.
            The  program IS implemented using strings pointers,functions,structures ,files and basic of c.
*/


#include <stdio.h>
#include "contact.h"
#include "file.h"

int main() {
    int choice;
    AddressBook addressBook;
   // initialize(&addressBook); // Initialize the address book
   addressBook.contactCount = 0;
   loadContactsFromFile(&addressBook);

    do {
        printf("\nAddress Book Menu:\n");
        printf("1. Create contact\n");
        printf("2. Search contact\n");
        printf("3. Edit contact\n");
        printf("4. Delete contact\n");
        printf("5. List all contacts\n");
    	printf("6. Save and exit contacts\n");		
        
        printf("Enter your choice: ");
        scanf("%d", &choice);
        
        switch (choice) {
            case 1:
                createContact(&addressBook);
                break;
            case 2:
                searchContact(&addressBook);
                break;
            case 3:
                editContact(&addressBook);
                break;
            case 4:
                deleteContact(&addressBook);
                break;
            case 5:          
                listContacts(&addressBook, choice);
                break;
            case 6:
                printf("Saving and Exiting...\n");
                saveContactsToFile(&addressBook);
                break;
            default:
                printf("Invalid choice. Please try again.\n");
        }
    } while (choice != 6);
    
       return 0;
}

