#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>
#include <math.h>
#include "functions.h"

char *Enter_input()
{
   char *input;
   int ch;
   size_t i;

   input = malloc(1);
   i = 0;

   while((ch = getchar()) != '\n' && ch != EOF) {
       input[i++] = ch;
       input = realloc(input,i + 1);
   }

   input[i] = '\0';

   return input;
}

int check_phone_no(char *phoneNum)
{
   int i;

   if (strlen(phoneNum) == 0  ) {
       return 1;
   }
   
    if (strlen(phoneNum) == 7 || strlen(phoneNum) == 10 )
    { 
   for (i=0; i<strlen(phoneNum); i++) {
       if (!isdigit(phoneNum[i])) {
           return 1;
       }
   }
   return 0;
    }
    return 1; 
}

int check_len(char *input)
{
  int len=strlen(input);
  return len;
}

int check_mail(char *mail)
{
      int pos_domain =0;
      int pos_tld= 0;
      
      int flag = 0;
      int flag2=0;
    int j;
      for(j=0;j<strlen(mail);j++){
        if(mail[j] == '@'){
          pos_domain = j;
          flag = 1;
        }
        if(mail[j]== '.'){
          flag2 = 1;
          pos_tld = j;
        }
      }
      if(flag == 0 || flag2==0){
        return 0;
      }
    int i;
      for(i=0;i<strlen(mail);i++)
      {
        if(isalpha(mail[pos_domain-1]) == 0 || (isalpha(mail[pos_domain+1])==0)){
          flag = 0;
          break;
        }
        if(isalpha(mail[pos_tld+1])==0 || (isalpha(mail[pos_tld+2])==0) || (isalpha(mail[pos_tld+3])==0))
        {
          flag2 = 0;
          break;
        }
      }
      return flag;
}
 

 
