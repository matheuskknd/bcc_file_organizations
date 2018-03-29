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
		echo "Código fonte não encontrado!"
		encerrar
	else
		g++ cep_solver.cpp -o cep_solver.run
	fi

	if [ ! -f cep_ordenado.dat ] ; then
		echo "Base de dados não encontrada!"
		echo "Se você não tiver o arquivo cep_ordenado.dat pode baixá-lo no seguinte endereço:"
		echo "https://mega.nz/#!vnpEjRqS!AjZou1g2_vdqE_-Z7ELdwqC7qIK5RNeN530wtYGCZDY"
		encerrar
	else
		./cep_solver.run cep_ordenado.dat $1
	fi

	rm "cep_solver.run"

return 0;}

if [ -z $1 ] ; then

	echo "Tente de novo passando o CEP para comparar..."
	exit 0

elif [ ${#1} != 8 ] ; then

	echo "CEP incorreto, por favor tente de novo."
	exit 0

else
	main $1
fi
