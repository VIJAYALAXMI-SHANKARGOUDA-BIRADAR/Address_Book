/*
NAME: VIJAYALAXMI SHANKARGOUDA BIRADAR
DATE: 20-08-2025
DESCRIPTION: This program is about an address book system project.
             It can create contacts with validated Name, Phone, and Email.
             It can list all contacts sorted by name, phone or email.
             It can search contacts by any field.
             It can edit selected contact details.
             It can delete contacts which are selected.
             Save all changes to a file before exit.
             The program is implemented using strings, pointers, functions,
             structures, files and basics of C.
*/

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "contact.h"
#include "file.h"
#include "populate.h"
#include <ctype.h>

//====================== LIST CONTACTS ===========================
void listContacts(AddressBook *addressBook, int sortCriteria) 
{
    if(addressBook->contactCount == 0)
    {
        printf("No contacts found.\n");
        return;
    }
    printf("Enter the sort criteria: ");
    scanf("%d", &sortCriteria);
    getchar();

    if (sortCriteria < 1 || sortCriteria > 3)
	{
        printf("Invalid sort choice. Sorting by Name.\n");
        sortCriteria = 1; // default to name
    }
    // Bubble sort based on criteria
    for(int i = 0; i < addressBook->contactCount - 1; i++)
    {
        for(int j = 0; j < addressBook->contactCount - 1 - i; j++)
        {
            int cmp = 0;
            if(sortCriteria == 1) // Name
                cmp = strcasecmp(addressBook->contacts[j].name, addressBook->contacts[j+1].name);
            else if(sortCriteria == 2) // Phone
                cmp = strcmp(addressBook->contacts[j].phone, addressBook->contacts[j+1].phone);
            else if(sortCriteria == 3) // Email
                cmp = strcmp(addressBook->contacts[j].email, addressBook->contacts[j+1].email);

            if(cmp > 0) 
			{
                Contact temp = addressBook->contacts[j];
                addressBook->contacts[j] = addressBook->contacts[j+1];
                addressBook->contacts[j+1] = temp;
            }
        } // end inner for
    } // end outer for

    // Print table
    printf("----------------------------------------------------------------------------------\n");
    printf("%-6s %-35s %-15s %-30s\n", "SL.No", "Name", "Phone", "Email");
    printf("----------------------------------------------------------------------------------\n");

    for(int i = 0; i < addressBook->contactCount; i++)
    {
        printf("%-6d %-35s %-15s %-30s\n", i+1, 
               addressBook->contacts[i].name, 
               addressBook->contacts[i].phone,
               addressBook->contacts[i].email);
    } // end for

    printf("----------------------------------------------------------------------------------\n");
    printf("Total contacts: %d\n", addressBook->contactCount);
    printf("----------------------------------------------------------------------------------\n");
} // end listContacts
//==================================================================================================================

//====================== SAVE AND EXIT ===========================
void saveAndExit(AddressBook *addressBook)
{
    saveContactsToFile(addressBook);
    exit(EXIT_SUCCESS);
} // end saveAndExit


//====================== CREATE CONTACT ==========================
void createContact(AddressBook *addressBook)
{
    char name[50], phone[20], email[50];
    int valid_name, valid_phone, valid_email;
    
   ///////// // Validate Name////////////
	
    do {
        printf("Enter Name: ");
        scanf(" %[^\n]", name);

        valid_name = 1;
        int i = 0;
        while(name[i] != '\0')
        {
            if((name[i] >= 'a' && name[i] <= 'z') ||
               (name[i] >= 'A' && name[i] <= 'Z') ||
               name[i] == '-' || name[i] == '.' || name[i] == ' ')
            {
                i++;
            }
            else 
			{
                valid_name = 0;
                break;
            }
        }
        if(valid_name == 0)
            printf("Invalid name! Only letters, space, dot allowed\n");

    } while(valid_name == 0);
    strcpy(addressBook->contacts[addressBook->contactCount].name, name);

    /////////// Validate Phone///////
	
    do {
        printf("Enter Mobile Number: ");
        scanf("%s", phone);

        valid_phone = 1;
        int i = 0;

        if(strlen(phone) != 10)
            valid_phone = 0;

        while(phone[i] != '\0')
        {
            if(phone[i] >= '0' && phone[i] <= '9')
                i++;
            else {
                valid_phone = 0;
                break;
            }
        }

        // Check duplicate phone
        for(int j = 0; j < addressBook->contactCount; j++) 
		{
            if(strcmp(addressBook->contacts[j].phone, phone) == 0) 
			{
                valid_phone = 0;
                printf("Phone number already exists! Try a different number.\n");
                break;
            }
        }
        if(valid_phone == 0)
            printf("Invalid phone number! Enter 10 digits\n");

    } while(valid_phone == 0);
    strcpy(addressBook->contacts[addressBook->contactCount].phone, phone);
	

   ////////////////////// // Validate Email//////////////////////////////////////
	
    do {
        printf("Enter Email: ");
        scanf(" %[^\n]", email);

        valid_email = 1;
        int i = 0;
        while(email[i] != '\0')\
			{
            if((email[i] >= 'a' && email[i] <= 'z') || 
               (email[i] >= '0' && email[i] <= '9') ||
               email[i] == '@' || email[i] == '.' || email[i] == '-')
            {
                i++;
            } 
			else
			{
                valid_email = 0;
                break;
            }
        }

        // Must contain one @
        char *at = strchr(email, '@');
        if(!at || strchr(at+1, '@') || *(at+1) == '\0')
            valid_email = 0;

        // Domain check
        char *dot = strrchr(email, '.');
        if(!dot || strlen(dot) < 3)
            valid_email = 0;

        if(valid_email == 0)
            printf("Invalid email format! Try again.\n");

    } while(valid_email == 0);
    strcpy(addressBook->contacts[addressBook->contactCount].email, email);

    // Increase contact count
    addressBook->contactCount++;
} // end createContact
//===========================================================================================================


//====================== SEARCH CONTACT ==========================
int searchContact(AddressBook *addressBook) 
{
    if(addressBook->contactCount == 0)
	{
        printf("No contacts found\n");
        return -1;
    }

    char name[50], phone[20], email[50];
    int search;

    do {
        printf("Enter search by:\n1.Name\n2.Phone\n3.Email\nChoice: ");
        scanf("%d", &search);
    } while(search < 1 || search > 3);

    int matchedIndex[MAX_CONTACTS];
    int matchCount = 0;

    switch(search) {
        case 1: // Name
            printf("Enter Name: ");
            scanf(" %[^\n]", name);
            for(int i = 0; i < addressBook->contactCount; i++)
			{
                if(strcasestr(addressBook->contacts[i].name, name) != NULL)
				{
                    matchedIndex[matchCount++] = i;
                }
            }
            break;
        case 2: // Phone
            printf("Enter Phone: ");
            scanf(" %[^\n]", phone);
            for(int i = 0; i < addressBook->contactCount; i++) 
			{
                if(strcmp(addressBook->contacts[i].phone, phone) == 0) 
				{
                    matchedIndex[matchCount++] = i;
                }
            }
            break;
        case 3: // Email
            printf("Enter Email: ");
            scanf(" %[^\n]", email);
            for(int i = 0; i < addressBook->contactCount; i++) 
			{
                if(strcmp(addressBook->contacts[i].email, email) == 0) 
				{
                    matchedIndex[matchCount++] = i;
                }
            }
            break;
    } // end switch

    if(matchCount == 0) 
	{
        printf("No contacts found.\n");
        return -1;
    }

    // Print matched contacts
    printf("----------------------------------------------------------------------------------\n");
    printf("%-6s %-35s %-15s %-30s\n","SL.No","Name","Phone","Email");
    printf("----------------------------------------------------------------------------------\n");

    for(int i = 0; i < matchCount; i++)
		{
        int index = matchedIndex[i];
        printf("%-6d %-35s %-15s %-30s\n",
               index + 1,
               addressBook->contacts[index].name,
               addressBook->contacts[index].phone,
               addressBook->contacts[index].email);
        }
    printf("----------------------------------------------------------------------------------\n");

    int finalIndex;
    if(matchCount == 1) 
	{
        finalIndex = matchedIndex[0];
    } 
	else 
	{
        int sl, found = 0;
        while(!found) 
		{
            printf("Multiple matches found. Enter Serial No: ");
            scanf("%d", &sl);
            for(int i = 0; i < matchCount; i++)
			{
                if(sl == matchedIndex[i] + 1) 
				 {
                    finalIndex = matchedIndex[i];
                    found = 1;
                    break;
                 }
            }
            if(!found)
                printf("Invalid Serial No.\n");
        }
    }

    return finalIndex;
} // end searchContact


//====================== EDIT CONTACT ==========================
void editContact(AddressBook *addressBook)
{
    if(addressBook->contactCount == 0) 
	{
        printf("No contacts to edit\n");
        return;
    }

    int index = searchContact(addressBook);
    if(index == -1)
        return;

    int choice;
    printf("Which field do you want to edit:\n1.Name\n2.Phone\n3.Email\nChoice: ");
    scanf("%d", &choice);

    char name[50], phone[20], email[50];
    int valid_name, valid_phone, valid_email;

    switch(choice)
    {
        case 1: // Name
            do {
                printf("Enter new Name: ");
                scanf(" %[^\n]", name);

                valid_name = 1;
                for(int i = 0; name[i] != '\0'; i++)
					{
                    if(!isalpha(name[i]) && name[i] != '-' && name[i] != '.' && name[i] != ' ')
                        valid_name = 0;
                    }
                if(!valid_name) printf("Invalid name!\n");
            } while(!valid_name);
            strcpy(addressBook->contacts[index].name, name);
            break;

        case 2: // Phone
            do {
                printf("Enter new Phone: ");
                scanf("%s", phone);
                valid_phone = (strlen(phone) == 10);
                for(int i = 0; phone[i] != '\0'; i++)
					{
                    if(!isdigit(phone[i])) valid_phone = 0;
                   }
            } while(!valid_phone);
            strcpy(addressBook->contacts[index].phone, phone);
            break;

        case 3: // Email
            do {
                printf("Enter new Email: ");
                scanf(" %[^\n]", email);
                valid_email = (strchr(email,'@') && strrchr(email,'.'));
            } while(!valid_email);
            strcpy(addressBook->contacts[index].email, email);
            break;
    } // end switch
} // end editContact

//====================== DELETE CONTACT ==========================
void deleteContact(AddressBook *addressBook)
{
    if(addressBook->contactCount == 0)
	{
        printf("Address book is empty\n");
        return;
    }

    int index = searchContact(addressBook);
    if(index == -1)
        return;

    for(int i = index; i < addressBook->contactCount - 1; i++) 
	{
        addressBook->contacts[i] = addressBook->contacts[i + 1];
    }
    addressBook->contactCount--;

    printf("Contact deleted successfully.\n");
} // end deleteContact

