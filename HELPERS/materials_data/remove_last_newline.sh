#! /bin/bash

srcDir=$1

for filename in "$srcDir"/*.txt; do
	sed -i.bak '/^[[:blank:]]*$/{$d;}' ${filename}
done
