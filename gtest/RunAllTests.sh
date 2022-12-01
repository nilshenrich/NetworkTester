#!/bin/bash

# Get directory of this script
currentDir=$(dirname $(readlink -f $0))

# Is any test failed?
failed=false

# Run all tests and safe the results in a file
cd $currentDir/build/
./networktester --gtest_filter=Forwarding_* --gtest_output=json:$currentDir/results_forwarding.json
ret=$?
if [ $ret -ne 0 ]
then
    failed=true
fi
./networktester --gtest_filter=Fragmentation_* --gtest_output=json:$currentDir/results_Fragmentation.json
ret=$?
if [ $ret -ne 0 ]
then
    failed=true
fi
./networktester --gtest_filter=General_* --gtest_output=json:$currentDir/results_general.json
ret=$?
if [ $ret -ne 0 ]
then
    failed=true
fi

if [ "$failed" = true ]
then
    exit -1
fi
