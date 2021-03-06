#!/bin/sh

DIE=0

echo "deb directory..."
(mkdir deb ) > /dev/null || {
	echo "cleaning..."

	(rm -Rf deb/*) > /dev/null || {
	  echo
	  echo "**Error**: removing error ."
	  echo ""
	  exit 1
	}
}



echo "making distribution source file..."
(make dist) > /dev/null || {
  echo
  echo "**Error**: make dist ."
  echo ""
  exit 1
}


echo "copying..."

(mv wxMoldeoControls-*.tar.gz ./deb/) > /dev/null || {
  echo
  echo "**Error**: moving file ."
  echo ""
  exit 1
}


echo "renaming..."
( rename 's/wxMoldeoControls/libmoldeocontrols/' deb/*.tar.gz ) > /dev/null || {
  echo
  echo "**Error**: renaming to libmoldeocontrols."
  echo ""
  exit 1
}
( rename 's/\.tar.gz/\.orig.tar.gz/' deb/*.tar.gz ) > /dev/null || {
  echo
  echo "**Error**: renaming to orig."
  echo ""
  exit 1
}
( rename 's/\-/\_/' deb/*.tar.gz ) > /dev/null || {
  echo
  echo "**Error**: renaming to underscore."
  echo ""
  exit 1
}
( rename 's/A-Z/a-z/' deb/*.tar.gz ) > /dev/null || {
  echo
  echo "**Error**: renaming to lowercase."
  echo ""
  exit 1
}

echo "extracting..."

(tar -C deb -zxvf ./deb/*.orig.tar.gz ) > /dev/null || {
  echo
  echo "**Error**: extracting ."
  echo ""
  exit 1
}

( rename 's/wxMoldeoControls/libmoldeocontrols/' deb/wxMoldeoControls-* ) > /dev/null || {
  echo
  echo "**Error**: renaming to libmoldeocontrols."
  echo ""
  exit 1
}

echo " 
Now execute in deb folder for ubuntu 9.10:
 cd deb/libmoldeocontrols-*
 dh_make -l -e fabricio.costa@moldeointeractive.com.ar -p libmoldeocontrols
 cp ../../control.amd64 debian/control
 cp ../../rules.amd64 debian/rules
 cp ../../libmoldeocontrols.dirs.amd64 debian/libmoldeocontrols.dirs
 cp ../../libmoldeocontrols.install.amd64 debian/libmoldeocontrols.install 
 cp ../../libmoldeocontrols-dev.dirs.amd64 debian/libmoldeocontrols-dev.dirs
 cp ../../libmoldeocontrols-dev.install.amd64 debian/libmoldeocontrols-dev.install
 vi debian/changelog
 dpkg-buildpackage -us -uc -rfakeroot 2>&1 | tee ../../buildpkg_logs.txt

Now execute in deb folder for ubuntu 10.10:
 cd deb/libmoldeocontrols-*
 dh_make -l -e fabricio.costa@moldeointeractive.com.ar
 cp ../../control.amd64 debian/control
 cp ../../libmoldeocontrols-dev.install.amd64 debian/libmoldeocontrols-dev.install
 cp ../../libmoldeocontrols-dev.dirs.amd64 debian/libmoldeocontrols-dev.dirs
 cp ../../libmoldeocontrols.install.amd64 debian/libmoldeocontrols.install
 cp ../../libmoldeocontrols.dirs.amd64 debian/libmoldeocontrols.dirs
 vi debian/changelog
 dpkg-buildpackage -us -uc -rfakeroot 2>&1 | tee ../../buildpkg_logs.txt

Now execute in deb folder for ubuntu 11.10:
 cd deb/libmoldeocontrols-*
 dh_make -l -e fabricio.costa@moldeointeractive.com.ar
 cp ../../control.amd64.11.10 debian/control
 cp ../../libmoldeocontrols-dev.install.amd64 debian/libmoldeocontrols-dev.install
 cp ../../libmoldeocontrols-dev.dirs.amd64 debian/libmoldeocontrols-dev.dirs
 cp ../../libmoldeocontrols.install.amd64 debian/libmoldeocontrols.install
 cp ../../libmoldeocontrols.dirs.amd64 debian/libmoldeocontrols.dirs
 vi debian/changelog
 dpkg-buildpackage -us -uc -rfakeroot 2>&1 | tee ../../buildpkg_logs.txt

Now execute in deb folder for ubuntu 12.10:
 cd deb/libmoldeocontrols-*
 dh_make -l -e info@moldeointeractive.com.ar
 gedit ../../control.amd64.11.10 debian/control ../../libmoldeocontrols-dev.install.amd64 debian/libmoldeocontrols-dev.install ../../libmoldeocontrols-dev.dirs.amd64 debian/libmoldeocontrols-dev.dirs ../../libmoldeocontrols.install.amd64 debian/libmoldeocontrols.install ../../libmoldeocontrols.dirs.amd64 debian/libmoldeocontrols.dirs debian/changelog
 dpkg-buildpackage -us -uc -rfakeroot 2>&1 | tee ../../buildpkg_logs.txt



"


echo "Success: extraction"
exit 0
