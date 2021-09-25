#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <fcntl.h>
#include <unistd.h>
#include <iostream>

int main()
{
        int isClosestdOut =  close(1);
        if (isClosestdOut == -1 ) {
            perror("Cannot close std out descriptor");
            return EXIT_FAILURE;
        }

        int fd = open("test", O_WRONLY | O_CREAT );
        if (fd == -1 ) {
            perror("File cannot be opened");
            return EXIT_FAILURE;
        }
        std::cout << "This is a program that creates and write into a file without fstream, using the POSIX interface" << std::endl;

        close(fd);
        return 0;
}                                                                                                                                                                                                                         
