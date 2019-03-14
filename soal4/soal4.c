#include <sys/types.h>
#include <sys/stat.h>
#include <stdio.h>
#include <stdlib.h>
#include <fcntl.h>
#include <errno.h>
#include <unistd.h>
#include <syslog.h>
#include <string.h>
#include <time.h>

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
	//close(STDOUT_FILENO);
	close(STDERR_FILENO);

	int a=0;
	while(1){
		struct stat info;
		stat("/home/mlr/Documents/makanan/makan_enak.txt", &info);
		time_t rawtime;
		rawtime=time(&rawtime);
		if(rawtime-info.st_atime<=30){
			FILE *makan;
			a++;
			char path[1000000]="/home/mlr/Documents/makanan/makan_sehat";
			char b[100000];
			sprintf(b, "%d", a);
			strcat(path, b);
			strcat(path, ".txt");
			makan=fopen(path, "w");
			fprintf(makan, "Ingat Elen, kamu harus diet!");
			fclose(makan);
		}
		sleep(5);
	}  
	exit(EXIT_SUCCESS);
}
