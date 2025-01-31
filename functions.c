#include "functions.h"

char playfield[H][W] =
        {
           { "############################################################" },
           { "#                                                          #" },
           { "#   ##################     ######    ###################   #" },
           { "#                  ####      ##     ####                   #" },
           { "#    ####   ###    ####      ##     ####    ###    ####    #" },
           { "#    ####   ###    ####    ######   ####    ###    ####    #" },
           { "#    ####                                          ####    #" },
           { "#     ##################     ##     ##################     #" },
           { "#                            ##                            #" },
           { "#   ###############   ###    ##    ###   ###############   #" },
           { "#   ###               ###          ###               ###   #" },
           { "#   ###  ###   ##########  ##  ##  ##########  ###   ###   #" },
           { "#   ###               ###          ###               ###   #" },
           { "#   ###############   ###  ##  ##  ###   ###############   #" },
           { "#                                                          #" },
           { "#   ####    ###   #######   #  #   #######   ###    ####   #" },
           { "#   ####    ###   #######   #  #   #######   ###    ####   #" },
           { "#   ####    ###       ###   #  #   ###       ###    ####   #" },
           { "#   ####                    #  #                    ####   #" },
           { "#   ####     ############          ############     ####   #" },
           { "#   ####     ###                            ###     ####   #" },
           { "#   ####     ###                            ###     ####   #" },
           { "#   ####     ##################################     ####   #" },
           { "#   ####                                            ####   #" },
           { "#   ####   #############     ##     #############   ####   #" },
           { "#   ####   #############     ##     #############   ####   #" },
           { "#   ####        ####         ##          ####       ####   #" },
           { "#               ####     ##########      ####              #" },
           { "#       ####             ##########             ####       #" },
           { "############################################################" }
        };
char player_name[MAX_CHAR];
int *px,*py;
int *gx,*gy;
int *score;
int *h_score;
const int lives=3;
int *final_lives;
int *flag;


void display();
void menu();
void signup();
void player_name_input();
void how_to_play();
void clear_scoreboard();
int login();
void game();
void scoreboard();
void score_input_to_scoreboard();
void rendermap();
void updatepacmanposition(int nx, int ny);
int allowedmove(int x, int y);
void updateghostposition();
void col_check();
void inputhandling();
int gameover();


void display(){
    int y;
    while(1){
        system("cls");
        printf("The Maze-Runner: Pac-Man\n\n\n");
        printf("1. Login\n");
        printf("2. Sign up\n");
        printf("3. Exit\n\n");
        printf("Sign up first if you are not logged in\n");
        printf("Enter your choice: ");
        scanf("%d",&y);
        switch(y){
            case 1:
                if(login()){
                    menu();
                    break;
                }
                else{
                    Sleep(2000);
                    break;
                }
            case 2:
                signup();
                break;
            case 3:
                exit(0);
            default:
                printf("Invalid choice!...\n");
                Sleep(2000);
                break;
        }
    }
}

void menu(){
    int x;
    while(1){
        system("cls");
        printf("The Maze-Runner: Pac-Man\n\n\n");
        printf("1. Start Game\n");
        printf("2. View Scoreboard\n");
        printf("3. Logout\n");
        printf("4. How to play?\n");
        printf("5. Exit\n\n\n");
        printf("Enter your choice: ");
        scanf("%d",&x);
        switch(x){
        case 1:
            player_name_input();
            game();
            break;
        case 2:
            scoreboard();
            break;
        case 3:
            display();
            break;
        case 4:
            how_to_play();
            break;
        case 5:
            exit(0);
        default:
            printf("Invalid choice!...\n");
            Sleep(2000);
            break;
        }
    }
}
void player_name_input(){
    FILE *file1=fopen("scoreboard.txt","a");
    fprintf(file1,"%s ",player_name);
    fclose(file1);
}

void signup(){
        system("cls");
        FILE *sign_up=fopen("users.txt","a");
        if(sign_up==NULL){
            printf("Sorry! Can't sign up right now...");
            return;
        }
        char uname[MAX_CHAR],pword[MAX_CHAR];
        printf("Enter username: ");
        scanf("%s",uname);
        printf("Enter password: ");
        char pass;
        int j=0;
        while((pass=getch())!='\r'){
            if(pass==8){
                if(j>0){
                    j--;
                    printf("\b \b");
                }
            }
            else{
                pword[j]=pass;
                j++;
                printf("*");
            }
        }
        pword[j]='\0';
        printf("\n");
        fprintf(sign_up,"%s %s\n",uname,pword);
        fclose(sign_up);
        printf("Successfully signed up!...\n");
        printf("Press any key to return to the login page...");
        getch();
}

int login(){
    system("cls");
    char password[MAX_CHAR],pass;
    printf("Enter your username: ");
    scanf("%s",player_name);
    printf("Enter your password: ");
    int j=0;
    while((pass=getch())!='\r') {
        if(pass==8){
            if(j>0){
                j--;
                printf("\b \b");
            }
        }
        else{
            password[j]=pass;
            printf("*");
            j++;
        }
    }
    password[j] ='\0';
    printf("\n");
    FILE *loginFile=fopen("users.txt","r");
    if(loginFile==NULL){
        printf("Sorry! Can't login right now...\n");
        return 0;
    }
    char fileUsername[MAX_CHAR],filePassword[MAX_CHAR];
    while(fscanf(loginFile,"%s %s",fileUsername,filePassword)!=EOF){
        if(strcmp(player_name,fileUsername)==0 && strcmp(password,filePassword)==0){
            fclose(loginFile);
            return 1;
        }
    }

    fclose(loginFile);
    printf("Wrong username or password!\n");
    return 0;
}

void how_to_play(){
    system("cls");
    printf("The Maze-Runner: Pac-Man\n\n\n");
    printf("Press 'W' or 'w' to move upward\n");
    printf("Press 'S' or 's' to move downward\n");
    printf("Press 'A' or 'a' to move left\n");
    printf("Press 'D' or 'd' to move right\n");
    printf("Press 'Q' or 'q' to quit\n\n\n");
    printf("Press enter to return to menu...\n");
    getch();
}

void game(){
    for(int i=0;i<H;i++){
        for(int j=0;j<W;j++){
            if(playfield[i][j]!='#'){
                playfield[i][j]='.';
            }
        }
    }
    *px=W/2;
    *py=H/2;
    playfield[*py][*px]='P';
    for(int i=0;i<G_CNT;i++){
        do{
            *(gx+i)=rand()%(W-1);
            *(gy+i)=rand()%(H-1);
        }while(playfield[*(gy+i)][*(gx+i)]!='.');
        playfield[*(gy+i)][*(gx+i)]='G';
    }
    *flag=1;
    int g_speed_counter=0;
    while(*flag){
        rendermap();
        inputhandling();
        if(g_speed_counter%3==0){
            updateghostposition();
        }
        col_check();
        g_speed_counter++;
        if(gameover()){
            FILE *file2=fopen("scoreboard.txt","a");
            fprintf(file2,"%d\n",*score);
            fclose(file2);
            FILE *fp1=fopen("highscore.txt","r");
            fscanf(fp1,"%d",h_score);
            fclose(fp1);
            if(*score>*h_score) {
                *h_score=*score;
                fp1=fopen("highscore.txt","w");
                fprintf(fp1,"%d",*h_score);
                fclose(fp1);
            }
            system("cls");
            printf("Game Over!\n");
            printf("Final Score: %d\n", *score);
            printf("High Score: %d\n", *h_score);
            printf("Press any key to return to menu...");
            getch();
            *final_lives=lives;
            *score=0;
            menu();
        }
        Sleep(100);
    }
}

void scoreboard(){
    system("cls");
    struct player_out{
        char name[MAX_CHAR];
        int sc;
    };
    FILE *chk_scbrd=fopen("scoreboard.txt","r");
    if(chk_scbrd==NULL){
        printf("Sorry! Can't show the scoreboard right now...\n");
        return;
    }
    struct player_out p[MAX_PLAYERS];
    int cnt=0;
    for(int i=0;i<MAX_PLAYERS;i++){
        if(fscanf(chk_scbrd,"%s %d",p[i].name,&p[i].sc)!=2){
            break;
        }
        else{
            cnt++;
        }
    }
    fclose(chk_scbrd);
    struct player_out temp;
    for(int i=0;i<cnt-1;i++){
        for(int j=i+1;j<cnt;j++){
            if(p[i].sc<p[j].sc){
                temp=p[i];
                p[i]=p[j];
                p[j]=temp;
            }
        }
    }
    printf("Player\t\t\tScore\n");
    printf("------\t\t\t-----\n\n");
    for(int i=0;i<cnt;i++){
        printf("%s\t\t\t%d\n",p[i].name,p[i].sc);
    }
    printf("\n");
    printf("1. Return to menu\n");
    printf("2. Clear scoreboard\n");
    int z,i;
    printf("Enter your choice: ");
    scanf("%d",&z);
    switch(z){
    case 1:
        system("cls");
        printf("Press any key to return to menu...\n");
        getch();
        return;
    case 2:
        system("cls");
        printf("Do you want to clear the scoreboard?\n");
        printf("1. Yes\n");
        printf("2. No\n");
        printf("Enter your choice: ");
        scanf("%d",&i);
        if(i==1){
            clear_scoreboard();
            printf("Scoreboard cleared!\n");
            printf("Press any key to return to menu...\n");
            getch();
            return;
        }
        else if(i==2){
            printf("Press any key to return to menu...\n");
            getch();
            return;
        }
        else{
            printf("Invalid choice!\n");
            printf("Press any key to return to menu...\n");
            getch();
            return;
        }
    default:
        printf("Invalid choice!\n");
        printf("Press any key to return to menu...\n");
        getch();
        return;
    }
}
void clear_scoreboard(){
    FILE *file_clear1=fopen("scoreboard.txt","w");
    fclose(file_clear1);
    FILE *file_clear2=fopen("highscore.txt","w");
    fprintf(file_clear2,"%d",0);
    fclose(file_clear2);
}

void rendermap(){
    COORD cursorpos={0,0};
    SetConsoleCursorPosition(GetStdHandle(STD_OUTPUT_HANDLE), cursorpos);
    for(int i=0;i<H;i++){
        for(int j=0;j<W;j++){
            printf("%c",playfield[i][j]);
        }
        printf("\n");
    }
    printf("Score: %d\nLives: %d\n",*score,*final_lives);
    printf("Press 'Q' or 'q' to quit the game...\n");
}

void updatepacmanposition(int nx,int ny){
    if(playfield[ny][nx]!='#' && playfield[ny][nx]!='G'){
        if(playfield[ny][nx]=='.'){
            (*score)++;
        }
        playfield[*py][*px]=' ';
        *px=nx;
        *py=ny;
        playfield[*py][*px]='P';
    }
}

int allowedmove(int x,int y){
    return playfield[y][x]!='#' && playfield[y][x]!='G';
}

void updateghostposition(){
    for(int i=0;i<G_CNT;i++){
        playfield[*(gy+i)][*(gx+i)]='.';
        int dx,dy,nx,ny;
        dx=*px-*(gx+i);
        dy=*py-*(gy+i);
        nx=*(gx+i);
        ny=*(gy+i);
        if(abs(dx)>abs(dy)){
            nx+=(dx>0)?1:-1;
            if(!allowedmove(nx,*(gy+i))){
                nx=*(gx+i);
                ny+=(dy>0)?1:-1;
            }
        }
        else{
            ny+=(dy>0)?1:-1;
            if(!allowedmove(*(gx+i),ny)){
                ny=*(gy+i);
                nx+=(dx>0)?1:-1;
            }
        }
        *(gx+i)=nx;
        *(gy+i)=ny;
        playfield[*(gy+i)][*(gx+i)]='G';
    }
}

void col_check(){
    for(int i=0;i<G_CNT;i++){
        if(*px==*(gx+i) && *py==*(gy+i)){
            (*final_lives)--;
            if(gameover()){
                return;
            }
            Sleep(500);
            game();
            return;
        }
    }
}

void inputhandling(){
    if (_kbhit()){
        switch(tolower(_getch())){
            case 'w':
                updatepacmanposition(*px,*py-1);
                break;
            case 's':
                updatepacmanposition(*px,*py+1);
                break;
            case 'a':
                updatepacmanposition(*px-1,*py);
                break;
            case 'd':
                updatepacmanposition(*px+1,*py);
                break;
            case 'q':
                score_input_to_scoreboard();
                *flag=0;
                break;
        }
    }
}

void score_input_to_scoreboard(){
    FILE *fp2=fopen("highscore.txt","r");
    fscanf(fp2,"%d",h_score);
    fclose(fp2);
    if(*score>*h_score){
        *h_score=*score;
        fp2=fopen("highscore.txt","w");
        fprintf(fp2,"%d",*h_score);
        fclose(fp2);
    }
    FILE *game_quit=fopen("scoreboard.txt","a");
    fprintf(game_quit,"%d\n",*score);
    fclose(game_quit);
    *score=0;
    *final_lives=lives;
}

int gameover(){
    if(*final_lives<=0){
        return 1;
    }
    return 0;
}
