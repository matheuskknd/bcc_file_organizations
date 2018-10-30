#!/bin/bash

#Para executar esse script entre nesse diretorio pelo terminal do linux e digite: "chmod +x sort_checker_aux.sh"
#Depois: "./sort_checker_aux.sh"

function encerrar(){

	echo -e "Encerrando programa precocemente...\n"

exit 2;}

function main(){

	echo -e "\nExecutando sort_checker para para verificar se o arquivo de CEPs está ordenado.\n"

	if [ ! -f 'sort_checker.cpp' ] || [ ! -f '../registro/Registro.h' ] || [ ! -f '../registro/Registro.cpp' ] ; then

		echo -e "Código fonte não encontrado!\n"
		encerrar
	else
		g++ -std=c++14 'sort_checker.cpp' '../registro/Registro.cpp' -o 'sort_checker.run'
	fi

	./sort_checker.run "$1"

	rm -rf 'sort_checker.run'

return 0;}

if (( "$#" != 1 )) ; then

	echo -e "Tente de novo passando o arquivo de CEPs a ser checado.\n"
else

	if [ ! -f "$1" ] ; then

		echo -e "O arquivo $1 não foi encontrado.\n"
	fi

	main "$1"
fi
