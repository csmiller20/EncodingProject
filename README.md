# EncodingProject
This project creates an executable that encodes a file to binary and an executable that decodes that file.
The insertion argument can be replaced with "merge" and vice versa to merge/insertion sort the characters in the file.

Command Line Steps:
  make
  preprocess < file.txt > prefile.txt
  encode prefile.txt insertion < file.txt > encoded-file.txt
  decode prefile.txt merge < encoded-file.txt > decoded-file.txt
  
The decoded file should look exactly the same as the original file, but only uses info from the encoded file when created.
