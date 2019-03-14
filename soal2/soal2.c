#include <sys/types.h>
#include <sys/stat.h>
#include <stdio.h>
#include <stdlib.h>
#include <fcntl.h>
#include <errno.h>
#include <unistd.h>
#include <syslog.h>
#include <string.h>
#include <pwd.h>
#include <grp.h>

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

	while(1){
		FILE *elen;
		elen=fopen("/home/mlr/hatiku/elen.ku", "r");
		if(elen){
			struct stat info;
			stat("/home/mlr/hatiku/elen.ku", &info);
			struct passwd *pw = getpwuid(info.st_uid);
			struct group *gr = getgrgid(info.st_gid);
			if(strcmp(pw->pw_name, "www-data")==0 && strcmp(gr->gr_name,"www-data")==0){
				chmod("/home/mlr/hatiku/elen.ku", 0777);
				fclose(elen);
				remove("/home/mlr/hatiku/elen.ku");
			}
		}
		sleep(3);
	}  
	exit(EXIT_SUCCESS);
}
