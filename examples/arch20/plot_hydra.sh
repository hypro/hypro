#!/bin/bash

# Runs gnuplot on .plt files in created by hydra and converts the pdf files
# to png. The plots are written in the input directory.
# Arguments:
#   Input directory: directory containing the .plt files.
# Example call:
#   ./plot_hydra.sh .

if [ ! -d "$1" ]; then
  echo "Usage: $0 directory"
  exit
fi

for e in "$1"/*pdf.plt; do
  BASE=`basename "$e" "_pdf.plt"`
  echo "[+] Plotting $BASE"
  gnuplot "$e"
  pdftoppm "$BASE.pdf" "$1/$BASE" -png
  rm "$BASE.pdf"
done
