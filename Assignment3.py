#Name: Lur Bing Huii
#Student ID: 6212748
#Subject Code: CSIT110

import csv
filePath = "data.csv"

def isValidStudentIDFormat(studentid):
    if(len(studentid) == 9):
        if((studentid[0] == 'S') or (studentid[0] == 's')):
            if(((studentid[8] >= 'B') and (studentid[8] <= 'M')) or ((studentid[8] >= 'b') and (studentid[8] <= 'm'))):
                for x in range(1,8):
                    if((studentid[x] < '0') or (studentid[x] > '9')):
                        return "Doesn't have 7 numbers between the first and the last letter."
                else:
                    return True
            else:
                return "Doesn't end with a letter between B-M"
        else:
            return "Doesn't start with the letter S"
    else:
        return "Length of Student ID is not 9"

def isValidStudentIDLetter(studentid):
    table = {'0':'B', '1':'C', '2':'D', '3':'E', '4':'F', '5':'G', '6':'H', '7':'I', '8':'J', '9':'K', '10':'L'}
    s1 = (int)(studentid[1]) * 2 
    s2 = (int)(studentid[2]) * 7 
    s3 = (int)(studentid[3]) * 6 
    s4 = (int)(studentid[4]) * 5 
    s5 = (int)(studentid[5]) * 4 
    s6 = (int)(studentid[6]) * 3 
    s7 = (int)(studentid[7]) * 2 
    sumresults = s1 + s2 + s3 + s4 + s5 + s6 + s7
    remainder = sumresults % 11
    if(studentid[8] == table[str(remainder)]):
        return True
    else:
        return False

with open(filePath) as csvfile:
    reader = csv.DictReader(csvfile) 
    print("{0:<14} {1:<14} {2:<14} {3:<}".format("First Name", "Last Name", "Student ID", "Comments"))
    for row in reader:
        formatcheck = isValidStudentIDFormat(row['student_id'])
        if(not isinstance(formatcheck,bool)):
            print("{0:<14} {1:<14} {2:<14} {3:<}".format(row['first_name'], row['last_name'], row['student_id'], formatcheck))
        elif (not isValidStudentIDLetter(row['student_id'])):
            print("{0:<14} {1:<14} {2:<14} {3:<}".format(row['first_name'], row['last_name'], row['student_id'], "Invalid last letter"))