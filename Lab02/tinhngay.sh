#!/bin/bash

nam=$1
thang=$2
tap_tin=$3

> $tap_tin

if [ $nam -lt 1900 ]; then
    echo "Nam khong hop le" > $tap_tin
    exit 1
fi

if [ $thang -lt 1 ] || [ $thang -gt 12 ]; then
    echo "Thang khong hop le" > $tap_tin
    exit 1
fi

case "$thang" in
    "1" | "3" | "5" | "7" | "8" | "10" | "12") ngay=31;;
    "4" | "6" | "9" | "11") ngay=30;;
    "2") 
        if [ $((nam % 4)) -eq 0 ] && [ $((nam % 100)) -ne 0 ] || [ $((nam % 400)) -eq 0 ]; then
            ngay=29
        else
            ngay=28
        fi
        ;;
    *) echo "Thang khong hop le" > $tap_tin
       exit 1
       ;;
esac

echo $ngay > $tap_tin
exit 0





