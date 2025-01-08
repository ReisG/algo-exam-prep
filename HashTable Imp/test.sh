gcc main.c -O3 -o main
gcc gen.c -O3 -o gen

for t in $(seq 1 100000); do
    ./gen > test
    ./main < test > out || exit
done