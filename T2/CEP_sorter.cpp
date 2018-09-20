#include<stdlib.h>
#include<stdio.h>

typedef unsigned short int ltNatural;
typedef unsigned long int bigNatural;
typedef unsigned int natural;

#define LINE_SIZE 300
#define CEP_SIZE 8

struct address{

	char logradouro[72];
	char bairro[72];
	char cidade[72];
	char uf[72];
	char sigla[2];
	char cep[8];
	char lixo[2];
};


void redefineCEPCHAR( char*& oldOne, address& ad){

	if( oldOne == NULL ){

		oldOne = new char[CEP_SIZE+1];
		oldOne[CEP_SIZE] = 0;
	}

	char* aux = ad.cep;

	for( ltNatural i = 0; i < CEP_SIZE; i++)
		oldOne[i] = aux[i];

return ;}


int main(int argc, char ** argv){

	if( argc == 4 ){

		FILE * originalFile1 = fopen(argv[1],"r");
		FILE * originalFile2 = fopen(argv[2],"r");

		if( originalFile2 == NULL || originalFile1 == NULL ){

			fprintf(stderr,"\nErro! Falha ao tentar abrir %s ou %s para leitura.\n\n",argv[1],argv[2]);
			exit(1);
		}

		FILE * NewFile = fopen(argv[3],"w");

		if( NewFile == NULL ){

			fprintf(stderr,"\nErro! Falha ao tentar abrir %s para escrita.\n\n",argv[3]);
			exit(1);
		}

		address temp1, temp2;	//Declaração dos structs...

		char * CEPCHAR1 = NULL;
		char * CEPCHAR2 = NULL;

		natural Num1 = fread(&temp1,sizeof(address),1,originalFile1);
		natural Num2 = fread(&temp2,sizeof(address),1,originalFile2);

		do{

			if( Num1 != 0 && Num2 != 0 ){

				redefineCEPCHAR(CEPCHAR1,temp1);
				redefineCEPCHAR(CEPCHAR2,temp2);

				if( atoi(CEPCHAR1) <= atoi(CEPCHAR2) ){

					fwrite(&temp1,sizeof(address),1,NewFile);
					Num1 = fread(&temp1,sizeof(address),1,originalFile1);

				}else{

					fwrite(&temp2,sizeof(address),1,NewFile);
					Num2 = fread(&temp2,sizeof(address),1,originalFile2);
				}

			}else if( Num1 != 0 ){

				fwrite(&temp1,sizeof(address),1,NewFile);
				Num1 = fread(&temp1,sizeof(address),1,originalFile1);

			}else if( Num2 != 0 ){

				fwrite(&temp2,sizeof(address),1,NewFile);
				Num2 = fread(&temp2,sizeof(address),1,originalFile2);

			}else
				break;

		}while( true );

		delete[] CEPCHAR1;
		delete[] CEPCHAR2;

		fclose(originalFile1);
		fclose(originalFile2);
		fclose(NewFile);
	}

return 0;}
