#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <fcntl.h>
#include <unistd.h>
#include <iostream>

int main()
{
        int fd = open("test", O_WRONLY | O_CREAT );
        if (fd == -1 ) {
            perror("File cannot be opened");
            return EXIT_FAILURE;
        }
        char buf [256] = "This is a program that creates and write into a file without fstream, using the POSIX interface";
        ssize_t fgWrite = write(fd, &buf, strlen(buf));

        if (fgWrite == -1)
        {
                perror("Cannot write in file");
                return EXIT_FAILURE;
        } 
        else if (fgWrite < strlen(buf))
        {
              perror("it is not all text");  
        }

        close(fd);
        return 0;
}                                                                                                                                                                                                                         