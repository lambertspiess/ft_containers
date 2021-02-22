#! /bin/bash

green='\033[32m'
reset='\033[0m'

for (( ;; ))
do
	echo -e "${green}================================================${reset}"
	echo -e "Pick a container to test :"
	for (( ;; ))
	do
		echo -e "[1] List, [2] Stack, [3] Queue, [4] Vector, [5] Map"
		echo -en "Your choice : "
		read input
		if [ $input -lt 6 ] && [ $input -gt 0 ]; then
			break
		fi
	done

	printf "\033c"

	echo -e "${green}================================================${reset}"

	declare -a CONTAINER_NAMES=( 'list' 'stack' 'queue' 'vector' 'map' )

	make N=${CONTAINER_NAMES[($input - 1)]}

done
