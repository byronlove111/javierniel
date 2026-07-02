EXERCISE="BSQ"

index=0

if [ -e traceback ]; then
    rm traceback
fi

cd .system/grading

# Compile reference solution
gcc bsq.c main.c -o source 2>/dev/null

# --- 7 test cases ---

# Test 1: file argument (original map)
./source map.txt | cat -e > sourcexam

# Test 2: stdin (original map)
./source < map.txt | cat -e >> sourcexam

# Test 3: all obstacles via stdin
printf "3 . o x\noooo\noooo\noooo\n" | ./source | cat -e >> sourcexam

# Test 4: no obstacles via stdin (biggest square = whole map)
printf "3 . o x\n....\n....\n....\n" | ./source | cat -e >> sourcexam

# Test 5: single empty cell surrounded by obstacles
printf "3 . o x\noooo\noo.o\noooo\n" | ./source | cat -e >> sourcexam

# Test 6: invalid map — two chars identical (map error on stderr)
printf "3 . . x\n...\n...\n...\n" | ./source 2>&1 | cat -e >> sourcexam

# Test 7: multiple map files as arguments (newline between)
./source map.txt map2.txt | cat -e >> sourcexam

rm -f source

# Compile student solution
{
    gcc ../../rendu/"$EXERCISE"/*.c -o final
} 2>traceback

if [ -f final ]; then
    ./final map.txt | cat -e > finalexam
    ./final < map.txt | cat -e >> finalexam
    printf "3 . o x\noooo\noooo\noooo\n" | ./final | cat -e >> finalexam
    printf "3 . o x\n....\n....\n....\n" | ./final | cat -e >> finalexam
    printf "3 . o x\noooo\noo.o\noooo\n" | ./final | cat -e >> finalexam
    printf "3 . . x\n...\n...\n...\n" | ./final 2>&1 | cat -e >> finalexam
    ./final map.txt map2.txt | cat -e >> finalexam
    rm -f final
else
    touch finalexam
fi

DIFF=$(diff sourcexam finalexam)
if [ "$DIFF" != "" ]; then
    index=$((index + 1))
    echo "<-------------- YOUR OUTPUT ------------>" >> traceback
    cat finalexam >> traceback
    if [ -s finalexam ]; then
        echo "<-------------- EXPECTED OUTPUT : ------------>" >> traceback
        cat sourcexam >> traceback
        echo "<-------------- DIFF : ------------>" >> traceback
        echo "$DIFF" >> traceback
    else
        echo "Compilation Error." >> traceback
        echo "Reminder: expected files in rendu/BSQ/: *.c *.h (including your own main.c)" >> traceback
    fi
fi

rm -f finalexam

if [ $index -eq 0 ]; then
    touch passed
fi

{ mv traceback ../../traceback; } &>/dev/null
rm -f sourcexam

cd ../..
