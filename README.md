[![Daily GitHub Commit](https://github.com/eDDie-05/contact/actions/workflows/daily-commit.yml/badge.svg)](https://github.com/eDDie-05/contact/actions/workflows/daily-commit.yml)
Contact Management System

A simple Contact Management System that allows users to store, manage, search, update, and delete contact information.

Features
Add new contacts
View all contacts
Search for contacts
Update existing contact information
Delete contacts
Store contact details such as:
Full Name
Phone Number
Email Address
Address
Simple and user-friendly interface
Data management through a structured database
Technologies Used
Python — Application logic
SQLite — Database management
Tkinter — Graphical User Interface (if applicable)
Project Structure
Contact-Management-System/
│
├── main.py
├── database.py
├── contacts.db
├── README.md
└── requirements.txt


The exact files may vary depending on your implementation.

Installation
1. Clone the repository
git clone https://github.com/yourusername/contact-management-system.git

2. Navigate to the project folder
cd contact-management-system

3. Create a virtual environment

On macOS/Linux:

python3 -m venv venv
source venv/bin/activate


On Windows:

python -m venv venv
venv\Scripts\activate

4. Install dependencies
pip install -r requirements.txt


If the project does not have external dependencies, this step can be skipped.

5. Run the application

On macOS/Linux:

python3 main.py


On Windows:

python main.py

How to Use
Add a Contact

Enter the contact's name, phone number, email address, and other required information, then click Add or Save.

View Contacts

Select the View Contacts option to display all saved contacts.

Search

Enter a name, phone number, or email address in the search field to find a specific contact.

Update

Select an existing contact, modify the required information, and click Update.

Delete

Select the contact you want to remove and click Delete.

Database

The system uses SQLite to store contact information locally. The database can contain fields such as:

Field	Description
id	Unique contact ID
name	Contact's full name
phone	Phone number
email	Email address
address	Contact's address
Requirements
Python 3.x
SQLite3
Tkinter (if using a Tkinter GUI)
Future Improvements

Possible improvements include:

User authentication
Contact groups/categories
Profile pictures
Import/export contacts
CSV and Excel support
Cloud database integration
Contact sorting and filtering
Backup and restore functionality
Improved responsive user interface
Author

eDDie

License

This project is available for educational and personal use. You may modify and improve it according to your needs.
