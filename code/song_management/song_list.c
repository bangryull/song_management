#include "header.h"

void song_list_menu() //노래 리스트 주 메뉴
{
	int mode, err=0;
	while (1)
	{
		if (err == 0) //입력 조건에 맞았을 때
		{
			printf("\n원하는 메뉴를 선택하세요.\n\n");
		}
		else //입력 조건에 맞지 않았을 때
		{
			printf("\n해당 메뉴는 존재하지 않습니다.\n");
			printf("밑의 메뉴 중 선택하세요(예시:1)\n\n");
			err = 0;
		}
		printf("1. 노래 리스트 출력\n");
		printf("2. 노래 추가\n");
		printf("3. 노래 삭제\n");
		printf("0. 뒤로 가기\n");
		printf("\n메뉴 선택 : ");
		scanf(" %d", &mode);

		switch (mode) {
		case 1: //노래 리스트 출력
			song_list_print();
			break;

		case 2: //노래 추가
			song_add();
			break;

		case 3: //노래 삭제
			song_dlt();
			break;

		case 0: //뒤로 가기
			return 0;
			break;
		default: //error
			while (getchar() != '\n'); //입력 버터 비우기
			err = 1;
			break;
		}
	}
}

void song_list_print()//노래 리스트 출력
{
	printf("\n노래 리스트를 출력합니다.");
	printf("\n\n제목 / 가수 / 작곡가 / 작사가 / 장르 / 재생시간 / 앨범명 / 앨범 출시 날짜\n");

}

void song_add()//노래 추가
{
	char name[100000];
	char singer[200];
	char song_writer[200];
	char lyric_writer[200];
	char genre[20];
	int play_time_hour = 0, play_time_min = 0, play_time_sec = 0;
	char album_name[200];
	int album_year = 0, album_month = 0, album_day = 0;
	printf("?");


}

void song_dlt()//노래 삭제
{

}