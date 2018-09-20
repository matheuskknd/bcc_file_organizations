#include<stdlib.h>
#include<stdio.h>

typedef unsigned int natural;

int main(int argc, char ** argv){

	if( argc == 1 ){

		FILE * file1 = fopen("CEPS/cep_ordenado.dat","r");
		FILE * file2 = fopen("CEPS/NOVO_cep_ordenado.dat","r");

		if( file2 == NULL || file1 == NULL ){

			fprintf(stderr,"\nErro! Falha ao tentar abrir 1 ou 2 para leitura.\n\n");
			exit(1);
		}


		natural t1, t2;
		char teste1, teste2;

		while( (t1= fread(&teste1,sizeof(char),1,file1)) | (t2 = fread(&teste2,sizeof(char),1,file2)) )
			if( teste1 != teste2 || t1 != t2 ){

				fprintf(stderr,"\nErro! Detectado diferença de arquivos na verificação Byte a byte.\n\n");
				exit(0);
			}

		printf("\nOs dois arquivos são idênticos!!!.\n\n");

		fclose(file2);
		fclose(file1);
	}

return 0;}
