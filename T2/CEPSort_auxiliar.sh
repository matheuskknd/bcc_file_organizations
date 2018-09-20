#!/bin/bash

#Para executar esse script entre nesse diretorio pelo terminal do linux e digite: "chmod +x testando.sh" e execute.

function encerrar(){

	echo -e "Encerrando programa precocemente...\n"
	if [ -x 'CEP_sorter.run' ] ; then rm 'CEP_sorter.run'; fi

exit 2;}


function main(){

	echo -e "\nExecutando CEPSort_auxiliar.sh nos dois arquivo com CEPs ordenados.\n"

	if [ ! -f 'CEP_sorter.cpp' ] ; then

		echo -e "Código fonte não encontrado!\n"
		encerrar
	else
		g++ CEP_sorter.cpp -o CEP_sorter.run
	fi

	if [ ! -f 'CEPS/cep_ordenado_1.1.dat' ] || [ ! -f 'CEPS/cep_ordenado_1.2.dat' ] ; then

		echo -e "Base de dados não encontrada!\n"
		echo "Se você não tiver os arquivos 'cep_ordenado_1.1.dat' e 'cep_ordenado_1.2.dat' você pode executar 'CEPsplit_auxiliar.sh' para criá-los."
		encerrar
	else
		./CEP_sorter.run "CEPS/cep_ordenado_1.1.dat" "CEPS/cep_ordenado_1.2.dat" "CEPS/NOVO_cep_ordenado.dat"
	fi

	rm 'CEP_sorter.run'

return 0;}


main
