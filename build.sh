#!/bin/bash

OUT=app.wast
IN=main.cpp

eosiocpp -o $OUT $IN
ls *.wast
