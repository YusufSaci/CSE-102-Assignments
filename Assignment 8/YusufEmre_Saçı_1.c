
#include <stdio.h>
#include <string.h>

#define MAX_OF_PERSON 30
#define NUM_OF_INFO 5
#define MAX_LENGTH 25
#define MAX_LINE 100

/* It sorts the elements of the relevant array in the index array from smallest to largest */
void sort(char data[][NUM_OF_INFO][MAX_LENGTH],int index[], int n, int mode){
    
    int i,k,temp,len1,len2,min;
    
    for(i=0;i<n-1;i++){
        for(k=0;k<n-i-1;k++){
   
             /* Those who do not have a second branch should be at the bottom*/
             if((strcmp(data[index[k + 1]][mode],"")==0 && mode==4));

             /* Compares two consecutive elements.*/
             else if ((strcmp(data[index[k]][mode],"")==0 && mode==4) || (strcmp(data[index[k]][mode], data[index[k + 1]][mode])) > 0) {
                
                temp=index[k];
                index[k]=index[k+1];
                index[k+1]=temp;
                
                
            }
        }
    }
}

/* Prints the list.*/
void print_txt(char data[][NUM_OF_INFO][MAX_LENGTH],int index[],int num_person){

    int i,j,k;

     printf("Name                Surname             Age                 Branch1             Branch2         \n\n\n");
     

    for(i=0;i<num_person;i++){

        for(j=0;j<NUM_OF_INFO;j++){

            printf("%-20s",data[index[i]][j]);
        }
        printf("\n\n");
            
     }
    
}

/* Reads data from file and stores it in array.*/
void convert_to_array(char data[][NUM_OF_INFO][MAX_LENGTH], int *num_person){

     FILE *fileptr;
    
     int i=0,j,k,l;
     char temp[MAX_OF_PERSON][MAX_LINE];
     char *token,len;
    
     fileptr=fopen("input1.txt","r");
    
     while (fgets(temp[i], MAX_LINE, fileptr) != NULL) {/* Stores line by line .*/
        
         i++;
     }
    
     *num_person=i;

    for(i=0;i<*num_person-1;i++){
        temp[i][strlen(temp[i])-2]='\0';
    }
    
    /* fills the array with empty strings.*/
     for(i=0; i<*num_person; i++) {

        for(j=0; j<NUM_OF_INFO; j++) {

            strcpy(data[i][j],"");
        }
     }
   
     /* Stores all information by separating it with commas.*/
     for(i=0;i<*num_person;i++){
        
        j=0;
        token = strtok(temp[i], ",");
              
        while (token != NULL) {
            len=strlen(token);
            
            /* If there is a leading space character, it will remove it.*/
            if(token[0]==' '){

                for(l=0,k=1;k<len;l++,k++){

                    token[l]=token[k];
                }
                token[len-1]='\0';
            }
            
            strcpy(data[i][j++],token);
            
            token = strtok(NULL, ",");
            
        }
     }

     fclose(fileptr);
    
}

 
void sort_people_by_age(char data[][NUM_OF_INFO][MAX_LENGTH], int num_person){
     
    int index[num_person],i;

    for(i=0;i<num_person;i++){
        index[i]=i;
    }

    /* sort people by age and print the sorted list. */
    sort(data,index,num_person,2);
    
    print_txt(data,index,num_person);
    
}

void sort_people_by_branch(char data[][NUM_OF_INFO][MAX_LENGTH], int num_person){
      
    int index[num_person],i;

    for(i=0;i<num_person;i++){
        index[i]=i;
    }

    sort(data,index,num_person,2); /* sort people by age. */
    sort(data,index,num_person,4); /* sort people by second branch. */
    sort(data,index,num_person,3); /* sort people by first branch. */
    
    print_txt(data,index,num_person);
     
}


void filter_people_by_branch(char data[][NUM_OF_INFO][MAX_LENGTH], int num_person){

      
     char filter[20]="SCIENCE";
     int i,k=0;
     int index[num_person];

     for(i=0;i<num_person;i++){
        index[i]=i;
     }
     
     /*Store indexes of people with this profession.*/
     for(i=0;i<num_person;i++){

        if(strstr(data[i][3],filter)!=NULL || strstr(data[i][4],filter)!=NULL )
        index[k++]=i;
       
     }
     
     print_txt(data,index,k);/* print the selected people*/

}

void filter_people_by_profession (char data[][NUM_OF_INFO][MAX_LENGTH], int num_person){

     int index[num_person],i,k=0;

     for(i=0;i<num_person;i++){
        index[i]=i;
     }
    /* Save indexes for people whose profession are computer science but not mathematics.*/
     for(i=0;i<num_person;i++){
    
       if(strcmp(data[i][3],"COMPUTER SCIENCE")==0 && strcmp(data[i][4],"MATHEMATICS")!=0)
        index[k++]=i;
        
     }

     print_txt(data,index,k);

}

int main() {

    int choice,flag=0,num_person;
    char data[MAX_OF_PERSON][NUM_OF_INFO][MAX_LENGTH];
    
    convert_to_array(data,&num_person);
    
    /* Print the menu.*/
    printf("\n*********************** MENU **********************\n");
    printf("1. Sort and display all individuals by age.\n");
    printf("2. Sort and display individuals int the branch by age.\n");
    printf("3. Show individuals with the branch 'SCIENCE'.\n");
    printf("4. Show computer scientist who are not mathematicians.\n");
    printf("5. Exit.\n");
    
    while(flag==0){

        printf("**************************************************************************\n\n");
        printf("Choice: ");
        scanf(" %d",&choice); /* Get input from the user.*/
        printf("\n");

        /* Perform the selected action.*/
        switch(choice){

            case 1: sort_people_by_age(data,num_person); break;

            case 2: sort_people_by_branch(data,num_person); break;

            case 3: filter_people_by_branch(data,num_person); break;
        
            case 4: filter_people_by_profession(data,num_person); break;

            case 5: flag=1; printf("Program is terminating...\n"); break;

            default: printf("invalid input.\n"); break;
        }
    }
    
    return 0;
}

