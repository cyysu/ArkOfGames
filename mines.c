/**
 * Implementation of the minessweeper game, 
 * resorting to ncurses.
 * @author Rui Couto
 */
#define tc 10

int tcv,tch;

/**
 * 
 */
void mcj(char cj[tcv][tch]) {
    attron(COLOR_PAIR(1));
    int linha,coluna,hlp;
    for(linha=0;(linha<tcv);linha++) {
        for(coluna=0;coluna<(tch);coluna++)	{
            if (cj[linha][coluna]=='-')
                attron(COLOR_PAIR(1));
            if (cj[linha][coluna]=='0')
			    attron(COLOR_PAIR(11));
            if (cj[linha][coluna]=='1')
                attron(COLOR_PAIR(11));
            if (cj[linha][coluna]=='2')
                attron(COLOR_PAIR(12));
            if (cj[linha][coluna]=='3')
                attron(COLOR_PAIR(13));
            if (cj[linha][coluna]=='4')
			    attron(COLOR_PAIR(13));
            mvprintw(linha,coluna,"%c",cj[linha][coluna]);
        };
    };
}

/**
 *
 *
 */
int mcp(int cp[tcv][tch]) {
    bkgd(COLOR_PAIR(1));
    attron(COLOR_PAIR(1));
    int linha,coluna;
    for(linha=0;linha<(tcv);linha++) {
        for(coluna=0;coluna<(tch);coluna++)	{
            if (cp[linha][coluna]==9) {
                mvprintw(linha,coluna,"*");
            }
	        else {
                mvprintw(linha,coluna,"%d",cp[linha][coluna]);
            };
        }
    };
    bkgd(COLOR_PAIR(3));
    return(0);
}

/**
 * Function to handle level selection
 * @return the number of bombs to put on the field
 */
int nivel() {
    int bbs = 0,o=0,a = (LINES/2),b = (COLS/2),x= (LINES/2);

    mvprintw(a-4, b-18, "+-----------------------------------+"); 
    mvprintw(a-3, b-18, "| Bem vindo ao Minesweeper pi_0607! |"); 
    mvprintw(a-2, b-18, "| Escolha o nível de dificuldade:   |"); 
    mvprintw(a-1, b-18, "| > Iniciado                        |"); 
    mvprintw(a  , b-18, "| > Médio                          |"); 
    mvprintw(a+1, b-18, "| > Especialista                    |"); 
    mvprintw(a+2, b-18, "| > Personalizar                    |"); 
    mvprintw(a+3, b-18, "+-----------------------------------+"); 

    while(o == 0) {
        mvprintw(x-1, b-16, "");

        switch(getch()) {
            case (KEY_UP) : {
                if ( x >= (a+1)) {
                    x--;
                };
            };break;
            case (KEY_DOWN): {
                if (x <= (a+2)) {
                    x++;
                };
            };break;
            case 10 : {
                if (x == (a))   {
                    o = 1;
                };
                if (x == (a+1)) {
                    o = 2;
                };
                if (x == (a+2)) {
                    o = 3;
                };
                if (x == (a+3)) {
                    o = 4;
                };
		    };break;
            default : {;};break;
        };
    };
    clear();
    echo();
    
    switch(o) {
        case 1 : {bbs = 10;tcv=10;tch=10;};break;
        case 2 : {bbs = 20;tcv=15;tch=15;};break;
        case 3 : {bbs = 30;tcv=20;tch=20;};break;
        case 4 : {
            while((bbs <= 0) ||(bbs > tc*tc)){
                mvprintw(a, b-9, "Insira numero de bombas: __");
                mvscanw(a,b+16,"%d",&bbs);
			    mvprintw(a+1,b-9,"Insira dimensoes (x y): _ _");
                mvscanw(a+1,b+15,"%d %d",&tcv,&tch);
            }
        };break;
        default : {;};break;
    }
    noecho();
    return(bbs);
}

/**
 * Function to clear all empty spaces around a selected one
 */
int lp_zer(int cp[tcv][tch],char cj[tcv][tch], int x, int y) {
    cj[x][y] = (cp[x][y] + 48);

    //empty spaces
    if ((cp[x-1][y-1] == 0) && (((x-1)>=0)&&((y-1)>=0)&&((x-1)<tcv)&&((y-1)<tch)) && (cj[x-1][y-1] == '-')) {
        lp_zer(cp,cj,(x-1),(y-1));
    };
    if ((cp[x-1][y] == 0) && (((x-1)>=0)&&((y)>=0)&&((x-1)<tcv)&&((y)<tch))&& (cj[x-1][y] == '-')) {
        lp_zer(cp,cj,(x-1),y);
    };    
    if ((cp[x-1][y+1] == 0) && (((x-1)>=0)&&((y+1)>=0)&&((x-1)<tcv)&&((y+1)<tch))&& (cj[x-1][y+1] == '-')) {
        lp_zer(cp,cj,(x-1),(y+1));
    };
    
    if ((cp[x][y-1] == 0) && (((x)>=0)&&((y-1)>=0)&&((x)<tcv)&&((y-1)<tch))&& (cj[x][y-1] == '-')) {
        lp_zer(cp,cj,(x),(y-1));
    };
    if ((cp[x][y+1] == 0) && (((x)>=0)&&((y+1)>=0)&&((x)<tcv)&&((y+1)<tch))&& (cj[x][y+1] == '-')) {
        lp_zer(cp,cj,(x),(y+1));
    };

    if ((cp[x+1][y-1] == 0) && (((x+1)>=0)&&((y-1)>=0)&&((x+1)<tcv)&&((y-1)<tch))&& (cj[x+1][y-1] == '-')) {
        lp_zer(cp,cj,(x+1),(y-1));
    };
    if ((cp[x+1][y] == 0) && (((x+1)>=0)&&((y)>=0)&&((x+1)<tcv)&&((y)<tch))&& (cj[x+1][y] == '-')) {
        lp_zer(cp,cj,(x+1),(y));
    };
    if ((cp[x+1][y+1] == 0) && (((x+1)>=0)&&((y+1)>=0)&&((x+1)<tcv)&&((y+1)<tch))&& (cj[x+1][y+1] == '-')) {
        lp_zer(cp,cj,(x+1),(y+1));
    };
    
    // numbers

    if ((cp[x-1][y-1] != 9) && (((x-1)>=0)&&((y-1)>=0)&&((x-1)<tcv)&&((y-1)<tcv)) && (cj[x-1][y-1] == '-')) {
         cj[x-1][y-1] = (cp[x-1][y-1] + 48);
     };
     if ((cp[x-1][y] != 9) && (((x-1)>=0)&&((y)>=0)&&((x-1)<tcv)&&((y)<tch))&& (cj[x-1][y] == '-')) {
         cj[x-1][y] = (cp[x-1][y] + 48);};
     if ((cp[x-1][y+1] != 9) && (((x-1)>=0)&&((y+1)>=0)&&((x-1)<tcv)&&((y+1)<tch))&& (cj[x-1][y+1] == '-')) {
         cj[x-1][y+1] = (cp[x-1][y+1] + 48);};

     if ((cp[x][y-1] != 9) && (((x)>=0)&&((y-1)>=0)&&((x)<tcv)&&((y-1)<tch))&& (cj[x][y-1] == '-')) { 
         cj[x][y-1] = (cp[x][y-1] + 48);};
     if ((cp[x][y+1] != 9) && (((x)>=0)&&((y+1)>=0)&&((x)<tcv)&&((y+1)<tch))&& (cj[x][y+1] == '-')) { 
         cj[x][y+1] = (cp[x][y+1] + 48);};

     if ((cp[x+1][y-1] != 9) && (((x+1)>=0)&&((y-1)>=0)&&((x+1)<tcv)&&((y-1)<tch))&& (cj[x+1][y-1] == '-')) {
          cj[x+1][y-1] = (cp[x+1][y-1] + 48);
      };
     if ((cp[x+1][y] != 9) && (((x+1)>=0)&&((y)>=0)&&((x+1)<tcv)&&((y)<tch))&& (cj[x+1][y] == '-')) { 
         cj[x+1][y] = (cp[x+1][y] + 48);
     };
     if ((cp[x+1][y+1] != 9) && (((x+1)>=0)&&((y+1)>=0)&&((x+1)<tcv)&&((y+1)<tch))&& (cj[x+1][y+1] == '-')) {
         cj[x+1][y+1] = (cp[x+1][y+1] + 48);
     };
     return(0);
}



/**
 * Main function, initializes and starts the game
 */
int mines(int narg,char** fls) {
    int linha=0,coluna=0,n,perder=0,ganhou=0,x,y,bbs=10,ctrmn=0,o=0,gn=0,k,ll=1,tmpx,tmpy,e;
    char of,tmpof,s1[50],estado;
    FILE* tab;
    FILE* jogs;
    initscr();
    cbreak();
    keypad(stdscr,TRUE);
    noecho();
    start_color();

    init_pair(1,COLOR_BLUE,COLOR_WHITE);
    init_pair(2,COLOR_BLACK,COLOR_WHITE);
    init_pair(3,COLOR_WHITE,COLOR_BLACK);
    init_pair(4,COLOR_RED,COLOR_BLACK);
    init_pair(5,COLOR_GREEN,COLOR_BLACK);

    init_pair(10,COLOR_YELLOW,COLOR_WHITE);
    init_pair(11,COLOR_BLUE,COLOR_WHITE);
    init_pair(12,COLOR_GREEN,COLOR_WHITE);
    init_pair(13,COLOR_RED,COLOR_WHITE);

    bkgd(COLOR_PAIR(3));



    if (narg >= 2){	tab = fopen(fls[1],"r");
	    fscanf(tab,"%d %d",&tcv,&bbs);
        tch=tcv;

        char cj[tcv][tch];
        int cp[tcv][tch];
	    // init the user field
        for(linha=0;linha<(tcv);linha++) {
            for(coluna=0;coluna<(tch);coluna++)
                (cj[linha][coluna]= '-');
	    };
	    // init the game field
        for(linha=0;linha<(tcv);linha++) {
            for(coluna=0;coluna<(tch);coluna++)
 		        (cp[linha][coluna]= 0);
        };
    
        while (fscanf(tab,"%d %d",&x,&y)!=EOF)
            cp[x][y]=9;
    
        ctrmn=0;
        for(linha=0;linha<tcv;linha++) {
            for(coluna=0;coluna<tch;coluna++) {
                if (cp[linha][coluna] != 9) {
                    if ((cp[linha-1][coluna-1] == 9) && (linha-1>=0) && (coluna-1>=0)) {
                        ctrmn++;
                    };
                    if ((cp[linha-1][coluna] == 9) && (linha-1>=0)) {
                        ctrmn++;
                    };
                    if ((cp[linha-1][coluna+1] == 9) && (linha-1>=0) && (coluna+1<=tch)) {
                        ctrmn++;
                    };
                    if ((cp[linha][coluna-1] == 9)  && (coluna-1>=0)) {
                        ctrmn++;
                    };
                    if ((cp[linha][coluna+1] == 9) && (coluna-1<=tch)) {
                        ctrmn++;
                    };
                    if ((cp[linha+1][coluna-1] == 9) && (linha+1<=tcv) && (coluna-1>=0)) {
                        ctrmn++;
                    };
                    if ((cp[linha+1][coluna] == 9) && (linha+1<=tcv)) {
                        ctrmn++;
                    };
                    if ((cp[linha+1][coluna+1] == 9) && (linha+1<=tcv) && (coluna+1<=tch)) {
                        ctrmn++;
                    };
                    cp[linha][coluna] = ctrmn;
                };
                ctrmn=0;
            };
        };
    } else {
        bbs = nivel();
        char cj[tcv][tch];
        int cp[tcv][tch];
        srand(time(NULL));
        // init the user field
        for(linha=0;linha<(tcv);linha++) {
            for(coluna=0;coluna<(tch);coluna++)
 			    (cj[linha][coluna]= '-');
        };
        //init the game field
        for(linha=0;linha<(tcv);linha++) {
            for(coluna=0;coluna<(tch);coluna++)
 			    (cp[linha][coluna]= 0);
		};
        //place the bombs in the field
        n=0;
        while(n<bbs) {
            linha = rand() % tcv;
            coluna = rand() % tch;
            if(cp[linha][coluna] == 0) {
                cp[linha][coluna]=9;
                n++;
            };
        };
        // Calculate the field mines
        ctrmn=0;
        for(linha=0;linha<tcv;linha++) {
            for(coluna=0;coluna<tch;coluna++) {
                if (cp[linha][coluna] != 9)	{
                    if (cp[linha-1][coluna-1] == 9) {
                        ctrmn++;
                    };
                    if (cp[linha-1][coluna] == 9) {
                        ctrmn++;
                    };
                    if (cp[linha-1][coluna+1] == 9) {
                        ctrmn++;
                    };
                    if (cp[linha][coluna-1] == 9) {
                        ctrmn++;
                    };
                    if (cp[linha][coluna+1] == 9) {
                        ctrmn++;
                    };
                    if (cp[linha+1][coluna-1] == 9) {
                        ctrmn++;
                    };
                    if (cp[linha+1][coluna] == 9) {
                        ctrmn++;
                    };
                    if (cp[linha+1][coluna+1] == 9) {
                        ctrmn++;
                    };
                    cp[linha][coluna] = ctrmn;
                };
                ctrmn=0;
            };
        };
    };

    char cj[tcv][tch];
    int cp[tcv][tch];
    mcj(cj);
    x=0;
    y=0;

    //Beggining of the game
    while(perder!=1 && ganhou!=1) {
        if (narg == 3) {
            jogs = fopen(fls[2],"r");
            for(k=0;k!=ll;k++)
                fscanf(jogs,"%c %d %d\n",&of,&x,&y);
            if (of == 'A') o = 1;
            if (of == 'M') o = 2;
            if (fscanf(jogs,"%c %d %d\n",&tmpof,&tmpx,&tmpy) != EOF) {
                ll++;
            } else {
                ganhou=1;
            };
        } else {
            e=0;
            while(e==0) {
                mvprintw(x,y,"");
                switch(getch())	{
                    case (KEY_UP) : {
                        if (x>0) 
                            x--;
                    };break;
                    case (KEY_DOWN): {
                        if(x<(tch-1)) 
                            x++;
                    };break;
                    case (KEY_LEFT): {
                        if(y>0) 
                            y--;
                    };break;
                    case (KEY_RIGHT): {
                        if(y<(tcv-1)) 
                            y++;
                    };break;
                    case (10)      : {
                        e=1;o=1;
                    };break;
                    case (32): {
                        e=1;o=2;
                    };break;
                };
	
            };
        };

        if(o == 1) {
            if ((cp[x][y] == 9) && (cj[x][y] != 'M')) {
                cj[x][y] ='*';
                perder = 1;
                ganhou = 0;
			};
            if (((cp[x][y] != 0) && cp[x][y] != 9)  && (cj[x][y] != 'M'))
                 cj[x][y] = (cp[x][y]+48);
            if ((cp[x][y] == 0 && ((cj[x][y] != '?') && (cj[x][y] != 'M') ))) 
                lp_zer(cp,cj,x,y);
        };
        if(o == 2) {
            switch(cj[x][y]) {
                case 'M' : {
                    cj[x][y] = '-';
                };break;
                case '-' : {
                    cj[x][y] = 'M';
                };break;
                default : {;};break;
            };
        };
        clear();
        mcj(cj);
        // Winning 
        if (perder != 1) {
            gn = 1;
            for (linha=0;linha<(tcv-1);linha++) {
                for (coluna =0;coluna<(tch-1);coluna++) {
                    if ((cp[linha][coluna] != 9) && (cj[linha][coluna] == '-')) 
                        gn = 0;
                };
            };
            if ( gn == 1) 
                ganhou=1;
        };
    };

    // End of the game
    if (narg == 3) {
        FILE *out;
        FILE *reses;
        out = fopen("mine.out","w");
        reses = fopen("results.txt","a");

        for(linha=0;(linha<tcv);linha++) {
            for(coluna=0;coluna<(tch);coluna++) {
                if (cj[linha][coluna] == '-') {
                    fprintf(out,"- ");
                }
                else {
                    fprintf(out,"%c ",cj[linha][coluna]);
                };
		    };
            fprintf(out,"\n");
        };
        if (ganhou == 1)
            estado = 'G';
        if (ganhou == 0) {
            estado = 'P';
        } else {
            estado = 'I';
        };

        fclose(out);
        fscanf(reses,"%s",s1);
        if (s1 == "TABULEIRO") { //??
            fprintf(reses,"%s\t%s\t%c%d\tmines.out\n",fls[2],fls[1],estado,ll);
	    } else {
            fprintf(reses,"TABULEIRO\tJOGADAS\tRESULTADO\tFIC.RESULTADO\n");
            fprintf(reses,"%s\t%s\t%c%d\tmines.out\n",fls[2],fls[1],estado,ll);
        };
    } else {
        clear();
        x=(LINES/2);y=(COLS/2);

        if (ganhou == 1) {
            clear();
            attron(COLOR_PAIR(5));
            mvprintw(x-1,y-10,"+------------------------------------+");
            mvprintw(x,y-10,"|Parabens, ganhou o jogo Minesweeper!|");
            mvprintw(x+1,y-10,"+------------------------------------+");
            for(linha=0;(linha<tcv-1);linha++) {
                for(coluna=0;coluna<(tch-1);coluna++) {
                    if (cj[linha][coluna] == '*') {
                        mvprintw(linha,coluna,"*");
                    } else {
                        mvprintw(linha,coluna,"%c  ",cj[linha][coluna]);
                    };
                };
            };
            getch();
        } else {
            clear();
            mcj(cj);
            attron(COLOR_PAIR(4));
            mvprintw(x-1,y-10,"+------------------------------------+");
            mvprintw(x,y-10,"|Perdeu, melhor sorte para a proxima.|");
            mvprintw(x+1,y-10,"+------------------------------------+");
            getch();
        };
    }
    bkgd(COLOR_PAIR(2));
    endwin();
    return(0);
}