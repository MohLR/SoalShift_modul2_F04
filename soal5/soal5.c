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
	close(STDOUT_FILENO);
	close(STDERR_FILENO);

	int a=0;
	time_t waktu=0;
	char path[100];
	while(1){
		a++;
		time_t rawtime;
		rawtime=time(&rawtime);
		if(waktu==0 || rawtime-waktu==1800){
			waktu=rawtime;
			char date[20];
			strftime(date, sizeof(date), "%d:%m:%Y-%H:%M", localtime(&rawtime));
			memset(path, 0, sizeof(path));
			sprintf(path, "/home/mlr/log/");
			strcat(path, date);
			mkdir(path, 0755);
		}
		char full[1000000];
		sprintf(full, "%s", path);
		strcat(full, "/log");
		char b[100000];
		sprintf(b, "%d", a);
		strcat(full, b);
		strcat(full, ".log");
		FILE *syslog;
		FILE *log;
		syslog=fopen("/var/log/syslog", "r");
		log=fopen(full, "w");
		do{
			char ch=fgetc(syslog);
			if(ch==EOF) break;
			else fprintf(log, "%c", ch);
		} while(1);
		fclose(syslog);
		fclose(log);
		sleep(60);
	}  
	exit(EXIT_SUCCESS);
}
