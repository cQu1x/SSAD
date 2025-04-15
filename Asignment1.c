#include <ctype.h>
#include <stdio.h>
#include <string.h>
#include <stdlib.h>
// Defining constants
#define MAX_NAME_LEN 20
#define MAX_SOFTWARE_LEN 20
#define MIN_FACULTY_LEN 4
#define MAX_FACULTY_LEN 30
#define MIN_SOFTWARE_LEN 2
#define MAX_SOFTWARE_LEN 20
#define MAX_STUDENT_ID 1000
#define MAX_EXAM_ID 500
#define MAX_GRADE 101
#define MAX_DURATION 181
#define MINUS_ONE -1


//Declaring structures, enums and a union according to the condition of the problem
struct Student {
    int student_id;
    char name[MAX_NAME_LEN];
    char faculty[MAX_FACULTY_LEN];
};
enum ExamType {
    WRITTEN,
    DIGITAL
};
union ExamInfo {
    int duration;
    char software[MAX_SOFTWARE_LEN];
};
struct Exam {
    int exam_id;
    enum ExamType exam_type;
    union ExamInfo exam_info;
};
struct ExamGrade {
    int exam_id;
    int student_id;
    int grade;
};

// Functions to check the validity of variables
int wordchecker(char a[]) {

    for (int i = 0; i < strlen(a); i++) {
        if (!isalpha(a[i])) {
            return 0;
        }
    }
    return 1;
}

int numchecker(char a[]) { //Checking wether we variable is a string or not
    for (int i=0;i<strlen(a);i++) {
        if (!isdigit(a[i])) {
            return 0;
        }
    }
    return 1;
}
//Functions to check the validity of information according to the problem
int valid_student_id(char a[]) {
    if ((numchecker(a)) && (0<atoi(a)) && (atoi(a)<MAX_STUDENT_ID)) {
        return 1;
    }
    return 0;
}

int valid_exam_id(char a[]) {
    if ((numchecker(a)) && (atoi(a)>0) && (atoi(a)<MAX_EXAM_ID)) {
        return 1;
    }
    return 0;
}
int valid_name(char a[]) {
    if ((wordchecker(a)) && (strlen(a)>1) && (strlen(a)<MAX_NAME_LEN)) {
        return 1;
    }
    return 0;
}
int valid_faculty(char a[]) {
    if ((wordchecker(a)) && (strlen(a)>MIN_FACULTY_LEN) && (strlen(a)<MAX_FACULTY_LEN)) {
        return 1;
    }
    return 0;
}
int valid_grade(char a[]) {
    if ((numchecker(a)) && (0<=atoi(a)) && (atoi(a)<=100)) {
        return 1;
    }
    return 0;
}
int valid_duration(int a) {
    if ((40<=a) && (a<=180)) {
        return 1;
    }
    return 0;
}

// Initializing arrays of structures
struct Student students[MAX_STUDENT_ID];
struct Exam exam[MAX_EXAM_ID];
struct ExamGrade grades[MAX_EXAM_ID][MAX_STUDENT_ID];

int main() {
    //Opening files
    FILE* input = fopen("input.txt","r");
    FILE* output = fopen("output.txt","w");
    if (!input) {
        printf("File not found\n");
    }


    char line[100];
    //Initializing
    int student_counter = 0;
    int disorderedids[1000];
    for (int i = 0; i < 1000; i++) {
        disorderedids[i] = -1;
    }

    while (fgets(line, 100, input)) {
        //declaring variables for future inputs
        line[strcspn(line, "\n")] = 0;
        char student_id[100];
        char exam_id[100];
        char grade[100];
        char name[MAX_NAME_LEN];
        char faculty[100];
        char exam_type[100];
        char exam_specifier[100];



// Scanning line from file and comparing to the string to find the command
        //Command ADD_STUDENT
        if (sscanf(line, "ADD_STUDENT %s %s %s", student_id, name, faculty)) {
            int student_id_num = atoi(student_id);
            if (!valid_student_id(student_id)) {
            fprintf(output,"Invalid student id\n");
            }
            else if (students[student_id_num].student_id && students[student_id_num].student_id!=MINUS_ONE) {
                fprintf(output,"Student: %s already exists\n",student_id);
            }
            else if (!valid_name(name)) {
                fprintf(output,"Invalid name\n");
            }
            else if (!valid_faculty(faculty)) {
                fprintf(output,"Invalid faculty\n");
            }
            else {
                students[student_id_num].student_id = student_id_num;
                strcpy(students[student_id_num].name,name);
                strcpy(students[student_id_num].faculty,faculty);
                //Saving the ID into another array to print the IDs in the order they were inputted
                disorderedids[student_counter] = students[student_id_num].student_id;
                student_counter+=1;
                fprintf(output,"Student: %s added\n",student_id);
            }
        }


        //Command ADD_EXAM
        else if (sscanf(line, "ADD_EXAM %s %s %s", exam_id, exam_type, exam_specifier)) {
            int exam_id_num = atoi(exam_id);
            if (!valid_exam_id(exam_id)) {
                fprintf(output, "Invalid exam id\n");
            }
            else if (exam[exam_id_num].exam_id && exam[exam_id_num].exam_id!=MINUS_ONE) {
                fprintf(output,"Exam: %d already exists\n",exam_id_num);
            }

            else if ((strcmp(exam_type,"WRITTEN")!=0)&&strcmp(exam_type,"DIGITAL")!=0) {
                fprintf(output,"Invalid exam type\n");
            }
            else if (strcmp(exam_type,"WRITTEN")==0)
                if (numchecker(exam_specifier) && 40<=atoi(exam_specifier) && atoi(exam_specifier)<=180) {
                    exam[exam_id_num].exam_id=exam_id_num;
                    exam[exam_id_num].exam_type=WRITTEN;
                    exam[exam_id_num].exam_info.duration=atoi(exam_specifier);
                    fprintf(output,"Exam: %d added\n",exam_id_num);
                }
                else {
                    fprintf(output,"Invalid duration\n");
                }
            else if (strcmp(exam_type,"DIGITAL")==0) {
                if (wordchecker(exam_specifier) && strlen(exam_specifier)>2 && strlen(exam_specifier)<20) {
                    exam[exam_id_num].exam_id = exam_id_num;
                    exam[exam_id_num].exam_type = DIGITAL;
                    strcpy(exam[exam_id_num].exam_info.software , exam_specifier);
                    fprintf(output,"Exam: %d added\n",exam_id_num);
                }
                else {
                    fprintf(output,"Invalid software\n");
                }
                }
        }


        //Command ADD_GRADE
        else if (sscanf(line, "ADD_GRADE %s %s %s", exam_id, student_id, grade)){
            int exam_id_num = atoi(exam_id);
            int student_id_num = atoi(student_id);
            if (!valid_exam_id(exam_id)) {
            fprintf(output,"Invalid exam id\n");
            }
            else if (!valid_student_id(student_id)) {
                fprintf(output,"Invalid student id\n");
            }
            else if (!valid_grade(grade)) {
                fprintf(output,"Invalid grade\n");
            }
            else if (!exam[exam_id_num].exam_id || exam[exam_id_num].exam_id==MINUS_ONE) {
                fprintf(output,"Exam not found\n");
            }
            else if (!students[student_id_num].student_id || students[student_id_num].student_id== MINUS_ONE) {
                fprintf(output,"Student not found\n");
            }
            else {
                grades[exam_id_num][student_id_num].exam_id = exam_id_num;
                grades[exam_id_num][student_id_num].student_id = student_id_num;
                grades[exam_id_num][student_id_num].grade = atoi(grade);
                fprintf(output, "Grade %s added for the student: %s\n",grade,student_id);
            }
        }

        //Command SEARCH_STUDENT
        else if (sscanf(line, "SEARCH_STUDENT %s", student_id)){
            int student_id_num = atoi(student_id);
            if (!valid_student_id(student_id)) {
            fprintf(output,"Invalid student id\n");
            }
            else if (!students[student_id_num].student_id || students[student_id_num].student_id==MINUS_ONE) {
                fprintf(output,"Student not found\n");
            }
            else {
                fprintf(output,"ID: %d, Name: %s, Faculty: %s\n",students[student_id_num].student_id,students[student_id_num].name,students[student_id_num].faculty);
            }
        }


        //Command ADD_SEARCH GRADE
        else if (sscanf(line, "SEARCH_GRADE %s %s", exam_id, student_id)){
            int exam_id_num = atoi(exam_id);
            int student_id_num = atoi(student_id);
            if (!valid_exam_id(exam_id)) {
            fprintf(output,"Invalid exam id\n");
            }
            else if (!valid_student_id(student_id)) {
                fprintf(output,"Invalid student id\n");
            }
            else if (!(exam[exam_id_num].exam_id) || (exam[exam_id_num].exam_id)==MINUS_ONE) {
                fprintf(output,"Exam not found\n");
            }
            else if ((!grades[exam_id_num][student_id_num].student_id) || (grades[exam_id_num][student_id_num].student_id)==MINUS_ONE) {
                fprintf(output,"Student not found\n");
            }
            else {
                if (exam[exam_id_num].exam_type==WRITTEN) {
                    char temp[] = "WRITTEN";
                    fprintf(output,"Exam: %d, Student: %d, Name: %s, Grade: %d, Type: %s, Info: %d\n",grades[exam_id_num][student_id_num].exam_id,grades[exam_id_num][student_id_num].student_id,students[student_id_num].name,grades[exam_id_num][student_id_num].grade,temp,exam[exam_id_num].exam_info.duration);
                }
                else {
                    char temp[] = "DIGITAL";
                    fprintf(output,"Exam: %d, Student: %d, Name: %s, Grade: %d, Type: %s, Info: %s\n",grades[exam_id_num][student_id_num].exam_id,grades[exam_id_num][student_id_num].student_id,students[student_id_num].name,grades[exam_id_num][student_id_num].grade,temp,exam[exam_id_num].exam_info.software);
                }
            }
        }


        //Command UPDATE_EXAM
        else if (sscanf(line, "UPDATE_EXAM %s %s %s", exam_id, exam_type, exam_specifier)) {
            int exam_id_num = atoi(exam_id);
            if ((strcmp(exam_type,"WRITTEN")!=0) && (strcmp(exam_type,"DIGITAL")!=0)) {
                fprintf(output,"Invalid exam type\n");
            }
            else if (strcmp(exam_type,"WRITTEN")==0) {
                if (numchecker(exam_specifier) && valid_duration(atoi(exam_specifier))) {
                    exam[exam_id_num].exam_id = exam_id_num;
                    exam[exam_id_num].exam_type = WRITTEN;
                    exam[exam_id_num].exam_info.duration = atoi(exam_specifier);
                    fprintf(output,"Exam: %d updated\n",exam_id_num);
                }
                else {
                    fprintf(output,"Invalid duration\n");
                }
            }
            else if (strcmp(exam_type,"DIGITAL")==0) {
                if (wordchecker(exam_specifier) && strlen(exam_specifier)>2 && strlen(exam_specifier)<20) {
                    exam[exam_id_num].exam_id = exam_id_num;
                    exam[exam_id_num].exam_type = DIGITAL;
                    strcpy(exam[exam_id_num].exam_info.software, exam_specifier);
                    fprintf(output,"Exam: %d updated\n",exam_id_num);
                }
                else{
                    fprintf(output,"Invalid software\n");
                }
            }
        }


        //Command UPDATE_GRADE
        else if (sscanf(line, "UPDATE_GRADE %s %s %s", exam_id, student_id, grade)){
            int exam_id_num = atoi(exam_id);
            int student_id_num = atoi(student_id);
            if (!valid_grade(grade)) {
                fprintf(output,"Invalid grade\n");
            }
            else {
                grades[exam_id_num][student_id_num].exam_id = exam_id_num;
                grades[exam_id_num][student_id_num].student_id = student_id_num;
                grades[exam_id_num][student_id_num].grade = atoi(grade);
                fprintf(output,"Grade %d updated for the student: %d\n",grades[exam_id_num][student_id_num].grade, grades[exam_id_num][student_id_num].student_id);
            }
        }


        //Command LIST_ALL_STUDENTS
        else if (strcmp(line,"LIST_ALL_STUDENTS")==0){
            for (int i=0; i<student_counter;i++) {
                if (disorderedids[i]!=MINUS_ONE && students[disorderedids[i]].student_id != MINUS_ONE) {
                    fprintf(output,"ID: %d, Name: %s, Faculty: %s\n",students[disorderedids[i]].student_id,students[disorderedids[i]].name,students[disorderedids[i]].faculty);
                }
            }
        }


        //Command DELETE_STUDENT
        else if (sscanf(line, "DELETE_STUDENT %s", student_id)){
            int student_id_num = atoi(student_id);
            students[student_id_num].student_id=MINUS_ONE;
            memset(students[student_id_num].name, '\0', MAX_NAME_LEN);
            memset(students[student_id_num].faculty, '\0', MAX_FACULTY_LEN);
            for (int i=0;i<1000;i++) {
                if (disorderedids[i]==student_id_num) {
                    disorderedids[i]=MINUS_ONE;
                }
            }
            for (int i=0;i<MAX_EXAM_ID;i++) {
                if ((grades[i][student_id_num].exam_id) && (grades[i][student_id_num].exam_id!=MINUS_ONE)) {
                    grades[i][student_id_num].exam_id = MINUS_ONE;
                    grades[i][student_id_num].grade=MINUS_ONE;
                    grades[i][student_id_num].student_id = MINUS_ONE;
                }
            }
            fprintf(output,"Student: %d deleted\n",student_id_num);

        }
        //Command END
        if (strcmp(line,"END")==0){
            break;
        }
    }
    fclose(input);
    fclose(output);
    return 0;
}
