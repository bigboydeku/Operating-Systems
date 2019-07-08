typedef struct File {
	int fd;  //descriptor
	int mode; 
	int bp; //buffer pointer for checking size
} FILE;

FILE * mystdout;

void fprintf(const FILE * file, const char *fmt, ...);
void myprintf(const char *fmt, ...);
FILE * fopen(const char *filename, const char *mode);
void fclose(const FILE* file);
void flushBuff(const FILE* filename);