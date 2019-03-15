# SoalShift_modul2_F04
Jawaban soal shift Sisop modul 2


## Soal 1:
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
                        

## Soal 2:
Pada soal 2 kita disuruh untuk menghapus semua file dengan nama elen.ku pada directory hatiku, tetapi dengan syarat owner dan group dari elen.ku adalah www-data dan mengubah mode dari elen.ku menjadi 777.

Pertama, kami membuat suatu program daemon, program ini mengambil dari template yang sudah ada pada modul 2.

Isi dari progrmanya pada awalnya kita mengecek apakah ada file dengan nama elen.ku pada directory hatiku dengan potongan berikut
```
FILE *elen;
elen=fopen("/home/mlr/hatiku/elen.ku", "r");
if(elen){
```
ketika ada file bernama elen.ku maka program dalam if akan berjalan, tetapi jika tidak ada, program akan menunngu 3 detik sebelum mengecek lagi.

lalu, semua info yang ada dari file elen.ku disimpan pada suatu variable dengan nama info. berikut potongan kodenya
```
struct stat info;
stat("/home/mlr/hatiku/elen.ku", &info);
```
lalu, kita ambil owner dan group dari elen.ku dengan uid dan gid yang ada pada info. berikut potongan kodenya
```
struct passwd *pw = getpwuid(info.st_uid);
struct group *gr = getgrgid(info.st_gid);
```
setelah mendapat owner dan group dari elen.ku dicek, apakah nama owner dan nama groupnya www-data dengan strcmp. berikut potongan kodenya
```
if(strcmp(pw->pw_name, "www-data")==0 && strcmp(gr->gr_name,"www-data")==0)
```
jika memang owner dan groupnya bernama www-data, maka mode dari elen.ku akan dirubah menjadi 777 dan filenya akan dihapus. berikut potongan kodenya
```
chmod("/home/mlr/hatiku/elen.ku", 0777);
fclose(elen);
remove("/home/mlr/hatiku/elen.ku");
```

## Soal 3:
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
## Soal 4:
Pada soal 4 kita disuruh untuk membuat file makan_sehat#.txt, dengan # adalah bilangan bulat, pada /home/[user]/Documents/makanan ketika file makan_enak.txt dibuka setidaknya 30 detik yang lalu.

Pertama, kami membuat program daemon dengan menyalin template yang ada pada modul 2.

Isi dari programnya adalah pertama, kita membuat suatu variable dengan tipe data integer sebelum masuk ke while, sehingga variable, tersebut selama program berjalan bisa disimpan isi terakhirnya.

lalu, dalam while, kita simpan info file dari makan_enak.txt pada suatu variable. berikut potongan kodenya
```
struct stat info;
stat("/home/mlr/Documents/makanan/makan_enak.txt", &info);
```
lalu kita ambil waktu saat ini dan bandingkan dengan waktu terakhir file makan_enak.txt dibuka, jika kurang atau sama dengan 30 maka program akan jalan, jika tidak program akan menunggu 5 detik selanjutnya sebelum pengecekan selanjutnya. berikut potongan kodenya
```
time_t rawtime;
rawtime=time(&rawtime);
if(rawtime-info.st_atime<=30)
```
lalu, kita simpan path pada suatu variable array dengan tipe data char.
lalu, variable integer yang kita inisialisasi sebelum while kita ubah menjadi string baru disambung dengan path tadi lalu diakhiri dengan .txt.
dan akhirnya file dengan path yang disimpan tadi dibuat dan diisi dengan "Ingat Elen, kamu harus diet!".
berikut potongan kodenya
```
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
```

## Soal 5:
Pada soal 5, kita disuruh untuk mencatat log pada syslog setiap menit ke /home/[user]/log/[dd:MM:yyyy-hh:mm]/log#.log, dengan folder [dd:MM:yyyy-hh:mm] akan dibuat per 30 menit, log tadi dimasukkan pada folder tersebut, dan # adalah bilangan bulat.

Pertama, kami membuat program daemon dengan menyalin template dari modul 2.

Isinya adalah, sebelum while inisialisasi suatu variable integer dengan angka 0, variable time_t dengan angka 0, dan suatu variable char array. berikut potongan kodenya
```
int a=0;
time_t waktu=0;
char path[100];
```
setelah itu, setiap program jalan, variable integer tadi akan di increment.
lalu inisialisasi variable time_t untuk menyimpan waktu sekarang untuk dibandingkan dengan waktu yang tadi diinisialisasi untuk mengetahui apakah sudah 30 menit. berikut potongan kodenya
```
a++;
time_t rawtime;
rawtime=time(&rawtime);
if(waktu==0 || rawtime-waktu==1800)
```
jika sudah 30 menit atau program baru saja jalan, maka isi dari variable time_t yang diinisialisasi sebelum masuk while akan diisi dengan waktu sekarang.
lalu, waktu sekarang akan dirubah menjadi format waktu lokal dan memasukkannya pada suatu variable untuk dibuat foldernya. berikut potongan kodenya
```
waktu=rawtime;
char date[20];
strftime(date, sizeof(date), "%d:%m:%Y-%H:%M", localtime(&rawtime));
memset(path, 0, sizeof(path));
sprintf(path, "/home/mlr/log/");
strcat(path, date);
mkdir(path, 0755);
```
lalu, kita masukkan path tadi ke suatu variable untuk ditambah lagi dengan log#.log.
setelah itu, kita membuka file syslog untuk dibaca dan membuat file baru yang isinya sama dengan syslog (atau mungkin bisa dikatakan meng-copy and paste isi syslog ke file baru). berikut potongan kodenya
```
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
```
