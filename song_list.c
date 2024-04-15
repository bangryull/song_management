#include "header.h"

char* trim_left(char* str);
char* trim_right(char* str);
char* trim(char* str);

char* trim_left(char* str) {
	while (*str) {
		if (isspace(*str)) {
			str++;
		}
		else {
			break;
		}
	}
	return str;
}

char* trim_right(char* str) {
	int len = (int)strlen(str) - 1;

	while (len >= 0) {
		if (isspace(*(str + len))) {
			len--;
		}
		else {
			break;
		}
	}
	*(str + ++len) = '\0';
	return str;
}

char* trim(char* str) {
	return trim_left(trim_right(str));
}

void song_list_menu() //노래 리스트 주 메뉴
{
	int mode, err = 0;
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
		scanf("%d", &mode);

		while (getchar() != '\n'); //입력 버터 비우기

		switch (mode) {
		case 1: //노래 리스트 출력
			song_list_menu();
			break;

		case 2: //노래 추가
			add_song();
			song_list_menu();
			break;

		case 3: //노래 삭제

			break;

		case 0: //뒤로 가기

			break;
		default: //error
			while (getchar() != '\n'); //입력 버터 비우기
			err = 1;
			break;
		}
	}
}

void add_song() {
	char title_buffer[STRING_SIZE] = "";	//제목
	char singers_buffer[STRING_SIZE] = "";	//가수
	char composers_buffer[STRING_SIZE] = "";	//작곡가
	char lyricists_buffer[STRING_SIZE] = "";	//작사가
	char genre_buffer[STRING_SIZE] = "";    //장르
	char playtime[STRING_SIZE]; //재생시간
	char album_buffer[STRING_SIZE];    //앨범명
	char release[STRING_SIZE];  //앨범출시날짜
	FILE* fp = fopen("song_list.txt", "a");	//추가모드로 파일 열기


	printf("제목을 입력하세요.\n");	//제목
	while (1) {
		printf("\n");
		printf("제목 :");
		gets(title_buffer);	//제목 입력받기

		char* title = trim(title_buffer);	//앞뒤 공백 제거

		//printf("%s\n", title);			//제대로 입력되었는지 확인(검사)
		if (strlen(title) == 0) {	//틀린 입력일 경우
			printf("제목 입력이 잘못되었습니다.정확히 입력해주세요.(예시:좋니)\n");
			continue;
		}
		else {		//맞는 입력일 경우
			fprintf(fp, "%s | ", title);
		}
		break;
	}	//제목 끝
	
	printf("가수를 입력하세요.\n");	//가수
	while (1) {
		printf("\n");
		printf("가수 :");
		gets(singers_buffer);	//가수 입력받기

		char* singers = trim(singers_buffer);	//앞뒤 공백 제거

		if (strlen(singers)==0) {	//틀린 입력일 경우
			printf("가수 입력이 잘못되었습니다.정확히 입력해주세요.(예시:윤종신)\n");
			continue;
		}
		else {		//맞는 입력일 경우
			char* singer_buffer = strtok(singers, ",");	//","를 기준으로 자르기
			char* singer = trim(singer_buffer);	//앞뒤 공백 제거
												//중복 확인

			fprintf(fp, "%s ", singer);			//첫 가수 파일에 저장
			singer = strtok(NULL, ",");

			while (singer != NULL) {				//가수가 더 있을 경우 계속 추가 저장
				char* next_singer = trim(singer);	//앞뒤 공백 제거
													//중복 확인
				fprintf(fp, ", %s ", next_singer);
				singer = strtok(NULL, ",");
			}
			fputs("| ", fp);
		}
		break;
	}		//가수 끝


	printf("작곡가를 입력하세요.\n");	//작곡가
	while (1) {
		printf("\n");
		printf("작곡가 :");
		gets(composers_buffer);	//작곡가 입력받기

		char* composers = trim(composers_buffer);	//앞뒤 공백 제거

		if (strlen(composers)==0) {	//틀린 입력일 경우
			printf("작곡가 입력이 잘못되었습니다.정확히 입력해주세요.(예시:윤종신)\n");
			continue;
		}
		else {		//맞는 입력일 경우
			char* composer_buffer = strtok(composers, ",");	//","를 기준으로 자르기
			char* composer = trim(composer_buffer);	//앞뒤 공백 제거
												//중복 확인

			fprintf(fp, "%s ", composer);			//첫 작곡가 파일에 저장
			composer = strtok(NULL, ",");

			while (composer != NULL) {				//작곡가가 더 있을 경우 계속 추가 저장
				char* next_composer = trim(composer);	//앞뒤 공백 제거
													//중복 확인
				fprintf(fp, ", %s ", next_composer);
				composer = strtok(NULL, ",");
			}
			fputs("| ", fp);		
		}
		break;	//작곡가 끝
	}

	printf("작사가를 입력하세요.\n");	//작사가
	while (1) {
		printf("\n");
		printf("작사가 :");
		gets(lyricists_buffer);	//작사가 입력받기

		char* lyricists = trim(lyricists_buffer);	//앞뒤 공백 제거

		if (strlen(lyricists) == 0) {	//틀린 입력일 경우
			printf("작사가 입력이 잘못되었습니다.정확히 입력해주세요.(예시:윤종신)\n");
			continue;
		}
		else {		//맞는 입력일 경우
			char* lyricist_buffer = strtok(lyricists, ",");	//","를 기준으로 자르기
			char* lyricist = trim(lyricist_buffer);	//앞뒤 공백 제거
			//중복 확인

			fprintf(fp, "%s ", lyricist);			//첫 작사가 파일에 저장
			lyricist = strtok(NULL, ",");

			while (lyricist != NULL) {				//작사가가 더 있을 경우 계속 추가 저장
				char* next_lyricist = trim(lyricist);	//앞뒤 공백 제거
				//중복 확인
				fprintf(fp, ", %s ", next_lyricist);
				lyricist = strtok(NULL, ",");
			}
			fputs("| ", fp);		
		}
		break;	//작사가 끝
	}

	printf("장르를 입력하세요.\n");	//장르
	while (1) {
		printf("\n");
		printf("장르 :");
		gets(genre_buffer);

		char* genre = trim(genre_buffer);	//앞뒤 공백 제거

		if (strcmp(genre, "클래식") * strcmp(genre, "재즈") * strcmp(genre, "팝") * strcmp(genre, "발라드") * strcmp(genre, "힙합") * strcmp(genre, "트로트") * strcmp(genre, "디스코") * strcmp(genre, "댄스") == 0) {	//맞는 입력일 경우
			fprintf(fp, "%s | ", genre);
		}
		else {		//틀린 입력일 경우
			printf("장르 입력이 잘못되었습니다.정확히 입력해주세요.(예시:재즈)\n");
			continue;
		}
		break;
	}		//장르 끝

	/*
	printf("시간를 입력하세요.\n");	//시간
	while (1) {
		char minute_str[STRING_SIZE] = "";
		char second_str[STRING_SIZE] = "";
		int error = 0;
		printf("\n");
		printf("시간 :");
		gets(playtime);

		char* playtime_ = trim(playtime);	//앞뒤 공백 제거

		if (strlen(playtime_) == 0) { error = 1; }	//틀린 입력일 경우	
		else if (strchr(playtime_, "분") == NULL && strchr(playtime_, "초") == NULL) { error = 1; }
		else if (strchr(playtime_, "분") == NULL && strchr(playtime_, "초") != NULL) {
			*second_str = strtok(playtime_, "초");
			if (strtok(NULL, "초") != NULL) { error = 1; }
		}
		else if (strchr(playtime_, "분") != NULL && strchr(playtime_, "초") == NULL) {
			*minute_str = strtok(playtime_, "분");
			if (strtok(NULL, "분") != NULL) { error = 1; }
		}
		else {
			*minute_str = strtok(playtime_, "분");
			*second_str = strtok(NULL, "초");
			if (strtok(NULL, "초") != NULL) { error = 1; }
		}
		printf("%s분%s초\n", second_str, minute_str);
		if (error == 1) {
			printf("시간 입력이 잘못되었습니다.정확히 입력해주세요.(예시:윤종신)\n");
			continue;
		}
		break;
	}		//시간 끝
	*/  //수정중

	printf("앨범명을 입력하세요.\n");	//앨범명
	while (1) {
		printf("\n");
		printf("앨범명 :");
		gets(album_buffer);	//앨범명 입력받기

		char* album = trim(album_buffer);	//앞뒤 공백 제거

		if (0) {	//틀린 입력일 경우
			printf("앨범명 입력이 잘못되었습니다.정확히 입력해주세요.(예시:밤양갱)\n");
			continue;
		}
		else {		//맞는 입력일 경우
			fprintf(fp, "%s | ", album);
		}
		break;
	}	//앨범명 끝



	fclose(fp);
}