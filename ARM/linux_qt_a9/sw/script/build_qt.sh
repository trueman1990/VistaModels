#!/bin/bash

SCRIPT="$( cd "$( dirname "${BASH_SOURCE[0]}" )" && pwd )"
SW_ROOT="$(dirname "$SCRIPT")"

source $SW_ROOT/setup.sh

source $SW_ROOT/script/setup_apps.sh

cd $SW_ROOT/packages/qt-everywhere-opensource-src-$VER_QT

cp -rv $SW_ROOT/qt5_patches/linux-vista-g++ qtbase/mkspecs/devices

export SW_ROOT

./configure -v -opensource -confirm-license -release -sysroot $SW_ROOT/sdcard/sysroot -device linux-vista-g++ -device-option CROSS_COMPILE=$CROSS_COMPILE -prefix /usr/local/qt5 -no-sql-psql -no-sql-mysql -no-sql-odbc -no-sql-tds -no-sql-oci -no-sql-db2 -no-sql-sqlite -no-sql-sqlite2 -no-sql-ibase -no-cups -no-nis -no-dbus -no-xcb -no-wayland -nomake examples -nomake tests -no-openssl -no-gtkstyle -no-audio-backend -no-gif -no-widgets -no-qml-debug -no-accessibility -no-eglfs -nomake tools -no-opengl -no-kms -no-directfb -no-xcb -no-compile-examples

make -j 15

make -k -j 15 install

