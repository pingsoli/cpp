#!/bin/bash

g++ -std=c++11 -o test.out test.cpp -I/usr/local/boost/include \
  -L/usr/local/boost/lib -lboost_regex
