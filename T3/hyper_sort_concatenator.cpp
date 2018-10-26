#include"Registro.h"

#include<iostream>
using std::cout;

#include<cstdlib>
using std::exit;

#include<string>

using std::to_string;
using std::string;

#define LIMITE_MEMORIA 58428800	//50 MB
using natural = unsigned int;

#include<iostream>
using std::cout;


void abrir_arquivos( FILE ** const & old_files, const size_t NbOlds, FILE ** const & new_files, const size_t NbNews, const char * const * const & argv) noexcept(0);
void ordenar_salvar( FILE ** const & old_files, const size_t NbOlds, FILE ** const & new_files, const size_t NbNews) noexcept(0);
void merge_concatenando( FILE ** const & new_files, const size_t index, const size_t length) noexcept(0);


int main( int argc, char ** argv){

	const size_t N = argc - 1;
	const size_t length = 2*N - 1;
	const size_t penult = length-1;

	try{

		//Inicio: verificação de parametros, e instanciação das variaveis mais visíveis...

		if( N < 2 )
			throw "deve-se chamar esse programa com no mínimo dois parametros, que são os endereços completos das subdivisões do arquivo original de CEPs.";

		FILE ** const prcs_files = new FILE * [length];
		FILE ** const old_files = new FILE * [N];

		//Parte 2: abrindo os arquivos apenas de leitura do ourto programa, criando os nomes para os novos arquivos...

		abrir_arquivos(old_files,N,prcs_files,length,argv);

		//Copiando para memória e ordenando para depois levar de volta ao disco...

		ordenar_salvar(old_files,N,prcs_files,length);

		for( size_t i = 0; i != N; ++i)
			fclose(old_files[i]);	//Read only files are closed here...

		delete[] old_files;

		//Fazendo merge dos arquivos concatenando dos menores para os maiores recursivamente...

		merge_concatenando(prcs_files,N,length);

		//Apagando resíduos...

		for( size_t i = 0; i != length; ++i)
			fclose(prcs_files[i]);

		delete[] prcs_files;

	}catch( const char * const dscrpt){

		fprintf(stderr,"\nHouve uma exceção na execução do programa, explicação: %s\n\nPrograma se encerrando precocemente...\n\n",dscrpt);
		exit(-1);

	}catch(...){

		fprintf(stderr,"\nHouve um erro inesperado durante a execução.\n\nPrograma se encerrando precocemente...\n\n");
		exit(-2);
	}

return 0;}


void abrir_arquivos( FILE ** const & old_files, const size_t NbOlds, FILE ** const & new_files, const size_t NbNews, const char * const * const & argv) noexcept(0){

	const size_t penult = NbNews-1;

	static constexpr char _NFBN_ [] = "re_union/cep_ordenado_subpart_";	//_NEW_prcs_files_BASE_NAME_
	string names = _NFBN_;

	for( size_t i = 0; i != NbOlds; ++i){

		old_files[i] = fopen(argv[i+1],"rb");

		new_files[i] = fopen( ( names += string("0_") += to_string(i) += ".txt" ).c_str() ,"wb+");
		names.erase(sizeof(_NFBN_)-1);

		if( old_files[i] == nullptr )
			throw "um dos arquivos de partes não pode ser aberto para leitura no diretório splitters/.";

		if( new_files[i] == nullptr )
			throw "um dos arquivos de subpartes não pode ser aberto para escrita no diretorio re_union/.";
	}

	size_t aux = 0, n = NbOlds/2;
	natural layer = 1;

	for( size_t i = NbOlds; i != penult; ++i, ++aux){

		if( aux == n ){

			++layer;
			aux = 0;
			n /= 2;
		}

		new_files[i] = fopen( ( names +=  to_string(layer) += string("_") += to_string(aux) += ".txt" ).c_str() ,"wb+");
		names.erase(sizeof(_NFBN_)-1);

		if( new_files[i] == nullptr )
			throw "um dos arquivos de subpartes não pode ser aberto para escrita no diretorio re_union/.";
	}

	names.erase(0);
	new_files[penult] = fopen( ( names +=  string("re_union/rebuilded_cep_ordenado.dat") ).c_str() ,"wb+");

return ;}


void ordenar_salvar( FILE ** const & old_files, const size_t NbOlds, FILE ** const & new_files, const size_t NbNews) noexcept(0){

	Registro ** array = nullptr;

	for( size_t i = 0; i != NbOlds; ++i){

		fseek(old_files[i],0,SEEK_END);

		const size_t nb_rgstr = ftell(old_files[i])/sizeof(Registro);
		rewind(old_files[i]);

		if( nb_rgstr*sizeof(Registro) > LIMITE_MEMORIA )
			throw "o objetivo deste trabalho é não trabalhar com arquivos muito grandes na memória... Este arquivo tem mais de 50 MB.";

		array = new Registro * [nb_rgstr];

		for( size_t j = 0; j != nb_rgstr; ++j)
			array[j] = new Registro(old_files[i]);

#if 0
		cout << *array[0] << *array[1];

		const int result = array[0]->compare_with(*array[1]);

		if( result > 0 )
			cout << "o primeiro e maior que o segundo\n\n";

		else if( result < 0 )
			cout << "o primeiro e menor que o segundo\n\n";

		else
			cout << "os dois sao iguais\n\n";

		 exit(0);	//O quick sort nao esta funcionando corretamente neste array, apesar da funcao de compare_with funcionar corretamente nos objetos...
#endif

		qsort(array,nb_rgstr,sizeof(Registro*),[]( const void* r1, const void* r2) noexcept -> int{ return static_cast<const Registro*>(r1)->compare_with( *static_cast<const Registro*>(r2) ); });

		for( size_t j = 0; j != nb_rgstr; ++j){

			array[j]->dump_writing_in(new_files[i]);
			delete(array[j]);
		}

		delete[] array;
	}

return ;}


void merge_concatenando( FILE ** const & new_files, size_t index, const size_t length) noexcept(0){

	size_t i = 1;

	Registro temp1, temp2;	//Declaração dos structs...

	do{	//For each peer of prcs_files...

		rewind(new_files[i-1]);
		rewind(new_files[i]);

		natural Num1 = temp1.fill_reading_from(new_files[i-1]);
		natural Num2 = temp2.fill_reading_from(new_files[i]);

		do{

			if( Num1 != 0 && Num2 != 0 ){

				if( temp1 <= temp2 ){

					temp1.dump_writing_in(new_files[index]);
					Num1 = temp1.fill_reading_from(new_files[i-1]);

				}else{

					temp2.dump_writing_in(new_files[index]);
					Num2 = temp2.fill_reading_from(new_files[i]);
				}

			}else if( Num1 != 0 ){

				temp1.dump_writing_in(new_files[index]);
				Num1 = temp1.fill_reading_from(new_files[i-1]);

			}else if( Num2 != 0 ){

				temp2.dump_writing_in(new_files[index]);
				Num2 = temp2.fill_reading_from(new_files[i]);

			}else
				break;

		}while( true );

		++index;

	}while( ( i += 2 ) < length );

return ;}
