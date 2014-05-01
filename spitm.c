/**
 * Implementation of the spite and malice game,
 * resorting to ncurses.
 * It uses also a linked list.
 * @author Rui Couto
 */
#define num 53
#define stk 20
#define sz 14
#define dbar num*2-2

//Linked list related functions

/**
 * Linked list definition
 */
typedef struct LinkList {
    int carta;
	struct LinkList *prox;
} List, *listP;


/**
 * Get the number of elements in the list
 */
int elemN(listP lista) {
    int n;
    for (n=0; lista!=NULL; n++) 
        lista = lista->prox;
    return(n);
}

/**
 * Get the card number at a given position
 */
int showi(listP lista, int valor) {
    for ( ; valor>0; valor--) 
	    lista=lista->prox;
    return (lista->carta);
}

/**
 * Insert a new card in the linked list
 *
 */
listP poe(listP lista, int valor) {
    listP nova;
    nova = (listP)malloc(sizeof(List));
    nova->carta = valor;
    nova->prox = lista;
    return (nova);
}

/**
 * Remove the last element of the list (pop)
 */
listP rmUlt(listP lista) {
    listP aux;
    aux = lista->prox;
    free(lista);
    return aux;
}

/**
 * Remove the element at the given position
 */
void rmI(listP lista, int valor) {
    listP aux;
    for ( ; valor>1; valor--) 
        lista = lista->prox;
    aux = lista->prox;
    lista->prox = aux->prox;
    free(aux);
}

/**
 * Show the linked list
 */
void show2(listP lista) {
    int i,j, sequencia[elemN(lista)];
    for (i=0; lista!=NULL; i++) {
        sequencia[i] = lista->carta;
	    lista = lista->prox;
	}
    for (j=i-1; j>=0; j--) {
        if(sequencia[j] == 11) 
            printw("V  ");
	    if(sequencia[j] == 12) 
            printw("D  ");
	    if(sequencia[j] == 13) 
            printw("R  ");
        if(sequencia[j] < 11) 
            printw("%d  ",sequencia[j]);
	};
}

//

void showA(int tam,int arr[tam]) {
    int n;
    for(n=0;n<tam;n++)
 	    if(arr[n] !=0) {
        printw("%d ",arr[n]);
    };
}

/**
 * Array to list
 */
listP atod (int from[(dbar)],listP to,int n) {
    int i=0,c=0;
    while(c<n) {
        if (from[i] != 0) {
            to=poe(to,from[i]);
		    from[i]=0;
		    c++;
            i++;
		} else
		    i++;
	};
    return(to);
}

/**
 * List to array
 */
void dtoa (listP from,int pos, int* to) {
    int i=0;
    while(to[i]!=0)
        i++;
    to[i]=showi(from,pos);
    mvprintw(0,0,"#casa %d#",pos);
    getch();
    if (elemN(from) != (pos-1)) 
        rmI(from,pos);
    else {
        from=rmUlt(from);
     };
}

/**
 * Copy array to array
 */
void atoa (int* from,int* to,int n) { 
    int i=0,c=0;
    while(c<n) {
        if (from[i] != 0) {
            to[c]=from[i];
            from[i]=0;
            c++;
            i++;
		} else
            i++;
	};
}

/**
 * Reset an array
 */
void limpa(int* lista, int tam) {
    int i;
    for (i=0;i < tam;i++)
	    lista[i] = 0;
}

/**
 * Shuffle an array
 */
int shuff(int* baralho) {
    int i=0, n=0,r;
    srand(time(NULL));
    limpa(baralho,dbar);
    while(i<104) {
        r = rand() % 105;
	    if ( n >= 13) {
            n=0;
        };
	    if (baralho[r] == 0) {
            n++;baralho[r] = n;
            i++;
        };
	};
    return(0);
}

/**
 * Shuffle a list
 */
listP baralhar(listP baralho) {
    int cartArr[(num*2)-2],i;
    shuff(cartArr);
    limpa (cartArr,dbar);
    for(i=0;i<=(num*2)-3;i++) {
        baralho = poe(baralho,cartArr[i]);
	};
    return(baralho);
}

/**
 *
 */
void barStk(int* stock, int tmn) {
    int tmp[stk],r,i=0;
    limpa(tmp,tmn);
    r=(rand()%tmn);
    showA(tmn,stock);
    while(i<tmn) {
        if (tmp[r] == 0) {
            tmp[r] = stock[i];
            i++;
            r=rand()%stk;
        } else {
            r=rand()%stk;
        };
    };
}

void addAe(int* from,int* to)
{
    int i=0,c=0,k=0;
    while(to[k]==0)
	    k++;
    k--;
    while(c==0) {
        if (from[i] != 0) {
            to[k]=from[i];
            from[i]=0;
            c++;
            i++;
		} else
            i++;
	};
}

int topAr(int* list) { 
    int i=0;
    while(list[i] == 0)
	    i++;
    if (i == 13) 
        return (list[i-1]);
    else 
        return (list[i]);
}

int strt(int* a,int n) {
    int i=0,j=0;
    while(i<stk) {
        if (a[i] != 0) {
            j++;
            i++;
        } else 
            j++;
	};
    return(j);
}

/**
 * Show the game field
 */
void mostrac(listP mao1,listP pl11,listP pl12,listP pl13,listP pl14,listP mao2,listP pl21,listP pl22,listP pl23,listP pl24,int* pc1,int* pc2,int* pc3,int* stock1,int* stock2,int turno) {
    int n=0;
    mvprintw(0,0,"+--------------------------------------------------------+");
    mvprintw(0,3,"|Turno: %d|",turno);
    mvprintw(1,0,"|Jogador 1");
    mvprintw(1,57,"|");
    mvprintw(2,0,"|(1-5)Mao: [");
    if(turno==1) {
        show2(mao1);
    } else {
        mvprintw(2,12,"~  ~  ~  ~  ~");
    };
    mvprintw(2,57,"|");
    mvprintw(2,28,"]");
    mvprintw(3,0,"|(10) Stock[");
    while ((stock1[n]==0) && (n<stk)) {
        n++;
    }; 
    if (stock1[n] == 0) {
        mvprintw(3,12,"X]");
    } else  {
        if(stock1[n] == 11) 
            mvprintw(3,12,"V]");
        if(stock1[n] == 12) 
            mvprintw(3,12,"D]");
        if(stock1[n] == 13) 
            mvprintw(3,12,"R]");
        if(stock1[n] <11) 
            mvprintw(3,12,"%d]",stock1[n]);
    };
    mvprintw(3,57,"|");
    mvprintw(4,0,"|      (6)P.l.1 [");show2(pl11);mvprintw(4,57,"|");
    mvprintw(5,0,"|      (7)P.l.2 [");show2(pl12);mvprintw(5,57,"|");
    mvprintw(6,0,"|      (8)P.l.3 [");show2(pl13);mvprintw(6,57,"|");
    mvprintw(7,0,"|      (9)P.l.4 [");show2(pl14);mvprintw(7,57,"|");

    mvprintw(8,0,"+--------------------------------------------------------+");
    mvprintw(9,3,"(d1)P.c.1 [");showA(13,pc1);
    mvprintw(10,3,"(d2)P.c.2 [");showA(13,pc2);
    mvprintw(11,3,"(d3)P.c.3 [");showA(13,pc3);
    mvprintw(12,0,"+--------------------------------------------------------+");
    mvprintw(13,0,"|      (9)P.l.4 [");show2(pl24);mvprintw(13,57,"|");
    mvprintw(14,0,"|      (8)P.l.3 [");show2(pl23);mvprintw(14,57,"|");
    mvprintw(15,0,"|      (7)P.l.2 [");show2(pl22);mvprintw(15,57,"|");
    mvprintw(16,0,"|      (6)P.l.1 [");show2(pl21);mvprintw(16,57,"|");
    n=0;
    mvprintw(17,0,"|(10) Stock[");
    while ((stock2[n]==0) && (n<stk)) {
        n++;
    }; 
    if (stock2[n] == 0) {
        mvprintw(17,12,"X]");
    } else {
        if(stock2[n] == 11) 
            mvprintw(17,12,"V]");
        if(stock2[n] == 12) 
            mvprintw(17,12,"D]");
        if(stock2[n] == 13) 
            mvprintw(17,12,"R]");
        if((stock2[n] != 11) &&(stock2[n] != 12)&&(stock2[n] != 13))
		    mvprintw(17,12,"%d]",stock2[n]);
	};
    mvprintw(17,57,"|");
    mvprintw(18,0,"|(1-5)Mao: [");
    if(turno==2) {
        show2(mao2);
    } else {
        mvprintw(18,12,"~  ~  ~  ~  ~");
    };
    mvprintw(18,57,"|");
    mvprintw(18,28,"]");
    mvprintw(19,0,"|Jogador 2");mvprintw(19,57,"|");
    mvprintw(20,0,"+--------------------------------------------------------+");	
}

/**
 * Main function. Initializes and starts the game
 */
int spitm() {listP mao1,mao2,pl11,pl12,pl13,pl14,pl21,pl22,pl23,pl24;
    int stock1[stk],stock2[stk],baralho[(num*2)-2],pc1[sz],pc2[sz],pc3[sz];
    mao1=mao2=pl11=pl12=pl13=pl14=pl21=pl22=pl23=pl24=NULL;
    int vencedor=0,turno=1,o,d,i=0,n=0,x=(LINES/2),y=(COLS/2);

    initscr();
    cbreak();
    keypad(stdscr,TRUE);
    noecho();
    start_color();
    init_pair(1,COLOR_WHITE,COLOR_GREEN);
    init_pair(2,COLOR_RED,COLOR_GREEN);
    bkgd(COLOR_PAIR(1));
    attron(COLOR_PAIR(2));

    limpa(pc1,13);
    limpa(pc2,13);
    limpa(pc3,13);
    shuff(baralho);
    atoa(baralho,stock1,20);
    atoa(baralho,stock2,20);
    mao1=atod(baralho,mao1,5);
    mao2=atod(baralho,mao2,5);
    while(!i) {
        if(stock1[0] > stock2[0]) {
            turno=1;i++;
        };break;
	    if(stock1[0] < stock2[0]) {
            turno=2;
            i++;
        };break;
	    barStk(stock1,stk);
        barStk(stock2,stk);
	};
    
    while(vencedor==0) {
        while(elemN(mao1)<5)
            mao1=atod(baralho,mao1,1);
        while(turno==1)	{
            clear();
            mostrac(mao1,pl11, pl12,pl13, pl14, mao2, pl21, pl22, pl23,pl24, pc1, pc2, pc3, stock1, stock2,turno);
            echo();
            mvprintw(22,0,"Insira origem(1-10) e destino (1-7):__ __");
            mvscanw(22,36," %d %d",&o,&d);
            if(o>0 && o<6) {
                if(d==1) {
                    if (showi(mao1,elemN(mao1)-o) == topAr(pc1)+1) {
                        dtoa(mao1,elemN(mao1)-o,pc1);
                    };
                };
                if(d==2) {
                    if (showi(mao1,elemN(mao1)-o) == topAr(pc2)+1) {
                        dtoa(mao1,elemN(mao1)-o,pc2);
                    };
                };
			    if(d==3) {
                    if (showi(mao1,elemN(mao1)-o) == topAr(pc3)+1) {
                        dtoa(mao1,elemN(mao1)-o,pc3);
                    };
                };
    			if(d==4) {
                    pl11=poe(pl11,showi(mao1,elemN(mao1)-o));
                    if(elemN(mao1) == o) {
                        mao1=rmUlt(mao1);turno=2;
                    } else {
                        rmI(mao1,elemN(mao1)-(o));
                        turno=2;
                    };
                };
	
			    if(d==5) {
                    pl12=poe(pl12,showi(mao1,elemN(mao1)-o));
                    if(elemN(mao1) == o) {
                        mao1=rmUlt(mao1);
                        turno=2;
                    } else {
                        rmI(mao1,elemN(mao1)-(o));
                        turno=2;
                    };
                };
			    if(d==6) {
                    pl13=poe(pl13,showi(mao1,elemN(mao1)-o));
                    if(elemN(mao1) == o) {
                        mao1=rmUlt(mao1);
                        turno=2;
                    } else {
                        rmI(mao1,elemN(mao1)-(o));
                        turno=2;
                    };
                };
			    if(d==7) {
                    pl14=poe(pl14,showi(mao1,elemN(mao1)-o));
                    if(elemN(mao1) == o) {
                        mao1=rmUlt(mao1);
                        turno=2;
                    } else {
                        rmI(mao1,elemN(mao1)-(o));
                        turno=2;
                    };
                };
			}; //end if(o>0 && o<6)
            if(o==10) {
                if(d==1){
                    if (topAr(stock1) == topAr(pc1)+1) {
                        addAe(stock1,pc1);
                    };
                };
			    if(d==2) {
                    if (topAr(stock1) == topAr(pc2)+1) {
                        addAe(stock1,pc2);
                    };
                };
			    if(d==3) {
                    if (topAr(stock1) == topAr(pc3)+1) {
                        addAe(stock1,pc3);
                    };
                };
            };
            if(o>5 && o< 10) {
                if(o==6 && d==1 && (elemN(pl11)!=0)) {
                    if (showi(pl11,elemN(pl11)-o) == topAr(pc1)+1) {
                        dtoa(pl11,elemN(pl11)-1,pc1);
                    };
                };
			    if(o==7 && d==1 && (elemN(pl12)!=0)) {
                    if (showi(pl12,elemN(pl12)-o) == topAr(pc1)+1) {
                        dtoa(pl12,elemN(pl12)-1,pc1);
                    };
                };
			    if(o==8 && d==1 && (elemN(pl13)!=0)) {
                    if (showi(pl13,elemN(pl13)-o) == topAr(pc1)+1) {
                        dtoa(pl13,elemN(pl13)-1,pc1);
                    };
                };
                if(o==9 && d==1 && (elemN(pl14)!=0)) {
                    if (showi(pl14,elemN(pl14)-o) == topAr(pc1)+1) {
                        dtoa(pl14,elemN(pl14)-1,pc1);
                    };
                };
            
                if(o==6 && d==2 && (elemN(pl11)!=0)) {
                    if (showi(pl11,elemN(pl11)-o) == topAr(pc2)+1) {
                        dtoa(pl11,elemN(pl11)-1,pc2);
                    };
                };
                if(o==7 && d==2 && (elemN(pl12)!=0)) {
                    if (showi(pl12,elemN(pl12)-o) == topAr(pc2)+1) {
                        dtoa(pl12,elemN(pl12)-1,pc2);
                    };
                };
                if(o==8 && d==2 && (elemN(pl13)!=0)) {
                    if (showi(pl13,elemN(pl13)-o) == topAr(pc2)+1) {
                        dtoa(pl13,elemN(pl13)-1,pc2);
                    };
                };
                if(o==9 && d==2 && (elemN(pl14)!=0)) {
                    if (showi(pl14,elemN(pl14)-o) == topAr(pc2)+1) {
                        dtoa(pl14,elemN(pl14)-1,pc2);
                    };
                };

                if(o==6 && d==3 && (elemN(pl11)!=0)) {
                    if (showi(pl11,elemN(pl11)-o) == topAr(pc3)+1) {
                        dtoa(pl11,elemN(pl11)-1,pc3);
                    };
                };
                if(o==7 && d==3 && (elemN(pl12)!=0)) {
                    if (showi(pl12,elemN(pl12)-o) == topAr(pc3)+1) {
                        dtoa(pl12,elemN(pl12)-1,pc3);
                    };
                };
                if(o==8 && d==3 && (elemN(pl13)!=0)) {
                    if (showi(pl13,elemN(pl13)-o) == topAr(pc3)+1) {
                        dtoa(pl13,elemN(pl13)-1,pc3);
                    };
                };
                if(o==9 && d==3 && (elemN(pl14)!=0)) {
                    if (showi(pl14,elemN(pl14)-o) == topAr(pc3)+1) {
                        dtoa(pl14,elemN(pl14)-1,pc3);
                    };
                };
            };//end if(o>5 && o< 10)
        }; //end while(turno==1)

        n=0;
        while ((stock1[n]==0) && (n<stk)) {
            n++;
        };
        // Winner is player 1
        if (stock1[n] == 0) {
            vencedor=1;
            turno=1;
        }

        // Tie
        if(baralho[num*2-3]==0)	{
            vencedor=3;
        };

        // Clean central stack
        if(pc1[0]==13) {
            atoa(pc1,baralho,13);
        };
        if(pc2[0]==13) {
            atoa(pc2,baralho,13);
        };
        if(pc3[0]==13) {
            atoa(pc3,baralho,13);
        };

        // fill hand 2
        while(elemN(mao2)<5) {
            mao2=atod(baralho,mao2,1);
        };

        while(turno==2) {
            clear();
            mostrac(mao1,pl11, pl12,pl13, pl14, mao2, pl21, pl22, pl23,pl24, pc1, pc2, pc3, stock1, stock2,turno);
            echo();
            mvprintw(22,0,"Insira origem(1-10) e destino (1-7):__ __");
            mvscanw(22,36,"%d %d",&o,&d);
            if(o>0 && o<6) {
                if(d==1) {
                    if (showi(mao2,elemN(mao2)-o) == topAr(pc1)+1) {
                        dtoa(mao2,elemN(mao2)-o,pc1);};
                    };
                    if(d==2) {
                        if (showi(mao2,elemN(mao2)-o) == topAr(pc2)+1) {
                            dtoa(mao2,elemN(mao2)-o,pc2);
                        };
                    };
                    if(d==3) {
                        if (showi(mao2,elemN(mao2)-o) == topAr(pc3)+1) {
                            dtoa(mao2,elemN(mao2)-o,pc3);
                        };
                    };
                    if(d==4) {
                        pl21=poe(pl21,showi(mao2,elemN(mao2)-o));
                        if(elemN(mao2) == o) {
                            mao2=rmUlt(mao2);turno=1;
                        } else {
                            rmI(mao2,elemN(mao2)-(o));
                            turno=1;
                        };
                    };
                    if(d==5) {
                        pl22=poe(pl22,showi(mao2,elemN(mao2)-o));
                        if(elemN(mao2) == o) {
                            mao2=rmUlt(mao2);
                            turno=1;
                        } else {
                            rmI(mao2,elemN(mao2)-(o));
                            turno=1;
                        };
                    };
                    if(d==6) {
                        pl23=poe(pl23,showi(mao2,elemN(mao2)-o));
                        if(elemN(mao2) == o) {
                            mao2=rmUlt(mao2);
                            turno=1;
                        } else {
                            rmI(mao2,elemN(mao2)-(o));
                            turno=1;
                        };
                    };
                    if(d==7) {
                        pl24=poe(pl24,showi(mao2,elemN(mao2)-o));
                        if(elemN(mao2) == o) {
                            mao2=rmUlt(mao2);
                            turno=1;
                        } else {
                            rmI(mao2,elemN(mao2)-(o));
                            turno=1;
                        }
                    };
		        };
                if(o==10) {
                    if(d==1){
                        if (topAr(stock2) == topAr(pc1)+1) {
                            addAe(stock2,pc1);
                        };
			        };
		            if(d==2) {
                        if (topAr(stock2) == topAr(pc2)+1) {
                            addAe(stock2,pc2);
                        };
			        };
                    if(d==3) {
                        if (topAr(stock2) == topAr(pc3)+1)  {
                            addAe(stock2,pc3);
                        };
				    };
                };
                if(o>5 && o< 10) {
                    if(o==6 && d==1 && (elemN(pl21)!=0)) {
                        if (showi(pl21,elemN(pl21)-o) == topAr(pc1)+1) {
                            dtoa(pl21,elemN(pl21)-1,pc1);
                        };
                    };
                    if(o==7 && d==1 && (elemN(pl22)!=0)) {
                        if (showi(pl22,elemN(pl22)-o) == topAr(pc1)+1) {
                            dtoa(pl22,elemN(pl22)-1,pc1);
                        };
                    };
                if(o==8 && d==1 && (elemN(pl23)!=0)) {
                    if (showi(pl23,elemN(pl23)-o) == topAr(pc1)+1) {
                        dtoa(pl23,elemN(pl23)-1,pc1);
                    };
                };
                if(o==9 && d==1 && (elemN(pl24)!=0)) {
                    if (showi(pl24,elemN(pl24)-o) == topAr(pc1)+1) {
                        dtoa(pl24,elemN(pl24)-1,pc1);
                    };
                };
                if(o==6 && d==2 && (elemN(pl21)!=0)) {
                    if (showi(pl21,elemN(pl21)-o) == topAr(pc2)+1) {
                        dtoa(pl21,elemN(pl21)-1,pc2);
                    };
                };
                if(o==7 && d==2 && (elemN(pl22)!=0)) {
                    if (showi(pl22,elemN(pl22)-o) == topAr(pc2)+1) {
                        dtoa(pl22,elemN(pl22)-1,pc2);
                    };
			    };
                if(o==8 && d==2 && (elemN(pl23)!=0)) {
                    if (showi(pl23,elemN(pl23)-o) == topAr(pc2)+1) {
                         dtoa(pl23,elemN(pl23)-1,pc2);
                     };
                };
                if(o==9 && d==2 && (elemN(pl24)!=0)) {
                    if (showi(pl24,elemN(pl24)-o) == topAr(pc2)+1) {
                        dtoa(pl24,elemN(pl24)-1,pc2);
                    };
                };

                if(o==6 && d==3 && (elemN(pl21)!=0)) {
                    if (showi(pl21,elemN(pl21)-o) == topAr(pc3)+1) {
                        dtoa(pl21,elemN(pl21)-1,pc3);
                    };
                };
                if(o==7 && d==3 && (elemN(pl22)!=0)) {
                    if (showi(pl22,elemN(pl22)-o) == topAr(pc3)+1) {
                        dtoa(pl22,elemN(pl22)-1,pc3);
                    };
                };
                if(o==8 && d==3 && (elemN(pl23)!=0)) {
                    if (showi(pl23,elemN(pl23)-o) == topAr(pc3)+1) {
                        dtoa(pl23,elemN(pl23)-1,pc3);
                    };
                };
                if(o==9 && d==3 && (elemN(pl24)!=0)) {
                    if (showi(pl24,elemN(pl24)-o) == topAr(pc3)+1) {
                        dtoa(pl24,elemN(pl24)-1,pc3);
                    };
                };
             };
        };
        n=0;
        while ((stock2[n]==0) && (n<stk)) {
            n++;
        };
        // Winner is player 2
        if (stock2[n] == 0) {
            vencedor=1;
            turno=1;
        }

        // Tie
        if(baralho[num*2-3]==0) {
            vencedor=3;
        };

        // Clean central stack
        if(pc1[0]==13) {
            atoa(pc1,baralho,13);
        };
        if(pc2[0]==13) {
            atoa(pc2,baralho,13);
        };
        if(pc3[0]==13) {
            atoa(pc3,baralho,13);
        };
    };
    if((vencedor==1)||(vencedor==2)) {
        clear();
        mvprintw(x-1,y-10,"+------------------------------------+");
        mvprintw(x,y-10,"|O jogador %d vence!                 |",vencedor);
        mvprintw(x+1,y-10,"+------------------------------------+");
        getch();
    } else {
        clear();
        mvprintw(x-1,y-10,"+------------------------------------+");
        mvprintw(x,y-10,"|Empate, não há vencedores.          |");
        mvprintw(x+1,y-10,"+------------------------------------+");
        getch();
    };
    endwin();
    bkgd(COLOR_PAIR(2));
    return 0;
}
