#define _CRT_SECURE_NO_WARNINGS
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <conio.h>
#include "playlist.h"

#define STRING_SIZE 256

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

//검색 함수 선언
void searchInPli(char pliName[]);
// 노래 검색 함수 선언
int searchSongInPli(char* filename, char* searchWord, int found, char pliName[]);

void searchTagInPli(char pliName[]); //태그 검색

void searchZeroInPli(const char* filename, const char* tag, const char* word, char pliName[]);//태그 검색에서 0 입력시

void searchWordOfTagInPli(const char* tag, const char* word, char pliName[]); //검색어 검색

void searchMenuInPli(char pliName[])
{
    int mode;
    int err = 0;
    char input[STRING_SIZE];
    while (1)
    {
        if (err == 0)
        {
            printf("원하는 메뉴를 선택하세요.\n\n");
        }
        else if (err == 1) {
            printf("\n해당 메뉴는 존재하지 않습니다. ");
            printf("다시 선택하세요.\n\n");
            err = 0;
        }
        printf("1. 통합 검색\n");
        printf("2. 태그 검색\n");
        printf("0. 뒤로 가기\n\n");
        printf("메뉴 선택 : ");
        fgets(input, sizeof(input), stdin);
        input[strcspn(input, "\n")] = '\0'; // 엔터키 제거
        sscanf(input, "%d", &mode);


        switch (mode) {
        case 1: //통합 검색
            system("cls");
            searchInPli(pliName);
            break;

        case 2: //태그 검색
            system("cls");
            searchTagInPli(pliName);
            break;

        case 0: //뒤로 가기
            return 0;
            break;

        default: //error
            while (getchar() != '\n'); //입력 버퍼 비우기
            err = 1;
            break;
        }
    }
}

// 검색 함수 정의
void searchInPli(char pliName[]) {
    char input[STRING_SIZE] = { 0, };
    // 검색할 파일명 지정
    char filename[] = "song_list.txt";
    // 검색어 저장 변수 선언
    char searchWord[STRING_SIZE];
    // 검색 결과 여부를 나타내는 변수 초기화
    int found = 0;
    // 사용자에게 검색어 입력 요청
    printf("통합 검색을 선택하셨습니다.\n검색어를 입력하세요 (0 입력 시 뒤로가기): ");
    // 사용자가 검색어를 입력할 때까지 반복
    do {
        // 사용자로부터 검색어 입력 받음
        fgets(input, sizeof(input), stdin);
        input[strcspn(input, "\n")] = '\0'; // 엔터키 제거
        sscanf(input, "%s", searchWord);

        if (searchWord[0] == '0') {
            searchMenuInPli(pliName);
            break;
        }
        else {
            // 검색 결과 출력
            found = searchSongInPli(filename, searchWord, found, pliName);
        }
        // 만약 검색 결과가 없다면 다시 검색어 입력 요청
        if (found == 0)
            printf("해당 검색어는 존재하지 않습니다.\n검색어를 다시 입력하세요: ");
    } while (found == 0);
}

// 노래 검색 함수 정의
int searchSongInPli(char* filename, char* searchWord, int found, char pliName[])
{
    // 파일 포인터 선언 및 파일 열기 시도
    FILE* file = fopen("song_list.txt", "r");
    FILE* fp = fopen(pliName, "a");
    // 파일 열기 실패 시 메시지 출력 후 종료
    if (file == NULL) {
        printf("파일을 열 수 없습니다.\n");
        return 0;
    }

    // 노래 정보를 저장할 구조체 배열 선언
    found = 0;
    struct Song song;
    char line[STRING_SIZE * 8]; // 가장 긴 라인의 길이를 기준으로 버퍼를 할당
   /* while (fgets(line, sizeof(line), file) != NULL) {
        sscanf(line, "%[^\t]\t%[^\t]\t%[^\t]\t%[^\t]\t%[^\t]\t%[^\t]\t%[^\t]\t%[^\t\n]", song.title, song.singer, song.composer, song.lyricist, song.genre, song.playtime, song.album, song.release);

        if (strstr(song.title, searchWord) != NULL || strstr(song.singer, searchWord) != NULL ||
            strstr(song.composer, searchWord) != NULL || strstr(song.lyricist, searchWord) != NULL ||
            strstr(song.genre, searchWord) != NULL || strstr(song.playtime, searchWord) != NULL ||
            strstr(song.album, searchWord) != NULL || strstr(song.release, searchWord) != NULL) {
            printf("제목 / 가수 / 작곡가 / 작사가 / 장르 / 재생시간 / 앨범명 / 앨범출시날짜\n");
            printf("%s / %s / %s / %s / %s / %s / %s / %s\n",
                song.title, song.singer, song.composer, song.lyricist, song.genre, song.playtime, song.album, song.release);
            found = 1;

            fputs(line, fp);
        }
    }*/
    printf("제목 / 가수 / 작곡가 / 작사가 / 장르 / 재생시간 / 앨범명 / 앨범출시날짜\n");
    while (fgets(line, sizeof(line), file) != NULL) {
        sscanf(line, "%[^\t]\t%[^\t]\t%[^\t]\t%[^\t]\t%[^\t]\t%[^\t]\t%[^\t]\t%[^\t\n]", song.title, song.singer, song.composer, song.lyricist, song.genre, song.playtime, song.album, song.release);
        if (strstr(song.title, searchWord) != NULL || strstr(song.singer, searchWord) != NULL ||
            strstr(song.composer, searchWord) != NULL || strstr(song.lyricist, searchWord) != NULL ||
            strstr(song.genre, searchWord) != NULL || strstr(song.playtime, searchWord) != NULL ||
            strstr(song.album, searchWord) != NULL || strstr(song.release, searchWord) != NULL) {

            printf("%s / ", song.title);
            printf("%s / ", song.singer);
            printf("%s / ", song.composer);
            printf("%s / ", song.lyricist);
            int k = strlen(song.title) + strlen(song.singer) + strlen(song.composer) + strlen(song.lyricist) + 4; //공란 예외 처리
            for (k; k < strlen(line); k++) {
                if (line[k] == '\t')
                    printf(" / ");
                else
                    printf("%c", line[k]);
            }
            // printf("%s / %s / %s / %s / %s / %s / %s / %s\n",
            //     song.title, song.singer, song.composer, song.lyricist, song.genre, song.playtime, song.album, song.release);
            fputs("\n", fp);
            fputs(line, fp);
            found = 1;
        }
    }
    fclose(file);
    fclose(fp);
    return found;
}

void searchTagInPli(char pliName[])
{
    char tag[STRING_SIZE], word[STRING_SIZE], input[STRING_SIZE];
    int err = 0;
    int goback;

    while (1) {
        // system("cls");
        if (err == 0) {
            printf("태그 검색을 선택하셨습니다.\n");
        }
        else {
            printf("해당 태그는 존재하지 않습니다.\n");
            err = 0;
        }
        printf("(태그 = 제목/가수/작곡가/작사가/장르/재생시간/앨범명/앨범출시날짜)\n");
        printf("검색할 태그를 입력하세요 (0 입력 시 뒤로가기) : ");
        if (fgets(input, sizeof(input), stdin) != NULL) {
            input[strcspn(input, "\n")] = '\0'; // 엔터키 제거
            sscanf(input, "%s", tag);
        }

        if (strcmp(tag, "제목") == 0 || strcmp(tag, "가수") == 0 || strcmp(tag, "작곡가") == 0 || strcmp(tag, "작사가") == 0 || strcmp(tag, "장르") == 0 || strcmp(tag, "재생시간") == 0 || strcmp(tag, "앨범명") == 0 || strcmp(tag, "앨범출시날짜") == 0) {
            printf("검색어를 입력하세요 (0 입력 시 뒤로가기) : ");
            do {
                printf("검색어를 입력하세요 (0 입력 시 뒤로가기) : ");

                if (fgets(input, sizeof(input), stdin) != NULL) {
                    input[strcspn(input, "\n")] = '\0'; // 엔터키 제거
                    sscanf(input, "%s", word);
                }

                printf("\n");

                if (word[0] == '0') {
                    searchMenuInPli(pliName);
                    break;
                }
                else if (searchWordExistInPli(tag, word) == 0) { // 검색어가 존재하지 않으면
                    printf("해당 검색어는 존재하지 않습니다.\n");
                    printf("(태그 = 제목/가수/작곡가/작사가/장르/재생시간/앨범명/앨범출시날짜)\n");
                    printf("검색할 태그를 입력하세요 (0 입력 시 뒤로가기) : %s\n", tag);
                }
                else {
                    // 검색 결과 출력
                    searchWordOfTagInPli(tag, word, pliName);
                    break;
                }
            } while (1);
            break;
        }
        else if (strcmp(tag, "0") == 0) { // 뒤로가기
            searchMenuInPli(pliName);
            break;
        }
        else { // 잘못 입력
            err = 1;
        }
    }

}

int searchWordExistInPli(const char* tag, const char* word) {//검색어가 존재하는지
    FILE* file = fopen("song_list.txt", "r");

    struct Song song;
    char line[STRING_SIZE * 8]; // 가장 긴 라인의 길이를 기준으로 버퍼를 할당
    int found = 0;
    while (fgets(line, sizeof(line), file) != NULL) {
        sscanf(line, "%[^\t]\t%[^\t]\t%[^\t]\t%[^\t]\t%[^\t]\t%[^\t]\t%[^\t\n]", song.title, song.singer, song.composer, song.lyricist, song.genre, song.playtime, song.album, song.release);

        if ((strcmp(tag, "제목") == 0 && strstr(song.title, word) != NULL) ||
            (strcmp(tag, "가수") == 0 && strstr(song.singer, word) != NULL) ||
            (strcmp(tag, "작곡가") == 0 && strstr(song.composer, word) != NULL) ||
            (strcmp(tag, "작사가") == 0 && strstr(song.lyricist, word) != NULL) ||
            (strcmp(tag, "장르") == 0 && strstr(song.genre, word) != NULL) ||
            (strcmp(tag, "재생시간") == 0 && strstr(song.playtime, word) != NULL) ||
            (strcmp(tag, "앨범명") == 0 && strstr(song.album, word) != NULL) ||
            (strcmp(tag, "앨범출시날짜") == 0 && strstr(song.release, word) != NULL)) {
            found = 1;
            break;
        }
    }
    fclose(file);
    return found;
}


void searchZeroInPli(const char* tag, const char* word, char pliName[]) {
    int err = 0;
    int goback = 0;
    while (1) {
        if (err == 0) {
            printf("'0'을 입력 하셨습니다. 정말 뒤로 가시겠습니까?\n\n");
        }
        else {
            printf("잘못 입력 하셨습니다. 다시 선택해주세요.\n\n");
            err = 0;
        }
        printf("1. 뒤로가기\n");
        printf("2. '0' 검색하기\n\n");
        printf("메뉴선택 : ");
        scanf("%d", &goback);
        while (getchar() != '\n');
        printf("\n");
        if (goback == 1) {
            searchTagInPli(pliName);
            break;
        }
        else if (goback == 2) { // '0' 검색
            searchWordOfTagInPli(tag, word, pliName);
            break;
        }
        else {
            err = 1;
            break;
        }
    }
}

void searchWordOfTagInPli(const char* tag, const char* word, char pliName[]) {
    FILE* file = fopen("song_list.txt", "r");
    FILE* fp = fopen(pliName, "a");

    struct Song song;
    char line[STRING_SIZE * 8]; // 가장 긴 라인의 길이를 기준으로 버퍼를 할당
    printf("제목 / 가수 / 작곡가 / 작사가 / 장르 / 재생시간 / 앨범명 / 앨범출시날짜\n");
    while (fgets(line, sizeof(line), file) != NULL) {
        sscanf(line, "%[^\t]\t%[^\t]\t%[^\t]\t%[^\t]\t%[^\t]\t%[^\t]\t%[^\t\n]", song.title, song.singer, song.composer, song.lyricist, song.genre, song.playtime, song.album, song.release);

        if (strcmp(tag, "제목") == 0 && strstr(song.title, word) != NULL ||
            strcmp(tag, "가수") == 0 && strstr(song.singer, word) != NULL ||
            strcmp(tag, "작곡가") == 0 && strstr(song.composer, word) != NULL ||
            strcmp(tag, "작사가") == 0 && strstr(song.lyricist, word) != NULL ||
            strcmp(tag, "장르") == 0 && strstr(song.genre, word) != NULL ||
            strcmp(tag, "재생시간") == 0 && strstr(song.playtime, word) != NULL ||
            strcmp(tag, "앨범명") == 0 && strstr(song.album, word) != NULL ||
            strcmp(tag, "앨범출시날짜") == 0 && strstr(song.release, word) != NULL) {
            printf("%s / ", song.title);
            printf("%s / ", song.singer);
            printf("%s / ", song.composer);
            printf("%s / ", song.lyricist);
            int k = strlen(song.title) + strlen(song.singer) + strlen(song.composer) + strlen(song.lyricist) + 4; //공란 예외 처리
            for (k; k < strlen(line); k++) {
                if (line[k] == '\t')
                    printf(" / ");
                else
                    printf("%c", line[k]);
            }
            fputs("\n", fp);
            fputs(line, fp);

            // printf("%s / %s / %s / %s / %s / %s / %s / %s\n", 
            //        song.title, song.singer, song.composer, song.lyricist, song.genre, song.playtime, song.album, song.release);
        }
    }
    fclose(fp);
    fclose(file);
    printf("\n메인화면으로 돌아가려면 아무키나 누르세요.");
    _getwch(); // 한글은 엔터를 쳐야함.
    system("cls");
}
