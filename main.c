#include <stdio.h>
#include <stdlib.h>
#include <string.h>

struct studentRecordDetail
{
    char studentId[15];
    char studentPassword[50];
    char studentFirstName[20];
    char studentLastName[20];
    char address[75];
    int dateOfBirthY;
    int dateOfBirthM;
    int dateOfBirthD;
    char gender[8];
    char mobileNumber[15];
    char emailAddress[50];
    char contactPersonName[20];
    char contactPersonNumber[15];
};
struct adminRecordDetail
{
    char adminId[15];
    char adminPassword[15];
};
struct courseDetail
{
    char courseId[15];
    char courseName[30];
    char studentId[15];
};
struct examResultSheet
{
    char examId[15];
    char courseId[15];
    char examName[50];
    char studentId[15];
    int marks;
    char grade;
};
struct attendanceDetail
{
    char courseId[15];
    char courseName[30];
    char studentId[15];
    char PorA[1];
    int dateY;
    int dateM;
    int dateD;

};


void readBiodata(struct studentRecordDetail student[],int *topstudentIndex);
void readUserNameAndPassword(char [],char []);
char determineUserType(char);
void printAdminMainMenu(int *);
void printStudentMainMenu(int *);
void printResultGraph(int *aCount, int *bCount, int *cCount, int *sCount, int *fCount);
void goBack(int *);
void readExamResult(struct examResultSheet exam[],int *topExamIndex);
char verifyUserIdAndPassword(struct adminRecordDetail admin[],struct studentRecordDetail student[], char userId[], char userPassword[], char *userType, int *topAdminIndex, int *topStudentIndex);
void printExamResult(struct examResultSheet exam[], int *topExamIndex);
void printAttendance(struct attendanceDetail attendance[],int *topAttendance);
void readAttendance(struct attendanceDetail attendance[],struct courseDetail course[],int *topAttendanceId,int *topCourseId);
void enrollToCourse(char studentId[],struct courseDetail course[], int *topCourseIndex);

void searchAndUpdateStudentDetail(struct studentRecordDetail student[],int *topIndex,char searchId[]);
void searchAndGetStudentDetail(struct studentRecordDetail student[],int *topIndex,char searchId[]);
void searchAndGetCourseDetail(struct courseDetail course[],int *topIndex,char searchId[]);
void searchAndGetExamResult(struct examResultSheet exam[],int *topIndex,char searchId[]);
void searchAndGetAttendance(struct attendanceDetail attendance[],int *topIndex,char searchId[]);
void searchAndDeleteStudentDetail(struct studentRecordDetail student[],int *topIndex,char searchId[]);
void readAdminDetails(struct adminRecordDetail admin[],int *topAdminIndex);
int calGrade(struct examResultSheet exam[],char searchCourseId[],int *aCount,int *bCount, int *cCount, int *sCount, int *fCount,int *topExamIndex);

int checkStudentId(struct studentRecordDetail student[],int *topstudentIndex);
int checkValidDate(int year,int month,int day);
int checkGender(char student[]);
int checkPhoneNumber(char mobileNumber[]);
int checkEmailAddress(char emailAddress[]);
int checkName(char name[]);
int checkMark(int *marks);
int checkAdminId(struct adminRecordDetail admin[],int *topAdminIndex);

int checkForId(struct studentRecordDetail student[],int *topIndex,char searchId[]);

char getGrade(int *marks);

int main()
{
    struct studentRecordDetail student[50];
    struct adminRecordDetail admin[50];
    struct courseDetail course[100];
    struct examResultSheet exam[100];
    struct attendanceDetail attendance[100];

    int selection = 0;
    char userId[15];
    char userPassword[30];
    char userType = '0';
    char validation = '0';
    int logoutSelection = 1;
    int selectionToUpdate = 0;

    int topstudentIndex = 0;
    int topAdminIndex = 0;
    int topExamIndex = 0;
    int topAttendanceId = 0;
    int topCourseId = 0;

    char searchId[10];

    int aCount = 0;
    int bCount = 0;
    int cCount = 0;
    int sCount = 0;
    int fCount = 0;

    int validExamId = 0;

    FILE *fptr = fopen("adminDetails.txt","r");
        while (!feof(fptr))
        {
            fscanf(fptr, "%s %s\n",&admin[topAdminIndex].adminId, &admin[topAdminIndex].adminPassword);
            topAdminIndex++;
        }
        fclose(fptr);

        FILE *fptrToStudentDetails = fopen("studentDetails.txt", "r");
        while (!feof(fptrToStudentDetails))
        {

            fscanf(fptrToStudentDetails, "%s %s %s %s %d %d %d %s %s %s %s %s %s\n",&student[topstudentIndex].studentId, &student[topstudentIndex].studentFirstName, &student[topstudentIndex].studentLastName, &student[topstudentIndex].address, &student[topstudentIndex].dateOfBirthY, &student[topstudentIndex].dateOfBirthM, &student[topstudentIndex].dateOfBirthD, &student[topstudentIndex].gender, &student[topstudentIndex].mobileNumber, &student[topstudentIndex].emailAddress, &student[topstudentIndex].contactPersonName, &student[topstudentIndex].contactPersonNumber, &student[topstudentIndex].studentPassword);
            topstudentIndex++;
        }
        fclose(fptrToStudentDetails);

        FILE *fptrCourseDetail = fopen("courseDetails.txt", "r");
        while (!feof(fptrCourseDetail))
        {
            fscanf(fptrCourseDetail, "%s %s %s\n",course[topCourseId].studentId, course[topCourseId].courseId, course[topCourseId].courseName );
            topCourseId++;
        }
        fclose(fptrCourseDetail);

        FILE *fptrExamDetail = fopen("examDetails.txt", "r");
        while (!feof(fptrExamDetail))
        {
            fscanf(fptrExamDetail, "%s %s %s %d %c\n", &exam[topExamIndex].examId, &exam[topExamIndex].courseId, &exam[topExamIndex].studentId, &exam[topExamIndex].marks, &exam[topExamIndex].grade);
            topExamIndex++;
        }
        fclose(fptrExamDetail);

        FILE *fptrAttendanceDetails = fopen("attendanceDetails.txt", "r");
        while (!feof(fptrAttendanceDetails))
        {
            fscanf(fptr, "%s %s %s %d %d %d %s\n", &attendance[topAttendanceId].studentId, &attendance[topAttendanceId].courseId, &attendance[topAttendanceId].courseName, &attendance[topAttendanceId].dateY, &attendance[topAttendanceId].dateM, &attendance[topAttendanceId].dateD, &attendance[topAttendanceId].PorA);
            topAttendanceId++;
        }
        fclose(fptrAttendanceDetails);

    for (int i = 0; logoutSelection != 0; i++)
    {
        system("cls");
        logoutSelection = 0;
        int backSelection = 0;
//login
        readUserNameAndPassword(userId,userPassword);
        userType = determineUserType(userId[0]);
        validation = verifyUserIdAndPassword(admin,student,userId,userPassword,&userType, &topAdminIndex, &topstudentIndex);

        if(userType == 'A' && validation == 'V')
        {
          for(int i=0; backSelection != 2;i++)
          {

            printAdminMainMenu(&selection);

            switch (selection)
            {
        case 1:
            readBiodata(student,&topstudentIndex);
            enrollToCourse(student[topstudentIndex].studentId,course,&topCourseId);
            topstudentIndex+=1;
            goBack(&backSelection);
            break;
        case 2:
            system("cls");
            printf("\n\n            **STUDENT INFORMATION SYSTEM**\n\n");
            printf("                     **Update**\n\n");
            printf("Search Student ID : ");
            scanf("%s",& searchId);
            printf("1. Update Personal Details\n");
            printf("2. Enroll to New Course\n");
            printf("\nYour Selection          : ");
            scanf("%d", &selectionToUpdate);
            if(selectionToUpdate == 1)
            {
                searchAndUpdateStudentDetail(student, &topstudentIndex, searchId);
            }
            else if(selectionToUpdate == 2)
            {
                int validID = 0;
                validID = checkForId(student,&topstudentIndex, searchId);
                if(validID == 1)
                {
                    enrollToCourse(searchId,course,&topCourseId);
                }
            }
            goBack(&backSelection);
            break;
        case 3:
            system("cls");
            printf("\n\n            **STUDENT INFORMATION SYSTEM**\n\n");
            printf("                     **Delete**\n\n");
            printf("Search Student ID : ");
            scanf("%s",& searchId);
            searchAndDeleteStudentDetail(student,&topstudentIndex, searchId);
            goBack(&backSelection);
            break;
        case 4:
            readExamResult(exam,&topExamIndex);
            goBack(&backSelection);
            break;
        case 5:
            readAttendance(attendance,course,&topAttendanceId,&topCourseId);
            goBack(&backSelection);
            break;
        case 6:
            system("cls");
            printf("\n\n            **STUDENT INFORMATION SYSTEM**\n\n");
            printf("                     **Search**\n\n");
            printf("Search Student ID : ");
            scanf("%s",& searchId);
            searchAndGetStudentDetail(student,&topstudentIndex,searchId);
            int validID = 0;
            validID = checkForId(student,&topstudentIndex, searchId);
            if(validID == 1)
            {
                searchAndGetCourseDetail(course,&topCourseId,searchId);
            }
            goBack(&backSelection);
            break;
        case 7:
            printExamResult(exam,&topExamIndex);
            goBack(&backSelection);
            break;
        case 8:
            aCount = 0;
            bCount = 0;
            cCount = 0;
            sCount = 0;
            fCount = 0;
            char searchExamId[10];
            system("cls");
            printf("\n\n            **STUDENT INFORMATION SYSTEM**\n\n");
            printf("                      **Result Graph**\n\n");
            printf("Enter Exam ID  : ");
            scanf("%s", &searchExamId);
            validExamId = calGrade(exam,searchExamId,&aCount,&bCount,&cCount,&sCount,&fCount,&topExamIndex);
            if(validExamId == 1)
            {
                printResultGraph(&aCount,&bCount,&cCount,&sCount,&fCount);
            }
            goBack(&backSelection);
            break;
        case 9:
            printAttendance(attendance,&topAttendanceId);
            goBack(&backSelection);
            break;
        case 10:
            readAdminDetails(admin, &topAdminIndex);
            goBack(&backSelection);
            break;
        case 11:
            logoutSelection = 1;
            backSelection = 2;
            break;
        case 12:
            backSelection = 2;
            /*aCount = 0;
            bCount = 0;
            cCount = 0;
            sCount = 0;
            fCount = 0;
            char searchExamId[10] = "EX0001";
            calGrade(exam,searchExamId,&aCount,&bCount,&cCount,&sCount,&fCount,&topExamIndex);
            printResultGraph(&aCount,&bCount,&cCount,&sCount,&fCount);
            goBack(&backSelection);*/
            break;
        default:
            system("cls");
            printf("Invalid Input");
            goBack(&backSelection);
            }
          }
        }
        else if(userType == 'S' && validation == 'V')
        {
            for(int j=0; backSelection!= 2; j++)
            {

                printStudentMainMenu(&selection);
                switch(selection)
                {
                case 1:
                    searchAndGetStudentDetail(student,&topstudentIndex,userId);
                    searchAndGetCourseDetail(course,&topCourseId,userId);
                    goBack(&backSelection);
                    break;
                case 2:
                    system("cls");
                    searchAndGetAttendance(attendance, &topAttendanceId, userId);
                    goBack(&backSelection);
                    break;
                case 3:
                    system("cls");
                    searchAndGetExamResult(exam,&topExamIndex,userId);
                    goBack(&backSelection);
                    break;
                case 4:
                    logoutSelection = 1;
                    backSelection = 2;
                    break;
                case 5:
                    backSelection = 2;
                    break;
                default:
                    system("cls");
                    printf("Invalid Input");
                    goBack(&backSelection);
                }
            }
        }
        else
        {
            int goToLoginProcess = 0;

            printf("\nYour User ID or Password is Wrong.Please try again.\n");
            printf("1. Try Again\n");
            printf("2. Exit\n");
            printf("Your Selection : ");
            scanf("%d",& goToLoginProcess);
            if (goToLoginProcess == 1)
            {
                logoutSelection = 1;
            }

        }
    }




    return 0;
}

//*******************************************************OUTPUT
//adminMainMenu
void printAdminMainMenu(int *selection)
{
    system("cls");
    printf("\n\n            **STUDENT INFORMATION SYSTEM**\n\n");
    printf("                   **Main Menu**\n\n");
    printf(" 1. Add New Student\n");
    printf(" 2. Update Student Information\n");
    printf(" 3. Delete Student\n");
    printf(" 4. Add Exam Result\n");
    printf(" 5. Mark Attendance\n");
    printf(" 6. View student Information\n");
    printf(" 7. View result sheet\n");
    printf(" 8. View Exam Result Graph\n");
    printf(" 9. View Attendance\n");
    printf("10. Add Admin\n");
    printf("11. Logout \n");
    printf("12. End \n");
    printf("\n\n    Your Selection :");
    scanf ("%d", selection);

}

void printExamResult(struct examResultSheet exam[], int *topExamIndex)
{
    system("cls");
    int topExamIndexT = *topExamIndex;
    int i=0;
        printf("\n                       **STUDENT INFORMATION SYSTEM**\n\n");
        printf("                                **Result Sheet**\n\n");
        printf("Exam ID             Course ID              Student ID               Marks              Grade\n\n");
    for (i=0; i<topExamIndexT;i++)
    {
        printf("%7s       %15s              %10s                 %3d                  %c\n",exam[i].examId, exam[i].courseId, exam[i].studentId, exam[i].marks, exam[i].grade);
    }
}

void printAttendance(struct attendanceDetail attendance[],int *topAttendance)
{
    system("cls");
    int topAttendanceTemp = *topAttendance;
    int i = 0;
    printf("\n\n            **STUDENT INFORMATION SYSTEM**\n\n");
    printf("                    **Attendance**\n\n");
    printf("Course ID         Course Name              Date         Student ID           Present/Absent   \n");
    for (i=0; i<topAttendanceTemp;i++)
    {
        printf("%9s  %18s        %4d/%02d/%02d           %8s                        %s\n",attendance[i].courseId, attendance[i].courseName, attendance[i].dateY, attendance[i].dateM, attendance[i].dateD, attendance[i].studentId, attendance[i].PorA);
    }

}

//studentMainMenu
void printStudentMainMenu(int *selection)
{
    system("cls");
    printf("\n\n            **STUDENT INFORMATION SYSTEM**\n\n");
    printf("                   **Main Menu**\n\n");
    printf("1. View Profile\n");
    printf("2. View Attendance\n");
    printf("3. View Exam Result\n");
    printf("4. Logout \n");
    printf("5. End \n");
    printf("\n\n    Your Selection :");
    scanf ("%d", selection);
}


//*****************************************************************INPUT

void readBiodata(struct studentRecordDetail student[],int *topstudentIndex)
{
    system("cls");
    int validName = 0;
    int invalidGender = 1;
    int validateEmail = 0;
    int phoneNumVallidate = 0;
    int guardianPhoneNumVallidate = 0;
    int validDob = 0;
    int studentId = 1;
    int topstudentIndexT = *topstudentIndex;
    char temp;


        printf("\n                       **STUDENT INFORMATION SYSTEM**\n\n");
        printf("                             **Add New Student**\n\n");
        printf("\nPlease don't use space when entering data\n\n");
        while(studentId == 1)
        {
            printf("Enter student ID                           : ");
            scanf("%s",& student[topstudentIndexT].studentId);
            studentId = checkStudentId(student,&topstudentIndexT);
        }
        printf("Enter Student Password                     : ");
        scanf("%s", &student[topstudentIndexT].studentPassword);

        while(validName != 1)
        {
            printf("Enter Student First Name                   : ");
            scanf("%c",&temp);
            scanf("%[^\n]",& student[*topstudentIndex].studentFirstName);
            validName = checkName(student[*topstudentIndex].studentFirstName);
        }
        validName = 0;
        while(validName != 1)
        {
            printf("Enter Last Name                            : ");
            scanf("%c",&temp);
            scanf("%[^\n]",& student[*topstudentIndex].studentLastName);
            validName = checkName(student[*topstudentIndex].studentLastName);
        }
        printf("Enter student address                      : ");
        scanf("%c",&temp);
        scanf("%[^\n]",& student[*topstudentIndex].address);
        while (validDob == 0)
        {
        printf("Enter student birthday(Year/Month/Date)    : ");
        scanf("%c",&temp);
        scanf("%d/%d/%d",& student[*topstudentIndex].dateOfBirthY ,& student[*topstudentIndex].dateOfBirthM ,& student[*topstudentIndex].dateOfBirthD);
        validDob = checkValidDate(student[*topstudentIndex].dateOfBirthY,student[*topstudentIndex].dateOfBirthM,student[*topstudentIndex].dateOfBirthD);
        }

        while (invalidGender == 1)
        {
        printf("Enter student gender                       : ");
        scanf("%s",& student[*topstudentIndex].gender);
        invalidGender = checkGender(student[*topstudentIndex].gender);
        }

       while(phoneNumVallidate != 10)
        {
            phoneNumVallidate = 0;
            printf("Enter student mobile number                : ");
            scanf("%s",& student[*topstudentIndex].mobileNumber);
            phoneNumVallidate = checkPhoneNumber(student[*topstudentIndex].mobileNumber);
        }
        scanf("%c",&temp);
        while(validateEmail != 1)
        {
            printf("Enter student email address                : ");
            scanf(" %[^\n]",& student[*topstudentIndex].emailAddress);
            validateEmail = checkEmailAddress(student[*topstudentIndex].emailAddress);
        }

        printf("Enter student contact person name          : ");
        scanf("%c",&temp);
        scanf("%[^\n]",& student[*topstudentIndex].contactPersonName);

        while(guardianPhoneNumVallidate != 10)
        {
           guardianPhoneNumVallidate = 0;
           printf("Enter student contact person contact number: ");
           scanf(" %s",& student[topstudentIndexT].contactPersonNumber);
           guardianPhoneNumVallidate = checkPhoneNumber(student[topstudentIndexT].contactPersonNumber);

        }
        FILE *fptr = fopen("studentDetails.txt", "a");
        fprintf(fptr, "%s %s %s %s %d %d %d %s %s %s %s %s %s\n",student[topstudentIndexT].studentId, student[*topstudentIndex].studentFirstName,student[*topstudentIndex].studentLastName,student[*topstudentIndex].address,student[*topstudentIndex].dateOfBirthY,student[*topstudentIndex].dateOfBirthM,student[*topstudentIndex].dateOfBirthD,student[*topstudentIndex].gender,student[*topstudentIndex].mobileNumber,student[*topstudentIndex].emailAddress,student[*topstudentIndex].contactPersonName,student[topstudentIndexT].contactPersonNumber,student[topstudentIndexT].studentPassword);
        fclose(fptr);

}

void enrollToCourse(char studentId[],struct courseDetail course[], int *topCourseIndex)
{
    int topCourseIndexTemp = *topCourseIndex;
    int addAnother = 0;
    FILE *fptr = fopen("courseDetails.txt", "a");
    while(addAnother != 2)
    {
        system("cls");
        printf("\n                       **STUDENT INFORMATION SYSTEM**\n\n");
        printf("                             **Enroll to Course**\n\n");
        strcpy(course[topCourseIndexTemp].studentId,studentId);
        printf("Enter Course ID             :");
        scanf("%s",& course[topCourseIndexTemp].courseId);
        printf("Enter Course Name           :");
        scanf("%s",& course[topCourseIndexTemp].courseName);

        fprintf(fptr, "%s %s %s\n",course[topCourseIndexTemp].studentId, course[topCourseIndexTemp].courseId, course[topCourseIndexTemp].courseName);
        topCourseIndexTemp+=1;
        *topCourseIndex = topCourseIndexTemp;
        printf("\n\nEnroll to another course\n");
        printf("1. Yes\n");
        printf("2. No\n");
        printf("Your selection : ");
        scanf("%d",& addAnother);
    }
    fclose(fptr);

}

void readUserNameAndPassword(char userId[],char userPassword[])
{
    printf("\n\n            **STUDENT INFORMATION SYSTEM**\n\n");
    printf("                 **Login Process**\n\n");
    printf("Enter User ID       : ");// admin user id like AD###### and student user id like ST######
    scanf("%s", userId);
    printf("Enter User Password : ");
    scanf("%s", userPassword);

}
void readExamResult(struct examResultSheet exam[],int *topExamIndex)
{
    system("cls");
    int i=0;
    int validMarks = 0;
    char examId[8];
    char courseId[15];
    int numOfResult = 0;
    int topExamIndexT = *topExamIndex;
    FILE *fptr = fopen("examDetails.txt", "a");

    {
        printf("\n                       **STUDENT INFORMATION SYSTEM**\n\n");
        printf("                           **Create Result Sheet**\n\n");
        printf("Enter Exam Id                         : ");
        scanf("%s",& examId);
        printf("Enter course Id                       : ");
        scanf("%s",& courseId);
        printf("How many results do you want to enter : ");
        scanf("%d", &numOfResult);
        for (i=0; i< numOfResult ;i++)
        {
        strcpy(exam[topExamIndexT].examId,examId);
        strcpy(exam[topExamIndexT].courseId,courseId);
        printf("Enter Student Id                      : ");
        scanf("%s",& exam[topExamIndexT].studentId);
        validMarks = 0;
        while (validMarks != 1)
        {
        printf("Enter Marks                           : ");
        scanf("%d",& exam[topExamIndexT].marks);
        validMarks = checkMark(& exam[topExamIndexT].marks);
        }
        exam[topExamIndexT].grade = getGrade(&exam[topExamIndexT].marks);

        fprintf(fptr, "%s %s %s %d %c\n",exam[topExamIndexT].examId, exam[topExamIndexT].courseId, exam[topExamIndexT].studentId, exam[topExamIndexT].marks, exam[topExamIndexT].grade);
        topExamIndexT+=1 ;
        *topExamIndex = topExamIndexT;
        }
        fclose(fptr);
    }
}

void readAttendance(struct attendanceDetail attendance[],struct courseDetail course[],int *topAttendanceId,int *topCourseId)
{
    system("cls");
    int topAttendanceIdTemp = *topAttendanceId;
    int topCourseIdTemp = *topCourseId;
    char courseId[10];
    int dateY=0,dateM=0,dateD=0;
    int noSearchResult = 0;
    printf("\n                       **STUDENT INFORMATION SYSTEM**\n\n");
    printf("                                  **Attendance**\n\n");
    printf("Enter Course ID        : ");
    scanf("%s",& courseId);
    printf("Enter Date             : ");
    scanf("%d/%d/%d",& dateY,& dateM,& dateD);
    FILE *fptr = fopen("attendanceDetails.txt","a");
    for(int i=0; i<topCourseIdTemp;i++)
    {
        if(strcmp(courseId,course[i].courseId) == 0)
        {
            strcpy(attendance[topAttendanceIdTemp].studentId,course[i].studentId);
            strcpy(attendance[topAttendanceIdTemp].courseId,courseId);
            strcpy(attendance[topAttendanceIdTemp].courseName,course[i].courseName);
            attendance[topAttendanceIdTemp].dateY = dateY;
            attendance[topAttendanceIdTemp].dateM = dateM;
            attendance[topAttendanceIdTemp].dateD = dateD;
            printf("Student ID             : %s\n",& attendance[topAttendanceIdTemp].studentId);
            printf("Present or Absent(P/A) : ");
            scanf("%s",& attendance[topAttendanceIdTemp].PorA);

            fprintf(fptr, "%s %s %s %d %d %d %s\n",attendance[topAttendanceIdTemp].studentId, attendance[topAttendanceIdTemp].courseId, attendance[topAttendanceIdTemp].courseName, attendance[topAttendanceIdTemp].dateY, attendance[topAttendanceIdTemp].dateM, attendance[topAttendanceIdTemp].dateD, attendance[topAttendanceIdTemp].PorA);

            noSearchResult+=1;
            topAttendanceIdTemp++;
            *topAttendanceId = topAttendanceIdTemp;
        }
    }
    fclose(fptr);
    if(noSearchResult == 0)
    {
        printf("Invalid Course ID\n");
    }
}

void searchAndGetStudentDetail(struct studentRecordDetail student[],int *topIndex,char searchId[])
{
    int tempTopIndex = *topIndex;
    int i = 0;
    int searchResult = 0;
    for( i=0; i<tempTopIndex; i++)
    {
        if(strcmp(student[i].studentId,searchId) == 0)
        {
            system("cls");
            printf("\n\n            **STUDENT INFORMATION SYSTEM**\n\n");
            printf("              **View Student Information**\n\n");
            printf("ID                            : %s\n", student[i].studentId);
            printf("Name                          : %s %s\n", student[i].studentFirstName,student[i].studentLastName);
            printf("Address                       : %s\n", student[i].address);
            printf("Birthday                      : %4d/%02d/%02d\n",student[i].dateOfBirthY , student[i].dateOfBirthM , student[i].dateOfBirthD);
            printf("Gender                        : %s\n", student[i].gender);
            printf("Contact Number                : %s\n", student[i].mobileNumber);
            printf("Email Address                 : %s\n", student[i].emailAddress);
            printf("Contact person name           : %s\n", student[i].contactPersonName);
            printf("contact person contact number : %s\n", student[i].contactPersonNumber);
            searchResult = 1;
        }
    }
    if(searchResult!= 1)
        {
            printf("\nNo Search Result Found\n");
        }

}

void searchAndGetCourseDetail(struct courseDetail course[],int *topIndex,char searchId[])
{
    int searchResult = 0;
    int tempTopIndex = *topIndex;
    printf("\nEnrolled Courses              :   Course Id            Course Name\n");
    for(int i=0; i<tempTopIndex; i++)
    {
        if(strcmp(course[i].studentId,searchId) == 0)
        {
            printf("                              : %11s    %20s\n", course[i].courseId, course[i].courseName);
            searchResult = 1;
        }

    }
    if(searchResult != 1)
    {
        printf("\nNo enrolled Courses\n");
    }
}

void searchAndGetExamResult(struct examResultSheet exam[],int *topIndex,char searchId[])
{
    int searchResult = 0;
    int tempTopIndex = *topIndex;
    printf("\n                       **STUDENT INFORMATION SYSTEM**\n\n");
    printf("                                 **Result Sheet**\n\n");
    printf("Exam ID             Course ID              Student ID               Marks              Grade\n\n");
    for(int i=0; i<tempTopIndex; i++)
    {
        if(strcmp(exam[i].studentId,searchId) == 0)
        {
            printf("%7s       %15s              %10s                 %3d                  %c\n",exam[i].examId, exam[i].courseId, exam[i].studentId, exam[i].marks, exam[i].grade);
            searchResult = 1;
        }

    }
    if(searchResult != 1)
    {
        printf("\nNo Results Found.\n");
    }
}

void searchAndGetAttendance(struct attendanceDetail attendance[],int *topIndex,char searchId[])
{
    int searchResult = 0;
    int tempTopIndex = *topIndex;
    printf("\n\n            **STUDENT INFORMATION SYSTEM**\n\n");
    printf("                    **Attendance**\n\n");
    printf("Course ID          Course Name              Date         Present/Absent   \n");
    for(int i=0; i<tempTopIndex; i++)
    {
        if(strcmp(attendance[i].studentId,searchId) == 0)
        {
            printf("%9s   %18s        %4d/%02d/%02d                      %s\n",attendance[i].courseId, attendance[i].courseName, attendance[i].dateY, attendance[i].dateM, attendance[i].dateD, attendance[i].PorA);
            searchResult = 1;
        }

    }
    if(searchResult != 1)
    {
        printf("\nNo Search Results.\n");
    }
}


int checkStudentId(struct studentRecordDetail student[],int *topstudentIndex)
{
    int studentIdTypeValidate = 0;
    int dublicateStudentId = 0;
    int topstudentIndexT = *topstudentIndex;
    int studentIdValidate = 0;



            studentIdTypeValidate = 0;
            dublicateStudentId = 0;
            if(student[topstudentIndexT].studentId[0] == 'S' && student[topstudentIndexT].studentId[1] == 'T' )
            {
                studentIdTypeValidate = 1;
                for(int i=0; i<topstudentIndexT; i++)
                {
                    if(strcmp(student[i].studentId,student[topstudentIndexT].studentId) == 0)
                    {
                        dublicateStudentId = 1;
                    }
                }
            }

        if(studentIdTypeValidate != 1 || dublicateStudentId == 1)
            {
                printf("Invalid Student ID type or duplicate ID. ID(STxxxxx)\n");
                studentIdValidate = 1;
            }
        else
            {
                studentIdValidate = 0;
            }
    return studentIdValidate;
}


int checkValidDate(int year,int month,int day)
{
    int validDob = 0;
        {
            validDob = 0;
            if(year > 1900 && year < 2020)
            {
                if(month > 1 && month <=12)
                {
                    if((day >= 1 && day <= 31) && (month == 1 || month == 3 || month == 5 || month == 7 || month == 8 || month == 10 || month == 12 ))
                    {
                        validDob = 1;
                    }
                    else if((day >= 1 && day <= 30) && (month == 4 || month == 6 || month == 9 || month == 11 ))
                    {
                        validDob = 1;
                    }
                    else if((day >= 1 && day <= 28) && month == 2)
                    {
                        validDob = 1;
                    }
                    else if((day == 29 && month == 2) && (year%400 == 0 || (year%4 == 0 && year%100 != 0)))
                    {
                        validDob = 1;
                    }
                    else
                    {
                        validDob = 0;
                    }
                }
            else
                {
                   validDob = 0;
                }
           }
        else
         {
            validDob = 0;
         }
        if(validDob != 1)
         {
            printf("Invalid Date\n");
         }
      }
    return validDob;
}

int checkPhoneNumber(char mobileNumber[])
{

    int phoneNumVallidate = 0;
    for (int j=0; j<10; j++)
    {
        if(mobileNumber[j] >= 48 && mobileNumber[j] <= 57 && strlen(mobileNumber)== 10)
        {
            phoneNumVallidate+=1;
        }
    }
    if(phoneNumVallidate != 10)
    {
        printf("Invalid Mobile Number\n");
    }
    return phoneNumVallidate;
}


int checkGender(char student[])
{
    int invalidGender = 0;

    if(strcmp(student,"Male") != 0 &&  strcmp(student,"male") != 0 && strcmp(student,"Female")!= 0 && strcmp(student,"female")!= 0 && strcmp(student,"Other")!= 0 && strcmp(student,"other")!= 0 )
    {
        printf("Invalid Gender Type\n");
        invalidGender = 1;
    }
    else
    {
        invalidGender = 0;
    }
    return invalidGender;
}


int checkEmailAddress(char emailAddress[])
{
    int validateEmail = 0;
    int validSymbol = 0;
    int validLettersNumbers = 0;
    for(int j =0; j<= strlen(emailAddress)  ;j++)
    {
        if(emailAddress[j] == '@')
        {
            validSymbol+=1;
        }
        if((emailAddress[j]>='A' && emailAddress[j]<='Z') || (emailAddress[j]>= 'a' && emailAddress[j]<= 'z') || emailAddress[j]== '@' || emailAddress[j]== '.' || (emailAddress[j]>= '0' && emailAddress[j]<='9') )
        {
            validLettersNumbers+=1;
        }
    }
    if(validLettersNumbers == strlen(emailAddress) && validSymbol == 1)
    {
        validateEmail = 1;
    }
    else
    {
        printf("Invalid Email Address\n");
    }
    return validateEmail;
}

int checkName(char name[])
{
    int validName = 0;
    int count =0;
    for(int j = 0; j<strlen(name);j++)
    {
        if((name[j]>='A' && name[j]<='Z') || (name[j]>='a' && name[j]<='z'))
        {
            count+=1;
        }
    }
    if(count == strlen(name))
    {
        validName = 1;
    }
    else
    {
        printf("Invalid Name\n");
        validName = 0;
    }
    return validName;
}

int checkMark(int *marks)
{
    int validMark = 0;
    if (*marks >= 0 && *marks <= 100)
    {
        validMark = 1;
    }
    else
    {
        validMark = 0;
        printf("\nInvalid Result\n");
    }
    return validMark;
}

char getGrade(int *marks)
{
    char grade;
    if(*marks <35)
    {
        grade = 'F';
    }
    if(*marks >= 35)
    {
        grade = 'S';
    }
    if(*marks >= 50)
    {
        grade = 'C';
    }
    if(*marks >= 65)
    {
        grade = 'B';
    }
    if(*marks >= 75)
    {
        grade = 'A';
    }
    return grade;
}



void searchAndUpdateStudentDetail(struct studentRecordDetail student[],int *topIndex,char searchId[])
{

    int tempTopIndex = *topIndex;
    system("cls");
    int i = 0;
    int j = 0;
    int searchResult = 0;
    int choice = 0;
    int validateEmail = 0;
    int phoneNumVallidate = 0;
    int guardianPhoneNumVallidate = 0;
    char temp;


    printf("\n\n            **STUDENT INFORMATION SYSTEM**\n\n");
    printf("                      **Update**\n\n");
    for( i=0; i<tempTopIndex; i++)
    {
        if(strcmp(student[i].studentId,searchId) == 0)
        {
            searchResult = 1;
            printf("What do you want to update\n");
            printf("1. Address\n");
            printf("2. Contact Number\n");
            printf("3. Email\n");
            printf("4. Contact Person Number\n");
            printf("\nYour Selection        : ");
            scanf("%d", &choice);
            if(choice == 1)
            {
                printf("Enter student address                      : ");
                scanf("%c",&temp);
                scanf("%[^\n]",& student[i].address);
            }
            else if(choice == 2)
            {
                while(phoneNumVallidate != 10)
                {
                    phoneNumVallidate = 0;
                    printf("Enter student mobile number                : ");
                    scanf("%s",& student[i].mobileNumber);
                    phoneNumVallidate = checkPhoneNumber(student[i].mobileNumber);
                }
            }
            else if(choice == 3)
            {
                scanf("%c",&temp);
                while(validateEmail != 1)
                {
                    printf("Enter student email address                : ");
                    scanf(" %[^\n]",& student[i].emailAddress);
                    validateEmail = checkEmailAddress(student[i].emailAddress);
                }
            }
            else if(choice == 4)
            {
                while(guardianPhoneNumVallidate != 10)
                {
                    guardianPhoneNumVallidate = 0;
                    printf("Enter student contact person contact number: ");
                    scanf(" %s",& student[i].contactPersonNumber);
                    guardianPhoneNumVallidate = checkPhoneNumber(student[i].contactPersonNumber);
                }
            }
            else
            {
                printf("Invalid Selection\n");
            }
        }
    }

    FILE *fptr = fopen("studentDetails.txt", "w");
    for(j=0; j < tempTopIndex;j++)
    {
        fprintf(fptr, "%s %s %s %s %d %d %d %s %s %s %s %s %s\n",student[j].studentId, student[j].studentFirstName,student[j].studentLastName,student[j].address,student[j].dateOfBirthY,student[j].dateOfBirthM,student[j].dateOfBirthD,student[j].gender,student[j].mobileNumber,student[j].emailAddress,student[j].contactPersonName,student[j].contactPersonNumber,student[j].studentPassword);
    }
    fclose(fptr);

    if(searchResult!= 1)
        {
            printf("\nNo Search Result Found\n");
        }


}

void searchAndDeleteStudentDetail(struct studentRecordDetail student[],int *topIndex,char searchId[])
{

    int tempTopIndex = *topIndex;
    int i = 0;
    int j = 0;
    int x = 0;
    int searchResult = 0;
    system("cls");
    printf("\n\n            **STUDENT INFORMATION SYSTEM**\n\n");
    printf("                      **Delete**\n\n");
    for( x=0; x<tempTopIndex && searchResult != 1; x++)
    {
        if(strcmp(student[x].studentId,searchId) == 0)
        {
            for (i=x; i<tempTopIndex; i++)
            {
                searchResult = 1;
                strcpy(student[i].studentId,student[i+1].studentId);
                strcpy(student[i].studentPassword,student[i+1].studentPassword);
                strcpy(student[i].studentFirstName,student[i+1].studentFirstName);
                strcpy(student[i].studentLastName,student[i+1].studentLastName);
                strcpy(student[i].address,student[i+1].address);
                student[i].dateOfBirthY = student[i+1].dateOfBirthY;
                student[i].dateOfBirthM = student[i+1].dateOfBirthM;
                student[i].dateOfBirthD = student[i+1].dateOfBirthD;
                strcpy(student[i].gender,student[i+1].gender);
                strcpy(student[i].mobileNumber,student[i+1].mobileNumber);
                strcpy(student[i].emailAddress,student[i+1].emailAddress);
                strcpy(student[i].contactPersonName,student[i+1].contactPersonName);
                strcpy(student[i].contactPersonNumber,student[i+1].contactPersonNumber);
            }
          printf("\nSuccessfully Deleted\n ");
        }
    }
    tempTopIndex--;
    *topIndex = tempTopIndex;

    FILE *fptr = fopen("studentDetails.txt", "w");
    for(j=0; j < tempTopIndex;j++)
    {
        fprintf(fptr, "%s %s %s %s %d %d %d %s %s %s %s %s %s\n",student[j].studentId, student[j].studentFirstName,student[j].studentLastName,student[j].address,student[j].dateOfBirthY,student[j].dateOfBirthM,student[j].dateOfBirthD,student[j].gender,student[j].mobileNumber,student[j].emailAddress,student[j].contactPersonName,student[j].contactPersonNumber,student[j].studentPassword);
    }

    if(searchResult!= 1)
        {
            printf("\nNo Search Result Found\n");
        }

}

int calGrade(struct examResultSheet exam[],char searchExamId[],int *aCount,int *bCount, int *cCount, int *sCount, int *fCount,int *topExamIndex)
{
    int topExamIndexTemp = *topExamIndex;
    int validExamId = 0;
    for(int i = 0;i<topExamIndexTemp;i++)
    {
    if(strcmp(exam[i].examId,searchExamId)==0)
      {
        validExamId = 1;
        if(exam[i].grade == 'A')
        {
            *aCount+=1;

        }

        if(exam[i].grade == 'B')
        {
            *bCount+=1;

        }
        if(exam[i].grade == 'C')
        {
            *cCount+=1;
        }
        if(exam[i].grade == 'S')
        {
            *sCount+=1;
        }
        if(exam[i].grade == 'F')
        {
            *fCount+=1;
        }
      }
    }
    if(validExamId == 0)
    {
        printf("\nInvalid Exam ID\n");
    }
    return validExamId;
}

void printResultGraph(int *aCount, int *bCount, int *cCount, int *sCount, int *fCount)
{
    int numberArr[5];
    numberArr[0]= *aCount;
    numberArr[1]= *bCount;
    numberArr[2]= *cCount;
    numberArr[3]= *sCount;
    numberArr[4]= *fCount;
    //find max value
    int maxnum = numberArr[0];
    for(int i = 1; i<5;i++)
    {
        if(maxnum < numberArr[i])
        {
            maxnum = numberArr[i];
        }
    }
    //print A column
    printf(" \n Grade\n");
    printf("    ^   \n");
    printf("    \xB3\n");
    printf(" A");
    printf("  \xB3");
    for (int i = 0;i< *aCount;i++)
    {
        printf("\xDB");
    }
    if(*aCount>0)
    printf(" %d",*aCount);
    printf("\n");
    //print B column
    printf("    \xB3\n");
    printf(" B");
    printf("  \xB3");
    for (int i = 0;i< *bCount;i++)
    {
        printf("\xDB");
    }
    if(*bCount>0)
    printf(" %d",*bCount);
    printf("\n");
     //print C column
    printf("    \xB3\n");
    printf(" C");
    printf("  \xB3");
    for (int i = 0;i< *cCount;i++)
    {
        printf("\xDB");
    }
    if(*cCount>0)
    printf(" %d",*cCount);
     printf(" \n");
     //print S column
    printf("    \xB3\n");
    printf(" S");
    printf("  \xB3");
    for (int i = 0;i< *sCount;i++)
    {
        printf("\xDB");
    }
    if(*sCount>0)
    printf(" %d",*sCount);
     printf("\n");
     //print F column
    printf("    \xB3\n");
    printf(" F");
    printf("  \xB3");
    for (int i = 0;i< *fCount;i++)
    {
        printf("\xDB");
    }
    if(*fCount>0)
    printf(" %d",*fCount);
    printf(" \n");
    printf("    \xB3\n");
    printf("    \xC0");
     for (int i = 0;i< maxnum+5;i++)
    {
        printf("\xC4");
    }
    printf("\xAF  Students\n\n");


}


int checkForId(struct studentRecordDetail student[],int *topIndex,char searchId[])
{
    int tempTopIndex = *topIndex;
    int validID = 0;
    int i = 0;
    for( i=0; i<tempTopIndex; i++)
    {
        if(strcmp(student[i].studentId,searchId) == 0)
        {
            validID = 1;

        }
    }
    if(validID != 1)
    {
        printf("Invalid Student ID\n");
    }
    return validID;
}

void readAdminDetails(struct adminRecordDetail admin[],int *topAdminIndex)
{
    system("cls");
    int adminIdValidate = 1;
    int topAdminIndexT = *topAdminIndex;

    printf("\n                       **STUDENT INFORMATION SYSTEM**\n\n");
    printf("                             **Add New Admin**\n\n");
    while(adminIdValidate == 1)
    {
        printf("Enter Admin Id : ");
        scanf("%s",& admin[topAdminIndexT].adminId);
        adminIdValidate = checkAdminId(admin,&topAdminIndexT);
    }
    printf("Enter Password : ");
    scanf("%s", &admin[topAdminIndexT].adminPassword);

    FILE *fptr = fopen("adminDetails.txt","a");
    fprintf(fptr, "%s %s\n",admin[topAdminIndexT].adminId, admin[topAdminIndexT].adminPassword);
    fclose(fptr);
    topAdminIndexT++;
    *topAdminIndex = topAdminIndexT;

}

int checkAdminId(struct adminRecordDetail admin[],int *topAdminIndex)
{
    int adminIdTypeValidate = 0;
    int dublicateAdminId = 0;
    int topAdminIndexT = *topAdminIndex;
    int adminIdValidate = 0;



            //studentIdTypeValidate = 0;
            //dublicateStudentId = 0;
            if(admin[topAdminIndexT].adminId[0] == 'A' && admin[topAdminIndexT].adminId[1] == 'D' )
            {
                adminIdTypeValidate = 1;
                for(int i=0; i<topAdminIndexT; i++)
                {
                    if(strcmp(admin[i].adminId,admin[topAdminIndexT].adminId) == 0)
                    {
                        dublicateAdminId = 1;
                    }
                }
            }

        if(adminIdTypeValidate != 1 || dublicateAdminId == 1)
            {
                printf("\nInvalid Admin ID type or duplicate ID. (ADxxxx)\n\n");
                adminIdValidate = 1;
            }
        else
            {
                adminIdValidate = 0;
            }
    return adminIdValidate;
}


void goBack(int *backSelection)
{
    printf("\n1. Back\n");
    printf("2. End\n");
    printf("Your Selection :");
    scanf("%d", backSelection);
}




char determineUserType(char userId)
{
    char userType = '0';
    switch (userId)
    {
    case 'A':
    case 'a':
        {
            userType = 'A';
            break;
        }
    case 'S':
    case 's':
        {
            userType = 'S';
            break;
        }
    default :
        userType = 'I';
     }

    return userType;
}

char verifyUserIdAndPassword(struct adminRecordDetail admin[],struct studentRecordDetail student[], char userId[], char userPassword[], char *userType, int *topAdminIndex, int *topStudentIndex)
{
    char validation = '0';
    int i = 0;
    if(*userType == 'A')
    {

        for( i = 0; i<*topAdminIndex && validation != 'V'; i++)
        {
            if ((strcmp(admin[i].adminId,userId)) == 0 && (strcmp(admin[i].adminPassword,userPassword)) == 0)
            {
                validation = 'V';
            }
            else
            {
                validation = 'I';
            }
        }
    }
    if(*userType == 'S')
    {
        for (int j=0; j < *topStudentIndex && validation != 'V'; j++)
        {

        if ((strcmp(student[j].studentId,userId))== 0 && (strcmp(student [j].studentPassword,userPassword)) == 0)
            {
                validation = 'V';
            }
        else
            {
                validation = 'I';
            }
        }

    }

    return validation;
}
