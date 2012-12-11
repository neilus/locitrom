#!/bin/bash
workdir=`pwd`
echo $workdir
cd lemon-1.2
./configure --prefix="$workdir/lemon"
if [ $? != 0 ];then
	tput setf 4
	echo "elhasalt LEMON TELEPITESE az elofelteteleknel!!!"
else	
	tput setf 2
	echo "a lemon elofeltetelvizsgalaton sikeresen atment..."
	tput sgr0
	if [ $? != 0 ];then
		tput setf 4
		echo "elhasalt LEMON forditasa!!!"
	else	
		tput setf 2
		echo "lefordult lemon..."
		tput sgr0
		make install
		if [ $? != 0 ];then
			tput setf 4
			echo "nem tudtam telepiteni a lemont a megadott helyre!!!"
		else	
			tput setf 2
			echo "telepitettem a LEMON-t a $workdir/lemon konyvtarba "
		fi
	fi 	
fi 
sgr0
cp -r "$workdir/lemon" "$workdir/lemon$1"
