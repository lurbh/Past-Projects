#Name: Lur Bing Huii
#Student ID: 6212748
#Subject Code: CSIT110

#Error checking 1
#Check for invalid menu choice selection(Number not in menu or letter).
#The program will check if the user had entered 1 2 or 3 in the main menu selection.
#If an invalid choice is enter, the user is asked to re-enter the choice again
#Ensures user key in a valid id format
#Handles if id to delete is not in the data

import csv
filePath = "data.csv"

# Load data from data file
def loaddata():
    data = {}
    # Opens the data file
    with open(filePath) as csvfile:
        reader = csv.DictReader(csvfile)    
        for row in reader:  
            # get the first and last name 
            name = {"first_name": row['first_name'], "last_name": row['last_name']}
            # insert id with name into dictionary
            data[row['student_id']] = name
        return data

# Display Menu and get's user input
def menu():
    # print the options for menu
    print("Student Records Management System")
    print("1: Insert a new student")
    print("2: Delete a student")
    print("3: Save data to file and exit")
    choice = input("Enter choice: ")
    print()
    # Loop till a valid choice is entered
    if(not choice.isdigit() or int(choice) < 1 or int(choice) > 3) :
        print("Invalid choice, please enter again")
        print()
        choice = menu()
    choice = int(choice)
    return choice

# Checks the format for the student id 
def isValidStudentIDFormat(studentid):
    # Check length
    if(len(studentid) == 9):
        # Check First letter
        if((studentid[0] == 'S') or (studentid[0] == 's')):
            # Check Last Letter
            if(((studentid[8] >= 'B') and (studentid[8] <= 'M')) or ((studentid[8] >= 'b') and (studentid[8] <= 'm'))):
                # Check for 7 numbers between first and last letter
                for x in range(1,8):
                    if((studentid[x] < '0') or (studentid[x] > '9')):
                        return False
                else:
                    return True
            else:
                return False
        else:
            return False
    else:
        return False

# Insert student data 
def insertstudent(data):
    print("Insert a new student")
    # get user to enter data
    fname = input("Enter first name: ")
    lname = input("Enter last name: ")
    studentid = input("Enter student id: ")
    while(not isValidStudentIDFormat(studentid)):
        print("Invalid Student id format")
        studentid = input("Enter student id: ")
    # set name and id and insert data into dictionary
    name = {"first_name": fname , "last_name": lname}
    data[studentid] = name
    print()
    print("New Student Record Inserted")
    return data

# Delete student data    
def deletestudent(data):
    print("Delete a student")
    # get user to enter student id to delete
    studentid = input("Enter student id to delete: ")
    while(not isValidStudentIDFormat(studentid)):
        print("Invalid Student id format")
        studentid = input("Enter student id: ")    
    delobj = data.get(studentid)
    print()
    # if id is stored delete it
    if(delobj):
        del delobj
        print("Student Record Deleted")
    else:
        print("No Student with that id in the Record")        
    return data

# write data into data file
def writedata(data):
    with open(filePath, 'w', newline='') as csvfile:
        fieldnames = ['first_name', 'last_name', 'student_id']
        writer = csv.DictWriter(csvfile, fieldnames=fieldnames)
        writer.writeheader()
        # go through data and write the data into file
        for i in data.keys():
            writer.writerow({'first_name': data.get(i).get("first_name"), 
                             'last_name': data.get(i).get("last_name"),
                             'student_id': i})
        print("Data file saved.")

# Main program start
# Load data from file
dictionary = loaddata()
# get user choice
choice = menu()
# loop till user exits program
while(not (choice == 3)):
    if(choice == 1):
        # insert student
        dictionary = insertstudent(dictionary)
    elif(choice == 2):
        # delete student
        dictionary = deletestudent(dictionary)
    print()
    choice = menu()
# Write data to file
writedata(dictionary)
print("Thank you for using Student Records Management System")