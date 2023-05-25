#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <ctype.h>

typedef struct song_tag {         //initialize structure
char title [20];
char artist [20];
char album [20];
struct song_tag * nextSong ;
} song ;


typedef struct playlist_tag {
char name [50];
int songCount ;
song * songHead ;
struct playlist_tag * next ;
} playlist ;


void saveplaylist(playlist *head, int count){ // function for saving playlist
    FILE *fp=fopen("Playlist.txt","w");
    playlist *temp=head;
        fprintf(fp,"%d\n",count);
        for(playlist *temp=head;temp!=NULL;temp=temp->next){    //loops throught the lists and the songs in the lists then saves to file
        fprintf(fp,"%s\n",temp->name);
        fprintf(fp,"%d\n",temp->songCount);
            for (song *temp2=temp->songHead;temp2!=NULL;temp2=temp2->nextSong){
            fprintf(fp,"%s\n",temp2->title);
            fprintf(fp,"%s\n",temp2->artist);
            fprintf(fp,"%s\n",temp2->album);
            }
    }
    printf("Successfully saved data\n");
    fclose(fp);
}


void loadPlaylist(playlist **head,int *count){   //function for loading playlist
    int i=0,j;
    FILE *fp=fopen("Playlist.txt","r");
    fscanf(fp," %d\n",count);
    for( playlist *temp=*head;i<*count;i++){
        playlist *new=(playlist*)malloc(sizeof(playlist));  //initialize new pointer so its not pointing to null
        fgets((new->name),50,fp);
        new->name[strcspn(new->name, "\n")] = 0;
        fscanf(fp," %d\n",&(new->songCount));            //scans the contents of the file and adds them to their respective list address
        if (*head==NULL){
             new->next=*head;
            *head=new;
        }else{
             playlist *temp=*head;
            while(temp!=NULL){
            temp=temp->next;
            }
            temp=*head;
            while(temp->next!=NULL){
                temp=temp->next;
            }new->next=temp->next;(temp->next)=new;
        }j=0;
            for(song *temp2=(new->songHead);j<new->songCount;j++){             //use loops to traverse each playlist and song to find where to load the data
                song *new2=(song*)(malloc(sizeof(song)));
                fgets((new2->title),20,fp);
                new2->title[strcspn(new2->title, "\n")] = 0;
                fgets((new2->artist),20,fp);
                new2->artist[strcspn(new2->artist, "\n")] = 0;
                fgets((new2->album),20,fp);
                new2->album[strcspn(new2->album, "\n")] = 0;

                if (new->songHead==NULL){
                     new2->nextSong=new->songHead;   //function for adding lists
                     new->songHead=new2;
                }else{
                    song *temp2=new->songHead;
                    while(temp2!=NULL){
                    temp2=temp2->nextSong;
                    }
                    temp2=new->songHead;
                    while(temp2->nextSong!=NULL){
                        temp2=temp2->nextSong;
                    }new2->nextSong=temp2->nextSong;(temp2->nextSong)=new2;    
                }
                
            }
        

        
    }

    printf("Successfully loaded data\n");
    fclose(fp);
}

void freeHeap(playlist**head){     //function for freeing dynamic memory
    if (*head==NULL)return;
    while(*head!=NULL){
        playlist *temp=*head;
        while(temp->songHead!=NULL){
            song *temp2=temp->songHead;
            temp2=temp2->nextSong;
            free(temp2);
        }
        temp=temp->next;
        free(temp);
    }
}

void addPlaylist(playlist **head){  //function for adding playlists
    int count;   
    playlist *new=(playlist*)malloc(sizeof(playlist));
    printf("Enter playlist name: ");
    scanf(" %[^\n]", new->name);
    if (*head==NULL||*head!=NULL&&strcmp((new->name),((*head)->name))<0){          //adds alphabetically using strcmp value               
        new->next=*head;            //adds at head
        *head=new;
    }else{
        playlist *temp=*head;
        while(temp!=NULL){
            if(strcmp((new->name),(temp->name))==0){printf("Name already added\n");free(new);return ;} //checks if name is already added
            temp=temp->next;                                                                                
        }
        temp=*head;
        while(temp->next!=NULL&&strcmp((new->name),(temp->next->name))>0){  //ads at tail and middle
            temp=temp->next;
        }new->next=temp->next;(temp->next)=new;
    }
    printf("Playlist added\n");
}   

int Addsong( song **songHead, int song_counter){                 //function for adding a song
    song *new=(song*)malloc(sizeof(song));
    printf("Enter Song title: ");
    scanf(" %[^\n]", new->title);
    printf("Enter Song artist: ");
    scanf(" %[^\n]", new->artist);
    printf("Enter Song album: ");                        
    scanf(" %[^\n]", new->album);
    if (*songHead==NULL||*songHead!=NULL&&strcmp((new->title),((*songHead)->title))<0){   //adds alphabetically using strcmp value   
        new->nextSong=*songHead;
        *songHead=new;
    }else{
        song *temp2=*songHead;
        while(temp2->nextSong!=NULL&&strcmp((new->title),((temp2->nextSong)->title))>0){
            temp2=temp2->nextSong;
        }new->nextSong=temp2->nextSong;
        (temp2->nextSong)=new;
    }
    printf("Song added\n");
    song *temp3=*songHead;
    for(temp3=*songHead;temp3!=NULL;temp3=temp3->nextSong){
        song_counter=song_counter+1; //adds song counter
    }
    return song_counter;
}


void choosePlaylist_add(playlist **head){                                 //function to choose which playlist to add song to
    char x[50];
    int song_counter=0;
    if(*head==NULL){printf("No playlist yet\n");}
    else{printf("PLAYLISTS\n");
        for(playlist *temp=*head;temp!=NULL;temp=temp->next){
            printf("%s\n\n",temp->name);
        }
        printf("Enter playlist name: ");
        scanf(" %[^\n]", x);
        playlist *temp=*head;
        for(playlist *temp=*head;temp!=NULL;temp=temp->next){
                if(strcmp((x),(temp->name))==0){
                    song *songHead=NULL;
                    temp->songCount=Addsong(&(temp->songHead),song_counter);//adds song to the current playlist chosen
                    return;
                }
            }
        printf("Playlist not found!\n");
        }
}


void printSong(song *songHead){
    while (songHead!=NULL){                                 //prints playlist songs using for loops
        if (songHead->nextSong==NULL){
            printf("Song Title: %s\n",songHead->title);
            printf("Song Artist: %s\n",songHead->artist);
            printf("Song Album: %s\n\n",songHead->album);
            return;
        } else{
            printf("Song Title: %s\n",songHead->title);
            printf("Song Artist: %s\n",songHead->artist);
            printf("Song Album: %s\n\n",songHead->album);
        }
        songHead=songHead->nextSong;
    }

}

void printAll(playlist *head){                                    
    if(head==NULL){printf("No playlist yet\n");}
    else{printf("PLAYLISTS\n");
        for(playlist *temp=head;temp!=NULL;temp=temp->next){    //prints playlist content and song content
            printf("Playlist Name:%s\n\n",temp->name);
            printf("Song count:%d\n\n",temp->songCount);
            printSong(temp->songHead);                //print song function is called here
            }
        }
}

void viewPlaylist(playlist *head){                                            
    char x[50];
    if(head==NULL){printf("No playlist yet\n");}
    else{printf("PLEASE CHOOSE A PLAYLISTS\n");
        for(playlist *temp=head;temp!=NULL;temp=temp->next){          //prints a menu of playlists
            printf("Playlist Name:%s\n\n",temp->name);     
            }
        }
        printf("Enter playlist name here: ");
        scanf(" %[^\n]", x);
        for(playlist *temp=head;temp!=NULL;temp=temp->next){              //adds song to chosn playlist
            if (strcmp(x,temp->name)==0){
                printf("song count:%d\n",temp->songCount);
                printSong(temp->songHead);
                return;
            }  
        }
        printf("SONG NOT FOUND\n");

}


void deleteSong (song **songHead,playlist *temp_playlist){          //function to delete song
    char x[50];
    if (*songHead==NULL)printf("PLAYLIST IS EMPTY\n");
    else{
        printSong(*songHead);
        printf("Enter song title to delete: ");
        scanf(" %[^\n]", x);
        song *del=*songHead;
        while(del!=NULL){
            if(strcmp(del->title,x)==0)break;                   //checks if del is pointing to the same song to be deleted
            del=del->nextSong;
        }
        if (del==NULL)printf("Song not found\n");
        else{
            if (del==*songHead){                               
                *songHead=(*songHead)->nextSong;                    //deletes at head
                free(del);
                printf("Successfully deleted\n");
                temp_playlist->songCount=(temp_playlist->songCount)-1;
            }
            else{
                song *temp=*songHead;                           
                while(temp->nextSong!=del){
                    temp=temp->nextSong;
                }
                temp->nextSong=del->nextSong;                     //deletes at tail or middle
                free(del);
                printf("Successfully deleted\n");
                temp_playlist->songCount=(temp_playlist->songCount)-1; //reduces playlist count
                
                

            }
        }
    }
}

void choosePlaylist_delete(playlist **head){               //function for choosing playlist to delete
    char x[50];
    if(*head==NULL){printf("No playlist yet\n");}
    else{printf("PLAYLISTS\n");
        for(playlist *temp=*head;temp!=NULL;temp=temp->next){
            printf("%s\n\n",temp->name);
        }
        printf("Enter playlist name: ");
        scanf(" %[^\n]", x);
        playlist *temp=*head;
        for(playlist *temp=*head;temp!=NULL;temp=temp->next){
                if(strcmp((x),(temp->name))==0){
                    song *songHead=NULL;
                    deleteSong(&(temp->songHead),temp); //deleteSong function is called here
                    return;
                }
            }
        printf("Playlist not found!\n");
        }
    }

int main(){     //main function
    int choice,count=0;
    struct playlist_tag *head=NULL; 
     FILE *file;
    if (file = fopen("Playlist.txt", "r")){loadPlaylist(&head,&count);}//checks if file is opened before loading
    while(1){                                                           //while loop to continuously run the program unless terminated
        printf("[1] Add playlist\n");
        printf("[2] Add song to playlist\n");
        printf("[3] Remove song from playlist\n");
        printf("[4] View a playlist\n");
        printf("[5] View all data\n");
        printf("[6] Exit\n");
        
        printf("Enter choice: ");
        scanf("%d", &choice);
        if (choice==1){                      //conditional statments based on scanned choice
            addPlaylist(&head);

            count++;
        }
        else if (choice==2){
            choosePlaylist_add(&head);
        }
        else if (choice==3){
            choosePlaylist_delete(&head);
        }
        else if(choice==4){
            viewPlaylist(head);
        }
        else if(choice==5){
            printAll(head);
        }    
        else if(choice==6){
            saveplaylist(head,count);
            printf("PROGRAM TERMINATED\n");
            freeHeap(&head);                        //save and free the dynamic memory once exit is chosen
            break;
        }
        else printf("INVALID CHOICE\n");
        
            
    
            
        

    }
}