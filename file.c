#include <stdio.h>    
#include <stdlib.h>     
#include "contact.h"  
#include "file.h"     

// Function to save contacts to file
void saveContactsToFile(AddressBook *addressBook) {
    
    FILE *fptr ;  // File pointer

    fptr = fopen("addressbook_file.csv","w"); // Open file in write mode
     
    // Store total contact count at the top
    fprintf(fptr,"%d\n",addressBook->contactCount);

    // Write each contact’s details (name, phone, email)
    for(int i=0; i < addressBook->contactCount; i++)
    {
        fprintf(fptr,"%s,%s,%s\n",
            addressBook->contacts[i].name,
            addressBook->contacts[i].phone,
            addressBook->contacts[i].email);
    }
    fclose(fptr); // Close the file
}

// Function to load contacts from file
void loadContactsFromFile(AddressBook *addressBook)
{
    FILE *fptr = fopen("addressbook_file.csv","r"); // Open file in read mode

    if(fptr == NULL) // If file not found, set contact count = 0
    {
        addressBook->contactCount = 0;
        return;
    }
    
    // Read contact count from file
    fscanf(fptr,"%d\n",&addressBook->contactCount);
    
    // Read each contact’s details
    for(int i = 0; i < addressBook->contactCount; i++)
    {
        fscanf(fptr,"%[^,],%[^,],%[^\n]\n",
            addressBook->contacts[i].name,
            addressBook->contacts[i].phone,
            addressBook->contacts[i].email);
    }
    fclose(fptr); // Close the file
}
