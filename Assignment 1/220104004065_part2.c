
#include<stdio.h>

/*Checks whether the received character is in the alphabet or not.*/
int check(char alphabet[61],char ch){
    int i;
    for(i=0;i<61;i++){
        if(ch==alphabet[i]){
            return 1;
        }
    }
    return 0;
}

/*Returns the order of the entered character in our alphabet.*/
int correspond(char alphabet[61],char ch){
    int i;
    for(i=0;i<61;i++){
        if(ch==alphabet[i]){
            return i;
        }
    }
    return 0;
}

/*Calculates key value according to student id*/
int find_key(long int student_id){

    int result=0,temp;

    while(student_id>0){
        result+=student_id%10;
        student_id/=10;
    }
    /* Performs addition until the sum of the digits of the number is less than 10 */
    while(result>9){
        temp=0;
        while(result>0){
            
            temp+=result%10;
            result/=10;
        }
        result=temp;
    }

    return result;
}
/* This function decrypts the encrypted code */
char decrypt_code(char encrypted_c,char alphabet[61],int key_value){
    
    char ch;
    
    /*Checks whether the received character is in the alphabet or not.*/
            if(check(alphabet,encrypted_c)){
                
                /* It operates according to whether it is at the end of the alphabet or not.*/
                if((correspond(alphabet,encrypted_c)>=key_value)){
                    /* prints the character corresponding to the encrypted character */
                    ch=alphabet[(correspond(alphabet,encrypted_c)-key_value)];
                    return ch;
                }
                else{
                    ch=alphabet[correspond(alphabet,encrypted_c)-key_value+61];
                    return ch;
                }
            }
            else{
                return encrypted_c;
            }
        }


int main(void){
    
    
    char c; /* input variable*/
    long int student_id=220104004065;
    int key_value;
    
    char marker='@';
    
    char alphabet[61] = {'a', 'b', 'c', 'd', 'e', 'f', 'g', 'h', 'i', 'j', 'k', 'l', 'm', 'n', 'o', 'p', 'q', 'r', 's', 't', 'u', 'v', 'w', 'x', 'y', 'z', '(', '<', '=', '+', ')', '[', '*', '/', ']', '{', '>', '!', '-', '}', '?', '\\', '&', '|', '%', '_', ';', '"', '#','.', '\'', '0', '1', '2', '3', '4', '5', '6', '7', '8', '9'};
    
    key_value=find_key(student_id);
    
    printf("Decrypted C code: \n\n");
    
    /* It starts decrypting after the # sign, that is, the beginning of the C code. */
    while((scanf("%c",&c))==1){
        if(c==alphabet[(correspond(alphabet,'#')+key_value)]){
            break;
        }
    }

    /* Get input until the end of the file*/
    do{
            /* If there is a character indicating that it has a comment, enter it inside the if*/
            if(c==marker){
                /* for space */
                scanf("%c",&c);
                scanf("%c",&c);
                
                /* Prints how many characters are in the comment*/
                printf("/* There is ");
                while(check(alphabet,c)){
                    
                    printf("%c",decrypt_code(c,alphabet,key_value));
                    scanf("%c",&c);
                }
                printf(" characters as comment.*/");
                printf("%c",c);
                
            }
            else
            /*prints decrypted characters */
                printf("%c",decrypt_code(c,alphabet,key_value));
    }while((scanf("%c",&c))==1);
    
    
return 0;
}
