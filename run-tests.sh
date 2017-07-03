#! /bin/sh

TEST_DIR="tests"
GTEST_OUTPUT_DIR="gtest_results"

if test ! -d $TEST_DIR
then
    echo "Test directory not found."
    exit -1
fi

rm -rf $GTEST_OUTPUT_DIR && mkdir $GTEST_OUTPUT_DIR
echo "Running GTest tests:"
for FILE in $TEST_DIR/*
do
    if test -x $FILE
    then
        echo "    >>>> $FILE <<<<"
        ./$FILE --gtest_output="xml:./$GTEST_OUTPUT_DIR/"
    fi
done
