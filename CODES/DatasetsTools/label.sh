#!/bin/bash
InputDatasets='./square'

for m in $(ls $InputDatasets)
do
	txtPath=$m'.txt'
	if [ -f $txtPath ]; then
		rm $txtPath
	fi
	touch $txtPath
	for i in $(ls ${InputDatasets}/$m)
	do
		for j in $(ls ${InputDatasets}/$m/$i)
		do
			printf ${InputDatasets}/$m/$i/$j'\t' >> $txtPath
			printf $i'\t' >> $txtPath
			if [ $i == Appendicularia ];then
				printf '1\n' >> $txtPath
			elif [ $i == Bubble ];then
				printf '2\n' >> $txtPath
			elif [ $i == Chaetognatha ];then
				printf '3\n' >> $txtPath
			elif [ $i == CladoceraPenilia ];then
				printf '4\n' >> $txtPath
			elif [ $i == Copepoda ];then
				printf '5\n' >> $txtPath
			elif [ $i == Decapoda ];then
				printf '6\n' >> $txtPath
			elif [ $i == Doliolida ];then
				printf '7\n' >> $txtPath
			elif [ $i == Egg ];then
				printf '8\n' >> $txtPath
			elif [ $i == Fiber ];then
				printf '9\n' >> $txtPath
			elif [ $i == Gelatinous ];then
				printf '10\n' >> $txtPath
			elif [ $i == Multiple ];then
				printf '11\n' >> $txtPath
			elif [ $i == Nonbio ];then
				printf '12\n' >> $txtPath
			else 
				printf '13\n' >> $txtPath
			fi
		done
	done
done