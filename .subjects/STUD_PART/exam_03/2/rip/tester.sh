FILE='rip.c'
ASSIGN='rip'

# Test 1: no arguments (should fail or no output)
bash .system/auto_correc_program.sh $FILE $ASSIGN
if [ -e .system/grading/traceback ];then
    mv .system/grading/traceback .
	exit 1
fi

# Test 2: simple balanced pair (should output exactly: "()")
bash .system/auto_correc_program.sh $FILE $ASSIGN "()"
if [ -e .system/grading/traceback ];then
    mv .system/grading/traceback .
	exit 1
fi

# Test 3: balanced with spaces (should output exactly same string)
bash .system/auto_correc_program.sh $FILE $ASSIGN "( ( ( ) ( ) ( ) ) ( ) )"
if [ -e .system/grading/traceback ];then
    mv .system/grading/traceback .
	exit 1
fi

# Test 4: simple unbalanced - extra closing (should give 1 solution)
bash .system/auto_correc_program.sh $FILE $ASSIGN "())"
if [ -e .system/grading/traceback ];then
    mv .system/grading/traceback .
	exit 1
fi

# Test 5: case from subject '( ( )' (should give 2 solutions)
bash .system/auto_correc_program.sh $FILE $ASSIGN "( ( )"
if [ -e .system/grading/traceback ];then
    mv .system/grading/traceback .
	exit 1
fi

# Test 6: case from subject '( ) ( ) ) ( )' (should give 3 solutions)
bash .system/auto_correc_program.sh $FILE $ASSIGN "( ) ( ) ) ( )"
if [ -e .system/grading/traceback ];then
    mv .system/grading/traceback .
	exit 1
fi

# Test 7: case from subject '( ( ) ( ( ) (' (should give 5 solutions)
bash .system/auto_correc_program.sh $FILE $ASSIGN "( ( ) ( ( ) ("
if [ -e .system/grading/traceback ];then
    mv .system/grading/traceback .
	exit 1
fi

# Test 8: only closing parenthesis
bash .system/auto_correc_program.sh $FILE $ASSIGN "))"
if [ -e .system/grading/traceback ];then
    mv .system/grading/traceback .
	exit 1
fi

# Test 9: only opening parenthesis
bash .system/auto_correc_program.sh $FILE $ASSIGN "(("
if [ -e .system/grading/traceback ];then
    mv .system/grading/traceback .
	exit 1
fi

# Test 10: complex nested balanced
bash .system/auto_correc_program.sh $FILE $ASSIGN "((()))"
if [ -e .system/grading/traceback ];then
    mv .system/grading/traceback .
	exit 1
fi

# Test 11: single opening parenthesis
bash .system/auto_correc_program.sh $FILE $ASSIGN "("
if [ -e .system/grading/traceback ];then
    mv .system/grading/traceback .
	exit 1
fi

# Test 12: single closing parenthesis
bash .system/auto_correc_program.sh $FILE $ASSIGN ")"
if [ -e .system/grading/traceback ];then
    mv .system/grading/traceback .
	exit 1
fi

# Test 13: empty string (edge case)
bash .system/auto_correc_program.sh $FILE $ASSIGN ""
if [ -e .system/grading/traceback ];then
    mv .system/grading/traceback .
	exit 1
fi

# Test 14: multiple arguments (should fail)
bash .system/auto_correc_program.sh $FILE $ASSIGN "()" "()"
if [ -e .system/grading/traceback ];then
    mv .system/grading/traceback .
	exit 1
fi

# Test 15: alternating unbalanced
bash .system/auto_correc_program.sh $FILE $ASSIGN ")()("
if [ -e .system/grading/traceback ];then
    mv .system/grading/traceback .
	exit 1
fi

touch .system/grading/passed;

