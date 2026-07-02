EXERCISE="vect2"
STUDENT_DIR="../../rendu/$EXERCISE"

index=0

if [ -e traceback ]; then
    rm traceback
fi

cd .system/grading

# Compile reference solution
clang++ -std=c++98 main.cpp vect2.cpp -o source 2>/dev/null
./source | cat -e > sourcexam
rm -f source

# Copy main.cpp into student's rendu folder for compilation
cp main.cpp "$STUDENT_DIR/"

cd ../../rendu

{
    clang++ -std=c++98 "$EXERCISE/main.cpp" "$EXERCISE/vect2.cpp" -o final
} 2>../.system/grading/traceback
rm -f "$EXERCISE/main.cpp"

{
    ./final | cat -e > finalexam
    mv finalexam ../.system/grading/
    rm -f final
} &>/dev/null

cd ../.system/grading

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
        echo "Reminder: you must have vect2.cpp & vect2.hpp in your rendu/vect2/ folder." >> traceback
    fi
fi

rm -f finalexam

if [ $index -eq 0 ]; then
    touch passed
fi

{ mv traceback ../../traceback; } &>/dev/null
rm -f sourcexam
