/**
 * This file contains the menu and main class for the game.
 * @author Rui Couto
 */
#include "hd.h"

/**
 * Function which handles the login
 */
int login() {
    char nomeint[tm],nomefic[tm],passint[tm],passfic[tm],sair=0,op;
    int a = (LINES/2),b = (COLS/2);
    FILE *reg;
    reg = fopen("regs.txt","a+");
    while(sair == 0) {
        mvprintw(a-2, b-11, "+------|Login:|------+"); 
        mvprintw(a-1, b-11, "| Nome:_____________ |");
        mvprintw(a, b-11,   "| Password:_________ |");
        mvprintw(a+1, b-11, "+--------------------+");

        echo();
        mvscanw(a-1,b-4,"%s",nomeint);
        noecho();
        mvscanw(a,b,"%s",passint);

        while (fscanf(reg,"%s %s",nomefic,passfic)!=EOF) {
            if ((strcmp(nomeint, nomefic) != 0) || (strcmp(passint, passfic)!=0)) {
                ;
            } else {
                attron(COLOR_PAIR(2));
                mvprintw(a+2, b-11, ">Login realizado com sucesso!");
                mvprintw(a+3, b-11, "Bem vindo, %s.",nomeint);
                fprintf(reg,"%s %s\n",nomeint,passint);
                getch();
                attron(COLOR_PAIR(1));
                return(1);
            };
        };
        attron(COLOR_PAIR(3));
        mvprintw(a+2, b-11, ">Login inválido. Sair (s/n)?");
        op=getch();
        attron(COLOR_PAIR(1));
        switch(op) {
            case 's' : {
                sair = 1;
            }; break;
            case 'n' : {
                sair = 0;
            };break;
            default : {;}; break;
        };
    };
    return(0);
}

/**
 * Function which handles the register of a new user
 */
int registo() {
    char n[tm], p[tm];
    int a = (LINES/2),b = (COLS/2);
    FILE *reg;
    reg = fopen("regs.txt","a");
    mvprintw(a-2, b-11, "+-----|Registo:|-----+"); 
    mvprintw(a-1, b-11, "| Nome:_____________ |");
    mvprintw(a, b-11,   "| Password:_________ |");
    mvprintw(a+1, b-11, "+--------------------+");
    echo();
    mvscanw(a-1,b-4,"%s",n);
    noecho();
    mvscanw(a,b,"%s",p);
    fprintf(reg,"%s %s\n",n,p);
    fclose(reg);
    return(1);
}

/**
 * Function to display wellcome message
 */
int wlc() {
    int a = (LINES/2),b = (COLS/2);
    nodelay(stdscr,TRUE);
    while(getch()!=10) {
        mvprintw(a-3, b-15, "+~~~~~~~~~~~~~~~~~~~~~~~~~~~~+"); 
        mvprintw(a-2, b-15, "| Bem vindo a arca de jogos  |");
        mvprintw(a-1, b-15,   "| PI_0607, grupo 80!         |");
        mvprintw(a, b-15,   "| (Prima a tecla 'enter'     |");
        mvprintw(a+1, b-15,   "|  para continuar      )     |");
        mvprintw(a+2, b-15, "+~~~~~~~~~~~~~~~~~~~~~~~~~~~~+");
    };
    nodelay(stdscr,FALSE);
    clear();
    return(0);
}

/**
 * Displays the main menu
 */
int entrar() {
    int c=0,a = (LINES/2),b = (COLS/2),o=2,x= (LINES/2);
    wlc();
    mvprintw(a-2, b-7, "+------------+"); 
    mvprintw(a-1, b-7, "| >  Login   |");
    mvprintw(a, b-7,   "| >  Registo |");
    mvprintw(a+1, b-7, "+------------+");
    while(o == 2) {
        mvprintw(x-1, b-5, "");
        switch(getch()) {
            case (KEY_UP) : {
                if (x==(a+1)) {
                    x--;
                };
            };break;
            case (KEY_DOWN):{
                if (x==(a)) {
                    x++;
                };
            };break;
            case 10 : {
                if (x == a) {
                    o = 0;
                } 
	            else {
                    o = 1;
                };
            };break;
            default : {;};break;
        }
    };

    switch(o) {
        case 0 : {
            c=login();
        };break;
        case 1 : {
            c=registo();
        };break;
    };
    return(c);
}

/**
 * Displays the menu to select the game
 */
int menu() {
    int a = (LINES/2),b = (COLS/2),o=7,x= (LINES/2);
    clear();
    mvprintw(a-5, b-11, "+--------------------+"); 
    mvprintw(a-4, b-11, "| Jogos:             |");
    mvprintw(a-3, b-11, "|                    |");
    mvprintw(a-2, b-11, "| >  Jogo da forca   |");
    mvprintw(a-1, b-11, "| >  Minesweeper     |");
    mvprintw(a  , b-11, "| >  Spite and Malice|");
    mvprintw(a+1, b-11, "| >  Sair            |");
    mvprintw(a+2, b-11, "+--------------------+");

    while(o == 7) {
        mvprintw(x-2, b-9, "");

        switch(getch()) {
            case (KEY_UP) : {
                if (x>=(a+1)) {
                    x--;
                };
                refresh();
            };break;
            case (KEY_DOWN):{
                if (x<=(a+2)) {
                    x++;
                };
                refresh();
            };break;
            case 10 : {
                if (x == a) {
                    forca();
                    clear();
                    menu();
                }
		        if (x == (a+1)) {
                    mines(0,NULL);
                    clear();
                    menu();
                }
		        if (x == (a+2)) {
                    spitm();
                    clear();
                    menu();
                }
		        if (x == (a+3)) {
                    o=0;
                }
            };break;
            default : {;};break;
        };
    };
    return(0);
}

/**
 * The main function.
 * initialized the ncurses and shows the menu
 */
int main() {
    int c=1;

    initscr();
    cbreak();
    keypad(stdscr,TRUE);
    noecho();
    start_color();

    init_pair(1,COLOR_BLACK,COLOR_WHITE);
    init_pair(2,COLOR_GREEN,COLOR_WHITE);
    init_pair(3,COLOR_RED,COLOR_WHITE);
    bkgd(COLOR_PAIR(1));

    // start
    c = entrar();
    while (c == 1) {
        c = menu();
    };

    // end
    endwin();
    printf("terminado\n");
    return(0);
}
