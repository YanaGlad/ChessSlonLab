#include <iostream>
#include <vector>
#include <Windows.h>
using namespace std;
 
struct Figure {
    short x, y, fight = 0;

    bool put = false;

    Figure() {

    }

    void set(short x, short y) {
        this->x = x;
        this->y = y;
    }
};


struct Slon {
    short x, y, fight = 0;
    bool draw = false;
    vector<Figure> figuresss;

    Slon() {

    }

    void set(short x, short y) {
        this->x = x;
        this->y = y;
    }
};

 
short** init(short dots) {

    short** A = new short* [dots];

    for (int i = 0; i < dots; i++)
        A[i] = new short[dots];

    for (int i = 0; i < dots; i++)
        for (int j = 0; j < dots; j++)
            cin >> A[i][j];

    return A;
}

void findBestSlon(Slon ** &sloni, Figure ** &figures, short s, short dots) {
    for (short i = 0; i < dots; i++) {
        for (short j = 0; j < dots; j++) {

            short size = 0;
            for (short k = 0; k < sloni[i][j].figuresss.size(); k++) {
                Figure check = sloni[i][j].figuresss[k];

                if (figures[check.x][check.y].x == check.x && figures[check.x][check.y].y == check.y && !figures[check.x][check.y].put) {
                    size++;
                }
            }


            if (size == s)
                for (short k = 0; k < sloni[i][j].figuresss.size(); k++) {
                    Figure check = sloni[i][j].figuresss[k];

                    if (figures[check.x][check.y].x == check.x && figures[check.x][check.y].y == check.y && !figures[check.x][check.y].put) {
                        sloni[i][j].draw = true;
                        figures[check.x][check.y].put = true;
                    }

                }
        }
    }
}
 
void check3(short** matrix, short dots) {
    Slon** sloni = new Slon * [dots * dots];
    Figure** figures = new Figure * [dots * dots];

    for (int i = 0; i < dots; i++)
        sloni[i] = new Slon[dots];

    for (int i = 0; i < dots; i++)
        figures[i] = new Figure[dots];

    bool ch = false;

    for (int i = 0; i < dots; i++) {
        for (int j = 0; j < dots; j++) {

            if (matrix[i][j] != 2) {
                sloni[i][j].set(i, j);
                figures[i][j].set(-1, -1);
            }

            else if (matrix[i][j] == 2) {
                figures[i][j].set(i, j);
                sloni[i][j].set(-1, -1);
            }

   

            else {
                sloni[i][j].set(-1, -1);
                figures[i][j].set(-1, -1);
            }
        }
    }
    cout << endl;

    for (int i = 0; i < dots; i++) {
        for (int j = 0; j < dots; j++) {

            bool leftUp = false, leftDown = false, rightUp = false, rightDown = false; 

            if (sloni[i][j].x == i) {
                int ii = i, jj = j;
                //лево вверх
                for (int x = min(i, j); x > -1; x--) {

                    if (matrix[ii][jj] == 1) {
                        leftUp = true;
                        break;
                    }
                    ii--;
                    jj--;
                }

                ii = i, jj = j;
                //право вниз
                for (int x = max(i, j); x < dots; x++) {

                    if (matrix[ii][jj] == 1) {
                        rightDown = true;
                        break;
                    }

                    ii++;
                    jj++;
                }



                ii = i, jj = j;
                //право вверх
                for (int x = min(i, j); x > -1 && jj < dots; x--) {

                    if (matrix[ii][jj] == 1) {
                        rightUp = true;
                        break;
                    }

                    ii--;
                    jj++;
                }



                ii = i, jj = j;
                //лево вниз
                for (int x = max(i, j); x < dots; x++) {


                    if (matrix[ii][jj] == 1) {
                        leftDown = true;
                        break;
                    }

                    ii++;
                    jj--;
                }




                ///////////////////////////////

                  ii = i, jj = j;
                //лево вверх
                if(!leftUp){
                for (int x = min(i, j); x > -1; x--) {
 
                    if (matrix[ii][jj] == 2) {
                        sloni[i][j].fight++;
                        figures[ii][jj].fight++;
                        sloni[i][j].figuresss.push_back(figures[ii][jj]);
                        break;
                    }
                    ii--;
                    jj--;
                }
            }
                if(!rightDown){ 
                ii = i, jj = j;
                //право вниз
                for (int x = max(i, j); x < dots; x++) {
 
                    if (matrix[ii][jj] == 2) {
                        sloni[i][j].fight++;
                        figures[ii][jj].fight++;
                        sloni[i][j].figuresss.push_back(figures[ii][jj]);


                        break;
                    }
                    ii++;
                    jj++;
                }
                }

                if(!rightUp){ 
                ii = i, jj = j;
                //право вверх
                for (int x = min(i, j); x > -1 && jj < dots; x--) {
 
                    if (matrix[ii][jj] == 2) {
                        sloni[i][j].fight++;
                        figures[ii][jj].fight++;
                        sloni[i][j].figuresss.push_back(figures[ii][jj]);

                        break;
                    }

                    ii--;
                    jj++;
                }
                }

                if(!leftDown){ 
                ii = i, jj = j;
                //лево вниз
                for (int x = max(i, j); x < dots; x++) {
 

                    if (matrix[ii][jj] == 2) {
                        sloni[i][j].fight++;
                        figures[ii][jj].fight++;
                        sloni[i][j].figuresss.push_back(figures[ii][jj]);

                        break;
                    }
                    ii++;
                    jj--;
                }

                }
            }

        }
    }
   
 

    findBestSlon(sloni, figures, 4, dots);
    findBestSlon(sloni, figures, 3, dots);
    findBestSlon(sloni, figures, 2, dots);
    findBestSlon(sloni, figures, 1, dots);

    bool da = false;
    for (int i = 0; i < dots && !da; i++) {
        for (int j = 0; j < dots && !da; j++) {
          
            if (matrix[i][j] == 2 && !figures[i][j].put) {
                cout << " Расстановка невозможна ";
                da = true;
          }
        }
        
    }


  if(!da){ 
    for (int i = 0; i < dots; i++) {
        for (int j = 0; j < dots; j++) {
           if(sloni[i][j].draw)
                cout << " S ";
            else if (matrix[i][j] == 2)
                cout << " V ";
            else if (matrix[i][j] == 1)
               cout << " O ";
            else cout << " . ";
        }
        cout << endl;
    }
  }
}


 
int main()
{
    SetConsoleCP(1251);
    SetConsoleOutputCP(1251);

    short n;
    cin >> n;

    short** matrix = init(n);

    check3(matrix, n);
}

 
/*
0 0 0 2 0
0 0 0 0 0
0 1 0 0 0
2 0 0 1 0
0 0 0 0 2
*/


/*
0 0 0 2 0
0 0 0 0 0
0 1 0 0 0
2 0 0 2 0
0 0 0 0 1
*/


/*
0 0 0 0 0 0 0 0
0 0 0 0 0 2 0 2
0 2 0 0 0 0 0 0
0 0 0 0 0 2 0 2
0 0 0 0 0 0 0 0
0 0 0 2 0 0 0 0
0 0 0 0 0 0 0 0
0 2 0 2 0 0 2 0
*/