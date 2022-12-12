#!/bin/bash
echo "enter a number"
read n
num=0
temp=$n
while (($temp>0))
do
    k=$((temp % 10))
    num=$((num * 10 +k))
    temp=$((temp / 10))
done
echo "$num is reverse of $n."
