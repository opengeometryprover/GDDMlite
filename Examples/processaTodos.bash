#!/bin/bash

# Função para percorrer um directório
walk_dir () {
    for pathname in *.gddm; do
        nome=`echo "$pathname" | cut -d'.' -f1`
        extensao=`echo "$pathname" | cut -d'.' -f2`
#	sed -i '/^$/d' "$nome.p"
#	sed -i '/%/d' "$nome.p"
#        sed "/geometryDeductiveDatabaseMethod/d" "$nome.p" > "${nome}.gddm"
	echo "./gddm $nome.gddm > $nome.proof"
	timeout 600s ./gddm "$nome.gddm" > "$nome.proof"
    done
}

walk_dir


