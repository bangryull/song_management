#pragma once
#define _CRT_SECURE_NO_WARNINGS	
#define STRING_SIZE 256
#include <stdio.h>
#include <string.h>
#include <wchar.h>
#include <ctype.h>
#include <time.h>
#include <Windows.h>

struct Artist { //가수, 작곡가, 작사가 -> 아티스트로 묶기
    char name[STRING_SIZE];     //아티스트 이름
    clock_t Key;                //Key값(시간)
};

struct Song { //구조체
    char title[STRING_SIZE];    //제목
    struct Artist singer;       //가수
    struct Artist composer;     //작곡가
    struct Artist lyricist;     //작사가
    char genre[STRING_SIZE];    //장르
    char playtime[STRING_SIZE]; //재생시간
    char album[STRING_SIZE];    //앨범명
    char release[STRING_SIZE];  //앨범출시날짜
};


void song_list_menu();//노래 리스트 주 메뉴

void add_song();//노래 리스트 메뉴에서 노래 추가하기



void playlistMenu();//플레이리스트 화면에 처음 들어갔을 때

void printPlaylist();//플레이리스트이 리스트를 출력

void addPlaylist();//플레이리스트 추가

void deletePlaylist();//플레이리스트 삭제

void openPlaylist(char* playlistName);//플레이리스트 열기

void addSong();//플레이리스트에 노래 추가

void deleteSong();//플레이리스트의 노래 삭제