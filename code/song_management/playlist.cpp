#include "playlist.h"
#include "searchInPli.h"
#include <stdexcept>
#define STRING_SIZE 256

const int FILE_NAME = 100;
const int MAX = 100000;

void playlistMenu()
{
	bool loop = true;
	while (loop)
	{
		int getMenu;
		printf("\n원하는 메뉴에 해당하는 숫자를 입력해주세요.\n\n");
		printf("0. 뒤로가기\n");
		printf("1. 플레이리스트 출력\n");
		printf("2. 플레이리스트 추가\n");
		printf("3. 플레이리스트 삭제\n\n");
		printf("메뉴 선택: ");
		scanf("%d", &getMenu);

		while (getchar() != '\n');//버퍼 비우기

		switch (getMenu)
		{
			case 0:
			{
				//이전메뉴로 돌아갑니다.
				loop = false;
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
			//default:
			//{
			//	//다시 플리메뉴 선택 페이지로 이동
			//	break;
			//}
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
		int listCount = 0;
		printf("\n");

		FILE* fp = fopen("Playlist_list.txt", "r");

		char buffer[MAX] = { 0, };

		fread(buffer, 1, MAX, fp);
		printf("%s", buffer);


		buffer[0] = '\n';

		printf("\n원하는 플레이리스트에 해당하는 번호를 입력하세요. (숫자 \"0\"입력시 이전 페이지로 이동) : ");



		cin>> getMenu;//원하는 플리에 해당하는 번호 입력받기
		cin.ignore();

		int numLength = getMenu/10 + 1; //원하는 플레이리스트의 번호의 길이 입력받음

		if (cin.fail())
		{
			cin.clear(); // cin의 상태를 초기화
			cin.ignore(1000, '\n'); // 입력 버퍼를 비우기
		}
		else if (getMenu == 0)
		{
			fclose(fp);
			break;
		}
		
		else
		{
			fseek(fp, 0, SEEK_SET);//파일 포인터를 다시 파일의 처음으로 이동
			char playlistName[MAX] = { 0, };
			while (fgets(playlistName, MAX, fp)!=NULL || listCount<=getMenu) //원하는 플리에 해당하는 번호를 발견할 때까지 루프
			{
				//fgets(playlistName, MAX, fp);

				string index = "";

				int j = 0;

				for (int i = 0; i < numLength; i++)
				{
					index += playlistName[i];
					j++;
				}
			
				//원하는 플리에 매칭된 번호인가 체크
				if (stoi(index) == getMenu && playlistName[j] == '.') //index가 "12"일때와 플리에 매칭된 번호 "123. "이 동일시 되는 것을 방지
				{
					fclose(fp);
					openPlaylist(playlistName);
					break;
				}
			}
			
		}
	}
	
}

void openPlaylist(char playlistName[]) //playlistName의 예시 : 1. 퇴근길 플레이리스트
{
	while (1)
	{
		system("cls");
		//받은 플레이리스트 이름에서 공백과 숫자를 지워줌
		//ex) <1. 퇴근길 플레이리스트 -> 퇴근길 플레이리스트>로 받아 변경해줌
		char pliName[FILE_NAME] = { 0, };
		strcpy(pliName, playlistName);

		int i = 0;
		char* playlistName = pliName + 3; //숫자를 생략해줌
		char copyPliName[FILE_NAME] = {0,};
		strcpy(copyPliName, pliName);
		int len = 0; // strlen(pliName);
		len = strlen(pliName);

		if (len > 0 && pliName[len - 1] == '\n') {
			pliName[len - 1] = '\0'; // 개행 문자를 제거
		}
		printf("\n%s\n", playlistName);

		strcat(playlistName, ".txt");

		FILE* fp = fopen(playlistName, "r");

		char buffer[MAX] = { 0, };

		fread(buffer, 1, MAX, fp);
		
		printf("\n%s\n", buffer);

		fclose(fp);

		printf("\n아래의 메뉴 중 원하는 번호를 선택해주세요. \n\n");
		printf("0. 뒤로가기\n");
		printf("1. 현재 플레이리스트에 노래 추가\n");
		printf("2. 현재 플레이리스트에 노래 삭제\n");
		printf("\n메뉴선택 : ");

		int getMenu;

		scanf("%d", &getMenu);
		while (getchar() != '\n');

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
			deleteSong(copyPliName, playlistName);
		}

	}
	return;
}


//플레이리스트 추가
void addPlaylist()
{
	char pName[STRING_SIZE];
	printf("추가하고 싶은 플레이리스트의 이름을 입력해주세요. (공백 입력시 이전 페이지로 이동):");
	fgets(pName,sizeof(pName),stdin);

	int i = 0;
	int isAllSpace = 0;
	// 문자열이 공백과 탭으로만 이루어졌는지 확인
	while (pName[i] != '\0') {
		if (pName[i] != ' ' && pName[i] != '\t') {
			isAllSpace = 1;
			break;
		}
		i++;
	}
	if (isAllSpace) {
	}

	FILE* fp = fopen("Playlist_list.txt", "a");
	fputs(removeSpace(pName), fp);
	fputs("\n", fp);

	fclose(fp);
}

//플레이리스트 삭제
void deletePlaylist()
{
	while (1)
	{
		system("cls");
		int getMenu;
		
		printf("\n플레이리스트 목록\n\n");

		FILE* fp = fopen("Playlist_list.txt", "r");

		char buffer[MAX] = { 0, };

		fread(buffer, 1, MAX, fp);
		printf("%s", buffer);

		printf("\n삭제할 플레이리스트의 번호를 입력해주세요 (숫자 \"0\"입력시 이전 페이지로 이동) : ");


		fseek(fp, 0, SEEK_SET);//파일 포인터를 다시 파일의 처음으로 이동

		cin>>getMenu;
		cin.ignore();//버퍼비우기

		int numLength = getMenu/10+1;

		if (cin.fail())
		{
			cin.clear(); // cin의 상태를 초기화
			cin.ignore(1000, '\n'); // 입력 버퍼를 비우기
		}
		else if (getMenu == 0)
		{
			fclose(fp);
			break;
		}
		else
		{
			char playlistName[MAX] = { 0, };


			while (feof(fp) == 0) //원하는 플리에 해당하는 번호를 발견할 때까지 루프
			{
				string index = "";

				fgets(playlistName, MAX, fp);
				 //원하는 플리에 매칭된 번호인가 체크
				int j = 0;

				for (int i = 0; i < numLength; i++)
				{
					index += playlistName[i];
					j++;
				}
				if (index == "\n")
					break;
				if (stoi(index) == getMenu && playlistName[j] == '.') //index가 "12"일때와 플리에 매칭된 번호 "123. "이 동일시 되는 것을 방지
				{
					char* pliName = playlistName + 3;

					int len = strlen(pliName);

					if (len > 0 && pliName[len - 1] == '\n')
					{
						pliName[len - 1] = '\0'; // 개행 문자를 제거
					}

					fclose(fp);

					strcat(pliName, ".txt");
					//플레이리스트 목록(Playlist_list.txt)에서 지울 플리 이름을 지워주기
					delName(index, "Playlist_list.txt"); //인덱스 번호로 파악해서 지워줌

					FILE* fp = fopen("Playlist_list.txt", "r"); //플리의 인덱스 번호를 정렬하기 위해 다시 연다
					fileArrange(fp, "Playlist_list.txt"); //정렬하고 파일닫기

					remove(pliName);
					break;
					//플리목록을 정리(플리 번호) 등등
				}

			}
			fclose(fp);
		}
	}
	
}

void delName(string index, const char* fileName)//파일에서 index에 해당하는 노래 또는 플리를 삭제
{
	
	char sourcefileName[FILE_NAME] = {0,};
	strcpy(sourcefileName, fileName);
	FILE* sourceFile = fopen(sourcefileName, "r");//Playlist_list.txt파일을 오픈


	FILE* tempFile; //새로 생성할 파일의 포인터
	char tempName[30] = "tempFile.txt";
	char buffer[MAX];
	
	tempFile = fopen(tempName, "w");
	int currentLine = 1;
	int lineToRemove = stoi(index);

	while (fgets(buffer, MAX, sourceFile) != NULL)
	{
		if (currentLine != lineToRemove) {
			fputs(buffer, tempFile);
		}
		currentLine++;
	}
	fputs("\n", tempFile);
	
	fclose(sourceFile);
	fclose(tempFile);

	remove(sourcefileName);
	rename("tempFile.txt", sourcefileName);

	return;
}

void fileArrange(FILE* fp, const char* pliName)//텍스트 파일에 쓰여진 인덱스를 정리해줌
{
	int indexCount = 0;
	int currentLine = 1;
	char buffer[MAX] = { 0, };
	char sourceName[MAX] = {0, };
	char tempName[MAX] = "temp.txt";

	strcpy(sourceName, pliName);
	//const char* sourceName = strcat(source, ".txt");
	
	FILE* tempFile = fopen(tempName, "w");

	while (fgets(buffer, sizeof(buffer), fp)!=NULL)//라인 인덱스를 순서대로 정렬
	{
		if (strlen(buffer) <= 2)
			break;
		char index[MAX] = {0, };//라인 정렬을 위한 index받기용
		sprintf(index, "%d", currentLine); 
		int spaceToReplace = 0; //라인에 따라 수정할 인데스를 입력할 공간의 수
		

		while (buffer[spaceToReplace+ 1] == '.')
		{
			spaceToReplace++;
		}
		
		for (int i = 0; i < spaceToReplace; i++)
		{
			for(int j =0; j<strlen(buffer); j++)
				buffer[j] = buffer[j + 1];
			buffer[strlen(buffer)-1] = NULL;
		} //인덱스 지워주기 ( ex)"1. 출근길 플레이리스트"->". 출근길 플레이리스트")

		string str1(index);
		string str2(buffer);

		str1 = str1 + str2 + "\n"; //새로 정렬된 인덱스와 기존의 플레이리스트 이름에서 인덱스를 지워준 부분을 합쳐준다.
		const char* newInput = str1.c_str();
		fputs(newInput, tempFile);
		
		memset(buffer, 0, sizeof(buffer));//버퍼를 비워줌

		currentLine++;
	}

	fclose(fp);
	fclose(tempFile);

	remove(sourceName);
	rename(tempName, sourceName);

	return;
}

void addSongInPli(char pliName[])//텍스트파일의 이름을 받음
{
	while (1)
	{
		system("cls");
		printf("\n");

		int count = 1;
		string getMenu;

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
		cin >> getMenu;
		cin.ignore();

		if (getMenu == "검색")
		{
			searchMenuInPli(pliName);
		}
		else
		{

			int songNum = 0;
			try {
				// 문자열을 정수로 변환합니다.
				songNum = stoi(getMenu);
			}
			catch (const invalid_argument& e) {
				continue;
				// 변환할 수 없는 경우 예외 처리
			}
			if (songNum == 0)
			{
				break;
			}
			int lineNumber = 0;
			if (count-1 < songNum)//현재 노래 수보다 큰 숫자를 받으면 과정을 생략해준다.
				continue;
			else
			{
				FILE* songList = fopen("song_list.txt", "r");
				FILE* playlist = fopen(pliName, "a");

				if (playlist == NULL)
					printf("파일을 열 수 없습니다!\n");
				while (fgets(buffer, sizeof(buffer), songList) != NULL)
				{
					lineNumber++;
					if (lineNumber == songNum) {
						fputs("1. ", playlist);
						fputs(buffer, playlist);
						fputs("\n", playlist);

						fclose(playlist);
						FILE* fp = fopen(pliName, "r"); //파일 내 커서의 위치를 초기화
						fileArrange(playlist, pliName); //번호를 정렬

						break; // 찾은 후에는 더 이상 반복할 필요가 없으므로 반복문을 종료
					}
				}

			}

		}

	}

	return;
}


//플레이리스트에서 노래를 삭제 ->현재 플레이리스트의 file pointer는 열린상태
void deleteSong( char* pliName, char* fileName) //인자로 받은 pliName은 ".txt"를 포함하지 않은 형식이다.
{
	while (1)
	{
		system("cls");
		char playlistName[FILE_NAME] = { 0, };
		strcpy(playlistName, pliName);
		char* noNumName = playlistName + 3;
		
		FILE* fp = fopen(fileName, "r");

		string getMenu;

		printf("\n\n%s\n\n", noNumName);

		char buffer[MAX] = { 0, };

		fread(buffer, 1, MAX, fp);


		printf("\n%s\n", buffer);

		printf("\n숫자 \"0\"을 입력시 이전 페이지로 이동합니다.\n");
		printf("플레이리스트에서 삭제할 노래에 해당하는 번호를 입력해주세요 : ");

		cin >> getMenu;
		cin.clear();

		int numLength = getMenu.length();

		if (getMenu == "0")
		{
			fclose(fp);
			break;
		}
		else
		{
			fclose(fp);

			delName(getMenu, fileName);

			FILE* fp = fopen(fileName, "r");
			fileArrange(fp, fileName);

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
