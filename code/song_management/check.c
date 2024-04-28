#include "header.h"

void check(){ // song_list.txt 파일이 있는지 확인
    FILE* txttest = fopen("song_list.txt", "r");
        if (txttest == NULL) {      //없으면 새로 생성
            printf("노래리스트 데이터 파일이 생성되었습니다.");
            Sleep(1500);
            system("cls");          //1.5초 후에 프롬프트 창 비우기
            FILE* txttest = fopen("song_list.txt", "w");
            fclose(txttest);
        }
        else {                      //있으면
            // printf("확인");
            fclose(txttest);
        }
}