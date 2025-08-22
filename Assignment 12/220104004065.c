#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "customDict.h"


int main(){

    struct CustomDict *dict=create_dict();
    union Value *value;
    int num,i,num_val;
    char *val[10];

    for (i = 0; i < 10; i++) {
        val[i] = (char *)malloc(3 * sizeof(char)); 
    }

    printf("\n****************************** MENU ********************************\n\n");
    printf("1-Read .csv file and  populates the dictionary accordingly.\n");
    printf("2-Sorts the dictionary by keys.\n");
    printf("3-Updates the value associated with the specified key.\n");
    printf("4-Searches for an item in the dictionary by its key and returns its value.\n");
    printf("5-Deletes an item from the dictionary by its key.\n");
    printf("6-Adds a new item to the dictionary with the specified key and value.\n");
    printf("7-Frees the memory allocated for the dictionary.\n");
    printf("8-EXIT.\n");

    do{
    printf("\n------------------------------------------------\n");
    printf("\nSelect the action you want to perform: "); 
    scanf("%d",&num);/* get input from the user */
    printf("\n\n");
    value=(union Value*)malloc(sizeof(union Value));

    /* Perform the action requested by the user*/
    switch(num){
        case 1: 
            if(read_csv(dict, "data.csv"))
            print_dict(dict); 
            break;

        case 2: 
            sort_dict(dict); 
            print_dict(dict); 
            break;

        case 3: 
            /* Update the values ​​of the score key with the specified values*/
            strcpy(val[0],"5");  strcpy(val[1],"10");  strcpy(val[2],"15"); strcpy(val[3],"25");
            value=load_value("int",val,4);
            set_value(dict,"score",value,4);
            print_dict(dict);
            break;
        
        case 4:
            /* print the values ​​of the temperature key*/
            value=search_item(dict,"temperature",&num_val);
            if(value==NULL){
                printf("The key you were looking for was not found.\n");
            }
            else{
                printf("Value: ");
                print_value("float",value,num_val);
            }
            break;

        case 5: 
            delete_item(dict,"price");
            print_dict(dict);
            break;
        
        case 6:
            /* Add time item to dictionary with specified values*/
            strcpy(val[0],"3");  strcpy(val[1],"6");  strcpy(val[2],"9"); strcpy(val[3],"12"); strcpy(val[4],"23");
            value=load_value("int",val,5);
            add_item(dict,"time",value,"int",5);
            print_dict(dict);
            break;

        case 7: 
            free_dict(dict); 
            printf("Allocated memory has been cleared.\n");
            break;

        case 8: 
            return 0;

        default: 
            printf("invalid input try again.\n");
            break;

    }

    }while(num!=8);
    
    for (i = 0; i < 10; i++) {
        free(val[i]);
    }

    return 0;
}
