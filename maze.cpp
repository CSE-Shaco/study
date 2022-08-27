#include <iostream>
#include <cstring>
#include <utility>
using namespace std;

class Maze {
private:
	int x;
	int y;
	char dir;
	bool isValidMove(int k) {
		if (maze[x + dx[k]][y + dy[k]] == '.') {
			return true;
		}
		else {
			return false;
		}
	}
	char maze[15][15];
	char mmap[15][15];
public:
	const int dx[4]{ -1, 0, 1, 0 }, dy[4]{ 0, -1, 0, 1 };
	Maze() {
		x = 0;
		y = 0;
		makeMaze();
		initMap();
	}
	bool flag;
	pair<int, int> coo() {
		return make_pair(x, y);
	}
	void printMap() {
		for (int i{ 0 }; i < 15; ++i) {
			for (int j{ 0 }; j < 15; ++j) {
				cout << mmap[i][j] << ' ';
			}
			cout << '\n';
		}
		cout << '\n';
	}
	void renew() {
		mmap[x][y] = 'J';
		for (int i{ 0 }; i < 4; ++i) {
			int mx{ x + dx[i] }, my{y + dy[i]};
			if (mx >= 0 && mx <= 14 && my >= 0 && my <= 14) {
				mmap[mx][my] = maze[mx][my];
			}
			mmap[0][0] = 'S';
			mmap[14][14] = 'E';
		}
	}
	void move(int k) {
		if (isValidMove(k)) {
			flag = true;
			x += dx[k];
			y += dy[k];
			renew();
		}
		else {
			flag = false;
			cout << "벽으로는 이동할 수 없습니다.\n";
		}
	}
	void setdir() {
		switch (dir) {
		case 'W':
		case 'w':
			move(0);
			break;
		case 'A':
		case 'a':
			move(1);
			break;
		case 'S':
		case 's':
			move(2);
			break;
		case 'D':
		case 'd':
			move(3);
			break;
		default:
			cout << "올바르지 않은 입력입니다.\n";
			inputdir();
		}
	}
	void inputdir() {
		cout << "이동할 방향을 입력해주세요.\n( w : 위쪽, a : 왼쪽, s : 아래쪽, d : 오른쪽, 대소문자 구분 없음 )\n";
		cin >> dir;
		setdir();
	}
	void initMap() {
		memset(mmap, '?', sizeof(mmap));
		mmap[0][0] = 'J';
		mmap[14][14] = 'E';
		mmap[0][1] = maze[0][1];
		mmap[1][0] = maze[1][0];
	}
	void makeMaze() {
		for (int i{ 0 }; i < 15; ++i) {
			for (int j{ 0 }; j < 15; ++j) {
				int n{ rand() % 4 };
				if (n) {
					maze[i][j] = '.';
				}
				else {
					maze[i][j] = '#';
				}
			}
		}
		maze[0][0] = maze[14][14] = '.';
	}
};

int main() {
	Maze M;
	M.printMap();
	while (M.coo() != make_pair(14, 14)) {
		M.inputdir();
		while (!M.flag) {
			M.inputdir();
		}
		M.printMap();
	}
	cout << "재성이는 무사히 집에 돌아갔습니다.";
}
