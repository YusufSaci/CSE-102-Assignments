#include <stdio.h>

#define MAX_NUM_FLOWER 100
#define MAX_SIZE_MAP 50


/* struct that holds information about the forest */
typedef struct {

    char map[MAX_SIZE_MAP][MAX_SIZE_MAP];
    int width;
    int height;
    int flower_x[MAX_NUM_FLOWER];
    int flower_y[MAX_NUM_FLOWER];


}Forest;


/* struct that holds information about the botanist */
typedef struct{

    int coord_x;
    int coord_y;
    int water_bottle_size;

}Botanist;

/* Check whether the coordinate belongs to the flowers or not*/
int is_flower(Forest forest, int num_of_flower, int x, int y){

    int i,result=0;

    for(i=0;i<num_of_flower;i++){
         if(y==forest.flower_y[i] && x==forest.flower_x[i]){

           result=i+1;
        }

    }
    
    return result; /*return the index of the flower*/

}

/* Removes the flower whose index is entered from the array. */
void remove_flower(Forest *forest, int num , int *num_of_flower){

    int i;

    for(i=num;i<(*num_of_flower)-1;i++){

        forest->flower_x[i]=forest->flower_x[i+1];
        forest->flower_y[i]=forest->flower_y[i+1];
    }

    (*num_of_flower)--; /* Reduce the number of flowers by one.*/

}

/* Stores information from the file in an array.*/
void init_game(Forest *forest, Botanist *botanist){
     
     char c;
     int i,j,k;

     FILE *fileptr;
     fileptr=fopen("init.txt","r");

     fscanf(fileptr,"%d %c %d ",&forest->height,&c,&forest->width);
     fscanf(fileptr,"%d %c %d %c %d ",&botanist->coord_y,&c,&botanist->coord_x,&c,&botanist->water_bottle_size);
         
     j=i=k=0;
     
     /* stores the map in array.*/
     while (fscanf(fileptr,"%c",&c)==1) {

    if(c=='X'){
            
            forest->flower_x[k]=j;
            forest->flower_y[k]=i;
            forest->map[i][j++]=' ';
            k++;

        }

        else if(c=='B'){
            forest->map[i][j++]=' ';
        }

        /* Stores trees and whitespaces.*/
        else{
            if (c != ',' && c != '\n'){
              forest->map[i][j++]=c;
            }
            /*next line*/
            else if(c=='\n'){
              i++;
              j=0;
            }
        }
    
     }

     fclose(fileptr);

}

/* Find the number of flowers in the forest*/
void find_num_flower(int *num_of_flower){

     FILE *fileptr;
     char c;
     fileptr=fopen("init.txt","r");

     while (fscanf(fileptr,"%c",&c)==1) {

        if(c=='X'){
            
            (*num_of_flower)++;

        }
     }

}

/* Prints the current view of the forest.*/
void display_forest(Forest forest,Botanist botanist, int num_of_flower, int collected_flower){

    int i,j;
    
     printf("\n\n");

     /* print the necessary information.*/
     printf("Botanist coordinates:(%d,%d)\n",botanist.coord_y,botanist.coord_x);
     printf("Number of collected flowers: %d\n",collected_flower);
     printf("Number of bottle: %d\n\n",botanist.water_bottle_size);


     for (i = 0;i < forest.width;i++) {

        for (j = 0;j < forest.height;j++) {

            if(botanist.coord_x==j && botanist.coord_y==i){ /* If the relevant coordinates are equal to those of the botanist, print B*/
                printf("B");
            }

            else if((is_flower(forest,num_of_flower,j,i))){ /* If the corresponding coordinates are equal to the coordinates of the flowers, print X*/
                printf("X");
            }

            else{
                printf("%c",forest.map[i][j]);/* prints spaces and trees.*/
            }

            if(j!=forest.height-1)
            printf(",");
        }

        printf("\n");
        
     }
     printf("\n");
     printf("=========================================================\n\n");
   

}

/* Return the botanist to the previous position.*/
void previous_location(char direction,Botanist *botanist){

    switch(direction){

        case 'r': botanist->coord_x--; break;

        case 'l': botanist->coord_x++; break;

        case 'u': botanist->coord_y++; break;

        case 'd': botanist->coord_y--; break;

    }
}

/* Ensures that the botanist acts according to the necessary rules */
void search(Forest *forest, Botanist *botanist, int *num_of_flower, int *collected_flower){
 
    int i,flag=1;
    char direction;

    display_forest(*forest,*botanist,*num_of_flower,*collected_flower);

    if((*num_of_flower)!=0){

        printf("Enter a direciton to move (Press e to exit): ");
        scanf(" %c",&direction);

        /* The location of the botanist is updated according to the entered direction*/
        switch(direction){

            case 'r': botanist->coord_x++; break;

            case 'l': botanist->coord_x--; break;

            case 'u': botanist->coord_y--; break;

            case 'd': botanist->coord_y++; break;

            case 'e': flag=0; break;

            default : printf("\nInvalid direction."); break;
        }
    }

    if(flag && !((*num_of_flower)==0)){
        

        /* Checks whether the botanist has gone out of the forest */
        if(botanist->coord_y<0 || botanist->coord_y>=forest->width || botanist->coord_x<0 ||  botanist->coord_x>=forest->height){
            previous_location(direction,botanist);
            printf("\nYou cannot leave the forest.");
        }

        /* Checks if the player only moves through spaces*/
        else if(forest->map[botanist->coord_y][botanist->coord_x]!=' '){
            previous_location(direction,botanist);
            printf("\nYou only move in whitespaces.");
        }

        /* If the botanist encounters a flower, necessary action will be taken.*/
        else if((i=is_flower(*forest,*num_of_flower,botanist->coord_x,botanist->coord_y))){

            (*collected_flower)++;
            remove_flower(forest,i-1,num_of_flower);/* The relevant flower is removed.*/
            botanist->water_bottle_size--;

            printf("\nI've found it!\n");
        }

        /* It continues recursively until the e button is pressed or all the flowers are collected. */
        search(forest,botanist,num_of_flower,collected_flower);
    }

}

/* saves the final version of the game in another file.*/
void print_txt(Forest forest, Botanist botanist,int num_of_flower,int collected_flower){

    FILE* fileptr;

    fileptr=fopen("last.txt","w");
     
     fprintf(fileptr,"Botanist coordinates:(%d,%d)\n",botanist.coord_y,botanist.coord_x);
     fprintf(fileptr,"Number of collected flowers: %d\n",collected_flower);
     fprintf(fileptr,"Number of bottle: %d\n\n",botanist.water_bottle_size);

    int i,j;

     for (i = 0;i < forest.width;i++) {

        for (j = 0;j < forest.height;j++) {

            if(botanist.coord_x==j && botanist.coord_y==i){
                fprintf(fileptr,"B");
            }

            else if((is_flower(forest,num_of_flower,j,i))){
                 fprintf(fileptr,"X");
            }

            else{
                fprintf(fileptr,"%c",forest.map[i][j]);
            }

            if(j!=forest.height-1)
            fprintf(fileptr,",");
        }

        fprintf(fileptr,"\n");
        
     }
     fclose(fileptr);
     
}

int main(){

    int num_of_flower=0,collected_flower=0;

    Botanist botanist;
    Forest forest;

    init_game(&forest,&botanist);
    find_num_flower(&num_of_flower);
    search(&forest,&botanist,&num_of_flower,&collected_flower);
    print_txt(forest,botanist,num_of_flower,collected_flower);

    printf("\nGame Over!\n");
    
    return 0;
}
