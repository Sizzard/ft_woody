#!/bin/bash

if [ "$#" -lt 1 ]
then
  echo "No arguments supplied"
  exit 1
fi

objcopy -O binary -j .text $1 binary

od -An -v -t x1 binary > binary.tmp

cat binary.tmp | sed -e 's/ /, 0x/g'

rm binary binary.tmp