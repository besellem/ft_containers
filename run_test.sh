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
PATH_TO_HEADERS="."
PATH_TO_TESTS="./test"

CC="clang++"
FLAGS="-Wall -Wextra -Werror"

# Ansi color codes
RED="\033[1;31m"
GREEN="\033[1;32m"
YELLOW="\033[1;33m"
BLUE="\033[1;34m"
PURPLE="\033[1;35m"
GRAY="\033[1;37m"
CLR_COLOR="\033[0m"
CLR_LINE="\033[2K\r"
CLR_SCREEN="\033[2J\033[H"


### Functions
print_header()
{
	printf $RED"  __ _                    _        _                         
 / _| |                  | |      (_)                        
| |_| |_   ___ ___  _ __ | |_ __ _ _ _ __   ___ _ __ ___     
|  _| __| / __/ _ \\| '_ \\| __/ _' | | '_ \\ / _ \\ '__/ __|    
| | | |_ | (_| (_) | | | | || (_| | | | | |  __/ |  \\__ \\    
|_|  \\__| \\___\\___/|_| |_|\\__\\__,_|_|_| |_|\\___|_|  |___/    
      ______                                                 
     |______|                                                
 _            _               __                             
| |          | |             / _|                            
| |_ ___  ___| |_   _ __ ___| |_ ___ _ __ ___ _ __   ___ ___ 
| __/ _ \\/ __| __| | '__/ _ \\  _/ _ \\ '__/ _ \\ '_ \\ / __/ _ \\
| ||  __/\\__ \\ |_  | | |  __/ ||  __/ | |  __/ | | | (_|  __/
 \\__\\___||___/\\__| |_|  \\___|_| \\___|_|  \\___|_| |_|\\___\\___|
               ______                                        
              |______|                                       \n\n" $CLR_COLOR

	printf "    ${YELLOW}Credits to besellem ${CLR_COLOR}\n\n"
}


### Main
clear
print_header

if [ $# -lt 1 ]
then
	CONTAINERS="vector stack map set"
else
	CONTAINERS=$*
fi

for _container in $CONTAINERS
do

	printf "\n"

	if [ ! -d "$PATH_TO_TESTS/$_container" ]
	then
		echo "$RED'$_container' tests don't exist !$CLR_COLOR";
		continue
	fi

	# print container's name
	echo "Testing $GREEN$_container$CLR_COLOR :";
	
	# print tab labels
	printf $GRAY"%37s status | %s | %s\n"$CLR_COLOR "" "My time" "Real time"

	for _file in $PATH_TO_TESTS/$_container/*.cpp
	do

		_current_test_name=$(basename $_file | cut -d '.' -f 2)
		printf $GRAY"%-40s"$CLR_COLOR "    $_current_test_name"
		
		# compile with my container
		$CC $FLAGS $_file -I $PATH_TO_HEADERS -o mine 2>/dev/null
		
		# if cannot compile
		if [ $? -eq 1 ]
		then
			echo "💀"
			continue
		fi

		# compile the real one (no check needed - shall compile normally)
		$CC $FLAGS $_file -I $PATH_TO_HEADERS -DSTD -o real

		# execute test with my container
		my_start=$(python -c "import time; print(int(time.time()*1000))")
		./mine > _mine.txt
		my_end=$(python -c "import time; print(int(time.time()*1000))")

		# execute test with the real container
		real_start=$(python -c "import time; print(int(time.time()*1000))")
		./real > _real.txt
		real_end=$(python -c "import time; print(int(time.time()*1000))")

		# difference between two results examined
		diff _mine.txt _real.txt >/dev/null

		# print results
		if [ $? -eq 1 ]
		then
			printf "❌"
		else
			printf "✅"
		fi

		# get execution time
		my_time=$(echo "$my_end - $my_start" | bc -l)
		real_time=$(echo "$real_end - $real_start" | bc -l)

		# print execution time
		if [ $my_time -lt $real_time ]
		then
			printf "    $GREEN%5d$CLR_COLOR ms"   "$my_time"
			printf "    %5d ms\n"                 "$real_time"
		else
			printf "    %5d ms"                   "$my_time"
			printf "    $GREEN%5d$CLR_COLOR ms\n" "$real_time"
		fi


		rm mine real _mine.txt _real.txt
		
	done

done
