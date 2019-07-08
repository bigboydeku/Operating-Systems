#include "types.h"
#include "user.h"
#include "stdio.h"
#include "fcntl.h"

#define true 1
#define false 0

#define bufferSize 512

FILE * mystdout = &(FILE){1, O_RDWR};

char buffer[bufferSize];
int bufferPointer = 0;

static void putc(const FILE * file, char c) {
	buffer[bufferPointer] = c;
	bufferPointer++;
	
	if (bufferPointer == bufferSize)
		flushBuff(file);
}

static void printint(const FILE * file , int xx, int base, int sgn) {
  static char digits[] = "0123456789ABCDEF";
  char buf[16];
  int i, neg;
  uint x;

  neg = 0;
  if(sgn && xx < 0){
    neg = 1;
    x = -xx;
  } else {
    x = xx;
  }

  i = 0;
  do{
    buf[i++] = digits[x % base];
  }while((x /= base) != 0);
  if(neg)
    buf[i++] = '-';

  while(--i >= 0)
    putc(file, buf[i]);
}

// Print to the given fd. Only understands %d, %x, %p, %s.
void fprintf(const FILE * file, const char *fmt, ...) {
  char *s;
  int c, i, state = 0;
  uint *ap = (uint*)(void*)&fmt + 1; //refers to all variables after the string to be printed
  
  for(i = 0; fmt[i]; i++){
    c = fmt[i];
    if(state == 0){
      if(c == '%'){
        state = '%';
      } else {
        putc(file, c);
      }
    } else if(state == '%'){
      if(c == 'd'){
        printint(file, *ap, 10, true); //print int
        ap++; //next variable
      } else if(c == 'x' || c == 'p'){
        printint(file, *ap, 16, false);
        ap++;
      } else if(c == 's'){
        s = (char*)*ap;
        ap++;
        if(s == 0)
          s = "(null)";
        while(*s != 0){
          putc(file, *s);
          s++;
        }
      } else if(c == 'c'){
        putc(file, *ap);
        ap++;
      } else if(c == '%'){
        putc(file, c);
      } else {
        // Unknown % sequence.  Print it to draw attention.
        putc(file, '%');
        putc(file, c);
      }
      state = 0;
    }
  }
}

// Print to the given fd. Only understands %d, %x, %p, %s.
void myprintf(const char *fmt, ...) {
  char *s;
  int c, i, state = 0;
  uint *ap = (uint*)(void*)&fmt + 1; //refers to all variables after the string to be printed
  
  for(i = 0; fmt[i]; i++){
    c = fmt[i];
    if(state == 0){
      if(c == '%'){
        state = '%';
      } else {
        putc(mystdout, c);
      }
    } else if(state == '%'){
      if(c == 'd'){
        printint(mystdout, *ap, 10, true); //print int
        ap++; //next variable
      } else if(c == 'x' || c == 'p'){
        printint(mystdout, *ap, 16, false);
        ap++;
      } else if(c == 's'){
        s = (char*)*ap;
        ap++;
        if(s == 0)
          s = "(null)";
        while(*s != 0){
          putc(mystdout, *s);
          s++;
        }
      } else if(c == 'c'){
        putc(mystdout, *ap);
        ap++;
      } else if(c == '%'){
        putc(mystdout, c);
      } else {
        // Unknown % sequence.  Print it to draw attention.
        putc(mystdout, '%');
        putc(mystdout, c);
      }
      state = 0;
    }
  }
}


/*
* Opens the file, only supports read and write.
*/
FILE * fopen(const char *filename, const char *mode) {
	FILE * file = (FILE *) malloc(sizeof(FILE)); //allocate memory for saving file info
	
	if (mode[0] == 'r') {
		file->fd = open(filename, O_RDONLY);
	}
	else if(mode[0] == 'w') {
		file->fd = open(filename, O_WRONLY | O_CREATE);
	}
	
	for (int i = 0 ; i < bufferSize; i++) {
		buffer[i] = 0;
	}
	bufferPointer = 0;
	
	return file;
}


/*
* Closes the file by flushing the buffer and freeing the used memory
*/
void fclose(const FILE* file) {
	flushBuff(file);
	free((FILE *) file);
	
}

/*writes to the file descriptor, clears the buffer, and restores pointer
* Input: the file information
*/
void flushBuff(const FILE* file) {
	write(file->fd, buffer, bufferPointer);
	
	for (int i = 0 ; i < bufferSize; i++) {
		buffer[i] = 0;
	}
	bufferPointer = 0;
}



