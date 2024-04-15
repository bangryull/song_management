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

void song_list_menu() //�뷡 ����Ʈ �� �޴�
{
	int mode, err = 0;
	while (1)
	{
		if (err == 0) //�Է� ���ǿ� �¾��� ��
		{
			printf("\n���ϴ� �޴��� �����ϼ���.\n\n");
		}
		else //�Է� ���ǿ� ���� �ʾ��� ��
		{
			printf("\n�ش� �޴��� �������� �ʽ��ϴ�.\n");
			printf("���� �޴� �� �����ϼ���(����:1)\n\n");
			err = 0;
		}
		printf("1. �뷡 ����Ʈ ���\n");
		printf("2. �뷡 �߰�\n");
		printf("3. �뷡 ����\n");
		printf("0. �ڷ� ����\n");
		printf("\n�޴� ���� : ");
		scanf("%d", &mode);

		while (getchar() != '\n'); //�Է� ���� ����

		switch (mode) {
		case 1: //�뷡 ����Ʈ ���
			song_list_menu();
			break;

		case 2: //�뷡 �߰�
			add_song();
			song_list_menu();
			break;

		case 3: //�뷡 ����

			break;

		case 0: //�ڷ� ����

			break;
		default: //error
			while (getchar() != '\n'); //�Է� ���� ����
			err = 1;
			break;
		}
	}
}

void add_song() {
	char title_buffer[STRING_SIZE] = "";	//����
	char singers_buffer[STRING_SIZE] = "";	//����
	char composers_buffer[STRING_SIZE] = "";	//�۰
	char lyricists_buffer[STRING_SIZE] = "";	//�ۻ簡
	char genre_buffer[STRING_SIZE] = "";    //�帣
	char playtime[STRING_SIZE]; //����ð�
	char album_buffer[STRING_SIZE];    //�ٹ���
	char release[STRING_SIZE];  //�ٹ���ó�¥
	FILE* fp = fopen("song_list.txt", "a");	//�߰����� ���� ����


	printf("������ �Է��ϼ���.\n");	//����
	while (1) {
		printf("\n");
		printf("���� :");
		gets(title_buffer);	//���� �Է¹ޱ�

		char* title = trim(title_buffer);	//�յ� ���� ����

		//printf("%s\n", title);			//����� �ԷµǾ����� Ȯ��(�˻�)
		if (strlen(title) == 0) {	//Ʋ�� �Է��� ���
			printf("���� �Է��� �߸��Ǿ����ϴ�.��Ȯ�� �Է����ּ���.(����:����)\n");
			continue;
		}
		else {		//�´� �Է��� ���
			fprintf(fp, "%s | ", title);
		}
		break;
	}	//���� ��
	
	printf("������ �Է��ϼ���.\n");	//����
	while (1) {
		printf("\n");
		printf("���� :");
		gets(singers_buffer);	//���� �Է¹ޱ�

		char* singers = trim(singers_buffer);	//�յ� ���� ����

		if (strlen(singers)==0) {	//Ʋ�� �Է��� ���
			printf("���� �Է��� �߸��Ǿ����ϴ�.��Ȯ�� �Է����ּ���.(����:������)\n");
			continue;
		}
		else {		//�´� �Է��� ���
			char* singer_buffer = strtok(singers, ",");	//","�� �������� �ڸ���
			char* singer = trim(singer_buffer);	//�յ� ���� ����
												//�ߺ� Ȯ��

			fprintf(fp, "%s ", singer);			//ù ���� ���Ͽ� ����
			singer = strtok(NULL, ",");

			while (singer != NULL) {				//������ �� ���� ��� ��� �߰� ����
				char* next_singer = trim(singer);	//�յ� ���� ����
													//�ߺ� Ȯ��
				fprintf(fp, ", %s ", next_singer);
				singer = strtok(NULL, ",");
			}
			fputs("| ", fp);
		}
		break;
	}		//���� ��


	printf("�۰�� �Է��ϼ���.\n");	//�۰
	while (1) {
		printf("\n");
		printf("�۰ :");
		gets(composers_buffer);	//�۰ �Է¹ޱ�

		char* composers = trim(composers_buffer);	//�յ� ���� ����

		if (strlen(composers)==0) {	//Ʋ�� �Է��� ���
			printf("�۰ �Է��� �߸��Ǿ����ϴ�.��Ȯ�� �Է����ּ���.(����:������)\n");
			continue;
		}
		else {		//�´� �Է��� ���
			char* composer_buffer = strtok(composers, ",");	//","�� �������� �ڸ���
			char* composer = trim(composer_buffer);	//�յ� ���� ����
												//�ߺ� Ȯ��

			fprintf(fp, "%s ", composer);			//ù �۰ ���Ͽ� ����
			composer = strtok(NULL, ",");

			while (composer != NULL) {				//�۰�� �� ���� ��� ��� �߰� ����
				char* next_composer = trim(composer);	//�յ� ���� ����
													//�ߺ� Ȯ��
				fprintf(fp, ", %s ", next_composer);
				composer = strtok(NULL, ",");
			}
			fputs("| ", fp);		
		}
		break;	//�۰ ��
	}

	printf("�ۻ簡�� �Է��ϼ���.\n");	//�ۻ簡
	while (1) {
		printf("\n");
		printf("�ۻ簡 :");
		gets(lyricists_buffer);	//�ۻ簡 �Է¹ޱ�

		char* lyricists = trim(lyricists_buffer);	//�յ� ���� ����

		if (strlen(lyricists) == 0) {	//Ʋ�� �Է��� ���
			printf("�ۻ簡 �Է��� �߸��Ǿ����ϴ�.��Ȯ�� �Է����ּ���.(����:������)\n");
			continue;
		}
		else {		//�´� �Է��� ���
			char* lyricist_buffer = strtok(lyricists, ",");	//","�� �������� �ڸ���
			char* lyricist = trim(lyricist_buffer);	//�յ� ���� ����
			//�ߺ� Ȯ��

			fprintf(fp, "%s ", lyricist);			//ù �ۻ簡 ���Ͽ� ����
			lyricist = strtok(NULL, ",");

			while (lyricist != NULL) {				//�ۻ簡�� �� ���� ��� ��� �߰� ����
				char* next_lyricist = trim(lyricist);	//�յ� ���� ����
				//�ߺ� Ȯ��
				fprintf(fp, ", %s ", next_lyricist);
				lyricist = strtok(NULL, ",");
			}
			fputs("| ", fp);		
		}
		break;	//�ۻ簡 ��
	}

	printf("�帣�� �Է��ϼ���.\n");	//�帣
	while (1) {
		printf("\n");
		printf("�帣 :");
		gets(genre_buffer);

		char* genre = trim(genre_buffer);	//�յ� ���� ����

		if (strcmp(genre, "Ŭ����") * strcmp(genre, "����") * strcmp(genre, "��") * strcmp(genre, "�߶��") * strcmp(genre, "����") * strcmp(genre, "Ʈ��Ʈ") * strcmp(genre, "����") * strcmp(genre, "��") == 0) {	//�´� �Է��� ���
			fprintf(fp, "%s | ", genre);
		}
		else {		//Ʋ�� �Է��� ���
			printf("�帣 �Է��� �߸��Ǿ����ϴ�.��Ȯ�� �Է����ּ���.(����:����)\n");
			continue;
		}
		break;
	}		//�帣 ��

	/*
	printf("�ð��� �Է��ϼ���.\n");	//�ð�
	while (1) {
		char minute_str[STRING_SIZE] = "";
		char second_str[STRING_SIZE] = "";
		int error = 0;
		printf("\n");
		printf("�ð� :");
		gets(playtime);

		char* playtime_ = trim(playtime);	//�յ� ���� ����

		if (strlen(playtime_) == 0) { error = 1; }	//Ʋ�� �Է��� ���	
		else if (strchr(playtime_, "��") == NULL && strchr(playtime_, "��") == NULL) { error = 1; }
		else if (strchr(playtime_, "��") == NULL && strchr(playtime_, "��") != NULL) {
			*second_str = strtok(playtime_, "��");
			if (strtok(NULL, "��") != NULL) { error = 1; }
		}
		else if (strchr(playtime_, "��") != NULL && strchr(playtime_, "��") == NULL) {
			*minute_str = strtok(playtime_, "��");
			if (strtok(NULL, "��") != NULL) { error = 1; }
		}
		else {
			*minute_str = strtok(playtime_, "��");
			*second_str = strtok(NULL, "��");
			if (strtok(NULL, "��") != NULL) { error = 1; }
		}
		printf("%s��%s��\n", second_str, minute_str);
		if (error == 1) {
			printf("�ð� �Է��� �߸��Ǿ����ϴ�.��Ȯ�� �Է����ּ���.(����:������)\n");
			continue;
		}
		break;
	}		//�ð� ��
	*/  //������

	printf("�ٹ����� �Է��ϼ���.\n");	//�ٹ���
	while (1) {
		printf("\n");
		printf("�ٹ��� :");
		gets(album_buffer);	//�ٹ��� �Է¹ޱ�

		char* album = trim(album_buffer);	//�յ� ���� ����

		if (0) {	//Ʋ�� �Է��� ���
			printf("�ٹ��� �Է��� �߸��Ǿ����ϴ�.��Ȯ�� �Է����ּ���.(����:��簻)\n");
			continue;
		}
		else {		//�´� �Է��� ���
			fprintf(fp, "%s | ", album);
		}
		break;
	}	//�ٹ��� ��



	fclose(fp);
}