#!/bin/bash
function make_release()
{
	echo $1;
	echo $2;
	echo $3;
	make clean
	make "$2"
	zip sied-"$1"-"$3".prc.zip sied.prc
	mv sied-"$1"-"$3".prc.zip ../../sied_install/
}

#cvs tag -b SiEd-Release_$1

cd /tmp
git clone https://github.com/rtiangha/SiEd.git
mkdir sied_install
cd SiEd/src/
make clean
make
cp sied.prc ../../sied_install/sied-current.prc
zip sied-$1.prc.zip sied.prc
mv sied-$1.prc.zip ../../sied_install/
cp changelog ../../sied_install/changelog.txt

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
mv sied-$1-src.tar.gz sied_install

rm -rf sied/

