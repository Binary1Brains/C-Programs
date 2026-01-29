#!/bin/sh

if [ $# -eq 0 ]; then
    echo "Usage: ./build.sh <filename.c/cpp>"
    exit 1
fi

file="$1"
base=$(basename "$file")
name="${base%.*}"
ext="${base##*.}"
output="${name}.out"

if [ "$ext" = "c" ]; then
    compiler="clang"
elif [ "$ext" = "cpp" ]; then
    compiler="clang++"
else
  echo " :( Unsupported file type: .$ext"
    exit 1
fi

libs=""
if grep -q "#include <math.h>" "$file"; then
    libs="$libs -lm"
fi
if grep -q "#include <pthread.h>" "$file"; then
    libs="$libs -pthread"
fi
if grep -q "#include <curl/curl.h>" "$file"; then 
    libs="$libs -lcurl"
fi

if [ -f "$output" ] && [ "$output" -nt "$file" ]; then
  echo " :< No changes detected — running existing build."
else
    echo " :> Compiling $file with $compiler..."
    $compiler -Wall -Wextra "$file" -o "$output" $libs
    if [ $? -ne 0 ]; then
      echo ":-( Compilation failed"
        exit 1
    fi
    echo ":) Compilation successful"
fi

# Run the executable
echo "-----------------------------------------"
"./$output"
echo "-----------------------------------------"
