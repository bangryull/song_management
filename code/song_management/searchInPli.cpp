#define _CRT_SECURE_NO_WARNINGS
#include <iostream>
#include <stdlib.h>
#include <string>
#include <conio.h>
#include "playlist.h"

#define STRING_SIZE 256

using namespace std;

struct Song
{
    char title[STRING_SIZE];
    char singer[STRING_SIZE];
    char composer[STRING_SIZE];
    char lyricist[STRING_SIZE];
    char genre[STRING_SIZE];
    char playtime[STRING_SIZE];
    char album[STRING_SIZE];
    char release[STRING_SIZE];
};

//�˻� �Լ� ����
void searchInPli(char pliName[]);
// �뷡 �˻� �Լ� ����
void searchSongInPli(char* filename, char* searchWord, int* found, char pliName[]);

void searchTagInPli(char pliName[]); //�±� �˻�

void searchZeroInPli(const char* filename, const char* tag, const char* word, char pliName[]);//�±� �˻����� 0 �Է½�

void searchWordOfTagInPli(const char* filename, const char* tag, const char* word, char pliName[]); //�˻��� �˻�

void searchMenuInPli(char pliName[])
{
    int mode;
    int err = 0;

    while (1)
    {
        if (err == 0)
        {
            printf("���ϴ� �޴��� �����ϼ���.\n\n");
        }
        else if (err == 1) {
            printf("\n�ش� �޴��� �������� �ʽ��ϴ�. ");
            printf("�ٽ� �����ϼ���.\n\n");
            err = 0;
        }
        printf("1. ���� �˻�\n");
        printf("2. �±� �˻�\n");
        printf("0. �ڷ� ����\n\n");
        printf("�޴� ���� : ");
        scanf(" %d", &mode);

        switch (mode) {
        case 1: //���� �˻�
            system("cls");
            searchInPli(pliName);
            break;

        case 2: //�±� �˻�
            system("cls");
            searchTagInPli(pliName);
            break;

        case 0: //�ڷ� ����
            return;
            break;

        default: //error
            while (getchar() != '\n'); //�Է� ���� ����
            err = 1;
            break;
        }
    }
}

// �˻� �Լ� ����
void searchInPli(char pliName[]) {
    // �˻��� ���ϸ� ����
    char filename[] = "song_list.txt";
    // �˻��� ���� ���� ����
    char searchWord[STRING_SIZE];
    // �˻� ��� ���θ� ��Ÿ���� ���� �ʱ�ȭ
    int* found = NULL;
    int a = 0;
    *found = a;
    
    // ����ڿ��� �˻��� �Է� ��û
    printf("���� �˻��� �����ϼ̽��ϴ�.\n�˻�� �Է��ϼ���: ");
    // ����ڰ� �˻�� �Է��� ������ �ݺ�
    do {
        // ����ڷκ��� �˻��� �Է� ����
        fgets(searchWord, sizeof(searchWord), stdin);
        // ���� ���� ����
        searchWord[strcspn(searchWord, "\n")] = '\0';
        // �˻� �Լ� ȣ��
        searchSongInPli(filename, searchWord, found, pliName);
        // ���� �˻� ����� ���ٸ� �ٽ� �˻��� �Է� ��û
        if (!found) {
            printf("�ش� �˻���� �������� �ʽ��ϴ�.\n�˻�� �ٽ� �Է��ϼ���: ");
        }
    } while (!found);
    // return 0;
}

// �뷡 �˻� �Լ� ����
void searchSongInPli(char* filename, char* searchWord, int* found, char pliName[])
{
    // ���� ������ ���� �� ���� ���� �õ�
    FILE* file = fopen("song_list.txt", "r");
    FILE* fp = fopen(pliName, "a");
    // ���� ���� ���� �� �޽��� ��� �� ����
    if (file == NULL) {
        printf("������ �� �� �����ϴ�.\n");
        return;
    }

    // �뷡 ������ ������ ����ü �迭 ����
    struct Song song[STRING_SIZE];

    // ���Ϸκ��� ������ �о�� ����ü�� ����
    for (int i = 0; i < STRING_SIZE; i++)
        fscanf(file, "%s %s %s %s %s %s %s %s", &song[i].title, &song[i].singer, &song[i].composer, &song[i].lyricist, &song[i].genre, &song[i].playtime, &song[i].album, &song[i].release);

    // �˻���� ��ġ�ϴ� �뷡 ���� ���
    for (int i = 0; i < STRING_SIZE; i++) {
        if (strstr(song[i].title, searchWord) != NULL ||
            strstr(song[i].singer, searchWord) != NULL ||
            strstr(song[i].composer, searchWord) != NULL ||
            strstr(song[i].lyricist, searchWord) != NULL ||
            strstr(song[i].genre, searchWord) != NULL ||
            strstr(song[i].playtime, searchWord) != NULL ||
            strstr(song[i].album, searchWord) != NULL ||
            strstr(song[i].release, searchWord) != NULL) {

            printf("����: %s/", song[i].title);
            printf("����: %s/", song[i].singer);
            printf("�۰: %s/", song[i].composer);
            printf("�ۻ簡: %s/", song[i].lyricist);
            printf("�帣: %s/", song[i].genre);
            printf("����ð�: %s/", song[i].playtime);
            printf("�ٹ���: %s/", song[i].album);
            printf("�ٹ���ó�¥: %s/", song[i].release);
            printf("\n");
            
            string title = song[i].title;
            string singer = song[i].singer;
            string composer = song[i].composer;
            string lyricist = song[i].lyricist;
            string genre = song[i].genre;
            string playtime = song[i].playtime;
            string album = song[i].album;
            string release = song[i].release;
            string songInfo = "1. " + title + singer + composer + lyricist + genre + playtime + album + release;
            const char* buffer = songInfo.c_str();
            fputs(buffer, fp);
            fputs("\n\n", fp);
             
            *found = 1;
        }
    }
    fclose(fp);
    fclose(file);

    fp = fopen(pliName, "a");
    fileArrange(fp, pliName);
}

void searchTagInPli(char pliName[])
{
    char tag[STRING_SIZE], word[STRING_SIZE];
    int err = 0;
    int goback;
    while (1) {
        system("cls");
        if (err == 0) 
        {
            printf("�±� �˻��� �����ϼ̽��ϴ�.\n");
        }
        else {
            printf("�ش� �˻���� �������� �ʽ��ϴ�.\n");
            err = 0;
        }
        printf("(�±� = ����/����/�۰/�ۻ簡/�帣/����ð�/�ٹ���/�ٹ���ó�¥)\n");
        printf("�˻��� �±׸� �Է��ϼ��� (0 �Է� �� �ڷΰ���) : ");
        scanf("%s", tag);

        if (strcmp(tag, "����") == 0 || strcmp(tag, "����") == 0 || strcmp(tag, "�۰") == 0 || strcmp(tag, "�ۻ簡") == 0 || strcmp(tag, "�帣") == 0 || strcmp(tag, "����ð�") == 0 || strcmp(tag, "�ٹ���") == 0 || strcmp(tag, "�ٹ���ó�¥") == 0)
        {
            printf("�˻�� �Է��ϼ��� (0 �Է� �� �ڷΰ���) : ");

            scanf("%s", word);
            printf("\n");
            if (word[0] == '0') {
                searchZeroInPli("song_list.txt", tag, word, pliName);
                break;
            }
            else {
                // �˻� ��� ���
                searchWordOfTagInPli("song_list.txt", tag, word, pliName);
            }
            break;
        }
        else if (strcmp(tag, "0") == 0) { // �ڷΰ���
            searchMenuInPli(pliName);
            break;
        }
        else { // �߸��Է�
            err = 1;
        }
    }
}

void searchZeroInPli(const char* filename, const char* tag, const char* word, char* pliName) {
    int err = 0;
    int goback = 0;
    while (1) {
        if (err == 0) {
            printf("'0'�� �Է� �ϼ̽��ϴ�. ���� �ڷ� ���ðڽ��ϱ�?\n\n");
        }
        else {
            printf("�߸� �Է� �ϼ̽��ϴ�. �ٽ� �������ּ���.\n\n");
            err = 0;
        }
        printf("1. �ڷΰ���\n");
        printf("2. '0' �˻��ϱ�\n\n");
        printf("�޴����� : ");
        scanf("%d", &goback);
        printf("\n");
        if (goback == 1) {
            searchTagInPli(pliName);
            break;
        }
        else if (goback == 2) { // '0' �˻�
            searchWordOfTagInPli("song_list.txt", tag, word, pliName);
            break;
        }
        else {
            err = 1;
            break;
        }
    }
}

void searchWordOfTagInPli(const char* filename, const char* tag, const char* word, char pliName[]) {
    FILE* file = fopen(filename, "r");
    FILE* fp = fopen(pliName, "a");

    struct Song song;
    char line[STRING_SIZE * 8]; // ���� �� ������ ���̸� �������� ���۸� �Ҵ�
    printf("���� / ���� / �۰ / �ۻ簡 / �帣 / ����ð� / �ٹ��� / �ٹ���ó�¥\n");
    while (fgets(line, sizeof(line), file) != NULL) {
        sscanf(line, "%[^|]|%[^|]|%[^|]|%[^|]|%[^|]|%[^|]|%[^|]|%[^|\n]", song.title, song.singer, song.composer, song.lyricist, song.genre, song.playtime, song.album, song.release);

        if (strcmp(tag, "����") == 0 && strstr(song.title, word) != NULL) {
            printf("%s / %s / %s / %s / %s / %s / %s / %s\n",
                song.title, song.singer, song.composer, song.lyricist, song.genre, song.playtime, song.album, song.release);
            string singer = song.singer;
            string composer = song.composer;
            string lyricist = song.lyricist;
            string genre = song.genre;
            string playtime = song.playtime;
            string album = song.album;
            string release = song.release;
            string songInfo = "1. " + singer + composer + lyricist + genre + playtime + album + release;
            const char* buffer = songInfo.c_str();
            fputs(buffer, fp);
            fputs("\n", fp);
        }
        else if (strcmp(tag, "����") == 0 && strstr(song.singer, word) != NULL) {
            printf("%s / %s / %s / %s / %s / %s / %s / %s\n",
                song.title, song.singer, song.composer, song.lyricist, song.genre, song.playtime, song.album, song.release);
            string singer = song.singer;
            string composer = song.composer;
            string lyricist = song.lyricist;
            string genre = song.genre;
            string playtime = song.playtime;
            string album = song.album;
            string release = song.release;
            string songInfo = "1. " + singer + composer + lyricist + genre + playtime + album + release;
            const char* buffer = songInfo.c_str();
            fputs(buffer, fp);
            fputs("\n", fp);
        }
        else if (strcmp(tag, "�۰") == 0 && strstr(song.composer, word) != NULL) {
            printf("%s / %s / %s / %s / %s / %s / %s / %s\n",
                song.title, song.singer, song.composer, song.lyricist, song.genre, song.playtime, song.album, song.release);
            string singer = song.singer;
            string composer = song.composer;
            string lyricist = song.lyricist;
            string genre = song.genre;
            string playtime = song.playtime;
            string album = song.album;
            string release = song.release;
            string songInfo = "1. " + singer + composer + lyricist + genre + playtime + album + release;
            const char* buffer = songInfo.c_str();
            fputs(buffer, fp);
            fputs("\n", fp);
        }
        else if (strcmp(tag, "�ۻ簡") == 0 && strstr(song.lyricist, word) != NULL) {
            printf("%s / %s / %s / %s / %s / %s / %s / %s\n",
                song.title, song.singer, song.composer, song.lyricist, song.genre, song.playtime, song.album, song.release);
            string singer = song.singer;
            string composer = song.composer;
            string lyricist = song.lyricist;
            string genre = song.genre;
            string playtime = song.playtime;
            string album = song.album;
            string release = song.release;
            string songInfo = "1. " + singer + composer + lyricist + genre + playtime + album + release;
            const char* buffer = songInfo.c_str();
            fputs(buffer, fp);
            fputs("\n", fp);
        }
        else if (strcmp(tag, "�帣") == 0 && strstr(song.genre, word) != NULL) {
            printf("%s / %s / %s / %s / %s / %s / %s / %s\n",
                song.title, song.singer, song.composer, song.lyricist, song.genre, song.playtime, song.album, song.release);
            string singer = song.singer;
            string composer = song.composer;
            string lyricist = song.lyricist;
            string genre = song.genre;
            string playtime = song.playtime;
            string album = song.album;
            string release = song.release;
            string songInfo = "1. " + singer + composer + lyricist + genre + playtime + album + release;
            const char* buffer = songInfo.c_str();
            fputs(buffer, fp);
            fputs("\n", fp);
        }
        else if (strcmp(tag, "����ð�") == 0 && strstr(song.playtime, word) != NULL) {
            printf("%s / %s / %s / %s / %s / %s / %s / %s\n",
                song.title, song.singer, song.composer, song.lyricist, song.genre, song.playtime, song.album, song.release);
            string singer = song.singer;
            string composer = song.composer;
            string lyricist = song.lyricist;
            string genre = song.genre;
            string playtime = song.playtime;
            string album = song.album;
            string release = song.release;
            string songInfo = "1. " + singer + composer + lyricist + genre + playtime + album + release;
            const char* buffer = songInfo.c_str();
            fputs(buffer, fp);
            fputs("\n", fp);
        }
        else if (strcmp(tag, "�ٹ���") == 0 && strstr(song.album, word) != NULL) {
            printf("%s / %s / %s / %s / %s / %s / %s / %s\n",
                song.title, song.singer, song.composer, song.lyricist, song.genre, song.playtime, song.album, song.release);
            string singer = song.singer;
            string composer = song.composer;
            string lyricist = song.lyricist;
            string genre = song.genre;
            string playtime = song.playtime;
            string album = song.album;
            string release = song.release;
            string songInfo = "1. " + singer + composer + lyricist + genre + playtime + album + release;
            const char* buffer = songInfo.c_str();
            fputs(buffer, fp);
            fputs("\n", fp);
        }
        else if (strcmp(tag, "�ٹ���ó�¥") == 0 && strstr(song.release, word) != NULL) {
            printf("%s / %s / %s / %s / %s / %s / %s / %s\n",
                song.title, song.singer, song.composer, song.lyricist, song.genre, song.playtime, song.album, song.release);
            string singer = song.singer;
            string composer = song.composer;
            string lyricist = song.lyricist;
            string genre = song.genre;
            string playtime = song.playtime;
            string album = song.album;
            string release = song.release;
            string songInfo = "1. " + singer + composer + lyricist + genre + playtime + album + release;
            const char* buffer = songInfo.c_str();
            fputs(buffer, fp);
            fputs("\n", fp);
        }
    }
    fclose(fp);
    fclose(file);

    fp = fopen(pliName, "r");
    fileArrange(fp, pliName);

    printf("\n����ȭ������ ���ư����� �ƹ�Ű�� ��������.");
    _getwch(); // �ѱ��� ���͸� �ľ���.
    system("cls");
}