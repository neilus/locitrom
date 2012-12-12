#!/bin/bash
workdir=`pwd`
echo $workdir
cd lemon-1.2
./configure --prefix="$workdir/lemon"
if [ $? != 0 ];then
	tput setf 4 ||true
	echo "elhasalt LEMON TELEPITESE az elofelteteleknel!!!"
else	
	tput setf 2 || true
	echo "a lemon elofeltetelvizsgalaton sikeresen atment..."
	tput sgr0||true
	make
	if [ $? != 0 ];then
		tput setf 4||true
		echo "elhasalt LEMON forditasa!!!"
	else	
		tput setf 2||true
		echo "lefordult lemon..."
		tput sgr0||true
		make install
		if [ $? != 0 ];then
			tput setf 4||true
			echo "nem tudtam telepiteni a lemont a megadott helyre!!!"
		else	
			tput setf 2||true
			echo "telepitettem a LEMON-t a $workdir/lemon konyvtarba "
		fi
	fi 	
fi 
tput sgr0
cp -r "$workdir/lemon" "$workdir/lemon$1"
