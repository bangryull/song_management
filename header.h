#pragma once
#define _CRT_SECURE_NO_WARNINGS	
#define STRING_SIZE 256
#include <stdio.h>
#include <string.h>
#include <wchar.h>
#include <ctype.h>
#include <time.h>
#include <Windows.h>

struct Artist { //����, �۰, �ۻ簡 -> ��Ƽ��Ʈ�� ����
    char name[STRING_SIZE];     //��Ƽ��Ʈ �̸�
    clock_t Key;                //Key��(�ð�)
};

struct Song { //����ü
    char title[STRING_SIZE];    //����
    struct Artist singer;       //����
    struct Artist composer;     //�۰
    struct Artist lyricist;     //�ۻ簡
    char genre[STRING_SIZE];    //�帣
    char playtime[STRING_SIZE]; //����ð�
    char album[STRING_SIZE];    //�ٹ���
    char release[STRING_SIZE];  //�ٹ���ó�¥
};


void song_list_menu();//�뷡 ����Ʈ �� �޴�

void add_song();//�뷡 ����Ʈ �޴����� �뷡 �߰��ϱ�



void playlistMenu();//�÷��̸���Ʈ ȭ�鿡 ó�� ���� ��

void printPlaylist();//�÷��̸���Ʈ�� ����Ʈ�� ���

void addPlaylist();//�÷��̸���Ʈ �߰�

void deletePlaylist();//�÷��̸���Ʈ ����

void openPlaylist(char* playlistName);//�÷��̸���Ʈ ����

void addSong();//�÷��̸���Ʈ�� �뷡 �߰�

void deleteSong();//�÷��̸���Ʈ�� �뷡 ����