#include <stdio.h>
#include <time.h>
#include <stdlib.h>

#define SIZE_OF_BOARD 16

/* Global variables */
int total_ects=0,step_counter=0;
int student_x=SIZE_OF_BOARD/2,student_y=SIZE_OF_BOARD/2; /* Student's coordinates */
int first_year_x[4],first_year_y[4];/* For the coordinates of the course in the first grade. */
int second_year_x[24],second_year_y[24]; /* For the coordinates of the course in the second grade. */
int number_second_course; /* Number of courses in second grade */
int number_first_course=4; /* Number of courses in first grade */
int first_wall_x[16],first_wall_y[16]; /* Variables that hold the coordinates of the inner wall */
int second_wall_x[32],second_wall_y[32]; /* Variables that hold the coordinates of the outer wall */

/* Checks whether the entered point is an element of the array in the received parameter. */
int is_in_array(int point_x, int point_y, int size,int x[],int y[]){
    int i;
    for(i=0;i<size;i++){
        if(x[i]==point_x && y[i]==point_y){
            return 1;
        }
    }
    return 0;
}
/* If the entered point belongs to the array entered in the parameter, it throws the coordinates of that point out of the game board, that is, that point disappears from the game and that point turns into a '.' character. */
int make_point (int a, int b, int size,int x[],int y[]){
    int i;
    for(i=0;i<size;i++){
        if(x[i]==a && y[i]==b){
            x[i]=SIZE_OF_BOARD+1;
            y[i]=SIZE_OF_BOARD+1;
            return 1;
        }
    }
    return 0;
}

/* Return the student to the previous position */
void previous_location(char direction){
    
    switch(direction){
        case 'a':
            student_x+=1;
            break;
        case 'd':
            student_x-=1;
            break;
        case 'w':
            student_y+=1;
            break;
        case 's':
            student_y-=1;
            break;
    }
}
 /* Randomly distributes course to specific coordinates on the game board */
void random_location_course(int start,int end,int size,int y[size], int x[size]){
    srand(time(0));
    int i,temp;
    for(i=0;i<size;i++){
        y[i]=rand()%(end-start+1)+start;
    }
    for(i=0;i<size;i++){
        if(y[i]!=start && y[i]!=end){
            temp=rand()%2;
            if(temp==1){
                x[i]=start;
            }
            else {
                x[i]=end;
            }
        }
        else{
            x[i]=rand()%(end-start+1)+start;;
        }
        if(is_in_array(x[i],y[i],i,x,y)){
            y[i]=rand()%(end-start+1)+start;
            i--;
            
        }
    }
}
/* determines the coordinates of the walls */
void wall_location(int start, int end, int length, int wall_x[length] , int wall_y[length]){
    int j=0,i;
    
    for(i=0;i<length;i++){
        wall_x[j]=start;
        wall_y[j]=i+start;
        j++;
    }
    for(i=0;i<length;i++){
        wall_x[j]=end;
        wall_y[j]=i+start;
        j++;
    }
    for(i=1;i<length-1;i++){
        wall_x[j]=i+start;
        wall_y[j]=start;
        j++;
    }
    for(i=1;i<length-1;i++){
        wall_x[j]=i+start;
        wall_y[j]=end;
        j++;
    }
}

/* Starts the game using functions that determine the coordinates of the courses and walls */
void initialize_game(){
    
    srand(time(0));
    int start_first_wall=6,end_first_wall=10,length_first=5;
    int start_second_wall=4,end_second_wall=12,length_second=9;;
    int start_first_course=7,end_first_course=9;
    int start_second_course=5,end_second_course=11;
    number_second_course=rand()%22+3;
    
    random_location_course(start_second_course,end_second_course,number_second_course,second_year_y,second_year_x);
    random_location_course(start_first_course,end_first_course,number_first_course,first_year_y,first_year_x);
    wall_location(start_first_wall, end_first_wall, length_first,first_wall_x,first_wall_y);
    wall_location(start_second_wall, end_second_wall, length_second,second_wall_x,second_wall_y);

}
/* It checks the necessary actions by updating the player's movements according to the input entered. */
void move_player(char direction){
    
    /* capitalization check */
    if(direction>='A'&& direction<='Z'){
        direction+=32;
    }
    /* Coordinate update according to input */
    switch(direction){
        case 'a':
            student_x--;
            break;
        case 'd':
            student_x++;
            break;
        case 'w':
            student_y--;
            break;
        case 's':
            student_y++;
            break;
        default:
            printf("invalid direciton try again. \n");
    }
    /* Checking if you are within the game board limits */
    if(student_x>=SIZE_OF_BOARD || student_y >= SIZE_OF_BOARD || student_y<0 || student_x<0){
        printf("You can't leave the game board. Try again. \n");
        previous_location(direction);

    }
    /* f the student's position and the course position are equal, increase ects by 8 */
    else if(make_point(student_x,student_y,number_first_course,first_year_x,first_year_y)){
        total_ects+=8;

    }
   
    else if(make_point(student_x,student_y,number_second_course,second_year_x,second_year_y)){
        total_ects+=8;
    }
    /* If it tries to pass through the wall without sufficient ects, it gives a warning message */
    if(total_ects<32 && is_in_array(student_x,student_y,16,first_wall_x,first_wall_y) ){
        printf("Your ects are not enough to pass the class.\n");
        previous_location(direction);
    
    }
    else if(total_ects<56 && is_in_array(student_x,student_y,32,second_wall_x,second_wall_y) ){
        printf("Your ects are not enough to pass the class.\n");
        previous_location(direction);
    }
}

/* prints the game board according to the specified coordinates */
void print_board(){
    int i,j;
    
    for(i=0;i<SIZE_OF_BOARD;i++){
        for(j=0;j<SIZE_OF_BOARD;j++){
        /* If the position belongs to any symbol, print that symbol, it does not belong, print a dot */
            if(j==student_x && i == student_y){
                printf("P ");
            }
            else if(is_in_array(j,i,16,first_wall_x,first_wall_y)){
                printf("# ");
            }
            else if(is_in_array(j,i,32,second_wall_x,second_wall_y)){
                printf("# ");
            }
            else if(is_in_array(j,i,number_second_course,second_year_x,second_year_y)){
                printf("2 ");
            }
            else if(is_in_array(j,i,4,first_year_x,first_year_y)){
                printf("1 ");
            }
            else if(j==SIZE_OF_BOARD-1 && i==SIZE_OF_BOARD-1){
                printf("X");
            }
           else
            printf(". ");
        }
        printf("\n");
    }
}

int main() {
    
    char direction;

    initialize_game();
    while (!(student_x == SIZE_OF_BOARD - 1 && student_y == SIZE_OF_BOARD - 1)) {
        printf("\nUse W (up), A (Left), S (Down), D (Right) to move\n");
        print_board();
        printf("\nTotal ECTS: %d\n", total_ects);
        printf("Enter your move: ");
        scanf(" %c", &direction);
        step_counter++;
        move_player(direction);
    }
    print_board();
    printf("\nTotal ECTS: %d\n", total_ects);
    printf("Total number of movements: %d\n",step_counter);
    printf("Game over!!\n");
    return 0;
}
