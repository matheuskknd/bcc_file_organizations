#!/bin/bash

#Para executar esse script entre nesse diretorio pelo terminal do linux e digite: "chmod +x testando.sh"

function encerrar(){

	echo -e "Encerrando programa precocemente...\n"
	if [ -x 'CEP_splitter.run' ] ; then rm "CEP_splitter.run"; fi

exit 2;}


function main(){

	echo -e "\nExecutando CEP_splitter.run no arquivo com CEPs ordenados.\n"

	if [ ! -f 'CEP_splitter.cpp' ] ; then

		echo -e "Código fonte não encontrado!\n"
		encerrar
	else
		g++ CEP_splitter.cpp -o CEP_splitter.run
	fi

	if [ ! -f 'CEPS/cep_ordenado.dat' ] ; then

		echo -e "Base de dados não encontrada!\n"
		echo "Se você não tiver o arquivo cep_ordenado.dat pode baixá-lo no seguinte endereço:"
		echo -e "https://mega.nz/#!vnpEjRqS!AjZou1g2_vdqE_-Z7ELdwqC7qIK5RNeN530wtYGCZDY\n"
		echo "Favor colocar destro da pasta CEPS neste mesmo diretório."
		encerrar
	else
		./CEP_splitter.run "CEPS/cep_ordenado.dat" "CEPS/cep_ordenado_1.1.dat" "CEPS/cep_ordenado_1.2.dat"
	fi

	rm "CEP_splitter.run"

return 0;}

main
