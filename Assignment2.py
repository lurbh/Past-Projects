#Name: Lur Bing Huii
#Student ID: 6212748
#Subject Code: CSIT110

import csv
filePath = "data.csv"

# Display Menu and get's user input
def menu():
    print("1: Display modules average scores")
    print("2: Display modules top scorer")
    print("0: Exit")
    choice = int(input("Enter choice: "))
    # Loop till a valid choice is entered
    if(choice < 0 or choice > 2):
        print("===============================================")
        print("Invalid choice, please enter again")
        print("===============================================")
        choice = menu()
    return choice
    
# Calculate and display average scores for all subject
def display_modules_average_scores():
    csit110sum = 0
    csit121sum = 0
    csit135sum = 0
    csit142sum = 0
    count = 0
    # Opens the data file
    with open(filePath) as csvfile:
        reader = csv.DictReader(csvfile)    
        for row in reader:
            # Sum up scores
            csit110sum += (int)(row['CSIT110'])
            csit121sum += (int)(row['CSIT121'])
            csit135sum += (int)(row['CSIT135'])
            csit142sum += (int)(row['CSIT142'])
            count += 1
    # Calculate average for all subjects
    csit110ave = round(csit110sum/count,2)
    csit121ave = round(csit121sum/count,2)
    csit135ave = round(csit135sum/count,2)
    csit142ave = round(csit142sum/count,2)
    # Print results
    print("===============================================")
    print("Display Modules Average Scores")
    print("===============================================")
    print("{0:<8}|{1:^9}|{2:^9}|{3:^9}".format("CSIT110", "CSIT121", "CSIT135", "CSIT142"))
    print("{0:^8}|{1:^9}|{2:^9}|{3:^9}".format(csit110ave, csit121ave, csit135ave, csit142ave))
    print("===============================================")
    
# Prints the all the people with the high score for a certain subject  
def print_module_top_scorer(subject,score):
    with open(filePath) as csvfile:
        reader = csv.DictReader(csvfile)    
        for row in reader:
            if((int)(row[subject]) == score):
                print("{0:<8}|{1:>11} | {2:<10}".format(subject, row['first_name'], row['last_name']))

# Find and display the top scorers for all subjects
def display_modules_top_scorer():
    csit110max = 0
    csit121max = 0
    csit135max = 0
    csit142max = 0
    # Opens the data file
    with open(filePath) as csvfile:
        reader = csv.DictReader(csvfile)    
        for row in reader:
            # Finds the highest scores for each subject
            if((int)(row['CSIT110']) > csit110max):
                csit110max = (int)(row['CSIT110']) 
            if((int)(row['CSIT121']) > csit121max):
                csit121max = (int)(row['CSIT121']) 
            if((int)(row['CSIT135']) > csit135max):
                csit135max = (int)(row['CSIT135']) 
            if((int)(row['CSIT142']) > csit142max):
                csit142max = (int)(row['CSIT142']) 
    # Prints results
    print("===============================================")
    print("Display modules top scorer")
    print("===============================================")
    print("{0:<8}|{1:^12}|{2:^11}".format("Module", "First Name", "Last Name"))
    print_module_top_scorer("CSIT110",csit110max)
    print_module_top_scorer("CSIT121",csit121max)
    print_module_top_scorer("CSIT135",csit135max)
    print_module_top_scorer("CSIT142",csit142max)
    print("===============================================")
    

# Main program start
print("===============================================")
print("Welcome to Students' Result System")
print("===============================================")
#get user choice
choice = menu()
# loop till user exits program
while(not (choice == 0)):
    if(choice == 1):
        display_modules_average_scores()
    elif(choice == 2):
        display_modules_top_scorer()
    choice = menu()
print("===============================================")
print("Thank you for using Students' Result System")
print("===============================================")
        