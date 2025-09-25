#include <stdio.h>    
#include <stdlib.h>     
#include "contact.h"  
#include "file.h"     



void saveContactsToFile(AddressBook *addressBook) {
    
     FILE *fptr ;

     fptr= fopen("addressbook_file.csv","w");
     
     //store count
     fprintf(fptr,"%d\n",addressBook->contactCount);

     //write contact to file
     for(int i=0;i<addressBook->contactCount;i++)
     {
        fprintf(fptr,"%s,%s,%s\n",
        addressBook->contacts[i].name,
        addressBook->contacts[i].phone,
        addressBook->contacts[i].email);
     }
     fclose(fptr);
    }

void loadContactsFromFile(AddressBook *addressBook)
{
    FILE *fptr = fopen("addressbook_file.csv","r");

    if(fptr==NULL)
    {
        addressBook->contactCount=0;
        return;
    }
    

    //read count2qqqqqqqqwq
    fscanf(fptr,"%d\n",&addressBook->contactCount);
    
    //read contact
    for(int i=0;i<addressBook->contactCount;i++)
    {
        fscanf(fptr,"%[^,],%[^,],%[^\n]\n",
    addressBook->contacts[i].name,
    addressBook->contacts[i].phone,
    addressBook->contacts[i].email);
    }
    fclose(fptr);
}