#!/bin/bash

while [[ 1 ]]
do
		./a.out > test
		./solution <test >out 2>out_warns
		if [[ $? > 0 ]]
		then
			echo -e "\033[1;31mWarning!"
			exit 1
		else
			echo -e "\033[1;32mPassed!"
		fi
done
