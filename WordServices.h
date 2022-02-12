/* Slayter Teal
A file containing access to various helper methods 
related to checking words and other... word related things.
*/

#ifndef WORDSERVICES_H_
#define WORDSERVICES_H_

int isValidWord(char *inputWord, char **usedWords, int usedSize, int inputFileNumber);
int isValidDict(char *inputWord);
int isUsedWord(char *inputWord, char **usedWords, int usedLength);
int isKnown(int inputNumber, char *inputword);
char *generateWord(int inputFileNumber);
char **addToUsed(char **usedWords, char *inputWord, int usedSize);
void addToInput(int inputNumber, char *inputWord);

#endif