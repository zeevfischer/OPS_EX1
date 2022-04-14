#include <string.h>
#include <unistd.h>
#include <dirent.h>
#include "TCP.h"
#include <stdio.h>
#include <stdlib.h>

void print_cmd()
{
    char cmd[100];
    getcwd(cmd, 100);
    printf("Hellow-user-at:%s$ ", cmd);
}
void dir()
{
    DIR *dir;
    dir = opendir(".");
    if (dir == NULL)
    {
        printf("Error failed to open directory\n");
        return;
    }
    struct dirent *reader;
    reader = readdir(dir);
    while (reader != NULL)
    {
        printf("%s  ", reader->d_name);
        reader = readdir(dir);
    }
    printf("\n");
    closedir(dir);
}

int main(int argc, char const *argv[])
{
    char command[100];

    while (strcmp(command, "EXIT"))
    {
        // printf("yes master");

        print_cmd();   // print a prumpt
        gets(command); // get command

        if (strncmp(command, "ECHO ", 5) == 0)
        {
            // no need to have a stop on i becaude at the end of every String there is a \0
            for (int i = 5; command[i] != '\0'; i++)
            {
                printf("%c", command[i]);
            }
            printf("\n");
        }
        else if (strncmp(command, "TCP PORT", 8) == 0)
        {
            clinet();
            dup2(1, 500);
            dup2(sock, 1);
        }
        else if (strncmp(command, "LOCAL", 5) == 0)
        {
            close(sock);
            dup2(500, 1);
        }
        else if (strcmp(command, "DIR") == 0)
        {
            dir();
        }
        else if (strncmp(command, "CD ", 3) == 0)
        {
            char new_path[100];
            int i = 0;
            while (command[i] != '\0')
            {
                new_path[i] = command[i + 3];
                i++;
            }
            new_path[i] = '\0';
            // this is a system call chdir
            if (chdir(new_path) == -1)
            {
                printf("-bash: cd: %s: No such file or directory\n", new_path);
                return 0;
            }
        }
        else if (strncmp(command, "COPY ", 5) == 0)
        {
            char *src_name;
            char *dest_name;
            char s[2] = " ";
            src_name = strtok(command, s);
            src_name = strtok(NULL, s);
            dest_name = strtok(NULL, s);
            FILE *src_file = fopen(src_name, "r");
            FILE *dest_file = fopen(dest_name, "w+");

            if (src_file == NULL || dest_file == NULL)
            {
                fclose(src_file);
                fclose(dest_file);
                printf("file Error\n");
                return 0;
            }

            char temp;
            while (fscanf(src_file, "%c", &temp) != EOF)
            {
                fprintf(dest_file, "%c", temp);
            }
            fclose(src_file);
            fclose(dest_file);
        }
        else if (strncmp(command, "DELETE ", 7) == 0)
        {
            char new_path[100];
            int i = 0;
            while (command[i] != '\0')
            {
                new_path[i] = command[i + 7];
                i++;
            }
            new_path[i] = '\0';
            unlink(new_path);
        }
        else
        {
            // system(command);
            // this is by the name a system command
            int sys = fork();
            if (sys < 0)
            {
                printf("fork failed\n");
            }
            if (sys == 0)
            {
                char path[100] = "/bin/";
                strcat(path, command);
                execl(path, command, NULL);
            }
            wait();
        }
    }
    return 0;
}