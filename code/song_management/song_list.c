#include "header.h"
#define MAX_SIZE 100000
#define STRING_SIZE 256

char* trim_left(char* str);
char* trim_right(char* str);
char* trim(char* str);

char* trim_left(char* str) {		//앞 공백 제거
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

char* trim_right(char* str) {		//뒷 공백 제거
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

char* trim(char* str) {			//앞뒤 공백 제거
	return trim_left(trim_right(str));
}

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

		while (getchar() != '\n'); //입력 버퍼 비우기

		switch (mode) {
		case 1: //노래 리스트 출력
			song_list_print();
			break;

		case 2: //노래 추가
			add_song();
			song_list_menu();
			break;

		case 3: //노래 삭제
			song_dlt("song_list.txt");
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

void song_list_print()//노래 리스트 출력
{
	printf("\n노래 리스트를 출력합니다.");
	printf("\n\n제목 / 가수 / 작곡가 / 작사가 / 장르 / 재생시간 / 앨범명 / 앨범 출시 날짜\n");
	FILE* fp;
	fp = fopen("song_list.txt", "r");
}

//void song_add()//노래 추가
//{
//	char name[MAX_SIZE]; //제목
//	char singer[200]; //가수
//	char song_writer[200]; //작곡가
//	char lyric_writer[200]; //작사가
//	char genre[20]; //장르
//	int play_time_hour = 0, play_time_min = 0, play_time_sec = 0; //재생시간들
//	char album_name[200]; //앨범명
//	int album_year = 0, album_month = 0, album_day = 0;//앨범출시날짜
//
//	FILE* fp;
//	fp = fopen("song_list.txt", "a+");
//
//	//제목 입력
//	printf("\n제목을 입력하세요.\n\n");
//	printf("제목 : ");
//	int err=1;
//	getchar();
//	do
//	{
//		gets(name, MAX_SIZE);
//		if (strlen(name) == 0) //입력하지 않았을 때
//		{
//			printf("\n제목 입력이 잘못되었습니다. 정확히 입력해주세요.(예시:좋니)\n\n");
//			printf("제목 : ");
//		}
//		else if (name[0] == ' ' || name[0] == '\t' || name[strlen(name) - 1] == ' ' || name[strlen(name) - 1] == '\t') //앞 뒤에 공백이 있을 때
//		{
//			printf("\n제목 입력이 잘못되었습니다. 정확히 입력해주세요.(예시:좋니)\n\n");
//			printf("제목 : ");
//			name[0] = NULL;
//		}
//		else //맞는 입력일 때
//		{
//			err = 0;
//		}
//	} while (err == 1);
//	//printf("\n%s", name);
//
//	//가수 입력
//	printf("\n가수를 입력하세요.\n\n");
//	printf("가수 : ");
//	err = 1;
//	getchar();
//	do
//	{
//		gets(singer, 200);
//		if (strlen(singer) == 0) //입력하지 않았을 때
//		{
//			printf("\n가수 입력이 잘못되었습니다. 정확히 입력해주세요.(예시:윤종신)\n\n");
//			printf("가수 : ");
//		}
//		else if (singer[0] == ' ' || singer[0] == '\t' || singer[strlen(singer) - 1] == ' ' || singer[strlen(singer) - 1] == '\t') //앞 뒤에 공백이 있을 때
//		{
//			printf("\n가수 입력이 잘못되었습니다. 정확히 입력해주세요.(예시:윤종신)\n\n");
//			printf("가수 : ");
//			singer[0] = NULL;
//		}
//		else //맞는 입력일 때
//		{
//			err = 0;
//		}
//	} while (err == 1);
//	//printf("\n%s", singer);
//
//	//작곡가 입력
//	printf("\n작곡가를 입력하세요.\n\n");
//	printf("작곡가 : ");
//	err = 1;
//	getchar();
//	do
//	{
//		gets(song_writer, 200);
//		if (strlen(song_writer) == 0) //입력하지 않았을 때
//		{
//			printf("\n작곡가 입력이 잘못되었습니다. 정확히 입력해주세요.(예시:윤종신)\n\n");
//			printf("작곡가 : ");
//		}
//		else if (song_writer[0] == ' ' || song_writer[0] == '\t' || song_writer[strlen(song_writer) - 1] == ' ' || song_writer[strlen(song_writer) - 1] == '\t') //앞 뒤에 공백이 있을 때
//		{
//			printf("\n작곡가 입력이 잘못되었습니다. 정확히 입력해주세요.(예시:윤종신)\n\n");
//			printf("작곡가 : ");
//			song_writer[0] = NULL;
//		}
//		else //맞는 입력일 때
//		{
//			err = 0;
//		}
//	} while (err == 1);
//	//printf("\n%s", song_writer);
//
//	//작사가 입력
//	printf("\n작사가를 입력하세요.\n\n");
//	printf("작사가 : ");
//	err = 1;
//	getchar();
//	do
//	{
//		gets(lyric_writer, 200);
//		if (strlen(lyric_writer) == 0) //입력하지 않았을 때
//		{
//			printf("\n작사가 입력이 잘못되었습니다. 정확히 입력해주세요.(예시:윤종신)\n\n");
//			printf("작사가 : ");
//		}
//		else if (lyric_writer[0] == ' ' || lyric_writer[0] == '\t' || lyric_writer[strlen(lyric_writer) - 1] == ' ' || lyric_writer[strlen(lyric_writer) - 1] == '\t') //앞 뒤에 공백이 있을 때
//		{
//			printf("\n작사가 입력이 잘못되었습니다. 정확히 입력해주세요.(예시:윤종신)\n\n");
//			printf("작사가 : ");
//			lyric_writer[0] = NULL;
//		}
//		else //맞는 입력일 때
//		{
//			err = 0;
//		}
//	} while (err == 1);
//	//printf("\n%s", lyric_writer);
//
//	//작사가 입력
//	printf("\n작사가를 입력하세요.\n\n");
//	printf("작사가 : ");
//	err = 1;
//	getchar();
//	do
//	{
//		gets(lyric_writer, 200);
//		if (strlen(lyric_writer) == 0) //입력하지 않았을 때
//		{
//			printf("\n작사가 입력이 잘못되었습니다. 정확히 입력해주세요.(예시:윤종신)\n\n");
//			printf("작사가 : ");
//		}
//		else if (lyric_writer[0] == ' ' || lyric_writer[0] == '\t' || lyric_writer[strlen(lyric_writer) - 1] == ' ' || lyric_writer[strlen(lyric_writer) - 1] == '\t') //앞 뒤에 공백이 있을 때
//		{
//			printf("\n작사가 입력이 잘못되었습니다. 정확히 입력해주세요.(예시:윤종신)\n\n");
//			printf("작사가 : ");
//			lyric_writer[0] = NULL;
//		}
//		else //맞는 입력일 때
//		{
//			err = 0;
//		}
//	} while (err == 1);
//	//printf("\n%s", lyric_writer);
//
//	//장르 입력
//	printf("\n장르를 입력하세요.\n\n");
//	printf("장르 : ");
//	err = 1;
//	getchar();
//	do
//	{
//		gets(genre, 20);
//		if (strcmp(genre,"클래식")==0 || strcmp(genre, "재즈") == 0 || strcmp(genre, "팝") == 0 || strcmp(genre, "발라드") == 0 || strcmp(genre, "힙합") == 0 || strcmp(genre, "트로트") == 0 || strcmp(genre, "디스코") == 0 || strcmp(genre, "댄스") == 0) //맞는 입력일 때
//		{
//			err = 0;
//		}
//		else //규칙과 다를 때
//		{
//			printf("\n장르 입력이 잘못되었습니다. 정확히 입력해주세요.(예시:재즈)\n\n");
//			printf("장르 : ");
//			genre[0] = NULL;
//		}
//	} while (err == 1);
//	//printf("\n%s", genre);
//
//	//재생시간 입력
//	printf("\n재생시간을 입력하세요.\n\n");
//	printf("재생시간 : ");
//	// 수정필요수정필요수정필요수정필요수정필요수정필요수정필요수정필요수정필요수정필요수정필요수정필요수정필요수정필요
//	// 수정필요수정필요수정필요수정필요수정필요수정필요수정필요수정필요수정필요수정필요수정필요수정필요수정필요수정필요
//	// 수정필요수정필요수정필요수정필요수정필요수정필요수정필요수정필요수정필요수정필요수정필요수정필요수정필요수정필요 
//	// 수정필요수정필요수정필요수정필요수정필요수정필요수정필요수정필요수정필요수정필요수정필요수정필요수정필요수정필요
//	// 수정필요수정필요수정필요수정필요수정필요수정필요수정필요수정필요수정필요수정필요수정필요수정필요수정필요수정필요
//	// 수정필요수정필요수정필요수정필요수정필요수정필요수정필요수정필요수정필요수정필요수정필요수정필요수정필요수정필요 
//	// 수정필요수정필요수정필요수정필요수정필요수정필요수정필요수정필요수정필요수정필요수정필요수정필요수정필요수정필요
//	// 수정필요수정필요수정필요수정필요수정필요수정필요수정필요수정필요수정필요수정필요수정필요수정필요수정필요수정필요
//	// 수정필요수정필요수정필요수정필요수정필요수정필요수정필요수정필요수정필요수정필요수정필요수정필요수정필요수정필요 
//	// 수정필요수정필요수정필요수정필요수정필요수정필요수정필요수정필요수정필요수정필요수정필요수정필요수정필요수정필요
//	// 수정필요수정필요수정필요수정필요수정필요수정필요수정필요수정필요수정필요수정필요수정필요수정필요수정필요수정필요
//	// 수정필요수정필요수정필요수정필요수정필요수정필요수정필요수정필요수정필요수정필요수정필요수정필요수정필요수정필요 
//
//	//앨범명 입력
//	printf("\n앨범명을 입력하세요.\n\n");
//	printf("앨범명 : ");
//	err = 1;
//	getchar();
//	do
//	{
//		gets(album_name, 200);
//		if (strlen(album_name) == 0) //입력하지 않았을 때
//		{
//			printf("\n작사가 입력이 잘못되었습니다. 정확히 입력해주세요.(예시:윤종신)\n\n");
//			printf("작사가 : ");
//		}
//		else if (album_name[0] == ' ' || album_name[0] == '\t' || album_name[strlen(album_name) - 1] == ' ' || album_name[strlen(album_name) - 1] == '\t') //앞 뒤에 공백이 있을 때
//		{
//			printf("\n작사가 입력이 잘못되었습니다. 정확히 입력해주세요.(예시:윤종신)\n\n");
//			printf("작사가 : ");
//			album_name[0] = NULL;
//		}
//		else //맞는 입력일 때
//		{
//			err = 0;
//		}
//	} while (err == 1);
//	//printf("\n%s", album_name);
//
//	//앨범 출시 날짜 입력
//	printf("\n앨범 출시 날짜를 입력하세요.\n\n");
//	printf("앨범 출시 날짜 : ");
//	// 수정필요수정필요수정필요수정필요수정필요수정필요수정필요수정필요수정필요수정필요수정필요수정필요수정필요수정필요
//	// 수정필요수정필요수정필요수정필요수정필요수정필요수정필요수정필요수정필요수정필요수정필요수정필요수정필요수정필요
//	// 수정필요수정필요수정필요수정필요수정필요수정필요수정필요수정필요수정필요수정필요수정필요수정필요수정필요수정필요 
//	// 수정필요수정필요수정필요수정필요수정필요수정필요수정필요수정필요수정필요수정필요수정필요수정필요수정필요수정필요
//	// 수정필요수정필요수정필요수정필요수정필요수정필요수정필요수정필요수정필요수정필요수정필요수정필요수정필요수정필요
//	// 수정필요수정필요수정필요수정필요수정필요수정필요수정필요수정필요수정필요수정필요수정필요수정필요수정필요수정필요 
//	// 수정필요수정필요수정필요수정필요수정필요수정필요수정필요수정필요수정필요수정필요수정필요수정필요수정필요수정필요
//	// 수정필요수정필요수정필요수정필요수정필요수정필요수정필요수정필요수정필요수정필요수정필요수정필요수정필요수정필요
//	// 수정필요수정필요수정필요수정필요수정필요수정필요수정필요수정필요수정필요수정필요수정필요수정필요수정필요수정필요 
//	// 수정필요수정필요수정필요수정필요수정필요수정필요수정필요수정필요수정필요수정필요수정필요수정필요수정필요수정필요
//	// 수정필요수정필요수정필요수정필요수정필요수정필요수정필요수정필요수정필요수정필요수정필요수정필요수정필요수정필요
//	// 수정필요수정필요수정필요수정필요수정필요수정필요수정필요수정필요수정필요수정필요수정필요수정필요수정필요수정필요 
//}

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
		gets(title_buffer, STRING_SIZE);	//제목 입력받기

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

		if (strlen(singers) == 0) {	//틀린 입력일 경우
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

		if (strlen(composers) == 0) {	//틀린 입력일 경우
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

void song_dlt(char* filename)//노래 삭제
{
	FILE* input_file = fopen(filename, "r");    //기존 txt파일
	if (input_file == NULL) {
		printf("Error opening input file.\n");
		return;
	}

	FILE* output_file = fopen("temp.txt", "w"); //새로 덮어씌울 txt파일
	if (output_file == NULL) {
		printf("Error opening temporary file.\n");
		fclose(input_file);
		return;
	}

	char line[256];   //기존 문자열을 담아둘 배열
	char delete_text[256]; // 삭제할 문자열을 저장할 변수

	printf("노래를 삭제합니다.");
	printf("삭제할 노래의 제목을 입력하세요 : ");
	fgets(delete_text, 256, stdin);

	int found = 0;  // 문자열 발견 여부 확인 변수
	while (fgets(line, 256, input_file)) {    // 찾으려는 문자열이 포함된 행이 아닌 경우 새 파일에 쓰기
		if (!strstr(line, delete_text)) {
			fputs(line, output_file);   // 제거하고자 하는 문자열과 일치하지 않으면 새로운 txt파일에 쓰기, 일치할 경우 해당 문자열은 쓰지 않음
		}
		else {
			found = 1; // 문자열 발견
		}
	}

	fclose(input_file);
	fclose(output_file);

	remove(filename);   // 기존 파일 삭제
	rename("temp.txt", filename);   // 새로 쓴 파일의 이름 변경

	if (found) {
		printf("삭제할 대상이 하나로 특정되었습니다.\n");
	}
	else {
		printf("..! 삭제 대상이 존재하지 않습니다\n");
	}
}
