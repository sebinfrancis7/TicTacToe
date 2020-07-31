#include <stdio.h>
#include <conio.h>
#include <stdlib.h>
#include <graphics.h>
#include <string.h>
#include <time.h>
#include <dos.h>

int d = 35, s = 30, f = 200;
//d=distance s=size f=offset

char grid[3][3];

int menu();
void help();
void game();
int getkey();				 //To capture arrow keys pressed
void display(int, int);		 //To display grid
int checkWin(int, int, int); //Check win; return 1 if any one of two players win else 0
int checkDraw(int, int);	 //Check draw; return 1 if draw else 0
void end(char *);			 //Game end
void animate(int, int);		 //Show Blinking and Fill animation
void smiley(char *);		 //Show Winner screen

void main()
{
	int gd, gm, sm, i, j, y = 130, off = 10;
	detectgraph(&gd, &gm); //detect graphics driver and graphics mode
	initgraph(&gd, &gm, "C:\\TURBOC3\\BGI"); 

	for (i = 7; i >= 5; i--)
	{
		cleardevice();
		settextstyle(DEFAULT_FONT, HORIZ_DIR, i);  //(font, direction, font size)
		settextjustify(CENTER_TEXT, CENTER_TEXT); 	//((left/center/right), (top/center/bottom))
		outtextxy(getmaxx() / 2, y, "TIC-TAC-TOE");
		y = y + off;
		delay(500);
	}
	cleardevice();
	settextstyle(DEFAULT_FONT, HORIZ_DIR, 2);

	for (i = 0; i < 3; i++) //Initialize grid with blank spaces
		for (j = 0; j < 3; j++)
			grid[i][j] = ' ';

	sm = menu();
	if (sm)
		game();
	return;
}
/* Special keys such as arrow keys send 2 characters
first 0 to indicate that the next character is input from a special key
so we require 2 getch for arrow keys */
int getkey() //modified getch()
{
	int ch;
	ch = getch();
	if (ch == 0)
	{
		ch = getch();
		return (ch);
	}
	return (ch);
}

void display(int sx, int sy)
{
	int i, j;
	char str[2];
	for (i = 0; i < 3; i++)
	{
		for (j = 0; j < 3; j++)
		{
			if (j == sx && i == sy) //If the cell is selected cell
				setcolor(RED);
			else
				setcolor(WHITE); //For non-selected cell
			rectangle(j * d + f, i * d + f, j * d + s + f, i * d + s + f);
			sprintf(str, "%c", grid[i][j]); //To print Player's symbol in cell
			outtextxy(j * d + 8 + f, i * d + 8 + f, str);
		}
	}
}

int checkWin(int sx, int sy, int player)
{
	char str[25];
	int i = sx, j;
	i = sy;
	for (i = 0; i < 3; i++)
	{
		if ((grid[0][i] == grid[1][i] && grid[0][i] == grid[2][i] && grid[0][i] != ' '))
		{
			display(-1, -1);
			while (!kbhit()) // used to determine if a key has been pressed or not
				animate(1, i);
			getkey();
			sprintf(str, "Player %d (%c) You Won!!!", player + 1, player ? 'O' : 'X');
			while (!kbhit())
				smiley(str);
			getkey();
			end(str);
			return (1);
		}

		if ((grid[i][0] == grid[i][1] && grid[i][0] == grid[i][2] && grid[i][0] != ' '))
		{
			display(-1, -1);
			while (!kbhit())
				animate(0, i);
			getkey();
			sprintf(str, "Player %d (%c) You Won!!!", player + 1, player ? 'O' : 'X');
			while (!kbhit())
				smiley(str);
			getkey();
			end(str);
			return (1);
		}
	}
	if ((grid[0][0] == grid[1][1] && grid[1][1] == grid[2][2] && grid[2][2] != ' '))
	{
		display(-1, -1);
		while (!kbhit())
			animate(2, 0);
		getkey();
		sprintf(str, "Player %d (%c) You Won!!!", player + 1, player ? 'O' : 'X');
		while (!kbhit())
			smiley(str);
		getkey();
		end(str);
		return (1);
	}

	if ((grid[0][2] == grid[1][1] && grid[1][1] == grid[2][0] && grid[2][0] != ' '))
	{
		display(-1, -1);
		while (!kbhit())
			animate(3, 0);
		getkey();
		sprintf(str, "Player %d (%c) You Won!!!", player + 1, player ? 'O' : 'X');
		while (!kbhit())
			smiley(str);
		getkey();
		end(str);
	}
	return (0);
}

void animate(int type, int i)
{
	int j;
	char str[2];
	setlinestyle(SOLID_LINE, 0, THICK_WIDTH);
	switch (type)
	{
	case 0: //row
		for (j = 0; j < 3; j++)
		{
			setcolor(BLACK);
			rectangle(j * d + f, i * d + f, j * d + s + f, i * d + s + f);
			delay(100);
			setcolor(GREEN);
			rectangle(j * d + f, i * d + f, j * d + s + f, i * d + s + f);
			delay(100);
			setcolor(WHITE);
			rectangle(j * d + f, i * d + f, j * d + s + f, i * d + s + f);
			delay(100);
		}
		for (j = 0; j < 3; j++)
		{
			setfillstyle(SOLID_FILL, BLACK);
			floodfill(j * d + f + 2, i * d + f + 2, WHITE);
			setfillstyle(SOLID_FILL, GREEN); //(pattern, color)
			floodfill(j * d + f + 2, i * d + f + 2, WHITE); //(x, y, border)
		}
		delay(300);
		for (j = 0; j < 3; j++)
		{
			sprintf(str, "%c", grid[i][j]);
			setcolor(BLUE);
			outtextxy(j * d + 8 + f, i * d + 8 + f, str);
		}
		break;
	case 1: //column
		for (j = 0; j < 3; j++)
		{
			setcolor(BLACK);
			rectangle(i * d + f, j * d + f, i * d + s + f, j * d + s + f);
			delay(100);
			setcolor(GREEN);
			rectangle(i * d + f, j * d + f, i * d + s + f, j * d + s + f);
			delay(100);
			setcolor(WHITE);
			rectangle(i * d + f, j * d + f, i * d + s + f, j * d + s + f);
			delay(100);
		}
		for (j = 0; j < 3; j++)
		{
			setfillstyle(SOLID_FILL, BLACK);
			floodfill(i * d + f + 2, j * d + f + 2, WHITE);
			setfillstyle(SOLID_FILL, GREEN);
			floodfill(i * d + f + 2, j * d + f + 2, WHITE);
		}
		delay(300);
		for (j = 0; j < 3; j++)
		{
			sprintf(str, "%c", grid[j][i]);
			setcolor(BLUE);
			outtextxy(i * d + 8 + f, j * d + 8 + f, str);
		}
		break;
	case 2: //primary diagonal
		for (i = 0; i < 3; i++)
		{
			setcolor(BLACK);
			rectangle(i * d + f, i * d + f, i * d + s + f, i * d + s + f);
			delay(100);
			setcolor(GREEN);
			rectangle(i * d + f, i * d + f, i * d + s + f, i * d + s + f);
			delay(100);
			setcolor(WHITE);
			rectangle(i * d + f, i * d + f, i * d + s + f, i * d + s + f);
			delay(100);
		}
		for (i = 0; i < 3; i++)
		{
			setfillstyle(SOLID_FILL, BLACK);
			floodfill(i * d + f + 2, i * d + f + 2, WHITE);
			setfillstyle(SOLID_FILL, GREEN);
			floodfill(i * d + f + 2, i * d + f + 2, WHITE);
		}
		delay(300);
		for (i = 0; i < 3; i++)
		{
			sprintf(str, "%c", grid[i][i]);
			setcolor(BLUE);
			outtextxy(i * d + 8 + f, i * d + 8 + f, str);
		}
		break;
	case 3: //secondary diagonal
		for (i = 0; i < 3; i++)
		{
			j = 2 - i;
			setcolor(BLACK);
			rectangle(j * d + f, i * d + f, j * d + s + f, i * d + s + f);
			delay(100);
			setcolor(GREEN);
			rectangle(j * d + f, i * d + f, j * d + s + f, i * d + s + f);
			delay(100);
			setcolor(WHITE);
			rectangle(j * d + f, i * d + f, j * d + s + f, i * d + s + f);
			delay(100);
		}
		for (i = 0; i < 3; i++)
		{
			j = 2 - i;
			setfillstyle(SOLID_FILL, BLACK);
			floodfill(j * d + f + 2, i * d + f + 2, WHITE);
			setfillstyle(SOLID_FILL, GREEN);
			floodfill(j * d + f + 2, i * d + f + 2, WHITE);
		}
		delay(300);
		for (i = 0; i < 3; i++)
		{
			j = 2 - i;
			sprintf(str, "%c", grid[i][j]);
			setcolor(BLUE);
			outtextxy(j * d + 8 + f, i * d + 8 + f, str);
		}

		break;
	}
	return;
}

int checkDraw(int sx, int sy)
{
	int i, j, k = 0;
	char str[25];
	for (i = 0; i < 3; i++)
		for (j = 0; j < 3; j++)
			if (grid[i][j] != ' ')
				k++;
	if (k == 9) //All cells marked but yet no win i.e. Draw
	{
		display(sx, sy);
		getkey();
		sprintf(str, "Its a Tie!!!");
		smiley(str);
		getkey();
		end(str);
		return (1);
	}
	return (0);
}

void end()
{
	// delay(80);
	cleardevice();
	setcolor(WHITE);
	settextjustify(CENTER_TEXT, CENTER_TEXT);
	outtextxy(getmaxx() / 2, 200, "THANK YOU FOR PLAYING!!");
	outtextxy(getmaxx() / 2, 250, "HOPE TO SEE YOU AGAIN SOON");
	getkey();
	closegraph();
	return;
}

void smiley(char *str)
{
	cleardevice();
	setcolor(YELLOW);
	circle(325, 100, 25);
	setfillstyle(SOLID_FILL, YELLOW);
	floodfill(325, 100, YELLOW);
	setcolor(BLACK);
	setfillstyle(SOLID_FILL, BLACK);
	fillellipse(319, 85, 3, 1); //(x ,y ,xradius, yradius)
	fillellipse(331, 85, 3, 1);
	ellipse(325, 100, 205, 335, 20, 9); //(x , y , start angle, end angle, xradius, yradius)
	ellipse(325, 100, 205, 335, 20, 10);
	ellipse(325, 100, 205, 335, 20, 11);
	delay(200);

	setcolor(BLACK);
	setfillstyle(SOLID_FILL, BLACK);
	fillellipse(319, 85, 2, 6);
	fillellipse(331, 85, 2, 6);
	delay(500);
	setcolor(WHITE);
	settextjustify(CENTER_TEXT, CENTER_TEXT);
	outtextxy(getmaxx() / 2, getmaxy() / 2, str);
	delay(800);
	return;
}

int menu()
{
	int sy = 0, items = 3, i, l = 90, b = 25; //length, depth
	int ofs = 275, gap_f = 35, t_ofs = 13;	  // offset, gap_factor, text_offset
	char ch, menu[3][20] = {
				 "Start",
				 "Help",
				 "Exit",
			 };
	settextjustify(CENTER_TEXT, CENTER_TEXT);
	while (1)
	{
		cleardevice();
		for (i = 0; i < items; i++)
		{
			setcolor(WHITE);
			settextstyle(DEFAULT_FONT, HORIZ_DIR, 5);
			outtextxy(getmaxx() / 2, 150, "TIC-TAC-TOE");
			settextstyle(DEFAULT_FONT, HORIZ_DIR, 1);
			if (i == sy)
				setcolor(RED);
			else
				setcolor(WHITE);

			rectangle(ofs, i * gap_f + ofs,l + ofs, i * gap_f + b + ofs);
			outtextxy(getmaxx() / 2, i * gap_f + t_ofs + ofs, menu[i]);
		}

		ch = getkey();
		switch (ch)
		{
		case 72: //up arrow
			if (sy > 0)
				sy--;
			break;

		case 80: //down arrow
			if (sy < items - 1)
				sy++;
			break;
		case 13:
		case ' ':
			switch (sy)
			{
			case 0:
				return 1;
			case 1:
				help();
				break;
			case 2:
				return 0;
			default:
				break;
			}

		default:
			break;
		}
	}
}

void help()
{
	settextstyle(DEFAULT_FONT, HORIZ_DIR, 2);
	cleardevice();
	setcolor(WHITE);
	outtextxy(getmaxx() / 2, 200, "Press Space or Enter key to select cells");
	outtextxy(getmaxx() / 2, 220, "Press e to exit");
	setcolor(RED);
	outtextxy(getmaxx() / 2, 240, "Press any key to continue.");
	getkey();
	return;
}

void game()
{
	int sx = 0, sy = 0, i, j, k, count = 2, player;
	char str[25], ch;
	settextjustify(LEFT_TEXT, TOP_TEXT);
	settextstyle(DEFAULT_FONT, HORIZ_DIR, 2); //Initialize text style
	while (1)
	{
		cleardevice();
		setcolor(BLUE);
		outtextxy(175, 150, "TIC-TAC-TOE");
		player = count % 2;
		sprintf(str, "Player : %d (%c)", player + 1, player ? 'O' : 'X');
		setcolor(WHITE);
		outtextxy(350, 250, str);
		display(sx, sy);
		ch = getkey();
		switch (ch)
		{
		case 72: //up arrow
			if (sy != 0)
				sy--;
			break;
		case 80: //down arrow
			if (sy != 2)
				sy++;
			break;
		case 75: //left arrow
			if (sx != 0)
				sx--;
			break;
		case 77: //right arrow
			if (sx != 2)
				sx++;
			break;
		case 13:
		case ' ':
			if (grid[sy][sx] == ' ')
			{
				if (player == 0)
					grid[sy][sx] = 'X';
				else
					grid[sy][sx] = 'O';
				count++;
			}
			break;
		case 'e':
		case 'E':
			cleardevice();
			closegraph();
			return;
		default:
			break;
		}
		if (checkWin(sx, sy, player) == 1 || checkDraw(sx, sy) == 1)
			break;
	}
	return;
}
