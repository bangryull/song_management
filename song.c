#include <stdio.h>
#include <time.h>

#define STRING_SIZE 256

struct Artist { //����, �۰, �ۻ簡 -> ��Ƽ��Ʈ�� ����
    char name[STRING_SIZE];     //��Ƽ��Ʈ �̸�
    clock_t Key;                //Key��(�ð�)
};

struct Song { //����ü
    char title[STRING_SIZE];    //����
    struct Artist singer;       //����
    struct Artist composer;     //�۰
    struct Artist lyricist;     //�ۻ簡
    char genre[STRING_SIZE];    //�帣
    char playtime[STRING_SIZE]; //����ð�
    char album[STRING_SIZE];    //�ٹ���
    char release[STRING_SIZE];  //�ٹ���ó�¥
};

int main() {
    int mode;
    printf("menu\n");
    printf("1. �뷡 ����Ʈ ����\n");
    printf("2. �˻� ���\n");
    printf("3. �÷��̸���Ʈ\n");
    printf("4. ����\n");
    printf("�޴� ���� : ");
    scanf_s("%d", &mode);

    switch (mode) {
    case 1: //�뷡 ����Ʈ ����
        song_list_menu();
        break;

    case 2: //�˻� ���

        break;

    case 3: //�÷��̸���Ʈ

        break;

    case 4: //����

        break;

    default: //error
        break;
    }
    return 0;
}