#include <stdio.h>
#include <stdlib.h>
#include <string.h>

unsigned char *bufor1;
unsigned char *bufor2;
unsigned char *bufor3;

void main(int argc, unsigned char *argv[]) {
int dummy; // mode 0 - bin / 1 - asm
unsigned int bufsize1, bufsize2, bufsize3, i, j;
char c;
unsigned char *filename;
int filename_l;
char *filename_ptr;

char heksy[2];

FILE *srcfile_1;
FILE *srcfile_2;
FILE *dstfile;

  printf("\nAtari XL/XE to Atari 7800 font coverter\n");
  printf("tEDDYbOAR (2015.01.09)\n\n");

  if(argc>2){
    if (argc==4){
// open source file
      if ((srcfile_1 = fopen(argv[2],"rb")) == NULL) {
        printf("ERROR: unable to open file %s\n",argv[1]);
	     exit(1);
      }
// alloc mem for bufer
      if ((bufor1 = (unsigned char *) malloc(sizeof(unsigned char) * 1024)) == NULL) {
        printf("ERROR: unable to allocate memory");
	    exit(1);
      }
// read file into buffer 
      fread(bufor1, 1024,1, srcfile_1);
// close source file
      fclose(srcfile_1);
// open source file
      if ((srcfile_2 = fopen(argv[3],"rb")) == NULL) {
        printf("ERROR: unable to open file %s\n",argv[1]);
	     exit(1);
      }
// alloc mem for bufer
      if ((bufor2 = (unsigned char *) malloc(sizeof(unsigned char) * 1024)) == NULL) {
        printf("ERROR: unable to allocate memory");
	    exit(1);
      }
// read file into buffer 
      fread(bufor2, 1024,1, srcfile_2);
// close source file
      fclose(srcfile_2);
// alloc mem for bufer
      if ((bufor3 = (unsigned char *) malloc(sizeof(unsigned char) * 2048)) == NULL) {
        printf("ERROR: unable to allocate memory");
	    exit(1);
      }
      for (i=0; i < 128; i++){
        bufor3[256*7+i] = bufor1[8*i];
        bufor3[256*6+i] = bufor1[8*i+1];
        bufor3[256*5+i] = bufor1[8*i+2];
        bufor3[256*4+i] = bufor1[8*i+3];
        bufor3[256*3+i] = bufor1[8*i+4];
        bufor3[256*2+i] = bufor1[8*i+5];
        bufor3[256*1+i] = bufor1[8*i+6];
        bufor3[256*0+i] = bufor1[8*i+7];
// inversed characters
        bufor3[256*7+i+128] = bufor2[8*i];
        bufor3[256*6+i+128] = bufor2[8*i+1];
        bufor3[256*5+i+128] = bufor2[8*i+2];
        bufor3[256*4+i+128] = bufor2[8*i+3];
        bufor3[256*3+i+128] = bufor2[8*i+4];
        bufor3[256*2+i+128] = bufor2[8*i+5];
        bufor3[256*1+i+128] = bufor2[8*i+6];
        bufor3[256*0+i+128] = bufor2[8*i+7];
      }
      filename = argv[2];
      filename_ptr = strstr(filename,".");

      dummy = *argv[1];
      switch (dummy){
        case 'b':
          strncpy (filename_ptr, ".bin",4);
// open destinantion file           
          if ((dstfile = fopen(argv[2],"wb")) == NULL) {
            printf("ERROR: unable to open file %s\n",argv[1]);
	           exit(1);
          }
          fwrite(bufor3,2048,1,dstfile);    
          break;
        case 'a':
          strncpy (filename_ptr, ".asm",4);
          if ((dstfile = fopen(argv[2],"wb")) == NULL) {
            printf("ERROR: unable to open file %s\n",argv[1]);
	          exit(1);
            }
          //*****
          j = 0;
          for (i=0; i<2048; i++){
            if (j == 0) {
              fputs("     .byte ", dstfile);                    
              }
            fputs("$", dstfile);
            sprintf(heksy,"%02x",bufor3[i]);
            fputs(heksy,dstfile);
            if (j!=7) {
              fputs(", ",dstfile);
              j++;
            }
            else {
              fputs("\n",dstfile);
              j = 0;
            }
          
          }
      }
      
      fclose(dstfile);

      printf("\nFile %s created.\n", filename);
      free(bufor1);
      free(bufor2);
      free(bufor3);

    }
    else if (argc==3){
// open source file
      if ((srcfile_1 = fopen(argv[2],"r")) == NULL) {
        printf("ERROR: unable to open file %s\n",argv[1]);
	     exit(1);
      }
// alloc mem for bufer
      if ((bufor1 = (unsigned char *) malloc(sizeof(unsigned char) * 1024)) == NULL) {
        printf("ERROR: unable to allocate memory");
	    exit(1);
      }
// read file into buffer 
      fread(bufor1, 1024,1, srcfile_1);
// close source file
      fclose(srcfile_1);
// alloc mem for bufer
      if ((bufor3 = (unsigned char *) malloc(sizeof(unsigned char) * 2048)) == NULL) {
        printf("ERROR: unable to allocate memory");
	    exit(1);
      }
      for (i=0; i < 128; i++){
        bufor3[256*7+i] = bufor1[8*i];
        bufor3[256*6+i] = bufor1[8*i+1];
        bufor3[256*5+i] = bufor1[8*i+2];
        bufor3[256*4+i] = bufor1[8*i+3];
        bufor3[256*3+i] = bufor1[8*i+4];
        bufor3[256*2+i] = bufor1[8*i+5];
        bufor3[256*1+i] = bufor1[8*i+6];
        bufor3[256*0+i] = bufor1[8*i+7];
// inversed characters
        bufor3[256*7+i+128] = bufor1[8*i] ^ 0xff;
        bufor3[256*6+i+128] = bufor1[8*i+1] ^ 0xff;
        bufor3[256*5+i+128] = bufor1[8*i+2] ^ 0xff;
        bufor3[256*4+i+128] = bufor1[8*i+3] ^ 0xff;
        bufor3[256*3+i+128] = bufor1[8*i+4] ^ 0xff;
        bufor3[256*2+i+128] = bufor1[8*i+5] ^ 0xff;
        bufor3[256*1+i+128] = bufor1[8*i+6] ^ 0xff;
        bufor3[256*0+i+128] = bufor1[8*i+7] ^ 0xff;
      }
      filename = argv[2];
      filename_ptr = strstr(filename,".");

      dummy = *argv[1];
      switch (dummy){
        case 'b':
          strncpy (filename_ptr, ".bin",4);
// open destinantion file           
          if ((dstfile = fopen(argv[2],"wb")) == NULL) {
            printf("ERROR: unable to open file %s\n",argv[1]);
	           exit(1);
          }
          fwrite(bufor3,2048,1,dstfile);    
          break;
        case 'a':
          strncpy (filename_ptr, ".asm",4);
          if ((dstfile = fopen(argv[2],"wb")) == NULL) {
            printf("ERROR: unable to open file %s\n",argv[1]);
	          exit(1);
            }
          //*****
          j = 0;
          for (i=0; i<2048; i++){
            if (j == 0) {
              fputs("     .byte ", dstfile);                    
              }
            fputs("$", dstfile);
            sprintf(heksy,"%02x",bufor3[i]);
            fputs(heksy,dstfile);
            if (j!=7) {
              fputs(", ",dstfile);
              j++;
            }
            else {
              fputs("\n",dstfile);
              j = 0;
            }
          
          }
      }
      
      fclose(dstfile);

      printf("\nFile %s created.\n", filename);
      free(bufor1);
      free(bufor3);
    }
 }
 else {
      printf("Usage: fnt-conv.exe [options] filename1 [filename2]\n\n");
      printf("Options:\n");
      printf("         asm      = output asm include file\n");
      printf("         bin      = output binary file\n");
      
 }
} 