#include <stdio.h>
#include <string.h>

#define MAX_COL_COUNT 40
#define MAX_ROW_COUNT 30

/* Searches for the specified pattern in lines and saves the starting position .*/
void search_p1( char strs[][MAX_COL_COUNT], int num_rows, int matches[][2], int *num_matches){

    char match_array[]="***++++***++++***";
    int i;
    char *found;

    for(i=0;i<num_rows;i++){

        if((found=strstr(strs[i],match_array))!=NULL){/* Save the starting address if available in the line.*/

            matches[*num_matches][1]=found-strs[i]+1;/* save column position.*/
            matches[*num_matches][0]=i+1; /* save row position.*/

            (*num_matches)++;
        }

    }
    
}

/* Searches for the specified pattern in columns and saves the starting position .*/
void search_p2( char strs[][MAX_COL_COUNT], int num_rows, int matches[][2], int *num_matches){

    char match_array[]="+*+*+";
    int i=0,j=0,k,check=0,len;

    if(num_rows>=strlen(match_array)){

        len=strlen(strs[0])-2;/*number of columns. */

        for(i=0; i<len ;i++){ /* loop that will rotate as many as the number of columns.*/
        
            for(j=0;j<=num_rows-strlen(match_array);j++){  /* loop for columns equal to or longer than the searched pattern*/
            
                check=1;
                for(k=0; k<strlen(match_array); k++){ 

                    if(strs[j+k][i]!=match_array[k]){
                        check=0;
                        break;
                    }
                
                }

                /* If a relevant pattern is found, save it.*/
                if (check) { 
                    matches[*num_matches][0] = j+1; /* save row position.*/
                    matches[*num_matches][1] = i+1;  /* save column position.*/
                    (*num_matches)++;
                }
            
            }
        
        }
    }

}

/* search the desired pattern diagonally.*/
void search_p3( char strs[][MAX_COL_COUNT], int num_rows, int matches[][2], int *num_matches){

    char match_array[]="+**+++****+++**+";
    int i,j,k,len;
    int check1=0,check2=0;
       
     len=strlen(strs[0])-2;/*number of columns. */
    
    if(num_rows>=strlen(match_array)){

        for(i=0;i<len;i++){ /* loop that will rotate as many as the number of columns.*/

            for(j=0;j<=num_rows-strlen(match_array);j++){ /* loop for columns equal to or longer than the vertical component of searched pattern*/

                check1=1;
                check2=1;
                for(k=0;k<strlen(match_array);k++){

                    if((len-i>strlen(match_array)) || strs[j+k][i-k]!=match_array[k]){
                        check2=0;
                    }

                    if((len-i<strlen(match_array)) || strs[j+k][i+k]!=match_array[k]){
                        check1=0;
                    }

                }

                /* If a relevant pattern is found, save it.*/
                if (check1 || check2) {
                    matches[*num_matches][0] = j+1;
                    matches[*num_matches][1] = i+1;
                    (*num_matches)++;
                }
        
            }
        
        }   
    }

}

int main(){


    char input[MAX_ROW_COUNT][MAX_COL_COUNT];
    int matches[MAX_ROW_COUNT*3][2];
    int num_matches=0,i=0,num_rows=0,k,j;

    FILE *fileptr;

    fileptr=fopen("input2.txt","r");

    /* Storing data from file into array */
    while (fgets(input[i], MAX_COL_COUNT, fileptr) != NULL) {
        i++;
    }

    num_rows=i;

    /* Printing the array in which we record the positions of the found patterns.*/
    search_p1(input,num_rows,matches,&num_matches);

    for(i=0;i<num_matches;i++){
        printf("P%d @ (%d,%d)\n",1,matches[i][0],matches[i][1]);
    }

    search_p2(input,num_rows,matches,&num_matches);

    for(k=i;k<num_matches;k++){
        printf("P%d @ (%d,%d)\n",2,matches[k][0],matches[k][1]);
    }

    search_p3(input,num_rows,matches,&num_matches);

    for(j=k;j<num_matches;j++){
        printf("P%d @ (%d,%d)\n",3,matches[j][0],matches[j][1]);
    }

    return 0;
}
