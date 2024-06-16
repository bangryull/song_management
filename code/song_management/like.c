#include "header.h"

void push_like();
void like_song_print();

int is_valid_number(const char* str) {
    // 문자열의 각 문자가 숫자인지 확인
    for (int i = 0; str[i] != '\0'; i++) {
        if (!isdigit(str[i]) && str[i] != '\n') {
            return 0;
        }
    }
    return 1;
}

void like_menu() {
    int err = 0;
    while (1)
    {
        if (err == 1)
        {
            printf("해당 메뉴는 존재하지 않습니다. 다시 선택하세요.\n\n");
            err = 0; // 에러 메시지를 출력하고 나서 err를 초기화합니다.
        }
        else {
            printf("\n좋아요 메뉴를 선택하셨습니다.\n");
            printf("원하는 메뉴를 선택하세요.\n\n");
        }
        printf("1. 좋아요 누르기\n");
        printf("2. 즐겨찾기 - 좋아요 한 노래 출력\n");
        printf("0. 뒤로가기\n\n");

        char input[STRING_SIZE];
        int number; //메뉴 선택이 올바른 입력일 때 숫자 넣을 변수

        printf("메뉴 선택: ");
        if (fgets(input, sizeof(input), stdin)) {
            // 개행문자 제거
            input[strcspn(input, "\n")] = '\0';

            if (is_valid_number(input)) { //모든 입력이 숫자로 이루어져 있는지 확인
                number = atoi(input);
                switch (number)
                {
                case 1:
                    push_like();
                    break;
                case 2:
                    like_song_print();
                    break;
                case 0:
                    return;
                default: // 유효하지 않은 번호가 입력된 경우
                    err = 1;
                    break;
                }
            }
            else { //숫자로만 이루어져 있지 않으면
                err = 1;
            }
        }
    }
}

// 숫자인지 확인하는 함수
int is_digit(char ch) {
    return ch >= '0' && ch <= '9';
}

// 줄의 마지막 숫자를 1 올리는 함수
void like_plus(char* line) {
    int len = strlen(line);
    // 숫자를 찾기 위해 뒤에서부터 탐색
    for (int i = len - 1; i >= 0; i--) {
        if (is_digit(line[i])) {
            // 숫자를 문자열에서 숫자로 변환
            int num_start = i;
            while (i >= 0 && is_digit(line[i])) {
                i--;
            }
            i++;

            char number_str[STRING_SIZE];
            strncpy(number_str, &line[i], num_start - i + 1);
            number_str[num_start - i + 1] = '\0';

            // 숫자를 1 증가
            int number = atoi(number_str);
            number += 1;

            // 숫자를 문자열로 다시 변환
            char new_number_str[STRING_SIZE];
            sprintf(new_number_str, "%d", number);

            // 원래 숫자를 새로운 숫자로 교체
            strncpy(&line[i], new_number_str, strlen(new_number_str));
            line[i + strlen(new_number_str)] = '\n';
            break;
        }
    }
}

void like_song(const char* filename, int target_line) {
    FILE* file = fopen(filename, "r");
    if (!file) {
        perror("파일을 열 수 없습니다");
        exit(EXIT_FAILURE);
    }

    // 임시 파일을 생성하여 수정된 내용을 쓸 예정
    FILE* temp_file = fopen("temp.txt", "w");
    if (!temp_file) {
        perror("임시 파일을 열 수 없습니다");
        fclose(file);
        exit(EXIT_FAILURE);
    }

    char line[STRING_SIZE];
    int current_line = 1;

    while (fgets(line, sizeof(line), file)) {
        if (current_line == target_line) {
            // 줄의 마지막 숫자를 1 증가
            like_plus(line);
        }
        fputs(line, temp_file);
        current_line++;
    }

    fclose(file);
    fclose(temp_file);

    // 원본 파일을 덮어쓰기
    if (remove(filename) != 0) {
        perror("원본 파일을 삭제할 수 없습니다");
        exit(EXIT_FAILURE);
    }

    if (rename("temp.txt", filename) != 0) {
        perror("임시 파일을 원본 파일로 이름을 변경할 수 없습니다");
        exit(EXIT_FAILURE);
    }
}

void push_like()
{
    printf("\n좋아요를 누를 노래를 선택하세요.");
    printf("\n\n제목 / 가수 / 작곡가 / 작사가 / 장르 / 재생시간 / 앨범명 / 앨범 출시 날짜 / 좋아요\n\n");
    FILE* fp;
    fp = fopen("song_list.txt", "r"); // 텍스트 파일 불러오기
    if (fp == NULL) {
        printf("파일을 열 수 없습니다.\n");
        return;
    }

    char name[STRING_SIZE]; // 제목
    char singer[STRING_SIZE]; // 가수
    char song_writer[STRING_SIZE]; // 작곡가
    char lylic_writer[STRING_SIZE]; // 작사가
    char genre[STRING_SIZE]; // 장르
    char playtime[STRING_SIZE]; // 재생시간
    char album_name[STRING_SIZE]; // 앨범명
    char album_time[STRING_SIZE]; // 앨범 출시 날짜

    int num = 1;
    int song_count = 0; // 노래 개수를 세기 위한 변수

    char song[STRING_SIZE * 8]; // 불러올 한 줄
    while (fgets(song, sizeof(song), fp) != NULL) // 한 줄씩 불러오기
    {
        song_count++; // 노래 개수 증가
        sscanf(song, "%[^\t]\t%[^\t]\t%[^\t]\t%[^\t]\t%[^\t]\t%[^\t]\t%[^\t]\t%[^\t\n]", name, singer, song_writer, lylic_writer, genre, playtime, album_name, album_time); // 탭키를 구분자로 하나씩 불러오기
        printf("%d. %s / ", num, name); // 노래 번호와 제목 출력
        int size = 0;

        // 가수 출력
        while (1)
        {
            if (singer[size] == '|') // 인물 구분자를 만났을 때
            {
                while (1) // 띄어쓰기를 만날 때 또는 끝날 때까지 건너뛰기
                {
                    size++;
                    if (singer[size] == '\0') // 문자열이 끝났을 때
                    {
                        break;
                    }
                    else if (singer[size] == ' ') // 띄어쓰기를 만났을 때
                    {
                        size = size + 1; // 다음 인물의 이름으로 이동
                        break;
                    }
                }
            }
            if (singer[size] == '\0') // 문자열이 끝났을 때
            {
                printf(" / ");
                break;
            }
            printf("%c", singer[size]);
            size++;
        }
        size = 0;

        // 작곡가 출력
        while (1)
        {
            if (song_writer[size] == '|') // 인물 구분자를 만났을 때
            {
                while (1) // 띄어쓰기를 만날 때 또는 끝날 때까지 건너뛰기
                {
                    size++;
                    if (song_writer[size] == '\0') // 문자열이 끝났을 때
                    {
                        break;
                    }
                    else if (song_writer[size] == ' ') // 띄어쓰기를 만났을 때
                    {
                        size = size + 1;
                        break;
                    }
                }
            }
            if (song_writer[size] == '\0') // 문자열이 끝났을 때
            {
                printf(" / ");
                break;
            }
            printf("%c", song_writer[size]);
            size++;
        }
        size = 0;

        // 작사가 출력
        while (1)
        {
            if (lylic_writer[size] == '|') // 인물 구분자를 만났을 때
            {
                while (1) // 띄어쓰기를 만날 때 또는 끝날 때까지 건너뛰기
                {
                    size++;
                    if (lylic_writer[size] == '\0') // 문자열이 끝났을 때
                    {
                        break;
                    }
                    else if (lylic_writer[size] == ' ') // 띄어쓰기를 만났을 때
                    {
                        size = size + 1;
                        break;
                    }
                }
            }
            if (lylic_writer[size] == '\0') // 문자열이 끝났을 때
            {
                printf(" / ");
                break;
            }
            printf("%c", lylic_writer[size]);
            size++;
        }

        int k = strlen(name) + strlen(singer) + strlen(song_writer) + strlen(lylic_writer) + 4; // 공란 예외 처리
        for (k; k < strlen(song); k++) {
            if (song[k] == '\t')
                printf(" / ");
            else
                printf("%c", song[k]);
        }
        num++;
    }
    fclose(fp); // 노래 출력 끝

    printf("\n\n번호를 입력하세요 :");
    char input[STRING_SIZE];
    int number; // 메뉴 선택이 올바른 입력일 때 숫자 넣을 변수

    while (fgets(input, sizeof(input), stdin)) {
        // 개행문자 제거
        input[strcspn(input, "\n")] = '\0';

        if (is_valid_number(input)) { // 모든 입력이 숫자로 이루어져 있는지 확인
            number = atoi(input);
            if (number > 0 && number <= song_count) {
                break;
            }
            else {
                printf("잘못된 노래의 번호입니다. \n");
                return;
            }
        }
        else { // 숫자로만 이루어져 있지 않으면
            printf("잘못된 노래의 번호입니다.\n");
            return;
        }
    }

    const char* filename = "song_list.txt";
    like_song(filename, number);
    printf("%s의 좋아요가 1 증가 했습니다.\n", name);
}


// 각 줄의 마지막 숫자를 추출하는 함수
int getLastNumber(char* line) {
    int len = strlen(line);
    // 숫자를 찾기 위해 뒤에서부터 탐색
    for (int i = len - 1; i >= 0; i--) {
        if (is_digit(line[i])) {
            // 숫자를 문자열에서 숫자로 변환
            int num_start = i;
            while (i >= 0 && is_digit(line[i])) {
                i--;
            }
            i++;

            char number_str[STRING_SIZE]; //숫자를 저장할 char 변수
            strncpy(number_str, &line[i], num_start - i + 1);
            number_str[num_start - i + 1] = '\0';

            int number = atoi(number_str); //숫자를 int형으로 변환
            return number; //마지막 숫자 리턴
        }
    }
}

int compare(const void* a, const void* b) { //qsort()를 사용해 내림차순으로 정렬할 때 사용할 비교 함수
    int int_a = *(int*)a;
    int int_b = *(int*)b;

    if (int_a < int_b) return 1;
    else if (int_a > int_b) return -1;
    else return 0;
}

void like_song_print() //좋아요 목록 출력
{
    printf("\n내 즐겨찾기\n\n");
    printf("제목 / 가수 / 작곡가 / 작사가 / 장르 / 재생시간 / 앨범명 / 앨범출시날짜 / 좋아요\n\n");

    int last_numbers[STRING_SIZE] = { 0 }; //좋아요 숫자들을 저장할 배열, 중복이 없이 저장된다.
    int number_count = 0; //배열에 들어간 숫자 개수
    char line[STRING_SIZE * 8]; //한 줄씩 저장할 배열

    // 파일을 읽어옴
    FILE* file = fopen("song_list.txt", "r");

    while (fgets(line, sizeof(line), file) != NULL)
    {
        int last = getLastNumber(line); //좋아요 숫자를 임시 저장
        if (last != 0) //좋아요가 0이 아니면
        {
            int k = 0;
            int exist = 0; //중복이 있는지 검사하는 변수
            while (1)
            {
                if (k > number_count) //중복이 없으면
                    break;
                else if (last_numbers[k] == last) //중복이 있음
                {
                    exist = 1; //존재한다고 알려줌
                    break;
                }
                k++;
            }
            if (exist == 0) //중복이 없어서 exist가 0이면 
            {
                last_numbers[number_count] = last; //배열에 좋아요 숫자 삽입
                number_count++; //배열 크기 증가
            }
        }
    }
    fclose(file);

    qsort(last_numbers, number_count, sizeof(int), compare); //좋아요 숫자가 들어간 배열을 내림차순으로 정렬

    char name[STRING_SIZE]; //제목
    char singer[STRING_SIZE]; //가수
    char song_writer[STRING_SIZE]; //작곡가
    char lylic_writer[STRING_SIZE]; //작사가
    char genre[STRING_SIZE]; //장르
    char playtime[STRING_SIZE]; //재생시간
    char album_name[STRING_SIZE]; //앨범명
    char album_time[STRING_SIZE]; //앨범 출시 날짜

    for (int i = 0; i < number_count; i++) //좋아요 숫자가 들어간 배열만큼 반복
    {
        file = fopen("song_list.txt", "r");
        while (fgets(line, sizeof(line), file) != NULL)
        {
            int last = getLastNumber(line); //좋아요 숫자 임시 저장
            if (last == last_numbers[i]) //만약 좋아요 숫자가 좋아요 배열에 들어간 숫자와 일치하면 출력시작
            {
                sscanf(line, "%[^\t]\t%[^\t]\t%[^\t]\t%[^\t]\t%[^\t]\t%[^\t]\t%[^\t]\t%[^\t\n]", name, singer, song_writer, lylic_writer, genre, playtime, album_name, album_time); //탭키를 구분자로 하나씩 불러오기
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

                int k = strlen(name) + strlen(singer) + strlen(song_writer) + strlen(lylic_writer) + 4; //공란 예외 처리
                for (k; k < strlen(line); k++) {
                    if (line[k] == '\t')
                        printf(" / ");
                    else if (k + 1 == strlen(line) && line[k] != '\n') //마지막 줄 예외 출력
                        printf("%c\n", line[k]);
                    else
                        printf("%c", line[k]);
                }
            }
        }
        fclose(file);
    }

    return 0;
}
