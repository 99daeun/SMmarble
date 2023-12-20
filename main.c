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
	char BoardName[50];
	int Nodetype;
	int Credit;
	int Energy;
} board ; //struct for Board

typedef struct Food {
	char foodName[50];
	int foodenergy;
} food;//struct for Food

typedef struct festival {
    char data[100]; // data of node
} festival;//struct for Festival


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
    int initEnergy;
    int i;//use for tempoaray value
    char line[100];//array for each line
    
    board_nr = 0;
    food_nr = 0;
    festival_nr = 0;
    int player_nr = 0; //when game starts, it have a value.
    
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
    board *board_ = (board*)malloc(sizeof(board) * 50); //dynamically allocated array ... and '50' means MAX_line_nr 
    if (board_ == NULL) {//if dynamically allocated array is empty, file-close and return 1 for ERROR message
        fprintf(stderr, "Unable to allocate memory.\n");
        fclose(fp);
        return 1;
    }
    while (fgets(line, sizeof(line), fp) != NULL)//read a node parameter set
    {
        int smmdb_addTail(line);//store the parameter set 
        sscanf(line, "%s %d %d %d", board_[board_nr].BoardName, &board_[board_nr].Nodetype, &board_[board_nr].Credit, &board_[board_nr].Energy); // each data store at each variable in the struct
        board_nr++; //indicator for board number 
    }
    fclose(fp);
    printf("Total number of board nodes : %i\n", board_nr);
    
    //2. food card config 
    if ((fp = fopen(FOODFILEPATH,"r")) == NULL)
    {
        printf("[ERROR] failed to open %s. This file should be in the same directory of SMMarble.exe.\n", FOODFILEPATH);
        return -1;
    }
    printf("\nReading food card component......\n");
    food *food_ = (food*)malloc(sizeof(food) * 50); //dynamically allocated array ... and '50' means MAX_line_nr 
    if (food_ == NULL) {//if dynamically allocated array is empty, file-close and return 1 for ERROR message
        fprintf(stderr, "Unable to allocate memory.\n");
        fclose(fp);
        return 1;
    }
	while (fgets(line, sizeof(line), fp) != NULL) //read a food parameter set
    {
        int smmdb_addTail(line);     //store the parameter set
        sscanf(line, "%s %d", food_[food_nr].foodName, &food_[food_nr].foodenergy);// each data store at each variable in the struct
        food_nr++;//indicator for food number 
    }
    fclose(fp);
    printf("Total number of food cards : %i\n", food_nr);
	
    //3. festival card config 
    if ((fp = fopen(FESTFILEPATH,"r")) == NULL)
    {
        printf("[ERROR] failed to open %s. This file should be in the same directory of SMMarble.exe.\n", FESTFILEPATH);
        return -1;
    }
    printf("\nReading festival card component......\n");
    festival *festival_ = (festival*)malloc(sizeof(festival) * 50); //dynamically allocated array ... and '50' means MAX_line_nr 
    if (festival_ == NULL) {//if dynamically allocated array is empty, file-close and return 1 for ERROR message
        fprintf(stderr, "Unable to allocate memory.\n");
        fclose(fp);
        return 1;
    }
	while (fgets(line, sizeof(line), fp) != NULL) //read a festival card string
    {
    	int smmdb_addTail(line);
    	sscanf(line, "%s", festival_[festival_nr].data);// each data store at each variable in the struct
        festival_nr++;//indicator for festival number 
    }
    fclose(fp);
    printf("Total number of festival cards : %i\n", festival_nr); 
    
    //2. Player configuration ---------------------------------------------------------------------------------
    for(i=0;i<board_nr;i++){
    	if(board_[i].Nodetype == 3) initEnergy = board_[i].Energy; //Home Energy become initial Engergy
	}
	printf("How Many Player? : "); //input player number to player_nr
    scanf("%d",&player_nr); // when a turn begins, code have to repeat according this number
    char playerName[50][50]; //max num of name character and players is each 50 .
	for(i=0;i<player_nr;i++){
    	printf("What's Your Name? : ");
		scanf("%s", &playerName[i]); //input one's name
	}
	
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
