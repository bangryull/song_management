#pragma once

void searchMenuInPli(char pliName[]);

void searchInPli(char pliName[]);
// 노래 검색 함수 선언
void searchSongInPli(char* filename, char* searchWord, int* found, char pliName[]);

void searchTagInPli(char pliName[]); //태그 검색

void searchZeroInPli(const char* filename, const char* tag, const char* word);//태그 검색에서 0 입력시

void searchWordOfTagInPli(const char* filename, const char* tag, const char* word, char pliName[]); //검색어 검색

