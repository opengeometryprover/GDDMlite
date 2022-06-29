#!/bin/bash

# Função para percorrer um directório
walk_dir () {
    for pathname in *.proof; do
        nome=`echo "$pathname" | cut -d'.' -f1`
        extensao=`echo "$pathname" | cut -d'.' -f2`
	notproved=`grep ^Not  "$nome.proof"`
	proved=`grep ^Proved  "$nome.proof"`
	if  [ "$notproved" == "Not Proved" ]; then
	    echo "$nome.proof ; Not Proved ; `egrep '[0-9]+.[0-9.]+' $nome.proof`" | sed -re "s/Time spent: ([0-9]+).([0-9]+)/\1,\2/"
	else
	    if  [ "$proved" == "Proved" ]; then
		echo "$nome.proof ; Proved ; `egrep '[0-9]+.[0-9.]+' $nome.proof`"  | sed -re "s/Time spent: ([0-9]+).([0-9]+)/\1,\2/"
	    else
		echo  "$nome.proof ; Not Proved ; Timeout"
	    fi
	fi
    done
}

walk_dir
