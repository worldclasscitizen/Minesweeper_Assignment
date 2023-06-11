#include "minesweeper.h"

// 2019102903 최 진우
// Project 1

void minesweeper( string commands, string output );
void _load_( string, int**, char**, int );
void _touch_ ( int x, int y, int**, char**, bool**, bool&, int& ); // (x, y) 는 플레이어가 터치할 Coordination 값
// 좌표값이 2차원 배열 내에 없다면, 아무 일도 일어나지 않는다.
// touch 를 통해 밝혀질 space 는 터치한 공간만 밝혀진다. 실제 minesweeper처럼 한 번에 여러 개의 space가 공개되는 것이 아니라는 뜻이다.

void _display_ ( int**, char**, bool**, bool, int, ofstream& ); // 현재 board 상황을 출력
// touch된 space는 그 옆에 몇 개의 bombs가 이웃하고 있는지를 숫자로 표시하여 나타낸다.
// 이웃하고 있는 bomb가 없으면 0으로 표시한다.


int main() {
	cout << "Testing minesweeper" << endl;
	minesweeper("./test1commands.txt", "test1_output_mine.txt");
	minesweeper("./test2commands.txt", "test2_output_mine.txt");
	minesweeper("./test3commands.txt", "test3_output_mine.txt");
	minesweeper("./test4commands.txt", "test4_output_mine.txt");
	minesweeper("./test5commands.txt", "test5_output_mine.txt");
	minesweeper("./test6commands.txt", "test6_output_mine.txt");
	minesweeper("./test7commands.txt", "test7_output_mine.txt");
	minesweeper("./test8commands.txt", "test8_output_mine.txt");
	minesweeper("./test9commands.txt", "test9_output_mine.txt");
	minesweeper("./test10commands.txt", "test10_output_mine.txt");

	return 0;
}

void minesweeper( string commands, string output ) {
	int** arr = new int* [8];
    char** chr = new char* [8];
    bool** touched = new bool* [8];
    bool finished = false;
    bool bombBoom = false;
    int touchCount = 0;

	for(int i = 0; i < 8; i++) {
		arr[i] = new int[8];
        chr[i] = new char[8];
        touched[i] = new bool[8];
	} // 배열 선언

    for(int q = 0; q < 8; q++) {
        for(int w = 0; w < 8; w++) {
            touched[q][w] = false;
        }
    }
    
	ifstream rd;
    rd.open(commands);
	ofstream wr; // i/ofstream 선언	
    wr.open(output);

    // commands 파일에서 xpos 와 ypos 를 얻어와야 함
    // 그 전에, Command : display 를 처리할 함수를 만들어줘야 한다.
    string fnct, boardname;
    
    rd >> fnct; // 모든 파일이 load 로 시작하므로 if 함수는 쓰지 않았다.
    rd >> boardname; // 그 다음엔 board file 이 있으므로 이름을 입력받는다.
    wr << "Command: load " << boardname << endl;
    _load_(boardname, arr, chr, touchCount); // 2차원 배열 할당, arr은 숫자로 이루어진 배열이고, chr는 . 과 * 로 이루어진 배열

    
    while(!(rd.eof())) {
        fnct = "";
        rd >> fnct;
        if(bombBoom == true) {
            break;
        }
        if(fnct == "display") {
            wr << "Command: display" << endl;
            _display_(arr, chr, touched, finished, touchCount, wr);
        }
        else if(fnct == "touch" && finished == false) {
            int xpos, ypos;
            rd >> xpos >> ypos;
            wr << "Command: touch " << xpos << " " << ypos;
            _touch_(xpos, ypos, arr, chr, touched, bombBoom, touchCount);
                touchCount++;
            if(touchCount == 54) { finished = true; break; }
            if(bombBoom == true) { finished = true; break; }
            wr << endl;
        }
    }

	// for(int k = 0; k < 8; k++) {
    //     for(int q = 0; q < 8; q++) {
    //         cout << setw(3) << arr[k][q];
    //     }
    //     cout << endl;
    // } // arr 출력해보기

	// for(int k = 0; k < 8; k++) {
    //     for(int q = 0; q < 8; q++) {
    //         cout << chr[k][q];
    //     }
    //     cout << endl;
    // } // chr 출력해보기

    wr << endl;

    wr << "Game Over" << endl;
    wr << "~~~~~~~~~" << endl;
    wr << "Final Board" << endl;
    finished = true;
    _display_(arr, chr, touched, finished, touchCount, wr);

}
void _load_( string boardname, int** arr, char** chr, int touchCount ) {
    ifstream rd;
	rd.open(boardname);
    string line;
    char ch;
	
    for(int i = 0; i < 8; i++) {
        getline(rd, line);
        for(int j = 0; j < 8; j++) {
            ch = line.at(j);
			chr[i][j] = ch;
            if(ch == '.') {
                arr[i][j] = 0;
            }
            else if(ch == '*') {
                arr[i][j] = -1; // int형 vector에 다른 자료형을 저장하는 법을 몰라서 일단 * 을 -1로 치환했음.
            }
        }
    }

    for(int q = 0; q < 8; q++) {
        for(int w = 0; w < 8; w++) {
            if(chr[q][w] == '*') {
                if(w == 0) {
                    if(q == 0) {
                        if(chr[1][0] != '*') {
                            arr[1][0] += 1;
                        }
                        if(chr[0][1] != '*') {
                            arr[0][1] += 1;
                        }
                        if(chr[1][1] != '*') {
                            arr[1][1] += 1;
                        }
                    }
                    else if(q == 7) {
                        if(chr[6][0] != '*') {
                            arr[6][0] += 1;
                        }
                        if(chr[6][1] != '*') {
                            arr[6][1] += 1;
                        }
                        if(chr[7][1] != '*') {
                            arr[7][1] += 1;
                        }
                    }
                    else {
                        if(chr[q-1][w] != '*') {
                            arr[q-1][w] += 1;
                        }
                        if(chr[q-1][w+1] != '*') {
                            arr[q-1][w+1] += 1;
                        }
                        if(chr[q][w+1] != '*') {
                            arr[q][w+1] += 1;
                        }
                        if(chr[q+1][w+1] != '*') {
                            arr[q+1][w+1] += 1;
                        }
                        if(chr[q+1][w] != '*') {
                            arr[q+1][w] += 1;
                        }
                    }
                }
                else if(q == 0) {
                    if(w == 7) {
                        if(chr[0][6] != '*') {
                            arr[0][6] += 1;
                        }
                        if(chr[1][6] != '*') {
                            arr[1][6] += 1;
                        }
                        if(chr[1][7] != '*') {
                            arr[1][7] += 1;
                        }
                    }
                    else {
                        if(chr[q][w-1] != '*') {
                            arr[q][w-1] += 1;
                        }
                        if(chr[q+1][w-1] != '*') {
                            arr[q+1][w-1] += 1;
                        }
                        if(chr[q+1][w] != '*') {
                            arr[q+1][w] += 1;
                        }
                        if(chr[q+1][w+1] != '*') {
                            arr[q+1][w+1] += 1;
                        }
                        if(chr[q][w+1] != '*') {
                            arr[q][w+1] += 1;
                        }
                    }
                }
                else if(w == 7) {
                    if(q == 7) {
                        if(chr[6][7] != '*') {
                            arr[6][7] += 1;
                        }
                        if(chr[6][6] != '*') {
                            arr[6][6] += 1;
                        }
                        if(chr[7][6] != '*') {
                            arr[7][6] += 1;
                        }
                    }
                    else {
                        if(chr[q-1][w] != '*') {
                            arr[q-1][w] += 1;
                        }
                        if(chr[q-1][w-1] != '*') {
                            arr[q-1][w-1] += 1;
                        }
                        if(chr[q][w-1] != '*') {
                            arr[q][w-1] += 1;
                        }
                        if(chr[q+1][w-1] != '*') {
                            arr[q+1][w-1] += 1;
                        }
                        if(chr[q+1][w] != '*') {
                                arr[q+1][w] += 1;
                            }
                    }
                }
                else if(q == 7) {
                    if(chr[q][w-1] != '*') {
                        arr[q][w-1] += 1;
                    }
                    if(chr[q-1][w-1] != '*') {
                        arr[q-1][w-1] += 1;
                    }
                    if(chr[q-1][w] != '*') {
                        arr[q-1][w] += 1;
                    }
                    if(chr[q-1][w+1] != '*') {
                        arr[q-1][w+1] += 1;
                    }
                    if(chr[q][w+1] != '*') {
                        arr[q][w+1] += 1;
                    }
                }
                else {
                    if(chr[q-1][w-1] != '*') {
                        arr[q-1][w-1] += 1;
                    }
                    if(chr[q-1][w] != '*') {
                        arr[q-1][w] += 1;
                    }
                    if(chr[q-1][w+1] != '*') {
                        arr[q-1][w+1] += 1;
                    }
                    if(chr[q][w+1] != '*') {
                        arr[q][w+1] += 1;
                    }
                    if(chr[q+1][w+1] != '*') {
                        arr[q+1][w+1] += 1;
                    }
                    if(chr[q+1][w] != '*') {
                        arr[q+1][w] += 1;
                    }
                    if(chr[q+1][w-1] != '*') {
                        arr[q+1][w-1] += 1;
                    }
                    if(chr[q][w-1] != '*') {
                        arr[q][w-1] += 1;
                    }
                }
            }
        }
    }
	return;
}

void _touch_( int x, int y, int** arr, char** chr, bool** touched, bool& bombBoom, int& touchCount ) {
	if(chr[x-1][y-1] != '*') {
        touched[x-1][y-1] = true;
    }
    else {
        chr[x-1][y-1] = '#';
        bombBoom = true;
    }
    // cout << "Command: touch " << x << " " << y << endl;
}

void _display_( int** arr, char** chr, bool** touched, bool finished, int touchCount, ofstream& wr ) {
    for(int i = 0; i < 8; i++) {
        for(int j = 0; j < 8; j++) {
            if(touched[i][j] == false) { // 터치가 안 된 자리라면 . 을 출력한다.
                if(chr[i][j] == '*' && finished == true) { // Final display 면 터지지 않은 폭탄은 @ 로 바꿔준다.
                    wr << '@';
                }
                else if(chr[i][j] == '*' && finished == false) {
                    wr << '.';
                }
                else if(arr[i][j] >= 0 && arr[i][j] <= 9) {
                    wr << '.';
                }
                else if(chr[i][j] == '#') { // 폭탄을 터치했다면 거기서 touch 함수는 종료될 것이다.
                    wr << '*';
                }
            }
            else if(chr[i][j] != '*') { // touch가 되어 있고, 그 자리가 폭탄 자리가 아니라면
                wr << arr[i][j]; // arr의 값을 출력한다. arr은 추후에 이웃한 폭탄의 개수를 업데이트 해줄 필요가 있다.
            }
            else if(chr[i][j] == '#') { // 폭탄을 터치했다면 거기서 touch 함수는 종료될 것이다.
                wr << '*';
            }
        }
        wr << endl;
    }
    if(finished == true) {
        wr << endl;
        wr << "Spaces touched: " << touchCount << endl;
    }
}