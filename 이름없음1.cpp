#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define FESTFILEPATH "marbleFestivalConfig.txt" // 텍스트 파일의 경로와 이름을 정의

// 노드를 나타내는 구조체
typedef struct Node {
    char data[100]; // 노드의 데이터
    struct Node* next; // 다음 노드를 가리키는 포인터
} Node;

// 전역 변수로 리스트의 헤드 포인터를 선언
Node* list_database = NULL;

// 리스트에 노드를 추가하는 함수
int smmdb_addTail(char* obj) {
    Node* ndPtr;
    Node* newNdPtr;

    // parameter checking
    if (obj == NULL) {
        printf("[ERROR] smmdb_addTail() : Failed to do addTail : input object indicates NULL!\n");
        return -1;
    }

    // generate new node
    newNdPtr = (Node*)malloc(sizeof(Node)); // 노드 동적 할당
    if (newNdPtr == NULL) {
        printf("[ERROR] smmdb_addTail() : Failed to do addTail : Failed to create a node\n");
        return -1; // 노드 생성 실패 시 에러 반환
    }
    strcpy(newNdPtr->data, obj); // 새로운 노드에 데이터(obj) 저장

    // add node to the list tail
    if (list_database == NULL) {
        // 리스트가 비어있으면 새로운 노드를 리스트의 처음으로 지정
        list_database = newNdPtr;
        newNdPtr->next = NULL;
    } else {
        // 리스트의 끝에 새로운 노드 추가
        ndPtr = list_database;
        while (ndPtr->next != NULL) {
            ndPtr = ndPtr->next;
        }
        ndPtr->next = newNdPtr; // 마지막 노드의 다음을 새로운 노드로 지정
        newNdPtr->next = NULL;
    }

    return 0; // 함수 성공 시 0 반환
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
        // 노래 정보를 리스트에 추가
        smmdb_addTail(line);
    }

    fclose(fp);

    // 리스트의 내용 출력
    Node* current = list_database;
    while (current != NULL) {
        printf("%s", current->data);
        current = current->next;
    }

    // 리스트의 메모리 해제
    current = list_database;
    while (current != NULL) {
        Node* next = current->next;
        free(current);
        current = next;
    }

    return 0;
}

