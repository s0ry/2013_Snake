#include <stdio.h>
#include <stdlib.h>		//system
#include <windows.h>	//Sleep
#include <conio.h>		//_kbhit,_getch	
#include <time.h>	
//w(119),a(97),s(115),d(100),g(103)

char map[22][42];
char snake_retry;
int snake_location_row[300];
int snake_location_column[300];
int pre_row;
int pre_column;
int temp_row;
int temp_column;
char snake[300];
int snake_length = 2;
//[10][20] first position
int snake_direction = 2;	//	1-up, 2-right, 3-down, 4-left
int score_flag = 0;
int score_row = 0;
int score_column = 0;
int game_check = 1;			// Game over
int check_flag = 1;			

void map_setting();			// initiall map setting
void snake_setting();		// initiall snake setting
void snake_head_moving();	// snake head moving
void snake_moving(int i);	// except head moving
void gotoxy(int x, int y);	// curser moving
void gogo();				// moving process
void create_score();		// score random create
void check_eating();		// check eating score
void add_body();			// body grow
void check_crash();			// crash check
void setColor(unsigned short text, unsigned short back);

int main()
{
	snake_setting();
	map_setting();
	
	//printf("Press 'G key' \n");
	while(game_check > 0){
		gogo();
		check_crash();
		if (game_check == 2){
			check_flag = 1;
			score_flag = 0;
			snake_setting();
			map_setting();
			game_check = 1;
		}
		if(_kbhit()){
			char cChar = _getch();
			/*if(cChar == 103){
				map[10][19] = ' ';
			}*/
			if(cChar == 119 && snake_direction != 3)
				snake_direction = 1;
			else if(cChar == 100 && snake_direction != 4)
				snake_direction = 2;
			else if(cChar == 115 && snake_direction != 1)
				snake_direction = 3;
			else if(cChar == 97 && snake_direction != 2)
				snake_direction = 4;
		}
	}
	return 0;
}

void gogo(){
	gotoxy(0,0);
	Sleep(50);
	check_eating();
	create_score();
	snake_head_moving();
	for(int i=1;i<snake_length;i++){
		gotoxy(1,1);
		snake_moving(i);
	}
	for(int i=1;i<21;i++){
		for(int j=1;j<41;j++){
			if (map[i][j] == '*'){
				setColor(4,7);
				printf("%c", map[i][j]);
				setColor(7,0);
			}
			else if (map[i][j] == 'O'){
				setColor(1,7);
				printf("%c", map[i][j]);
				setColor(7,0);
			}
			else{
				setColor(7,7);
				printf("%c", map[i][j]);
				setColor(7,0);
			}
		}
		printf("\n");
		setColor(6,6);
		printf("O");
		setColor(7,0);
	}
	printf("\n");
	printf("Score : ");
	printf("%d", snake_length-2);
	return;
}

void map_setting(){
	system("mode con: cols=43 lines=24");	
	for (int i=0;i<22;i++){
		for (int j=0;j<42;j++){
			if (i == 0 || i == 21){
				map[i][j] = 'O';
			}
			else if (j == 0 || j == 41){
				map[i][j] = 'O';
			}
			else{
				map[i][j] = ' ';
			}
			
		}
	}

	map[snake_location_row[0]][snake_location_column[0]] = snake[0];
	map[snake_location_row[1]][snake_location_column[1]] = snake[1];

	create_score();

	for (int i=0;i<22;i++){
		for (int j=0;j<42;j++){
			if (map[i][j] == 'O'){
				setColor(6,6);
				printf("%c", map[i][j]);
				setColor(7,0);
			}
			else if (map[i][j] == '*'){
				setColor(4,7);
				printf("%c", map[i][j]);
				setColor(7,0);
			}
			else{
				setColor(7,7);
				printf("%c", map[i][j]);
				setColor(7,0);
			}
		}
		printf("\n");
	}
	
	return;
}

void snake_setting(){
	for (int i=0;i<300;i++){
		snake[i] = ' ';
		snake_location_row[i] = 0;
		snake_location_column[i] = 0;
	}
	temp_row = 0;
	temp_column = 0;
	pre_row = 0;
	pre_column = 0;
	snake[0] = 'O';
	snake[1] = 'O';
	snake_location_row[0] = 10;
	snake_location_column[0] = 20;
	snake_location_row[1] = 10;
	snake_location_column[1] = 19;
	return;
}

void snake_moving(int i){
	if (snake_length == (i+1)){
		map[snake_location_row[i]][snake_location_column[i]] = ' ';
	}
	temp_row = snake_location_row[i];
	temp_column = snake_location_column[i];
	snake_location_row[i] = pre_row;
	snake_location_column[i] = pre_column;
	pre_row = temp_row;
	pre_column = temp_column;
	map[snake_location_row[i]][snake_location_column[i]] = 'O';
	return;
}

void snake_head_moving(){
	map[snake_location_row[0]][snake_location_column[0]] = ' ';
	pre_row = snake_location_row[0];
	pre_column = snake_location_column[0];
	switch(snake_direction){
		case 1:	//up
			snake_location_row[0]--;
		break;
		case 2:	//right
			snake_location_column[0]++;
		break;
		case 3:	//down
			snake_location_row[0]++;
		break;
		case 4:	//left
			snake_location_column[0]--;
		break;
	}
	map[snake_location_row[0]][snake_location_column[0]] = 'O';
	return;
}

void gotoxy(int x, int y){
	COORD coord = { 0,0 };
	coord.X = x; coord.Y = y;
	SetConsoleCursorPosition(GetStdHandle(STD_OUTPUT_HANDLE), coord);
	return;	//curser
}

void create_score(){
	while (check_flag){
		if (score_flag == 0){
		srand((unsigned)time(NULL));
		score_row = rand()%19+1;
		score_column = rand()%39+1;
			if (map[score_row][score_column] != 'O'){
				map[score_row][score_column] = '*';
				score_flag = 1;
				check_flag = 0;
			}
		}	
	}
	return;
}

void check_eating(){
	if (score_flag == 1 && snake_location_row[0] == score_row && snake_location_column[0] == score_column){
		score_flag = 0;
		check_flag = 1;
		add_body();
	}
	return;
}

void add_body(){
	snake_length++;
	snake[snake_length-1] = 'O';
	snake_location_row[snake_length-1] = pre_row;
	snake_location_column[snake_length-1] = pre_column;
	return;
}

void check_crash(){
	for (int i=1;i<snake_length;i++){
		if (snake_location_row[0] == snake_location_row[i] && snake_location_column[0] == snake_location_column[i]){
			gotoxy(13,10);
			printf("YOU DEAD.. ");
			printf("Retry?? (Y)");
			scanf(" %c", &snake_retry);
			if (snake_retry == 'Y'){
				game_check = 2;
			}
			else
				game_check = 0;
				game_check = 0;
			system("pause>null");
			//Sleep(100);
			game_check = 2;
		}
	}
	if (snake_location_row[0] == 0 || snake_location_row[0] == 21){
		gotoxy(13,10);
		printf("YOU DEAD.. ");
		printf("Retry?? (Y)");
		scanf(" %c", &snake_retry);
		if (snake_retry == 'Y'){
			game_check = 2;
		}
		else
			game_check = 0;
		system("pause>null");
		//Sleep(100);
	}
	if (snake_location_column[0] == 0 || snake_location_column[0] == 41){
		gotoxy(13,10);
		printf("YOU DEAD.. ");
		printf("Retry?? (Y)");
		scanf(" %c", &snake_retry);
		if (snake_retry == 'Y'){
			game_check = 2;
		}
		else
			game_check = 0;
		//game_check = 0;
		system("pause>null");
		Sleep(100);
		game_check = 2;
	}
	return;
}

void setColor(unsigned short text, unsigned short back){
	SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), text|(back <<4));
}
