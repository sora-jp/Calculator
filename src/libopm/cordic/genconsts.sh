#!/bin/bash

rm -rf ./constants
mkdir constants
cd constants
touch ln.txt
touch atan.txt
sollya < ../genconsts_sollya.sol
cd ..