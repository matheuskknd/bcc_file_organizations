#!/bin/bash

#Para executar esse script entre nesse diretorio pelo terminal do linux e digite: "chmod +x hyper_sort_conc_aux.sh"
#Depois: "./hyper_sort_conc_aux.sh"

function encerrar(){

	echo -e "Encerrando programa precocemente...\n"
	if [ -x 'hyper_sort_concatenator.run' ] ; then rm 'hyper_sort_concatenator.run'; fi

exit 2;}

function main(){

	echo -e "\nExecutando hyper_sort_concatenator para concatenar vários sub-arquivos num único arquivo ordenado de CEPs.\n"

	if [ ! -d 'splitters' ] ; then

		echo -e "Erro! O diretorio splitters deve estar presente ao lado deste código para este ser executado!\n"
		echo -e "Execute hyper_split_aux.sh <param1> para que esta pasta seja criada!\n"
		encerrar
	fi

	sub_files=(splitters/*.txt);

	if [ ${#sub_files[@]} -lt '2' ] ; then

		echo -e "Algo está errado. O diretorio splitters deve conter ao menos dois arquivos de registros de CEP!\n"
		echo -e "Execute hyper_split_aux.sh <param1> com param1 maior ou igual a 2!\n"
		encerrar
	fi

	if [ -d 're_union' ] ; then rm -rf 're_union'; fi

	mkdir 're_union';

	if [ ! -f 'hyper_sort_concatenator.cpp' ] || [ ! -f 'Registro.h' ] || [ ! -f 'Registro.cpp' ] ; then

		echo -e "Código fonte não encontrado!\n"
		encerrar
	else
		g++ -std=c++14 'hyper_sort_concatenator.cpp' 'Registro.cpp' -o 'hyper_sort_concatenator.run'
	fi

	./hyper_sort_concatenator.run ${sub_files[@]}

	rm -rf 'hyper_sort_concatenator.run'

return 0;}

main
