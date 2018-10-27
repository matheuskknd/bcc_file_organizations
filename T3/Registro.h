#include<ostream>
using CEP = char[8];

class Registro{

private: /* Methods and Definitions */

	using natural = unsigned int;
	enum comp_r : int{ lt = -1, eq = 0, gt = 1 };	//Comparison results...

	comp_r compare_CEPs( const CEP& other) const noexcept;

private: /* Attibutes */

	char logradouro[72];
	char bairro[72];
	char cidade[72];
	char uf[72];
	char sigla[2];
	CEP cep;	//8 bytes....
	char lixo[2];

public: /* Methods */

	Registro(void) = default;	//Default constructor;
	~Registro() = default;

	inline Registro( FILE * const stream) noexcept{ fread(this,sizeof(char),sizeof(Registro),stream);}	//Reading initializer constructor;
	Registro(int) noexcept;		//Zero initializer constructor;

	inline natural fill_reading_from( FILE * const stream) noexcept{ return fread(this,sizeof(char),sizeof(Registro),stream);}
	inline natural dump_writing_in( FILE * const stream) noexcept{ return fwrite(this,sizeof(char),sizeof(Registro),stream);}

	inline int compare_with( const Registro& other) const noexcept{ return this->compare_CEPs(other.cep);}
	friend std::ostream& operator<<( std::ostream&, const Registro&) noexcept;	//C++ "toString()"

//################################
//########## Operators ###########
//################################

	inline bool operator==( const Registro& ot) const noexcept{ return comp_r::eq == compare_CEPs(ot.cep);}
	inline bool operator!=( const Registro& ot) const noexcept{ return comp_r::eq != compare_CEPs(ot.cep);}

	inline bool operator<=( const Registro& ot) const noexcept{ return comp_r::gt != compare_CEPs(ot.cep);}
	inline bool operator>=( const Registro& ot) const noexcept{ return comp_r::lt != compare_CEPs(ot.cep);}

	inline bool operator>( const Registro& ot) const noexcept{ return comp_r::gt == compare_CEPs(ot.cep);}
	inline bool operator<( const Registro& ot) const noexcept{ return comp_r::lt == compare_CEPs(ot.cep);}

	inline bool operator==( const CEP& ot) const noexcept{ return comp_r::eq == compare_CEPs(ot);}
	inline bool operator!=( const CEP& ot) const noexcept{ return comp_r::eq != compare_CEPs(ot);}

	inline bool operator<=( const CEP& ot) const noexcept{ return comp_r::gt != compare_CEPs(ot);}
	inline bool operator>=( const CEP& ot) const noexcept{ return comp_r::lt != compare_CEPs(ot);}

	inline bool operator>( const CEP& ot) const noexcept{ return comp_r::gt == compare_CEPs(ot);}
	inline bool operator<( const CEP& ot) const noexcept{ return comp_r::lt == compare_CEPs(ot);}

	friend bool operator==( const CEP&, const Registro&) noexcept;
	friend bool operator!=( const CEP&, const Registro&) noexcept;

	friend bool operator<=( const CEP&, const Registro&) noexcept;
	friend bool operator>=( const CEP&, const Registro&) noexcept;

	friend bool operator>( const CEP&, const Registro&) noexcept;
	friend bool operator<( const CEP&, const Registro&) noexcept;
};

inline bool operator==( const CEP& c,  const Registro& r) noexcept{ return Registro::comp_r::eq == r.compare_CEPs(c);}
inline bool operator!=( const CEP& c,  const Registro& r) noexcept{ return Registro::comp_r::eq != r.compare_CEPs(c);}

inline bool operator>=( const CEP& c,  const Registro& r) noexcept{ return Registro::comp_r::gt != r.compare_CEPs(c);}
inline bool operator<=( const CEP& c,  const Registro& r) noexcept{ return Registro::comp_r::lt != r.compare_CEPs(c);}

inline bool operator>( const CEP& c,  const Registro& r) noexcept{ return Registro::comp_r::lt == r.compare_CEPs(c);}
inline bool operator<( const CEP& c,  const Registro& r) noexcept{ return Registro::comp_r::gt == r.compare_CEPs(c);}
