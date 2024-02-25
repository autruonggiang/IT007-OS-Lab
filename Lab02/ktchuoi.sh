#!/bin/bash


chuoi=$1
tap_tin_kiem_tra=$2
tap_tin_ket_qua=$3

if [ ! -f "$tap_tin_kiem_tra" ]
then
	echo "Tap tin $tap_tin_kiem_tra khong ton tai" > "$tap_tin_ket_qua"
	exit 1
fi

echo "" > "$tap_tin_ket_qua" 

if grep -q "$chuoi" "$tap_tin_kiem_tra"
then
	echo "Trong tap tin $tap_tin_kiem_tra co chuoi $chuoi" > "$tap_tin_ket_qua"
else
	echo "Trong tap tin $tap_tin_kiem_tra khong co chuoi $chuoi" > "$tap_tin_ket_qua"
fi

exit 0




