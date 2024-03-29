import csv
filePath = "data.csv"
loop = True
while loop:
    with open(filePath) as csvfile:
        reader = csv.DictReader(csvfile)
        studentid = input("Enter Student ID: ")
        for row in reader:
            if row['student_id'] == studentid:
                print("=================")
                print("Student's details")
                print("=================")
                print("{0:<10} | {1:^10} | {2:<10}".format("Student ID", "First Name", "Last Name"))
                print("{0:<10} | {1:>10} | {2:<10}".format(row['student_id'], row['first_name'], row['last_name']))
                print("===============================================")
                print("{0:<8}|{1:^9}|{2:^9}|{3:^9}|{4:>8}".format("CSIT110", "CSIT121", "CSIT135", "CSIT142", "Average"))
                average = ((int)(row['CSIT110']) + (int)(row['CSIT121']) + (int)(row['CSIT135']) + (int)(row['CSIT142'])) / 4
                average = round(average, 2)
                print("{0:^8}|{1:^9}|{2:^9}|{3:^9}|{4:^8}".format(row['CSIT110'], row['CSIT121'], row['CSIT135'], row['CSIT142'], average))
                print("===============================================")
                loop = False
                break
        else:
            print("No student record found")
