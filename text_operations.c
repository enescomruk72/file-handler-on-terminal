#define _CRT_SECURE_NO_WARNINGS

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

// max no of chars per line
#define MAX_SIZE 256

// add text at the end of the given file
void Text_at_End(char* filename, char* text) {
	// opening the file in append mode
	FILE* file = fopen(filename, "a");
	// check if file opened or not
	if (!file) {
		printf("Unable to open file %s...\n", filename);
		return;
	}
	// writing text to the file at the end
	fputs(text, file);
	fclose(file);
	printf("FIle updated successfully...\n");
}

// delete all the contents of the file
int Delete_File_Content(char* filename) {
	// opening the fil in write mode, it will clear all the contents of the file and open the file in writing mode
	FILE* file = fopen(filename, "w");
	// check if file opened or not
	if (!file) {
		printf("File does't exist...\n");
		return 0;
	}
	// cloding the file, cntents of the file cleared
	fclose(file);
	return 1;
}

// Ad text at specific location
void Add_At_Location(char* filename, char* str, int loc) {
	// opening the file
	FILE* file = fopen(filename,"r");
	FILE* tmp = fopen("temp.txt", "w");
	// check if file opened or not
	if (!file) {
		printf("Unable to open file %s...\n", filename);
		return;
	}

	char buf[MAX_SIZE] = { 0 };
	char c;
	// copying the contents of the file into a temporary file
	for (int i = 0; i < loc && (c = fgetc(file)); i++)
		fputc(c, tmp);
	// puting the text at desired place
	fputs(str, tmp);
	// copying the remaining data
	while (fgets(buf, MAX_SIZE, file))
 		fputs(buf, tmp);
	// closing both files
	fclose(file);
	fclose(tmp);
	// deleting the contents of the file 
	Delete_File_Content(filename);
	// opening both files again
	file = fopen(filename, "w");
	tmp = fopen("temp.txt", "r");
	// copying the new content with the text at specified locatiomn from temp file
	while (fgets(buf, MAX_SIZE, tmp))
		fputs(buf, file);
	// closing both files
	fclose(file);
	fclose(tmp);
	// deleting the temporary file
	remove("temp.txt");
	printf("File updated successfully...\n");
}

// printing the contents of the file page by page. No of line per page will be passed as parameter
void Print_Page_By_Page(char* filename, int lpp) {
	FILE* file = fopen(filename, "r");
	// check if file opened or not
	if (!file) {
		printf("Unable to open file %s...\n", filename);
		return;
	}
	char str[MAX_SIZE] = { 0 };
	int count = 0;
	// reading file line by line
	while (fgets(str,MAX_SIZE,file)) {
		printf("%s", str);
		count++;
		// if page finished, give a pause
		if (count % lpp == 0) {
			printf("Press any key to continue...\n");
			getc(stdin);
		}
	}
	fclose(file);
}

// menu to gie options to the user for interaction
void Menu() {
	printf("Options:\n");
	printf("1. Add text at the end of the file.\n");
	printf("2. Delete all the contents of the file.\n");
	printf("3. Add text at specific location in the file.\n");
	printf("4. View file page by page.\n");
	printf("5. Exit\n");
}

int main() {
	int choice;
	char buf[MAX_SIZE] = { 0 };
	char filename[50] = { 0 };
	int val;
	do {
		// display menu
		Menu();
		// get user choice for menu
		printf("Choose option: ");
		scanf("%d", &choice);
		getc(stdin);
		// add text at the end, if choice is 1
		if (choice == 1) {
			// input file name
			printf("Enter file name: ");
			scanf("%s", filename);
			getc(stdin);
			// enter text to add
			printf("Enter text to add: ");
			fgets(buf, MAX_SIZE, stdin);
			Text_at_End(filename, buf);
		}
		// if choice is 2, delete all contents of the file
		else if (choice == 2) {
			printf("Enter file name: ");
			scanf("%s", filename);
			getc(stdin);
			if (Delete_File_Content(filename)) {
				printf("File contents deleted successfully...\n");
			}
		}
		// if chpice is 3, input filename, text, and location from the user to add text at the specified location
		else if (choice == 3) {
			printf("Enter file name: ");
			scanf("%s", filename);
			getc(stdin);
			printf("Enter text to add: ");
			fgets(buf, MAX_SIZE, stdin);
			do {
				printf("Enter location to add text (no of characters): ");
				scanf("%d", &val);
				getc(stdin);
				if (val < 0)
					printf("No of characters sould be a positive value...\n");
			} while (val < 0);
			Add_At_Location(filename, buf, val);
		}
		// if choice is 4, then diaplay file contents page by page. input filename and line per page from the user
		else if (choice == 4) {
			printf("Enter file name: ");
			scanf("%s", filename);
			getc(stdin);
			do {
				printf("Enter lines to display per page: ");
				scanf("%d", &val);
				getc(stdin);
				if (val < 1)
					printf("No of lines per page should be greater than 0...\n");
			} while (val < 1);
			Print_Page_By_Page(filename, val);
		}
		// if choice is 5, exit the program
		else if (choice == 5) {
			printf("Exiting...\n");
		}
		// if user entered an invalid value
		else {
			printf("Please enter a valid opton...\n");
		}
	} while (choice != 5);
	return 0;
}