#include <sys/types.h>
#include <sys/stat.h>
#include <sys/sendfile.h>
#include <stdio.h>
#include <stdlib.h>
#include <fcntl.h>
#include <errno.h>
#include <unistd.h>
#include <syslog.h>
#include <string.h>
#include <time.h>
#include <dirent.h>
#include <signal.h>
#include "write_log.h"
#include "time_test.h"
#include "file_copy.h"

struct dirent *ent_cat;
struct dirent *ent_cat2;
int recursive_read_flag = 0;
int size_limit = 0;

struct string
{
        char content[100];
};

struct string buffer_cat[100][2];
int recur_cats[100];

void cat_read (char* cat, char* cat2, char* prefix)
{
        write_log("Funkcja cat_read");
        write_log(cat);
        write_log(cat2);
        DIR *dir_cat;
        /*char* rec_cat;
        char* rec_cat2;
        strcpy(rec_cat, cat);
        strcpy(rec_cat2, cat2);
        char* rec_file;*/
        struct string testsss;
        int i = 0;
        if ((dir_cat = opendir (cat)) != NULL) {
                while ((ent_cat = readdir (dir_cat)) != NULL) {

                        if (ent_cat->d_type == DT_REG)
                        {
                                if(prefix == NULL)
                                {
                                        strcpy(buffer_cat[i][0].content, ent_cat->d_name);
                                }
                                /*else
                                {
                                        //strcpy(rec_file, "/");
                                        strcpy(rec_file, prefix);
                                        strcat(rec_file, "/");
                                        strcat(rec_file, ent_cat->d_name);
                                        strcpy(buffer_cat[i][0].content, rec_file);
                                }*/
                                
                                //printf("%i writing to buffer number %i file %s \n",i, 0, ent_cat->d_name);
                                write_log("Funkcja cat_read - pisanie nazwy pliku z katalogu zrodlowego do buforu");
                                i++;
                        }
                        /*else if(ent_cat->d_type == DT_DIR && recursive_read_flag !=0) /*TODO: REKURENCYJNE CZYTANIE PODKATALOGOW 
                        {
                                openlog ("logdemproj", LOG_CONS | LOG_PID | LOG_NDELAY, LOG_LOCAL1);
                                syslog (LOG_INFO, "proba rekurencji, cat read i nastepujace sciezki:");
                                closelog();
                                strcat(rec_cat, "/");
                                strcat(rec_cat2, "/");
                                strcat(rec_cat, ent_cat->d_name);
                                strcat(rec_cat2, ent_cat->d_name);
                                //closedir (dir_cat);
                                openlog ("logdemproj", LOG_CONS | LOG_PID | LOG_NDELAY, LOG_LOCAL1);
                                syslog (LOG_INFO, "%s ||| %s", rec_cat, rec_cat2);
                                closelog();
                                //cat_read(rec_cat, rec_cat2, ent_cat->d_name);
                                
                                //dir_cat = opendir(cat);
                        }*/
                }
                
                closedir (dir_cat);
        } else {
        /* could not open directory */
        //printf ("opening directory went wrong \n");
                char *er = strerror(errno);
                write_log("Funkcja cat_read - blad przy otwieraniu folderu zrodlowego:");
                write_log(er);
        }
         i=0;
        if ((dir_cat = opendir (cat2)) != NULL) {
                while ((ent_cat = readdir (dir_cat)) != NULL) {

                        if (ent_cat->d_type == DT_REG)
                        {
                                if(prefix == NULL)
                                {
                                        strcpy(buffer_cat[i][1].content, ent_cat->d_name);
                                }
                                /*else
                                {
                                        //strcpy(rec_file, "/");
                                        strcpy(rec_file, prefix);
                                        strcat(rec_file, "/");
                                        strcat(rec_file, ent_cat->d_name);
                                        strcpy(buffer_cat[i][1].content, rec_file);
                                }*/
                                
                                //printf("%i writing to buffer number %i file %s \n",i, 0, ent_cat->d_name);
                                write_log("Funkcja cat_read - pisanie nazwy pliku z katalogu docelowego do buforu");
                                i++;
                        }
                        /*else if(ent_cat->d_type == DT_DIR && recursive_read_flag !=0) /*TODO: REKURENCYJNE CZYTANIE PODKATALOGOW 
                        {
                                strcpy(rec_cat, cat);
                                strcpy(rec_cat2, cat2);
                                strcat(rec_cat, "/");
                                strcat(rec_cat2, "/");
                                strcat(rec_cat, ent_cat->d_name);
                                strcat(rec_cat2, ent_cat->d_name);
                                closedir (dir_cat);
                                cat_read(rec_cat, rec_cat2, ent_cat->d_name);
                                dir_cat = opendir(cat2);
                        }*/
                }
                
                closedir (dir_cat);
        } else {
        /* could not open directory */
        //printf ("opening directory went wrong \n");
                char *er = strerror(errno);
                write_log("Funkcja cat_read - blad przy otwieraniu folderu docelowego:");
                write_log(er);
        }
        
        
}

void demon (char *path1, char *path2) 
{
                write_log("Demon - uruchomienie");
                write_log(path1);
                write_log(path2);
                cat_read(path1, path2, NULL);
                int ix=0;
                int iy=0;
                float test;
                int file_checks[100];
                char file1[100];
                strcpy(file1, path1);
                char file2[100];
                strcpy(file2, path2);
                for(ix=0;ix<100;ix++)
                {
                        /*openlog ("logdemproj", LOG_CONS | LOG_PID | LOG_NDELAY, LOG_LOCAL1);
                        syslog (LOG_INFO, "Demon - petla");
                        closelog();*/
                        /*printf("%i buffer1: %s buffer2: %s \n", ix, buffer_cat[ix][0].content, buffer_cat[ix][1].content);*/
                        if(strcmp(buffer_cat[ix][0].content, ""))
                        {
                                for(iy=0;iy<100;iy++)
                                {
                                        /*openlog ("logdemproj", LOG_CONS | LOG_PID | LOG_NDELAY, LOG_LOCAL1);
                                        syslog (LOG_INFO, "Demon - petla wewn");
                                        closelog();*/
                                        if(strcmp(buffer_cat[iy][1].content, ""))
                                        {
                                                strcat(file1, "/");
                                                strcat(file2, "/");
                                                strcat(file1, buffer_cat[ix][0].content);
                                                strcat(file2, buffer_cat[iy][1].content);
                                                
                                                if(!(strcmp(buffer_cat[ix][0].content, buffer_cat[iy][1].content)))
                                                {
                                                        test = time_test(file1, file2);
                                                        file_checks[ix] = 2;
                                                        if(test == 1)
                                                        {
                                                                write_log(buffer_cat[ix][0].content);
                                                                write_log("jest bardziej aktualny od");
                                                                write_log(buffer_cat[iy][1].content);
                                                                write_log("kopiowanie");
                                                                file_copy(file1, file2, size_limit);
                                                        }
                                                        else if(test == -1)
                                                        {
                                                                write_log(buffer_cat[ix][0].content);
                                                                write_log("jest mniej aktualny od");
                                                                write_log(buffer_cat[iy][1].content);
                                                                write_log("ignorowanie");
                                                        }
                                                        else
                                                        {
                                                                write_log(buffer_cat[ix][0].content);
                                                                write_log("ma taka sama date modyfikacji co");
                                                                write_log(buffer_cat[iy][1].content);
                                                                write_log("mozliwy blad");
                                                        }
                                                }
                                                        strcpy(file1, path1);
                                                        strcpy(file2, path2);
                                        }
                                }

                        }
                        /*else
                        {
                                openlog ("logdemproj", LOG_CONS | LOG_PID | LOG_NDELAY, LOG_LOCAL1);
                                syslog (LOG_INFO, "Demon - warunek na null niespelniony");
                                closelog();
                        }*/
                        
                }
                strcpy(file1, path1);
                strcpy(file2, path2);
                for(ix = 0; ix <100; ix++)
                {
                        if(file_checks[ix] != 2 && strcmp(buffer_cat[ix][0].content, ""))
                        {
                                write_log("Flaga wskazuje na plik ktorego nie ma w katalogu docelowym, a jest w zrodlowym - kopiowanie");
                                strcat(file1, "/");
                                strcat(file2, "/");
                                strcat(file1, buffer_cat[ix][0].content);
                                strcat(file2, buffer_cat[ix][0].content);
                                file_copy(file1, file2, size_limit);
                                file_checks[ix] = 1;
                                strcpy(file1, path1);
                                strcpy(file2, path2);                
                        }
                }
	//} 
}

volatile sig_atomic_t signal_flag = 1;

void handler(int signum){
	write_log("Otrzymano sygnal");
	signal_flag = 0;
	return;
    //exit(signum);
}

int main(int argc, char * argv[]) 
{
        DIR *test_cat;
        if((test_cat = opendir (argv[1])) == NULL)
        {
                write_log("Pierwszy argument jest niepoprawny - bledna nazwa katalogu");
                closedir(test_cat);
                return 0;
        }

        if((test_cat = opendir (argv[2])) == NULL)
        {
                write_log("Drugi argument jest niepoprawny - bledna nazwa katalogu");
                closedir(test_cat);
                return 0;
        }
        
        int sec_count = 0;
        int sec_limit;
        if (argc < 4)
        {
                sec_limit = 300;
        }
        else
        {
                sec_limit = atoi(argv[3]);
        }
        if (argc < 5)
        {
                size_limit = 0;
        }
        else
        {
                size_limit = atoi(argv[4]);
        }
        
        //char chartest = 'h';
        //printf("%d \n", sec_limit);
        //Our process ID and Session ID 
        pid_t pid, sid;
        
        //Fork off the parent process
        pid = fork();
        if (pid < 0) {
                exit(EXIT_FAILURE);
        }
        //If we got a good PID, then
           //we can exit the parent process.
        if (pid > 0) {
                exit(EXIT_SUCCESS);
        }

        //Change the file mode mask
        umask(0);
                
        //Open any logs here        
                
        //Create a new SID for the child process 
        sid = setsid();
        if (sid < 0) {
                //Log the failure
                exit(EXIT_FAILURE);
        }
        

        
        //Change the current working directory
        if ((chdir("/")) < 0) {
                //Log the failure
                exit(EXIT_FAILURE);
        }
        
        //Close out the standard file descriptors
        close(STDIN_FILENO);
        close(STDOUT_FILENO);
        close(STDERR_FILENO);
        
        //Daemon-specific initialization goes here
        signal(SIGUSR1, handler); //TODO obsluga bledow!
        //The Big Loop

        while (1) {
                
                if(sec_count < sec_limit && signal_flag)
                {
                        write_log("Demon spi");
                        //sleep(1); 
                        //sec_count++;
                }
                else if (!(signal_flag))
                {
                        write_log("Demon otrzymal sygnal");
                        demon(argv[1], argv[2]); 
                        signal_flag = 1; 
                }
                else
                {
                        write_log("Demon sie obudzil");
                        demon(argv[1], argv[2]);
                        sec_count = 0;
                }
                sleep(1);
                sec_count++;
        }
   exit(EXIT_SUCCESS);
   return 0;
}
