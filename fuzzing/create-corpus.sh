#!/bin/bash

VECTORS=$(cat ../tests/test_vectors_unsigned.json)
len=$(echo $VECTORS | jq -re '.transactions | length')
for ((i=0;i<$len;i++)); do 
	name=$(echo $VECTORS | jq -re .transactions[$i].name); 
	value=$(echo $VECTORS | jq -re .transactions[$i].cases[0].binary); 
	echo "$name=$value"; 
	echo $value | base64 --decode > corpus/$name.bin
done

