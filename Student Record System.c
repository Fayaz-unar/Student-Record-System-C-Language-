#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define MAX_STUDENTS 100

struct Student {
    int rollNumber;
    char name[100];
    float marks;
};

void addStudent();
void viewStudent();
void updateStudent();
void deleteStudent();
void displayAllStudents();
void saveStudents();
void loadStudents();
int findStudentIndex(int rollNumber);

struct Student students[MAX_STUDENTS];
int studentCount = 0;

int main() {
    int choice;
    loadStudents();  
    
    while (1) {
        printf("\n--- Student Record System ---\n");
        printf("1. Add Student Record\n");
        printf("2. View Student Record\n");
        printf("3. Update Student Record\n");
        printf("4. Delete Student Record\n");
        printf("5. Display All Students\n");
        printf("6. Exit\n");
        printf("Enter your choice: ");
        scanf("%d", &choice);

        switch (choice) {
            case 1:
                addStudent();
                break;
            case 2:
                viewStudent();
                break;
            case 3:
                updateStudent();
                break;
            case 4:
                deleteStudent();
                break;
            case 5:
                displayAllStudents();
                break;
            case 6:
                saveStudents(); 
                printf("Exiting the system. Goodbye!\n");
                exit(0);
            default:
                printf("Invalid choice! Please try again.\n");
        }
    }

    return 0;
}


void addStudent() {
    struct Student newStudent;

    printf("Enter student name: ");
    getchar();  
    fgets(newStudent.name, 100, stdin);
    newStudent.name[strcspn(newStudent.name, "\n")] = '\0';  

    printf("Enter student roll number: ");
    scanf("%d", &newStudent.rollNumber);

    printf("Enter student marks: ");
    scanf("%f", &newStudent.marks);

    students[studentCount] = newStudent;
    studentCount++;
    printf("Student record added successfully!\n");
}

void viewStudent() {
    int rollNumber;

    printf("Enter student roll number: ");
    scanf("%d", &rollNumber);

    int index = findStudentIndex(rollNumber);
    if (index == -1) {
        printf("Student record not found!\n");
        return;
    }

    printf("\nStudent Record\n");
    printf("Name: %s\n", students[index].name);
    printf("Roll Number: %d\n", students[index].rollNumber);
    printf("Marks: %.2f\n", students[index].marks);
}

void updateStudent() {
    int rollNumber;

    printf("Enter student roll number: ");
    scanf("%d", &rollNumber);

    int index = findStudentIndex(rollNumber);
    if (index == -1) {
        printf("Student record not found!\n");
        return;
    }

    printf("Enter new name for the student: ");
    getchar(); 
    fgets(students[index].name, 100, stdin);
    students[index].name[strcspn(students[index].name, "\n")] = '\0';  

    printf("Enter new marks for the student: ");
    scanf("%f", &students[index].marks);

    printf("Student record updated successfully!\n");
}

void deleteStudent() {
    int rollNumber;

    printf("Enter student roll number: ");
    scanf("%d", &rollNumber);

    int index = findStudentIndex(rollNumber);
    if (index == -1) {
        printf("Student record not found!\n");
        return;
    }

    for (int i = index; i < studentCount - 1; i++) {
        students[i] = students[i + 1];
    }

    studentCount--;
    printf("Student record deleted successfully!\n");
}

void displayAllStudents() {
    if (studentCount == 0) {
        printf("No student records found!\n");
        return;
    }

    printf("\n--- All Student Records ---\n");
    for (int i = 0; i < studentCount; i++) {
        printf("Name: %s\n", students[i].name);
        printf("Roll Number: %d\n", students[i].rollNumber);
        printf("Marks: %.2f\n", students[i].marks);
        printf("---------------------------\n");
    }
}

void saveStudents() {
    FILE *file = fopen("students.dat", "wb");
    if (file == NULL) {
        printf("Error saving student records to file!\n");
        return;
    }
    fwrite(&studentCount, sizeof(int), 1, file);
    fwrite(students, sizeof(struct Student), studentCount, file);
    fclose(file);
}

void loadStudents() {
    FILE *file = fopen("students.dat", "rb");
    if (file == NULL) {
        return;  
    }

    fread(&studentCount, sizeof(int), 1, file);
    fread(students, sizeof(struct Student), studentCount, file);
    fclose(file);
}

int findStudentIndex(int rollNumber) {
    for (int i = 0; i < studentCount; i++) {
        if (students[i].rollNumber == rollNumber) {
            return i;  
        }
    }
    return -1;  
}
