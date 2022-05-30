#include <iostream>
#include <vector>
#include <algorithm>
#include <cstdlib>
#include <ctime>
#include <windows.h>
#include <math.h>
#include <chrono>
using namespace std;
using namespace std::chrono;

//size of the sudoku
#define ROW 9
#define COL 9
#define SQR 3
#define POW 27





//displayng the stuff, help not working at the moment
void display(vector <vector<int> > vecx, bool help){
    int t;
    if (help){
        for (int i = 1; i <= COL; i++){
            if ((i+1)%SQR == 0 && (i+1) < ROW){
                cout << "  ";
            }
            else{
                cout << i << " ";
            }
        }
    }
    for (int i = 0; i < vecx.size(); i++) {
        if (help){
            cout << i + 1 << "   ";
        }
        for (int j = 0; j < vecx[i].size(); j++){
            if(vecx[i][j] == 0){
                cout << "  ";
            }
            else{
                cout << vecx[i][j] << " ";
            }
            if ((j+1)%SQR == 0 && (j+1) < ROW){
                cout << "| ";
            }

        }
        cout << endl;
        if ((i+1)%SQR == 0 && (i+1) < ROW){
            if (help){
                cout << "    ";
            }
            for (int m = 0; m < SQR; m++){
                for (int n = 0; n < SQR; n++){
                    cout << "--";
                }
                if(m != 0 && m + 1 != SQR){
                    cout << "-";
                }
                if(m + 1 != SQR){
                    cout << "+";
                }
            }
            cout << endl;
        }
    }
};

vector <vector <int> > prepareSolver(vector<vector <int> >rozx) {
    vector <vector <int> > out;
    int t;
    for (int i = 0; i < POW; i++) {
        vector<int> vecy;
        for (int j = 0; j < POW; j++) {
            vecy.push_back(0);
        }
        out.push_back(vecy);
    }
    for (int i = 0; i < rozx.size(); i++) {
        for (int j = 0; j < rozx[i].size(); j++) {
            t = rozx[i][j];
            //cout << t << endl;
            //for (int c = ROW; c > 0; c--) {
                for (int x = 0; x < SQR; x++) {
                    for (int y = 0; y < SQR; y++) {
                        if (t % 10 == (9 - (x*3 + y))) {
                            //cout << t << endl;
                            out[i * 3 + (2 - x)][j * 3 + (2 - y)] = (9 - (x*3+y));
                            //cout << out[i * 3 + x][j * 3 + y] << endl << endl;
                            t = t / 10;
                        }
                        //out[i * 3 + x][j * 3 + y] = 0;
                    }
                }
            //}
        }
    }

    return out;
};

vector <vector <int> > testowy(int ts) {
    vector < vector <int> > out;
    vector <int> vecy;
    vecy.push_back(ts);
    out.push_back(vecy);
    return out;
}

void displaySolver(vector <vector <int> > rozx) {
    vector <vector <int> > toDisplay = prepareSolver(rozx);
    for (int i = 0; i < toDisplay.size(); i++) {
        for (int j = 0; j < toDisplay[i].size(); j++) {
            if (toDisplay[i][j] == 0) {
                cout << "  ";
            }
            else {
                cout << toDisplay[i][j] << " ";
            }
            if ((j + 1) % SQR == 0 && (j + 1) < POW) {
                cout << "|";
                if ((j + 1) % ROW == 0 && (j + 1) < POW) {
                    cout << "|";
                }
                cout << " ";
            }

        }
        cout << endl;
        if ((i + 1) % SQR == 0 && (i + 1) < POW) {
            for (int m = 0; m < ROW; m++) {
                for (int n = 0; n < SQR; n++) {
                    cout << "--";
                }
                if (m != 0 && m + 1 != ROW) {
                    cout << "-";
                }
                if (m + 1 != ROW) {
                    cout << "+";
                    if (((m + 1) % SQR) == 0 && (m+1) < POW) {
                        cout << "+";
                    }
                }
            }
            cout << endl;
            if ((i + 1) % ROW == 0 && (i + 1) < POW) {
                for (int m = 0; m < ROW; m++) {
                    for (int n = 0; n < SQR; n++) {
                        cout << "--";
                    }
                    if (m != 0 && m + 1 != ROW) {
                        cout << "-";
                    }
                    if (m + 1 != ROW) {
                        cout << "+";
                        if ((i + 1) % ROW == 0 && (i + 1) < POW && ((m + 1) % SQR) == 0 && (m + 1) < POW) {
                            cout << "+";
                        }
                    }
                }
                cout << endl;
            }
        }
    }
};

//cheks if a nuber exists in a vector
bool does_exist(const vector< vector<int> >&  v, int item){

     vector< vector<int> >::const_iterator row;

    for (row = v.begin(); row != v.end(); row++) {
        if(find(row->begin(), row->end(), item) != row->end() )
            return true;
    }

    return false;
};

//deletes one digit of a number
int deleteDigit(int a, int b){
    int c, d, e, i;
    e = a;
    d = 1;
    i = 1;
    while (e>0){
        if (e%10 == b){
            break;
        }
        i++;
        e = e/10;
    }
    for (i; i > 0; i--){
        d = d * 10;
    }
    c = a/d;
    c = c*d;
    a = a-c;
    b = a/(d/10);
    c = c/10;
    b = b*(d/10);
    b = a-b;
    c = c+b;
    return c;
};

//cheks if a nuber has a certain digit
bool hasDigit(int number, int digit)
{
      while(number > 0)
      {
          if(number % 10 == digit)
              return true;

          number=number/10;
      }
      return false;
};

//delets digits from the solving vector
vector < vector <int> > deleteDigits(int i, int j, int r, vector< vector<int> > rozx){
    for (int g = 0; g < ROW; g++){
            //cout << rozx[g][j] << endl;
        if (hasDigit(rozx[g][j], r)){

            rozx[g][j] = deleteDigit(rozx[g][j], r);
            //cout << rozx[g][j] << endl;
        }
    }

    for (int g = 0; g < COL; g++){
        if (hasDigit(rozx[i][g], r)){
            rozx[i][g] = deleteDigit(rozx[i][g], r);
        }
    }


    for (int g = 0; g < COL; g++){
        if (hasDigit(rozx[(i/SQR)*SQR+(g/SQR)][(j/SQR)*SQR+(g%SQR)], r)){
            rozx[(i/SQR)*SQR+(g/SQR)][(j/SQR)*SQR+(g%SQR)] = deleteDigit(rozx[(i/SQR)*SQR+(g/SQR)][(j/SQR)*SQR+(g%SQR)], r);
        }
    }
    return rozx;
};

//test if you can put a digit in a cell
bool test(vector< vector<int> > vecx, vector< vector<int> > stalyx, int x, int y, int f){
            bool o = true;
            for (int g = 0; g < ROW; g++){
                if (vecx[g][y] == f){
                    o = false;
                }
            }
            if (o){
               for (int g = 0; g < COL; g++){
                    if (vecx[x][g] == f){
                        o = false;
                    }
                }
            }
            if (o){
                for (int g = 0; g < COL; g++){
                    if (vecx[(x/SQR)*SQR+(g/SQR)][(y/SQR)*SQR+(g%SQR)] == f){
                        o = false;
                    }
                }
            }

            if (!o && vecx[x][y] == f ){
                o = true;
            }

        return o;
};


/*void delete_saved(vector< vector<int> > vec, int x, int y, int f) {
            for (int g = 0; g < ROW; g++){
                if (hasDigit(vec[g][y], f)){
                    vec[g][y] = usun_cyfre(vec[g][y], f);
                    cout << vec[g][y] << endl;
                    //display(vecx);
                }
            }

            for (int g = 0; g < COL; g++){
                if (hasDigit(vec[x][g], f)){
                    vec[x][g] = usun_cyfre(vec[g][y], f);
                    cout << vec[x][g] << endl;
                    //display(vecx);
                }
            }


            for (int g = 0; g < COL; g++){
                if (hasDigit(vec[(x/SQR)*SQR+(g/SQR)][(y/SQR)*SQR+(g%SQR)], f)){
                    vec[(x/SQR)*SQR+(g/SQR)][(y/SQR)*SQR+(g%SQR)] = usun_cyfre(vec[(x/SQR)*SQR+(g/SQR)][(y/SQR)*SQR+(g%SQR)], f);
                    cout << vec[(x/SQR)*SQR+(g/SQR)][(y/SQR)*SQR+(g%SQR)] << endl;
                    //display(vecx);
                }
            }
            vec[x][y] = 0;
}*/

bool check_for_not(vector< vector<int> > vec, int n){
    bool o = true;
    for (int i = 0; i < ROW; i++) {
        for (int j = 0; j < COL; j++) {
            if(vec[i][j] != n){
                o = false;
            }
        }
    }
    return o;
};

int look_for_lonely_x(vector < vector <int> > vec, int y){
    int test;
    bool untested = true;
    bool atest = true;
    int out = 10;
    int outt = 10;
    for (int l = 1; l <= ROW; l++){
        for (int j = 0; j < ROW; j++){
            test = vec [y][j];
            for (test; test > 0; test = test/10){
                //cout << test << endl;
                if (test%10 == l) {
                    //cout << "test" << endl;
                    if (untested){
                        out = l;
                        outt = j;
                        untested = false;
                    }
                    else{
                        out = 10;
                        outt = 10;
                        //cout << endl << l << endl;
                    }
                }
            }
            //cout << "koniec";

        }
        if (outt < 9 && out < 9){
            out = out*10 + outt;
            return out;
        }
        untested = true;
    }
    return 0;
}

int look_for_lonely_y(vector < vector <int> > vec, int x){
    int test;
    bool untested = true;
    bool atest = true;
    int out = 10;
    int outt = 10;
    for (int l = 1; l <= ROW; l++){
        for (int i = 0; i < ROW; i++){
            test = vec [i][x];
            for (test; test > 0; test = test/10){
                //cout << test << endl;
                if (test%10 == l) {
                    //cout << "test" << endl;
                    if (untested){
                        out = l;
                        outt = i;
                        untested = false;
                    }
                    else{
                        out = 10;
                        outt = 10;
                       // cout << endl << l << endl;
                    }
                }
            }
            //cout << "koniec";

        }
        if (outt < 9 && out < 9){
            out = out*10 + outt;
            return out;
        }
        untested = true;
    }
    return 0;
}

int look_for_lonely_square(vector < vector <int> > vec, int x, int y) {
    int test;
    bool untested = true;
    bool atest = true;
    int out = 10;
    int outt = 10;
    int outtt = 10;
    for (int l = 1; l <= ROW; l++) {
        for (int i = x/3*3; i < SQR + x/3*3; i++) {
            for (int j = y/3*3; j < SQR + y/3*3; j++){
                test = vec[i][j];
                for (test; test > 0; test = test / 10) {
                    //cout << test << " " << i << " " << j << endl;
                    if (test % 10 == l) {
                        //cout << "test" << endl;
                        if (untested) {
                            out = l;
                            outt = i;
                            outtt = j;
                            untested = false;
                        }
                        else {
                            out = 10;
                            outt = 10;
                            outt = 10;
                            //cout << endl << l << endl;
                        }
                    }
                }
            }
            //cout << "koniec";

        }
        if (outt < 9 && out < 9) {
            out = out * 100 + outt * 10 + outtt;
            return out;
        }
        untested = true;
    }
    return 0;
}





int main() {

    //creation of stuff
    srand((unsigned)time(0));
    vector<vector<int> > vecx;
    vector<vector<int> > stalyx;
    vector<vector<int> > rozx;
    vector<string> baza_sudoku;
    baza_sudoku.push_back("0000413230200003");
    baza_sudoku.push_back("4201104231002010");
    baza_sudoku.push_back("2100000010303014");
    baza_sudoku.push_back("4030034000202400");
    baza_sudoku.push_back("0004030200230240");
    baza_sudoku.push_back("0200043240010100");
    baza_sudoku.push_back("0021000330141002");
    baza_sudoku.push_back("0001014002140400");
    baza_sudoku.push_back("0300041302300120");
    baza_sudoku.push_back("3020403024030342");
    string t, sudoku;
    int num = 1;
    char a;
    int f, x, y, r, q, h, tak, cint;
    bool z = true;
    bool za = false;
    bool rozwiaz, wlas;
    int n = 0;
    f = rand() % 10;
    cout << "Your own sudoku?";
    cin >> tak;
    if (tak == 1) {
        cin >> sudoku;
    }
    else {
        sudoku = baza_sudoku[f];
    }

    if (sudoku.size() != ROW * COL) {
        return 0;
    }

    //vector of a main board
    for (int i = 0; i < ROW; i++) {
        vector<int> vecy;

        for (int j = 0; j < COL; j++) {
            a = sudoku.at(n);
            num = a - '0';
            vecy.push_back(num);
            n++;
        }
        vecx.push_back(vecy);
    }

    //vector of a fixed (starting) board
    n = 0;
    for (int i = 0; i < ROW; i++) {
        vector<int> stalyy;
        for (int j = 0; j < COL; j++) {
            a = sudoku.at(n);
            num = a - '0';
            stalyy.push_back(num);
            n++;
        }
        stalyx.push_back(stalyy);
    }


    cout << "Autosolve? (1 = yes; anything else = no) ";
    cin >> r;
    if (r == 1) {
        rozwiaz = false;
    }
    else {
        rozwiaz = true;
    }


    //solving it yourself
    while (rozwiaz) {
            system("CLS");
            display(vecx, false);
            cout << endl;
            if (!z) {
                cout << "Nie da sie" << endl << endl;
                z = true;
            }
            if (za) {
                cout << "Podaj puste pole" << endl << endl;
                za = false;
            }
            cout << "Podaj kolumne: ";
            cin >> y;
            cout << "Podaj wiersz: ";
            cin >> x;
            x--;
            y--;
            if (stalyx[x][y] == 0) {
                cout << "Podaj liczbe od 1-" << COL << ":";
                cin >> f;
                if (test(vecx, stalyx, x, y, f)) {
                    vecx[x][y] = f;
                }
                else {
                    z = false;
                }
            }
            else {
                za = true;
            }
            cout << endl;
            if (!does_exist(vecx, 0)) {
                display(vecx, false);
                cout << "Udalo ci sie";
                break;
            }

        }

    //autosolving
    while (!rozwiaz) {
            auto start = high_resolution_clock::now();
            //solving vector


            num = 0;
            for (int i = 0; i < ROW; i++) {
                vector<int> rozy;
                for (int j = 0; j < COL; j++) {
                    for (int s = 1; s <= COL; s++) {
                        if (stalyx[i][j] == 0) {
                            if (test(vecx, stalyx, i, j, s)) {
                                num = num * 10 + s;
                            }
                        }
                        else {
                            num = 0;
                        }
                    }
                    rozy.push_back(num);
                    num = 0;
                }
                rozx.push_back(rozy);
            }

            /*display(rozx, false);
            cout << endl;
            display(vecx, false);
            Sleep(500);*/
            //cin >> cint;
            //solving
            while (true) {
                for (int i = 0; i < ROW; i++) {
                    for (int j = 0; j < COL; j++) {
                        auto time = high_resolution_clock::now();
                        auto duration = duration_cast<microseconds>(time - start);
                        if (duration.count() > 11000000) {
                            system("CLS");
                            display(vecx, false);
                            cout << endl;
                            displaySolver(rozx);
                            cout << "couldn't compleate the puzzle";
                            return -1903458029589;
                        }
                        if (check_for_not(rozx, 0)) {
                            system("CLS");
                            display(vecx, false);
                            cout << endl << "completed";
                            auto stop = high_resolution_clock::now();
                            auto duration = duration_cast<microseconds>(stop - start);
                            cout << endl << "Time taken to solve: "
                                << duration.count() * 0.000001 << " seconds" << endl;
                            cin >> q;
                            return 0;
                        }
                        if (rozx[i][j] < ROW + 1 && rozx[i][j] > 0) {
                            vecx[i][j] = rozx[i][j];
                            r = rozx[i][j];
                            rozx = deleteDigits(i, j, r, rozx);

                            rozx[i][j] = 0;
                            /*system("CLS");
                            cout << endl;
                            display(vecx, false);
                            cout << endl;
                            displaySolver(rozx);
                            Sleep(500);*/
                        }
                        else {
                            /*system("CLS");
                            cout << endl;
                            display(vecx);
                            cout << endl;
                            display(rozx);*/
                        }
                        h = look_for_lonely_x(rozx, i);
                        //cout << "h = " << h;
                        //cin >> cint;
                        //return h;
                        //cout << j;
                        //cout << endl << endl << endl;
                        if (h > 0 && h < 99) {
                            //int h = look_for_lonely_x(rozx, i);
                            vecx[i][h % 10] = h / 10;
                            rozx[i][h % 10] = 0;
                            rozx = deleteDigits(i, h % 10, h / 10, rozx);
                            /*system("CLS");
                            display(vecx, false);
                            cout << endl;
                            displaySolver(rozx);*/
                            //return 2137;
                            h = 0;
                            //
                        }
                        //cin >> cint;
                        h = look_for_lonely_y(rozx, j);
                        if (h > 0 && h < 99) {
                            //int h = look_for_lonely_x(rozx, i);
                            vecx[h % 10][j] = h / 10;
                            rozx[h % 10][j] = 0;
                            rozx = deleteDigits(h % 10, j, h / 10, rozx);
                            /*system("CLS");
                            display(vecx, false);
                            cout << endl;
                            displaySolver(rozx);*/
                            //return 2137;
                            h = 0;
                            //system("CLS");
                        }
                        int inx, iny;
                        //cin >> inx;
                        //cin >> iny; 
                        h = look_for_lonely_square(rozx, i, j);
                        /*display(rozx, false);
                        cout << endl;
                        display(vecx, false);
                        cout << endl << h << " " << j + 1 << " " << i + 1 << endl;
                        //cin >> cint;*/
                        if (h > 0 && h < 999) {
                            //int h = look_for_lonely_x(rozx, i);
                            vecx[(h % 100) / 10][h % 10] = h / 100;
                            rozx[(h % 100) / 10][h % 10] = 0;
                            rozx = deleteDigits((h % 100) / 10, h % 10, h / 100, rozx);
                            /*system("CLS");
                            display(vecx, false);
                            cout << endl;
                            displaySolver(rozx);
                            //return 2137;
                            h = 0;
                            //system("CLS");*/
                        }
                        //cin >> cint;
                        //return 0;

                    }
                }
            }
        }
}