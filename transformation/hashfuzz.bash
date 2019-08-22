#!/bin/bash

FILE=$1

cat $FILE | grep include > $FILE.header
cat $FILE | grep -v include > $FILE.rest

echo "int _inst_i,_inst_j,_inst_c,_inst_len,_inst_counter=0;" > hashes.txt
echo "int _inst_x_1=$(($RANDOM % 255));" >> hashes.txt
echo "int _inst_x_2=$(($RANDOM % 255));" >> hashes.txt
echo "int _inst_x_3=$(($RANDOM % 255));" >> hashes.txt

if  grep -q data $FILE; then
    DATA="data";
elif grep -q Data $FILE; then
    DATA="Data";
else
    echo "Error"
fi

if grep -q size $FILE; then
    SIZE="size";
elif grep -q Size $FILE; then
    SIZE="Size";
else
    echo "Error"
fi

if grep -q main $FILE; then
    ENTRY="main";
elif grep -q LLVMFuzzer $FILE; then
    ENTRY="LLVMFuzzer";
else
    echo "Error"
fi
echo $ENTRY
sed "/$ENTRY/q" $FILE.rest > $FILE.restT
sed "1,/$ENTRY/d" $FILE.rest > $FILE.restB

echo " if ($SIZE == -1) { \
    printf(\"Failed to read from stdin\n\"); \
    return(-1); \
  } \
  int _inst_h_1=0,_inst_h_2=0,_inst_h_3=0; \
  for(int _inst_a =0; _inst_a < $SIZE; _inst_a++) \
    { \
      _inst_h_1=(_inst_h_1 + findParity(_inst_x_1&$DATA[_inst_a]))%2; \
      _inst_h_2=(_inst_h_2 + findParity(_inst_x_2&$DATA[_inst_a]))%2; \
      _inst_h_3=(_inst_h_3 + findParity(_inst_x_3&$DATA[_inst_a]))%2; \
    } \
  if(_inst_h_1==0) \
    _inst_counter++; \
  else \
    _inst_counter++; \
  if(_inst_h_2==0) \
    _inst_counter++; \
  else \
    _inst_counter++; \
  if(_inst_h_3==0) \
    _inst_counter++; \
  else \
    _inst_counter++; \
" >> hashes.txt

cat $FILE.header extraFunc.c $FILE.restT hashes.txt $FILE.restB > $FILE.hash.cc
