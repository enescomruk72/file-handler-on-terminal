#ifndef COMMAND_H
#define COMMAND_H


#include <stdlib.h>
#include <unistd.h>
#include "utility_function.h"


// Creates a new file with the specified filename
void createCommand(char *buffer){
    /*
        It only works if the file you want to create doesn't exist
        @Parameters:
            buffer: command expression
        @Return:
            None    
    */
    char *cmd_buffer[MAX_FILE_WORD_COUNT];
    
    // Split command line into appropriate parts
    int num_of_input=0;
    char *input = strtok(buffer, " ");
    while(input != NULL) {
        input = strtok(NULL, " ");
        cmd_buffer[num_of_input] = input;
        num_of_input++;
    }
    if(num_of_input > MAX_CREATE_FILE + 1) { // If you want to create more files than the file creation limit
        char message[256];
        strcat(message, RED"Error-create: ");
        strcat(message, WHITE"Maximum file creation limit has been exceeded.");
        strcat(message,PURPLE"[maximum file creation limit = 5]\n");
        strcat(message, white"\tTry: create <file1> <file2> <file3> <file4> <file5>\n\n");
        fflush(stdout);
        write(STDOUT_FILENO, message, strlen(message));
    }
    else { // If file creation limit is not exceeded
        for(int i=0; i<num_of_input-1; i++) {
            FILE *fp;
            if((fp = fopen(cmd_buffer[i], "r")) != NULL) { // If there is a file with the filename you want to create
                char message[256] = RED"Error-create: "WHITE;
                char cwd[PATH_MAX];
                getcwd(cwd,sizeof(cwd));
                strcat(message, WHITE"\"");
                strcat(message, cwd);
                strcat(message, "\\"PURPLE);
                strcat(message, cmd_buffer[i]);
                strcat(message, WHITE"\"");
                strcat(message, YELLOW" already exist.\n"white);
                fflush(stdout);
                write(STDOUT_FILENO, message, strlen(message));
                fclose(fp);
            }
            else { // If there is a file with the filename you want to create
                if((fp = fopen(cmd_buffer[i], "w")) !=NULL){
                    char message[128] = GREEN"Succes-create: "WHITE;
                    char cwd[PATH_MAX];
                    getcwd(cwd, sizeof(cwd));
                    strcat(message, "\"");
                    strcat(message, cwd);
                    strcat(message, "\"");
                    strcat(message, GREEN" file created successfully.\n"white);
                    fflush(stdout);
                    write(STDOUT_FILENO, message, strlen(message));
                    fclose(fp);
                }
            }
        }
    }
}

// Removes the specified file
void removeCommand(char *buffer){
    /*
        It only works if the specified file exist
        @Parameters:
            buffer: command expression
        @Return:
            None    
    */
    char *cmd_buffer[MAX_FILE_WORD_COUNT];
    
    // Split command line into appropriate parts
    int num_of_input=0;
    char *input = strtok(buffer, " ");
    while(input != NULL) {
        input = strtok(NULL, " ");
        cmd_buffer[num_of_input] = input;
        num_of_input++;
    }

    if(num_of_input > MAX_CREATE_FILE + 1) { // If if it exceeded the maximum number of arguments
        char message[256];
        strcat(message, RED"Error-remove: ");
        strcat(message, WHITE"The maximum file removal limit has been exceeded.");
        strcat(message,PURPLE"[maximum file removal limit = 5]\n");
        strcat(message, white"\tTry: remove <file1> <file2> <file3> <file4> <file5>\n\n");
        fflush(stdout);
        write(STDOUT_FILENO, message, strlen(message));
    }
    else { // If command is valid
        for(int i=0; i<num_of_input-1; i++) {
            FILE *fp;
            if((fp = fopen(cmd_buffer[i], "r")) != NULL) { // If specified file exis
                fclose(fp);
                int rm;
                rm = remove(cmd_buffer[i]);
                if(rm == 0) { // TO DO
                    char message[128] = GREEN"Succes-remove: "WHITE;
                    char cwd[PATH_MAX];
                    getcwd(cwd, sizeof(cwd));
                    strcat(message, "\"");
                    strcat(message, cwd);
                    strcat(message, "\\"PURPLE);
                    strcat(message, cmd_buffer[i]);
                    strcat(message, WHITE"\"");
                    strcat(message, GREEN" file removed successfully.\n"white);
                    fflush(stdout);
                    write(STDOUT_FILENO, message, strlen(message));
                }
            }
            else { // If specified file doesn't exist
                char message[256] = RED"Error-remove: "WHITE;
                char cwd[PATH_MAX];
                getcwd(cwd,sizeof(cwd));
                strcat(message, WHITE"\"");
                strcat(message, cwd);
                strcat(message, "\\"PURPLE);
                strcat(message, cmd_buffer[i]);
                strcat(message, WHITE"\"");
                strcat(message, YELLOW" doesn't exist.\n"white);
                fflush(stdout);
                write(STDOUT_FILENO, message, strlen(message));
            }
            fclose(fp);
        }
    }
}

// Renames the specified file
void renameCommand(char *buffer){
    /*
        It only works if the specified file exist and there is no file with the new name
        @Parameters:
            buffer: command expression
        @Return:
            None    
    */
    char *cmd_buffer[MAX_FILE_WORD_COUNT];
    
    // Split command line into appropriate parts
    int num_of_input=0;
    char *input = strtok(buffer, " ");
    while(input != NULL) {
        input = strtok(NULL, " ");
        cmd_buffer[num_of_input] = input;
        num_of_input++;
    }
    if(num_of_input == 1){ // If the argument number is 0, it does nothing
        printf("");
    }
    else if(num_of_input > 3 || num_of_input == 2) { // If the number of arguments is not greater than 3 or the number of arguments is not 2.
        char message[128];
        strcat(message, RED"Error-rename: ");
        strcat(message, WHITE"invalid arguments\n");
        strcat(message, white"\tTry: \"rename <source> <destionation>\"\n");
        fflush(stdout);
        write(STDOUT_FILENO, message, strlen(message));
    }
    else {  // If command is valid
        FILE *source, *target;
        if((source = fopen(cmd_buffer[0], "r")) != NULL) { // If specified file exist
            if((target = fopen(cmd_buffer[1], "r")) == NULL) { // There is no a file with same name. then rename the specified file     
                target = fopen(cmd_buffer[1], "w");
                
                char ch;
                while ((ch = fgetc(source)) != EOF)
                    fputc(ch, target);
                
                fclose(target);
                fclose(source);
                remove(cmd_buffer[0]);
                
                char message[128] = GREEN"Succes-rename: "WHITE;
                char cwd[PATH_MAX];
                getcwd(cwd, sizeof(cwd));
                strcat(message, "\"");
                strcat(message, cwd);
                strcat(message, "\\"PURPLE);
                strcat(message, cmd_buffer[0]);
                strcat(message, WHITE"\"");
                strcat(message, GREEN" file renamed successfully.\n"white);
                fflush(stdout);
                write(STDOUT_FILENO, message, strlen(message));
            }
            else { // There is a file with same name 
                char message[256] = RED"Error-create: "WHITE;
                char cwd[PATH_MAX];
                getcwd(cwd,sizeof(cwd));
                strcat(message, WHITE"\"");
                strcat(message, cwd);
                strcat(message, "\\"PURPLE);
                strcat(message, cmd_buffer[1]);
                strcat(message, WHITE"\"");
                strcat(message, YELLOW" already exist.\n"white);
                fflush(stdout);
                write(STDOUT_FILENO, message, strlen(message));
            }
            fclose(target);
        }
        else { // If specified file doesn't exist.
            char message[256] = RED"Error-remove: "WHITE;
            char cwd[PATH_MAX];
            getcwd(cwd,sizeof(cwd));
            strcat(message, WHITE"\"");
            strcat(message, cwd);
            strcat(message, "\\"PURPLE);
            strcat(message, cmd_buffer[0]);
            strcat(message, WHITE"\"");
            strcat(message, YELLOW" doesn't exist.\n"white);
            fflush(stdout);
            write(STDOUT_FILENO, message, strlen(message));
        }
        fclose(source);
    }
}

// Copies the specified file
void copyCommand(char *buffer){
    /*
        It only works if the specified file exist
        @Parameters:
            buffer: command expression
        @Return:
            None    
    */
    char *cmd_buffer[MAX_FILE_WORD_COUNT];
    
    // Split command line into appropriate parts
    int num_of_input=0;
    char *input = strtok(buffer, " ");
    while(input != NULL) {
        input = strtok(NULL, " ");
        cmd_buffer[num_of_input] = input;
        num_of_input++;
    }

    if(num_of_input == 1) { // If the argument number is 0, it does nothing
        printf("");
 
    }
    else if(num_of_input == 2) { // If the argument number is 1, it copies the specified file to it's current directory.
        FILE *source, *target;
        if((source = fopen(cmd_buffer[0], "r")) != NULL) { // If specified file exist
            char source_name[64];
            strcat(source_name, cmd_buffer[0]);
            strcat(source_name, "(kopya)");

            if((fopen(source_name, "r") != NULL)) { // if there is a copy of the specified file
                char message[128] = RED"Error-copy: "WHITE;
                strcat(message, YELLOW" copy of files already exist.\n"white);
                fflush(stdout);
                write(STDOUT_FILENO, message, strlen(message));
            }
            else {  // if there is no a copy of the specified file
                char ch;
                target = fopen(source_name, "w");
                while ((ch = fgetc(source)) != EOF)
                    fputc(ch, target);
                
                fclose(target);
                fclose(source);

                char message[128] = GREEN"Succes-copy: "WHITE;
                char cwd[PATH_MAX];
                getcwd(cwd, sizeof(cwd));
                strcat(message, "\"");
                strcat(message, cwd);
                strcat(message, "\\"PURPLE);
                strcat(message, cmd_buffer[0]);
                strcat(message, WHITE"\"");
                strcat(message, GREEN" file copied successfully.\n"white);
                fflush(stdout);
                write(STDOUT_FILENO, message, strlen(message));
            }
        }
        else { // If specified file doesn't exist
            char message[256] = RED"Error-copy: "WHITE;
            char cwd[PATH_MAX];
            getcwd(cwd,sizeof(cwd));
            strcat(message, WHITE"\"");
            strcat(message, cwd);
            strcat(message, "\\"PURPLE);
            strcat(message, cmd_buffer[0]);
            strcat(message, WHITE"\"");
            strcat(message, YELLOW" doesn't exist.\n"white);
            fflush(stdout);
            write(STDOUT_FILENO, message, strlen(message));
        }
    }
    else {  // If the directory to copy is specified
        FILE *source, *target;
        if((source = fopen(cmd_buffer[0], "r")) != NULL) { // If specified file exist
            char target_dir[PATH_MAX];
            char cwd[PATH_MAX];
            
            for(int i=1; i<num_of_input-1; i++) {
                strcat(target_dir, cmd_buffer[i]);
            }
            if(DirectoryExists(target_dir)) { // If specified directory exist
                if((target_dir[strlen(target_dir)-1]) != '/') // if there is no a '/' at the end of the input
                    strcat(target_dir,"/"); // destionation path + "/"
                strcat(target_dir, cmd_buffer[0]); // destionation path + filename
                
                if((target = fopen(target_dir, "r")) != 0) { // if there is a file with the same name in the specified directory
                    char source_name[64];
                    strcat(source_name, cmd_buffer[0]);
                    strcat(source_name, "(kopya)");

                    if((fopen(source_name, "r") != NULL)) { // if there is a copy of the file in the specified directory
                        char message[128] = RED"Error-copy: "WHITE;
                        strcat(message, target_dir);
                        strcat(message, YELLOW" copy of files already exist in specified directory.\n"white);
                        fflush(stdout);
                        write(STDOUT_FILENO, message, strlen(message));
                        fclose(target);
                    }
                    else {
                        char ch;
                        target = fopen(target_dir, "w");
                        while ((ch = fgetc(source)) != EOF)
                            fputc(ch, target);
                        
                        fclose(target);

                        char message[128] = GREEN"Succes-copy: "WHITE;
                        char cwd[PATH_MAX];
                        getcwd(cwd, sizeof(cwd));
                        strcat(message, "\"");
                        strcat(message, cwd);
                        strcat(message, "\\"PURPLE);
                        strcat(message, cmd_buffer[0]);
                        strcat(message, WHITE"\"");
                        strcat(message, GREEN" file copied successfully.\n"white);
                        fflush(stdout);
                        write(STDOUT_FILENO, message, strlen(message));
                    }
                }
                else { // If there is no a file with same name in the specified directory
                    char ch;
                    target = fopen(target_dir, "w");
                    while((ch = fgetc(source)) != EOF)
                        fputc(ch, target);

                    fclose(target);

                    char absolutePath[256];
                    getcwd(absolutePath, sizeof(absolutePath));
                    
                    char message[256] = GREEN"Succes-copy: "WHITE;
                    strcat(message, "from \"");
                    strcat(message, cwd);
                    strcat(message, "\\"PURPLE);
                    strcat(message, cmd_buffer[0]);
                    strcat(message, WHITE"\" to \""BLUE);
                    strcat(message, target_dir);
                    strcat(message, GREEN"\" file copied successfully.\n"white);
                    fflush(stdout);
                    write(STDOUT_FILENO, message, strlen(message));
                }
            }
            else { // If specified directory doesn't exist
                char message[256] = RED"Error-copy: "WHITE;
                strcat(message, WHITE"\"");
                strcat(message, target_dir);
                strcat(message, WHITE"\"");
                strcat(message, YELLOW" directory doesn't exist.\n"white);
                fflush(stdout);
                write(STDOUT_FILENO, message, strlen(message));
            }
            fclose(source);
        }
        else { // if specified file doesn't exist
            char message[256] = RED"Error-copy: "WHITE;
            char cwd[PATH_MAX];
            getcwd(cwd,sizeof(cwd));
            strcat(message, WHITE"\"");
            strcat(message, cwd);
            strcat(message, "\\"PURPLE);
            strcat(message, cmd_buffer[0]);
            strcat(message, WHITE"\"");
            strcat(message, YELLOW" doesn't exist.\n"white);
            fflush(stdout);
            write(STDOUT_FILENO, message, strlen(message));
        }
    }
}

// Move specified file to specified directory
void moveCommand(char *buffer){
    /*
        It only works if the specified file and specified directory exist
        @Parameters:
            buffer: command expression
        @Return:
            None    
    */
    char *cmd_buffer[MAX_FILE_WORD_COUNT];
    
    // Split command line into appropriate parts
    int num_of_input=0; // one more than the number of arguments in the command
    char *input = strtok(buffer, " ");
    while(input != NULL) {
        input = strtok(NULL, " ");
        cmd_buffer[num_of_input] = input;
        num_of_input++;
    }

    if(num_of_input == 1) { // If the argument number is 0, it does nothing
        printf("");
 
    }
    else if(num_of_input == 2) { // If the argument number is 1, it's wrong. 
        char message[128];
        strcat(message, RED"Error-move: ");
        strcat(message, WHITE"invalid arguments\n");
        strcat(message, white"\tTry: \"move <source> <destionation>\"\n");
        fflush(stdout);
        write(STDOUT_FILENO, message, strlen(message));
    }
    else { // If the command is valid
        FILE *source, *target;
        if((source = fopen(cmd_buffer[0], "r")) != NULL) { // If specified file exist
            char target_dir[PATH_MAX];
            char cwd[PATH_MAX];
            
            for(int i=1; i<num_of_input-1; i++) {
                strcat(target_dir, cmd_buffer[i]);
            }

            if(DirectoryExists(target_dir)) { // If specified directory exist
                if((target = fopen(target_dir, "r")) != 0) { // If there no a file with same name in the specified directory
                    char message[128] = RED"Error-move: "WHITE;
                    strcat(message, target_dir);
                    strcat(message, YELLOW" there is another file with the same name in the specified directory.\n"white);
                    fflush(stdout);
                    write(STDOUT_FILENO, message, strlen(message));
                    fclose(target);
                }
                else { // If there is no a file with same name in the specified directory
                    if((target_dir[strlen(target_dir)-1]) != '/') // if there is no a '/' at the end of the input
                        strcat(target_dir,"/"); // destionation path + "/"
                    strcat(target_dir, cmd_buffer[0]); // destionation path + filename
                    
                    char ch;
                    target = fopen(target_dir, "w");
                    while((ch = fgetc(source)) != EOF)
                        fputc(ch, target);

                    fclose(target);
                    fclose(source);
                    remove(cmd_buffer[0]);

                    char absolutePath[256];
                    getcwd(absolutePath, sizeof(absolutePath));
                    
                    char message[256] = GREEN"Succes-move: "WHITE;
                    strcat(message, "from \"");
                    strcat(message, absolutePath);
                    strcat(message, cwd);
                    strcat(message, "\\"PURPLE);
                    strcat(message, cmd_buffer[0]);
                    strcat(message, WHITE"\" to \""BLUE);
                    strcat(message, target_dir);
                    strcat(message, GREEN"\" file moved successfully.\n"white);
                    fflush(stdout);
                    write(STDOUT_FILENO, message, strlen(message));
                }
            }
            else { // If specified directory exist
                char message[256] = RED"Error-move: "WHITE;
                strcat(message, WHITE"\"");
                strcat(message, target_dir);
                strcat(message, WHITE"\"");
                strcat(message, YELLOW" directory doesn't exist.\n"white);
                fflush(stdout);
                write(STDOUT_FILENO, message, strlen(message));
            }
            
        }
        else { // If specified file doesn't exist
            char message[256] = RED"Error-move: "WHITE;
            char cwd[PATH_MAX];
            getcwd(cwd,sizeof(cwd));
            strcat(message, WHITE"\"");
            strcat(message, cwd);
            strcat(message, "\\"PURPLE);
            strcat(message, cmd_buffer[0]);
            strcat(message, WHITE"\"");
            strcat(message, YELLOW" doesn't exist.\n"white);
            fflush(stdout);
            write(STDOUT_FILENO, message, strlen(message));
        }
        fclose(source);
    }
}

// Helps with content of commands
void helpCommand(char *buffer){
    /*
        It only works if the specified command exist
        @Parameters:
            buffer: command expression
        @Return:
            None    
    */
    char *cmd_buffer[MAX_FILE_WORD_COUNT];
    
    int num_of_input=0;
    char *input = strtok(buffer, " ");
    while(input != NULL) {
        input = strtok(NULL, " ");
        cmd_buffer[num_of_input] = input;
        num_of_input++;
    }
    if(num_of_input > 2) {
        char message[256];
        strcat(message, RED"Error-help: ");
        strcat(message, WHITE"help argument limit has been exceeded.");
        strcat(message,PURPLE"[maximum file creation limit = 1]\n");
        strcat(message, white"\tTry: \"help <command>\" or  \"help\"\n");
        fflush(stdout);
        write(STDOUT_FILENO, message, strlen(message));
    }
    else if(num_of_input == 1) {
        fflush(stdout);
        write(STDOUT_FILENO, help_help, strlen(help_help));
    }
    else {
        if(isCommand(cmd_buffer[0])) {
            int commandIndex = getCommandIndex(cmd_buffer[0]);

            switch (commandIndex)
            {
            case 0: // help_create
                fflush(stdout);
                write(STDOUT_FILENO, help_create, strlen(help_create));
                break;
            case 1: // help_remove
                fflush(stdout);
                write(STDOUT_FILENO, help_remove, strlen(help_remove));
                break;
            case 2: // help_rename
                fflush(stdout);
                write(STDOUT_FILENO, help_rename, strlen(help_rename));
                break;
            case 3: // help_copy
                fflush(stdout);
                write(STDOUT_FILENO, help_copy, strlen(help_copy));
                break;
            case 4: // help_move
                fflush(stdout);
                write(STDOUT_FILENO, help_move, strlen(help_move));
                break;
            case 6  : // help_clear
                fflush(stdout);
                write(STDOUT_FILENO, help_clear, strlen(help_clear));
                break;
            default:
                break;
            }
        }
        else {
                char message[256];
                strcat(message, RED"Error-help: ["GREEN);
                strcat(message, cmd_buffer[0]);
                strcat(message, RED"]");
                strcat(message, WHITE" :help command doesn't have this argument.\n");
                strcat(message, white"\tTry: \"help <command>\" or  \"help\"\n");
                fflush(stdout);
                write(STDOUT_FILENO, message, strlen(message));
                
        }
    }
    strcpy(buffer, "");
}

// Clear the terminal screen
void clearCommand(){
    system("cls");
}


#endif