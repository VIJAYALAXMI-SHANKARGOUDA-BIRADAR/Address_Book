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
#include <stdlib.h>
#include <string.h>
#include "contact.h"
#include "file.h"
#include "populate.h"
#include<ctype.h>

void listContacts(AddressBook *addressBook, int sortCriteria) 
{
    // Sort contacts based on the chosen criteria

    if(addressBook->contactCount == 0)
    {
        printf("No contacts found.\n");
        return;
    }
    printf("enter the sort criteria:");
    scanf("%d",&sortCriteria);
    getchar();

     // Validate choice, default to sort by name if invalid
    if (sortCriteria < 1 || sortCriteria > 3) {
        printf("Invalid sort choice. Sorting by Name.\n");
        sortCriteria = 1;//default to name
    }
    
//bubble sort method to sort the conatacts
    for(int i = 0;i < addressBook -> contactCount-1;i++ )
    {
        for(int j =0;j<addressBook->contactCount-1-i;j++)
        {
            int cmp=0;
            if(sortCriteria == 1)//for name
             {
               cmp= strcasecmp(addressBook->contacts[j].name,addressBook->contacts[j+1].name); 
             }
            else if(sortCriteria ==2)//for phonr numbers
             {
             cmp = strcmp(addressBook->contacts[j].phone,addressBook->contacts[j+1].phone);
             }  
           else if(sortCriteria ==3)//for emails
            {
            cmp = strcmp(addressBook->contacts[j].email,addressBook->contacts[j+1].email);
            } 
            
            //swap
         if(cmp>0)  {
                Contact temp=addressBook->contacts[j];
                addressBook->contacts[j] = addressBook->contacts[j+1];
                addressBook->contacts[j+1] = temp;
            }
        }

    }
    printf("----------------------------------------------------------------------------------\n");
    printf("%-6s %-35s %-15s %-30s\n","SL.No","Name","Phone","email");
    printf("----------------------------------------------------------------------------------\n");

    for(int i=0;i<addressBook->contactCount;i++)
    {
        printf("%-6d %-35s %-15s %-30s\n",i+1,addressBook->contacts[i].name,addressBook->contacts[i].phone,
               addressBook->contacts[i].email);
        }

    printf("----------------------------------------------------------------------------------\n");
    printf("Total contacts: %d\n", addressBook->contactCount);
    printf("----------------------------------------------------------------------------------\n");
    }
    
/**/

void saveAndExit(AddressBook *addressBook) {
    saveContactsToFile(addressBook); // Save contacts to file
    exit(EXIT_SUCCESS); // Exit the program
}

//==========================1.CREATE CONTACT====================================
void createContact(AddressBook *addressBook)
{
	/* Define the logic to create a Contacts */


    char name[50],phone[20],email[50];
    int valid_name,valid_phone,valid_email;
    
    //---------------NAME VALIDATION-------------------------
    do{
        printf("Enter Name:");
        scanf(" %[^\n]",name); //read name with spaces
        
        valid_name=1;  //assume name is valid
        int i=0;

        /**/

        while(name[i]!='\0')//check every character until NULL
        {

            if(name[i] >= 'a' && name[i] <='z' || name[i] >='A' && name[i] <='Z' || name[i] =='-' || name[i] =='.' || name[i] == ' ')
             {
                i++;
            }
            else{
                    valid_name=0;
                    break;
                }
        }

         if(valid_name==0)
         {
            printf("Invalid name!.Only letters,space,dot allowed\n");
         }

        }while(valid_name==0);  
      //when we got valid name,copy that name into our addressbook  
    strcpy(addressBook->contacts[addressBook->contactCount].name,name);


    //------------------PHONE NUMBER--------------------
    //loop until we get valid number
    do{
        printf("Enter Mobile Number:");
        scanf("%s",phone);

        valid_phone=1; //assume intially valid
        int i=0;

        if(strlen(phone) !=10)//10 digits
        {
            valid_phone=0;
        }
        while(phone[i] != '\0')
        {
            if(phone[i]>='0' && phone[i]<='9')//only digits
            {
                i++;
            }
            else{
                valid_phone=0;
                break;
            }  
        }
        //uniq phone number
        for(int j=0;j<addressBook->contactCount;j++){
            if(strcmp(addressBook->contacts[j].phone,phone)==0){
                valid_phone = 0;
                printf("phone number already exists! try a different number.\n");
                break;
                 }
          }

        if(valid_phone==0)
        {
            printf("Invaild phone number! enter 10 digits\n ");
        }
    }while(valid_phone==0);

//phone number is valid copy it into addressbook
    strcpy(addressBook->contacts[addressBook->contactCount].phone,phone);


    //--------------Email VALIDATION----------------------
    //same for email until get proper formatted email
    do{
        printf("Enter Email:");
        scanf(" %[^\n]",email);
        

        valid_email=1;//assume it is valid
        int i=0;
        
        while(email[i] != '\0'){
        if((email[i] >='a' && email[i] <= 'z') || 
        (email[i]>='0' && email[i]<='9') ||
        (email[i]=='@') || 
        (email[i]=='.')|| (email[i]=='-'))
        {
            i++;
        }
        else{
            valid_email=0;
            break;
        }
    }

    //2.must contain one @
    char *at=strchr(email,'@');

    if(!at || strchr(at+1,'@') || *(at+1)=='\0'){
        printf("email must contain one @\n");
        valid_email=0;

    }

    //3.domain end with(.com,.net)
    char *dot=strrchr(email,'.');
    if(!dot || strlen(dot) < 3){
        printf("Email must have a valid domain ending with .com,.net");
        valid_email=0;
    }
    //4.between @ and dot
    if(valid_email && (dot-at <=1)){
        printf("must have charcter @ and domn\n");
        valid_email=0;
    }


        if(valid_email==0){
            
            printf("Invalid email format use correct email format:\n");
        }
    }while(valid_email==0);
    //email is valid ,save it into addressbook
 strcpy(addressBook->contacts[addressBook->contactCount].email,email);

  addressBook->contactCount++;//increase contact count

    }
//===============================================================================================================

//======================2.SEARCH CONTACT=========================================================================
int searchContact(AddressBook *addressBook) 
{
    
    char name[50], phone[20], email[50];
    int search;
    
do{     //first,ask user wants to serach by, until valid choice
    printf("enter  search by ");
    printf("\n 1.Name\n 2.Phone\n 3.email\n");
    scanf(" %d",&search);
    getchar();

    //char c;    // clear buffer after taking number input

   //while ((c = getchar()) != '\n' && c != EOF);

    if(search<1 || search>3)
    {
        printf("Invalid choice! try again\n");
    
    }    

    }while(search<1 || search>3);
  
    int matchedindex[MAX_CONTACTS];//store index of matched contacts
    int matchcount=0;

//decide which field to search based on choice
 switch (search ) {
   case 1:      //serach by name
        printf("Enter Name to search: ");
        scanf(" %[^\n]", name);

        for (int i = 0; i < addressBook->contactCount; i++) {
            if (strcasestr(addressBook->contacts[i].name, name) !=NULL) {
                 
               matchedindex[matchcount]=i;//we found one store its index
                matchcount++;
                
            }
        }
        break;
    
    // 2.Search by Phone Number
case 2:
    printf("Enter Phone Number to search: ");
    scanf(" %[^\n]", phone);

    for (int i = 0; i < addressBook->contactCount; i++) {
        if (strcmp(addressBook->contacts[i].phone, phone) == 0) {
           matchedindex[matchcount]=i;
           matchcount++;
        }
    }
    break;
    // 3.Search by Email
 case 3:
    printf("Enter Email to search: ");
    scanf(" %[^\n]", email);

    for (int i = 0; i < addressBook->contactCount; i++) {
        if (strcmp(addressBook->contacts[i].email, email) == 0) {
            matchedindex[matchcount]=i;
            matchcount++;
        }
    }
    break;
}
 

 if(matchcount==0)//If we didn't find any matches, let the user know and return -1 to signal failure.
 {
    printf("No conatcts found\n");
    return -1;
 }


 //print matched contacts in table if we found one match
     printf("----------------------------------------------------------------------------------\n");
    printf("%-6s %-35s %-15s %-30s\n","SL.No","Name","Phone","Email");
    printf("----------------------------------------------------------------------------------\n");
 
    for(int i=0;i<matchcount;i++){
    int index=matchedindex[i];//get original index that is i to contact
     printf("%-6d %-35s %-15s %-30s\n",
               index + 1,   // SL.No as index+1 (array starts from 0 )
               addressBook->contacts[index].name,
               addressBook->contacts[index].phone,
               addressBook->contacts[index].email);
    }
    printf("----------------------------------------------------------------------------------\n");

   
int finalindex;//This will hold the index of the contact the user final
if(matchcount==1)//here was only one result, we can just pick it automatically
{
  finalindex= matchedindex[0];
}

else{//multiple results we need to ask user to choose sl

int sl;
int found=0;
while(!found){
printf("Multiple matches are found.Enter serial number:");
scanf("%d",&sl);

for(int i=0;i<matchcount;i++)
{
    if(sl==matchedindex[i]+1){
       finalindex= matchedindex[i];
        found=1;
        break;
    }
}
if(!found){
printf("Invalid sl.No\n");
}
}

}

printf("contact found:\n%-6s %-35s %-15s %-30s\n","SL.No","Name","Phone","Email");
printf("%-6d %-35s %-15s %-30s\n", finalindex+1,
           addressBook->contacts[finalindex].name,
           addressBook->contacts[finalindex].phone,
           addressBook->contacts[finalindex].email);

           return finalindex;//return the the index of the choosen contact
}


//=================================3.EDIT CONTACT==========================================

void editContact(AddressBook *addressBook)
{
    if(addressBook->contactCount==0){
        printf("No contacts to edit\n");
        return;
    }
    //search
    int index=searchContact(addressBook);//call the serach function
    if(index==-1)
    {
        printf("contact not found\n");
        return;//earch function already told the user nothing was found, so we can just stop
    }

    //edit

    int choice;
    printf("which field do you want to edit:");
    printf("\n1.Name\n2.Phone\n3.Email\n ");
    scanf("%d",&choice);

    //validation
    char name[50],phone[20],email[50];
    int valid_name,valid_phone,valid_email; 

    switch(choice)
    {
        case 1://edit name

    do{
        printf("Enter Name:");
        scanf(" %[^\n]",name);
        getchar();
        

        valid_name=1;
        int i=0;

        /**/

        while(name[i]!='\0')
        {

            if(name[i] >= 'a' && name[i] <='z' || name[i] >='A' && name[i] <='Z' || name[i] =='-' || name[i] =='.' || name[i] == ' ')
             {
                i++;
            }
            else{
                    valid_name=0;
                    break;
                }
        }

         if(valid_name==0)
         {
            printf("Invalid name!.Only letters,space,dot allowed\n");
         }

        }while(valid_name==0);  
        
    strcpy(addressBook->contacts[index].name,name);
    printf("Name updated succesfully\n");
    break;


    //------------------PHONE NUMBER--------------------
    case 2://edit by phone
    do{
        printf("Enter Mobile Number:");
        scanf("%s",phone);

        valid_phone=1;
        int i=0;

        if(strlen(phone) !=10)//10 digits
        {
            valid_phone=0;
        }
        while(phone[i] != '\0')
        {
            if(phone[i]>='0' && phone[i]<='9')//only digits
            {
                i++;
            }
            else{
                valid_phone=0;
                break;
            }  
        }
        //uniq phone number
        for(int j=0;j<addressBook->contactCount;j++){
            if(j!=index && strcmp(addressBook->contacts[j].phone,phone)==0){
                valid_phone = 0;
                printf("phone number already exists! try a different number.\n");
                break;
                 }
          }

        if(valid_phone==0)
        {
            printf("Invaild phone number! enter 10 digits\n ");
        }
    }while(valid_phone==0);

    strcpy(addressBook->contacts[index].phone,phone);
    printf("phone updated successfully\n");

    break;


    //--------------Email VALIDATION----------------------
    case 3://edit by email

    do{
        printf("Enter Email:");
        scanf(" %[^\n]",email);
        

        valid_email=1;
        int i=0;
        
        while(email[i] != '\0'){
        if((email[i] >='a' && email[i] <= 'z') || 
        (email[i]>='0' && email[i]<='9') ||
        (email[i]=='@') || 
        (email[i]=='.')|| (email[i]=='-'))
        {
            i++;
        }
        else{
            valid_email=0;
            break;
        }
    }

    //2.must contain one @
    char *at=strchr(email,'@');

    if(!at || strchr(at+1,'@') || *(at+1)=='\0'){
        printf("email must contain one @\n");
        valid_email=0;

    }

    //3.domain end with(.com,.net)
    char *dot=strrchr(email,'.');
    if(!dot || strlen(dot) < 3){
        printf("Email must have a valid domain ending with .com,.net");
        valid_email=0;
    }
    //4.between @ and dot
    if(valid_email && (dot-at <=1)){
        printf("must have charcter @ and domain\n");
        valid_email=0;
    }


        if(valid_email==0){
            
            printf("Invalid email format use correct email format:\n");
        }
    }while(valid_email==0);
 strcpy(addressBook->contacts[index].email,email);
  printf("\nemail edited successfully\n");
  break;

    }//end of switch
}
//============================================================================================================== 
//===================================DELETE CONTACT---=============================---------------------------//
void deleteContact(AddressBook *addressBook)
{
    if(addressBook->contactCount==0){
        printf("Address book is empty\n");
        return;
    }
    int index=searchContact(addressBook);//call the serach function
    if(index==-1){
        return;
    }


    // Shift all elements after the chosen index one position to the left
    for (int i = index; i < addressBook->contactCount - 1; i++) 
    {
        addressBook->contacts[i] = addressBook->contacts[i + 1];
    }

    // Decrement the total number of contacts
    addressBook->contactCount--;

    printf("Contact deleted successfully.\n");
}






   

