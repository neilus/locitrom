#!/bin/bash
workdir=`pwd`
echo $workdir
lemonpath="$workdir/lemon"
cd lemon-1.2
echo `uname -a`|grep -i "mingw"
if [ $? == 0 ];then
	lemonpath="c:\lemon"
else
	lemonpath="$workdir/lemon"
fi
tput setf 4 || true
echo $lemonpath
tput sgr0||true
./configure --prefix="$lemonpath"
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
cd $workdir
cp -r "$lemonpath" "$workdir/lemon$1-bak"
tput setf 2||true
echo "-I $lemonpath/include -L $lemonpath/lib -lemon"|tee lemonpath
tput sgr0||true