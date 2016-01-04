#!/bin/bash
#
# Build script to compile all language versions of SiEd from the Master branch
# on  GitHub.
#
# USAGE:  do_release.sh [version number]
#

function make_release()
{
	echo $1;
	echo $2;
	echo $3;
	make clean
	make "$2"
	zip sied-"$1"-"$3".prc.zip sied.prc
	mv sied-"$1"-"$3".prc.zip ../../SiEd-"$1"/
}


if [ "$#" -ne 1 ]
then
        echo -e "\nERROR - Usage:  do_release.sh [release version number]\n"
else
	cd /tmp
	git clone https://github.com/rtiangha/SiEd.git
	mkdir SiEd-$1
	cd SiEd/src/
	make clean
	make
	cp sied.prc ../../SiEd-$1/sied-current.prc
	zip sied-$1.prc.zip sied.prc
	mv sied-$1.prc.zip ../../SiEd-$1/
	cp ../docs/changelog ../../SiEd-$1/changelog.txt
	cp ../docs/install ../../SiEd-$1/install.txt

	make_release $1 french fr
	make_release $1 german de
	make_release $1 italian it
	make_release $1 portuguese pt
	make_release $1 norwegian no
	make_release $1 dutch nl
	make_release $1 catalan ca
	make_release $1 spanish es
	make_release $1 turkish tr
	make_release $1 russian ru
	make_release $1 polish pl
	make_release $1 swedish se
	make_release $1 czech cz

	make clean
	cd /tmp/
	mv SiEd sied
	tar zcvf sied-$1-src.tar.gz sied/
	mv sied-$1-src.tar.gz SiEd-$1/ 
	zip -r SiEd-$1.zip SiEd-$1
	rm -rf sied/
fi

