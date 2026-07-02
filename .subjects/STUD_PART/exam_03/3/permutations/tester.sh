FILE='permutations.c'
ASSIGN='permutations'

# Test 1: no arguments (should fail - no output or return error)
bash .system/auto_correc_program.sh $FILE $ASSIGN
if [ -e .system/grading/traceback ];then
    mv .system/grading/traceback .
	exit 1
fi

# Test 2: single character (should give exactly 1 permutation: "a\n")
bash .system/auto_correc_program.sh $FILE $ASSIGN "a"
if [ -e .system/grading/traceback ];then
    mv .system/grading/traceback .
	exit 1
fi

# Test 3: two characters (should give exactly 2 permutations in alphabetical order)
bash .system/auto_correc_program.sh $FILE $ASSIGN "ab"
if [ -e .system/grading/traceback ];then
    mv .system/grading/traceback .
	exit 1
fi

# Test 4: three characters (should give exactly 6 permutations)
bash .system/auto_correc_program.sh $FILE $ASSIGN "abc"
if [ -e .system/grading/traceback ];then
    mv .system/grading/traceback .
	exit 1
fi

# Test 5: four characters (should give exactly 24 permutations)
bash .system/auto_correc_program.sh $FILE $ASSIGN "abcd"
if [ -e .system/grading/traceback ];then
    mv .system/grading/traceback .
	exit 1
fi

# Test 6: different characters test alphabetical order strictly
bash .system/auto_correc_program.sh $FILE $ASSIGN "xyz"
if [ -e .system/grading/traceback ];then
    mv .system/grading/traceback .
	exit 1
fi

# Test 7: five characters (should give exactly 120 permutations - performance test)
bash .system/auto_correc_program.sh $FILE $ASSIGN "abcde"
if [ -e .system/grading/traceback ];then
    mv .system/grading/traceback .
	exit 1
fi

# Test 8: six characters (should give exactly 720 permutations - harder performance)
bash .system/auto_correc_program.sh $FILE $ASSIGN "abcdef"
if [ -e .system/grading/traceback ];then
    mv .system/grading/traceback .
	exit 1
fi

# Test 9: seven characters (should give exactly 5040 permutations - stress test)
bash .system/auto_correc_program.sh $FILE $ASSIGN "abcdefg"
if [ -e .system/grading/traceback ];then
    mv .system/grading/traceback .
	exit 1
fi

# Test 10: reverse order input (should still output in alphabetical order)
bash .system/auto_correc_program.sh $FILE $ASSIGN "cba"
if [ -e .system/grading/traceback ];then
    mv .system/grading/traceback .
	exit 1
fi

# Test 11: non-consecutive characters (test ordering)
bash .system/auto_correc_program.sh $FILE $ASSIGN "ace"
if [ -e .system/grading/traceback ];then
    mv .system/grading/traceback .
	exit 1
fi

# Test 12: mixed case and special (if implementation handles it)
bash .system/auto_correc_program.sh $FILE $ASSIGN "zyx"
if [ -e .system/grading/traceback ];then
    mv .system/grading/traceback .
	exit 1
fi

# Test 13: longer string starting with different letter
bash .system/auto_correc_program.sh $FILE $ASSIGN "wxyz"
if [ -e .system/grading/traceback ];then
    mv .system/grading/traceback .
	exit 1
fi

# Test 14: empty string (edge case - should fail or no output)
bash .system/auto_correc_program.sh $FILE $ASSIGN ""
if [ -e .system/grading/traceback ];then
    mv .system/grading/traceback .
	exit 1
fi

# Test 15: multiple arguments (should fail)
bash .system/auto_correc_program.sh $FILE $ASSIGN "abc" "def"
if [ -e .system/grading/traceback ];then
    mv .system/grading/traceback .
	exit 1
fi

# Test 16: three arguments (should fail)
bash .system/auto_correc_program.sh $FILE $ASSIGN "a" "b" "c"
if [ -e .system/grading/traceback ];then
    mv .system/grading/traceback .
	exit 1
fi

# Test 17: single character different from 'a'
bash .system/auto_correc_program.sh $FILE $ASSIGN "z"
if [ -e .system/grading/traceback ];then
    mv .system/grading/traceback .
	exit 1
fi

# Test 18: two characters reversed
bash .system/auto_correc_program.sh $FILE $ASSIGN "ba"
if [ -e .system/grading/traceback ];then
    mv .system/grading/traceback .
	exit 1
fi

# Test 19: performance and correctness with 8 chars (40320 permutations)
bash .system/auto_correc_program.sh $FILE $ASSIGN "abcdefgh"
if [ -e .system/grading/traceback ];then
    mv .system/grading/traceback .
	exit 1
fi

# Test 20: numbers as characters (if accepted)
bash .system/auto_correc_program.sh $FILE $ASSIGN "123"
if [ -e .system/grading/traceback ];then
    mv .system/grading/traceback .
	exit 1
fi

touch .system/grading/passed;

