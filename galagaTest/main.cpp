#include <iostream>
#include <conio.h>
#include <string>
#include <Windows.h>
#include <vector>
#include <algorithm>
#include <time.h>



using namespace std;


// enemy class -----
class firstEnemy {

private:

    int level;
    int health;
    int damage;
    char symbol;
    int x,y;
    int isGone;

public:



    firstEnemy(int level, int y, int x) {

        this->level = level;
        this->health = 100 * level;
        this->damage = 10 * level;
        this->x = x;
        this->y = y;
        this->symbol = '@';

    };
    void view() {

        cout << level << " " << x << " " << y << " " << symbol << endl;

    };
    int getX() {

        return this->x;

    };
    int getY() {

        return this->y;

    };
    void chY(int change) {

        y += change;

    };
    void chX (int change) {


        this->x += change;

    };
    void setIsGone(int num) {

        this->isGone = num;

    };
    int getIsGone() {return this->isGone;};

    int getDamage() {return this->damage;};

};
//------------------

// shot class ------
class shot {

private:
    int x;
public:

    int y;

    shot(int x, int y) {

        this->x = x;
        this->y = y;

    }
    int getX() {

        return x;

    }
    int getY(){

        return y;

    }

    void chY() {

        y -= 2;

    }

};
//-----------------

//support class ----

class sup {

private:
    int x;
    int y;
public:
    sup(){

        this->x = rand() % 18 + 1;
        this->y = 1;

    };

    int getY(){return y;};
    int getX(){return x;};


};

//------------------


//global vars -----
bool gameover, shutDown = false, isGoing = false, goTurn = false, isShot = false;
char screen[20][20];
const int screenWidth = 20, screenHeight = 20;
int playerX,playerY,score, enemyOfLine = 1, lines = 1, renderCount = 2, chBoxY = 0, chBoxX1 = 1, chBoxX2 = 0, isEnemyMove = 0, enemySpeed = 3,lastScore, ammuCount = 10, maxAmmu = 10;
int health = 30, maxHealth = 30, supRand = 7;
vector <firstEnemy> enemyArr;
vector <shot> shotArr;
vector <int> goShotArr;
vector <sup> supArr;
vector <int> goSupArr;
enum eDirection {STOP, LEFT, RIGHT, DOWN, UP};
eDirection dir;
//-----------------

//system func -----


    template <typename T>
    void remove(std::vector<T>& v, size_t index) {
        v.erase(v.begin() + index);
    }


    void setup() {



        gameover = false;
        renderCount = 2;
        chBoxX2 = 0;
        chBoxX1 = 1;
        chBoxX2 = 0;
        shutDown = false;
        isGoing = false;
        goTurn = false;
        isEnemyMove = 0;
        enemyArr.clear();
        shotArr.clear();
        supArr.clear();
        goSupArr.clear();
        playerX = screenWidth / 2;
        playerY = 17;
        dir = STOP;
        isShot = false;
        ammuCount = 10;
        health = 30;
        maxHealth = 30;


    }

    void movePlayer();


    void getKey() {
    if(_kbhit()) {
        switch(_getch()){

            case('a'):
                dir = LEFT;
                break;
            case('s'):
                dir = DOWN;
                break;
            case('d'):
                dir = RIGHT;
                break;
            case('w'):
                dir = UP;
                break;
            case(32):
                if(ammuCount) {
                    shot a(playerX, playerY-1);
                    shotArr.push_back(a);
                    goShotArr.push_back(0);
                    ammuCount--;
                    break;
                }



        }
    }
        movePlayer();

    }

    void movePlayer() {

        switch(dir) {

        case(LEFT):
            if(playerX - 1 != 0) {

                playerX--;


            }
            break;
        case(RIGHT):
            if(playerX + 1 != 19) {

                playerX++;


            }
            break;
        case(DOWN):
            if(playerY + 1 != 19) {

                playerY++;


            }
            break;
        case(UP):
            if(playerY - 1 != 0) {

                playerY--;


            }
            break;


        }
        dir = STOP;

    }

    void goEnemyX() {

        if(goTurn) {

            chBoxX1 += 1;
            chBoxX2 -= 1;
            goTurn = !goTurn;

        }
        else {

            chBoxX1 -= 1;
            chBoxX2 += 1;
            goTurn = !goTurn;

        }

    }




    void StartScreen() {

        system("cls");
        cout << "Welcome!" << endl << "Press S button to start!" << endl;


    }


    void goEnemy() {

        chBoxY -= 1;



    }

    void createSup() {

        srand(time(NULL));

        int ran = rand() % supRand;

        if(ran) return;

        sup a;
        supArr.push_back(a);
        goSupArr.push_back(0);

    }


    void createScreen() {



        for (int i = 0; i < 20; i++) {
            for (int j = 0; j < 20; j++) {

                if (i == 0 || i == 19 || j == 0 || j == 19) screen[i][j] = '#';
                else if(i > 0 && i < 19 && j > 0 && j < 19) screen[i][j] = ' ';


            }


        }
        screen[playerY][playerX] = '^';

            int v = 0;

            for_each(shotArr.begin(), shotArr.end(), [&v] (shot a) {


                        if(a.getY() - goShotArr[v] == 0) {

                            remove(shotArr,v);
                            remove(goShotArr,v);
                            return;

                        }

                        screen[a.getY() - goShotArr[v]][a.getX()] = '|';
                        goShotArr[v]++;
                        v++;


                     });

            v = 0;

            for_each(supArr.begin(), supArr.end(), [&v] (sup a) {

                        if (screen[a.getY() + goSupArr[v]][a.getX()] == '^') {

                            health = maxHealth;
                            ammuCount = maxAmmu;
                            remove(supArr,v);
                            remove(goSupArr,v);
                            return;


                        }


                        if (a.getY() + goSupArr[v] == 19) {

                                remove(supArr,v);
                                remove(goSupArr,v);
                                return;
                        }

                        screen[a.getY() + goSupArr[v]][a.getX()] = '*';
                        goSupArr[v]++;
                        v++;

            });

            v = 0;
            for_each(enemyArr.begin(), enemyArr.end(), [&v] (firstEnemy a) {

                    if(a.getY() - chBoxY >= 19) {

                        gameover = true;
                        return;

                    }

                    if(a.getY() <= renderCount) {

                        if(a.getY() / 2 % 2 == 0) {

                            if(screen[a.getY() - chBoxY][a.getX() + chBoxX1] == '|') {

                                remove(enemyArr,v);
                                if(ammuCount + 1 <= maxAmmu) ammuCount++;
                                score++;

                            }
                            else if(screen[a.getY() - chBoxY][a.getX() + chBoxX1] == '^'){
                                if(health - a.getDamage()) {
                                    remove(enemyArr,v);
                                    if(ammuCount + 1 <= maxAmmu) ammuCount++;
                                    score++;
                                    health -= a.getDamage();
                                }
                                else {
                                    score++;
                                    gameover = true;
                                    return;

                                }

                            }
                            else{
                                screen[a.getY() - chBoxY][a.getX() + chBoxX1] = '@';
                            }
                        }
                        else {
                            if(screen[a.getY() - chBoxY][a.getX() + chBoxX2] == '|'){

                                remove(enemyArr,v);
                                if(ammuCount + 1 <= maxAmmu) ammuCount++;
                                score++;

                            }
                            else if(screen[a.getY() - chBoxY][a.getX() + chBoxX2] == '^') {

                                if(health - a.getDamage()) {
                                    remove(enemyArr,v);
                                    if(ammuCount + 1 <= maxAmmu) ammuCount++;
                                    score++;
                                    health -= a.getDamage();
                                }
                                else {

                                    score++;
                                    gameover = true;
                                    return;

                                }

                            }
                            else{

                                screen[a.getY() - chBoxY][a.getX() + chBoxX2] = '@';

                            }


                        }

                    }
                    v++;
                    });


        if(isEnemyMove == enemySpeed) {
            createSup();
            renderCount += 2;
            goEnemyX();
            if(enemyArr[enemyOfLine * lines - 1].getY() <= renderCount) {



                if(isGoing) {

                    goEnemy();
                    isGoing = false;


                }
                else {

                    isGoing = true;


                }


            }

            isEnemyMove = 0;
        }
        else {

            isEnemyMove++;

        }

    }



    void createEnemy() {
        int widthGap = screenWidth / 4;
        int heightGap = screenHeight / 10;
        int gone = 0;

        for (int i = 0; i < lines; i++) {
            for (int j = 0; j < enemyOfLine; j++) {

                firstEnemy a(1,(heightGap * (i + 1)), (widthGap * (j + 1)) - 3);
                enemyArr.push_back(a);

            }

        }

    }

    void printScreen() {

        for (int i = 0; i < 20; i++) {
            for (int j = 0; j < 20; j++) {

                cout << screen[i][j];

            }
            cout << endl;

        }
        cout << "AMMU:" << ammuCount << "   MAX AMMU:" << maxAmmu << endl;
        cout << "HEALTH:" << health << "   MAX HEALTH:" << maxHealth << endl;
        cout << "SCORE:" << score;



    }

    void checkNewLevel() {

        if(score == enemyOfLine * lines + lastScore) {

            if (enemyOfLine != 4) enemyOfLine++;

            lines++;
            renderCount = 2;
            chBoxX2 = 0;
            chBoxX1 = 1;
            chBoxX2 = 0;
            chBoxY = 0;
            isGoing = false;
            goTurn = false;
            lastScore = score;
            createEnemy();
            enemySpeed++;
            ammuCount = maxAmmu;
            maxAmmu += 5;
        }

    }

    bool start() {
        setup();

        StartScreen();
        createEnemy();
        if (_getch() == 's') {
            do{

                    createScreen();
                    printScreen();
                    getKey();
                    Sleep(50);
                    system("cls");
                    checkNewLevel();



            }while(!gameover);

            cout << "Game Over! Your score is "<< score << endl << "press S button to restart" << endl << "press Q button to quet";
            if (_getch() == 's') return 1;
            else if (_getch() == 'q') return 0;

        };

    }
//-----------------

int main()
{
    do {

        if (!start()) return 0;

    }while (!shutDown);
    return 0;
}
