#!/bin/bash

# Get directory of this script
currentDir=$(dirname $(readlink -f $0))

# Run all tests and safe the results in a file
cd $currentDir/build/
./networktester --gtest_filter=Forwarding_* --gtest_output=json:$currentDir/results_forwarding.json
./networktester --gtest_filter=Fragmentation_* --gtest_output=json:$currentDir/results_Fragmentation.json
./networktester --gtest_filter=General_* --gtest_output=json:$currentDir/results_general.json
