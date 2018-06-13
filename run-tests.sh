#! /bin/sh

TESTBIN_DIR="test/bin"
GTEST_OUTPUT_DIR="gtest_results"
BOLD_PURPLE="\033[1;35m"
BOLD_RED="\033[1;31m"
NORMAL="\033[0m"

echo ""

if test ! -d $TEST_DIR
then
    echo "${BOLD_RED}Test directory not found.${NORMAL}"
    exit -1
fi

rm -rf $GTEST_OUTPUT_DIR && mkdir $GTEST_OUTPUT_DIR
echo "${BOLD_PURPLE}Running GTest tests:${NORMAL}"

for FILE in $TESTBIN_DIR/*
do
    echo "\n${BOLD_PURPLE}    >>>> $(basename $FILE) <<<<${NORMAL}"
    ./$FILE --gtest_output="xml:./$GTEST_OUTPUT_DIR/"
done

echo ""
