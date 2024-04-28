#include "header.h"

int IsSpace(char ch); //공백 확인
char* strrtrim(char* s); //앞 공백 제거
char* strltrim(char* s); //뒷 공백 제거
char* trim(char* s); //앞뒤 공백 제거
void duplicate_people(const char* filename, const char* people); //동명이인 확인
int check_date(int y, int m, int d); //날짜 존재 여부 확인

int IsSpace(char ch)
{
    if (ch < 0)  // 음수인경우 한글로 간주
        return 0;
    else
        return isspace(ch);
}

char* strrtrim(char* s)   //뒷 공백 제거
{
    char* t;

    t = strchr(s, '\0');
    while (t > s && IsSpace(t[-1]))
        --t;
    *t = '\0';
    return s;
}

char* strltrim(char* s)   //앞 공백 제거
{
    char* t;
    char* e;

    t = s;
    e = strchr(s, '\0');
    while (IsSpace(*t))
        ++t;

    memmove(s, t, e - t + 1);

    return s;
}

char* trim(char* s)   //앞뒤 공백 제거
{
    strltrim(s);
    strrtrim(s);

    return s;
}

void duplicate_people(const char* filename, const char* people) {
    FILE* file = fopen(filename, "r");
    if (file == NULL) {
        fprintf(stderr, "파일을 열 수 없습니다: %s\n", filename);
        return;
    }

    char d_line[256]; // txt에서 각 줄을 읽기 위한 버퍼
    char dupli_peoples[256][256]; // index와 함께 중복된 사람 저장 배열
    int people_count = 0; // 중복된 사람 수
    int is_duplicate; // 중복 여부 확인

    while (fgets(d_line, sizeof(d_line), file)) { // txt파일의 각 줄 d_line에 저장
        char* dupli_word = strtok(d_line, "\t"); // \t를 구분자로 끊어 dupli_word에 저장

        while (dupli_word != NULL) {
            char* pipe_pos = strchr(dupli_word, '|'); // '|' 위치 찾기

            if (pipe_pos != NULL) {
                *pipe_pos = '\0'; // '|' 이전의 문자열 추출
                char extra[256] = ""; // '|' 이후의 문자열 저장

                char* after_pipe = pipe_pos + 1; // '|' 이후의 시작 위치
                char* next_tab_pos = strchr(after_pipe, '\t'); // 다음 '\t' 위치 찾기
                if (next_tab_pos != NULL) {
                    *next_tab_pos = '\0'; // '\t' 이후 제거
                }
                strcpy(extra, after_pipe); // '|' 이후의 문자열 저장

                if (strcmp(dupli_word, people) == 0) { // '|'이전의 문자열이 입력한 가수와 일치하면
                    strcat(dupli_word, "|");
                    strcat(dupli_word, extra);  //dupli_word에 '|' 이후 문자열 추가

                    // 중복 여부 확인
                    is_duplicate = 0;
                    for (int i = 0; i < people_count; i++) {
                        if (strcmp(dupli_peoples[i], dupli_word) == 0) { // 중복 확인
                            is_duplicate = 1;   //중복이라면
                            break;
                        }
                    }

                    if (is_duplicate == 0) { // 중복이 아니면 저장
                        strcpy(dupli_peoples[people_count], dupli_word);
                        people_count++;
                    }
                }
            }

            dupli_word = strtok(NULL, "\t"); // 다음 dupli_word로 이동
        }
    }

    int dupli_index;
    char dupli_add[100];
    if (people_count >= 1) {   // 중복된 사람 수가 1개 이상이면 인덱스와 함께 출력
        while (1) {
            printf("동명이인 아티스트가 존재합니다. 동일한 아티스트를 골라주세요.\n");
            for (int i = 0; i < people_count; i++) {    // 중복된 사람 출력
                printf("%d. %s\n", i + 1, dupli_peoples[i]);
            }
            printf("0. 없음\n");
            printf("입력: ");
            scanf("%d", &dupli_index);  // 번호 입력
            getchar();
            if (dupli_index == 0) { // 0. 없음 선택시, 새로 번호 생성 및 저장
                sprintf(dupli_add, "|%d", people_count);
                break;
            }
            else if (dupli_index > 0 && dupli_index < people_count + 1) {   // 선택한 사람으로 index 저장
                sprintf(dupli_add, "|%d", dupli_index - 1);
                break;
            }
        }
    }
    else {
        sprintf(dupli_add, "|%d", 0);   // 중복된 사람이 없다면 |0 을 붙임
    }
    strcat(people, dupli_add);  // 완성된 문자열을 people에 저장
    fclose(file); // 파일 닫기
}

int check_date(int y, int m, int d) {
    if (y > 1907 && y <= 2024 && m >= 1 && m <= 12) {	//년,월 범위
        if ((y % 4) == 0 && (y % 100) != 0 || (y % 400) == 0) {	//윤년
            int months[] = { 31,29,31,30,31,30,31,31,30,31,30,31 };
            if (d >= 1 && d <= months[m - 1]) { return 1; }	//일 범위까지 맞으면 TRUE
            else { return 0; }	//틀리면 FALSE
        }
        else {	//평년
            int months[] = { 31,28,31,30,31,30,31,31,30,31,30,31 };
            if (d >= 1 && d <= months[m - 1]) { return 1; }	//일 범위까지 맞으면 TRUE
            else { return 0; }	//틀리면 FALSE
        }
    }
    else { return 0; }
}

void song_list_menu() //노래 리스트 주 메뉴
{
    char input_text[STRING_SIZE];   //삭제할 문자열(노래)이 들어갈 배열
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
        scanf(" %d", &mode);

        switch (mode) {
        case 1: //노래 리스트 출력
            song_list_print();
            break;

        case 2: //노래 추가
            add_song();
            break;

        case 3: //노래 삭제
            while (getchar() != '\n'); //입력 버터 비우기
            get_dlt_song(input_text); //삭제 문자열 입력 및 생성 후 삭제
            break;

        case 0: //뒤로 가기
            while (getchar() != '\n'); //입력 버터 비우기
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
    printf("\n\n제목 / 가수 / 작곡가 / 작사가 / 장르 / 재생시간 / 앨범명 / 앨범 출시 날짜\n\n");
    FILE* fp;
    fp = fopen("song_list.txt", "r"); //텍스트 파일 불러오기
    //if (fp == NULL) //파일 내용 체크
    //{
    //    printf("오류");
    //}
    char name[STRING_SIZE]; //제목
    char singer[STRING_SIZE]; //가수
    char song_writer[STRING_SIZE]; //작곡가
    char lylic_writer[STRING_SIZE]; //작사가
    char genre[STRING_SIZE]; //장르
    char playtime[STRING_SIZE]; //재생시간
    char album_name[STRING_SIZE]; //앨범명
    char album_time[STRING_SIZE]; //앨범 출시 날짜

    char song[STRING_SIZE * 8]; //불러올 한 줄
    while (fgets(song, sizeof(song), fp) != NULL) //한 줄 씩 불러오기
    {
        sscanf(song, "%[^\t]\t%[^\t]\t%[^\t]\t%[^\t]\t%[^\t]\t%[^\t]\t%[^\t]\t%[^\t\n]", name, singer, song_writer, lylic_writer, genre, playtime, album_name, album_time); //탭키를 구분자로 하나씩 불러오기
        printf("%s / ", name); //제목 출력
        int size = 0;

        //가수 출력
        while (1)
        {
            if (singer[size] == '|') //인물 구분자를 만났을 때
            {
                while (1) //띄어쓰기를 만날 때 또는 끝날 때 까지 건너뛰기
                {
                    size++;
                    if (singer[size] == NULL) //문자열이 끝났을 때
                    {
                        break;
                    }
                    else if (singer[size] == ' ') //띄어쓰기를 만났을 때
                    {
                        size = size + 1; //다음 인물의 이름으로 이동
                        break; 
                    }
                }
            }
            if (singer[size] == NULL) //문자열이 끝났을 때
            {
                printf(" / ");
                break;
            }
            printf("%c", singer[size]);
            size++;
        }
        size = 0;

        //작곡가 출력
        while (1)
        {
            if (song_writer[size] == '|') //인물 구분자를 만났을 때
            {
                while (1) //띄어쓰기를 만날 때 또는 끝날 때 까지 건너뛰기
                {
                    size++;
                    if (song_writer[size] == NULL) //문자열이 끝났을 때
                    {
                        break;
                    }
                    else if (song_writer[size] == ' ') //띄어쓰기를 만났을 때
                    {
                        size = size + 1;
                        break;
                    }
                }
            }
            if (song_writer[size] == NULL) //문자열이 끝났을 때
            {
                printf(" / ");
                break;
            }
            printf("%c", song_writer[size]);
            size++;
        }
        size = 0;

        //작사가 출력
        while (1)
        {
            if (lylic_writer[size] == '|') //인물 구분자를 만났을 때
            {
                while (1) //띄어쓰기를 만날 때 또는 끝날 때 까지 건너뛰기
                {
                    size++;
                    if (lylic_writer[size] == NULL) //문자열이 끝났을 때
                    {
                        break;
                    }
                    else if (lylic_writer[size] == ' ') //띄어쓰기를 만났을 때
                    {
                        size = size + 1;
                        break;
                    }
                }
            }
            if (lylic_writer[size] == NULL) //문자열이 끝났을 때
            {
                printf(" / ");
                break;
            }
            printf("%c", lylic_writer[size]);
            size++;
        }
        int k = strlen(name) + strlen(singer)+ strlen(song_writer)+strlen(lylic_writer)+4; //공란 예외 처리
        for (k; k < strlen(song); k++) {
            if (song[k] == '\t')
                printf(" / ");
            else
                printf("%c", song[k]);
        }
        //printf("%s / ", genre); //장르 출력
        //printf("%s / ", playtime); //재생시간 출력
        //printf("%s / ", album_name); //앨범명 출력
        //printf("%s\n", album_time); //앨범 출시 날짜 출력
    }
    printf("\n\n메인화면으로 돌아가려면 아무키나 누르세요.\n");
    _getwch();
    fclose(fp);
    main();
}

void add_song() {
    char title_buffer[STRING_SIZE] = "";   //제목
    char singers_buffer[STRING_SIZE] = "";   //가수
    char composers_buffer[STRING_SIZE] = "";   //작곡가
    char lyricists_buffer[STRING_SIZE] = "";   //작사가
    char genre_buffer[STRING_SIZE] = "";    //장르
    char playtime_buffer[STRING_SIZE]; //재생시간
    char album_buffer[STRING_SIZE];    //앨범명
    char release_buffer[STRING_SIZE];  //앨범출시날짜

    //입력을 저장할 변수
    char title_result[STRING_SIZE] = "";	//제목
    char singers_result[STRING_SIZE] = "";	//가수
    char composers_result[STRING_SIZE] = "";	//작곡가
    char lyricists_result[STRING_SIZE] = "";	//작사가
    char genre_result[STRING_SIZE] = "";    //장르
    char playtime_result[STRING_SIZE] = ""; //재생시간
    char album_result[STRING_SIZE] = "";    //앨범명
    char release_result[STRING_SIZE] = "";  //앨범출시날짜

    FILE* fp = fopen("song_list.txt", "a");   //추가모드로 파일 열기


    printf("\n제목을 입력하세요.\n");	//제목
    while (1) {
        printf("\n");
        printf("제목 :");
        gets(title_buffer, STRING_SIZE);	//제목 입력받기

        char* title = trim(title_buffer);	//앞뒤 공백 제거

        //printf("%s\n", title);			//제대로 입력되었는지 확인(검사)
        if (strlen(title) == 0) {	//틀린 입력일 경우
            printf("\n제목 입력이 잘못되었습니다.정확히 입력해주세요.(예시:좋니)\n");
            continue;
        }
        else {		//맞는 입력일 경우
            strcat(title_result, title);	//제목 저장
        }
        break;
    }	//제목 끝

    printf("\n가수를 입력하세요.\n");	//가수
    while (1) {
        printf("\n");
        printf("가수 :");
        gets(singers_buffer);	//가수 입력받기

        char* singers = trim(singers_buffer);	//앞뒤 공백 제거

        if (strlen(singers) == 0) {	//틀린 입력일 경우
            printf("\n가수 입력이 잘못되었습니다.정확히 입력해주세요.(예시:윤종신)\n");
            continue;
        }
        else {		//맞는 입력일 경우
            char* ptr_comma_q = singers;
            char* ptr_comma_p = strchr(singers, ',');
            if (ptr_comma_p == NULL) {	//가수가 한명일 때
                duplicate_people("song_list.txt", singers);
                strcat(singers_result, singers);
            }
            else {
                char first_singer_buffer[STRING_SIZE] = "";
                strncpy(first_singer_buffer, ptr_comma_q, ptr_comma_p - ptr_comma_q);	//첫 가수 추출
                char* first_singer = trim(first_singer_buffer);	//앞뒤 공백 제거
                duplicate_people("song_list.txt", first_singer);	//중복확인
                strcat(singers_result, first_singer);	//첫 가수 저장
                while (ptr_comma_p != NULL) {	//가수가 더 있는지 확인
                    char singer_buffer[STRING_SIZE] = "";
                    strncpy(singer_buffer, ptr_comma_q + 1, ptr_comma_p - ptr_comma_q - 1);	//가수 추출
                    char* singer = trim(singer_buffer);	//앞뒤 공백 제거
                    duplicate_people("song_list.txt", singer);	//중복확인
                    strcat(singers_result, " , ");
                    strcat(singers_result, singer);	//가수 저장
                    ptr_comma_q = ptr_comma_p;
                    ptr_comma_p = strchr(ptr_comma_p + 1, ',');
                }
                char last_singer_buffer[STRING_SIZE] = "";
                ptr_comma_p = strrchr(singers, ',');
                strncpy(last_singer_buffer, ptr_comma_p + 1, (singers + strlen(singers) - 1) - ptr_comma_p);	//마지막 가수 추출
                char* last_singer = trim(last_singer_buffer);	//앞뒤 공백 제거
                duplicate_people("song_list.txt", last_singer);	//중복확인
                strcat(singers_result, " , ");
                strcat(singers_result, last_singer);	//마지막 가수 저장
            }
        }

        break;
    }		//가수 끝


    printf("\n작곡가를 입력하세요.\n");	//작곡가
    while (1) {
        printf("\n");
        printf("작곡가 :");
        gets(composers_buffer);	//작곡가 입력받기

        char* composers = trim(composers_buffer);	//앞뒤 공백 제거

        if (strlen(composers) == 0) {	//틀린 입력일 경우
            printf("\n작곡가 입력이 잘못되었습니다.정확히 입력해주세요.(예시:윤종신)\n");
            continue;
        }
        else {		//맞는 입력일 경우
            char* ptr_comma_q = composers;
            char* ptr_comma_p = strchr(composers, ',');
            if (ptr_comma_p == NULL) {	//작곡가 한명일 때
                duplicate_people("song_list.txt", composers);
                strcat(composers_result, composers);
            }
            else {
                char first_composer_buffer[STRING_SIZE] = "";
                strncpy(first_composer_buffer, ptr_comma_q, ptr_comma_p - ptr_comma_q);	//첫 작곡가 추출
                char* first_composer = trim(first_composer_buffer);	//앞뒤 공백 제거
                duplicate_people("song_list.txt", first_composer);	//중복확인
                strcat(composers_result, first_composer);	//첫 작곡가 저장
                while (ptr_comma_p != NULL) {	//작곡가가 더 있는지 확인
                    char composer_buffer[STRING_SIZE] = "";
                    strncpy(composer_buffer, ptr_comma_q + 1, ptr_comma_p - ptr_comma_q - 1);	//작곡가 추출
                    char* composer = trim(composer_buffer);	//앞뒤 공백 제거
                    duplicate_people("song_list.txt", composer);	//중복확인
                    strcat(composers_result, " , ");
                    strcat(composers_result, composer);	//작곡가 저장
                    ptr_comma_q = ptr_comma_p;
                    ptr_comma_p = strchr(ptr_comma_p + 1, ',');
                }
                char last_composer_buffer[STRING_SIZE] = "";
                ptr_comma_p = strrchr(composers, ',');
                strncpy(last_composer_buffer, ptr_comma_p + 1, (composers + strlen(composers) - 1) - ptr_comma_p);	//마지막 가수 추출
                char* last_composer = trim(last_composer_buffer);	//앞뒤 공백 제거
                duplicate_people("song_list.txt", last_composer);	//중복확인
                strcat(composers_result, " , ");
                strcat(composers_result, last_composer);	//마지막 작곡가 저장
            }
        }
        break;	//작곡가 끝
    }

    printf("\n작사가를 입력하세요.\n");	//작사가
    while (1) {
        printf("\n");
        printf("작사가 :");
        gets(lyricists_buffer);	//작사가 입력받기

        char* lyricists = trim(lyricists_buffer);	//앞뒤 공백 제거

        if (strlen(lyricists) == 0) {	//틀린 입력일 경우
            printf("\n작사가 입력이 잘못되었습니다.정확히 입력해주세요.(예시:윤종신)\n");
            continue;
        }
        else {		//맞는 입력일 경우
            char* ptr_comma_q = lyricists;
            char* ptr_comma_p = strchr(lyricists, ',');
            if (ptr_comma_p == NULL) {	//작사가가 한명일 때
                duplicate_people("song_list.txt", lyricists);
                strcat(lyricists_result, lyricists);
            }
            else {
                char first_lyricist_buffer[STRING_SIZE] = "";
                strncpy(first_lyricist_buffer, ptr_comma_q, ptr_comma_p - ptr_comma_q);	//첫 작사가 추출
                char* first_lyricist = trim(first_lyricist_buffer);	//앞뒤 공백 제거
                duplicate_people("song_list.txt", first_lyricist);	//중복확인
                strcat(lyricists_result, first_lyricist);	//첫 작사가 저장
                while (ptr_comma_p != NULL) {	//작사가가 더 있는지 확인
                    char lyricist_buffer[STRING_SIZE] = "";
                    strncpy(lyricist_buffer, ptr_comma_q + 1, ptr_comma_p - ptr_comma_q - 1);	//작사가 추출
                    char* lyricist = trim(lyricist_buffer);	//앞뒤 공백 제거
                    duplicate_people("song_list.txt", lyricist);	//중복확인
                    strcat(lyricists_result, " , ");
                    strcat(lyricists_result, lyricist);	//작사가 저장
                    ptr_comma_q = ptr_comma_p;
                    ptr_comma_p = strchr(ptr_comma_p + 1, ',');
                }
                char last_lyricist_buffer[STRING_SIZE] = "";
                ptr_comma_p = strrchr(lyricists, ',');
                strncpy(last_lyricist_buffer, ptr_comma_p + 1, (lyricists + strlen(lyricists) - 1) - ptr_comma_p);	//마지막 가수 추출
                char* last_singer = trim(last_lyricist_buffer);	//앞뒤 공백 제거
                duplicate_people("song_list.txt", last_singer);	//중복확인
                strcat(lyricists_result, " , ");
                strcat(lyricists_result, last_singer);	//마지막 작사가 저장
            }
        }
        break;	//작사가 끝
    }

    printf("\n장르를 입력하세요.\n");	//장르
    while (1) {
        printf("\n");
        printf("장르 :");
        gets(genre_buffer);

        char* genre = trim(genre_buffer);	//앞뒤 공백 제거

        if (strcmp(genre, "클래식") * strcmp(genre, "재즈") * strcmp(genre, "팝") * strcmp(genre, "발라드") * strcmp(genre, "힙합") * strcmp(genre, "트로트") * strcmp(genre, "디스코") * strcmp(genre, "댄스") == 0 || strlen(genre) == 0) {	//맞는 입력일 경우
            strcat(genre_result, genre);	//장르 저장
        }

        else {		//틀린 입력일 경우
            printf("\n장르 입력이 잘못되었습니다.정확히 입력해주세요.(예시:재즈)\n");
            continue;
        }
        break;
    }		//장르 끝

    printf("\n시간을 입력하세요.\n");	//재생시간
    while (1) {
        char minute_str[STRING_SIZE] = "";
        char second_str[STRING_SIZE] = "";
        int count_m = 0;
        int count_s = 0;
        int error = 0;
        printf("\n");
        printf("시간 :");
        gets(playtime_buffer);

        char* playtime = trim(playtime_buffer);	//앞뒤 공백 제거

        //"분","초" 각각 개수 세기
        char* ptr_m = strstr(playtime, "분");
        while (ptr_m != NULL) // 더이상 "분"이 등장하지 않을 때까지 반복
        {
            ptr_m = strstr(ptr_m + 1, "분"); // 다음 등장 위치 탐색
            count_m++;
        }
        char* ptr_s = strstr(playtime, "초");
        while (ptr_s != NULL) // 더이상 "초"가 등장하지 않을 때까지 반복
        {
            ptr_s = strstr(ptr_s + 1, "초"); // 다음 등장 위치 탐색
            count_s++;
        }

        //재생시간 문법 형식 확인
        if (strlen(playtime) == 0) { error = 1; }	//틀린 입력일 경우	
        else if (count_m == 1 && count_s == 1) {	//모두 1개씩 있는 경우
            char* ptr_m = strstr(playtime, "분");
            char* ptr_s = strstr(playtime, "초");
            if ((ptr_s - playtime) == strlen(playtime) - 2 && ptr_m < ptr_s) {	//"초"가 마지막이고 "분"이 "초"보다 앞에 있어야 됨
                strncpy(minute_str, playtime, ptr_m - playtime);
                strncpy(second_str, ptr_m + 2, ptr_s - ptr_m - 2);
                if (strchr(minute_str, ' ') || strchr(minute_str, '\t') || strchr(second_str, ' ') || strchr(second_str, '\t')) { error = 1; }	//공백이 없어야 됨
                else {
                    for (int i = 0; i < strlen(minute_str); i++)	//문자열이 숫자인지 확인
                    {
                        if ((int)minute_str[i] < 48 || (int)minute_str[i] > 57) { error = 1; }
                    }
                    for (int i = 0; i < strlen(second_str); i++)	//문자열이 숫자인지 확인
                    {
                        if ((int)second_str[i] < 48 || (int)second_str[i] > 57) { error = 1; }
                    }
                }
            }
            else { error = 1; }
        }
        else if (count_m == 1 && count_s == 0) {	//입력에 "분"이 1개 있는 경우
            char* ptr_m = strstr(playtime, "분");
            if ((ptr_m - playtime) == strlen(playtime) - 2) {	//"분"이 마지막이어야 됨
                strncpy(minute_str, playtime, ptr_m - playtime);
                if (strchr(minute_str, ' ') || strchr(minute_str, '\t')) { error = 1; }	//공백이 없어야 됨
                else {
                    for (int i = 0; i < strlen(minute_str); i++)	//문자열이 숫자인지 확인
                    {
                        if ((int)minute_str[i] < 48 || (int)minute_str[i] > 57) { error = 1; }
                    }
                }
            }
            else { error = 1; }
        }
        else if (count_m == 0 && count_s == 1) {	//입력에 "초"가 1개 있는 경우
            char* ptr_s = strstr(playtime, "초");
            if ((ptr_s - playtime) == strlen(playtime) - 2) {	//"초"가 마지막이어야 됨
                strncpy(second_str, playtime, ptr_s - playtime);
                if (strchr(second_str, ' ') || strchr(second_str, '\t')) { error = 1; }	//공백이 없어야 됨
                else {
                    for (int i = 0; i < strlen(second_str); i++)	//문자열이 숫자인지 확인
                    {
                        if ((int)second_str[i] < 48 || (int)second_str[i] > 57) { error = 1; }
                    }
                }
            }
            else { error = 1; }
        }
        else { error = 1; }		//나머지는 모두 틀린 경우

        if (error == 1) {		//오류 처리
            printf("\n시간 입력이 잘못되었습니다.정확히 입력해주세요.(예시:02분44초)\n");
            continue;
        }

        //재생시간 의미 규칙 확인
        int minute = 0;
        int second = 0;
        if (strcmp(minute_str, "")) {	//"분"이 공백이 아니면
            minute = atoi(minute_str);
            if (minute <= 0) { error = 1; }	//"분"은 0보다 크다
        }
        if (strcmp(second_str, "")) {	//"초"가 공백이 아니면
            second = atoi(second_str);
            if (second <= 0 || second >= 60) { error = 1; }	//"초"는 1~59사이
        }
        if (error == 1) {		//오류 처리
            printf("\n시간 입력이 잘못되었습니다.정확히 입력해주세요.(예시:02분44초)\n");
            continue;
        }

        if (strcmp(minute_str, "")) {	//"분"이 공백이 아니면 "분" 저장
            sprintf(minute_str, "%02d", minute);
            strcat(playtime_result, minute_str);
            strcat(playtime_result, "분");
        }
        if (strcmp(second_str, "")) {	//"초"가 공백이 아니면 "초" 저장
            sprintf(second_str, "%02d", second);
            strcat(playtime_result, second_str);
            strcat(playtime_result, "초");
        }
        break;
    }		//재생시간 끝

    printf("\n앨범명을 입력하세요.\n");	//앨범명
    while (1) {
        printf("\n");
        printf("앨범명 :");
        gets(album_buffer);	//앨범명 입력받기

        char* album = trim(album_buffer);	//앞뒤 공백 제거

        if (0) {	//틀린 입력일 경우(없음)
            printf("\n앨범명 입력이 잘못되었습니다.정확히 입력해주세요.(예시:밤양갱)\n");
            continue;
        }
        else {		//맞는 입력일 경우
            strcat(album_result, album);	//앨범명 저장
        }
        break;
    }	//앨범명 끝

    printf("\n앨범 출시 날짜를 입력하세요.\n");	//앨범 출시 날짜
    while (1) {
        char year_str[5] = "";
        char month_str[3] = "";
        char day_str[3] = "";
        int count_hyphen = 0;
        int count_slash = 0;
        int count_dot = 0;
        int error = 0;
        printf("\n");
        printf("앨범 출시 날짜 :");
        gets(release_buffer);

        char* release = trim(release_buffer);	//앞뒤 공백 제거

        //'-','/','.' 각각 개수 세기
        char* ptr_hyphen_temp = strchr(release, '-');
        while (ptr_hyphen_temp != NULL) // 더이상 '-'이 등장하지 않을 때까지 반복
        {
            ptr_hyphen_temp = strchr(ptr_hyphen_temp + 1, '-'); // 다음 등장 위치 탐색
            count_hyphen++;
        }
        char* ptr_slash_temp = strchr(release, '/');
        while (ptr_slash_temp != NULL) // 더이상 '/'가 등장하지 않을 때까지 반복
        {
            ptr_slash_temp = strchr(ptr_slash_temp + 1, '/'); // 다음 등장 위치 탐색
            count_slash++;
        }
        char* ptr_dot_temp = strchr(release, '.');
        while (ptr_dot_temp != NULL) // 더이상 '.'가 등장하지 않을 때까지 반복
        {
            ptr_dot_temp = strchr(ptr_dot_temp + 1, '.'); // 다음 등장 위치 탐색
            count_dot++;
        }

        //앨범 출시 날짜 문법 형식 확인
        if (strlen(release) == 10) {
            if (count_hyphen == 2 && count_slash == 0 && count_dot == 0) {	//'-'이 2개인 경우
                char* ptr_hyphen_1 = strchr(release, '-');
                char* ptr_hyphen_2 = strchr(ptr_hyphen_1 + 1, '-');
                if ((ptr_hyphen_1 - release) == 4 && (ptr_hyphen_2 - ptr_hyphen_1) == 3) {	//년,월,일이 각각 4,2,2자리인지 확인
                    strncpy(year_str, release, 4);
                    strncpy(month_str, ptr_hyphen_1 + 1, 2);
                    strncpy(day_str, ptr_hyphen_2 + 1, 2);
                }
                else { error = 1; }
            }
            else if (count_hyphen == 0 && count_slash == 2 && count_dot == 0) {	//'/'이 2개인 경우
                char* ptr_slash_1 = strchr(release, '/');
                char* ptr_slash_2 = strchr(ptr_slash_1 + 1, '/');
                if ((ptr_slash_1 - release) == 4 && (ptr_slash_2 - ptr_slash_1) == 3) {	//년,월,일이 각각 4,2,2자리인지 확인
                    strncpy(year_str, release, 4);
                    strncpy(month_str, ptr_slash_1 + 1, 2);
                    strncpy(day_str, ptr_slash_2 + 1, 2);
                }
                else { error = 1; }
            }
            else if (count_hyphen == 0 && count_slash == 0 && count_dot == 2) {	//'.'이 2개인 경우
                char* ptr_dot_1 = strchr(release, '.');
                char* ptr_dot_2 = strchr(ptr_dot_1 + 1, '.');
                if ((ptr_dot_1 - release) == 4 && (ptr_dot_2 - ptr_dot_1) == 3) {	//년,월,일이 각각 4,2,2자리인지 확인
                    strncpy(year_str, release, 4);
                    strncpy(month_str, ptr_dot_1 + 1, 2);
                    strncpy(day_str, ptr_dot_2 + 1, 2);
                }
                else { error = 1; }
            }
            else { error = 1; }
        }
        else if (strlen(release) == 8) {
            strncpy(year_str, release, 4);
            strncpy(month_str, release + 4, 2);
            strncpy(day_str, release + 6, 2);
        }
        else { error = 1; }	//나머지는 모두 틀린 경우

        if (error == 1) {
            printf("\n앨범 출시 날짜 입력이 잘못되었습니다.정확히 입력해주세요.\n(예시:2024-04-01 또는 2024/04/01 또는 2024.04.01 또는 20240401)\n");
            continue;
        }

        for (int i = 0; i < strlen(year_str); i++)	//문자열이 숫자인지 확인
        {
            if ((int)year_str[i] < 48 || (int)year_str[i] > 57) { error = 1; }
        }
        for (int i = 0; i < strlen(month_str); i++)	//문자열이 숫자인지 확인
        {
            if ((int)month_str[i] < 48 || (int)month_str[i] > 57) { error = 1; }
        }
        for (int i = 0; i < strlen(day_str); i++)	//문자열이 숫자인지 확인
        {
            if ((int)day_str[i] < 48 || (int)day_str[i] > 57) { error = 1; }
        }

        if (error == 1) {
            printf("\n앨범 출시 날짜 입력이 잘못되었습니다.정확히 입력해주세요.\n(예시:2024-04-01 또는 2024/04/01 또는 2024.04.01 또는 20240401)\n");
            continue;
        }

        //앨범 출시 날짜 의미 규칙 확인
        int year = atoi(year_str);
        int month = atoi(month_str);
        int day = atoi(day_str);
        if (check_date(year, month, day)) {	//날짜 존재 여부 확인
            sprintf(release_result, "%04d-%02d-%02d", year, month, day);
        }
        else {
            printf("\n앨범 출시 날짜 입력이 잘못되었습니다.정확히 입력해주세요.\n(예시:2024-04-01 또는 2024/04/01 또는 2024.04.01 또는 20240401)\n");
            continue;
        }
        break;
    }		//앨범 출시 날짜 끝

    fprintf(fp, "%s\t%s\t%s\t%s\t%s\t%s\t%s\t%s\n", title_result, singers_result, composers_result, lyricists_result, genre_result, playtime_result, album_result, release_result);
    fclose(fp);
}

void get_dlt_song(char* dlt_song) { // 삭제 문자열 입력 및 생성 함수 -> 해당 문자열 삭제 함수로 넘어감
    char dlt_songname[STRING_SIZE];   // 삭제할 노래 제목
    char dlt_singer[STRING_SIZE];   // 삭제할 노래 가수
    int line_number_check[MAX_SIZE] = { 0 };   // 노래 중복시 삭제할 노래 선택 때 사용할 배열
    int line_num = 0;   // 중복 노래 개수 담을 변수

    printf("노래를 삭제합니다.\n");
    printf("삭제할 노래의 제목을 입력하세요: ");
    fgets(dlt_songname, STRING_SIZE, stdin);
    dlt_songname[strcspn(dlt_songname, "\n")] = '\0'; // 개행 문자 제거

    printf("삭제할 노래의 가수를 입력하세요: ");
    fgets(dlt_singer, STRING_SIZE, stdin);
    dlt_singer[strcspn(dlt_singer, "\n")] = '\0'; // 개행 문자 제거

    FILE* file = fopen("song_list.txt", "r");
    if (file == NULL) {
        printf("Error opening file for reading.\n");
        return;
    }

    char buffer[STRING_SIZE*8];   // txt파일에서 읽어올 문자열 원본
    char dlt_print[STRING_SIZE];   // 노래 정보의 구분자를 '\t' 에서 ' / ' 로 바꿔 출력할 배열
    int line_number = 1; // 중복 노래 각 줄 번호를 저장할 변수
    int selected_line = 0; // 노래가 중복되지 않으면 삭제할 특정 노래의 줄을 담고, 중복되면 사용자가 선택한 번호 저장할 변수
    while (fgets(buffer, STRING_SIZE, file) != NULL) {
        char* token = strtok(buffer, "\t"); // 탭을 구분자로 사용하여 문자열을 분할
        char* song = strtok(NULL, "\t");

        // 입력한 제목과 가수를 txt파일에서 비교하며, 중복 노래 개수 카운트
        if (strcmp(dlt_songname, token) == 0 && strcmp(dlt_singer, song) == 0) {
            line_number_check[line_num] = line_number;
            line_num++;
        }
        line_number++;
    }

    fclose(file);

    if (line_num > 1) { // 삭제 노래 제목과 가수가 중복인 경우
        line_number = 1; // 줄 번호 초기화
        file = fopen("song_list.txt", "r"); // 파일을 다시 열어서 출력
        while (fgets(buffer, STRING_SIZE, file) != NULL) {
            strcpy(dlt_print, buffer);
            char* token = strtok(buffer, "\t"); // 탭을 구분자로 사용하여 문자열을 분할
            char* song = strtok(NULL, "\t");

            // 제목과 가수 일치시 해당 노래 정보 출력
            if (strcmp(dlt_songname, token) == 0 && strcmp(dlt_singer, song) == 0) {
                printf("%d.  ", line_number);
                for (int k = 0; k < strlen(dlt_print); k++) {
                    if (dlt_print[k] == '\t')
                        printf(" / ");
                    else
                        printf("%c", dlt_print[k]);
                }
            }
            line_number++;
        }
        fclose(file);

        printf("삭제할 노래의 번호를 선택하세요: ");
        scanf("%d", &selected_line);
        getchar();

        // 선택한 번호가 잘못된 경우 오류 메시지 출력 후 종료
        int valid_selection = 0;
        for (int i = 0; i < line_num; i++) {
            if (selected_line == line_number_check[i]) {
                valid_selection = 1;
                break;
            }
        }
        if (!valid_selection) {
            printf("잘못된 노래의 번호입니다.\n");
            return;
        }
    }
    else if (line_num == 1) { // 삭제 노래가 중복되지 않은 경우
        line_number = 1; // 줄 번호 초기화
        file = fopen("song_list.txt", "r"); // 파일을 다시 열어서 출력
        while (fgets(buffer, STRING_SIZE, file) != NULL) {
            strcpy(dlt_print, buffer);
            char* token = strtok(buffer, "\t"); // 탭을 구분자로 사용하여 문자열을 분할
            char* song = strtok(NULL, "\t");

            // 제목과 가수 일치시 해당 노래 정보 출력
            if (strcmp(dlt_songname, token) == 0 && strcmp(dlt_singer, song) == 0) {
                for (int k = 0; k < strlen(dlt_print); k++) {
                    if (dlt_print[k] == '\t')
                        printf(" / ");
                    else
                        printf("%c", dlt_print[k]);
                }
                selected_line = line_number;
            }
            line_number++;
        }
        fclose(file);
    }
    else {
        printf(".!! 삭제 대상이 존재하지 않습니다\n");
        return;
    }

    // 선택한 번호에 해당하는 줄을 다시 읽기 위해 fopen
    file = fopen("song_list.txt", "r");
    if (file == NULL) {
        printf("Error opening file for reading.\n");
        return;
    }

    // 선택한 번호에 해당하는 줄을 다시 읽어서 dlt_song에 저장
    line_number = 1;
    while (fgets(buffer, STRING_SIZE, file) != NULL) {
        if (line_number == selected_line) {
            strcpy(dlt_song, buffer);
            break;
        }
        line_number++;
    }

    fclose(file);

    // dlt_song 문자열을 song_list에서 삭제하는 함수
    song_dlt("song_list.txt", dlt_song);
}

void song_dlt(const char* filename, const char* dlt_song) {   // dlt_song 문자열을 song_list에서 삭제하는 함수
    FILE* input_file = fopen(filename, "r");    // 기존 txt 파일
    if (input_file == NULL) {
        printf("%s파일을 찾지 못했습니다.\n", filename);
        return;
    }

    FILE* output_file = fopen("temp.txt", "w"); // 새로 덮어씌울 txt 파일
    if (output_file == NULL) {
        printf("파일 생성 에러\n");
        fclose(input_file);
        return;
    }

    char line[STRING_SIZE];   // 기존 문자열을 담아둘 배열
    int found = 0;  // 문자열 발견 여부 확인 변수

    while (fgets(line, sizeof(line), input_file)) {
        // 찾으려는 문자열이 포함된 행이 아닌 경우 새 파일에 쓰기
        if (strstr(line, dlt_song) == NULL) {
            fputs(line, output_file);
        }
        else {
            found = 1; // 문자열 발견
        }
    }

    char dlt_ans[STRING_SIZE];   // 삭제 여부 답변 입력 배열
    if (found) {
        printf("정말 삭제하시겠습니까? (Delete/...)\n");
        scanf("%s", &dlt_ans);   // 삭제 여부
        if (strcmp(dlt_ans, "Delete") == 0)   // "Delete"와 일치시 삭제 진행
            printf("성공적으로 노래를 삭제했습니다.\n");
        else
            return;   // 일치하지 않으면 리턴
    }
    else {
        printf("..! 삭제 대상이 존재하지 않습니다\n");
    }

    fclose(input_file);
    fclose(output_file);

    remove(filename);   // 기존 파일 삭제
    rename("temp.txt", filename);   // 새로 쓴 파일의 이름 변경
}