#include <stdio.h>
#define MAX_NUM_ADD_NUMBER 5
#define MAX_B_VALUE 200

/* Finds the size of the array. */
int find_size_of_array(int number_array[]) {
    
    int i, size = 0;
    
    /*increases size until element is -1 */
    for (i = 0; number_array[i] != -1; i++) {
        size++;
    }
    return size;
}

/* Calculates the number of repetitions of elements in a certain range in the array. */
void num_of_repeat(int number_array[], int n, int max_eleman, int num_repeat[]) {
    
    int i;
    
    /* Assigns 0 to all elements in the array. */
    for (i = 0; i <= max_eleman; i++) {
        num_repeat[i] = 0;
    }
    for (i = 0; i < n; i++) {
        num_repeat[number_array[i]]++;
    }
}

/*Finds the maximum number of repetitions in a certain range in the array. */
int max_repeat(int num_repeat[], int max_eleman, int min_eleman) {
    
    int i, max;
    
    max = num_repeat[min_eleman];
    
    /* Compares all elements and find the one that repeats the most. */
    for (i = min_eleman + 1; i <= max_eleman; i++) {
        if (num_repeat[i] > max) {
            max = num_repeat[i];
        }
    }
    
    return max;
}

/* Draws a histogram according to the number of repetitions of elements */
void draw_histogram(int a, int b,int num_repeat[]) {
    
    int i, j,max;
    
    max = max_repeat(num_repeat, b, a);
    
    for (i=max; i>0 ; i--) {
        for (j = a; j <= b; j++) {
            
            if (num_repeat[j] >= i) {
                printf("*");
            } else {
                printf(" ");
            }
        }
        printf("\n");
    }
}

/*Calculates and prints the average of numbers in the desired range. */
void print_average(int num_repeat[],int a,int b){
    
    int i,counter=0;
    float avg=0;
    
    for(i=a;i<=b;i++){
        /* Finds how many elements there are by using the number of repetitions of all elements in a certain range */
            counter+=num_repeat[i];
        /*
         It finds the sum of all elements in the array by multiplying that repeating element by the number of repetitions.*/
            avg+=num_repeat[i]*i;
    }
    
    printf("\nAverage: %.2f\n",avg/counter);
}

/*Prints the most repeated elements in the array. */
void print_mode(int num_repeat[], int a, int b){
    
    int max,i;
    
    max = max_repeat(num_repeat, b, a);
    
    printf("Mode: ");
    for(i=a;i<=b;i++){
        /* If the number of repetitions of the element is equal to the maximum number of repetitions, print it */
        if(num_repeat[i]==max){
            printf("%d ",i);
        }
    }
    printf("\n");
    
}

/* Finds the median of the array and prints it. */
void print_median(int num_repeat[],int a, int b){
    
    int i,j;
    int size=0,counter=0;
    float median=0;
    
    for(i=a;i<=b;i++){
            size+=num_repeat[i]; /* calculates the size of the array. */
    }
    
    for(i=a;i<=b;i++){
        for(j=0;j<num_repeat[i];j++){
                
            counter++;
            
            /* If the number of elements of the array is even, add the first of the two middle elements to the median.*/
            if(size%2==0 && counter==size/2 ){
                median+=i;
            }
            
            /* Add the element in the middle of the array to the median. */
            if(counter==(size/2)+1){
                median+=i;
            }
        }
    }
    
    if(size%2==0)
        printf("Median: %.2f\n",median/2);

    else
        printf("Median: %.2f\n",median);
   
}

int main() {
    
    int a,b,n,choice,add_num=0,i=0,flag;
    
    int number_array[] = {58, 63, 62, 62, 62, 62, 63, 74, 80, 57, 73, 58, 70, 58, 69, 73, 57, 80, 85, 71, 83, 62, 58, 74, 66, 70, 63, 71, 85, 67, 70, 71, 63, 71, 62, 57, 58, 59, 74, 66, 56, 63, 73, 74, 71, 80, 80, 84, 69, 74,-1};
    
    int num_repeat[MAX_B_VALUE+1];
    
    n = find_size_of_array(number_array);
    
    /* Prompt the user for a limit until a valid limit is entered. */
    do{
        printf("Enter A and B values: ");
        scanf("%d %d", &a, &b);
        flag=0;
      
        if((a<50 || a>200) || (b<50 || b>200)){
            printf("Numbers can be between 50 and 200. TRY AGAIN!\n");
            flag=1;
        }
        
        else if(a>b){
            printf("The value A must be less than B. TRY AGAIN!\n");
            flag=1;
        }
        
    }while(flag==1);
    
    num_of_repeat(number_array,n,b,num_repeat);
    draw_histogram(a,b,num_repeat);
    
    printf("would you like to add new numbers? (Press 1 for yes, Press 0 for no: ");
    scanf("%d",&choice);
    
    if(choice==1){
        
        flag=1;
        printf("Enter the numbers (press -1 to exit):\n");
        
        /* Get value until user enters -1 (The user can enter a maximum of 5 values) */
        for(i=0;i<MAX_NUM_ADD_NUMBER && flag==1;i++){
            scanf("%d",&add_num);
            
            /*If the values ​​are in the desired range, increase the number of repetitions of that value by one.*/
            if(add_num>=a && add_num<=b){
                                         
                num_repeat[add_num]++;
            }
            else if(add_num!=-1){
                printf("The number entered is not within the specified interval.\n");
            }
            else
                flag=0;
        }
        printf("\n");
        
        draw_histogram(a, b,num_repeat);
    }
    
    print_average(num_repeat,a,b);
    print_median(num_repeat,a,b);
    print_mode(num_repeat,a,b);
    
    return 0;
}

