#ifndef UTILITY_FUNCTION_H
#define UTILITY_FUNCTION_H

#include <string.h>
#include <stdbool.h>
#include <io.h>
#include <sys/types.h>
#include <sys/stat.h>
#include "info.h"


// The command entered matches which command in the Commands string. Returns its index
int getCommandIndex(char *buffer) {
    /*
        @Parameters:
            buffer: command expression or command line
        @Return:
            int: command's index.
    */
    char t_buffer[64];
    strcpy(t_buffer, buffer);

    int commandIndex;
    char *input = strtok(t_buffer, " ");

    for(int i=0; i<NUMBER_OF_COMMAND; i++){
        if(!strcmp(input, gCommands[i])){
            commandIndex = i;
            break;
        }
    }
    return commandIndex;
}

// Is the command entered valid?. Return 1 if true, return 0 if not
int isCommand(char *input) {
    /*
        @Parameters:
            buffer: command expression or command line
        @Return:
            int: 1 or 0
    */
    int i=0;
    while(i < NUMBER_OF_COMMAND) {
        if(strcmp(gCommands[i], input) == 0) {
            return 1;
        }
        i++;
    }
    return 0;
}

// Does the specified directory exist? Return true if true, return false if not
bool DirectoryExists( const char* absolutePath ){
    /*
        @Parameters:
            buffer: command expression or command line
        @Return:
            bool: true or false
    */
    if( _access( absolutePath, 0 ) == 0 ){

        struct stat status;
        stat( absolutePath, &status );

        return (status.st_mode & S_IFDIR) != 0;
    }
    return false;
}




#endif