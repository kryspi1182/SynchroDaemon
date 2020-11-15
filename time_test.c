#include <sys/types.h>
#include <sys/stat.h>
#include <stdio.h>
#include <time.h>
#include "write_log.h"
#include "time_test.h"

float time_test(char* file1, char* file2)
{
        write_log("Funkcja time_test");
        struct stat filestat;
        struct stat filestat2;

        stat(file1,&filestat);
        stat(file2,&filestat2);

        
        if(filestat.st_mtime > filestat2.st_mtime) //file1 bardziej aktualny niz file2 - demon ignoruje
        {
                return 1;
        }
                
        
        else if(filestat.st_mtime < filestat2.st_mtime) //file1 mniej aktualny niz file2 - demon kopiuje
        {
                return -1;
        }
        else // pliki taka sama data - ignoruj
                return 0;

}