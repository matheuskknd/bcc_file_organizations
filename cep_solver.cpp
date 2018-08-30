#include<stdio.h>
#include<stdlib.h>
#include<string.h>
#include<iostream>
using namespace std;
typedef unsigned int natural;

#pragma package(1)	//Diz o tamanho do alinhamento em memória, para fins de otimização de processamento.
#define CEPSIZE 8

struct Endereco{

	char logradouro[72];
	char bairro[72];
	char cidade[72];
	char uf[72];
	char sigla[2];
	char cep[8];
	char lixo[2];
};


int main(int argc, char ** argv){

	if( argc != 3 )
		printf("Use: <file.dat> <cep to compare>\n");

	else{

		FILE * my_file = fopen(argv[1],"r");

		Endereco my_adress;
		memset(&my_adress,0,sizeof(Endereco));

		const natural seekedCEP = atoi(argv[2]);

		fseek(my_file,0,SEEK_END);
		natural low = 0, mid = 0, high = ftell(my_file)/sizeof(Endereco);
		rewind(my_file);

		char * CEP_TEST = new char [CEPSIZE];
		bool achou = false;

		natural complexity = 0;
		natural cep_testing;

		do{
			complexity++;
			mid = (low+high)/2;

			fseek(my_file,290+300*mid,SEEK_SET);
			fread(CEP_TEST,sizeof(char),CEPSIZE,my_file);

			cep_testing = atoi(CEP_TEST);

			if( seekedCEP < cep_testing )
				high = mid-1;

			else if( seekedCEP > cep_testing )
				low = mid+1;

			else{
				achou = true;
				break;
			}

		}while( low < high );

		if( achou ){

			fseek(my_file,300*mid,SEEK_SET);			//Move o cursor pra linha de interesse.
			fread(&my_adress,sizeof(char),72*4,my_file);

			cout << "Em " << complexity << " interações encontrou:\n";

			printf("\nLogradouro: %.72s",my_adress.logradouro);
			printf("\nBairro:\t%.72s",my_adress.bairro);
			printf("\nCidade:\t%.72s",my_adress.cidade);
			printf("\nUF:\t%.72s",my_adress.uf);

		}else
			cout << "Não achou nada!!! Em " << complexity << " interações.";

		cout << "\n\n";

		delete[] CEP_TEST;
	}

return 0;}
