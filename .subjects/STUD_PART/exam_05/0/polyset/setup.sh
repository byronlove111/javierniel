#!/bin/bash
STUDENT_DIR="rendu/polyset"

mkdir -p "$STUDENT_DIR"
cp .system/grading/bag.hpp             "$STUDENT_DIR/"
cp .system/grading/searchable_bag.hpp  "$STUDENT_DIR/"
cp .system/grading/array_bag.hpp       "$STUDENT_DIR/"
cp .system/grading/array_bag.cpp       "$STUDENT_DIR/"
cp .system/grading/tree_bag.hpp        "$STUDENT_DIR/"
cp .system/grading/tree_bag.cpp        "$STUDENT_DIR/"
cp .system/grading/main.cpp            "$STUDENT_DIR/"
