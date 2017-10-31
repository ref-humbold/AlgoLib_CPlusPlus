#! /bin/sh

TESTBIN_DIR="test/bin"
GTEST_OUTPUT_DIR="gtest_results"

if test ! -d $TESTBIN_DIR
then
    echo "\033[0;31mTest directory not found.\033[0m"
    exit -1
fi

rm -rf $GTEST_OUTPUT_DIR && mkdir $GTEST_OUTPUT_DIR
echo "\033[1;35mRunning GTest tests:\033[0m"
for FILE in $TESTBIN_DIR/*
do
    echo ""
    echo "\033[1;35m    >>>> $FILE <<<<\033[0m"
    ./$FILE --gtest_output="xml:./$GTEST_OUTPUT_DIR/"
done
