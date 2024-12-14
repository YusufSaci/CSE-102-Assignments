
#include <stdio.h>
#define NUM_OF_CUPS 7
#define NUM_OF_PLAYERS 2
#define PLAYER 1
#define COMPUTER 0
#define NUM_OF_STONES 2


/* Fills each small cup in the game with an equal number of stones. */
void initialize_game(int num_stones[][NUM_OF_CUPS],int num_of_stone){
    
    int i,j;
    
    /* Initializes large cup with 0 */
    num_stones[COMPUTER][NUM_OF_CUPS-1]=0;
    num_stones[PLAYER][NUM_OF_CUPS-1]=0;
    
    for(i=0;i<NUM_OF_PLAYERS;i++){

        for(j=0;j<NUM_OF_CUPS-1;j++){
            num_stones[i][j]=num_of_stone;
        }
    }
    
}

/*Prints the game board with the stones in the cups. */
void print_board(int num_stones[][NUM_OF_CUPS]){
    
    int i;
    
    printf("+----+---+---+---+---+---+---+----+\n");
    printf("|    ");
    
    /* Prints the stones in the cup of the computer. */
    for(i=NUM_OF_CUPS-2;i>=0;i--){
        printf("| %-2d",num_stones[COMPUTER][i]);
    }
    
    printf("|    |\n");
    printf("| %2d |---+---+---+---+---+---| %2d |\n",num_stones[COMPUTER][6],num_stones[PLAYER][6]);
    printf("|    ");
    
     /* Prints the stones in the cup of the player. */
    for(i=0;i<NUM_OF_CUPS-1;i++){
        printf("| %-2d",num_stones[PLAYER][i]);
    }
    
    printf("|    |\n");
    printf("+----+---+---+---+---+---+---+----+\n");
    
}

/* Checks whether the game is over or not.*/
int end_condition(int num_stones[][NUM_OF_CUPS]){
    
    int i,j,flag;
    
    for(i=0;i<NUM_OF_PLAYERS;i++){
        
        flag=1;
        /* Checks whether all the stones in one side's cup are 0 or not.*/
        for(j=0;j<NUM_OF_CUPS-1;j++){
            if(num_stones[i][j]!=0){
                flag=0;
            }
        }
        if(flag)
            return 0;/* Game over.*/
    }
    return 1;
}

/* Distributes the stones in the selected cup according to a certain rule*/
int movement(int num_stones[][NUM_OF_CUPS],int selected_cup,int who, int mode){
    
    int side_flag=-1,i,k,stone_num,record_who,turn;
    
    record_who=who;
    
    do{
        
        stone_num=num_stones[who][selected_cup];/* number of stones in the selected cup.*/
        num_stones[who][selected_cup]=0;
        k=selected_cup+1;
    
        /* Continue until the stones in the selected cup are finished.*/
            for(i=0;i<stone_num;i++){
              
              
                if(k==NUM_OF_CUPS-1 && record_who==who){
                    num_stones[who][k]++;
                    who=!who;
                    k=-1;
                }
                
                /* if turn comes to opponent's large cup, skip it.*/
                else if (k==NUM_OF_CUPS-1 && record_who!=who){
                    k=-1;
                    who=!who;
                    i--;
                }
                
                else
                    num_stones[who][k]++;
                
                k++;
            }
            
            k--;
            
            selected_cup=k;
            
            /* If the last stone lands on an empty cup, set the flag to 0.*/
            if(k!=-1 && num_stones[who][k]==1){
                side_flag=0;
            }
            
            /* If the last stone lands in the playing side's large cup,make the flag one.*/
            else if(k==-1){
                side_flag=1;
            }
        
        /*not test mode. */
        if(mode==1){
            print_board(num_stones);
        }
        
        
    }while(side_flag==-1);
    
    
    if(side_flag==1)
        turn=record_who;
       
    else
        turn=!record_who;
    

    return turn;
 
    
}


/* Controls the flow of the game.*/
int game_play(int num_stones[][NUM_OF_CUPS],int who){
    
    int cup,winner,idx;
    int best_step=0,i,j,new=0,a;
    int test[NUM_OF_PLAYERS][NUM_OF_CUPS];
    
  
    /* Continues as long as the termination condition is not met.*/
    while(end_condition(num_stones)){
        idx=-1;

        if(who==PLAYER){
            printf("(player) Pls select a cup: ");
            scanf("%d",&cup);
            
            if(!(cup>=0 && cup<=5)){
                printf("invalid input. Select another cup.\n");
            }

            else if(num_stones[PLAYER][cup]==0){
                printf("This cup is empty select another.\n");
            }
            
            else
            who=movement(num_stones,cup,who,1);
        }
        
        else{
            printf("computer is playing.");

            /* Play the situation where the last stone lands the large cup*/
            for(i=0;i<NUM_OF_CUPS-1;i++){
                if(num_stones[COMPUTER][i]+i==6){
                    idx=i;
                }
            }

            if(idx==-1){

                /* Algorithm that selects the cup with the most points */
                for(i=0;i<NUM_OF_CUPS-1;i++){
                
                
                    /* Assigns the stones on the game board to the test array */
                    for(a=0;a<NUM_OF_PLAYERS;a++){

                        for(j=0;j<NUM_OF_CUPS;j++){
                        
                         test[a][j]=num_stones[a][j];
                        }
                    }

                 if(test[COMPUTER][i]!=0){
                    
                     movement(test,i,who,0);
                     new=test[COMPUTER][NUM_OF_CUPS-1];
                    
                        /* Saves the number of the best situation.*/
                     if(new>=best_step){
                            best_step=new;
                            idx=i;
                     }
                 }
               
                }
            }
            printf("(%d) \n",idx);
            who=movement(num_stones,idx,who,1);
        }
        
      printf("\n\n");
    }
    
    /* After all the stones in the small cups become 0, the one with the most stones in the large cup wins. */
    if(num_stones[COMPUTER][NUM_OF_CUPS-1]>num_stones[PLAYER][NUM_OF_CUPS-1])
        winner=0;
    
    else if(num_stones[COMPUTER][NUM_OF_CUPS-1]<num_stones[PLAYER][NUM_OF_CUPS-1])
        winner=1;
    
    else
        winner=-1;

    return winner;
    
}


int main(){
    
    int num_stones[NUM_OF_PLAYERS][NUM_OF_CUPS],winner;
    
    printf("***** Welcome to  the GAME *****\n\n");

    initialize_game(num_stones,NUM_OF_STONES);
    print_board(num_stones);
    printf("\n");
    winner=game_play(num_stones,PLAYER);
    
    if(winner==PLAYER)
        printf("Player won!! Skor: %d\n",num_stones[winner][NUM_OF_CUPS-1]);
    
    else if(winner==COMPUTER)
        printf("Computer won!! Skor: %d\n",num_stones[winner][NUM_OF_CUPS-1]);
    
    else
        printf("The game ended in a draw.\n");
    
    return 0;
   
}
