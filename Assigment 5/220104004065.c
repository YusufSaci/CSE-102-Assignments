#include <stdio.h>
#define NUM_OF_MAGIC_NUM 9

/* Checks whether the news has been read before. */
int check_news(int which_news){
    
    FILE* readed_news=fopen("readed_news_id.txt","r");
    int num;
    
    /* Reads the characters in the file one by one.*/
        while((fscanf(readed_news,"%d",&num))==1){
            if(num==which_news){
                fclose(readed_news);
                return 1;
            }
        }
    
    fclose(readed_news);
    return 0;
}

/* Finds magic numbers and how many they are in the text read.*/
void info_about_magic(FILE* news,char ch,int magic_num[],int *num_of_magic,int *index){
    
    if(ch=='#'){
        (*num_of_magic)++;
        fscanf(news,"%c",&ch);
        printf("%c",ch);
        
        magic_num[*index]=ch-'0';/* Stores the magic numbers  in the array */
        (*index)++;
    }
}

/* Calculates secret number by applying the necessary functions*/
float cal_secret_num(int magic_num[],int number_of_magic){
    int i,f=0,g=0,x,result=0;
    
    /* Applies necessary functions to magic numbers.*/
    for(i=0;i<number_of_magic;i++){
        x=magic_num[i];
        f=x*x*x-x*x+2;
        g=f*f;
        result+=g;
    }
    return result;
}

/* It reads and prints the characters in the desired file and collects information about the magic numbers in that text. */
void read_news(int which_news,int *num_of_magic,int magic_num[], char option){
    
    char ch;
    int index=0,flag=1;
    
    FILE* fileptr;
    FILE* readed_news=fopen("readed_news_id.txt","a");
    
    switch(which_news){
            
        case 1: fileptr=fopen("1.txt","r"); break;
            
        case 2: fileptr=fopen("2.txt","r"); break;
            
        case 3: fileptr=fopen("3.txt","r"); break;
            
        case 4: fileptr=fopen("4.txt","r"); break;
            
        default: printf("invalid input.\n"); flag=0; break;
    }
    /* If the news has not been read yet and it is valid, add it to the readed_news file*/
    if(flag==1){
        if(!check_news(which_news) && option!='c')
            fprintf(readed_news,"%d ",which_news);
    }
    
    /* Read and print the desired news and collect information about magic numbers.*/
    while((flag==1 && fscanf(fileptr,"%c",&ch)==1 )){
        printf("%c",ch);
        info_about_magic(fileptr,ch,magic_num,num_of_magic,&index);
    }
      
    if(flag==1)
    fclose(fileptr);
    fclose(readed_news);
}

void menu(){
    
    char choice,ch='y',check;
    int news,readed,num_of_magic,magic_num[NUM_OF_MAGIC_NUM],flag=1;
    float secret_num;
    
    FILE* newsptr;
    FILE* readed_news;
    
    while(ch!='n'){
        num_of_magic=0;
        /* Print the menu and title of the news.*/
        printf("\n\n****************Daily Press**************\n\n");
        printf("Today's news are listened for you: \n");
        
        newsptr= fopen("1.txt","r");
        printf("\nTitle of 1. news:");
        while(fscanf(newsptr,"%c",&ch) && ch!='\n'){
            printf("%c",ch);
        }
        fclose(newsptr);
        
        newsptr= fopen("2.txt","r");
        printf("\nTitle of 2. news:");
        while(fscanf(newsptr,"%c",&ch) && ch!='\n'){
            printf("%c",ch);
        }
        fclose(newsptr);
        
        newsptr= fopen("3.txt","r");
        printf("\nTitle of 3. news:");
        while(fscanf(newsptr,"%c",&ch) && ch!='\n'){
            printf("%c",ch);
        }
        fclose(newsptr);
        
        newsptr= fopen("4.txt","r");
        printf("\nTitle of 4. news:");
        while(fscanf(newsptr,"%c",&ch) && ch!='\n'){
            printf("%c",ch);
        }
        fclose(newsptr);
        
        
        printf("\n\nWhat do you want to do?\n");
        printf("a.Read a new.\n");
        printf("b.List a readed news.\n");
        printf("c.Get decrypted information from the news.\n");
        scanf(" %c",&choice);
        
        switch(choice){
            case 'a':
                printf("\nWhich news would you like to read?\n");
                scanf("%d",&news);
                printf("\n");
                
                if(check_news(news)){ /* Check if the news has been read before and print appropriate messages .*/
                    printf("This new is readed. Do you want to read again? Yes(1)/No(0)\n");
                    scanf(" %c",&check);
                    
                    if(check=='1'){
                        read_news(news,&num_of_magic,magic_num,choice);
                    }
                    else if(check!='0'){
                        printf("Invalid input.\n");
                    }
                }
                
                else{
                    read_news(news,&num_of_magic,magic_num,choice);
                }
                break;
                
            case 'b':
                readed_news=fopen("readed_news_id.txt","r");
                
                /* Print previously read news. */
                while((fscanf(readed_news,"%d",&readed))==1){
                    printf("%d. new is readed\n",readed);
                    flag=0;
                }
                
                if(flag==1){
                    printf("No news could be read.\n");
                }
                fclose(readed_news);
                break;
                
            case 'c':
                printf("\nWhich news would you like to decrypt?: ");
                scanf("%d",&news);
                
                read_news(news,&num_of_magic,magic_num,choice);
                /* According to the information collected from the readed news, calculate and print the secret number.*/
                secret_num=cal_secret_num(magic_num,num_of_magic);
                
                printf("\n%d. Experimet Key = %.2f\n",news,secret_num);
                break;
                
            default: printf("invalid Input.\n"); break;
                
        }
        /* Ask if the user wants to continue */
        do{
            printf("\nDo you want to continue? Yes(y)/No(n): \n");
            scanf(" %c",&ch);
            
            if(ch=='n')
                printf("Good Bye!\n");
            else if(ch!='y' && ch!='n')
            printf("Invalid input. Try again\n");
            
        } while(!(ch=='y' || ch=='n'));
    }
}

int main() {
    menu();
    return 0;
}
