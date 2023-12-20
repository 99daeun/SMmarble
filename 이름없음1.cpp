#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define FESTFILEPATH "marbleFestivalConfig.txt" // �ؽ�Ʈ ������ ��ο� �̸��� ����

// ��带 ��Ÿ���� ����ü
typedef struct Node {
    char data[100]; // ����� ������
    struct Node* next; // ���� ��带 ����Ű�� ������
} Node;

// ���� ������ ����Ʈ�� ��� �����͸� ����
Node* list_database = NULL;

// ����Ʈ�� ��带 �߰��ϴ� �Լ�
int smmdb_addTail(char* obj) {
    Node* ndPtr;
    Node* newNdPtr;

    // parameter checking
    if (obj == NULL) {
        printf("[ERROR] smmdb_addTail() : Failed to do addTail : input object indicates NULL!\n");
        return -1;
    }

    // generate new node
    newNdPtr = (Node*)malloc(sizeof(Node)); // ��� ���� �Ҵ�
    if (newNdPtr == NULL) {
        printf("[ERROR] smmdb_addTail() : Failed to do addTail : Failed to create a node\n");
        return -1; // ��� ���� ���� �� ���� ��ȯ
    }
    strcpy(newNdPtr->data, obj); // ���ο� ��忡 ������(obj) ����

    // add node to the list tail
    if (list_database == NULL) {
        // ����Ʈ�� ��������� ���ο� ��带 ����Ʈ�� ó������ ����
        list_database = newNdPtr;
        newNdPtr->next = NULL;
    } else {
        // ����Ʈ�� ���� ���ο� ��� �߰�
        ndPtr = list_database;
        while (ndPtr->next != NULL) {
            ndPtr = ndPtr->next;
        }
        ndPtr->next = newNdPtr; // ������ ����� ������ ���ο� ���� ����
        newNdPtr->next = NULL;
    }

    return 0; // �Լ� ���� �� 0 ��ȯ
}

int main() {
    FILE* fp;
    char line[100];

    // 3. festival card config
    if ((fp = fopen(FESTFILEPATH, "r")) == NULL) {
        printf("[ERROR] failed to open %s. This file should be in the same directory of SMMarble.exe.\n", FESTFILEPATH);
        return -1;
    }

    printf("\n\nReading festival card component......\n");
    
    while (fgets(line, sizeof(line), fp) != NULL) {
        // �뷡 ������ ����Ʈ�� �߰�
        smmdb_addTail(line);
    }

    fclose(fp);

    // ����Ʈ�� ���� ���
    Node* current = list_database;
    while (current != NULL) {
        printf("%s", current->data);
        current = current->next;
    }

    // ����Ʈ�� �޸� ����
    current = list_database;
    while (current != NULL) {
        Node* next = current->next;
        free(current);
        current = next;
    }

    return 0;
}

