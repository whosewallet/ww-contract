#!/bin/bash

OUT=main.wast
IN=main.cpp

eosiocpp -o $OUT $IN
ls *.wast
