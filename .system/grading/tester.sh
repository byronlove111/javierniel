EXERCISE="Life"

index=0

if [ -e traceback ]; then
    rm traceback
fi

cd .system/grading

# Compile reference solution (main is inside life.c)
gcc life.c -o source 2>/dev/null

# Run all test cases from the subject
echo 'sdxddssaaww' | ./source 5 5 0 | cat -e > sourcexam
echo 'sdxssdswdxddddsxaadwxwdxwaa' | ./source 10 6 0 | cat -e >> sourcexam
echo 'dxss' | ./source 3 3 0 | cat -e >> sourcexam
echo 'dxss' | ./source 3 3 1 | cat -e >> sourcexam
echo 'dxss' | ./source 3 3 2 | cat -e >> sourcexam

rm -f source

# Compile student solution (they provide all *.c *.h including main)
{
    gcc ../../rendu/"$EXERCISE"/*.c -o final
} 2>traceback

if [ -f final ]; then
    echo 'sdxddssaaww' | ./final 5 5 0 | cat -e > finalexam
    echo 'sdxssdswdxddddsxaadwxwdxwaa' | ./final 10 6 0 | cat -e >> finalexam
    echo 'dxss' | ./final 3 3 0 | cat -e >> finalexam
    echo 'dxss' | ./final 3 3 1 | cat -e >> finalexam
    echo 'dxss' | ./final 3 3 2 | cat -e >> finalexam
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
        echo "Reminder: expected files in rendu/Life/: *.c *.h" >> traceback
    fi
fi

rm -f finalexam

if [ $index -eq 0 ]; then
    touch passed
fi

{ mv traceback ../../traceback; } &>/dev/null
rm -f sourcexam

cd ../..
