#!/bin/sh
# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    run_test.sh                                        :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: besellem <besellem@student.42.fr>          +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2021/10/13 18:34:52 by besellem          #+#    #+#              #
#    Updated: 2021/10/13 18:50:29 by besellem         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #


### Constants
PATH_TO_HEADERS="../"
PATH_TO_TESTS="."

CC="clang++"
FLAGS="-Wall -Wextra -Werror -std=c++98"

# Internal paths
_TMP_FOLDER_="$PATH_TO_TESTS/.__tester_tmp__"
REAL_EXEC="$_TMP_FOLDER_/real"
YOUR_EXEC="$_TMP_FOLDER_/yours"
REAL_DIFF="$_TMP_FOLDER_/real_diff.txt"
YOUR_DIFF="$_TMP_FOLDER_/your_diff.txt"


# Ansi color codes
RED="\033[1;31m"
GREEN="\033[1;32m"
YELLOW="\033[0;33m"
BLUE="\033[1;34m"
PURPLE="\033[1;35m"
GRAY="\033[1;37m"
CLR_COLOR="\033[0m"
CLR_LINE="\033[2K\r"
CLR_SCREEN="\033[2J\033[H"


### Functions
print_header()
{
	printf "${RED}  __ _                    _        _                         
 / _| |                  | |      (_)                        
| |_| |_   ___ ___  _ __ | |_ __ _ _ _ __   ___ _ __ ___     
|  _| __| / __/ _ \\| '_ \\| __/ _' | | '_ \\ / _ \\ '__/ __|    
| | | |_ | (_| (_) | | | | || (_| | | | | |  __/ |  \\__ \\    
|_|  \\__| \\___\\___/|_| |_|\\__\\__,_|_|_| |_|\\___|_|  |___/    
      ______                                                 
     |______|                                                \n\n${CLR_COLOR}"

	printf "${RED}%36s${CLR_COLOR}\n"      "REFERENCE TESTS"
	printf "${YELLOW}%40s${CLR_COLOR}\n\n" "- Credits to besellem -"
}


### Main
clear
print_header

if [ $# -lt 1 ]; then
	CONTAINERS="vector stack map set"
else
	CONTAINERS=$*
fi


# create tmp folder
if [ ! -d "$_TMP_FOLDER_" ]; then
	mkdir $_TMP_FOLDER_
fi


for _container in $CONTAINERS; do

	printf "\n"

	if [ ! -d "$PATH_TO_TESTS/$_container" ]; then
		echo "${RED}'$_container' tests don't exist !${CLR_COLOR}";
		continue
	fi

	# print container's name
	echo "Testing ${GREEN}$_container${CLR_COLOR} :";
	
	# print tab labels
	printf "${GRAY}%37s %s | %s | %s${CLR_COLOR}\n" "" "Status" "Your time" "Real time"

	for _file in $PATH_TO_TESTS/$_container/*.cpp; do

		_current_test_name=$(basename $_file | cut -d '.' -f 2)
		printf "${GRAY}%-40s${CLR_COLOR}" "    $_current_test_name"
		
		# compile with your container
		$CC $FLAGS $_file -I $PATH_TO_HEADERS -o "$YOUR_EXEC" 2>/dev/null
		
		# if cannot compile
		if [ $? -eq 1 ]; then
			echo "💀"
			continue
		fi

		# compile the real one (no check needed - shall compile normally)
		$CC $FLAGS $_file -I $PATH_TO_HEADERS -DSTD -o "$REAL_EXEC"

		# execute test with your container
		your_start=$(python -c "import time; print(int(time.time()*1000))")
		./"$YOUR_EXEC" > "$YOUR_DIFF"
		your_end=$(python -c "import time; print(int(time.time()*1000))")

		# execute test with the real container
		real_start=$(python -c "import time; print(int(time.time()*1000))")
		./"$REAL_EXEC" > "$REAL_DIFF"
		real_end=$(python -c "import time; print(int(time.time()*1000))")

		# difference between two results examined
		diff "$REAL_DIFF" "$YOUR_DIFF" >/dev/null

		# print results
		if [ $? -eq 1 ]; then
			printf "❌"
		else
			printf "✅"
		fi

		# get execution time
		your_time=$(echo "$your_end - $your_start" | bc -l)
		real_time=$(echo "$real_end - $real_start" | bc -l)

		# print execution time
		if [ $your_time -lt $real_time ]; then
			printf "${GREEN}%11d${CLR_COLOR} ms"  "$your_time"
			printf          "%9d ms\n"            "$real_time"
		else
			printf        "%11d ms"               "$your_time"
			printf "${GREEN}%9d${CLR_COLOR} ms\n" "$real_time"
		fi
		
	done

done

# remove tmp folder and files
if [ -d "$_TMP_FOLDER_" ]; then
	rm -rf $_TMP_FOLDER_
fi
