#!/bin/bash
classifyPath='./square'
classifyTrainTestPath=$(ls $classifyPath)

for m in $classifyTrainTestPath
do
	txtName=$m'.txt'
	if [ -f $txtName ]; then
		rm $txtName
	fi
	touch $txtName
	classify=$(ls ${classifyPath}/$m)
	for i in $classify
	do
		# if [ -d $i ]; then
			imgName=$(ls ${classifyPath}/$m/$i)
			for j in $imgName
			do
				echo ${classifyPath}/$m/$i/$j >> $txtName
				echo $i >> $txtName
			done
		# fi
	done
done