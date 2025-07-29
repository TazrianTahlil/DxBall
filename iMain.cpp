#include "iGraphics.h"
#include "iSound.h"

void homePage();
void gamePage();
void gamePage1();
void gamePage2();
void gamePage3();
void gamePage4();
void ballChange1();
void aboutPage();
void scorePage();
void gameOverPage();
void victoryPage();
void initLevel2();
void initLevel3();
void initLevel4();
void saveUserName();
void loadUserName(int level);
void helpPage();
int channel = -1;
//******flags */
int hp = 1;
int gp = 0;
int gp1 = 0;
int ap = 0;
int ip = 0;
int sp = 0;
int gp2 = 0;
int gp3=0;
int gp4=0;
int currentLevel = 0;
int point1;
int life;
int gameOver = 0;
int victory = 0;
int delx = 2;
int dely = -2;
int counter = 0;
bool start = 0;
int total_player;
//this is for game level unlock feature .still i dont implement this in game,
bool level1Unlocked = false;
bool level2Unlocked = false;
bool level3Unlocked = false;
bool level4Unlocked = false;
bool musicOn = true;

char name[100];
char username[100];
char prev_names[6][100];
char prev_points[6][100];
char currentusername[100];

//about ball
int xBall = 500;
int yBall = 50;
int radiusBall = 10;
int dx = 7;
int dy = 5;
//about board
int xBoard = xBall - 50;
int yBoard = yBall - 20;
int dxBoard = 100;
int dyBoard = 10;
int minscore = -1;


//about tiles
struct tiles
{
    int cx;
    int cy;
    int show;
    char img[100];

};

tiles arr[350];


/*
function iDraw() is called again and again by the system.
*/


void saveName()
{
    FILE *fil = fopen("saves/names.txt", "a");
    fprintf(fil, "%s\n", name);
    char mmm[100];
    sprintf(mmm, "%d", point1);
    fprintf(fil, "%s\n", mmm);
    fclose(fil);
    FILE *file = fopen("saves/names.txt", "r");
    char k[100];
    fgets(k, 100, file);
    int t = atoi(k);
    for (int i = 0; i < t+1; i++)
    {
        if (fgets(prev_names[i], 100, file) == nullptr)
        {
            break;
        }
        if (fgets(prev_points[i], 100, file) == nullptr)
        {
            break;
        }
    }
    fclose(file);
    for (int i = 0; i < t + 1; i++)
    {
        for (int j = i + 1; j < t + 1; j++)
        {
            int a = atoi(prev_points[i]);
            int b = atoi(prev_points[j]);
            if (a < b)
            {
                char temp[100];
                int m = 0;
                while (prev_points[i][m] != '\0')
                {
                    temp[m] = prev_points[i][m];
                    m++;
                }
                temp[m] = '\0';
                m = 0;
                while (prev_points[j][m] != '\0')
                {
                    prev_points[i][m] = prev_points[j][m];
                    m++;
                }
                prev_points[i][m] = '\0';
                m = 0;
                while (temp[m] !='\0')
                {
                    prev_points[j][m] = temp[m];
                    m++;
                }
                prev_points[j][m] = '\0';
                m = 0;
                while (prev_names[i][m] != '\0')
                {
                    temp[m] = prev_names[i][m];
                    m++;
                }
                temp[m] = '\0';
                m = 0;
                while (prev_names[j][m] != '\0')
                {
                    prev_names[i][m] = prev_names[j][m];
                    m++;
                }
                prev_names[i][m] = '\0';
                m = 0;
                while (temp[m] !='\0')
                {
                    prev_names[j][m] = temp[m];
                    m++;
                }
                prev_names[j][m] = '\0';
            }
        }
    }
    char mew[100];
    if ( t + 1 > 5)
    {
        t = 5;
    }
    else
    {
        t = t + 1;
    }
    sprintf(mew, "%d", t);
    FILE *filee = fopen("saves/names.txt", "w");
    fputs(mew, filee);
    fputs("\n", filee);
    for (int i = 0; i < t; i++)
    {
        fputs(prev_names[i], filee);
        fputs(prev_points[i], filee);
    }
    fclose(filee);
}

void saveUserName()
{
    FILE *file = fopen("saves/usernames.txt", "r");
    int found = 0;
    while(1)
    {
        char prev_usernames[100];
        char prev_userlevels[100];
        if (fgets(prev_usernames, 100, file) == nullptr)
        {
            break;
        }
        if (fgets(prev_userlevels, 100, file) == nullptr)
        {
            break;
        }
        char user[100];
        strcpy(user, prev_usernames);
        user[strlen(prev_usernames) - 1] = '\0';
        if (strcmp(user, username) == 0) {
            int w = atoi(prev_userlevels);
            found = w;
            break;
        }
    }
    fclose(file);
    if (found == 0) {
        level1Unlocked = 1;
        FILE *fil = fopen("saves/usernames.txt", "a");
        fputs(username, fil);
        fputs("\n", fil);
        fputs("1\n", fil);
        fclose(fil);
    }
    else {
        if (found >= 1) {
            level1Unlocked = 1;
            level2Unlocked = 0;
            level3Unlocked = 0;
            level4Unlocked = 0;
        }
        if (found >= 2) {
            level2Unlocked = 1;
            level3Unlocked = 0;
            level4Unlocked = 0;
        }
        if (found >= 3) {
            level3Unlocked = 1;
            level4Unlocked = 0;
        }
        if (found >= 4) {
            level4Unlocked = 1;
        }
    }
}

void loadNames()
{
    FILE *file = fopen("saves/names.txt", "r");
    if (file == nullptr)
    {
        printf("Failed to open file\n");
        return;
    }
    char k[100];
    fgets(k, 100, file);
    total_player = atoi(k);
    for (int i = 0; i < total_player; i++)
    {
        if (fgets(prev_names[i], 100, file) == nullptr)
        {
            break;
        }
        if (fgets(prev_points[i], 100, file) == nullptr)
        {
            break;
        }
    }
    fclose(file);
    return;
}
void loadUserName(int level) {
    char user_name[1000][100];
    char user_level[1000][100];
    int cnt = 0;
    FILE *file = fopen("saves/usernames.txt", "r");
    while(1)
    {
        
        if (fgets(user_name[cnt], 100, file) == nullptr)
        {
            break;
        }
        if (fgets(user_level[cnt], 100, file) == nullptr)
        {
            break;
        }
        cnt++;
    }
    fclose(file);
    FILE *fil = fopen("saves/usernames.txt", "w");
    for (int i = 0; i < cnt; i++)
    {
        fputs(user_name[i], fil);
        char user[100];
        strcpy(user, user_name[i]);
        user[strlen(user_name[i]) - 1] = '\0';
        if (strcmp(user, currentusername) == 0) {
            int w = atoi(user_level[i]);
            if (w < level) {
                w = level;
            }
            char ki[100];
            sprintf(ki, "%d", w);
            fputs(ki, fil);
            fputs("\n", fil);
        }
        else {
            fputs(user_level[i], fil);
        }
        
    }
    fclose(fil);

}
void iDraw()
{
    iClear();
    if (gameOver == 1)
    {
        gameOverPage();
        return;
    }

    else if (victory == 1)
    {
        victoryPage();
        return;
    }

    if (hp == 1)
    {
        homePage();
        level1Unlocked = 0;
        level2Unlocked = 0;
        level3Unlocked = 0;
        level4Unlocked = 0;
    }
    else if (gp == 1)
    {
        gamePage();
    }
    else if (ap == 1)
    {
        aboutPage();
    }
    else if (sp == 1)
    {
        scorePage();
    }
    else if (gp1 == 1)
    {
        gamePage1();
    }
    else if (gp2 == 1)
    {
        gamePage2();
    }
    else if (gp3 == 1)
    {
        gamePage3();
    }
    else if (gp4 == 1)
    {
        gamePage4();

    }else if(ip==1){
        helpPage();
    }

    if (hp == 1) {
        for (int i = 0; i < 100; i++)
        {
                username[i] = '\0';
        }
    }
}



void homePage ()
{
    iShowImage(0, 0, "assets\\images\\bc.jpg");
    iShowImage(370, 500, "assets\\images\\button1.jpg");
    iShowImage(370, 400, "assets\\images\\button2.jpg");
    iShowImage(370, 300, "assets\\images\\button3.jpg");
    iShowImage(370, 200, "assets\\images\\button4.jpg");
    iShowImage(370, 100, "assets\\images\\button2.jpg");
    iShowImage(775, 23, "assets\\images\\button1.jpg");
    iSetColor(255, 255, 255);
    iText(851, 43, "EXIT", GLUT_BITMAP_TIMES_ROMAN_24);
    iText(450, 520, "Start", GLUT_BITMAP_TIMES_ROMAN_24);
    iText(450, 420, "About us", GLUT_BITMAP_TIMES_ROMAN_24);
    iText(450, 320, "Instruction", GLUT_BITMAP_TIMES_ROMAN_24);
    iText(450, 220, "Score", GLUT_BITMAP_TIMES_ROMAN_24);
    iText(420, 120, "Music On/Off", GLUT_BITMAP_TIMES_ROMAN_24);
    iSetColor(255,255,255);

}

void gamePage()
{
    iShowImage(0, 0, "assets\\images\\3.jpg");
    iShowImage(370, 500, "assets\\images\\button1.jpg");
    iShowImage(370, 400, "assets\\images\\button2.jpg");
    iShowImage(370, 300, "assets\\images\\button3.jpg");
    iShowImage(370, 200, "assets\\images\\button4.jpg");
    iShowImage(775, 23, "assets\\images\\button1.jpg");
    iSetColor(255, 255, 255);
    if (level1Unlocked == 1) iText(450, 520, "Level 1", GLUT_BITMAP_TIMES_ROMAN_24);
    else iText(450, 520, "Locked", GLUT_BITMAP_TIMES_ROMAN_24);
    if (level2Unlocked == 1)iText(450, 420, "Level 2", GLUT_BITMAP_TIMES_ROMAN_24);
    else iText(450, 420, "Locked", GLUT_BITMAP_TIMES_ROMAN_24);
    if (level3Unlocked == 1)iText(450, 320, "Level 3", GLUT_BITMAP_TIMES_ROMAN_24);
    else iText(450, 320, "Locked", GLUT_BITMAP_TIMES_ROMAN_24);
    if (level4Unlocked == 1)iText(450, 220, "Level 4", GLUT_BITMAP_TIMES_ROMAN_24);
    else iText(450, 220, "Locked", GLUT_BITMAP_TIMES_ROMAN_24);
    iText(237, 50, "Enter your username: ", GLUT_BITMAP_HELVETICA_18);
    iRectangle(425, 40, 200, 30);
    if (strlen(username) > 0)
    {
        iText(427, 48, username, GLUT_BITMAP_HELVETICA_18);
    }
    iText(851, 43, "BACK", GLUT_BITMAP_TIMES_ROMAN_24);
    iSetColor(255,255,255);
}

void aboutPage()
{
    iShowImage(0, 0, "assets\\images\\aboutus.png");
    iShowImage(775, 23, "assets\\images\\button1.jpg");
    iSetColor(255, 255, 255);
    iText(851, 43, "BACK", GLUT_BITMAP_TIMES_ROMAN_24);
    iSetColor(255,255,255);
}
void helpPage(){
    iShowImage(0, 0, "assets\\images\\inst.png");
    iShowImage(775, 23, "assets\\images\\button1.jpg");
    iSetColor(255, 255, 255);
    iText(851, 43, "BACK", GLUT_BITMAP_TIMES_ROMAN_24);
    iSetColor(255,255,255);

}
void scorePage()
{   iShowImage(0, 0, "assets\\images\\hs.jpg");
    iShowImage(775, 23, "assets\\images\\button1.jpg");
    iSetColor(255, 255, 255);
    iText(851, 43, "BACK", GLUT_BITMAP_TIMES_ROMAN_24);
    iSetColor(255,255,255);
    loadNames();
    iText (400, 500, "Top Five Scores", GLUT_BITMAP_TIMES_ROMAN_24);
    for (int i = 0; i < total_player; i++)
    {
        iText(300, 440 - 40 * i, prev_names[i], GLUT_BITMAP_TIMES_ROMAN_24);
        iText(600, 440 - 40 * i, prev_points[i], GLUT_BITMAP_TIMES_ROMAN_24);

    }
}
void gamePage1()
{
    iShowImage(0, 0, "assets\\images\\1.jpg");
    iShowImage(775, 23, "assets\\images\\button1.jpg");
    iSetColor(255, 255, 255);
    iText(851, 43, "QUIT", GLUT_BITMAP_TIMES_ROMAN_24);
    iShowImage(9, 540, "assets\\images\\button3.jpg");
    iShowImage(780, 540, "assets\\images\\button4.jpg");
    iSetColor(203, 116, 198);
    iFilledCircle(xBall, yBall, radiusBall, 1000);
    iFilledRectangle(xBoard, yBoard, dxBoard, dyBoard);
    int cnt = -1;
    for (int i = 0; i <= 9; i++)
    {
        for (int j = 0; j <= 8; j++)
        {
            cnt++;
            if (arr[cnt].show >= 1)
            {
                iShowImage(arr[cnt].cx, arr[cnt].cy, arr[cnt].img);
            }
        }
    }
    if (gp1 == 1)
    {
        iSetColor(255, 255, 255);
        char pnt[100];
        sprintf(pnt, "%d", point1);
        char lfe[100];
        sprintf(lfe, "%d", life);

        iText(39, 555, "POINT ", GLUT_BITMAP_TIMES_ROMAN_24);
        iText(125, 555, pnt, GLUT_BITMAP_TIMES_ROMAN_24);
        iText(840, 555, "LIFE ", GLUT_BITMAP_TIMES_ROMAN_24);
        iText(900, 555, lfe, GLUT_BITMAP_TIMES_ROMAN_24);



    }

}


void gamePage2()
{
    iShowImage(0, 0, "assets\\images\\2lev.jpg");
    iShowImage(775, 23, "assets\\images\\button1.jpg");
    iShowImage(9, 540, "assets\\images\\button3.jpg");
    iShowImage(780, 540, "assets\\images\\button4.jpg");
    iSetColor(255, 255, 255);
    iText(851, 43, "QUIT", GLUT_BITMAP_TIMES_ROMAN_24);
    iSetColor(255, 215, 0);
    iFilledCircle(xBall, yBall, radiusBall, 1000);
    iFilledRectangle(xBoard, yBoard, dxBoard, dyBoard);

    int cnt = -1;
    for (int i = 0; i <= 9; i++)
    {
        for (int j = 0; j < 8; j++)
        {
            cnt++;
            if (arr[cnt].show >= 1)
            {
                iShowImage(arr[cnt].cx, arr[cnt].cy, arr[cnt].img);
            }
        }
    }

    if (gp2 == 1)
    {
        iSetColor(255, 255, 255);
        char pnt[100], lfe[100];
        sprintf(pnt, "%d", point1);
        sprintf(lfe, "%d", life);
        iText(39, 555, "POINT ", GLUT_BITMAP_TIMES_ROMAN_24);
        iText(125, 555, pnt, GLUT_BITMAP_TIMES_ROMAN_24);
        iText(840, 555, "LIFE ", GLUT_BITMAP_TIMES_ROMAN_24);
        iText(900, 555, lfe, GLUT_BITMAP_TIMES_ROMAN_24);
    }
}


void gamePage3()
{
    iShowImage(0, 0, "assets\\images\\3lev.jpg");
    iShowImage(775, 23, "assets\\images\\button1.jpg");
    iShowImage(9, 540, "assets\\images\\button3.jpg");
    iShowImage(780, 540, "assets\\images\\button4.jpg");
    iSetColor(255, 255, 255);
    iText(851, 43, "QUIT", GLUT_BITMAP_TIMES_ROMAN_24);
    iSetColor(178, 215, 0);
    iFilledCircle(xBall, yBall, radiusBall, 1000);
    iFilledRectangle(xBoard, yBoard, dxBoard, dyBoard);

    int cnt = -1;
    for (int i = 0; i < 11; i++)
    {
        for (int j = 0; j < 11; j++)
        {
            cnt++;
            if (arr[cnt].show >= 1)
            {
                iShowImage(arr[cnt].cx, arr[cnt].cy, arr[cnt].img);
            }
        }
    }

    if (gp3 == 1)
    {
        iSetColor(255, 255, 255);
        char pnt[100], lfe[100];
        sprintf(pnt, "%d", point1);
        sprintf(lfe, "%d", life);
        iText(39, 555, "POINT ", GLUT_BITMAP_TIMES_ROMAN_24);
        iText(125, 555, pnt, GLUT_BITMAP_TIMES_ROMAN_24);
        iText(840, 555, "LIFE ", GLUT_BITMAP_TIMES_ROMAN_24);
        iText(900, 555, lfe, GLUT_BITMAP_TIMES_ROMAN_24);
    }
}



void gamePage4()
{
    iShowImage(0, 0, "assets\\images\\4lev.jpg");
    iShowImage(775, 23, "assets\\images\\button1.jpg");
    iShowImage(9, 540, "assets\\images\\button3.jpg");
    iShowImage(780, 540, "assets\\images\\button4.jpg");
    iSetColor(255, 255, 255);
    iText(851, 43, "QUIT", GLUT_BITMAP_TIMES_ROMAN_24);
    iSetColor(0, 255, 255);
    iFilledCircle(xBall, yBall, radiusBall, 1000);
    iFilledRectangle(xBoard, yBoard, dxBoard, dyBoard);

    int cnt = -1;
    for (int i = 0; i < 11; i++)
    {
        for (int j = 0; j < 11; j++)
        {
            cnt++;
            if (arr[cnt].show >= 1)
            {
                iShowImage(arr[cnt].cx, arr[cnt].cy, arr[cnt].img);
            }
        }
    }

    if (gp4 == 1)
    {
        iSetColor(255, 255, 255);
        char pnt[100], lfe[100];
        sprintf(pnt, "%d", point1);
        sprintf(lfe, "%d", life);
        iText(39, 555, "POINT ", GLUT_BITMAP_TIMES_ROMAN_24);
        iText(125, 555, pnt, GLUT_BITMAP_TIMES_ROMAN_24);
        iText(840, 555, "LIFE ", GLUT_BITMAP_TIMES_ROMAN_24);
        iText(900, 555, lfe, GLUT_BITMAP_TIMES_ROMAN_24);
    }
}


void gameOverPage()
{
    iShowImage(0, 0, "assets\\images\\gameover.jpg");
    iSetColor(255, 255, 255);
    iShowImage(775, 23, "assets\\images\\button1.jpg");
    iText(851, 43, "BACK", GLUT_BITMAP_TIMES_ROMAN_24);
    iSetColor(255, 255, 255);

    iText(217, 50, "Enter your display name: ", GLUT_BITMAP_HELVETICA_18);
    iText(248, 30, "to save highscore ", GLUT_BITMAP_HELVETICA_18);
    iRectangle(425, 40, 200, 30);
    iSetColor(203, 116, 198);
    iFilledRectangle(348, 531, 310, 59);
    iSetColor(0, 0, 255);
    iText(371, 561, "Score = points * level Bonus", GLUT_BITMAP_TIMES_ROMAN_24);
    char pnt[100];
    sprintf(pnt, "%d", point1);
    iText(432, 535, "= ", GLUT_BITMAP_TIMES_ROMAN_24);
    iText(448, 535, pnt , GLUT_BITMAP_TIMES_ROMAN_24);
    iSetColor(255, 255, 255);
    if (strlen(name) > 0)
    {
        iText(427, 48, name, GLUT_BITMAP_HELVETICA_18);
    }
}


void victoryPage()
{
    iShowImage(0, 0, "assets\\images\\levelup.jpg");
    iSetColor(0, 255, 0);
    iShowImage(775, 23, "assets\\images\\button1.jpg");
    iSetColor(255, 255, 255);
    iText(851, 43, "NEXT", GLUT_BITMAP_TIMES_ROMAN_24);
    iSetColor(203, 116, 198);
    iFilledRectangle(348, 531, 310, 59);
    iSetColor(0, 0, 255);
    iText(371, 561, "Score = points * level Bonus", GLUT_BITMAP_TIMES_ROMAN_24);
    char pnt[100];
    sprintf(pnt, "%d", point1);
    iText(432, 535, "= ", GLUT_BITMAP_TIMES_ROMAN_24);
    iText(448, 535, pnt , GLUT_BITMAP_TIMES_ROMAN_24);
    iSetColor(255, 255, 255);
    iText(217, 50, "Enter your display name: ", GLUT_BITMAP_HELVETICA_18);
    iText(248, 30, "to save highscore ", GLUT_BITMAP_HELVETICA_18);
    iRectangle(425, 40, 200, 30);
    if (strlen(name) > 0)
    {
        iText(427, 48, name, GLUT_BITMAP_HELVETICA_18);
    }

}


//after complete one level if i press 's' then this function will work according my condition
void initLevel2()
{
    for (int i = 0; i < 121; i++)
    {
        arr[i].show = 0;
    }
    dely = -2;
    counter = 0;
    dely = -2;
    life = 3;
    point1 = 0;
    hp = 0;
    gp = 0;
    gp1 = 0;
    gp2 = 1;
    gp3 = 0;
    gp4 = 0;
    victory = 0;
    gameOver = 0;
    currentLevel = 2;

    xBall = 500;
    yBall = 50;
    radiusBall = 10;
    dx = 8;
    dy = 6;
    start = 0;
    xBoard = xBall - 50;
    yBoard = yBall - 20;

    int cy = 510;
    int cnt = -1;
    int w = -1;
    for (int i = 0; i <= 100; i++)
    {
        arr[i].show = 0;
    }
    for (int i = 0; i <= 6; i++)
    {
        int cx = 87;
        for (int j = 0; j <= 10; j++)
        {
            cnt++;
            if ((i + j) % 2 == 0)
            {
                w++;
                arr[cnt].show = 1;
                strcpy(arr[cnt].img, "assets\\images\\tile001.jpg");
                arr[cnt].img[20] = w % 4 + '0';
                arr[cnt].cx = cx;
                arr[cnt].cy = cy;
            }
            else
            {
                arr[cnt].show = 0;
            }
            cx += 70;
        }
        cy -= 25;
    }
    arr[cnt-2].img[20] = '4';
    arr[cnt-4].img[20] = '4';
    arr[cnt-6].img[20] = '4';
    arr[cnt - 8].img[20] = '4';
    arr[cnt-2].show = 3;
    arr[cnt-4].show = 3;
    arr[cnt-6].show = 3;
    arr[cnt - 8].show = 3;
    arr[cnt/2].img[20] = '5';

}
void initLevel3()
{
    for (int i = 0; i < 121; i++)
    {
        arr[i].show = 0;
    }
    counter = 0;
    dely = -2;
    life = 3;
    point1 = 0;
    hp = 0;
    gp = 0;
    gp1 = 0;
    gp2 = 0;
    gp3 = 1;
    gp4 = 0;
    victory = 0;
    gameOver = 0;
    currentLevel = 3;

    xBall = 500;
    yBall = 50;
    dx = 17;
    dy = 15;
    radiusBall = 10;
    start = 0;
    xBoard = xBall - dxBoard / 2;
    yBoard = yBall - 20;
    int pattern[11][11] =
    {
        {0,0,1,1,1,1,1,1,1,0,0},
        {0,1,1,0,0,0,0,0,1,1,0},
        {1,1,0,1,1,0,1,1,0,1,1},
        {1,1,0,0,0,0,0,0,0,1,1},
        {1,1,0,0,0,0,0,0,0,1,1},
        {1,1,0,0,0,0,0,0,0,1,1},
        {1,1,0,1,0,0,0,1,0,1,1},
        {0,1,1,0,1,1,1,0,1,1,0},
        {0,0,1,1,0,0,0,1,1,0,0},
        {0,0,0,3,1,1,1,3,0,0,0},
        {0,0,0,0,3,3,3,0,0,0,0}
    };


    int cnt = -1;
    int cy = 540;
    int w = -1;


    for (int i = 0; i < 11; i++)
    {
        int cx = 105;

        for (int j = 0; j < 11; j++)
        {
            cnt++;
            if (pattern[i][j] >= 1)
            {
                w++;
                arr[cnt].show = pattern[i][j];
                strcpy(arr[cnt].img, "assets\\images\\tile001.jpg");
                arr[cnt].img[20] = w % 4 + '0';
                if (pattern[i][j] == 3)
                {
                    arr[cnt].img[20] = '4';
                }
                arr[cnt].cx = cx;
                arr[cnt].cy = cy;
            }
            else
            {
                arr[cnt].show = 0;
            }
            cx += 70;
        }
        cy -= 30;
    }
    arr[82].img[20] = '5';
}
void initLevel4()
{
    for (int i = 0; i < 121; i++)
    {
        arr[i].show = 0;
    }
    counter = 0;
    dely = -2;
    life = 3;
    point1 = 0;
    hp = 0;
    gp = 0;
    gp1 = 0;
    gp2 = 0;
    gp3 = 0;
    gp4 = 1;
    victory = 0;
    gameOver = 0;
    currentLevel = 4;

    xBall = 500;
    yBall = 50;
    radiusBall = 10;
    dx = 14;
    dy = 13;
    start = 0;
    xBoard = xBall - dxBoard / 2;
    yBoard = yBall - 20;
    int pattern[10][10] =
    {
        {0,1,1,0,0,0,1,1,0},
        {1,1,1,1,0,1,1,1,1,0},
        {1,1,1,1,1,1,1,1,1, 0},
        {1,1,1,1,1,1,1,1,1, 0},
        {0,1,1,1,1,1,1,1,0, 0},
        {0,0,1,1,1,1,1,0,0,0},
        {0,0,0,3,1,3,0,0,0,0},
        {0,0,0,0,3,0,0,0,0,0},
        {0,0,0,0,3,0,0,0,0,0},


    };






    int cnt = -1;
    int cy = 500;
    int w = -1;

    for (int i = 0; i < 10; i++)
    {
        int cx = 50;
        for (int j = 0; j < 10; j++)
        {
            cnt++;
            if (pattern[i][j] >= 1)
            {
                w++;
                arr[cnt].show = pattern[i][j];
                strcpy(arr[cnt].img, "assets\\images\\tile001.jpg");
                arr[cnt].img[20] = w % 4 + '0';
                arr[cnt].cx = cx;
                arr[cnt].cy = cy;
                if (arr[cnt].show == 3)
                {
                    arr[cnt].img[20] = '4';
                }
            }
            else
            {
                arr[cnt].show = 0;
            }
            cx += 100;
        }
        cy -= 30;
    }
    arr[44].img[20] = '5';


}




/*
function iMouseMove() is called when the user moves the mouse.
(mx, my) is the position where the mouse pointer is.
*/
void iMouseMove(int mx, int my)
{
    // place your codes here
    if (start == 1)
    {
        xBoard = mx - dxBoard / 2;

        if(xBoard < 0)
            xBoard = 0;
        if(xBoard + dxBoard > 1000)
            xBoard = 1000 - dxBoard;
    }
}

/*
function iMouseDrag() is called when the user presses and drags the mouse.
(mx, my) is the position where the mouse pointer is.
*/
void iMouseDrag(int mx, int my)
{
    // place your codes here
}

/*
function iMouse() is called when the user presses/releases the mouse.
(mx, my) is the position where the mouse pointer is.
*/
void iMouse(int button, int state, int mx, int my)
{
    if (button == GLUT_LEFT_BUTTON && state == GLUT_DOWN)
    {
        //printf("x=%d  y=%d\n", mx, my);

        // ---------- HOME PAGE ----------
        if (hp == 1)
        {
            if (mx >= 370 && mx <= 590 && my >= 500 && my <= 552) // Play
            {
                hp = 0;
                gp = 1;
                ap = 0;
                ip = 0;
                sp = 0;
                victory=0;
                gameOver=0;
            }
            else if (mx >= 370 && mx <= 590 && my >= 400 && my <= 452) // About Us
            {
                hp = 0;
                ap = 1;
                gp = 0;
                ip = 0;
                sp = 0;
                victory=0;
                gameOver=0;
                //printf("%d", ap);
            }
            else if (mx >= 370 && mx <= 590 && my >= 300 && my <= 352) // Help
            {
                hp = 0;
                ip = 1;
                gp = 0;
                ap = 0;
                sp = 0;
                victory=0;
                gameOver=0;
            }
            else if (mx >= 370 && mx <= 590 && my >= 200 && my <= 252)
            {
                hp = 0;
                ip = 0;
                gp = 0;
                ap = 0;
                sp = 1;
                victory=0;
                gameOver=0;
            }
            else if (mx >= 775 && mx <= 995 && my >= 23 && my <= 75)
            {
                exit(0);
            }
            else if (mx >= 370 && mx <= 590 && my >= 100 && my <= 152)
            {
                musicOn = !musicOn;
                if (!musicOn)
                {
                    iPauseSound(channel);
                }
                else
                {
                    iResumeSound(channel);
                }
            }

        }

        // ---------- LEVEL SELECTION PAGE ----------
        else if (gp == 1)
        {
            // ----- LEVEL 1 -----
            if (mx >= 370 && mx <= 590 && my >= 500 && my <= 552 && level1Unlocked == 1)
            {
                for (int i = 0; i < 121; i++)
                {
                    arr[i].show = 0;
                }
                counter = 0;
                dely = -2;
                life = 3;
                point1 = 0;
                hp = 0;
                gp = 0;
                gp1 = 1;
                currentLevel= 1;

                xBall = 500;
                yBall = 50;
                radiusBall = 10;
                dx = 10;
                dy = 8;
                start = 0;
                xBoard = xBall - 50;
                yBoard = yBall - 20;
                victory=0;
                gameOver = 0;

                int cy = 550;
                int cnt = -1;
                int w = -1;

                for (int i = 0; i <= 9; i++)
                {
                    int cx = 50;
                    for (int j = 0; j <= 8; j++)
                    {
                        cnt++;
                        int k = 4;
                        int z = i % 5;
                        z = (i > 4) ? 4 - z : z;
                        if (j >= (k - z) && j <= (k + z))
                        {
                            w++;
                            arr[cnt].show = 1;

                            strcpy(arr[cnt].img, "assets\\images\\tile001.jpg");
                            arr[cnt].img[20] = w % 4 + '0';
                            arr[cnt].cx = cx;
                            arr[cnt].cy = cy;
                            if (w == 49 || w == 46 || w == 48)
                            {
                                arr[cnt].img[20] = '4';
                                arr[cnt].show = 3;
                            }
                            if (w == 20)
                            {
                                arr[cnt].img[20] = '5';
                            }
                        }
                        else
                        {
                            arr[cnt].show = 0;
                        }
                        cx += 100;
                    }
                    cy -= 20;
                }
            }

            // ----- LEVEL 2 -----
            else if (mx >= 370 && mx <= 590 && my >= 400 && my <= 452 && level2Unlocked == 1)
            {
                for (int i = 0; i < 121; i++)
                {
                    arr[i].show = 0;
                }
                counter = 0;
                dely = -2;
                life = 3;
                point1 = 0;
                hp = 0;
                gp = 0;
                gp2 = 1;
                victory=0;
                gameOver = 0;
                currentLevel=2;

                xBall = 500;
                yBall = 50;
                radiusBall = 10;
                dx = 8;
                dy = 6;
                start = 0;
                xBoard = xBall - 50;
                yBoard = yBall - 20;

                int cy = 510;
                int cnt = -1;
                int w = -1;

                for (int i = 0; i <= 6; i++)
                {
                    int cx = 87;
                    for (int j = 0; j <= 10; j++)
                    {
                        cnt++;
                        if ((i + j) % 2 == 0)
                        {
                            w++;
                            arr[cnt].show = 1;
                            strcpy(arr[cnt].img, "assets\\images\\tile001.jpg");
                            //printf("%d %d\n", cx, cy);
                            arr[cnt].img[20] = w % 4 + '0';
                            arr[cnt].cx = cx;
                            arr[cnt].cy = cy;
                        }
                        else
                        {
                            arr[cnt].show = 0;
                        }
                        cx += 70;
                    }
                    cy -= 25;
                }
                arr[cnt-2].img[20] = '4';
                arr[cnt-4].img[20] = '4';
                arr[cnt-6].img[20] = '4';
                arr[cnt - 8].img[20] = '4';
                arr[cnt-2].show = 3;
                arr[cnt-4].show = 3;
                arr[cnt-6].show = 3;
                arr[cnt - 8].show = 3;
                arr[cnt/2].img[20] = '5';
            }

            //--------------level 3----------------

            else if (mx >= 373 && mx <= 586 && my >= 300 && my <= 352 && level3Unlocked == 1)
            {
                for (int i = 0; i < 121; i++)
                {
                    arr[i].show = 0;
                }
                counter = 0;
                dely = -2;
                life = 3;
                point1 = 0;
                hp = 0;
                gp = 0;
                gp3 = 1;
                victory=0;
                gameOver = 0;
                currentLevel=3;

                xBall = 500;
                yBall = 50;
                radiusBall = 10;
                dx = 17;
                dy = 15;
                start = 0;
                xBoard = xBall - dxBoard / 2;
                yBoard = yBall - 20;

                int pattern[11][11] =
                {
                    {0,0,1,1,1,1,1,1,1,0,0},
                    {0,1,1,0,0,0,0,0,1,1,0},
                    {1,1,0,1,1,0,1,1,0,1,1},
                    {1,1,0,0,0,0,0,0,0,1,1},
                    {1,1,0,0,0,0,0,0,0,1,1},
                    {1,1,0,0,0,0,0,0,0,1,1},
                    {1,1,0,1,0,0,0,1,0,1,1},
                    {0,1,1,0,1,1,1,0,1,1,0},
                    {0,0,1,1,0,0,0,1,1,0,0},
                    {0,0,0,3,1,1,1,3,0,0,0},
                    {0,0,0,0,3,3,3,0,0,0,0}
                };






                int cnt = -1;
                int cy = 540;
                int w = -1;

                for (int i = 0; i < 11; i++)
                {
                    int cx = 105;
                    for (int j = 0; j < 11; j++)
                    {
                        cnt++;
                        if (pattern[i][j] >= 1)
                        {
                            w++;
                            arr[cnt].show = pattern[i][j];
                            strcpy(arr[cnt].img, "assets\\images\\tile001.jpg");
                            arr[cnt].img[20] = w % 4 + '0';
                            if (pattern[i][j] == 3)
                            {
                                arr[cnt].img[20] = '4';
                            }
                            arr[cnt].cx = cx;
                            arr[cnt].cy = cy;
                        }
                        else
                        {
                            arr[cnt].show = 0;
                        }
                        cx += 70;
                    }
                    cy -= 30;
                }
                arr[82].img[20] = '5';

            }
            //-------------------level 4-----------------------
            else if (mx >= 370 && mx <= 590 && my >= 200 && my <= 252 && level4Unlocked == 1)
            {
                for (int i = 0; i < 121; i++)
                {
                    arr[i].show = 0;
                }
                dely = -2;
                counter = 0;
                life = 3;
                point1 = 0;
                hp = 0;
                gp = 0;
                gp3 = 0;
                gp2 = 0;
                gp1 = 0;
                gp4 = 1;
                victory=0;
                gameOver = 0;
                currentLevel=4;

                xBall = 500;
                yBall = 50;
                radiusBall = 10;
                dx = 14;
                dy = 13;
                start = 0;
                xBoard = xBall - dxBoard / 2;
                yBoard = yBall - 20;
                int pattern[10][10] =
                {
                    {0,1,1,0,0,0,1,1,0},
                    {1,1,1,1,0,1,1,1,1,0},
                    {1,1,1,1,1,1,1,1,1, 0},
                    {1,1,1,1,1,1,1,1,1, 0},
                    {0,1,1,1,1,1,1,1,0, 0},
                    {0,0,1,1,1,1,1,0,0,0},
                    {0,0,0,3,1,3,0,0,0,0},
                    {0,0,0,0,3,0,0,0,0,0},
                    {0,0,0,0,3,0,0,0,0,0},
                };






                int cnt = -1;
                int cy = 500;
                int w = -1;

                for (int i = 0; i < 10; i++)
                {
                    int cx = 50;
                    for (int j = 0; j < 10; j++)
                    {
                        cnt++;
                        if (pattern[i][j] >= 1)
                        {
                            w++;
                            arr[cnt].show = pattern[i][j];
                            strcpy(arr[cnt].img, "assets\\images\\tile001.jpg");
                            arr[cnt].img[20] = w % 4 + '0';
                            arr[cnt].cx = cx;
                            arr[cnt].cy = cy;
                            if (arr[cnt].show == 3)
                            {
                                arr[cnt].img[20] = '4';
                            }
                        }
                        else
                        {
                            arr[cnt].show = 0;
                        }
                        cx += 100;
                    }
                    cy -= 30;
                }
                arr[44].img[20] = '5';
            }
            else if(mx >= 775 && mx <= 995 && my >= 23 && my <= 75)
            {
                sp = 0;
                ap = 0;
                ip = 0;
                gp1 = 0;
                gp2 = 0;
                hp = 1;
                gp3 = 0;
                gp4 = 0;
                gp = 0;

            }


        }

        // ---------- COMMON BACK BUTTON ----------add kora lagbe(" - ")
        else if ((gp1 == 1 || gp2 == 1 || gp3 == 1 || gp4 == 1) && (mx >= 775 && mx <= 995 && my >= 23 && my <= 75))

        {
            sp = 0;
            ap = 0;
            ip = 0;
            gp1 = 0;
            gp2 = 0;
            hp = 0;
            gp3 = 0;
            gp4 = 0;
            gp = 0;
            gameOver = 1;
            point1 *= currentLevel*10;
            for (int i = 0; i < 100; i++)
            {
                name[i] = '\0';
            }
        }
        else if (victory == 1 && (mx >= 775 && mx <= 995 && my >= 23 && my <= 75))

        {
            if(currentLevel==1 )
        {
            gp1=0;
            gp2=1;
            initLevel2();
            level2Unlocked = 1;
            gameOver = 0;
            victory = 0;
            loadUserName(currentLevel);


        }
        else if (currentLevel == 2 )
        {
            gp2 = 0;
            gp3 = 1;
            initLevel3();
            level3Unlocked = 1;
            gameOver = 0;
            victory = 0;
            loadUserName(currentLevel);

        }
        else if (currentLevel == 3 )
        {
            gp3 = 0;
            gp4 = 1;
            initLevel4();
            level4Unlocked = 1;
            gameOver = 0;
            victory = 0;
            loadUserName(currentLevel);

        }
        else
        {

            hp = 0;
            gameOver = 0;
            sp = 0;
            ap = 0;
            ip = 0;
            gp1 = 0;
            gp2 = 0;
            hp = 0;
            gp3 = 0;
            gp4 = 0;
            gp = 1;
            currentLevel = 1;
            victory = 0;
            gamePage();
            
        }
        }
        else if ((sp == 1 || ap == 1 || ip == 1) &&
                 (mx >= 775 && mx <= 995 && my >= 23 && my <= 75))

        {
            sp = 0;
            ap = 0;
            ip = 0;
            gp1 = 0;
            gp2 = 0;
            hp = 1;
            gp3 = 0;
            gp4 = 0;
            gp = 0;
        }
        else if ((mx >= 775 && mx <= 995 && my >= 23 && my <= 75) && gameOver == 1)
        {
            hp = 0;
            gameOver = 0;
            sp = 0;
            ap = 0;
            ip = 0;
            gp1 = 0;
            gp2 = 0;
            hp = 0;
            gp3 = 0;
            gp4 = 0;
            gp = 1;
        }


    }
}


/*
function iMouseWheel() is called when the user scrolls the mouse wheel.
dir = 1 for up, -1 for down.
*/
void iMouseWheel(int dir, int mx, int my)
{
    // place your code here
}

/*
function iKeyboard() is called whenever the user hits a key in keyboard.
key- holds the ASCII value of the key pressed.
*/
void iKeyboard(unsigned char key)
{
    switch (key)
    {
    case 'q':
        if(dy<0){
            dy*=-1;
        }
        start = 1;
        break;
    // place your codes for other keys here
    case 'w':
        start = 0;
        break;
    default:
        break;
    }
    if (key == '\r' && (gameOver == 1 || (victory == 1 && currentLevel == 4)))
    {
        saveName();
        loadNames();
        name[0] = '\0';
        gameOver = 0;
        hp = 0;
        gp = 1;
        gp1 = 0;
        gp2 = 0;
        gp3 = 0;
        gp3 = 0;
        victory = 0;
    }
    else if (key == '\r' && gp == 1)
    {
        level1Unlocked = 0;
        level2Unlocked = 0;
        level3Unlocked = 0;
        level4Unlocked = 0;
        saveUserName();
        strcpy(currentusername, username);
        for (int i = 0; i < 100; i++)
        {
            username[i] = '\0';
        }

    }
    else if (key == '\r' && victory == 1)
    {
        saveName();
        loadNames();
        name[0] = '\0';
        if(currentLevel==1 )
        {
            gp1=0;
            gp2=1;
            initLevel2();
            level2Unlocked = 1;
            gameOver = 0;
            victory = 0;
            loadUserName(currentLevel);


        }
        else if (currentLevel == 2 )
        {
            gp2 = 0;
            gp3 = 1;
            initLevel3();
            level3Unlocked = 1;
            gameOver = 0;
            victory = 0;
            loadUserName(currentLevel);

        }
        else if (currentLevel == 3 )
        {
            gp3 = 0;
            gp4 = 1;
            initLevel4();
            level4Unlocked = 1;
            gameOver = 0;
            victory = 0;
            loadUserName(currentLevel);

        }
        else
        {

            gp1 = gp2 = gp3 = gp4 = 0;
            hp = 0;
            gp = 1;
            loadUserName(currentLevel);
            currentLevel = 0;
            gamePage();
        }

    }

    else if (key == '\b' && (gameOver == 1 || victory == 1))
    {
        if (strlen(name) > 0)
        {
            name[strlen(name) - 1] = '\0';
        }
    }
    else if (gameOver == 1 || victory == 1)
    {
        if (strlen(name) < 99)
        {
            name[strlen(name)] = key;
            name[strlen(name) + 1] = '\0';
        }
    }
    else if (key == '\b' && (gp == 1))
    {
        if (strlen(username) > 0)
        {
            username[strlen(username) - 1] = '\b';
            username[strlen(username)-1] = '\0';
        }
    }
    else if (gp == 1)
    {
        if (strlen(username) < 99)
        {
            username[strlen(username)] = key;
            username[strlen(username) + 1] = '\0';
        }
    }

}

/*
function iSpecialKeyboard() is called whenver user hits special keys likefunction
keys, home, end, pg up, pg down, arraows etc. you have to use
appropriate constants to detect them. A list is:
GLUT_KEY_F1, GLUT_KEY_F2, GLUT_KEY_F3, GLUT_KEY_F4, GLUT_KEY_F5, GLUT_KEY_F6,
GLUT_KEY_F7, GLUT_KEY_F8, GLUT_KEY_F9, GLUT_KEY_F10, GLUT_KEY_F11,
GLUT_KEY_F12, GLUT_KEY_LEFT, GLUT_KEY_UP, GLUT_KEY_RIGHT, GLUT_KEY_DOWN,
GLUT_KEY_PAGE_UP, GLUT_KEY_PAGE_DOWN, GLUT_KEY_HOME, GLUT_KEY_END,
GLUT_KEY_INSERT */
void iSpecialKeyboard(unsigned char key)
{
    switch (key)
    {
    case GLUT_KEY_END:
        // do something
        break;

    case GLUT_KEY_LEFT:
        if (start == 0)
        {
            break;
        }
        xBoard -= 50;;
        if (xBoard < 0)
        {
            xBoard = 0;
        }
        break;
    case GLUT_KEY_RIGHT:
        if (start == 0)
        {
            break;
        }
        xBoard += 50;;
        if (xBoard > 900)
        {
            xBoard = 900;
        }
        break;
    default:
        break;
    }
}



void ballChange1()
{
    if (!(gp1 || gp2 || gp3 || gp4)) return;

    if (start == 1)
    {
        xBall += dx;
        yBall += dy;
    }

    if (xBall >= 1000 - radiusBall || xBall <= radiusBall)
    {
        dx = -dx;
    }
    if (yBall >= 600 - radiusBall)
    {
        dy = -dy;
    }

    if (yBall - radiusBall <= yBoard + dyBoard && yBall + radiusBall>= yBoard)
    {
        if (xBall + radiusBall >= xBoard && xBall - radiusBall <= xBoard + dxBoard)
        {
            dy = -dy;
        }
    }


    if (yBall < 0)
    {
        xBall = 500;
        yBall = 50;
        xBoard = xBall - dxBoard / 2;
        yBoard = yBall - 20;
        start = 0;
        life--;
        if (life < 0) life = 0;
        //printf("Life: %d\n", life);
    }



    int cnt = -1;
    int total = 0;

    int max_rows, max_cols;

    if (gp1 == 1)
    {
        max_rows = 10;
        max_cols = 9;
        counter++;
        counter %= 50;
        if (counter == 49)
        {
            delx *= -1;
            dely *= -1;
        }

        for (int i = 0; i < 121; i++)
        {
            if (arr[i].show >= 1)
            {
                arr[i].cy += dely;
            }
        }

    }
    else if (gp2 == 1)
    {
        max_rows = 7;
        max_cols = 11;
        counter++;
        counter %= 50;
        if (counter == 49)
        {
            delx *= -1;
            dely *= -1;
        }

        for (int i = 0; i < 121; i++)
        {
            if (arr[i].show >= 1)
            {
                arr[i].cy += dely;
            }
        }
    }
    else if (gp3 == 1)
    {
        max_rows = 11;
        max_cols = 11;
        counter++;
        counter %= 50;
        if (counter == 49)
        {
            delx *= -1;
            dely *= -1;
        }

        for (int i = 0; i < 121; i++)
        {
            if (arr[i].show >= 1)
            {
                arr[i].cy += dely;
            }
        }
    }
    else if (gp4 == 1)
    {
        max_rows = 15;
        max_cols = 20;
        counter++;
        counter %= 50;
        if (counter == 49)
        {
            delx *= -1;
            dely *= -1;
        }

        for (int i = 0; i < 121; i++)
        {
            if (arr[i].show >= 1)
            {
                arr[i].cy += dely;
            }
        }
    }
    else
    {
        max_rows = 10;
        max_cols = 9;
    }

    for (int i = 0; i < max_rows; i++)
    {
        for (int j = 0; j < max_cols; j++)
        {
            cnt++;
            if (arr[cnt].show >= 1 && (xBall >= arr[cnt].cx && xBall <= arr[cnt].cx + 100) && (yBall >= arr[cnt].cy && yBall <= arr[cnt].cy + 20))
            {
                arr[cnt].show--;
                if (arr[cnt].img[20] == '5')
                {
                    life += 2;
                }
                int first = xBall - dx;
                int second = yBall - dy;
                if (first < arr[cnt].cx || first > arr[cnt].cx + 100)
                {
                    dx = -dx;
                    xBall += dx;
                }
                if (second - dy < arr[cnt].cy || second - dy > arr[cnt].cy + 20)
                {
                    dy = -dy;
                    yBall += dy;
                }
                point1 += 10;
            }
            if (arr[cnt].show >= 1)
            {
                total++;
            }
        }
    }

    if (life == 0)
    {
        start = 0;
        gp1 = 0;
        gp2 = 0;
        gp3 = 0;
        gp4 = 0;
        gp = 0;
        name[0] = '\0';
        gameOver = 1;
        point1 *= currentLevel*10;

    }
    else if (total == 0 && (gp1 || gp2 || gp3 || gp4))
    {
        start = 0;


        if (gp1 == 1) level2Unlocked = true;
        if (gp2 == 1) level3Unlocked = true;
        if (gp3 == 1) level4Unlocked = true;

        gp1 = 0;
        gp2 = 0;
        gp3 = 0;
        gp4 = 0;
        gp = 0;
        victory = 1;
        point1 *= currentLevel*10;
        for (int i = 0; i < 100; i++)
        {
            name[i] = '\0';
        }
    }
}


int main(int argc, char *argv[])
{
    life = 3;
    start = 0;

    gameOver = 0;
    victory = 0;

    glutInit(&argc, argv);

    iInitializeSound();

    channel = iPlaySound("assets/sounds/music.wav", true, 80);
    iSetTimer(25, ballChange1);
    iInitialize(1000, 600, "Dx Ball");
    return 0;
}