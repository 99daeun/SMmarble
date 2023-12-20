//
//  main.c
//  SMMarble
//
//  Created by Juyeop Kim on 2023/11/05.
//

#include <time.h>
#include <string.h>
#include "smm_object.h"
#include "smm_database.h"
#include "smm_common.h"

#define BOARDFILEPATH "marbleBoardConfig.txt"
#define FOODFILEPATH "marbleFoodConfig.txt"
#define FESTFILEPATH "marbleFestivalConfig.txt"


//board configuration parameters
static int board_nr;
static int food_nr;
static int festival_nr;

typedef struct Board {
	char boardName[50];
	int Nodetype;
	int Credit;
	int Energy;
} board ;

typedef struct Food {
	char foodName[50];
	int foodenergy;
} food;

typedef struct festival {
    char data[100]; // 노드의 데이터
    struct Node* next; // 다음 노드를 가리키는 포인터
} festival;

// 전역 변수로 리스트의 헤드 포인터를 선언
festival* list_database = NULL;

//function prototypes
int isGraduated(void); //check if any player is graduated

void generatePlayers(int n, int initEnergy); //generate a new player

void printGrades(int player); //print grade history of the player

void goForward(int player, int step); //make player go "step" steps on the board (check if player is graduated)

void printPlayerStatus(void); //print all player status at the beginning of each turn

float calcAverageGrade(int player); //calculate average grade of the player

void takeLecture(int player, char *lectureName, int credit); //take the lecture (insert a grade of the player)

void* findGrade(int player, char *lectureName); //find the grade from the player's grade history

void printGrades(int player); //print all the grade history of the player




int rolldie(int player)
{
    char c;
    printf(" Press any key to roll a die (press g to see grade): ");
    c = getchar();
    fflush(stdin);
    
    if (c == 'g')
        printGrades(player);
    
    return (rand()%MAX_DIE + 1);
}

void printGrades(int player)
{
	//print grade history of the player
}

//action code when a player stays at a node
void actionNode(int player)
{
/*  switch(type)
    {
        //case lecture:
        default:
            break;
    }*/
}



int main(int argc, const char * argv[]) {
    
    FILE* fp;
    char name[MAX_CHARNAME];
    int type;
    int credit;
    int energy;
    int i;
    char line[100];
    
    board_nr = 0;
    food_nr = 0;
    festival_nr = 0;
    int player_nr = 0;
    
    festival *festival1 ;
    board *board1;
    
    board *borad1 = (board*)malloc(sizeof(board) * 16);  // 예제 데이터가 16개이므로 크기를 조절
    
    srand(time(NULL));
    
    //1. import parameters ---------------------------------------------------------------------------------
    //1-1. boardConfig 
    if ((fp = fopen(BOARDFILEPATH,"r")) == NULL)
    {
        printf("[ERROR] failed to open %s. This file should be in the same directory of SMMarble.exe.\n", BOARDFILEPATH);
        getchar();
        return -1;
    }
    
    printf("Reading board component......\n");
    while (fgets(line, sizeof(line), fp) != NULL)//read a node parameter set
    {
        int smmdb_addTail(line);//store the parameter set
        board_nr++;
    }
    fclose(fp);
    printf("Total number of board nodes : %i\n", board_nr);
    
    //2. food card config 
    if ((fp = fopen(FOODFILEPATH,"r")) == NULL)
    {
        printf("[ERROR] failed to open %s. This file should be in the same directory of SMMarble.exe.\n", FOODFILEPATH);
        return -1;
    }
    
    printf("\n\nReading food card component......\n");
    while (fgets(line, sizeof(line), fp) != NULL) //read a food parameter set
    {
        int smmdb_addTail(line);     //store the parameter set
        food_nr++;
    }
    fclose(fp);
    printf("Total number of food cards : %i\n", food_nr);

    
    //3. festival card config 
    if ((fp = fopen(FESTFILEPATH,"r")) == NULL)
    {
        printf("[ERROR] failed to open %s. This file should be in the same directory of SMMarble.exe.\n", FESTFILEPATH);
        return -1;
    }
    
    printf("\n\nReading festival card component......\n");
    while (fgets(line, sizeof(line), fp) != NULL) //read a festival card string
    {
    	int smmdb_addTail(line);
    	//sscanf(line, "%s", festival1.data);
        festival_nr++;
    }
    fclose(fp);
    printf("Total number of festival cards : %i\n", festival_nr);
    

    
    
    //2. Player configuration ---------------------------------------------------------------------------------
    printf("How Many Player? : "); //input player number to player_nr
    scanf("%d",&player_nr); // when a turn begins, code have to repeat according this number
    char playerName[50][50]; //max num of name character and players is each 50 .
    for(i=0;i<player_nr;i++){
    	printf("What's Your Name? : ");
		scanf("%s", &playerName[i]); //input one's name
		//generatePlayers(i, initEnergy); //generate a new player
	}
	//MUST-DO ; initEnergy from "marbleBoardConfig.txt" (home energy)


    
    
    
    //3. SM Marble game starts ---------------------------------------------------------------------------------
    while (0) //is anybody graduated?
    {
        int die_result;
        
        //4-1. initial printing
        //printPlayerStatus();
        
        //4-2. die rolling (if not in experiment)
        
        
        //4-3. go forward
        //goForward();

		//4-4. take action at the destination node of the board
        //actionNode();
        
        //4-5. next turn
        
    }
    
    return 0;
}
