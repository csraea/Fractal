#define _DEFAULT_SOURCE

#include <stdio.h>
#include <ncurses.h>
#include <unistd.h>
#include <stdlib.h>
#include <time.h>

void printPeaks(int startY, int startX);
void renderPoint(int startY, int startX);
void destroyPoint(int startY, int startX);
void makeFractal(int itNum, int Ay, int Ax, int By, int Bx, int Cy, int Cx, int Dy, int Dx);

int main(){
	int itNum;
	scanf("%d", &itNum);
	srand(time(NULL));
	initscr();
	noecho();
	cbreak();
	start_color();
	curs_set(0);
	keypad(stdscr, TRUE);

	int startY = LINES / 2;
	int startX = COLS / 2;
	int Ax, Ay, Bx, By, Cx, Cy, Dy, Dx;

	init_pair(1, COLOR_CYAN, COLOR_BLACK);

	attron(COLOR_PAIR(1));
	wbkgd(stdscr,COLOR_PAIR(1));

	//determining important coordinates *
	printPeaks(startY, startX);
	getyx(stdscr, Ay, Ax);
	printPeaks(startY, startX);
	getyx(stdscr, By, Bx);
	printPeaks(startY, startX);
	getyx(stdscr, Cy, Cx);


	attroff(COLOR_PAIR(1));
	printPeaks(startY, startX);
	getyx(stdscr, Dy, Dx);
	makeFractal(itNum, Ay, Ax, By, Bx, Cy, Cx, Dy, Dx);


	getch();
	endwin();
}

void printPeaks(int startY, int startX) {
	int but;
	renderPoint(startY, startX);
	init_pair(1, COLOR_WHITE, COLOR_BLACK);
	init_pair(2, COLOR_CYAN, COLOR_BLACK);
	while((but = getch()) != KEY_F(1)){
		attron(COLOR_PAIR(1) | A_BOLD);
		mvprintw(0, 0, "Max-y: %d\nMax-x: %d\nCoordinates are: (%d;%d)", LINES, COLS, startY, startX);
		attroff(COLOR_PAIR(1) | A_BOLD);
		attron(COLOR_PAIR(2));
		switch(but) {
			case KEY_LEFT :
				destroyPoint(startY, startX);
				startX = (startX > 1) ? startX : 1;
				renderPoint(startY, --startX);
				break;
			case KEY_RIGHT : 
				destroyPoint(startY, startX);
				startX = (startX == COLS - 1) ? COLS - 2 : startX;
				renderPoint(startY, ++startX);
				break;
			case KEY_UP :
				destroyPoint(startY, startX);
				startY = (startY > 1) ? startY : 1;
				renderPoint(--startY, startX);
				break;
			case KEY_DOWN :
				destroyPoint(startY, startX);
				startY = (startY == LINES - 1) ? LINES - 2 : startY;
				renderPoint(++startY, startX);
				break;				
		}
	}
}

void renderPoint(int startY, int startX) {
	attron(A_BOLD);
	mvprintw(startY, startX, "*");
	refresh();
}

void destroyPoint(int startY, int startX) {
	mvprintw(startY, startX, " ");
	refresh();
}

void makeFractal(int itNum, int Ay, int Ax, int By, int Bx, int Cy, int Cx, int Dy, int Dx){
	mvprintw(0, 0, "\n\n\n");
	init_pair(2, COLOR_WHITE, COLOR_BLACK);
	wbkgd(stdscr,COLOR_PAIR(2));
	int randNum, remainder;
	for(int i = 1; i <= itNum; i++){
		randNum = rand();
		remainder = randNum % 3;
		switch (remainder) {
			case 0 :
				Dy = (Ay + Dy)/2;
				Dx = (Ax + Dx)/2;
				renderPoint(Dy, Dx);
				break;
			case 1 :
				Dy = (By + Dy)/2;
				Dx = (Bx + Dx)/2;
				renderPoint(Dy, Dx);
				break;		
			case 2 :
				Dy = (Cy + Dy)/2;
				Dx = (Cx + Dx)/2;
				renderPoint(Dy, Dx);
				break;		
		}
		attron(COLOR_PAIR(2) | A_BOLD);
		mvprintw(1, 0, " Iterations: %d", i);
		attroff(COLOR_PAIR(2) | A_BOLD);
		sleep(1);
	}
}