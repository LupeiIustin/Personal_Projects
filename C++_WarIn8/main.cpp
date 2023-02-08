#include <iostream>
#include<graphics.h>
#include <winbgim.h>
#include<windows.h>
#define MAX 100
#include <stdlib.h>
#include <mmsystem.h>
#include <ctime>
#include <stdio.h>
using namespace std;

struct structura
{
    int numarCitit;
    int lungimeFereastra=getmaxwidth();
    int inaltimeFereastra=getmaxheight();
    int tabla[MAX][MAX];
    bool finalMeniu;
    bool gata;
    bool gataMeniul;
    ///n=nr linii si m=nr coloane
    int n=8; int m=8;
    int latura=50;
    int width=m*latura;
    int height=n*latura;
    int stanga;
    int dreapta;
    int sus;
    int jos;
    int schimbareGrafica=false;
    int modJucator;
    int scorJucator1=0;
    int scorJucator2=0;
    char sirScorJucator1[10];
    char sirScorJucator2[10];
    bool scadereScor=0;
    bool crestereScor=0;
}joc;

struct vecini1
{
    bool vecinDreaptaJos;
    bool vecinStangaJos;
    bool vecinDreaptaSus;
    bool vecinStangaSus;
    int nrvecini;
    int piesaStearsa;
}vecini;

void afiseazaScor(int jucator)
{
    joc.sirScorJucator1[10];
    joc.sirScorJucator2[10];
    settextstyle(GOTHIC_FONT, HORIZ_DIR, 3);
    itoa(joc.scorJucator1,joc.sirScorJucator1, 10);
    itoa(joc.scorJucator2,joc.sirScorJucator2, 10);
    setcolor(WHITE);
    if (jucator>-1&& joc.crestereScor==1)
    {
        for (int i=0;i<=joc.n;i++)
            for (int j=1;j<=joc.n;j++)
                if (joc.tabla[i][j]==1 && jucator==1)
                    joc.scorJucator1++;
                else if(joc.tabla[i][j]==2 &&jucator==2)
                    joc.scorJucator2++;
    }
    else if(jucator>-1&& joc.scadereScor==1 && joc.scorJucator1>0 && joc.scorJucator2>0)
    {
        if(joc.scorJucator1>2 &&joc.scorJucator2>2)
        {
            if(jucator==1)
                joc.scorJucator1-=3;
            else
                joc.scorJucator2-=3;
        }
        else
        {
            if(jucator==1)
                joc.scorJucator1=0;
            else
                joc.scorJucator2=0;
        }
    }
    joc.crestereScor=0;
    joc.scadereScor=0;
    itoa(joc.scorJucator1,joc.sirScorJucator1,10);
    itoa(joc.scorJucator2, joc.sirScorJucator2,10);
    outtextxy(0.2*getmaxwidth(),10,joc.sirScorJucator1);
    outtextxy(0.23*getmaxwidth(),100,joc.sirScorJucator2);
    settextstyle(GOTHIC_FONT, HORIZ_DIR, 3);
    outtextxy(0.02*getmaxwidth(),10,"PIESA ALBA: ");
    outtextxy(0.02*getmaxwidth(),100,"PIESA NEAGRA: ");
}
bool castigat(int jucator);

void resetareScor()
{
    joc.scorJucator1=0;
    joc.scorJucator2=0;
}

void lungimeSiInaltimeFereastra()
{
    FILE *fptr;
    if ((fptr = fopen("newprogram.txt","r")) == NULL)
    {
        printf("Error! opening file");
        // Program exits if the file pointer return0s NULL.
        exit(1);
    }
    fscanf(fptr,"%d", &joc.numarCitit); ///am extras valoarea care imi trebuie din fisier
    fclose(fptr);

    if(joc.numarCitit!=800)
    {
        joc.lungimeFereastra=getmaxwidth();
        joc.inaltimeFereastra=getmaxheight();
        joc.stanga=(joc.lungimeFereastra-joc.width)/2; joc.dreapta=(joc.lungimeFereastra+joc.width)/2;
        joc.sus=(joc.inaltimeFereastra-joc.height)/2; joc.jos=(joc.inaltimeFereastra+joc.height)/2;
    }
    else
    {
        joc.lungimeFereastra=joc.numarCitit;
        joc.inaltimeFereastra=joc.numarCitit;
        joc.stanga=(joc.lungimeFereastra-joc.width)/2; joc.dreapta=(joc.lungimeFereastra+joc.width)/2;
        joc.sus=(joc.inaltimeFereastra-joc.height)/2; joc.jos=(joc.inaltimeFereastra+joc.height)/2;
    }
}

void stareaJocului()///vreau sa memorez intr-un vector
{
    FILE *fptr;
    if ((fptr = fopen("newprogram.txt","r")) == NULL)
    {
        printf("Error! opening file");
        // Program exits if the file pointer return0s NULL.
        exit(1);
    }
    fscanf(fptr,"%d", &joc.numarCitit); ///am extras valoarea care imi trebuie din fisier
    fclose(fptr);

    if(joc.numarCitit!=800)
    {
        joc.lungimeFereastra=getmaxwidth();
        joc.inaltimeFereastra=getmaxheight();
        joc.stanga=(joc.lungimeFereastra-joc.width)/2; joc.dreapta=(joc.lungimeFereastra+joc.width)/2;
        joc.sus=(joc.inaltimeFereastra-joc.height)/2; joc.jos=(joc.inaltimeFereastra+joc.height)/2;
    }
    else
    {
        joc.lungimeFereastra=joc.numarCitit;
        joc.inaltimeFereastra=joc.numarCitit;
        joc.stanga=(joc.lungimeFereastra-joc.width)/2; joc.dreapta=(joc.lungimeFereastra+joc.width)/2;
        joc.sus=(joc.inaltimeFereastra-joc.height)/2; joc.jos=(joc.inaltimeFereastra+joc.height)/2;
    }
}

void afiseazaCastigator()
{
    if(castigat(1)==1)///daca a castigat alb
    {
        readimagefile("negruoptimizat.gif",0,0,joc.lungimeFereastra, joc.inaltimeFereastra);
        readimagefile("you-win-animation0002.gif",(joc.stanga+(joc.n*joc.latura)/2)-275, 0.35*joc.inaltimeFereastra,(joc.stanga+(joc.n*joc.latura)/2)+275, 0.65*joc.inaltimeFereastra);
        readimagefile("piesa-alba-optimizat1.gif",(joc.stanga+(joc.n*joc.latura)/2)-50, 0.4*joc.inaltimeFereastra,(joc.stanga+(joc.n*joc.latura)/2)+50, 0.5*joc.inaltimeFereastra);
        delay(100);
        readimagefile("negruoptimizat.gif",0,0,joc.lungimeFereastra, joc.inaltimeFereastra);
        readimagefile("you-win-animation0003.gif",(joc.stanga+(joc.n*joc.latura)/2)-275, 0.35*joc.inaltimeFereastra,(joc.stanga+(joc.n*joc.latura)/2)+275, 0.65*joc.inaltimeFereastra);
        readimagefile("piesa-alba-optimizat1.gif",(joc.stanga+(joc.n*joc.latura)/2)-50, 0.4*joc.inaltimeFereastra,(joc.stanga+(joc.n*joc.latura)/2)+50, 0.5*joc.inaltimeFereastra);
        delay(100);
        readimagefile("negruoptimizat.gif",0,0,joc.lungimeFereastra, joc.inaltimeFereastra);
        readimagefile("you-win-animation0004.gif",(joc.stanga+(joc.n*joc.latura)/2)-275, 0.35*joc.inaltimeFereastra,(joc.stanga+(joc.n*joc.latura)/2)+275, 0.65*joc.inaltimeFereastra);
        readimagefile("piesa-alba-optimizat1.gif",(joc.stanga+(joc.n*joc.latura)/2)-50, 0.4*joc.inaltimeFereastra,(joc.stanga+(joc.n*joc.latura)/2)+50, 0.5*joc.inaltimeFereastra);
        delay(100);
        readimagefile("negruoptimizat.gif",0,0,joc.lungimeFereastra, joc.inaltimeFereastra);
        readimagefile("you-win-animation0005.gif",(joc.stanga+(joc.n*joc.latura)/2)-275, 0.35*joc.inaltimeFereastra,(joc.stanga+(joc.n*joc.latura)/2)+275, 0.65*joc.inaltimeFereastra);
        readimagefile("piesa-alba-optimizat1.gif",(joc.stanga+(joc.n*joc.latura)/2)-50, 0.4*joc.inaltimeFereastra,(joc.stanga+(joc.n*joc.latura)/2)+50, 0.5*joc.inaltimeFereastra);
        delay(100);
        readimagefile("negruoptimizat.gif",0,0,joc.lungimeFereastra, joc.inaltimeFereastra);
        readimagefile("you-win-animation0006.gif",(joc.stanga+(joc.n*joc.latura)/2)-275, 0.35*joc.inaltimeFereastra,(joc.stanga+(joc.n*joc.latura)/2)+275, 0.65*joc.inaltimeFereastra);
        readimagefile("piesa-alba-optimizat1.gif",(joc.stanga+(joc.n*joc.latura)/2)-50, 0.4*joc.inaltimeFereastra,(joc.stanga+(joc.n*joc.latura)/2)+50, 0.5*joc.inaltimeFereastra);
        delay(100);
        readimagefile("negruoptimizat.gif",0,0,joc.lungimeFereastra, joc.inaltimeFereastra);
        readimagefile("you-win-animation0007.gif",(joc.stanga+(joc.n*joc.latura)/2)-275, 0.35*joc.inaltimeFereastra,(joc.stanga+(joc.n*joc.latura)/2)+275, 0.65*joc.inaltimeFereastra);
        readimagefile("piesa-alba-optimizat1.gif",(joc.stanga+(joc.n*joc.latura)/2)-50, 0.4*joc.inaltimeFereastra,(joc.stanga+(joc.n*joc.latura)/2)+50, 0.5*joc.inaltimeFereastra);
        delay(100);
        readimagefile("negruoptimizat.gif",0,0,joc.lungimeFereastra, joc.inaltimeFereastra);
        readimagefile("you-win-animation0008.gif",(joc.stanga+(joc.n*joc.latura)/2)-275, 0.35*joc.inaltimeFereastra,(joc.stanga+(joc.n*joc.latura)/2)+275, 0.65*joc.inaltimeFereastra);
        readimagefile("piesa-alba-optimizat1.gif",(joc.stanga+(joc.n*joc.latura)/2)-50, 0.4*joc.inaltimeFereastra,(joc.stanga+(joc.n*joc.latura)/2)+50, 0.5*joc.inaltimeFereastra);
        delay(100);
        readimagefile("negruoptimizat.gif",0,0,joc.lungimeFereastra, joc.inaltimeFereastra);
        readimagefile("you-win-animation0009.gif",(joc.stanga+(joc.n*joc.latura)/2)-275, 0.35*joc.inaltimeFereastra,(joc.stanga+(joc.n*joc.latura)/2)+275, 0.65*joc.inaltimeFereastra);
        readimagefile("piesa-alba-optimizat1.gif",(joc.stanga+(joc.n*joc.latura)/2)-50, 0.4*joc.inaltimeFereastra,(joc.stanga+(joc.n*joc.latura)/2)+50, 0.5*joc.inaltimeFereastra);
        delay(100);
        readimagefile("negruoptimizat.gif",0,0,joc.lungimeFereastra, joc.inaltimeFereastra);
        readimagefile("you-win-animation0010.gif",(joc.stanga+(joc.n*joc.latura)/2)-275, 0.35*joc.inaltimeFereastra,(joc.stanga+(joc.n*joc.latura)/2)+275, 0.65*joc.inaltimeFereastra);
        readimagefile("piesa-alba-optimizat1.gif",(joc.stanga+(joc.n*joc.latura)/2)-50, 0.4*joc.inaltimeFereastra,(joc.stanga+(joc.n*joc.latura)/2)+50, 0.5*joc.inaltimeFereastra);
        delay(100);
        readimagefile("negruoptimizat.gif",0,0,joc.lungimeFereastra, joc.inaltimeFereastra);
        readimagefile("you-win-animation0011.gif",(joc.stanga+(joc.n*joc.latura)/2)-275, 0.35*joc.inaltimeFereastra,(joc.stanga+(joc.n*joc.latura)/2)+275, 0.65*joc.inaltimeFereastra);
        readimagefile("piesa-alba-optimizat1.gif",(joc.stanga+(joc.n*joc.latura)/2)-50, 0.4*joc.inaltimeFereastra,(joc.stanga+(joc.n*joc.latura)/2)+50, 0.5*joc.inaltimeFereastra);
        delay(100);
        readimagefile("negru optimizat.gif",0,0,joc.lungimeFereastra, joc.inaltimeFereastra);
        readimagefile("you-win-animation0012.gif",(joc.stanga+(joc.n*joc.latura)/2)-275, 0.35*joc.inaltimeFereastra,(joc.stanga+(joc.n*joc.latura)/2)+275, 0.65*joc.inaltimeFereastra);
        readimagefile("piesa-alba-optimizat1.gif",(joc.stanga+(joc.n*joc.latura)/2)-50, 0.4*joc.inaltimeFereastra,(joc.stanga+(joc.n*joc.latura)/2)+50, 0.5*joc.inaltimeFereastra);
        delay(100);
        readimagefile("negruoptimizat.gif",0,0,joc.lungimeFereastra, joc.inaltimeFereastra);
        readimagefile("you-win-animation0013.gif",(joc.stanga+(joc.n*joc.latura)/2)-275, 0.35*joc.inaltimeFereastra,(joc.stanga+(joc.n*joc.latura)/2)+275, 0.65*joc.inaltimeFereastra);
		readimagefile("piesa-alba-optimizat1.gif",(joc.stanga+(joc.n*joc.latura)/2)-50, 0.4*joc.inaltimeFereastra,(joc.stanga+(joc.n*joc.latura)/2)+50, 0.5*joc.inaltimeFereastra);
        delay(100);
    }
    else///daca a castigat negru
    {
        readimagefile("negruoptimizat.gif",0,0,joc.lungimeFereastra, joc.inaltimeFereastra);
        delay(100);
        readimagefile("piesa-neagra-optimizat1.gif",(joc.stanga+(joc.n*joc.latura)/2)-50, 0.4*joc.inaltimeFereastra,(joc.stanga+(joc.n*joc.latura)/2)+50, 0.5*joc.inaltimeFereastra);
		readimagefile("you-win-animation0002.gif",(joc.stanga+(joc.n*joc.latura)/2)-275, 0.35*joc.inaltimeFereastra,(joc.stanga+(joc.n*joc.latura)/2)+275, 0.65*joc.inaltimeFereastra);
        readimagefile("piesa-neagra-optimizat1.gif",(joc.stanga+(joc.n*joc.latura)/2)-50, 0.4*joc.inaltimeFereastra,(joc.stanga+(joc.n*joc.latura)/2)+50, 0.5*joc.inaltimeFereastra);
        delay(100);
        readimagefile("negruoptimizat.gif",0,0,joc.lungimeFereastra, joc.inaltimeFereastra);
        readimagefile("you-win-animation0003.gif",(joc.stanga+(joc.n*joc.latura)/2)-275, 0.35*joc.inaltimeFereastra,(joc.stanga+(joc.n*joc.latura)/2)+275, 0.65*joc.inaltimeFereastra);
        readimagefile("piesa-neagra-optimizat1.gif",(joc.stanga+(joc.n*joc.latura)/2)-50, 0.4*joc.inaltimeFereastra,(joc.stanga+(joc.n*joc.latura)/2)+50, 0.5*joc.inaltimeFereastra);
        delay(100);
        readimagefile("negruoptimizat.gif",0,0,joc.lungimeFereastra, joc.inaltimeFereastra);
        readimagefile("you-win-animation0004.gif",(joc.stanga+(joc.n*joc.latura)/2)-275, 0.35*joc.inaltimeFereastra,(joc.stanga+(joc.n*joc.latura)/2)+275, 0.65*joc.inaltimeFereastra);
        readimagefile("piesa-neagra-optimizat1.gif",(joc.stanga+(joc.n*joc.latura)/2)-50, 0.4*joc.inaltimeFereastra,(joc.stanga+(joc.n*joc.latura)/2)+50, 0.5*joc.inaltimeFereastra);
        delay(100);
        readimagefile("negruoptimizat.gif",0,0,joc.lungimeFereastra, joc.inaltimeFereastra);
        readimagefile("you-win-animation0005.gif",(joc.stanga+(joc.n*joc.latura)/2)-275, 0.35*joc.inaltimeFereastra,(joc.stanga+(joc.n*joc.latura)/2)+275, 0.65*joc.inaltimeFereastra);
        readimagefile("piesa-neagra-optimizat1.gif",(joc.stanga+(joc.n*joc.latura)/2)-50, 0.4*joc.inaltimeFereastra,(joc.stanga+(joc.n*joc.latura)/2)+50, 0.5*joc.inaltimeFereastra);
        delay(100);
        readimagefile("negruoptimizat.gif",0,0,joc.lungimeFereastra, joc.inaltimeFereastra);
        readimagefile("you-win-animation0006.gif",(joc.stanga+(joc.n*joc.latura)/2)-275, 0.35*joc.inaltimeFereastra,(joc.stanga+(joc.n*joc.latura)/2)+275, 0.65*joc.inaltimeFereastra);
        readimagefile("piesa-neagra-optimizat1.gif",(joc.stanga+(joc.n*joc.latura)/2)-50, 0.4*joc.inaltimeFereastra,(joc.stanga+(joc.n*joc.latura)/2)+50, 0.5*joc.inaltimeFereastra);
        delay(100);
        readimagefile("negruoptimizat.gif",0,0,joc.lungimeFereastra, joc.inaltimeFereastra);
        readimagefile("you-win-animation0007.gif",(joc.stanga+(joc.n*joc.latura)/2)-275, 0.35*joc.inaltimeFereastra,(joc.stanga+(joc.n*joc.latura)/2)+275, 0.65*joc.inaltimeFereastra);
        readimagefile("piesa-neagra-optimizat1.gif",(joc.stanga+(joc.n*joc.latura)/2)-50, 0.4*joc.inaltimeFereastra,(joc.stanga+(joc.n*joc.latura)/2)+50, 0.5*joc.inaltimeFereastra);
        delay(100);
        readimagefile("negruoptimizat.gif",0,0,joc.lungimeFereastra, joc.inaltimeFereastra);
        readimagefile("you-win-animation0008.gif",(joc.stanga+(joc.n*joc.latura)/2)-275, 0.35*joc.inaltimeFereastra,(joc.stanga+(joc.n*joc.latura)/2)+275, 0.65*joc.inaltimeFereastra);
        readimagefile("piesa-neagra-optimizat1.gif",(joc.stanga+(joc.n*joc.latura)/2)-50, 0.4*joc.inaltimeFereastra,(joc.stanga+(joc.n*joc.latura)/2)+50, 0.5*joc.inaltimeFereastra);
        delay(100);
        readimagefile("negruoptimizat.gif",0,0,joc.lungimeFereastra, joc.inaltimeFereastra);
        readimagefile("you-win-animation0009.gif",(joc.stanga+(joc.n*joc.latura)/2)-275, 0.35*joc.inaltimeFereastra,(joc.stanga+(joc.n*joc.latura)/2)+275, 0.65*joc.inaltimeFereastra);
        readimagefile("piesa-neagra-optimizat1.gif",(joc.stanga+(joc.n*joc.latura)/2)-50, 0.4*joc.inaltimeFereastra,(joc.stanga+(joc.n*joc.latura)/2)+50, 0.5*joc.inaltimeFereastra);
        delay(100);
        readimagefile("negruoptimizat.gif",0,0,joc.lungimeFereastra, joc.inaltimeFereastra);
        readimagefile("you-win-animation0010.gif",(joc.stanga+(joc.n*joc.latura)/2)-275, 0.35*joc.inaltimeFereastra,(joc.stanga+(joc.n*joc.latura)/2)+275, 0.65*joc.inaltimeFereastra);
        readimagefile("piesa-neagra-optimizat1.gif",(joc.stanga+(joc.n*joc.latura)/2)-50, 0.4*joc.inaltimeFereastra,(joc.stanga+(joc.n*joc.latura)/2)+50, 0.5*joc.inaltimeFereastra);
        delay(100);
        readimagefile("negruoptimizat.gif",0,0,joc.lungimeFereastra, joc.inaltimeFereastra);
        readimagefile("you-win-animation0011.gif",(joc.stanga+(joc.n*joc.latura)/2)-275, 0.35*joc.inaltimeFereastra,(joc.stanga+(joc.n*joc.latura)/2)+275, 0.65*joc.inaltimeFereastra);
        readimagefile("piesa-neagra-optimizat1.gif",(joc.stanga+(joc.n*joc.latura)/2)-50, 0.4*joc.inaltimeFereastra,(joc.stanga+(joc.n*joc.latura)/2)+50, 0.5*joc.inaltimeFereastra);
        delay(100);
        readimagefile("negru optimizat.gif",0,0,joc.lungimeFereastra, joc.inaltimeFereastra);
        readimagefile("you-win-animation0012.gif",(joc.stanga+(joc.n*joc.latura)/2)-275, 0.35*joc.inaltimeFereastra,(joc.stanga+(joc.n*joc.latura)/2)+275, 0.65*joc.inaltimeFereastra);
        readimagefile("piesa-neagra-optimizat1.gif",(joc.stanga+(joc.n*joc.latura)/2)-50, 0.4*joc.inaltimeFereastra,(joc.stanga+(joc.n*joc.latura)/2)+50, 0.5*joc.inaltimeFereastra);
        delay(100);
        readimagefile("negruoptimizat.gif",0,0,joc.lungimeFereastra, joc.inaltimeFereastra);
        readimagefile("you-win-animation0013.gif",(joc.stanga+(joc.n*joc.latura)/2)-275, 0.35*joc.inaltimeFereastra,(joc.stanga+(joc.n*joc.latura)/2)+275, 0.65*joc.inaltimeFereastra);
		readimagefile("piesa-neagra-optimizat11.gif",0.48*joc.lungimeFereastra, 0.40*joc.inaltimeFereastra,0.52*joc.lungimeFereastra, 0.5*joc.inaltimeFereastra);
        delay(100);
    }
}

void desenareTabla()
{
        readimagefile("negru.gif",joc.stanga, joc.sus, joc.dreapta,joc.jos);
        int x1,y1,x2,y2;
        setcolor(WHITE);
        for( int i=1;i<=joc.n;i++ )
            for( int j=1;j<=joc.m;j++ )
               {
                rectangle(joc.stanga+joc.latura*(i-1),joc.sus+joc.latura*(j-1),joc.stanga+joc.latura*i,joc.sus+joc.latura*j);///am facut patratele cu rectangle
                if(i%2==0 && j%2==0)///am colorat patratele
                {
                    setfillstyle(SOLID_FILL, WHITE);
                    floodfill(joc.stanga+joc.latura*(i-1)+1,joc.sus+joc.latura*(j-1)+1,WHITE);
                }
                if(i%2!=0 && j%2!=0)
                {
                    setfillstyle(SOLID_FILL, WHITE);
                    floodfill(joc.stanga+joc.latura*(i-1)+1,joc.sus+joc.latura*(j-1)+1,WHITE);
                }
               }
}
void desenarePiese(int i,int j,int piesa)
{
        int x1,y1,x2,y2;
        int linia=i;
        int coloana=j;
        x1=joc.stanga+joc.latura*(coloana-1); y1=joc.sus+joc.latura*(linia-1);
        x2=x1+joc.latura; y2=y1+joc.latura;
        if(piesa==1)
            readimagefile("piesa alba optimizat.gif",x1, y1, x2, y2);
        else
            readimagefile("piesa neagra optimizat.gif",x1, y1, x2, y2);
}

void stergerePiese(int i, int j)
{
                if((i+j)%2==0)///daca pozitia e pe alb, deseneaza o imagine alba
                    readimagefile("alboptimizat.gif",joc.stanga+joc.latura*(j-1),joc.sus+joc.latura*(i-1),joc.stanga+joc.latura*(j-1)+joc.latura,joc.sus+joc.latura*(i-1)+joc.latura);
                else///daca pozitia e pe negru, deseneaza o imagine neagra
                    readimagefile("negruoptimizat.gif",joc.stanga+joc.latura*(j-1),joc.sus+joc.latura*(i-1),joc.stanga+joc.latura*(j-1)+joc.latura,joc.sus+joc.latura*(i-1)+joc.latura);
}
void matriceaJocului()
{
        ///Jucator 1
        for(int i=1;i<=2;i++)///liniile 1 si 2
            for(int j=1;j<=joc.m;j++)
            {
                if( (i+j)%2==0 )///pozitiile pare iau valoarea 1
                    joc.tabla[i][j]=1;
            }
        ///Jucator 2
        for(int i=joc.n-1;i<=joc.n;i++)///liniile n si n-1
            for(int j=1;j<=joc.m;j++)
            {
                if( (i+j)%2==0 )///pozitiile pare iau valoarea 2
                    joc.tabla[i][j]=2;
            }
        ///Spatiu gol
        for( int i=0;i<=joc.n+1;i++ )
            for( int j=0;j<=joc.m+1;j++ )
            {
                if( (i+j)%2!=0 )///pozitiile impare iau valoarea 0
                    joc.tabla[i][j]=0;
                if( i==0 or j==0 or j==9 or i==9 )
                           joc.tabla[i][j]=4;
            }
}

void resetareMatrice()
{
        for(int i=1;i<=joc.n;i++)
            for(int j=1;j<=joc.m;j++)
            {
                    joc.tabla[i][j]=0;
            }
}

void desenareTot()
{
    desenareTabla();
    matriceaJocului();
    for( int i=1;i<=joc.n;i++ )
        for( int j=1;j<=joc.m;j++ )
        {
            if( joc.tabla[i][j]==1 )
                desenarePiese(i,j,1);
            else if( joc.tabla[i][j]==2 )
                desenarePiese(i,j,2);
            else if(joc.tabla[i][j]==0)
                stergerePiese(i,j);
        }
}

void deseneazaBordura();
void afiseazaScor();
void desenareAproapeTot()
{
    readimagefile("menuu.jpg",0, 0, joc.lungimeFereastra,joc.inaltimeFereastra);
    deseneazaBordura();
    desenareTabla();
    afiseazaScor(1);
        afiseazaScor(2);

    for( int i=1;i<=joc.n;i++ )
        for( int j=1;j<=joc.m;j++ )
        {
            if( joc.tabla[i][j]==1 )
                desenarePiese(i,j,1);
            else if( joc.tabla[i][j]==2 )
                desenarePiese(i,j,2);
            else if(joc.tabla[i][j]==0)
                stergerePiese(i,j);
        }
}

bool pozitieCorecta(int linia1, int coloana1, int linia2, int coloana2)
{
    if((linia2==linia1-1 && coloana2==coloana1+1 || linia2==linia1+1 && coloana2==coloana1+1 || linia2==linia1+1 && coloana2==coloana1-1 || linia2==linia1-1 && coloana2==coloana1-1) && joc.tabla[linia2][coloana2]==0)
    return true;
    else
    return false;
}

void colorareMutare(int i,int j)
{
        int x1,y1,x2,y2;
        int linia=i;
        int coloana=j;
        x1=joc.stanga+joc.latura*(coloana-1); y1=joc.sus+joc.latura*(linia-1);
        x2=x1+joc.latura; y2=y1+joc.latura;
        readimagefile("neon borders.gif",x1, y1, x2, y2);
        if(joc.tabla[linia+1][coloana+1]==0 && linia!=joc.n && coloana!=joc.m)///dreapta jos
        {
            readimagefile("neon borders.gif",x1+joc.latura, y1+joc.latura, x2+joc.latura, y2+joc.latura);
           // stergerePiese(linia+1,coloana+1);
        }
        if(joc.tabla[linia+1][coloana-1]==0 && linia!=joc.n  && coloana!=1)///stanga jos
        {
            readimagefile("neon borders.gif",x1-joc.latura, y1+joc.latura, x2-joc.latura, y2+joc.latura);
          //  stergerePiese(linia+1,coloana-1);
        }
        if(joc.tabla[linia-1][coloana+1]==0 && linia!=joc.n && coloana!=joc.m && linia!=1 )///dreapta sus
        {
            readimagefile("neon borders.gif",x1+joc.latura, y1-joc.latura, x2+joc.latura, y2-joc.latura);
          //  stergerePiese(linia-1,coloana+1);
        }
        if(joc.tabla[linia-1][coloana-1]==0 && linia!=1 && coloana!=1 )///stanga sus
        {
            readimagefile("neon borders.gif",x1-joc.latura, y1-joc.latura, x2-joc.latura, y2-joc.latura);
            //stergerePiese(linia-1,coloana-1);
        }
}

void stergereColorareMutare(int i, int j)
{
    int x1,y1,x2,y2;
    int linia=i;
    int coloana=j;
    x1=joc.stanga+joc.latura*(coloana-1);
    y1=joc.sus+joc.latura*(linia-1);
    x2=x1+joc.latura;
    y2=y1+joc.latura;
        if(joc.tabla[linia+1][coloana+1]==0 && linia!=joc.n && coloana!=joc.m)///dreapta jos
        {
            stergerePiese(linia+1,coloana+1);
        }
        if(joc.tabla[linia+1][coloana-1]==0 && linia!=joc.n && coloana!=1)///stanga jos
        {
            stergerePiese(linia+1,coloana-1);
        }
        if(joc.tabla[linia-1][coloana+1]==0 && linia!=joc.n && coloana!=joc.m && linia!=1 )///dreapta sus
        {
            stergerePiese(linia-1,coloana+1);
        }
        if(joc.tabla[linia-1][coloana-1]==0 && linia!=1 && coloana!=1)///stanga sus
        {
            stergerePiese(linia-1,coloana-1);
        }
}

int NrVecini(int i,int j, int jucator)///calculeaza numarul de vecini diferiti de jucator si de 0 ///primeste datele vecinului mutarii actuale
{
        int nrvecini=0;
        int linia=i;
        int coloana=j;
        if(joc.tabla[linia+1][coloana+1]!=0 && joc.tabla[linia+1][coloana+1]!=jucator)///dreapta jos
        {
            nrvecini++;
        }
        if(joc.tabla[linia+1][coloana-1]!=0 && joc.tabla[linia+1][coloana-1]!=jucator)///stanga jos
        {
             nrvecini++;
        }
        if(joc.tabla[linia-1][coloana+1]!=0 && joc.tabla[linia-1][coloana+1]!=jucator)///dreapta sus
        {
             nrvecini++;
        }
        if(joc.tabla[linia-1][coloana-1]!=0 && joc.tabla[linia-1][coloana-1]!=jucator)///stanga sus
        {
             nrvecini++;
        }
       // cout<<"eroareee:"<<nrvecini<<endl;
        return nrvecini;
}

void scoatereVecini(int i,int j)
{
        int linia=i;
        int coloana=j;

            if(joc.tabla[linia+1][coloana+1]==1)///dreapta jos
            {
                if(NrVecini(linia+1, coloana+1, 1)==4)///se uita la fiecare vecin diferit de 0 si daca e inconjurat de 4 piese care nu sunt 0, sterge piesa
                    {
                        stergerePiese(linia+1, coloana+1);
                        joc.tabla[linia+1][coloana+1]=0;
                    }
            }
            if(joc.tabla[linia+1][coloana-1]==1)///stanga jos
            {
                if(NrVecini(linia+1, coloana-1, 1)==4)
                    {
                        stergerePiese(linia+1, coloana-1);
                        joc.tabla[linia+1][coloana-1]=0;
                    }
            }
            if(joc.tabla[linia-1][coloana+1]==1)///dreapta sus
            {
                if(NrVecini(linia-1, coloana+1, 1)==4)
                    {
                        stergerePiese(linia-1, coloana+1);
                        joc.tabla[linia-1][coloana+1]=0;
                    }
            }
            if(joc.tabla[linia-1][coloana-1]==1)///stanga sus
            {
                if(NrVecini(linia-1, coloana-1, 1)==4)
                    {
                        stergerePiese(linia+1, coloana+1);
                        joc.tabla[linia-1][coloana-1]=0;
                    }
            }
            ///vecinul e jucator 2
            if(joc.tabla[linia+1][coloana+1]==2)///dreapta jos
            {
                if(NrVecini(linia+1, coloana+1, 2)==4)///se uita la fiecare vecin diferit de 0 si daca e inconjurat de 4 piese care nu sunt 0, sterge piesa
                    {
                        stergerePiese(linia+1, coloana+1);
                        joc.tabla[linia+1][coloana+1]=0;
                    }
            }
            if(joc.tabla[linia+1][coloana-1]==2)///stanga jos
            {
                if(NrVecini(linia+1, coloana-1, 2)==4)
                    {
                        stergerePiese(linia+1, coloana-1);
                        joc.tabla[linia+1][coloana-1]=0;
                    }
            }
            if(joc.tabla[linia-1][coloana+1]==2)///dreapta sus
            {
                if(NrVecini(linia-1, coloana+1, 2)==4)
                    {
                        stergerePiese(linia-1, coloana+1);
                        joc.tabla[linia-1][coloana+1]=0;
                    }
            }
            if(joc.tabla[linia-1][coloana-1]==2)///stanga sus
            {
                if(NrVecini(linia-1, coloana-1, 2)==4)
                    {
                        stergerePiese(linia-1, coloana-1);
                        joc.tabla[linia-1][coloana-1]=0;
                    }
            }

}

void functiaJocului();

void mutarePiesa(int jucator)
{
    int linia1,coloana1,linia2,coloana2,x,y;
    int x1, y1, x2, y2;
    int xmijloc, ymijloc;
    int click=false;
    do
        if(ismouseclick(WM_LBUTTONDOWN) && !click)
        {
            clearmouseclick(WM_LBUTTONDOWN);
            x=mousex(); y=mousey();
            if(x>joc.stanga && x<joc.dreapta && y>joc.sus && y<joc.jos)///daca am apasat in interiorul tablei
                {
                    linia1=(y-joc.sus)/joc.latura+1; coloana1=(x-joc.stanga)/joc.latura+1;
                    if(joc.tabla[linia1][coloana1]==jucator)
                    {
                        click=true;///daca ai apasat click unde trebuie, click devine true, altfel se repeta continuu in bucla
                        colorareMutare(linia1, coloana1);
                        joc.tabla[linia1][coloana1]=0;
                    }
                }
            else if(x>(joc.lungimeFereastra-(200+10)) && x<(joc.lungimeFereastra-10) && y>10 && y<(106+10) )///daca am apasat pe exit, va iesi din joc
            {
                click=true;///daca ai apasat click unde trebuie, click devine true, altfel se repeta continuu in bucla
                resetareMatrice();
                resetareScor();
                functiaJocului();
            }
        }
    while (!click);
    click=false;
    do
        if(ismouseclick(WM_LBUTTONDOWN) && !click)
        {
            clearmouseclick(WM_LBUTTONDOWN);
            x=mousex(); y=mousey();
            if(x>joc.stanga && x<joc.dreapta && y>joc.sus && y<joc.jos)///daca am apasat in interiorul tablei
            {
                linia2=(y-joc.sus)/joc.latura+1; coloana2=(x-joc.stanga)/joc.latura+1;
                if(pozitieCorecta(linia1, coloana1, linia2, coloana2))
                {
                    joc.crestereScor=1;
                    stergereColorareMutare(linia1,coloana1);
                    joc.tabla[linia2][coloana2]=jucator;
                    afiseazaScor(jucator);
                    click=true;
                    cout<<"nr vecini: "<<NrVecini(linia2, coloana2,jucator)<<endl;

                }
                else///daca pozitia nu e corecta scad scorul
                {
                    joc.scadereScor=1;
                    afiseazaScor(jucator);
                }
            }
            else if(x>(joc.lungimeFereastra-(200+10)) && x<(joc.lungimeFereastra-10) && y>10 && y<(106+10) )///daca am apasat pe exit, va iesi din joc
            {
                click=true;///daca ai apasat click unde trebuie, click devine true, altfel se repeta continuu in bucla
                resetareMatrice();
                resetareScor();
                functiaJocului();
            }

        }
    while (!click);
    stergerePiese(linia1,coloana1);
    desenarePiese(linia2,coloana2,jucator);
    scoatereVecini(linia2,coloana2);
 }

void mutarePiesa1(int jucator)
{
    if( jucator==1 )
    {
            int linia1,coloana1,linia2,coloana2,x,y;
            int x1, y1, x2, y2;
            int xmijloc, ymijloc;
            int click=false;
             do{

                linia1=rand()%9;
                coloana1= rand()%9;
                if(linia1==0)
                    linia1++;
                if(coloana1==0)
                    coloana1++;
                cout<<linia1<<" "<<coloana1<<"___";
                    if(joc.tabla[linia1][coloana1]==jucator and ( joc.tabla[linia1+1][coloana1+1]==0 or joc.tabla[linia1-1][coloana1-1]==0 or joc.tabla[linia1+1][coloana1-1]==0 or joc.tabla[linia1-1][coloana1+1]==0 ) )
                        {
                            click=true;///daca ai apasat click unde trebuie, click devine true, altfel se repeta continuu in bucla
                            //colorareMutare(linia1, coloana1);
                            joc.tabla[linia1][coloana1]=0;
                            if(jucator==1)
                            {
                                joc.crestereScor=1;
                                joc.scorJucator1++;
                            }
                            afiseazaScor(1);
                        }

             } while(!click);

             click=false;

             do{
                        if( joc.tabla[linia1+1][coloana1+1]==0 )
                        {
                            joc.tabla[linia1+1][coloana1+1]=jucator;
                            stergerePiese(linia1,coloana1);
                            desenarePiese(linia1+1,coloana1+1,jucator);
                            scoatereVecini(linia1+1,coloana1+1);
                            click=true;
                        }

                else

                           if( joc.tabla[linia1+1][coloana1-1]==0 )
                         {
                            joc.tabla[linia1+1][coloana1-1]=jucator;
                            stergerePiese(linia1,coloana1);
                            desenarePiese(linia1+1,coloana1-1,jucator);
                            scoatereVecini(linia1+1,coloana1-1);
                            click=true;
                         }

                else

                    if( joc.tabla[linia1-1][coloana1-1]==0 )
                         {
                            joc.tabla[linia1-1][coloana1-1]=jucator;
                            stergerePiese(linia1,coloana1);
                            desenarePiese(linia1-1,coloana1-1,jucator);
                            scoatereVecini(linia1-1,coloana1-1);
                            click=true;
                         }

                else

                    if( joc.tabla[linia1-1][coloana1+1]==0 )
                         {
                            joc.tabla[linia1-1][coloana1+1]=jucator;
                            stergerePiese(linia1,coloana1);
                            desenarePiese(linia1-1,coloana1+1,jucator);
                            scoatereVecini(linia1-1,coloana1+1);
                            click=true;
                         }


               } while(!click);

         }
         else
            if( jucator==2 )
            {
                        int linia1,coloana1,linia2,coloana2,x,y;
                        int x1, y1, x2, y2;
                        int xmijloc, ymijloc;
                        int click=false;
                        do
                            if(ismouseclick(WM_LBUTTONDOWN) && !click)
                            {
                                clearmouseclick(WM_LBUTTONDOWN);
                                x=mousex(); y=mousey();
                                if(x>joc.stanga && x<joc.dreapta && y>joc.sus && y<joc.jos)///daca am apasat in interiorul tablei
                                    {
                                        linia1=(y-joc.sus)/joc.latura+1; coloana1=(x-joc.stanga)/joc.latura+1;
                                        if(joc.tabla[linia1][coloana1]==jucator)
                                        {
                                            click=true;///daca ai apasat click unde trebuie, click devine true, altfel se repeta continuu in bucla
                                            colorareMutare(linia1, coloana1);
                                            joc.tabla[linia1][coloana1]=0;
                                        }
                                    }
                                else if(x>(joc.lungimeFereastra-(200+10)) && x<(joc.lungimeFereastra-10) && y>10 && y<(106+10) )///daca am apasat pe exit, va iesi din joc
                                {
                                    click=true;///daca ai apasat click unde trebuie, click devine true, altfel se repeta continuu in bucla
                                    resetareMatrice();
                                    resetareScor();
                                    functiaJocului();
                                }
                            }
                        while (!click);
                        click=false;
                        do
                            if(ismouseclick(WM_LBUTTONDOWN) && !click)
                            {
                                clearmouseclick(WM_LBUTTONDOWN);
                                x=mousex(); y=mousey();
                                if(x>joc.stanga && x<joc.dreapta && y>joc.sus && y<joc.jos)///daca am apasat in interiorul tablei
                                {
                                    linia2=(y-joc.sus)/joc.latura+1; coloana2=(x-joc.stanga)/joc.latura+1;
                                    if(pozitieCorecta(linia1, coloana1, linia2, coloana2))
                                    {
                                        joc.crestereScor=1;
                                        stergereColorareMutare(linia1,coloana1);
                                        joc.tabla[linia2][coloana2]=jucator;
                                        afiseazaScor(jucator);
                                        click=true;
                                        cout<<"nr vecini: "<<NrVecini(linia2, coloana2,jucator)<<endl;

                                    }
                                    else///daca pozitia nu e corecta scad scorul
                                    {
                                        joc.scadereScor=1;
                                        afiseazaScor(jucator);
                                    }
                                }
                                else if(x>(joc.lungimeFereastra-(200+10)) && x<(joc.lungimeFereastra-10) && y>10 && y<(106+10) )///daca am apasat pe exit, va iesi din joc
                                {
                                    click=true;///daca ai apasat click unde trebuie, click devine true, altfel se repeta continuu in bucla
                                    resetareMatrice();
                                    resetareScor();
                                    functiaJocului();
                                }

                            }
                        while (!click);
                        stergerePiese(linia1,coloana1);
                        desenarePiese(linia2,coloana2,jucator);
                        scoatereVecini(linia2,coloana2);
            }
}

 bool castigat(int jucator)
{
    int valoriInTablaJucator1=0;
    int valoriInTablaJucator2=0;
    for (int i=0;i<=joc.n+1;i++)
        for (int j=0;j<=joc.n+1;j++)
            {
                if (joc.tabla[i][j]==1)
                    valoriInTablaJucator1++;
                else if(joc.tabla[i][j]==2)
                    valoriInTablaJucator2++;
            }
    if(jucator==1)
        if(valoriInTablaJucator2==7)///daca nr-ul de aparitii din matrice ale celuilalt jucator sunt 0, jucatorul a castigat
        {
            return true;
        }
        else
            return false;
    else
        if(valoriInTablaJucator1==7)
            {
                return true;
            }
            else
                return false;
}

int butonApasatMeniu(int x, int y, int &click)
{
    int nrButon;
    if(x>((joc.lungimeFereastra-300)/2) && x<((joc.lungimeFereastra-320)/2+300) && y>0.4*joc.inaltimeFereastra && y<0.5*joc.inaltimeFereastra)///daca am apasat buton1
    {
            click=true;///daca ai apasat click unde trebuie, click devine true, altfel se repeta continuu in bucla
            nrButon=1;
    }
    else if (x>((joc.lungimeFereastra-300)/2) && x<((joc.lungimeFereastra-320)/2+300) && y>0.6*joc.inaltimeFereastra && y<0.7*joc.inaltimeFereastra)///daca am apasat buton2
    {
            click=true;///daca ai apasat click unde trebuie, click devine true, altfel se repeta continuu in bucla
            nrButon=2;
    }
    else if (x>((joc.lungimeFereastra-300)/2) && x<((joc.lungimeFereastra-320)/2+300) && y>0.8*joc.inaltimeFereastra && y<0.9*joc.inaltimeFereastra)///daca am apasat buton3
    {
            click=true;///daca ai apasat click unde trebuie, click devine true, altfel se repeta continuu in bucla
            nrButon=3;
    }
    return nrButon;
}

void optiune1Meniu()
{
    readimagefile("menuu.jpg",0, 0, joc.lungimeFereastra,joc.inaltimeFereastra);
    //readimagefile("MUSICOFF_ICON.gif",(joc.lungimeFereastra-100)/2, 0.45*joc.inaltimeFereastra,(joc.lungimeFereastra-100)/2+100, 0.55*joc.inaltimeFereastra);
    readimagefile("pvp.gif",(joc.lungimeFereastra-200)/2, 0.35*joc.inaltimeFereastra,(joc.lungimeFereastra-200)/2+200, 0.45*joc.inaltimeFereastra);
    readimagefile("pvc.gif",(joc.lungimeFereastra-200)/2, 0.55*joc.inaltimeFereastra,(joc.lungimeFereastra-200)/2+200, 0.65*joc.inaltimeFereastra);
    //readimagefile("previous_icon.gif",joc.lungimeFereastra-(200+10),10,joc.lungimeFereastra-10,200+10);
    bool click=false;
        while (!click)
        {
            if(ismouseclick(WM_LBUTTONDOWN) && !click )
            {
                clearmouseclick(WM_LBUTTONDOWN);
                int x=mousex(); int y=mousey();
                if(x>(joc.lungimeFereastra-200)/2 && x<(joc.lungimeFereastra-200)/2+200 && y>0.35*joc.inaltimeFereastra && y<0.45*joc.inaltimeFereastra)///daca am apasat pe butonul pvp
                {

                    joc.modJucator=1;
                    click=true;
                }
                else if(x>(joc.lungimeFereastra-200)/2 && x<(joc.lungimeFereastra-200)/2+200 && y>0.55*joc.inaltimeFereastra && y<0.65*joc.inaltimeFereastra)///daca am apasat pe butonul pvc
                {
                    joc.modJucator=2;
                    click=true;
                }
                else if(x>joc.lungimeFereastra-(200+10) && x<joc.lungimeFereastra-10 && y>10 && y<(200+10) )///daca am apasat pe previous, va iesi din meniu
                {
                    click=true;///daca ai apasat click unde trebuie, click devine true, altfel se repeta continuu in bucla
                    cleardevice();///aici am golit fereastra
                }
            }
        }
}

void optiune2Meniu()
{
    readimagefile("menuu.jpg",0, 0, joc.lungimeFereastra,joc.inaltimeFereastra);
    readimagefile("info.gif",(joc.lungimeFereastra-400)/2,(joc.inaltimeFereastra-400)/2,(joc.lungimeFereastra-400)/2+400,(joc.inaltimeFereastra+400)/2);
    readimagefile("previous_icon.gif",joc.lungimeFereastra-(200+10),10,joc.lungimeFereastra-10,200+10);
    bool click=false;
    while (!click)
    {
        if(ismouseclick(WM_LBUTTONDOWN) && !click )
        {
            clearmouseclick(WM_LBUTTONDOWN);
            int x=mousex(); int y=mousey();
            click=true;
            cleardevice();///aici am golit fereastra
        }
    }
}

void setariVolum()
{
    readimagefile("menuu.jpg",0, 0, joc.lungimeFereastra,joc.inaltimeFereastra);
    //readimagefile("MUSICOFF_ICON.gif",(joc.lungimeFereastra-100)/2, 0.45*joc.inaltimeFereastra,(joc.lungimeFereastra-100)/2+100, 0.55*joc.inaltimeFereastra);
    readimagefile("MUSIC_ICON.gif",(joc.lungimeFereastra-90)/2, 0.35*joc.inaltimeFereastra,(joc.lungimeFereastra-90)/2+90, 0.45*joc.inaltimeFereastra);
    readimagefile("MUSICOFF_ICON.gif",(joc.lungimeFereastra-90)/2, 0.55*joc.inaltimeFereastra,(joc.lungimeFereastra-90)/2+90, 0.65*joc.inaltimeFereastra);
    readimagefile("previous_icon.gif",joc.lungimeFereastra-(200+10),10,joc.lungimeFereastra-10,200+10);
    bool click=false;
        while (!click)
        {
            if(ismouseclick(WM_LBUTTONDOWN) && !click )
            {
                clearmouseclick(WM_LBUTTONDOWN);
                int x=mousex(); int y=mousey();
                if(x>(joc.lungimeFereastra-90)/2 && x<(joc.lungimeFereastra-90)/2+90 && y>0.35*joc.inaltimeFereastra && y<0.45*joc.inaltimeFereastra)///daca am apasat pe butonul muzica activata
                {
                    PlaySound(TEXT("sound1.wav"), NULL,SND_ASYNC);
                }
                else if(x>(joc.lungimeFereastra-90)/2 && x<(joc.lungimeFereastra-90)/2+90 && y>0.55*joc.inaltimeFereastra && y<0.65*joc.inaltimeFereastra)///daca am apasat pe butonul muzica dezactivata
                {
                    PlaySound(TEXT("silent.wav"), NULL,SND_ASYNC);
                }
                else if(x>joc.lungimeFereastra-(200+10) && x<joc.lungimeFereastra-10 && y>10 && y<(200+10) )///daca am apasat pe return, va iesi din setari
                {
                    click=true;///daca ai apasat click unde trebuie, click devine true, altfel se repeta continuu in bucla
                    cleardevice();///aici am golit fereastra
                }
            }
        }
}

void setariGrafica()
{
    readimagefile("menuu.jpg",0, 0, joc.lungimeFereastra,joc.inaltimeFereastra);
   // readimagefile("MUSICOFF_ICON.gif",(joc.lungimeFereastra-100)/2, 0.45*joc.inaltimeFereastra,(joc.lungimeFereastra-100)/2+100, 0.55*joc.inaltimeFereastra);
    readimagefile("800x800.gif",(joc.lungimeFereastra-300)/2, 0.35*joc.inaltimeFereastra,(joc.lungimeFereastra-300)/2+300, 0.45*joc.inaltimeFereastra);
    readimagefile("fullscreen.gif",(joc.lungimeFereastra-300)/2, 0.55*joc.inaltimeFereastra,(joc.lungimeFereastra-300)/2+300, 0.65*joc.inaltimeFereastra);
    readimagefile("previous_icon.gif",joc.lungimeFereastra-(200+10),10,joc.lungimeFereastra-10,200+10);
    bool click=false;
        while (!click)
        {
            if(ismouseclick(WM_LBUTTONDOWN) && !click )
            {
                clearmouseclick(WM_LBUTTONDOWN);
                int x=mousex(); int y=mousey();
                if(x>(joc.lungimeFereastra-300)/2 && x<(joc.lungimeFereastra-300)/2+300 && y>0.35*joc.inaltimeFereastra && y<0.45*joc.inaltimeFereastra)///daca am apasat pe butonul 800x800
                {
                    int lungimeSiLatimeFereastraAux=800;
                    FILE *fptr;///am scris intr-un fisier lungimea si inaltimea ferestrei si m am gandit sa pornesc iar jocul cu datela din fisier
                    fptr=fopen("newprogram.txt","w");
                    if(fptr == NULL)
                    {
                        cout<<"eroare";
                        exit(1);
                    }
                    fprintf(fptr,"%d",lungimeSiLatimeFereastraAux);
                    fclose(fptr);
                    joc.schimbareGrafica=true;
                }
                else if(x>(joc.lungimeFereastra-300)/2 && x<(joc.lungimeFereastra-300)/2+300 && y>0.55*joc.inaltimeFereastra && y<0.65*joc.inaltimeFereastra)///daca am apasat pe butonul fullscreen
                {
                    FILE *fptr;///am scris intr-un fisier lungimea si inaltimea ferestrei diferite de 800 ca sa nu porneasca jocul pe 800x800
                    fptr=fopen("newprogram.txt","w");
                    if(fptr == NULL)
                    {
                        cout<<"eroare";
                        exit(1);
                    }
                    fprintf(fptr,"%d",1);///am scris 1 in fisier ca sa inceapa in fullscreen la verificarea conditiei de a fi scris in fisier 800
                    fclose(fptr);
                    joc.schimbareGrafica=true;
                }
                else if(x>joc.lungimeFereastra-(200+10) && x<joc.lungimeFereastra-10 && y>10 && y<(200+10) )///daca am apasat pe return, va iesi din setari
                {
                    click=true;///daca ai apasat click unde trebuie, click devine true, altfel se repeta continuu in bucla
                    cleardevice();///aici am golit fereastra
                }
            }
        }
}
void optiune3Meniu()
{
    readimagefile("menuu.jpg",0, 0, joc.lungimeFereastra,joc.inaltimeFereastra);
    //readimagefile("MUSICOFF_ICON.gif",(joc.lungimeFereastra-100)/2, 0.45*joc.inaltimeFereastra,(joc.lungimeFereastra-100)/2+100, 0.55*joc.inaltimeFereastra);
    readimagefile("grafica.gif",(joc.lungimeFereastra-300)/2, 0.35*joc.inaltimeFereastra,(joc.lungimeFereastra-300)/2+300, 0.45*joc.inaltimeFereastra);
    readimagefile("sonor.gif",(joc.lungimeFereastra-300)/2, 0.55*joc.inaltimeFereastra,(joc.lungimeFereastra-300)/2+300, 0.65*joc.inaltimeFereastra);
    readimagefile("previous_icon.gif",joc.lungimeFereastra-(200+10),10,joc.lungimeFereastra-10,200+10);
    bool click=false;
        while (!click)
        {
            if(ismouseclick(WM_LBUTTONDOWN) && !click )
            {
                clearmouseclick(WM_LBUTTONDOWN);
                int x=mousex(); int y=mousey();
                if(x>(joc.lungimeFereastra-300)/2 && x<(joc.lungimeFereastra-300)/2+300 && y>0.35*joc.inaltimeFereastra && y<0.45*joc.inaltimeFereastra)///daca am apasat pe butonul grafica
                {
                    setariGrafica();
                    optiune3Meniu();
                    click=true;
                }
                else if(x>(joc.lungimeFereastra-300)/2 && x<(joc.lungimeFereastra-300)/2+300 && y>0.55*joc.inaltimeFereastra && y<0.65*joc.inaltimeFereastra)///daca am apasat pe butonul volum
                {
                    setariVolum();
                    optiune3Meniu();
                    click=true;
                }
                else if(x>joc.lungimeFereastra-(200+10) && x<joc.lungimeFereastra-10 && y>10 && y<(200+10) )///daca am apasat pe return, va iesi din setari
                {
                    click=true;///daca ai apasat click unde trebuie, click devine true, altfel se repeta continuu in bucla
                    cleardevice();///aici am golit fereastra
                }
            }
        }
}

void meniuPrincipal()
{
    int click=false;
    readimagefile("menuu.jpg",0, 0, joc.lungimeFereastra,joc.inaltimeFereastra);
    readimagefile("titlu.gif",(joc.lungimeFereastra-400)/2, 0.1*joc.inaltimeFereastra,(joc.lungimeFereastra-400)/2+400, 0.3*joc.inaltimeFereastra);
    readimagefile("play.gif",(joc.lungimeFereastra-300)/2, 0.4*joc.inaltimeFereastra,(joc.lungimeFereastra-300)/2+300, 0.5*joc.inaltimeFereastra);
    readimagefile("help.gif",(joc.lungimeFereastra-300)/2, 0.6*joc.inaltimeFereastra,(joc.lungimeFereastra-300)/2+300, 0.7*joc.inaltimeFereastra);
    readimagefile("SETTING_BUTTON.gif",(joc.lungimeFereastra-300)/2, 0.8*joc.inaltimeFereastra,(joc.lungimeFereastra-300)/2+300, 0.9*joc.inaltimeFereastra);
   // settextjustify(CENTER_TEXT, CENTER_TEXT);
    //outtextxy(getmaxx()/2,jos/2, "Apasati CLICK pentru a incepe");
    while (!click)
        {
            if(ismouseclick(WM_LBUTTONDOWN) && !click )
            {
                clearmouseclick(WM_LBUTTONDOWN);
                int x=mousex(); int y=mousey();
                butonApasatMeniu(x,y,click);
            }
        }
        cleardevice();///aici am golit fereastra
        int x=mousex(); int y=mousey();
        if(butonApasatMeniu(x,y,click)==1)///am apasat primul buton din meniu
        {
             optiune1Meniu();
             //meniuPrincipal();
             joc.finalMeniu=1;
        }
        else if(butonApasatMeniu(x,y,click)==2)///am apasat al doilea buton din meniu
        {
             optiune2Meniu();
             meniuPrincipal();
             joc.finalMeniu=1;
        }
        else if(butonApasatMeniu(x,y,click)==3)///am apasat al treilea buton din meniu
        {
             optiune3Meniu();
             meniuPrincipal();
             joc.finalMeniu=1;
        }

}
void iesireInMeniuPrincipal()
{
    readimagefile("meniu.gif",joc.lungimeFereastra-(200+10),10,joc.lungimeFereastra-10,106+10);
}

void cineMuta1()
{
    readimagefile("piesa alba optimizat.gif", (joc.lungimeFereastra-(joc.stanga/2)), 0.25*joc.inaltimeFereastra, (joc.lungimeFereastra-(joc.stanga/2))+joc.latura, 0.25*joc.inaltimeFereastra+joc.latura);
}

void cineMuta2()
{
    readimagefile("piesa neagra optimizat.gif", (joc.lungimeFereastra-(joc.stanga/2)), 0.25*joc.inaltimeFereastra, (joc.lungimeFereastra-(joc.stanga/2))+joc.latura, 0.25*joc.inaltimeFereastra+joc.latura);

}

void afisareMatrice()
{
    for( int i=0;i<=joc.n+1;i++ )
    {
        for( int j=0;j<=joc.m+1;j++ )
        {
            cout<<joc.tabla[i][j]<<" ";
        }
        cout<<endl;
    }
    cout<<endl;
}

void deseneazaBordura()
{
    readimagefile("sus.gif", joc.stanga-joc.latura*0.9, joc.sus-joc.latura*0.9, joc.dreapta+joc.latura*0.9, joc.sus);
    readimagefile("jos.gif", joc.stanga-joc.latura*0.9, joc.jos, joc.dreapta+joc.latura*0.9, joc.jos+joc.latura*0.9);
    readimagefile("stanga.gif", joc.stanga-joc.latura*0.9, joc.sus-joc.latura*0.9, joc.stanga, joc.jos+joc.latura*0.9);
    readimagefile("dreapta.gif", joc.dreapta, joc.sus-joc.latura*0.9, joc.dreapta+joc.latura*0.9, joc.jos+joc.latura*0.9);
}

void functiaJocului()
{
    while(true)
    {
        //initwindow(joc.lungimeFereastra,joc.inaltimeFereastra,"titlu");
        //lungimeSiInaltimeFereastra();
        PlaySound(TEXT("sound1.wav"), NULL,SND_ASYNC);
        meniuPrincipal();
        if(joc.schimbareGrafica)
            {
                joc.schimbareGrafica=false;
                closegraph();
                lungimeSiInaltimeFereastra();
                initwindow(joc.lungimeFereastra,joc.inaltimeFereastra,"titlu");
                continue;
            }
        if(joc.finalMeniu)
        {
            readimagefile("menuu.jpg",0, 0, joc.lungimeFereastra,joc.inaltimeFereastra);///background
            deseneazaBordura();
            desenareTot();
            afiseazaScor(-1);
            iesireInMeniuPrincipal();//butonul de exit ce duce in meniu
            do
            {

                  if(joc.modJucator==1)
                  {
                        cout<<"mod111"<<endl;
                        //incepe piesa 1
                        cineMuta1();
                        if(!castigat(1) && !castigat(2))///daca nu a castigat nimeni, face mutarea piesei 1
                        {
                            mutarePiesa(1);
                            afisareMatrice();
                        }
                        else
                            break;
                        //incepe piesa 2
                        cineMuta2();
                        if(!castigat(1) && !castigat(2))///daca nu a castigat nimeni, face mutarea piesei 2
                        {
                            mutarePiesa(2);
                            afisareMatrice();
                        }
                        else
                            break;
                        cout<<endl<<castigat(1)<<" "<<castigat(2)<<endl;
                  }
                  else if(joc.modJucator==2)
                  {

                        //incepe piesa 1
                        //cineMuta1();
                        if(!castigat(2))///daca nu a castigat 2, face mutarea piesei 1
                            mutarePiesa1(1);
                        else
                            break;
                        afisareMatrice();
                        //incepe piesa 2
                        cineMuta2();
                        if(!castigat(1))///daca nu a castigat 1, face mutarea piesei 2
                            mutarePiesa1(2);
                        else
                            break;
                        afisareMatrice();

                  }
            }
            while (!castigat(1) && !castigat(2));///el asteapta o mutare piesa 2, de aia nu iese din while, dar piese nu mai poate muta daca nu exista
            //readimagefile("confetti.gif",joc.stanga, joc.sus, joc.dreapta, joc.jos);
            PlaySound(TEXT("won.wav"), NULL,SND_ASYNC);
            afiseazaCastigator();
            desenareAproapeTot();
            readimagefile("you-win-animation0013.gif",(joc.stanga+(joc.n*joc.latura)/2)-275, 0.35*joc.inaltimeFereastra,(joc.stanga+(joc.n*joc.latura)/2)+275, 0.65*joc.inaltimeFereastra);
            if(castigat(1)==1)///daca a castigat alb
                readimagefile("piesa-alba-optimizat1.gif",(joc.stanga+(joc.n*joc.latura)/2)-50, 0.4*joc.inaltimeFereastra,(joc.stanga+(joc.n*joc.latura)/2)+50, 0.5*joc.inaltimeFereastra);
            else
                readimagefile("piesa-neagra-optimizat1.gif",(joc.stanga+(joc.n*joc.latura)/2)-50, 0.4*joc.inaltimeFereastra,(joc.stanga+(joc.n*joc.latura)/2)+50, 0.5*joc.inaltimeFereastra);

            iesireInMeniuPrincipal();
            ///mai jos se deseneaza iar butonul de exit
            bool click=false;
            while (!click)
            {
                if(ismouseclick(WM_LBUTTONDOWN) && !click )
                {
                    clearmouseclick(WM_LBUTTONDOWN);
                    int x=mousex(); int y=mousey();
                    if(x>joc.lungimeFereastra-(200+10) && x<joc.lungimeFereastra-10 && y>10 && y<(200+10) )///daca am apasat pe return, va iesi din setari
                    {
                        click=true;///daca ai apasat click unde trebuie, click devine true, altfel se repeta continuu in bucla
                        cleardevice();///aici am golit fereastra
                        PlaySound(TEXT("silence.wav"), NULL,SND_ASYNC);///am scos sunetul
                    }
                }
            }
            ///mai jos am resetat matricea si scorul
            resetareMatrice();
            resetareScor();
        }

    }
    getch();
    closegraph();
}


void incarcareJoc()
{
    outtextxy((joc.lungimeFereastra-70)/2, 0.55*joc.inaltimeFereastra, "Loading...");
    rectangle((joc.lungimeFereastra-300)/2, 0.4*joc.inaltimeFereastra,(joc.lungimeFereastra-300)/2+300, 0.45*joc.inaltimeFereastra);
    for(int i=0;i<299;i++)
    {
        setcolor(RGB(255, 87, 51));
        rectangle((joc.lungimeFereastra-300)/2+1, 0.4*joc.inaltimeFereastra+1,(joc.lungimeFereastra-300)/2+1+i, 0.45*joc.inaltimeFereastra -1);
        delay(1);
    }
}

int main()
{
    lungimeSiInaltimeFereastra();
    initwindow(joc.lungimeFereastra,joc.inaltimeFereastra,"titlu");
    incarcareJoc();
    functiaJocului();
    return 0;
}






