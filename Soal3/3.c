
#include <sys/wait.h>
#include <sys/types.h>
#include <unistd.h>
#include <stdlib.h>
#include <stdio.h>
#include <string.h> 
  
 
int main() 
{ 
  int pid, pid1, pid2;
  int status;
  int fd[2];
  int buff;
  pipe(fd); 

    pid = fork(); 
    if (pid == 0) { 
  
        
        sleep(3); 
  
        
        dup2(fd[1], 1);
	execlp("ls", "ls", "campur2", NULL);
    } 
  
    else { 
        pid1 = fork(); 
        if (pid1 == 0) { 
            sleep(2); 
            execlp("touch", "touch", "daftar.txt", NULL);
        } 
        else { 
            pid2 = fork(); 
            if (pid2 == 0) { 
                execlp("unzip", "unzip", "campur2.zip", NULL);
            } 
            else { 
                 
                sleep(3); 
                char buff [1000];

	close(fd[1]);
	FILE* temp = fdopen(fd[0], "r");
	FILE *daftar = fopen("daftar.txt", "w");
	int i=0;
	while (fgets(buff, sizeof(buff), temp) != NULL) {
	if (strstr(&buff[strlen(buff)-5], ".txt") != NULL)
	fprintf(daftar, "%s", buff);
	}
fclose(daftar); 
            } 
        } 
    } 
  
} 


