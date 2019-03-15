#include <sys/types.h>
#include <sys/stat.h>
#include <stdio.h>
#include <stdlib.h>
#include <fcntl.h>
#include <errno.h>
#include <unistd.h>
#include <syslog.h>
#include <string.h>
#include <dirent.h>

const char *get_filename_ext(const char *filename) {
    const char *dot = strrchr(filename, '.');
    if(!dot || dot == filename) return "";
    return dot + 1;
}

int main() {
  pid_t pid, sid;

  pid = fork();

  if (pid < 0) {
    exit(EXIT_FAILURE);
  }

  if (pid > 0) {
    exit(EXIT_SUCCESS);
  }

  umask(0);

  sid = setsid();

  if (sid < 0) {
    exit(EXIT_FAILURE);
  }

  if ((chdir("/")) < 0) {
    exit(EXIT_FAILURE);
  }

  close(STDIN_FILENO);
  close(STDOUT_FILENO);
  close(STDERR_FILENO);

  while(1) {
    char *ptrToSubString;
    char fileName[100];

    DIR *dir;
    struct dirent *ent;
    dir = opendir("/home/ikul/Soal1");
    if (dir != NULL) {
            while((ent = readdir(dir)) != NULL) {
                   strcpy(fileName,ent->d_name);
                   ptrToSubString = strstr(fileName,".png");
                   if (ptrToSubString != NULL) {
	
			char temp[100]="";
			strncpy(temp, ent->d_name, (strlen (ent->d_name)-4));
			strcat(temp, "_grey.png");
			char oldname[100] ="";
			strcpy (oldname, "/home/ikul/Soal1/");
			strcat (oldname, ent->d_name);
			
    			char newname[100] ="";
    			strcpy (newname, "/home/ikul/modul2/gambar/");
			strcat (newname, temp);

			rename( oldname, newname );
                        
                   } else {
                      continue;
                   }
            }
            closedir(dir);
    } else {
            perror("");
            return 5;
 }
    sleep(3);
  }
  
  exit(EXIT_SUCCESS);
}
