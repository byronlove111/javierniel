FILE='nqueens.c'
ASSIGN='nqueens'

# Test 1: no arguments
bash .system/auto_correc_program.sh $FILE $ASSIGN
if [ -e .system/grading/traceback ];then
    mv .system/grading/traceback .
	exit 1
fi

# Test 2: n=1 (should give 1 solution: 0)
bash .system/auto_correc_program.sh $FILE $ASSIGN "1"
if [ -e .system/grading/traceback ];then
    mv .system/grading/traceback .
	exit 1
fi

# Test 3: n=2 (no solution - impossible)
bash .system/auto_correc_program.sh $FILE $ASSIGN "2"
if [ -e .system/grading/traceback ];then
    mv .system/grading/traceback .
	exit 1
fi

# Test 4: n=3 (no solution - impossible)
bash .system/auto_correc_program.sh $FILE $ASSIGN "3"
if [ -e .system/grading/traceback ];then
    mv .system/grading/traceback .
	exit 1
fi

# Test 5: n=4 (should give exactly 2 solutions)
bash .system/auto_correc_program.sh $FILE $ASSIGN "4"
if [ -e .system/grading/traceback ];then
    mv .system/grading/traceback .
	exit 1
fi

# Test 6: n=5 (should give exactly 10 solutions)
bash .system/auto_correc_program.sh $FILE $ASSIGN "5"
if [ -e .system/grading/traceback ];then
    mv .system/grading/traceback .
	exit 1
fi

# Test 7: n=6 (should give exactly 4 solutions)
bash .system/auto_correc_program.sh $FILE $ASSIGN "6"
if [ -e .system/grading/traceback ];then
    mv .system/grading/traceback .
	exit 1
fi

# Test 8: n=7 (should give exactly 40 solutions)
bash .system/auto_correc_program.sh $FILE $ASSIGN "7"
if [ -e .system/grading/traceback ];then
    mv .system/grading/traceback .
	exit 1
fi

# Test 9: n=8 (should give exactly 92 solutions)
bash .system/auto_correc_program.sh $FILE $ASSIGN "8"
if [ -e .system/grading/traceback ];then
    mv .system/grading/traceback .
	exit 1
fi

# Test 10: n=9 (should give exactly 352 solutions - performance test)
bash .system/auto_correc_program.sh $FILE $ASSIGN "9"
if [ -e .system/grading/traceback ];then
    mv .system/grading/traceback .
	exit 1
fi

# Test 11: n=0 (edge case)
bash .system/auto_correc_program.sh $FILE $ASSIGN "0"
if [ -e .system/grading/traceback ];then
    mv .system/grading/traceback .
	exit 1
fi

# Test 12: multiple arguments (should fail)
bash .system/auto_correc_program.sh $FILE $ASSIGN "4" "5"
if [ -e .system/grading/traceback ];then
    mv .system/grading/traceback .
	exit 1
fi

touch .system/grading/passed;

