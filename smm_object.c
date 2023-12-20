//
//  smm_node.c
//  SMMarble
//
//  Created by Juyeop Kim on 2023/11/05.
//

#include "smm_common.h"
#include "smm_object.h"
#include <string.h>

#define MAX_NODETYPE    7
#define MAX_GRADE       9



//object generation
void smmObj_genNode(void)
{
    
}

typedef struct Board {
	char boardName[50];
	int Nodetype;
	int credit;
	int energy;
} board ;

typedef struct Food {
	char foodName[50];
	int foodenergy;
}food;

typedef struct festival {
    char data[100]; // 노드의 데이터
    struct Node* next; // 다음 노드를 가리키는 포인터
} festival;


//member retrieving



//element to string
char* smmObj_getNodeName(smmNode_e type)
{
    return smmNodeName[type];
}

char* smmObj_getGradeName(smmGrade_e grade)
{
    return smmGradeName[grade];
}

