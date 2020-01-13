#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>
#include <math.h>
#include "functions.h"

struct contact
{
unsigned long phone_number;
long first_name_posn;
long last_name_posn;
long company_name_posn;
long email_posn;
long next;
};

struct data
{
  unsigned long phoneNo;
  char  first_name[30];
  char last_name[30];
  char comp_name[30];
  char alias[50];

};

 int  contacts_No()
{
  struct contact RecordData;
   FILE *file;
  file = fopen("myContactsList.db","a+");

  fseek(file,0,SEEK_END);
  long  endfile = ftell(file);
  fseek(file,0,SEEK_SET);


  int i=0;
  if(endfile >0)
  {

      while(!feof(file))
      {

        fread(&RecordData, sizeof(struct contact),1,file);
        i++;
        if(RecordData.next == endfile)
        {
            break;
        }
        fseek(file,RecordData.next,SEEK_SET);

      }
  }
  fclose(file);
  return i;
}

int struct_cmp_by_alias(const void *a, const void *b)
{
    struct data *ia = (struct data *)a;
    struct data *ib = (struct data *)b;

    return strcmp(ia->alias, ib->alias);

}

void print_struct_array(struct data *array, int len)
{
    int j;
    char fullname[50];
    for(j=0; j<len; j++)

    if(strlen(array[j].last_name) !=0){

    strcpy(fullname, array[j].first_name);
    strcat(fullname, " ");
    strcat(fullname, array[j].last_name);

     printf("%d. %s\n",j+1,fullname);
    }
    else
    {
       printf("%d. %s\n",j+1,array[j].comp_name);
    }



}

int display_contacts(struct data *mystruct)
{

  struct contact RecordData;
   FILE *file;

   file = fopen("myContactsList.db","a+");

  char firstname[30];
  char lastname[30];
  char comp[30];


  fseek(file,0,SEEK_END);
  long  endfile = ftell(file);
  fseek(file,0,SEEK_SET);



  int i=0;
  if(endfile >0)
  {

      while(!feof(file))
      {

        fread(&RecordData, sizeof(struct contact),1,file);

        if(RecordData.first_name_posn !=0 )
        {
                    fseek(file,RecordData.first_name_posn,SEEK_SET);
                    fread(firstname,sizeof(char),30,file);
                    strcpy( mystruct[i].first_name,firstname);
        }
        else
        {
            strcpy( mystruct[i].first_name,"");

        }

        if(RecordData.last_name_posn !=0 )
        {
            fseek(file,RecordData.last_name_posn,SEEK_SET);
            fread(lastname,sizeof(char),30,file);
            strcpy( mystruct[i].last_name,lastname);

        }
        else
        {
            strcpy( mystruct[i].last_name,"");

        }
        if(RecordData.company_name_posn !=0 )
        {

            fseek(file,RecordData.company_name_posn,SEEK_SET);
            fread(comp,sizeof(char),30,file);
            strcpy( mystruct[i].comp_name,comp);
        }
        else
        {
            strcpy( mystruct[i].comp_name,"");
        }
        if(RecordData.last_name_posn >0 )
        {
          strcpy( mystruct[i].alias,lastname);
        }
        else
        {
            strcpy( mystruct[i].alias,comp);
        }

        mystruct[i].phoneNo=RecordData.phone_number;

        i++;


        if(RecordData.next == endfile)
        {
            break;
        }

         fseek(file,RecordData.next,SEEK_SET);

      }


    qsort(mystruct, i, sizeof(struct data), struct_cmp_by_alias);
    print_struct_array(mystruct,i);

  }
      fclose(file);

      return i;
}

void show_contact(long temp_phone)
{

      struct contact RecordData;
      FILE *file;

     file = fopen("myContactsList.db","a+");

     char firstname[30];
     char lastname[30];
     char comp[30];
     char mail[30];

        fseek(file,0,SEEK_END);
        long  endfile = ftell(file);

         fseek(file,0,SEEK_SET);
         while(!feof(file))
         {

            fread(&RecordData, sizeof(struct contact),1,file);

            if(temp_phone == RecordData.phone_number)
            {

                      if(RecordData.first_name_posn !=0 )
                       {

                           fseek(file,RecordData.first_name_posn,SEEK_SET);

                           fread(firstname,sizeof(char),30,file);
                           printf("First Name: %s\n",firstname);
                        }
                        else
                        {
                            printf("First Name: \n");
                        }

                        if(RecordData.last_name_posn !=0 ){

                        fseek(file,RecordData.last_name_posn,SEEK_SET);

                        fread(lastname,sizeof(char),30,file);
                        printf("Last Name: %s\n",lastname);
                        }
                        else
                        {
                            printf("Last Name: \n");
                        }
                        if(RecordData.company_name_posn !=0 )
                        {

                          fseek(file,RecordData.company_name_posn,SEEK_SET);

                          fread(comp,sizeof(char),30,file);
                          printf("Company Name: %s\n",comp);

                        }
                        else
                        {
                            printf("Company Name: \n");
                        }

                        printf("Phone Number: %ld\n",temp_phone);

                        if(RecordData.email_posn !=0 )
                        {

                          fseek(file,RecordData.email_posn,SEEK_SET);
                          fread(mail,sizeof(char),30,file);
                          printf("Email: %s\n",mail);
                        }
                        else
                        {
                            printf("Email: \n");
                        }


                        break;
                       }

                      else
                      {
                          fseek(file,RecordData.next,SEEK_SET);
                      }
                      if(RecordData.next == endfile)
                      {
                          printf("No match found.\n");
                          break;
                      }
                 }
                 fclose(file);
}



void add_newcontact()
{
   struct contact *info;
   info = malloc(sizeof(struct contact));

   char *first_name;
   char *last_name;
   char *company;
   char *phone;
   char *email;
   int temploc=0;

   FILE *file;
   file = fopen("myContactsList.db","a+");

  fseek(file,0,SEEK_END);
  info->next=ftell(file);

  printf("First Name: ");
  first_name = Enter_input();

  do{
      printf("Last Name: ");
      last_name = Enter_input();
      printf("Company Name: ");
      company = Enter_input();
    }while(strlen(last_name) ==0 && strlen(company) ==0);

    do {
            printf("Phone Number (enter only numbers): ");
            phone = Enter_input();
       } while(check_phone_no(phone) != 0);


    do{
            printf("Email: ");
            email = Enter_input();
            if(strlen(email) ==0) break;
      }while(check_mail(email)==0 );

           info->phone_number = strtol(phone, NULL,10);
           temploc=0;
           if(check_len(first_name)>0)
           {
              info->first_name_posn = info->next+sizeof(struct contact);
              temploc=info->first_name_posn;
           }
           else
           {
               info->first_name_posn =0;
               temploc=info->next+sizeof(struct contact);
            }


            if(check_len(last_name)>0)
            {
               info->last_name_posn = temploc + 30;
               temploc= info->last_name_posn;
            }
           else
           {
               info->last_name_posn=0;
               temploc=temploc +30;
            }

            if(check_len(company)>0)
            {
                info->company_name_posn = temploc + 30;
                temploc= info->company_name_posn;
            }
            else
            {
                info->company_name_posn=0;
                temploc=temploc + 30;
            }

           if(check_len(email)>0)
           {
               info->email_posn = temploc +30;
               temploc= info->email_posn;
           }
          else
          {
            info->email_posn =0;
            temploc=temploc + 30;
          }


          info->next =temploc + 30;

          char *action;
          printf("\nActions:");
          printf("R-Return To main don't update contact list \nS- Save Contact and return to main\nSelect Action:");
          action=Enter_input();

          if(strcmp(action,"S")==0)
          {
           fwrite(info, sizeof(struct contact),1,file);
           fwrite(first_name,1,30,file);
           fwrite(last_name,1,30,file);
           fwrite(company,1,30,file);
           fwrite(email,1,30,file);

           }

        fclose(file);
}

void delete_contact(long temp_phone)
{
      struct contact RecordData;
      FILE *file,*ftemp;

        file = fopen("myContactsList.db","a+");
        ftemp = fopen("Temp.db","w+");

        char firstname[30];
        char lastname[30];
        char comp[30];
        char mail[30];
        struct contact *info;
        info = malloc(sizeof(struct contact));

        fseek(file,0,SEEK_END);
        long  endfile = ftell(file);

        fseek(file,0,SEEK_SET);
        int last_next_pos=0;
        while(!feof(file))
        {

            fread(&RecordData, sizeof(struct contact),1,file);
            if(temp_phone == RecordData.phone_number)
            {
                fseek(file,RecordData.next,SEEK_SET);
            }
            else
            {
                int temploc=0;
                if(RecordData.next != last_next_pos && last_next_pos !=0)
                {
                    info->next=last_next_pos;
                    if(RecordData.first_name_posn !=0 )
                    {

                        fseek(file,RecordData.first_name_posn,SEEK_SET);
                        fread(firstname,sizeof(char),30,file);
                        info->first_name_posn = info->next+sizeof(struct contact);
                        temploc=info->first_name_posn;

                    }
                    else
                    {
                            strcpy(firstname,"");
                            info->first_name_posn =0;
                            temploc=info->next+sizeof(struct contact);
                    }

                    if(RecordData.last_name_posn !=0 )
                    {
                        fseek(file,RecordData.last_name_posn,SEEK_SET);
                        fread(lastname,sizeof(char),30,file);
                        info->last_name_posn = temploc + 30;
                        temploc= info->last_name_posn;

                    }
                    else
                    {
                        strcpy(lastname,"");
                        info->last_name_posn=0;
                        temploc=temploc +30;

                    }
                    if(RecordData.company_name_posn !=0 )
                    {
                        fseek(file,RecordData.company_name_posn,SEEK_SET);
                        fread(comp,sizeof(char),30,file);
                        info->company_name_posn = temploc + 30;
                        temploc= info->company_name_posn;

                    }
                    else
                    {
                        strcpy(comp,"");
                        info->company_name_posn=0;
                        temploc=temploc + 30;
                    }

                    if(RecordData.email_posn !=0 )
                    {

                        fseek(file,RecordData.email_posn,SEEK_SET);
                        fread(mail,sizeof(char),30,file);
                        info->email_posn = temploc +30;
                        temploc= info->email_posn;
                    }
                    else
                    {
                        strcpy(mail,"");
                        info->email_posn =0;
                        temploc=temploc + 30;
                    }
                    info->next =temploc + 30;
                    fwrite(info,sizeof(struct contact),1,ftemp);
                    fwrite(firstname,1,30,ftemp);
                    fwrite(lastname,1,30,ftemp);
                    fwrite(comp,1,30,ftemp);
                    fwrite(mail,1,30,ftemp);

                }
                else
                {
                    if(RecordData.first_name_posn !=0 )
                    {
                        fseek(file,RecordData.first_name_posn,SEEK_SET);
                        fread(firstname,sizeof(char),30,file);
                    }
                    else
                    {
                        strcpy(firstname,"");
                    }

                    if(RecordData.last_name_posn !=0 )
                    {
                        fseek(file,RecordData.last_name_posn,SEEK_SET);
                        fread(lastname,sizeof(char),30,file);

                    }
                   else
                   {
                       strcpy(lastname,"");

                    }
                    if(RecordData.company_name_posn !=0 )
                    {
                        fseek(file,RecordData.company_name_posn,SEEK_SET);
                        fread(comp,sizeof(char),30,file);

                    }
                    else
                    {
                        strcpy(comp,"");
                    }
                    if(RecordData.email_posn !=0 )
                    {
                        fseek(file,RecordData.email_posn,SEEK_SET);
                        fread(mail,sizeof(char),30,file);

                    }
                    else
                    {
                        strcpy(mail,"");
                    }

                    fwrite(&RecordData,sizeof(struct contact),1,ftemp);
                    fwrite(firstname,1,30,ftemp);
                    fwrite(lastname,1,30,ftemp);
                    fwrite(comp,1,30,ftemp);
                    fwrite(mail,1,30,ftemp);
                    }
                    fseek(file,RecordData.next,SEEK_SET);
                    last_next_pos=RecordData.next;

                }
                if(RecordData.next == endfile)
                {
                    break;
                }
                 }
                 fclose(file);
                 fclose(ftemp);
                 remove("myContactsList.db");
                 rename("Temp.db","myContactsList.db");
                 file = fopen("myContactsList.db","a+");
}
void edit_contact(long temp_phone)
{
    struct contact RecordData;
    FILE *file,*ftemp;
    file = fopen("myContactsList.db","a+");
    ftemp = fopen("Temp.db","w+");
    char *phone;
    char *email;
    char firstname[30];
    char lastname[30];
    char comp[30];
    char mail[30];
    fseek(file,0,SEEK_END);
    long  endfile = ftell(file);
    fseek(file,0,SEEK_SET);
    while(!feof(file))
    {
        fread(&RecordData, sizeof(struct contact),1,file);
        if(temp_phone == RecordData.phone_number)
        {
            if(RecordData.first_name_posn !=0 )
            {

                fseek(file,RecordData.first_name_posn,SEEK_SET);
                fread(firstname,sizeof(char),30,file);

            }
            else
            {
                strcpy(firstname,"");
            }

            if(RecordData.last_name_posn !=0 )
            {
                fseek(file,RecordData.last_name_posn,SEEK_SET);
                fread(lastname,sizeof(char),30,file);

            }
            else
            {
                strcpy(lastname,"");
            }
            if(RecordData.company_name_posn !=0 )
            {
                fseek(file,RecordData.company_name_posn,SEEK_SET);
                fread(comp,sizeof(char),30,file);

            }
            else
            {
                strcpy(comp,"");
            }

            printf("\nYou can just Edit  phone or Email \n(Note: if you left phone empty it will keep the old one, if you left mail empty it will clear its data) \n");

            do
            {
                printf("Phone Number (enter only numbers): ");
                phone = Enter_input();
                if(strlen(phone)==0) break;
            } while(check_phone_no(phone) != 0);

            do
            {
                printf("Email: ");
                email = Enter_input();
                if(strlen(email) ==0) break;
            }while(check_mail(email)==0 );

            if(strlen(phone)==0 )
            {
                 RecordData.phone_number = temp_phone;
            }
            else
            {
                RecordData.phone_number = strtol(phone, NULL,10);
            }


            fwrite(&RecordData,sizeof(struct contact),1,ftemp);
            fwrite(firstname,1,30,ftemp);
            fwrite(lastname,1,30,ftemp);
            fwrite(comp,1,30,ftemp);
            fwrite(email,1,30,ftemp);
            fseek(file,RecordData.next,SEEK_SET);

            }

           else
           {
               if(RecordData.first_name_posn !=0 )
               {
                   fseek(file,RecordData.first_name_posn,SEEK_SET);
                   fread(firstname,sizeof(char),30,file);
               }
               else
               {
                   strcpy(firstname,"");
               }

               if(RecordData.last_name_posn !=0 )
               {
                   fseek(file,RecordData.last_name_posn,SEEK_SET);
                   fread(lastname,sizeof(char),30,file);

               }
              else
              {
                  strcpy(lastname,"");

              }
              if(RecordData.company_name_posn !=0 )
              {
                  fseek(file,RecordData.company_name_posn,SEEK_SET);
                  fread(comp,sizeof(char),30,file);

              }
              else
              {
                  strcpy(comp,"");
              }

             if(RecordData.email_posn !=0 )
             {
                 fseek(file,RecordData.email_posn,SEEK_SET);
                 fread(mail,sizeof(char),30,file);

            }
            else{
                    strcpy(mail,"");
                }

                fwrite(&RecordData,sizeof(struct contact),1,ftemp);
                fwrite(firstname,1,30,ftemp);
                fwrite(lastname,1,30,ftemp);
                fwrite(comp,1,30,ftemp);
                fwrite(mail,1,30,ftemp);
                fseek(file,RecordData.next,SEEK_SET);
                }
                if(RecordData.next == endfile)
                {
                    break;
                }
            }
            fclose(file);
            fclose(ftemp);
            char *action;
           printf("\nActions:");
           printf("R-Return To main don't update contact list \nS- Save Contact and return to main\nD- Delete this contact \nSelect Action:");
          action=Enter_input();

          if(strcmp(action,"S")==0)
          {
              remove("myContactsList.db");
              rename("Temp.db","myContactsList.db");
              file = fopen("myContactsList.db","a+");
          }
          else if (strcmp(action,"D")==0)
          {
            delete_contact(temp_phone);
          }
          else
          {
             remove("Temp.db");
          }
          fclose(file);
}

int main()
{

   struct data mystruct[30];
   while(1)
   {
        printf("Number of contacts= ");
        int i=contacts_No();
        printf("%d\n",i);
        int listno= display_contacts(mystruct);
        int selectedNo;

        char *outerAction;
        printf("\nActions: ");
        outerAction=Enter_input();
        if(strcmp(outerAction,"A")==0){
            add_newcontact();}
        else if(strcmp(outerAction ,"X")==0){break;}
        else
        {
            selectedNo=atoi(outerAction);

            if(selectedNo >= 1 && selectedNo<= listno )
            {
              printf("\nContact# %d\n",selectedNo);
              show_contact(mystruct[selectedNo-1].phoneNo);

              char *contact_action;
              printf("\nActions:");
              printf("R- Return to main\nE- Edit this contact\nD- Delete this contact and return to main\nSelect Action:");
             contact_action=Enter_input();

            if(strcmp(contact_action ,"R")==0)
            {

              continue;
            }
            else if(strcmp(contact_action ,"E")==0)
            {

              edit_contact(mystruct[selectedNo-1].phoneNo);
            }
             else if(strcmp(contact_action ,"D")==0)
            {
              delete_contact(mystruct[selectedNo-1].phoneNo);
            }
          }
          else
          {
               continue;
          }

       }

   }
return 0;
}
