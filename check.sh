#!/bin/bash

sum=0
max_sum=90;
mkdir output

for i in $(seq 1 10); do
	./christmas < input/test$i.in > output/test$i.out
	diff -wb output/test$i.out output-ref/test$i.out.ref > /dev/null
	if [ $? -eq 0 ]; then
		echo "Test $i ..................... passed"
		sum=$(($sum + 9))
	else
		echo "Test $i ..................... failed"
	fi
	sleep 0.5
done
echo ""
echo "TOTAL: $sum/$max_sum puncte"
if [ $sum -eq $max_sum ]; then
	cat Santa
fi

