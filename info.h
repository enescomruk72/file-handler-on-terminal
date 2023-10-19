#ifndef INFO_H
#define INFO_H

#include "color.h"

#define NUMBER_OF_COMMAND 7
#define STRING_OF_COMMAND 10
#define MAX_CREATE_FILE 5
#define MAX_FILE_WORD_COUNT 16

char const gCommands[NUMBER_OF_COMMAND][STRING_OF_COMMAND] =  {"create", "remove", "rename", "copy", "move", "help", "clear"};
int const gCommandsIndex[NUMBER_OF_COMMAND] = {0,1,2,3,4,5};

char general_info[512];
char help_create[256];
char help_remove[256];
char help_rename[256];
char help_copy[256];
char help_move[256];
char help_help[512];
char help_clear[256];

// Fill in all relevant string arrays to inform
void file_info() {
    // help_general info
        strcat(general_info, GREEN"Available Commands:\n"BLUE);
        strcat(general_info, "\tcreate		create new file\n");
        strcat(general_info, "\tremove		remove existing file\n");
        strcat(general_info, "\trename		rename existing file\n");
        strcat(general_info, "\tcopy		copy existing file\n");
        strcat(general_info, "\tmove		move existing file\n");
        strcat(general_info, "\thelp		help with commands\n");
        strcat(general_info, "\tclear		clear the screen\n");
        strcat(general_info, GREEN"SYNTAX\n"BLUE);
        strcat(general_info, "\tcreate  <filename>\n");
        strcat(general_info, "\tremove  <filename>\n");
        strcat(general_info, "\trename  <old file name>  <new file name>\n");
        strcat(general_info, "\tcopy  <source>  <destination>\n");
        strcat(general_info, "\tmove  <old file path>  <new file path>\n");
        strcat(general_info, "\thelp  --command\n");
        strcat(general_info, "\tclear\n");
    
    // help_create info 
        strcat(help_create, WHITE"NAME\n");
        strcat(help_create, white"\tcreate\n");
        strcat(help_create, WHITE"SYNTAX\n");
        strcat(help_create, white"\tcreate  <filename>\n");
        strcat(help_create, WHITE"DESCRIPTION\n");
        strcat(help_create, white"\tCreates a new file. If that file exists, it overwrites that file.\n");

    // help_remove info
        strcat(help_remove, WHITE"NAME\n");
        strcat(help_remove, white"\tremove\n");
        strcat(help_remove, WHITE"SYNTAX\n");
        strcat(help_remove, white"\tremove <filename>\n");
        strcat(help_remove, WHITE"DESCRIPTION\n");
        strcat(help_remove, white"\tRemove the specified file. If the file does not exist does nothing.\n");

    // help_rename info
        strcat(help_rename, WHITE"NAME\n");
        strcat(help_rename, white"\trename\n");
        strcat(help_rename, WHITE"SYNTAX\n");
        strcat(help_rename, white"\trename  <oldfilename> <newfilename>\n");
        strcat(help_rename, WHITE"DESCRIPTION\n");
        strcat(help_rename, white"\tRename the specified file. If the file does not exist or there is another file with the same name, does nothing\n");

    // help_copy info
        strcat(help_copy, WHITE"NAME\n");
        strcat(help_copy, white"\tcopy\n");
        strcat(help_copy, WHITE"SYNTAX\n");
        strcat(help_copy, white"\tcopy  <source>  <destination>\n");
        strcat(help_copy, WHITE"DESCRIPTION\n");
        strcat(help_copy, white"\tCopy the specified file. If the file does not exist does nothing\n");
    
    // help_move info
        strcat(help_move, WHITE"NAME\n");
        strcat(help_move, white"\tmove\n");
        strcat(help_move, WHITE"SYNTAX\n");
        strcat(help_move, white"\tmove  <old file path>  <new file path>\n");
        strcat(help_move, WHITE"DESCRIPTION\n");
        strcat(help_move, white"\tMove the specified file. If the file does not exist or there is another file with the same name in destination folder, does nothing\n");

    // help_help info
        strcat(help_help, BLUE"For more information on a specific command, type \"help command-name\"\n"WHITE);
        strcat(help_help, "\tcreate		create new file\n");
        strcat(help_help, "\tremove		remove existing file\n");
        strcat(help_help, "\trename		rename existing file\n");
        strcat(help_help, "\tcopy		copy existing file\n");
        strcat(help_help, "\tmove		move existing file\n");
        strcat(help_help, "\thelp		help with commands\n");
        strcat(help_help, BLUE"SYNTAX\n"WHITE);
        strcat(help_help, "\tcreate  <filename>\n");
        strcat(help_help, "\tremove  <filename>\n");
        strcat(help_help, "\trename  <old file name>  <new file name>\n");
        strcat(help_help, "\tcopy  <source>  <destination>\n");
        strcat(help_help, "\tmove  <old file path>  <new file path>\n");
        strcat(help_help, "\thelp  --command\n"white);

    // help_clear info
        strcat(help_clear, WHITE"NAME\n");
        strcat(help_clear, white"\tclear\n");
        strcat(help_clear, WHITE"SYNTAX\n");
        strcat(help_clear, white"\tclear\n");
        strcat(help_clear, WHITE"DESCRIPTION\n");
        strcat(help_clear, white"\tClear the terminal screen\n");


};




#endif