#!/bin/bash

cd ../build
# refresh the project when modifying
if [[ -n $1 && $1 = "r" ]]; then
  rm -rf *
  cmake ../src
fi

if ! make; then
  exit 1
fi

cd ../bin
./main
