Huffman coding is a lossless data compression algorithm. In this algorithm, a variable-length code is assigned to input different characters. The code length is related to how frequently characters are used. Most frequent characters have the smallest codes and longer codes for least frequent characters.

To compile, simply type: g++ huff.cpp

The default message that will be compressed is "hello world". You can change it to any other valid string for the variable "str". The output will display the character's frequencies and their respective codes. The initial string will also be displayed as the decompressed message.