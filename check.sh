# @Author: Cristi Cretan
# @Date:   05-05-2019 23:00:09
# @Last Modified by:   Cristi Cretan
# @Last Modified time: 06-05-2019 11:21:57
#!/bin/bash

make build

task1ref="_task1.ref"
task2in="_task2.in"
task2ref="_task2.ref"
task3ref="_task3.ref"

task1_res=0
task2_res=0
task3_res=0

for i in $(seq 0 24)
do
	echo "------------------------"
	echo "TEST $i"
	if  [ $i -lt 15 ]
	then
		cp tests/problema1/test$i.in movies.in
        	./movies -c1 movies.in movies.out

        	diff movies.out tests/problema1/ref/task1/test$i$task1ref > /dev/null

        	out=$(echo $?)
		if [ $out -eq 0 ] 
		then
			echo "TASK 1 PASSED"
			task1_res=$(($task1_res+1))
		else
			echo "TASK 1 FAILED"
		fi

		cp tests/problema1/test$i$task2in movies.in
        	./movies -c2 movies.in movies.out

        	diff movies.out tests/problema1/ref/task2/test$i$task2ref > /dev/null
        	out=$(echo $?)
        	if [ $out -eq 0 ]
        	then
                	echo "TASK 2 PASSED"
			task2_res=$(($task2_res+1))
        	else
                	echo "TASK 2 FAILED"
        	fi
	fi
	cp tests/problema1/test$i.in movies.in
        ./movies -c3 movies.in movies.out

        diff movies.out tests/problema1/ref/task3/test$i$task3ref > /dev/null
	out=$(echo $?)
	if [ $out -eq 0 ]
	then
		echo "TASK 3 PASSED"
		task3_res=$(($task3_res+1))
	else
		echo "TASK 3 FAILED"
	fi
done

echo "Ai obtinut $task1_res/15 pentru Task-ul 1!"
echo "Ai obtinut $task2_res/15 pentru Task-ul 2!"
echo "Ai obtinut $task3_res/25 pentru Task-ul 3!"

big=$(($task1_res+$task2_res+$task3_res))

if [ $big -eq 55 ]
then
	echo "Felicitari ai obtinut punctaj maxim pe task-urile 1, 2, 3 :)"
else
	echo "Ai obtinut doar $big puncte pe task-urile 1, 2, 3 :("
fi

make clean
rm movies.out movies.in
