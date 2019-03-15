#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <signal.h>

int main(){
	char a[100];
	FILE *p=popen("pidof soal5", "r");
	fgets(a, 100, p);
	pid_t pid=strtoul(a, NULL, 10);
	if(pid!=0){
		kill(pid, SIGTERM);
		printf("Program soal5 berhasil dihentikan\n");
	}
	else printf("Tidak ada program yang dihentikan\n");
	pclose(p);
	return 0;
}
