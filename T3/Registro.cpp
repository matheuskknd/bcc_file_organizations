#include"Registro.h"

Registro::Registro(int) noexcept{

	for( natural i = 0; i != sizeof(uf); ++i){

		logradouro[i] = ' ';
		bairro[i] = ' ';
		cidade[i] = ' ';
		uf[i] = ' ';
	}

	for( natural i = 0; i != sizeof(lixo); ++i){

		sigla[i] = ' ';
		lixo[i] = '\0';
	}

	for( natural i = 0; i != sizeof(CEP); ++i)
		cep[i] = '0';
}


Registro::comp_r Registro::compare_CEPs( const CEP& other) const noexcept{

	for( natural i = 0; i != sizeof(CEP); ++i){

		if( this->cep[i] - other[i] < 0 )
			return comp_r::lt;

		else if( this->cep[i] - other[i] > 0 )
			return comp_r::gt;
	}

return comp_r::eq;}


std::ostream& operator<<( std::ostream& out, const Registro& r) noexcept{

	using natural = unsigned int;

	char last, cur;

//################################

	out << "\nLogradouro: ";
	last = r.logradouro[0];

	for( natural i = 1; i != sizeof(r.logradouro); ++i){

		cur = r.logradouro[i];

		if( last == ' ' ){

			if( cur == ' ' )
				break;

			out << last;
			last = cur;

		}else{

			out << last;
			last = cur;
		}
	}

	if( last != ' ' )
		out << last;

//################################



	out << "\nBairro: ";
	last = r.bairro[0];

	for( natural i = 1; i != sizeof(r.bairro); ++i){

		cur = r.bairro[i];

		if( last == ' ' ){

			if( cur == ' ' )
				break;

			out << last;
			last = cur;

		}else{

			out << last;
			last = cur;
		}
	}

	if( last != ' ' )
		out << last;

//################################

	out << "\nCidade: ";
	last = r.cidade[0];

	for( natural i = 1; i != sizeof(r.cidade); ++i){

		cur = r.cidade[i];

		if( last == ' ' ){

			if( cur == ' ' )
				break;

			out << last;
			last = cur;

		}else{

			out << last;
			last = cur;
		}
	}

	if( last != ' ' )
		out << last;

//################################

	out << "\nEstado: ";
	last = r.uf[0];

	for( natural i = 1; i != sizeof(r.uf); ++i){

		cur = r.uf[i];

		if( last == ' ' ){

			if( cur == ' ' )
				break;

			out << last;
			last = cur;

		}else{

			out << last;
			last = cur;
		}
	}

	if( last != ' ' )
		out << last;

//################################

	out << "\tSigla: ";

	if( r.sigla[0] != ' ' ){

		out << r.sigla[0];

		if( r.sigla[1] != ' ' )
			out << r.sigla[1];
	}

//################################

	out << "\n\nCEP:\t";

	for( natural i = 0; i != sizeof(CEP); ++i)
		out << r.cep[i];

//################################

	out << "\n\n";
	
return out;}
