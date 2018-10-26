#include<type_traits>
using std::is_arithmetic;
using std::is_pointer;

#include<cstdlib>

template< class T> void shuffle( T * const & array, const size_t range) noexcept(0){

	static_assert( is_arithmetic<T>::value || is_pointer<T>::value ,"\n\n\tUse essa função apenas para vetores de valor aritimético ou ponteiros de qualquer tipo...\n\n");

	if( array == nullptr )
		throw "null pointer exception na função shuffle!!";

	T aux;

	for( size_t i = 0, r; i != range; ++i){

		r = rand() % range;

		aux = array[r];

		array[r] = array[i];
		array[i] = aux;
	}

return ;}

//################################
//################################
//################################
#include"Registro.h"

#include<cstdlib>
using std::strtoul;
using std::srand;
using std::rand;
using std::exit;

#include<string>

using std::to_string;
using std::string;


int main( int argc, char ** argv){

	using bigNatural = unsigned long int;
	using natural = unsigned int;

	srand(time(0));

	try{

		if( argc != 2 )
			throw "deve-se chamar esse programa com um parametro, que é o número de subdivisões para o arquivo original.";

		FILE * original = fopen("cep_ordenado.dat","rb");

		if( original == nullptr )
			throw "arquivo cep_ordenado.dat não pode ser aberto para leitura.";

		const natural nb_split = strtoul(argv[1],nullptr,10);

		FILE ** splt_files = new FILE * [nb_split];

		{
			static constexpr char _NFBN_ [] = "splitters/cep_desordenado_part_";	//_NEW_FILES_BASE_NAME_
			string names = _NFBN_;

			for( natural i = 0; i != nb_split; ++i){

				splt_files[i] = fopen( ( names += to_string(i) += ".txt" ).c_str() ,"wb");
				names.erase(sizeof(_NFBN_)-1);

				if( splt_files[i] == nullptr )
					throw "um dos arquivos de partes não pode ser aberto para escrita no diretorio splitteds/.";
			}
		}
		{
			const size_t length = 1000;	//Arbitrário...
			bigNatural qtd;

			Registro ** const rgtrs = new Registro * [length];

			for( natural i = 0; i != length; ++i)
				rgtrs[i] = new Registro;

			while( true ){

				qtd = rgtrs[0]->fill_reading_from(original);

				for( natural i = 1; i != length; ++i)
					qtd += rgtrs[i]->fill_reading_from(original);

				if( !qtd )
					break;

				shuffle(rgtrs,length);

				for( natural i = 0; i != length && qtd != 0; ++i)
					qtd -= rgtrs[i]->dump_writing_in(splt_files[ rand() % nb_split ]);	//Writes on a randon file!!!

				if( qtd != 0 )
					throw "fatal execution error in the file reading and writes...";
			}

			for( natural i = 0; i != length; ++i)
				delete rgtrs[i];

			delete[] rgtrs;	
		}

		fclose(original);

		for( natural i = 0; i != nb_split; ++i)
			fclose(splt_files[i]);

		delete[] splt_files;

	}catch( const char * const dscrpt){

		fprintf(stderr,"\nHouve uma exceção na execução do programa, explicação: %s\n\nPrograma se encerrando precocemente...\n\n",dscrpt);
		exit(-1);

	}catch(...){

		fprintf(stderr,"\nHouve um erro inesperado durante a execução.\n\nPrograma se encerrando precocemente...\n\n");
		exit(-2);
	}

return 0;}
