# Address Book -Project
A robust, menu-driven Address Book application built in C for managing contacts via the command line. It performs full CRUD operations with input validation and CSV-based persistence crafted using modular design and static memory.

What makes it unique? It mirrors real-world logic with structured arrays, uses formatted I/O for clarity, and stores data in a way that opens seamlessly in Excel. No dynamic memory, no libraries just pure C, precision, and purpose.


Name : Vijayalaxmi Shankargouda Biradar

Date : 20/08/2025

# 📝 Description
This Address Book project is a command-line application developed in C using structured programming principles. It allows users to manage contact information—name, phone, and email with full control over:
- Creating new contacts with input validation
- Searching contacts by name, phone, or email (case-insensitive)
- Editing existing contact details
- Deleting contacts with confirmation
- Listing all contacts with optional sorting
- Saving and loading contacts via a CSV file for persistence
The program avoids dynamic memory and external libraries, relying on arrays, structures, and standard file I/O (fopen, fscanf, fprintf).

> *** **Why CSV? – The Jacket Analogy**  
> Choosing a file format is like choosing the right jacket.  
> Suppose Jacket J1 works for both rainy and winter seasons, while Jacket J2 is only for winter and Jacket J3 is only for rain. Naturally, we prefer Jacket J1 because it’s more versatile.

> Similarly, I chose a **CSV file** because it’s flexible and supports multiple needs. It stores contact data in a structured format each contact is saved as a row, and fields like name, phone, and email are separated by commas.

> Internally, it looks like plain text. But when opened in tools like Excel or Google Sheets, those commas are interpreted as column separators, and each line becomes a row.

> So just like Jacket J1, **CSV gives me more features in one format**—it’s readable, portable, structured, and compatible across platforms. That’s why I used it for permanent contact storage in my Address Book system.

# Work Flow :
<img width="2000" height="1123" alt="image" src="https://github.com/user-attachments/assets/6d678416-e0d8-4917-9be4-6a2139aede86" />

# Files included :
contact.h       -   Contains all necessary data types and declares the functions for                        managing contacts.

contact.c       -   Houses the full implementation logic for handling contact                               operations.

file.h          -   Declares functions and structures for reading from and writing to                       data files.

file.c          -   Implements detailed file input/output routines for persistent contact                   storage.

main.c          -   Controls the user interface and orchestrates menu-driven                                interactions.

populate.h      -   Provides declarations for populating the address book with sample entries.

populate.c      -   Implements test data routines for quickly filling the address book.

contacts_data.abook   -   Stores all address book entries in a custom pipe-separated                               format for uniqueness.


# Sample Input/Output :

# Sample I/O 1 : Creating a Contact.

<img width="669" height="423" alt="image" src="https://github.com/user-attachments/assets/01ca1e13-bd27-4148-b93b-e0b921b6f8b5" />

# Sample I/O 2 : Search Contact.
<img width="792" height="630" alt="image" src="https://github.com/user-attachments/assets/879269ae-41cb-49af-b0f4-793559b57087" />

# Sample I/O 3: Edit Contact.

<img width="853" height="782" alt="image" src="https://github.com/user-attachments/assets/5c9c603a-187c-4b83-8697-52721d128702" />

# Sample I/O 4:Deleting a Contact.
<img width="825" height="638" alt="image" src="https://github.com/user-attachments/assets/67c3af74-b392-49df-85aa-ef398f0fae61" />

# Sample I/O 5 : List All Contacts.

<img width="787" height="828" alt="image" src="https://github.com/user-attachments/assets/72d9f2d6-d83d-4217-8ad1-13ab412758c4" />

# Sample I/O 6 : Exiting the Program.

<img width="749" height="274" alt="image" src="https://github.com/user-attachments/assets/01a542b6-1e05-4447-987d-2d026ac06bc7" />

























