rm 1 -f
rm 2 -f
rm dataGenerator
g++ -Wall -o 1 1.cpp 
g++ -Wall -o 2 2.cpp
g++ -o dataGenerator dataGenerator.cpp -std=c++11
declare -i t=0 t1=0 t2=0 t1Sum=0 t2Sum=0 t1Avg=0 t2Avg=0 start=0 finish=0
while [ $t -lt $1 ]
do
    t=t+1
    rm input -f
    rm output1 -f
    rm output2 -f
    ./dataGenerator
    start=$(date +%s%N)
    ./1 < input > output1
    finish=$(date +%s%N)
    t1=finish-start
    start=$(date +%s%N)
    ./2 < input > output2
    finish=$(date +%s%N)
    t2=finish-start
    t1Sum=t1Sum+t1
    t2Sum=t2Sum+t2
    if diff output1 output2; then
        echo AC${t} ${t1}ns ${t2}ns

    else
        echo WA
        exit 0
    fi
done
echo
echo Pass!
echo
t1Avg=t1Sum/$1
t2Avg=t2Sum/$1
echo Average: ${t1Avg}ns ${t2Avg}ns