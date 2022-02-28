/**
 * @file WordServices.h
 * @author Jackson Wildman (jawildm@okstate.edu)
 * @brief Group D
 * @date 2022-02-27
 * 
 */

#ifndef WORDSERVICES_H_
#define WORDSERVICES_H_

int isValidWord(char *inputWord, int inputSize, char ***usedWords, int *usedSize, char *inputFileName);
int isValidDict(char *inputWord);
int isUsedWord(char *inputWord, char **usedWords, int usedLength);
int isKnown(char *inputFileName, char *inputword);
char *generateWord(char *inputFileName);
char **addToUsed(char **usedWords, char *inputWord, int usedSize);
void addToInput(char *inputFileName, char *inputWord);
char *toLowerStr(char *inputWord, int inputSize);
char *getRandomAlphabet(char *input_txt);

#endif
