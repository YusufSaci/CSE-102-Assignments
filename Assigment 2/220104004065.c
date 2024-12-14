#include <stdio.h>

int main() {
    
    int max_x0,max_y0,max_x1,max_y1; /* Max x and y values ​​in both classes */
    int min_x0,min_y0,min_x1,min_y1; /* Min x and y values ​​in both classes */
    int one_time0=1,one_time1=1; /* To assign the first values ​​taken from the class */
    /*Values ​​read from the file and variables required to find the appropriate coordinate */
    int x,y,class,sep_x,sep_y;
    /*Variables that show how many elements from which class are in which region*/
    int r1_0=0,r1_1=0,r2_0=0,r2_1=0,r3_0=0,r3_1=0,r4_0=0,r4_1=0;
    int i,j;
    int allmax_x,allmax_y,allmin_x,allmin_y; /* Largest and smallest coordinate values ​​in the whole class */
    int r1,r2,r3,r4; /* For region labels */
    int error=0; /* Number of errors for each coordinate value */
    int min_error = 0;
    /*current class labels and coordinates */
    int actual_r1,actual_r2,actual_r3,actual_r4,actual_sep_x,actual_sep_y;
    int one=1;
    int total_data=0,succes=0; /* total number of data in the file and success rate */
    int choice,check_1=0,check_2=0;/* Control variables for the selection order in the menu*/
    
    FILE* file;
    FILE* file2;
    
    while(1){
        printf("\n**********MENU**********\n");
        printf("1-Data Exploration\n");
        printf("2-AI Model Construction\n");
        printf("3-Testing and Evaluating\n");
        printf("4-Exit the program\n");
        printf("Select the action you want to perform: \n");
        scanf("%d",&choice);
        
        switch(choice){
            case 1:
                check_1=1;
                file=fopen("data.txt","r");
                
                if(!file){
                    printf("Could not open file");
                    return 1;
                }
                /* finds the minimum and maximum x and y coordinates in the whole class by reading the values */
                while((fscanf(file,"%d %d %d",&x,&y,&class))==3){
                    
                    if(class==0){
                        /* To make a comparison, we assign the first values ​​we read for class 0. */
                        if(one_time0){
                            min_x0 = max_x0 = x;
                            min_y0 = max_y0 = y;
                            one_time0 = 0;
                        }
                        /* We find the max and min x y values ​​for class 0*/
                        if(x>max_x0) max_x0 = x;
                        
                        if(y>max_y0) max_y0 = y;
                        
                        if(x<min_x0) min_x0 = x;
                        
                        if(y<min_y0) min_y0 = y;
                        
                    }
                    else{
                        /* To make a comparison, we assign the first values ​​we read for class 1. */
                        if(one_time1){
                            min_x1 = max_x1 = x;
                            min_y1 = max_y1 = y;
                            
                            one_time1 = 0;
                        }
                        /* We find the max and min x y values ​​for class 1*/
                        if(x>max_x1) max_x1 = x;
                        
                        if(y>max_y1) max_y1 = y;
                        
                        if(x<min_x1) min_x1 = x;
                        
                        if(y<min_y1) min_y1 = y;
                        
                    }
                }
                /* We print the values ​​we found */
                printf("Minimum and maximum X and Y values:\n");
                printf("Class 0: X in [%d %d], Y in [%d %d]\n",min_x0,max_x0,min_y0,max_y0);
                printf("Class 1: X in [%d %d], Y in [%d %d]\n",min_x1,max_x1,min_y1,max_y1);
                
                fclose(file);
                break;
                
            case 2:
                /*  Before case 2, we check whether case 1 is selected or not*/
                if(check_1==0){
                    printf("To construct an artificial intelligence model, you must first explore the data.\n");
                }
                /* find the largest and smallest coordinates in both classes */
                else{
                    check_2=1;
                    if(min_x0<=min_x1){
                        allmin_x=min_x0;
                    }
                    else{
                        allmin_x=min_x1;
                    }
                    
                    if(min_y0<=min_y1){
                        allmin_y=min_y0;
                    }
                    else{
                        allmin_y=min_y1;
                    }
                    
                    if(max_x0<=max_x1){
                        allmax_x=max_x1;
                    }
                    else{
                        allmax_x=max_x0;
                    }
                    
                    if(max_y0<=max_y1){
                        allmax_y=max_y1;
                    }
                    else{
                        allmax_y=max_y0;
                    }
                    /* We examine all coordinates one by one to find the minimum number of errors. */
                    for(i=allmin_x;i<=allmax_x;i++){
                        for(j=allmin_y;j<=allmax_y;j++){
                            sep_x=i;
                            sep_y=j;
                            error=0;
                            r1_0=r1_1=r2_0=r2_1=r3_0=r3_1=r4_0=r4_1=0; /*  We reset for the new loop */
                            file=fopen("data.txt","r");
                            if(!file){
                                printf("Could not open file");
                                return 1;
                            }
                            while((fscanf(file,"%d %d %d",&x,&y,&class))==3){
                                
                               /* By comparing the x and y values ​​read with the separator, we decide in which region our data is and we increase our variable belonging to the appropriate class in that region by one. */
                                if(class==0){
                                    if(x<=sep_x && y>sep_y){
                                        r1_0++;
                                    }
                                    else if(x>sep_x && y>sep_y){
                                        r2_0++;
                                    }
                                    else if(x<=sep_x && y<=sep_y){
                                        r3_0++;
                                    }
                                    else if(x>sep_x && y<=sep_y){
                                        r4_0++;
                                    }
                                }
                                else{
                                    
                                    if(x<=sep_x && y>sep_y){
                                        r1_1++;
                                    }
                                    else if(x>sep_x && y>sep_y){
                                        r2_1++;
                                    }
                                    else if(x<=sep_x && y<=sep_y){
                                        r3_1++;
                                    }
                                    else if(x>sep_x && y<=sep_y){
                                        r4_1++;
                                    }
                                }
                            }
                            fclose(file);
                            /* Whichever class has more data, we assign that class label to that region and increase our error counter by the number of data with the other label.*/
                            if(r1_0>=r1_1){
                                r1=0;
                                error+=r1_1;
                            }
                            else{
                                r1=1;
                                error+=r1_0;
                            }
                            if(r2_0>=r2_1){
                                r2=0;
                                error+=r2_1;
                            }
                            else{
                                r2=1;
                                error+=r2_0;
                            }
                            if(r3_0>=r3_1){
                                r3=0;
                                error+=r3_1;
                            }
                            else{
                                r3=1;
                                error+=r3_0;
                            }
                            if(r4_0>=r4_1){
                                r4=0;
                                error+=r4_1;
                            }
                            else{
                                r4=1;
                                error+=r4_0;
                            }
                            /* Assignments made in case the first coordinates we received were valid */
                            if(one){
                                min_error=error;
                                actual_sep_x=sep_x;
                                actual_sep_y=sep_y;
                                actual_r1=r1;
                                actual_r2=r2;
                                actual_r3=r3;
                                actual_r4=r4;
                                one=0;
                            }
                            /* We update our variables for a smaller error value. */
                            if(error<min_error){
                                min_error=error;
                                actual_sep_x=sep_x;
                                actual_sep_y=sep_y;
                                actual_r1=r1;
                                actual_r2=r2;
                                actual_r3=r3;
                                actual_r4=r4;
                            }
                        }
                    }
                printf("Separator coordinates:X=%d Y=%d\n",actual_sep_x,actual_sep_y);
                printf("Training error of the model = %d\n",min_error);
                printf("Labels of the regions:R1=%d,R2=%d,R3=%d,R4=%d\n",actual_r1,actual_r2,actual_r3,actual_r4);
            }
            break;
                
                
            case 3:
                /*  Before case 3, we check whether case 2 is selected or not*/
                if(check_1==0){
                    printf("You must first construct an AI model to test and evaluate it.\n");
                }
                else{
                    file=fopen("test.txt","r");
                    
                    if(!file){
                        printf("Could not open file");
                        return 1;
                    }
                    printf("\n\nPredicted data label for test.txt:\n");
                    while((fscanf(file,"%d %d %d",&x,&y,&class))==3){
                        
                        total_data++;
                        /* After comparing the data we read from the file with the separators we found in the 2nd case, we compare it with the class label previously assigned to that region. If they are the same, we increment our counter by one. */
                        if(x<=actual_sep_x && y>actual_sep_y){
                            printf("%d %d %d\n",x,y,actual_r1);
                            if(actual_r1==class){
                                succes++;
                            }
                        }
                        else if(x>actual_sep_x && y>actual_sep_y){
                            printf("%d %d %d\n",x,y,actual_r2);
                            if(actual_r2==class){
                                succes++;
                            }
                        }
                        else if(x<=actual_sep_x && y<=actual_sep_y){
                            printf("%d %d %d\n",x,y,actual_r3);
                            if(actual_r3==class){
                                succes++;
                            }
                        }
                        else if(x>actual_sep_x && y<=actual_sep_y){
                            printf("%d %d %d\n",x,y,actual_r4);
                            if(actual_r4==class){
                                succes++;
                            }
                        }
                    }
                    fclose(file);
                    /* We print the success rate */
                    printf("Succes for test.txt : %0.2f \n\n",(float)succes/total_data);
                    
                    file2=fopen("test-final.txt","r");
                    
                    if(!file2){
                        printf("Could not open file");
                        return 1;
                    }
                    printf("Predicted data label for test-final.txt:\n");
                    while((fscanf(file,"%d %d",&x,&y))==2){
                        
                        /* After comparing the data in the last txt file with the separators we found before, we assign the appropriate label in that region and print it. */
                        if(x<=actual_sep_x && y>actual_sep_y){
                            
                            printf("%d %d %d\n",x,y,actual_r1);
                            
                        }
                        else if(x>actual_sep_x && y>actual_sep_y){
                            printf("%d %d %d\n",x,y,actual_r2);
                            
                        }
                        else if(x<=actual_sep_x && y<=actual_sep_y){
                            printf("%d %d %d\n",x,y,actual_r3);
                            
                        }
                        else if(x>actual_sep_x && y<=actual_sep_y){
                            printf("%d %d %d\n",x,y,actual_r4);
                        }
                    }
                    fclose(file2);
                }
                    break;
                    
                case 4:
                /* exit */
                    return 0;
                    break;
                    
                default:
                    printf("Invalid choice. Please choose again.\n");
            }
    }
    return 0;
}



