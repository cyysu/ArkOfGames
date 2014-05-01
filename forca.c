/**
 * Hangman game. 
 * This file has the implementation of the hangman game in C, 
 * resorting to ncurses
 * @author Rui Couto
 */

#define tm 20  //
#define max 20 //


/**
 * Show the menu to select the difficult.
 * @return The difficulty leve (1 easy to 3 hard)
 */
int dif() {
    int o=0, tent=0,a = (LINES/2),b = (COLS/2),x= (LINES/2)/*,y= (COLS/2)*/;
    clear();

    mvprintw(a-3, b-8, "+--------------+"); 
    mvprintw(a-2, b-8, "| >  Fácil     |");
    mvprintw(a-1, b-8, "| >  Médio     |");
    mvprintw(a, b-8,   "| >  Dificil   |");
    mvprintw(a+1, b-8, "+--------------+");

    while(o == 0) {
        mvprintw(x-1, b-6, "");

        switch(getch()) {
            case (KEY_UP) : {if ( x >= a) {x--;};};
            break;
            case (KEY_DOWN):{if (x <= a) {x++;};};
            break;
            case 10 : {if (x == (a-1)) {o = 1;} 
                if (x == (a)) {o = 2;} 
                if (x == (a+1)) {o = 3;} 
            };
            break;
            default : {;};
            break;
        };
    };
    switch(o) {
        case 1: {tent=10;};break;
        case 2: {(tent=6);};break;
        case 3: {(tent=4);};break;
	};
    return(tent);
}

/**
 * Start a new game, and select number of players.
 */
int njog() {
    int o=0,a = (LINES/2),b = (COLS/2),x= (LINES/2)/*,y= (COLS/2)*/;

    nodelay(stdscr,TRUE);
    while(getch()!=10){
        mvprintw(a-3, b-15, "+~~~~~~~~~~~~~~~~~~~~~~~~~~~~+"); 
        mvprintw(a-2, b-15, "| Jogo da Forca!             |");
        mvprintw(a-1, b-15, "| Parte do projecto          |");
        mvprintw(a, b-15,   "| PI_0607, grupo 80!         |");
        mvprintw(a+1, b-15, "|           (Prima enter     |");
        mvprintw(a+2,b-15,  "|            para continuar) |");
        mvprintw(a+3, b-15, "+~~~~~~~~~~~~~~~~~~~~~~~~~~~~+");
    };
    nodelay(stdscr,FALSE);
    clear();

    mvprintw(a-2, b-8, "+--------------+"); 
    mvprintw(a-1, b-8, "|>1  Jogador   |");
    mvprintw(a, b-8,   "|>2  Jogadores |");
    mvprintw(a+1, b-8, "+--------------+");

    while(o == 0) {
        mvprintw(x-1, b-7, "");
        switch(getch()) {
            case (KEY_UP) : {if (x==(a+1)) {x--;};};break;
            case (KEY_DOWN):{if (x==(a)) {x++;};};break;
            case 10 : {if (x == a)     {o=1;};
                if (x == (a+1)) {o=2;};
            };break;
            default : {;};break;
        };
    };

    switch(o){
	    case 1: {return(1);};break;
        case 2: {return(2);};break;
	};
    return(0);
}

/**
 * Select the game vategory.
 * @return the line of the word to play
 */
int escat() {
    int o=0,rn,cat=10,a = (LINES/2),b = (COLS/2),x= (LINES/2)/*,y= (COLS/2)*/;
    srand(time(NULL));
    rn = rand() % cat;

    mvprintw(a-3, b-8, "+--------------+"); 
    mvprintw(a-2, b-8, "| >  Animais   |");
    mvprintw(a-1, b-8, "| >  Grupos    |");
    mvprintw(a, b-8,   "| >  Verbos    |");
    mvprintw(a+1, b-8, "| >  Adjectivos|");
    mvprintw(a+2, b-8, "| >  Sair      |");
    mvprintw(a+3, b-8, "+--------------+");

    while(o == 0){
        mvprintw(x-1, b-6, "");

        switch(getch()) {
            case (KEY_UP) : {if ( x >= (a)) {x--;};};break;
            case (KEY_DOWN):{if (x <= (a+2)) {x++;};};break;
            case 10 : {if (x == (a-1)) {o = 1;}; 
                if (x == (a))   {o = 2;};
                if (x == (a+1)) {o = 3;};
                if (x == (a+2)) {o = 4;};
                if (x == (a+3)) {o = 5;};
            };
            break;
            default : {;};break;
        };
    };

    switch(o) {
        case 1: {;};break;
        case 2: {(rn=rn+10);};break;
        case 3: {(rn=rn+20);};break;
        case 4: {(rn=rn+30);};break;
        case 5: {(rn = -1);};break;
	};
    clear();
    return(rn);
}

/**
 * Print the current status of the game.
 * Includes the work, number of tries and hangman picture.
 *
 */
int stat(int tent, char s1[max],char s2[max]){
    clear();
    char pos = 'a';
    int ip=0/*,a = (LINES/2),b = (COLS/2)*/;
    while(pos != '\0') {
        if (s2[ip] == '-') {
            mvprintw(1,ip, "-");ip ++;pos = s1[ip];
        }
		else {
            mvprintw(1,ip, "%c",s2[ip]);ip++;pos = s1[ip];
        };
	};

    mvprintw(2,0, "%d tentativas.",tent);

	if (tent==10) {	
        mvprintw(0,20, "+");
		mvprintw(1,20, "|+");
		mvprintw(2,20, "||");
		mvprintw(3,20, "||");
		mvprintw(4,20, "||");
		mvprintw(5,20, "||");
		mvprintw(6,20, "||");
		mvprintw(7,20, "||");
		mvprintw(8,20, "||");
		mvprintw(9,20, "||");
		mvprintw(10,20,"||");
		mvprintw(11,20,"##");}
	else {;};

	if (tent==9) {  
        mvprintw(0,20, "+~~~~~~~~~~~~~~~+");
		mvprintw(1,20, "|+");
		mvprintw(2,20, "||");
		mvprintw(3,20, "||");
		mvprintw(4,20, "||");
		mvprintw(5,20, "||");
		mvprintw(6,20, "||");
		mvprintw(7,20, "||");
		mvprintw(8,20, "||");
		mvprintw(9,20, "||");
		mvprintw(10,20,"||");
		mvprintw(11,20,"##");}
	else {;};

	if (tent==8) {  
        mvprintw(0,20, "+~~~~~~~~~~~~~~~+");
		mvprintw(1,20, "|+~~~~~~~+~~~~~~+");
		mvprintw(2,20, "||");
		mvprintw(3,20, "||");
		mvprintw(4,20, "||");
		mvprintw(5,20, "||");
		mvprintw(6,20, "||");
		mvprintw(7,20, "||");
		mvprintw(8,20, "||");
		mvprintw(9,20, "||");
		mvprintw(10,20,"||");
		mvprintw(11,20,"##");}
	else {;};

	if (tent==7) {
        mvprintw(0,20, "+~~~~~~~~~~~~~~~+");
        mvprintw(1,20, "|+~~~~~~~+~~~~~~+");
        mvprintw(2,20, "||       |");
        mvprintw(3,20, "||");
        mvprintw(4,20, "||");
        mvprintw(5,20, "||");
        mvprintw(6,20, "||");
        mvprintw(7,20, "||");
        mvprintw(8,20, "||");
        mvprintw(9,20, "||");
        mvprintw(10,20, "||");
        mvprintw(11,20, "##");}
	else {;};

	if (tent==6) {
        mvprintw(0,20, "+~~~~~~~~~~~~~~~+");
        mvprintw(1,20, "|+~~~~~~~+~~~~~~+");
        mvprintw(2,20, "||       |");
        mvprintw(3,20, "||      (oo)");
        mvprintw(4,20, "||");
        mvprintw(5,20, "||");
        mvprintw(6,20, "||");
        mvprintw(7,20, "||");
        mvprintw(8,20, "||");
        mvprintw(9,20, "||");
        mvprintw(10,20, "||");
        mvprintw(11,20, "##");}
	else {;};

	if (tent==5) {
        mvprintw(0,20, "+~~~~~~~~~~~~~~~+");
        mvprintw(1,20, "|+~~~~~~~+~~~~~~+");
        mvprintw(2,20, "||       |");
        mvprintw(3,20, "||      (oo)");
        mvprintw(4,20, "||    ---+---");
        mvprintw(5,20, "||");
        mvprintw(6,20, "||");
        mvprintw(7,20, "||");
        mvprintw(8,20, "||");
        mvprintw(9,20, "||");
        mvprintw(10,20, "||");
        mvprintw(11,20, "##");}
	else {;};

	if (tent==4) {  
        mvprintw(0,20, "+~~~~~~~~~~~~~~~+");
		mvprintw(1,20, "|+~~~~~~~+~~~~~~+");
		mvprintw(2,20, "||       |");
		mvprintw(3,20, "||      (oo)");
		mvprintw(4,20, "||    ---+---");
		mvprintw(5,20, "||       |");
		mvprintw(6,20, "||");
		mvprintw(7,20, "||");
		mvprintw(8,20, "||");
		mvprintw(9,20, "||");
		mvprintw(10,20,"||");
		mvprintw(11,20,"##");}
	else {;};

	if (tent==3) {  
        mvprintw(0,20, "+~~~~~~~~~~~~~~~+");
		mvprintw(1,20, "|+~~~~~~~+~~~~~~+");
		mvprintw(2,20, "||       |");
		mvprintw(3,20, "||      (oo)");
		mvprintw(4,20, "||    ---+---");
		mvprintw(5,20, "||       |");
		mvprintw(6,20, "||       |");
		mvprintw(7,20, "||");
		mvprintw(8,20, "||");
		mvprintw(9,20, "||");
		mvprintw(10,20,"||");
		mvprintw(11,20,"##");}
	else {;};

	if (tent==2) {
        mvprintw(0,20, "+~~~~~~~~~~~~~~~+");
        mvprintw(1,20, "|+~~~~~~~+~~~~~~+");
        mvprintw(2,20, "||       |");
        mvprintw(3,20, "||      (oo)");
        mvprintw(4,20, "||    ---+---");
        mvprintw(5,20, "||       |");
        mvprintw(6,20, "||       |");
        mvprintw(7,20, "||       |");
        mvprintw(8,20, "||");
        mvprintw(9,20, "||");
        mvprintw(10,20, "||");
        mvprintw(11,20, "##");}
	else {;};

	if (tent<=1) {
        mvprintw(0,20, "+~~~~~~~~~~~~~~~+");
        mvprintw(1,20, "|+~~~~~~~+~~~~~~+");
        mvprintw(2,20, "||       |");
        mvprintw(3,20, "||      (oo)");
        mvprintw(4,20, "||    ---+---");
        mvprintw(5,20, "||       |");
        mvprintw(6,20, "||       |");
        mvprintw(7,20, "||       |");
        mvprintw(8,20, "||      / \\");
        mvprintw(9,20, "||");
        mvprintw(10,20, "||");
        mvprintw(11,20, "##");}
	else {;};
    return(0);
}


/**
 * Finishes the game and print end messages.
 *
 */
int fim(int ganhou,int sair,int pts,char s1[max]){
    int a = (LINES/2),b = (COLS/2);
    if (ganhou == 0) {
        if (sair ==1) {
            clear();
            mvprintw(a,b-24,"Obrigado por jogar \"O jogo da forca, p.i. 2007\".");
            getch();
            return(0);
        } else {
            clear();
            mvprintw(a,b-15,"Perdeu! A palavra era ' %s '.",s1);
            getch();
            return(0);
        };
    } else {
        clear();
        mvprintw(a,b-45,"Parabéns! Descobriu a palavra secreta que era ' %s '. A sua pontuação foi %d.",s1,pts);
        getch();
        return(pts);
    };
}

/**
 * Main function, begins the game.
 */
int forca() {
    char s1[max]="palavra", // word to guess
        s2[max]="----------", //hidden word placeholder
        c[max], 
        tent=6; //number of tries
        int n=0, //control variable
        cc=0, //control of tries
        ganhou=0,
        ccomp=0,
        gn=0,
        rn, //random number
        sair=0,
        pts=0,
        aux=0, //control
        jogadores=1,
        a = (LINES/2),
        b = (COLS/2);	
        FILE *lst;
        initscr();
        cbreak();
        keypad(stdscr,TRUE);
        noecho();
        start_color();
        init_pair(1,COLOR_BLUE,COLOR_YELLOW);
        init_pair(2,COLOR_BLACK,COLOR_WHITE);
        bkgd(COLOR_PAIR(1));
        // star ncurses
        jogadores = njog();
        clear();
        tent = dif();

        //get word from file
    if (jogadores == 1) {
        rn = escat();
        if (rn == -1) {
            tent=0;
            sair=1;
        } else {
            lst = fopen("palavras.bd","r");
            if (lst == NULL) {
                clear();
                mvprintw(a,b,"Não existe ficheiro!");
                echo();
                mvprintw(a+1,b,"Insira uma palavra para jogar:");		
                mvscanw(a+2,b,"%s",s1);
                noecho();
                clear();
            } else{
                while (rn != n) {
                    n++;
                    fscanf(lst,"%s",s1);
                }
            }
        }
    }

    if (jogadores == 2) {
        clear();
        mvprintw(a,b,"Insira uma palavra para jogar:");
        echo();
        mvscanw(a+2,b,"%s",s1);
        noecho();
        clear();
    }

    stat(tent,s1,s2);
    //begin game
    while (tent > 0 && ganhou!=1) {
        aux ++;
        mvprintw(20,0,"Letra ou palavra:");
        echo();
        mvscanw(20,17,"%s",c);
        noecho();
        while(!isalpha(c[0])) {
            mvprintw(21,0,"Não é um carctér!");
            echo();
            mvscanw(20,17,"%s",c);
            noecho();
        }
        for(n=0;n<strlen(c);n++) {
            c[n] = tolower(c[n]);
	    };
        n=0;
        ccomp=0;
        mvprintw(21,0,"                 ");	
        if(strlen(c) == 1) {
            while(n<strlen(s1)) {
                if (c[0] == s1[n]) {
                    s2[n] = c[0];
                    pts++;
                } else {
                    cc++;
                }
                n++;
            }
        } else {
            while (ccomp<strlen(s1)){
                if (s1[ccomp]==c[ccomp] && (s1[ccomp]!= '\0')) {
                    gn++;
                    ccomp++;
                } else {
                    ccomp++;
                }
            }
            if (gn == (strlen(s1))) {
                n=strlen(s1);
                ccomp=0;
                ganhou=1;
                tent=0;
                pts=strlen(c);
            } else {
                tent--;
                n=strlen(s1);
                pts=strlen(c);
            }
            gn=0;
        }

        if (cc > (strlen(s1)-1)) {
            tent --; 
            cc=0;
        } else { 
            cc=0;
        };
        n=0;
        //win
        while (ccomp<strlen(s1)) {
            if (s1[ccomp]==s2[ccomp] && (s1[ccomp]!= '\0')) {
                gn++;
                ccomp++;
            } else {
                ccomp++;
            }
        }
        if (gn == (strlen(s1))) {
            ccomp=0;
            ganhou=1;
        } else {
            ccomp=0;
        }
        gn=0;
        stat(tent,s1,s2);
    }

    fim(ganhou,sair,pts,s1);
    // end ncurses
    bkgd(COLOR_PAIR(2));
    endwin();
    return(0);
}