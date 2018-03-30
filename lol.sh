#!/bin/bash

i=0;
delay=0.25

while [ $? -lt 127 ] && [ $i -ne 200 ];
do
	sleep $delay;
	i=$[$i+1];
	tmp=$(echo "&&" | ./radamsa/bin/radamsa)
	printf "\033[31mTesting |%s||%s|\n\033[0m" "$tmp";
	(echo "$tmp" | xxd) || true
	./minishell <<< "$tmp && $tmp";
done;

if [ $i -eq 200 ];
then
	printf "\e[32mSuccess\033[0m";
	exit 0;
else
	exit 1;
fi;
