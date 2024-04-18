#include "playlist.h"
#define STRING_SIZE 256

const int FILE_NAME = 100;
const int MAX = 100000;

void playlistMenu()
{
	char getMenu;
	bool loop = true;
	while (loop)
	{
		printf("\n���ϴ� �޴��� �ش��ϴ� ���ڸ� �Է����ּ���.\n\n");
		printf("0. �ڷΰ���\n");
		printf("1. �÷��̸���Ʈ ���\n");
		printf("2. �÷��̸���Ʈ �߰�\n");
		printf("3. �÷��̸���Ʈ ����\n\n");
		printf("�޴� ����: ");
		scanf("%c", &getMenu);

		while (getchar() != '\n');//���� ����

		switch (getMenu)
		{
			case '0':
			{
				//�����޴��� ���ư��ϴ�.
				loop = false;
				break;
			}
			case '1':
			{
				//�ø� ��� ���
				printPlaylist();
				break;
			}
			case '2':
			{
				//�ø� �߰�
				addPlaylist();
				break;
			}
			case '3':
			{
				//�ø� ����
				deletePlaylist();
				break;
			}
			default:
			{
				//�ٽ� �ø��޴� ���� �������� �̵�
				playlistMenu();
				break;
			}
		}
	}
	return;
}

//�÷��̸���Ʈ ����� ���
void printPlaylist()
{
	while (1)
	{
		string getMenu;

		printf("\n");

		FILE* fp = fopen("Playlist_list.txt", "r");

		char buffer[MAX] = { 0, };

		fread(buffer, 1, MAX, fp);
		printf("%s", buffer);


		buffer[0] = '\n';

		printf("\n���ϴ� �÷��̸���Ʈ�� �ش��ϴ� ��ȣ�� �Է��ϼ���. (���� \"0\"�Է½� ���� �������� �̵�) : ");



		cin>> getMenu;//���ϴ� �ø��� �ش��ϴ� ��ȣ �Է¹ޱ�
		while (getchar() != '\n');

		int numLength = getMenu.length();//���ϴ� �÷��̸���Ʈ�� ��ȣ�� ���� �Է¹���

		if (getMenu == "0")
		{
			fclose(fp);
			break;
		}
		else
		{
			fseek(fp, 0, SEEK_SET);//���� �����͸� �ٽ� ������ ó������ �̵�
			char playlistName[MAX] = { 0, };
			while (feof(fp) == 0) //���ϴ� �ø��� �ش��ϴ� ��ȣ�� �߰��� ������ ����
			{
				fgets(playlistName, MAX, fp);

				string index = "";

				int j = 0;

				for (int i = 0; i < numLength; i++)
				{
					index += playlistName[i];
					j++;
				}
			
				//���ϴ� �ø��� ��Ī�� ��ȣ�ΰ� üũ
				if (index == getMenu && playlistName[j] == '.') //index�� "12"�϶��� �ø��� ��Ī�� ��ȣ "123. "�� ���Ͻ� �Ǵ� ���� ����
				{
					openPlaylist(playlistName);
					break;
				}
			}
			fclose(fp);
		}
	}
	
}

void openPlaylist(char playlistName[]) //playlistName�� ���� : 1. ��ٱ� �÷��̸���Ʈ
{
	int loopCount = 0;
	while (1)
	{
		//���� �÷��̸���Ʈ �̸����� ����� ���ڸ� ������
		//ex) <1. ��ٱ� �÷��̸���Ʈ -> ��ٱ� �÷��̸���Ʈ>�� �޾� ��������
		char pliName[FILE_NAME] = { 0, };
		strcpy(pliName, playlistName);

		int i = 0;
		char* playlistName = pliName + 3; //���ڸ� ��������
		char copyPliName[FILE_NAME] = {0,};
		strcpy(copyPliName, pliName);
		int len = 0; // strlen(pliName);
		len = strlen(pliName);

		if (len > 0 && pliName[len - 1] == '\n') {
			pliName[len - 1] = '\0'; // ���� ���ڸ� ����
		}
		printf("%s\n", playlistName);

		strcat(playlistName, ".txt");

		FILE* fp = fopen(playlistName, "r");

		//������ ��ã���� ���
		/*if (fp == NULL)
		{
			exit(1);
		}*/

		//�÷��̸���Ʈ �� �뷡���� ���
		char buffer[MAX] = { 0, };

		fseek(fp, 0, SEEK_SET);//���� �����͸� �ٽ� ������ ó������ �̵�, ������ ���� ���

		fread(buffer, 1, MAX, fp);
		
		printf("\n%s\n", buffer);

		fclose(fp);

		printf("\n�Ʒ��� �޴� �� ���ϴ� ��ȣ�� �������ּ���. \n\n");
		printf("0. �ڷΰ���\n");
		printf("1. ���� �÷��̸���Ʈ�� �뷡 �߰�\n");
		printf("2. ���� �÷��̸���Ʈ�� �뷡 ����\n");
		printf("\n�޴����� : ");

		char getMenu;

		scanf("%c", &getMenu);
		while (getchar() != '\n');

		if (getMenu == '0')
		{
			break;
		}
		else if (getMenu == '1')
		{
			FILE* fp = fopen(playlistName, "r");
			//addSong(fp);
		}
		else if (getMenu == '2')
		{
			//FILE* fp = fopen(playlistName, "r");
			deleteSong(copyPliName, playlistName);
		}

	}
	return;
}


//�÷��̸���Ʈ �߰�
void addPlaylist()
{
	char pName[STRING_SIZE];
	printf("�߰��ϰ� ���� �÷��̸���Ʈ�� �̸��� �Է����ּ���. (���� �Է½� ���� �������� �̵�):");
	fgets(pName,sizeof(pName),stdin);

	int i = 0;
	int isAllSpace = 0;
	// ���ڿ��� ����� �����θ� �̷�������� Ȯ��
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

//�÷��̸���Ʈ ����
void deletePlaylist()
{
	while (1)
	{
		string getMenu;
		
		printf("\n�÷��̸���Ʈ ���\n\n");

		FILE* fp = fopen("Playlist_list.txt", "r");

		char buffer[MAX] = { 0, };

		fread(buffer, 1, MAX, fp);
		printf("%s", buffer);

		printf("\n������ �÷��̸���Ʈ�� ��ȣ�� �Է����ּ��� (���� \"0\"�Է½� ���� �������� �̵�) : ");


		fseek(fp, 0, SEEK_SET);//���� �����͸� �ٽ� ������ ó������ �̵�

		cin>>getMenu;
		while (getchar() != '\n');//���ۺ���

		int numLength = getMenu.length();


		if (getMenu == "0")
		{
			fclose(fp);
			break;
		}
		else
		{
			char playlistName[MAX] = { 0, };


			while (feof(fp) == 0) //���ϴ� �ø��� �ش��ϴ� ��ȣ�� �߰��� ������ ����
			{
				string index = "";

				fgets(playlistName, MAX, fp);
				 //���ϴ� �ø��� ��Ī�� ��ȣ�ΰ� üũ
				int j = 0;

				for (int i = 0; i < numLength; i++)
				{
					index += playlistName[i];
					j++;
				}
				if (index == getMenu && playlistName[j] == '.') //index�� "12"�϶��� �ø��� ��Ī�� ��ȣ "123. "�� ���Ͻ� �Ǵ� ���� ����
				{
					char* pliName = playlistName + 3;

					int len = strlen(pliName);

					if (len > 0 && pliName[len - 1] == '\n')
					{
						pliName[len - 1] = '\0'; // ���� ���ڸ� ����
					}

					fclose(fp);

					strcat(pliName, ".txt");
					//�÷��̸���Ʈ ���(Playlist_list.txt)���� ���� �ø� �̸��� �����ֱ�
					delName(index, "Playlist_list.txt"); //�ε��� ��ȣ�� �ľ��ؼ� ������

					FILE* fp = fopen("Playlist_list.txt", "r"); //�ø��� �ε��� ��ȣ�� �����ϱ� ���� �ٽ� ����
					fileArrange(fp, "Playlist_list.txt"); //�����ϰ� ���ϴݱ�

					remove(pliName);
					break;
					//�ø������ ����(�ø� ��ȣ) ���
				}

			}
			fclose(fp);
		}
	}
	
}

void delName(string index, const char* fileName)//���Ͽ��� index�� �ش��ϴ� �뷡 �Ǵ� �ø��� ����
{
	
	char sourcefileName[FILE_NAME] = {0,};
	strcpy(sourcefileName, fileName);
	FILE* sourceFile = fopen(sourcefileName, "r");//Playlist_list.txt������ ����


	FILE* tempFile; //���� ������ ������ ������
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

void fileArrange(FILE* fp, const char* pliName)//�ؽ�Ʈ ���Ͽ� ������ �ε����� ��������
{
	int indexCount = 0;
	int currentLine = 1;
	char buffer[MAX] = { 0, };
	char sourceName[MAX] = {0, };
	char tempName[MAX] = "temp.txt";

	strcpy(sourceName, pliName);
	//const char* sourceName = strcat(source, ".txt");
	
	FILE* tempFile = fopen(tempName, "w");

	while (fgets(buffer, sizeof(buffer), fp)!=NULL)//���� �ε����� ������� ����
	{
		if (strlen(buffer) <= 2)
			break;
		char index[MAX] = {0, };//���� ������ ���� index�ޱ��
		sprintf(index, "%d", currentLine); 
		int spaceToReplace = 0; //���ο� ���� ������ �ε����� �Է��� ������ ��
		

		while (buffer[spaceToReplace+ 1] == '.')
		{
			spaceToReplace++;
		}
		
		for (int i = 0; i < spaceToReplace; i++)
		{
			for(int j =0; j<strlen(buffer); j++)
				buffer[j] = buffer[j + 1];
			buffer[strlen(buffer)-1] = NULL;
		} //�ε��� �����ֱ� ( ex)"1. ��ٱ� �÷��̸���Ʈ"->". ��ٱ� �÷��̸���Ʈ")

		string str1(index);
		string str2(buffer);

		str1 = str1 + str2 + "\n"; //���� ���ĵ� �ε����� ������ �÷��̸���Ʈ �̸����� �ε����� ������ �κ��� �����ش�.
		const char* newInput = str1.c_str();
		fputs(newInput, tempFile);
		
		memset(buffer, 0, sizeof(buffer));//���۸� �����

		currentLine++;
	}

	fclose(fp);
	fclose(tempFile);

	remove(sourceName);
	rename(tempName, sourceName);

	return;
}

void addSong()
{

}


//�÷��̸���Ʈ���� �뷡�� ���� ->���� �÷��̸���Ʈ�� file pointer�� ��������
void deleteSong( char* pliName, char* fileName) //���ڷ� ���� pliName�� ".txt"�� �������� ���� �����̴�.
{
	while (1)
	{
		char playlistName[FILE_NAME] = { 0, };
		strcpy(playlistName, pliName);
		char* noNumName = playlistName + 3;
		
		FILE* fp = fopen(fileName, "r");

		string getMenu;

		printf("\n\n%s\n\n", noNumName);

		char buffer[MAX] = { 0, };

		fread(buffer, 1, MAX, fp);


		printf("\n%s\n", buffer);

		printf("\n���� \"0\"�� �Է½� ���� �������� �̵��մϴ�.\n");
		printf("�÷��̸���Ʈ���� ������ �뷡�� �ش��ϴ� ��ȣ�� �Է����ּ��� : ");

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
	//���� ����
	while (*start != '\0') {
		if ((*start == ' ') || (*start == '\t'))
			start++;
		else
			break;
	}
	//���� ����
	while (1) {
		if ((*finish == ' ') || (*finish == '\t'))
			finish--;
		else {
			*(finish + 1) = '\0';
			break;
		}
	}

	return start;
}