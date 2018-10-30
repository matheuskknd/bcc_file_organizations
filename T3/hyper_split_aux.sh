#!/bin/bash

#Para executar esse script entre nesse diretorio pelo terminal do linux e digite: "chmod +x hyper_sppliter.sh"
#Depois: "./hyper_sppliter.sh"

function encerrar(){

	echo -e "Encerrando programa precocemente...\n"
	if [ -x 'hyper_splitter.run' ] ; then rm 'hyper_splitter.run'; fi

exit 2;}


function main(){

	echo -e "\nExecutando hyper_splitter no arquivo com CEPs ordenados. Para subdividir em $1 partes.\n"

	if [ -d 'splitters' ] ; then rm -rf 'splitters'; fi

	mkdir 'splitters'

	if [ ! -f 'hyper_splitter.cpp' ] || [ ! -f '../registro/Registro.h' ] ; then

		echo -e "Código fonte não encontrado!\n"
		encerrar
	else
		g++ -std=c++14 'hyper_splitter.cpp' -o 'hyper_splitter.run'
	fi

	if [ ! -f 'cep_ordenado.dat' ] ; then

		echo -e "Base de dados não encontrada!\n"
		echo "Se você não tiver o arquivo cep_ordenado.dat pode baixá-lo no seguinte endereço:"
		echo -e "https://mega.nz/#!vnpEjRqS!AjZou1g2_vdqE_-Z7ELdwqC7qIK5RNeN530wtYGCZDY\n"
		encerrar
	else
		./hyper_splitter.run $1
	fi

	rm 'hyper_splitter.run'

return 0;}


if [ -z $1 ] ; then

	echo -e "Tente de novo passando um número de subdivisões a serem feitas..."
	exit 0

elif [[ ! "$1" =~ ^[0-9]{1,9}$ ]] ; then

	echo "Parametro deve ser numérico de 1 a 9 digitos! Por favor tente de novo."
	exit 0

else
	main $1
fi
