#ifndef FILE_HANDLING_H
#define FILE_HANDLING_H


#include <stdio.h>
#include "command.h"




// Call the corresponding function if the command is valid
void commandController(char *buffer){
    char temp_buffer[64];
    strcpy(temp_buffer, buffer);
    
    int commandIndex;
    commandIndex = getCommandIndex(temp_buffer);

    switch (commandIndex)
    {
    case 0: // if command is create
        createCommand(temp_buffer);
        break;
    case 1: // if command is remove
        removeCommand(temp_buffer);
        break;
    case 2: // if command is rename
        renameCommand(temp_buffer);
        break;
    case 3: // if command is copy
        copyCommand(temp_buffer);
        break;
    case 4: // if command is move
        moveCommand(temp_buffer);
        break;
    case 5: // if command is help
        helpCommand(temp_buffer);
        break;
    case 6: // if command is claer
        clearCommand();
        break;

    default:
        break;
    }
}

// Get the input on STDIN
void getSTDIN(char *buffer){
    scanf("%[^\n]s", buffer);
    fflush(stdin);  // used to clear the buffer and accept the next string
}

// If command is invalid, print this situation to STDOUT
void invalidCommand(char *command){
    char message[64] = WHITE"error: "GREEN;
    strcat(strcat(message, command), RED": command not found\n"white);
    fflush(stdout);
    write(STDOUT_FILENO, message, strlen(message));
}

// Process the input command line
void processBuffer(char *buffer) {
    char temp_buffer[64];
    strcpy(temp_buffer, buffer);

    if (strlen(temp_buffer) != 0) { // If the commandline is not empty
        char *input = strtok(buffer, " ");
        if(!isCommand(input)){ // If the command is invalid
            invalidCommand(input);
        }
        else { // If the command is valid
            commandController(temp_buffer);
        }
        strcpy(buffer, "");
    }
    else // If the command line is empty, do nothing
        printf("");
}

// File Handling (start function)
void displayFileHandler(){
    file_info(); // set help information of commands
    char buffer[64];
    printf("%s\n >>> %sWelcome to %sFILE SYSTEM%s on terminal %s<<<\n\n",RED, YELLOW, PURPLE,YELLOW,RED);
    fflush(stdout);
    write(STDOUT_FILENO, general_info, strlen(general_info));
    
    do{ // keep the app running
        printf("%s\nFILE SYSTEM %s~ %s$ "white, BLACK,YELLOW,WHITE);
        getSTDIN(buffer);
        processBuffer(buffer);
    }while(1);
}



#endif 


