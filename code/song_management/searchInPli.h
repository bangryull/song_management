#pragma once

void searchMenuInPli(char pliName[]);

void searchInPli(char pliName[]);
// �뷡 �˻� �Լ� ����
void searchSongInPli(char* filename, char* searchWord, int* found, char pliName[]);

void searchTagInPli(char pliName[]); //�±� �˻�

void searchZeroInPli(const char* filename, const char* tag, const char* word);//�±� �˻����� 0 �Է½�

void searchWordOfTagInPli(const char* filename, const char* tag, const char* word, char pliName[]); //�˻��� �˻�

