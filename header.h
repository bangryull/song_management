#pragma once
#define _CRT_SECURE_NO_WARNINGS	
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <wchar.h>
#include <ctype.h>
#include <time.h>
#include <Windows.h>

void song_list_menu();//노래 리스트 주 메뉴

void song_list_print();//노래 리스트 출력

void song_add();//노래 추가

void song_dlt(char* filename);//노래 삭제

void search();// 노래 검색 함수 선언

void searchSong(char* filename, char* searchWord, int found);

void searchTag(); //태그 검색

void searchZero();//태그 검색에서 0 입력시

void searchWordOfTag(const char *filename, const char *tag, const char *word); //검색어 검색

void playlistMenu();//플레이리스트 화면에 처음 들어갔을 때

void printPlaylist();//플레이리스트이 리스트를 출력

void addPlaylist();//플레이리스트 추가

void deletePlaylist();//플레이리스트 삭제

void openPlaylist(char* playlistName);//플레이리스트 열기

void addSong();//플레이리스트에 노래 추가

void deleteSong();//플레이리스트의 노래 삭제
