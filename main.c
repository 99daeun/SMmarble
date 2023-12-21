//
//  main.c
//  SMMarble
//
//  Created by Juyeop Kim on 2023/11/05.
//

#include <time.h>
#include <string.h>
#include <stdlib.h>
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

typedef struct player_con {
		int position;
		int experiment;
		int acc_credit;
		int now_energy;
	} player_con ;//struct for player condition
	

//function prototypes
int isGraduated(void); //check if any player is graduated

void generatePlayers(int n, int initEnergy); //generate a new player

void printGrades(int player); //print grade history of the player

void goForward(int player, int step); //make player go "step" steps on the board (check if player is graduated)

void printPlayerStatus(void); //print all player status at the beginning of each turn

float calcAverageGrade(int player); //calculate average grade of the player

void* findGrade(int player, char *lectureName); //find the grade from the player's grade history

int rolldie()
{
    char c;
    printf(" Press any key to roll a die ");
    _getch(); // 키 입력 대기
    printf("%d칸이동\n", rand()%6 + 1 );
    return (rand()%6 + 1);
}

void printGrades(int player)
{
	//print grade history of the player
	//print all the grade history of the player
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
    int i,j,r,k;//use for tempoaray value
    char line[100];//array for each line
	int score[9]; //a+, a0, a-, b+, b0, b-, c+, c0, c- 
    int lec_check[50][50] = {0}; //0 means havenot take lecture, 1 means taken lecture
    int success = 0;
    board_nr = 0;
    food_nr = 0;
    festival_nr = 0;
    int player_nr = 0; //when game starts, it have a value.
    player_con player_con[50];
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
	printf("How Many Player? : "); //input player number to player_nr
    scanf("%d",&player_nr); // when a turn begins, code have to repeat according this number
    char playerName[50][50]; //max num of name character and players is each 50 .
	for(i=0;i<player_nr;i++)
	{
    	printf("What's Your Name? : ");
		scanf("%s", &playerName[i]); //input one's name
	}
	for(i=0;i<player_nr;i++)
	{
		player_con[i].acc_credit = 0;
		player_con[i].experiment = 0;	//if 1, on-experiment
		player_con[i].now_energy = board_[0].Energy; 	// first line of marbleBoardConfig.txt file is always home. and all the players starts home energy.
		player_con[i].position = 0; //start from the origin  
	}
	
    //3. SM Marble game starts ---------------------------------------------------------------------------------
    for(i=0;;i++)// A-turn
	{
		j = i % player_nr; // repeat-continued j'th player.
		//실험실 !
		if (player_con[j].experiment == 1)
		{
			player_con[j].position == 2;
			printf("실험실에 왔습니다!");
			if (rolldie() >= success ) player_con[j].experiment = 0; 
			else player_con[j].now_energy -= 3;// consumption energy
		} 
		r = rolldie();
		player_con[j].position += r; //position check
		if(player_con[j].position > board_nr) player_con[j].position -= board_nr; //board_nr is max of the position num
		r = player_con[j].position; // board node should be saved
		
		//take lecture.
		if (r == 0)
		{
			if (lec_check[j][r] == 0 && player_con[j].now_energy > board_[r].Energy)
			{
				char c;
    			printf(" press y to take a lecture");
    			c = getchar();
    			if (c == 'y')
    			{
    				player_con[j].now_energy -= board_[r].Energy;			
					lec_check[j][r] = 1;
					player_con[j].acc_credit += board_[r].Credit;
				}
				else
				{
					printf("you do not take a lecture.");
				}	
			}
			else
			{
			printf("you cannot take a lecture.");	
			}
		}
		
		//Eat !
		if (r == 1){
			player_con[j].now_energy += board_[r].Energy;
		}
		
		//실험!
		if (r == 4){
			player_con[j].experiment = 1;
			success = rand()%6 + 1;
			printf("실험실에 갑니다! 성공 주사위는 %d 입니다", &success); 
		} 
		
		//집 !
		if (r == 0)
		{
			player_con[j].now_energy += board_[0].Energy;
		} 
		//보충 찬스 
		if (r == 5)
		{
			k = rand()%food_nr;
			player_con[j].now_energy += food_[k].foodenergy;
			printf("%d th player! supplement the energy with %s\n",j+1,food_[k].foodName);
			k = 0; 
		} 
		//축제!
		if (r == 6)
		{
			k = rand()%festival_nr;
			printf("%d th player! execute the mission, %s\n",j+1,festival_[k].data);
			k = 0;
		}
		
		
		if (player_con[j].acc_credit >= GRADUATE_CREDIT) break;
	}	
	
	//game-end 
	j = i % player_nr;
	printf("%d th 플레이어 우승! 누적 학점 : %d 최종 에너지 : %d\n",j+1, player_con[j].acc_credit, player_con[i].now_energy) ;
    
    return 0;
}
