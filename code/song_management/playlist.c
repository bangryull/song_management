#include "playlist.h"
#include "searchInPli.h"
#define STRING_SIZE 256
#define MAX 1000
#define FILE_NAME 100


void delName(int index, const char* fileName);


void changePlaylist();
void changeSongInPli(char pliName[]);


void playlistMenu()
{
	int loop = 1;
	while (loop)
	{
		char input[STRING_SIZE];
		int getMenu;
		printf("\n원하는 메뉴에 해당하는 숫자를 입력해주세요.\n\n");
		printf("0. 뒤로가기\n");
		printf("1. 플레이리스트 출력\n");
		printf("2. 플레이리스트 추가\n");
		printf("3. 플레이리스트 삭제\n");
		printf("4. 플레이리스트 순서 변경\n\n");
		printf("메뉴 선택: ");
		fgets(input, sizeof(input), stdin);
		input[strcspn(input, "\n")] = '\0'; // 엔터키 제거
		sscanf(input, "%d", &getMenu);

		switch (getMenu)
		{
		case 0:
		{
			//이전메뉴로 돌아갑니다.
			loop = 0;
			break;
		}
		case 1:
		{
			//플리 목록 출력
			printPlaylist();
			break;
		}
		case 2:
		{
			//플리 추가
			addPlaylist();
			break;
		}
		case 3:
		{
			//플리 삭제
			deletePlaylist();
			break;
		}
		case 4:
		{
			//플리 순서 변경 함수
			changePlaylist();
			break;
		}

		}
	}
	return;
}

//플레이리스트 목록을 출력
void printPlaylist()
{
	while (1)
	{
		system("cls");
		int getMenu;
		int index = 1;
		int listCount = 1;
		char input[STRING_SIZE];
		printf("\n");

		FILE* fp = fopen("Playlist_list.txt", "r");

		char buffer[MAX] = { 0, };

		while (fgets(buffer, MAX, fp) != NULL)
		{
			printf("%d. ", index);
			printf(buffer);
			index++;
		}


		buffer[0] = '\n';

		printf("\n원하는 플레이리스트에 해당하는 번호를 입력하세요. (숫자 \"0\"입력시 이전 페이지로 이동) : ");

		fgets(input, sizeof(input), stdin);
		input[strcspn(input, "\n")] = '\0'; // 엔터키 제거
		sscanf(input, "%d", &getMenu);

		//원하는 플레이리스트의 번호의 길이 입력받음

		if (getMenu == 0)
		{
			fclose(fp);
			break;
		}

		else
		{
			fseek(fp, 0, SEEK_SET);//파일 포인터를 다시 파일의 처음으로 이동
			char playlistName[FILE_NAME] = { 0, };
			while (fgets(playlistName, MAX, fp) != NULL) //원하는 플리에 해당하는 번호를 발견할 때까지 루프
			{
				if (listCount == getMenu)
				{
					fclose(fp);
					openPlaylist(playlistName);
				}
				else
				{
					listCount++;
				}
			}
			fclose(fp);
		}
	}

}

void openPlaylist(char playlistName[]) //playlistName의 예시 : 1. 퇴근길 플레이리스트
{
	while (1)
	{
		char input[STRING_SIZE];
		system("cls");
		//받은 플레이리스트 이름에서 공백과 숫자를 지워줌
		//ex) <1. 퇴근길 플레이리스트 -> 퇴근길 플레이리스트>로 받아 변경해줌
		char textFileName[FILE_NAME] = { 0, };
		strcpy(textFileName, playlistName);

		int len = 0; // strlen(pliName);
		len = strlen(textFileName);

		if (len > 0 && textFileName[len - 1] == '\n')
		{
			textFileName[len - 1] = '\0'; // 개행 문자를 제거
		}
		printf("\n%s\n", playlistName);

		strcat(textFileName, ".txt");

		FILE* fp = fopen(textFileName, "r");

		char buffer[MAX] = { 0, };

		int index = 1;
		while (fgets(buffer, MAX, fp) != NULL)
		{
			printf("%d. ", index);
			printf(buffer);
			index++;
		}
		fclose(fp);

		printf("\n아래의 메뉴 중 원하는 번호를 선택해주세요. \n\n");
		printf("0. 뒤로가기\n");
		printf("1. 현재 플레이리스트에 노래 추가\n");
		printf("2. 현재 플레이리스트에 노래 삭제\n");
		printf("3. 현재 플레이리스트의 노래 순서변경\n");
		printf("\n메뉴선택 : ");

		int getMenu;

		fgets(input, sizeof(input), stdin);
		input[strcspn(input, "\n")] = '\0'; // 엔터키 제거
		sscanf(input, "%d", &getMenu);

		if (getMenu == 0)
		{
			break;
		}
		else if (getMenu == 1)
		{
			addSongInPli(playlistName);
		}
		else if (getMenu == 2)
		{
			//FILE* fp = fopen(playlistName, "r");
			deleteSong(playlistName, textFileName);
		}
		else if (getMenu == 3)
		{
			changeSongInPli(textFileName);
		}

	}
	return;
}


//플레이리스트 추가
void addPlaylist()
{
	char pName[STRING_SIZE];
	FILE* fp = fopen("Playlist_list.txt", "r");
	while (1) {
		int duplicated = 0;
		printf("추가하고 싶은 플레이리스트의 이름을 입력해주세요. (공백 입력시 이전 페이지로 이동):");
		gets(pName);

		char temp[STRING_SIZE];
		while (fgets(temp, sizeof(temp), fp) != NULL) {
			char existingName[STRING_SIZE];
			strcpy(existingName, temp + 3);
			existingName[strcspn(existingName, "\n")] = 0; //개행 문자 제거
			if (strcmp(existingName, pName) == 0) {
				printf("이미 존재하는 플레이리스트 이름입니다.다른 입력을 입력해주세요.\n");
				duplicated = 1;
				break;
			}
		}

		if (!duplicated) { //중복이 없으면 반복 종료
			break;
		}
	}

	int j = 0;
	int count = 0;
	// 입력받은 문자열이 공백과 탭으로만 이루어졌는지 확인
	while (pName[j] != '\0')
	{
		if (pName[j] == ' ' || pName[j] == '\t') {
			count++;
		}
		j++;
	}
	//공백 입력시 이전 페이지로 이동
	if (j == count) {
		if (j == count) {
			fclose(fp);
			playlistMenu();
		}
	}
	//추가할 번호 지정
	fp = fopen("Playlist_list.txt", "r");
	int num = 0;  // 기존에 존재하는 플레이리스트 개수
	char temp[STRING_SIZE];
	while (fgets(temp, sizeof(temp), fp) != NULL) {
		if (temp[0] >= '0' && temp[0] <= '9') {
			num++;
		}
	}


	fp = fopen("Playlist_list.txt", "a");
	fprintf(fp, "\n%d. %s", num + 1, removeSpace(pName)); // 파일에 플레이리스트 추가 

	// 플레이리스트 텍스트 파일 생성
	char filename[STRING_SIZE];
	sprintf(filename, "%s.txt", removeSpace(pName));
	fp = fopen(filename, "a");

	fclose(fp);
}

//플레이리스트 삭제
void deletePlaylist()
{
	while (1)
	{
		system("cls");
		int getMenu;
		char input[STRING_SIZE];
		printf("\n플레이리스트 목록\n\n");

		FILE* fp = fopen("Playlist_list.txt", "r");

		char buffer[MAX] = { 0, };

		int index = 1;
		if (fgets(buffer, MAX, fp) != NULL)
		{
			printf("%d. ", index);
			printf(buffer);
			index++;
		}
		memset(buffer, 0, MAX);

		printf("\n삭제할 플레이리스트의 번호를 입력해주세요 (숫자 \"0\"입력시 이전 페이지로 이동) : ");


		fseek(fp, 0, SEEK_SET);//파일 포인터를 다시 파일의 처음으로 이동

		fgets(input, sizeof(input), stdin);
		input[strcspn(input, "\n")] = '\0'; // 엔터키 제거

		if (sscanf(input, "%d", &getMenu) == 0)
		{
			continue;
		}//버퍼비우기

		if (getMenu == 0)
		{
			fclose(fp);
			break;
		}
		else
		{
			char playlistName[MAX] = { 0, };


			while (feof(fp) == 0) //원하는 플리에 해당하는 번호를 발견할 때까지 루프
			{
				int pliIndexToRemove = 1;

				fgets(playlistName, MAX, fp);
				//원하는 플리에 매칭된 번호인가 체크
				if (getMenu == pliIndexToRemove)
				{
					fclose(fp);

					int len = 0; // strlen(pliName);
					len = strlen(playlistName);

					if (len > 0 && playlistName[len - 1] == '\n')
					{
						playlistName[len - 1] = '\0'; // 개행 문자를 제거
					}

					strcat(playlistName, ".txt");
					//플레이리스트 목록(Playlist_list.txt)에서 지울 플리 이름을 지워주기
					delName(getMenu, "Playlist_list.txt"); //인덱스 번호로 파악해서 지워줌

					remove(playlistName);
					break;
					//플리목록을 정리(플리 번호) 등등
				}

				pliIndexToRemove++;
			}
			fclose(fp);
		}
	}

}

void delName(int index, const char* fileName)//파일에서 index에 해당하는 노래 또는 플리를 삭제
{

	char sourcefileName[FILE_NAME] = { 0, };
	strcpy(sourcefileName, fileName);
	FILE* sourceFile = fopen(sourcefileName, "r");//Playlist_list.txt파일을 오픈


	FILE* tempFile; //새로 생성할 파일의 포인터
	char tempName[30] = "tempFile.txt";
	char buffer[MAX];

	tempFile = fopen(tempName, "w");
	int currentLine = 1;
	int lineToRemove = index;

	while (fgets(buffer, MAX, sourceFile) != NULL)
	{
		if (currentLine != lineToRemove) {
			fputs(buffer, tempFile);
		}
		currentLine++;
	}
	fclose(sourceFile);
	fclose(tempFile);

	remove(sourcefileName);
	rename("tempFile.txt", sourcefileName);

	return;
}

void addSongInPli(char pliName[])//플레이리스트의 이름을 받음
{
	while (1)
	{
		system("cls");
		printf("\n");
		char textFileName[FILE_NAME] = { 0, };
		strcpy(textFileName, pliName);

		int len = 0;
		len = strlen(textFileName);

		if (len > 0 && textFileName[len - 1] == '\n')
		{
			textFileName[len - 1] = '\0'; // 개행 문자를 제거
		}

		strcat(textFileName, ".txt");

		int count = 1;
		char getMenu[STRING_SIZE];

		char buffer[MAX] = { 0, };

		FILE* songList = fopen("song_list.txt", "r");//모든 노래들을 출력
		while (fgets(buffer, sizeof(buffer), songList) != NULL) {
			printf("%d. ", count);
			printf("%s", buffer);
			count++;
		}
		fclose(songList);

		memset(buffer, 0, sizeof(buffer));//버퍼 비워줌

		printf("\n플레이리스트에 추가할 노래 번호를 입력하거나 \"검색\"을 입력하세요\n");
		printf("숫자 \"0\"을 입력시 이전 페이지로 이동합니다. \"검색\"을 입력시 노래를 검색하여 추가할 수 있습니다.\n\n");
		printf("메뉴 선택 : ");

		char input[STRING_SIZE];
		fgets(input, sizeof(input), stdin);
		input[strcspn(input, "\n")] = '\0'; // 엔터키 제거
		sscanf(input, "%s", getMenu);

		if (!strcmp(getMenu, "검색"))
		{
			//searchMenuInPli(textFileName);
		}
		else if (!strcmp(getMenu, "0"))
			break;
		else
		{
			char* endptr = NULL;
			int songNum = 0;
			songNum = strtol(getMenu, &endptr, 10);

			if (endptr == getMenu) {
				break;
				printf("변환 실패: 숫자로 시작하는 문자열이 아닙니다.\n");
			}
			else if (*endptr != '\0') {
				break;
				printf("변환 실패: 숫자로 변환된 후에 남아있는 문자열: %s\n", endptr);
			}
			else
			{
				int lineNumber = 0;
				if (count - 1 < songNum)//현재 노래 수보다 큰 숫자를 받으면 과정을 생략해준다.
					continue;
				else
				{
					FILE* songList = fopen("song_list.txt", "r");
					FILE* playlist = fopen(textFileName, "a");

					if (playlist == NULL)
						printf("파일을 열 수 없습니다!\n");
					while (fgets(buffer, sizeof(buffer), songList) != NULL)
					{
						lineNumber++;
						if (lineNumber == songNum) {
							fputs(buffer, playlist);
							//fputs("\n", playlist);

							fclose(playlist);
							fclose(songList);
							//fileArrange(playlist, pliName); //번호를 정렬

							break; // 찾은 후에는 더 이상 반복할 필요가 없으므로 반복문을 종료
						}
					}

				}
			}

		}

	}
	return;
}


//플레이리스트에서 노래를 삭제 ->현재 플레이리스트의 file pointer는 열린상태
void deleteSong(char* pliName, char* fileName) //인자로 받은 pliName은 ".txt"를 포함하지 않은 형식이다.
{
	while (1)
	{
		int index = 1;

		system("cls");
		char playlistName[FILE_NAME] = { 0, };

		strcpy(playlistName, pliName);

		int len = 0;
		len = strlen(playlistName);

		if (len > 0 && playlistName[len - 1] == '\n')
		{
			playlistName[len - 1] = '\0'; // 개행 문자를 제거
		}

		FILE* fp = fopen(fileName, "r");

		int getMenu;
		char input[STRING_SIZE];

		printf("\n\n%s\n\n", playlistName);

		char buffer[MAX] = { 0, };

		while (fgets(buffer, MAX, fp) != NULL)
		{
			printf("%d. ", index);
			printf(buffer);
			index++;
		}


		//printf("\n%s\n", buffer);

		printf("\n숫자 \"0\"을 입력시 이전 페이지로 이동합니다.\n");
		printf("플레이리스트에서 삭제할 노래에 해당하는 번호를 입력해주세요 : ");

		fgets(input, sizeof(input), stdin);
		input[strcspn(input, "\n")] = '\0'; // 엔터키 제거
		sscanf(input, "%d", &getMenu);



		if (getMenu == 0)
		{
			fclose(fp);
			break;
		}
		else
		{
			fclose(fp);

			delName(getMenu, fileName);

			printf("\n");
		}
	}
}

char* removeSpace(char* str) {
	char* start = str;
	char* finish = str + strlen(str) - 1;
	//좌측 제거
	while (*start != '\0') {
		if ((*start == ' ') || (*start == '\t'))
			start++;
		else
			break;
	}
	//우측 제거
	while (1)
	{
		if ((*finish == ' ') || (*finish == '\t'))
			finish--;
		else {
			*(finish + 1) = '\0';
			break;
		}
	}

	return start;
}



void changePlaylist() {
	while (1) {
		system("cls");
		int index = 1;
		printf("플레이리스트 목록\n\n");

		FILE* fp = fopen("Playlist_list.txt", "r");
		char buffer[MAX] = { 0, };

		while (fgets(buffer, MAX, fp) != NULL)
		{
			printf("%d. ", index);
			printf(buffer);
			index++;
		}
		//이후 index는 총 줄의 개수 + 1을 나타냄
		buffer[0] = '\n';


		char inputNums[STRING_SIZE];
		printf("\n순서를 바꿀 플레이리스트의 두 번호를 입력해주세요 (숫자 \"0\"입력시 이전 페이지로 이동)");
		gets(inputNums);
		strcpy(inputNums, removeSpace(inputNums));

		int changeLineNum1, changeLineNum2;
		for (int i = 0; i < strlen(inputNums); i++) {

			if (isdigit(inputNums[i]) == 0 && i >= 1) { //i번째가 자연수가 아니라면 0번째부터 i-1번째까지 temp에 복사하고 
				char temp[STRING_SIZE];
				int j = 0;
				for (j = 0; j < i; j++) {
					temp[j] = inputNums[j];
				}
				temp[j] = '\0';
				changeLineNum1 = atoi(temp); //앞 부분 숫자를 chagneLine1에 저장

				char temp2[STRING_SIZE];
				int k = 0, l;
				for (l = j + 1; k < strlen(inputNums); k++, l++) {
					temp2[k] = inputNums[l];
				}
				temp2[k] = '\0';
				changeLineNum2 = atoi(temp2);//e뒷 부분 숫자를 chagneLine2에 저장
			}
		}


		if (inputNums[0] == '0' && inputNums[1] == '\0') {
			fclose(fp);
			system("cls");
			break;
		}

		if (changeLineNum1 < 1 || changeLineNum2 < 1 || changeLineNum1 >= index || changeLineNum2 >= index) {
			continue;
		}


		{
			char lines[50][STRING_SIZE];
			int line_count = 0;

			rewind(fp);

			char buffer[STRING_SIZE];

			while (fgets(buffer, STRING_SIZE, fp) != NULL) {
				buffer[strlen(buffer) - 1] = '\0';
				strcpy(lines[line_count], buffer);
				line_count++;
			}
			changeLineNum1--;
			changeLineNum2--;
			char temp[STRING_SIZE];
			strcpy(temp, lines[changeLineNum1]);
			strcpy(lines[changeLineNum1], lines[changeLineNum2]);
			strcpy(lines[changeLineNum2], temp);

			fp = fopen("Playlist_list.txt", "w");
			for (int i = 0; i < line_count; i++) {
				fputs(lines[i], fp);
				fputs("\n", fp);
			}

		}

		fclose(fp);
	}
}

void changeSongInPli(char pliName[]) {
	while (1) {
		system("cls");
		int index = 1;
		printf("%s\n\n", pliName);

		FILE* fp = fopen(pliName, "r");
		char buffer[MAX] = { 0, };

		while (fgets(buffer, MAX, fp) != NULL)
		{
			printf("%d. ", index);
			printf(buffer);
			index++;
		}
		buffer[0] = '\n';

		char inputNums[STRING_SIZE];
		printf("\n숫자 \"0\"을 입력시 이전 페이지로 이동합니다.\n");
		printf("플레이리스트에서 순서를 바꿀 노래에 해당하는 두 번호를 입력해주세요 :");
		gets(inputNums);
		strcpy(inputNums, removeSpace(inputNums));

		int changeLineNum1, changeLineNum2;
		for (int i = 0; i < strlen(inputNums); i++) {

			if (isdigit(inputNums[i]) == 0 && i >= 1) { //i번째가 자연수가 아니라면 0번째부터 i-1번째까지 temp에 복사하고 
				char temp[STRING_SIZE];
				int j = 0;
				for (j = 0; j < i; j++) {
					temp[j] = inputNums[j];
				}
				temp[j] = '\0';
				changeLineNum1 = atoi(temp); //앞 부분 숫자를 chagneLine1에 저장

				char temp2[STRING_SIZE];
				int k = 0, l;
				for (l = j + 1; k < strlen(inputNums); k++, l++) {
					temp2[k] = inputNums[l];
				}
				temp2[k] = '\0';
				changeLineNum2 = atoi(temp2);//뒷 부분 숫자를 chagneLine2에 저장
			}
		}




		if (inputNums[0] == '0' && inputNums[1] == '\0') {
			fclose(fp);
			system("cls");
			break;
		}

		if (changeLineNum1 < 1 || changeLineNum2 < 1 || changeLineNum1 >= index || changeLineNum2 >= index) {
			continue;
		}


		{
			char lines[50][STRING_SIZE];
			int line_count = 0;

			rewind(fp);

			char buffer[STRING_SIZE];

			while (fgets(buffer, STRING_SIZE, fp) != NULL) {
				buffer[strlen(buffer) - 1] = '\0';
				strcpy(lines[line_count], buffer);
				line_count++;
			}
			changeLineNum1--;
			changeLineNum2--;

			char temp[STRING_SIZE];
			strcpy(temp, lines[changeLineNum1]);
			strcpy(lines[changeLineNum1], lines[changeLineNum2]);
			strcpy(lines[changeLineNum2], temp);


			fp = fopen(pliName, "w");
			for (int i = 0; i < line_count; i++) {

				fputs(lines[i], fp);
				fputs("\n", fp);
			}

		}
		fclose(fp);
	}
}
