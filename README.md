# SoalShift_modul2_F04
Jawaban soal shift Sisop modul 2


# Soal 1:
Pada soal 1 kita disuruh memrogram otomatis kalau ada file dengan ekstensi .png diubah menjadi _grey.png 
const char *get_filename_ext(const char *filename) {
    const char *dot = strrchr(filename, '.');
    if(!dot || dot == filename) return "";
    return dot + 1;
}

Fungsi di atas digunakan agar ekstensi diubah menjadi string biasa.
Karena harus otomatis maka saya membuat daemon yang sudah ada di modul 2. Isi di daemon :
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
                
Kodingan di atas digunakan untuk mengambil file .png

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
Kodingan di atas mengambil string sebelum .png lalu ditambahkan _grey.png dan pindahkan filenya ke /home/[user]/modul2/gambar/
                        

# Soal 2:

# Soal 3:
Pada soal 3 kita disuruh untuk mengesktrak file campur2.zip lalu membuat file daftar.txt yang berisi daftar file yang berekstensi .txt
Dengan catatan : Memiliki fork dan exec, minimal ada 3 exec, ada pipe, file daftar.txt
Pertama kami membuat 3 child 1 parent.

execlp("unzip", "unzip", "campur2.zip", NULL);
child ke 3 kami berisi unzip file

sleep(2); 
execlp("touch", "touch", "daftar.txt", NULL);
child ke 2 kami disleep dulu menunggu child 3 selesai lalu membuat file daftar.txt

sleep(3);       
dup2(fd[1], 1);
execlp("ls", "ls", "campur2", NULL);
child ke 1 kami ngepipe ke parent dan melihat folder campur2

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
parent kami digunakan untuk mengopi daftar file .txt ke daftar.txt. Program di atas dijalankan setelah semua child selesai.
# Soal 4:

# Soal 5:
