#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define MAX_FILES 100
#define MAX_FILENAME_LENGTH 100

// Structure to represent a file in the directory
typedef struct {
    char name[MAX_FILENAME_LENGTH];
} File;

// Structure to represent the directory
typedef struct {
    File files[MAX_FILES];
    int count;
} Directory;

// Function to initialize the directory
void init_directory(Directory *dir) {
    dir->count = 0;
}

// Function to add a file to the directory
void add_file(Directory *dir, const char *filename) {
    if (dir->count < MAX_FILES) {
        strncpy(dir->files[dir->count].name, filename, MAX_FILENAME_LENGTH);
        dir->count++;
        printf("File '%s' added.\n", filename);
    } else {
        printf("Directory is full. Cannot add file '%s'.\n", filename);
    }
}

// Function to list all files in the directory
void list_files(const Directory *dir) {
    if (dir->count == 0) {
        printf("No files in the directory.\n");
    } else {
        printf("Files in the directory:\n");
        for (int i = 0; i < dir->count; i++) {
            printf("%s\n", dir->files[i].name);
        }
    }
}

// Function to delete a file from the directory
void delete_file(Directory *dir, const char *filename) {
    int index = -1;
    for (int i = 0; i < dir->count; i++) {
        if (strcmp(dir->files[i].name, filename) == 0) {
            index = i;
            break;
        }
    }

    if (index == -1) {
        printf("File '%s' not found.\n", filename);
    } else {
        // Shift files to remove the deleted file
        for (int i = index; i < dir->count - 1; i++) {
            dir->files[i] = dir->files[i + 1];
        }
        dir->count--;
        printf("File '%s' deleted.\n", filename);
    }
}

int main() {
    Directory dir;
    char filename[MAX_FILENAME_LENGTH];
    int choice;

    init_directory(&dir);

    while (1) {
        printf("\nDirectory Management Menu:\n");
        printf("1. Add File\n");
        printf("2. List Files\n");
        printf("3. Delete File\n");
        printf("4. Exit\n");
        printf("Enter your choice: ");
        scanf("%d", &choice);
        getchar(); // Consume newline character left by scanf

        switch (choice) {
            case 1:
                printf("Enter filename to add: ");
                fgets(filename, MAX_FILENAME_LENGTH, stdin);
                filename[strcspn(filename, "\n")] = '\0'; // Remove newline character
                add_file(&dir, filename);
                break;
            case 2:
                list_files(&dir);
                break;
            case 3:
                printf("Enter filename to delete: ");
                fgets(filename, MAX_FILENAME_LENGTH, stdin);
                filename[strcspn(filename, "\n")] = '\0'; // Remove newline character
                delete_file(&dir, filename);
                break;
            case 4:
                printf("Exiting.\n");
                exit(0);
            default:
                printf("Invalid choice. Please try again.\n");
        }
    }

    return 0;
}

