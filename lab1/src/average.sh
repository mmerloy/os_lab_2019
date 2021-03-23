#!/bin/bash
sum=0
count=0
file="numbers.txt"
for i in $(cat $file)
do
let "sum=sum+var"
let "count=count+1"
done
let "ans=sum/count"
echo "&ans"