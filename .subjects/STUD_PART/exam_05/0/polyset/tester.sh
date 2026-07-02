EXERCISE="polyset"
STUDENT_DIR="../../rendu/$EXERCISE"

index=0

if [ -e traceback ]; then
    rm traceback
fi

cd .system/grading

# Compile reference solution
g++ -std=c++11 main.cpp array_bag.cpp tree_bag.cpp searchable_array_bag.cpp searchable_tree_bag.cpp set.cpp -o source 2>/dev/null

# --- 5 test cases covering: mixed, single, duplicates, sorted, reverse ---
./source 5 3 8 1 9 2        | cat -e > sourcexam
./source 42                  | cat -e >> sourcexam
./source 10 10 5 10          | cat -e >> sourcexam
./source 1 2 3 4 5           | cat -e >> sourcexam
./source 9 7 5 3 1           | cat -e >> sourcexam

rm -f source

# Copy infrastructure + main.cpp into student's rendu folder
cp main.cpp "$STUDENT_DIR/"
cp bag.hpp "$STUDENT_DIR/"
cp searchable_bag.hpp "$STUDENT_DIR/"
cp array_bag.hpp "$STUDENT_DIR/"
cp array_bag.cpp "$STUDENT_DIR/"
cp tree_bag.hpp "$STUDENT_DIR/"
cp tree_bag.cpp "$STUDENT_DIR/"

cd ../../rendu

{
    g++ -std=c++11 \
        "$EXERCISE/main.cpp" \
        "$EXERCISE/array_bag.cpp" \
        "$EXERCISE/tree_bag.cpp" \
        "$EXERCISE/searchable_array_bag.cpp" \
        "$EXERCISE/searchable_tree_bag.cpp" \
        "$EXERCISE/set.cpp" \
        -o final
} 2>../.system/grading/traceback

rm -f "$EXERCISE/main.cpp" "$EXERCISE/bag.hpp" "$EXERCISE/searchable_bag.hpp"
rm -f "$EXERCISE/array_bag.hpp" "$EXERCISE/array_bag.cpp"
rm -f "$EXERCISE/tree_bag.hpp" "$EXERCISE/tree_bag.cpp"

if [ -f final ]; then
    ./final 5 3 8 1 9 2        | cat -e > finalexam
    ./final 42                  | cat -e >> finalexam
    ./final 10 10 5 10          | cat -e >> finalexam
    ./final 1 2 3 4 5           | cat -e >> finalexam
    ./final 9 7 5 3 1           | cat -e >> finalexam
    mv finalexam ../.system/grading/
    rm -f final
else
    touch ../.system/grading/finalexam
fi

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
        echo "Reminder: expected files in rendu/polyset/: searchable_array_bag.cpp, searchable_array_bag.hpp, searchable_tree_bag.cpp, searchable_tree_bag.hpp, set.cpp, set.hpp" >> traceback
    fi
fi

rm -f finalexam

if [ $index -eq 0 ]; then
    touch passed
fi

{ mv traceback ../../traceback; } &>/dev/null
rm -f sourcexam
