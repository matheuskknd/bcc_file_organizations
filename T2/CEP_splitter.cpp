#include<stdlib.h>
#include<stdio.h>
#include<time.h>

typedef unsigned short int ltNatural;
typedef unsigned long int bigNatural;
typedef unsigned int natural;

#define LINE_SIZE 300
#define CEP_SIZE 8

int main(int argc, char ** argv){

	if( argc == 4 ){

		srand(time(NULL)+atoi(argv[2])*argc/50);

		FILE * originalFile = fopen(argv[1],"r");

		if( originalFile == NULL ){

			fprintf(stderr,"\nErro! Falha ao tentar abrir %s para leitura.\n\n",argv[1]);
			exit(1);
		}

		FILE * tempFile1 = fopen(argv[2],"w");
		FILE * tempFile2 = fopen(argv[3],"w");

		if( tempFile2 == NULL || tempFile1 == NULL ){

			fprintf(stderr,"\nErro! Falha ao tentar abrir %s ou %s para escrita.\n\n",argv[2],argv[3]);
			exit(1);
		}

		char buffer[LINE_SIZE];

		natural NbRead = fread(buffer,sizeof(char),LINE_SIZE,originalFile);

		while( NbRead != 0 ){

			if( rand() % 2 )
				fwrite(buffer,sizeof(char),LINE_SIZE,tempFile1);
			else
				fwrite(buffer,sizeof(char),LINE_SIZE,tempFile2);

			NbRead = fread(buffer,sizeof(char),LINE_SIZE,originalFile);
		}

		fclose(originalFile);
		fclose(tempFile1);
		fclose(tempFile2);
	}

return 0;}
