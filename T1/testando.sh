#!/bin/bash

#Para executar esse script entre nesse diretorio pelo terminal do linux e digite: "chmod +x testando.sh"
#Para buscar um CEP digite no terminal: "./testando.sh <CEP>"

function encerrar(){

	echo -e "Encerrando programa precocemente...\n"
	if [ -x cep_solver.run ] ; then rm "cep_solver.run"; fi

exit 2;}


function main(){

	echo -e "\nExecutando cep_solver no arquivo com CEPs ordenados. Buscando $1\n"

	if [ ! -f cep_solver.cpp ] ; then

		echo -e "Código fonte não encontrado!\n"
		encerrar
	else
		g++ cep_solver.cpp -o cep_solver.run
	fi

	if [ ! -f cep_ordenado.dat ] ; then

		echo -e "Base de dados não encontrada!\n"
		echo "Se você não tiver o arquivo cep_ordenado.dat pode baixá-lo no seguinte endereço:"
		echo -e "https://mega.nz/#!vnpEjRqS!AjZou1g2_vdqE_-Z7ELdwqC7qIK5RNeN530wtYGCZDY\n"
		encerrar
	else
		./cep_solver.run cep_ordenado.dat $1
	fi

	rm "cep_solver.run"

return 0;}

if [ -z $1 ] ; then

	echo -e "\nTente de novo passando o CEP para comparar...\n"
	exit 0

elif [[ ! "$1" =~ ^[0-9]{8}$ ]] ; then

	echo "CEP incorreto, por favor tente de novo."
	exit 0

else
	main $1
fi
