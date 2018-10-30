#include<type_traits>
using std::is_arithmetic;
using std::is_pointer;

template< class T> inline void swap( T& o1, T& o2){

	static_assert( is_arithmetic<T>::value || is_pointer<T>::value,"\n\n\tThe type to be swapped must to be arithmetic or a pointer.\n\n");

	T aux = o1;

	o1 = o2;
	o2 = aux;

return ;}

//################################
#include"../registro/Registro.h"

#include<cstdlib>
using std::exit;

#include<iostream>
using std::cout;


int main( const int argc, char ** argv){

	try{

		if( argc < 2 )
			throw "deve-se chamar esse programa com um parametro, que é o arquivo de CEPs a ser checado.";

		FILE * const file = fopen(argv[1],"rb");

		if( file == nullptr )
			throw "o arquivo requisitado não pode ser aberto para leitura.";

		Registro * r1 = new Registro(file);
		Registro * r2 = new Registro(file);

		bool sorted=true;
		size_t qtd;

		do{
			if( *r1 > *r2 ){

				sorted = false;
				break;
			}

			qtd = r1->fill_reading_from(file);
			swap(r1,r2);

		}while( qtd != 0 );

		if( !sorted )
			cout << "Este arquivo não está com todos os CEPs ordenados, foi encontrada um erro em:\n" << *r1 << *r2;
		else
			cout << "Este arquivo está perfeitamente ordenado por CEPs.\n\n";

		delete r1;
		delete r2;

		fclose(file);

	}catch( const char * const dscrpt){

		fprintf(stderr,"\nHouve uma exceção na execução do programa, explicação: %s\n\nPrograma se encerrando precocemente...\n\n",dscrpt);
		exit(-1);
	}

return 0;}
