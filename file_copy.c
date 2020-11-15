#include <sys/types.h>
#include <sys/stat.h>
#include <sys/sendfile.h>
#include <stdio.h>
#include <stdlib.h>
#include <fcntl.h>
#include <errno.h>
#include <unistd.h>
#include <string.h>
#include <time.h>
#include "write_log.h"
#include "file_copy.h"

void file_copy(char *file_src, char *file_dest, int size_limit)
{
    write_log("Funkcja file_copy");
    char buffer[128];  
	size_t bytes_read; 
    size_t filesize;
    struct stat srcstat;
    stat(file_src, &srcstat);
    filesize = srcstat.st_size; 
	int error_num;
	int fd_src = open (file_src, O_RDONLY); 
    int fd_dest = open (file_dest, O_WRONLY | O_CREAT | O_TRUNC , 0666); 
    int cond = 0;
	if (fd_src == -1) {
		error_num = errno;
		write_log("Funkcja file_copy - blad przy otwieraniu pliku:");
                write_log(strerror(error_num));
		return;}

    if(filesize < size_limit)
    {
        write_log("Funkcja file_copy - metoda read/write");
        do { 

            bytes_read = read (fd_src, buffer, sizeof (buffer)); 

            if(bytes_read == -1){
                error_num = errno;
                write_log("Blad przy czytaniu:");
                write_log(strerror(error_num));
                return;}


            write (fd_dest, buffer, bytes_read); 


        } while (bytes_read == sizeof (buffer));
    }
    else
    {
        write_log("Funkcja file_copy - metoda sendfile");
        sendfile(fd_dest, fd_src, NULL, filesize);
    }
        
  	close (fd_src);
    close (fd_dest); 

  	return; 
}