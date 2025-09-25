# Address Book -Project
A robust, menu-driven Address Book application built in C for managing contacts via the command line. It performs full CRUD operations with input validation and CSV-based persistence crafted using modular design and static memory.

What makes it unique? It mirrors real-world logic with structured arrays, uses formatted I/O for clarity, and stores data in a way that opens seamlessly in Excel. No dynamic memory, no libraries—just pure C, precision, and purpose.


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













