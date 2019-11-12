#include<stdio.h>
#include<stdlib.h>
#include<time.h>
#define deck 52//????????????
int poker[52];
int play[7];
int pub[3], hole_1[5], hole_2[5];


//select card
void swap(int*a, int*b) {
	int sw = *a;
	*a = *b;
	*b = sw;
}
void setpoker() {
	for (int p = 0; p < deck; p++) {
		poker[p] = p + 1;
	}
}
void qkpk(int deal[], int q) {
	srand((unsigned)time(NULL));
	for (int t = 0; t < q; t++) {
		int k = rand() % (deck - t) + t;
		swap(&poker[k], &poker[t]);
		deal[t] = poker[t];
		printf("%d ", deal[t]);
	}
	printf("\n");
}
void split(int a, int b, int play[]) {
	for (int i = 0; i < 7; i++) {
		if (i < a) {
			pub[i] = play[i];
			hole_1[i] = play[i];
			hole_2[i] = play[i];
		}
		else if (a <= i && i < a + b) {
			hole_1[i] = play[i];
		}
		else if (a + b <= i && i < 7) {
			hole_2[i - b] = play[i];
		}
	}
}
void showcard(int a, int hole[]) {
	for (int i = 0; i < 5; i++) {
		printf("flower%d ", hole[i] / 14);
		printf("hole_%d[%d]:%d\n", a, i + 1, hole[i] % 13);
	}
}


//compare card
void Bubble_sort(int *a) {
	int i, j, t;
	for (j = 0; j < 4; j++)
		for (i = j + 1; i < 5; i++) {
			a[j] = a[j] % 13;
			a[i] = a[i] % 13;
			if (a[j] < a[i]) {
				t = a[j] % 13;
				a[j] = a[i];
				a[i] = t;
			}
		}
}
int pair(int hole[]) {
	int y = 0, c = 0;//number of pair&other
	for (int i = 0; i < 5; i++) {
		for (int t = i; t < 4; t++) {
			int si = hole[i] / 14, si1 = hole[t + 1] / 14;
			if (si == si1) c += 10;	//flower
			if (hole[i] % 13 == hole[t + 1] % 13)y += 10;//pair			
		}
	}
	for (int i = 0; i < 5; i++) {
		Bubble_sort(hole);
		if ((hole[i] - hole[i + 1]) == 1 && i < 4) {
			c += 1;  //
			if (i == 0 && hole[4] % 13 == 0) {	//A
				c += 1000;
				if (hole[0] - hole[4] == 12)c += 1000;
			}
		}
	}
	if (c > 2000) {
		if (c == 2103) {
			y = 101;//large royal flush
		}
		else if (c % 10 == 3) {
			y = 37;//large stright
		}
	}
	else if (c == 1104) {//small royal flush
		y = 100;
	}
	else if (c == 104) {//stright flush
		y = 70;
	}
	else if (c / 100 == 1) {//flush 
		y = 39;
	}
	else if (c % 10 == 4) {
		if (c > 1000) {
			y = 36;//small stright
		}
		else if (c < 104) {
			y = 35;//stright
		}
	}
	else if (y == 0) {
		if (c == 10) {//high card
			y = 0;
		}
		else y = -1;//other
	}
	return y;
}
//compare number
//pair num
int precount(int y, int hole[]) {
	int i;
	for (i = y; i < 4; i++) {
		if (hole[i] == hole[i + 1]) {
			break;
		}
	}
	return hole[i];
}
//single num
void preprecount(int hole1[], int hole2[]) {
	int winner;
	for (int i = 0; i < 5; i++) {
		if (hole1[i] != hole2[i]) {
			printf("\nwinner is player %d", hole1[i] > hole2[i] ? (winner = 1) : (winner = 2));
			break;
		}
		if (i == 4) {
			printf("\nTIE");
			break;
		}
	}
}
void count(int *b1, int *b2, int hole_1[], int hole_2[]) {
	int winner;
	if (*b1 != *b2)
		printf("\nwinner is player %d", *b1 > *b2 ? (winner = 1) : (winner = 2));
	if (*b1 == *b2) {
		if (*b1 == 36 || *b1 == 37 || *b1 == 100 || *b1 == 101) {
			printf("\nTIE");
		}
		else if (*b1 <= 0) {
			int g1 = hole_1[0] % 13 + hole_1[1] % 13 + hole_1[2] % 13 + hole_1[3] % 13 + hole_1[4] % 13;
			int g2 = hole_2[0] % 13 + hole_2[1] % 13 + hole_2[2] % 13 + hole_2[3] % 13 + hole_2[4] % 13;
			printf("\ng1=%d g2=%d\n", g1, g2);
			if (g1 != g2) {
				printf("\nwinner is player %d", g1 > g2 ? (winner = 1) : (winner = 2));
			}
			else preprecount(hole_1, hole_2);
		}
		else if (*b1 > 0) {
			if (*b1 == 20) {
				for (int y = 0; y < 4; y++) {
					int d1 = precount(y, hole_1);
					int d2 = precount(y, hole_2);
					if (d1 != hole_2[y]) {
						printf("\nwinner is player %d", hole_1[y] > hole_2[y] ? (winner = 1) : (winner = 2));
						break;
					}
				}
			}
			if (*b1 == 39 || *b1 == 35 || *b1 >= 70) {
				preprecount(hole_1, hole_2);
			}
			else {
				int d1 = precount(0, hole_1);
				int d2 = precount(0, hole_2);
				if (d1 == d2) {
					preprecount(hole_1, hole_2);
				}
				else printf("\nwinner is player %d", *b1 > *b2 ? (winner = 1) : (winner = 2));
			}
		}
	}
}


int main() {
	setpoker();
	qkpk(play, 7);
	split(3, 2, play);
	//int hole_1[5] = {0,1,1,4,28};
	//int hole_2[5] = {1,1,26,4,29};
	showcard(1, hole_1);
	printf("\n");
	showcard(2, hole_2);
	int a1 = pair(hole_1);
	int a2 = pair(hole_2);
	printf("a1=%d\na2=%d", a1, a2);
	count(&a1, &a2, hole_1, hole_2);
	return 0;
}