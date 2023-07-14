#include<stdio.h>
#include<conio.h>
#include<stdlib.h>
#include<Windows.h>

int gameover;//  oyun icin olusturulan global degiskenler
int score;
int en = 20;// karenin eni boyu
int boy = 20;
int x, y, fruitx, fruity, flag;//meyve yilan yonu koordinatlari icin olusturulan
//degiskenler
int tailX[10], tailY[10];//yilanin kuyruk uzunlugunu tutan 2 adet array
int tailLength = 0;//yilanin uzunlugunu belirleyen degisken

void Setup() {
	gameover = 0;
	x = boy / 2;// meyve icin olusturulan degiskenler
	y = en / 2;
label1:  // eger ki rand fonksiyonumuz 0 degerini verirse geri donmesi icin
	fruitx = rand() % 20;// olusturulan 2 adet etiket
	if (fruitx == 0)
		goto label1;
label2:
	fruity = rand() % 20;
	if (fruity == 0)
		goto label2;
	score = 0;
}

void Area() {

	system("cls");
	for (int i = 0; i < boy; i++) {// kareyi cizdiren for donguleri
		for (int j = 0; j < en; j++) {
			if (i == 0 || i == en - 1
				|| j == 0
				|| j == boy - 1) {
				printf("#");
			}
			else {
				int isTail = 0;// yilanin kuyrugunu kontrol eden degisken
				for (int k = 0; k < tailLength; k++) {
					if (i == tailX[k] && j == tailY[k]) {
						printf("$");// eger ki yilanin kuyruguysa yilana kuyruk
						//ekleyen dongu
						isTail = 1;
						break;
					}
				}
				if (!isTail) {
					if (i == x && j == y)
						printf("$");
					else if (i == fruitx// eger ki hicbiri degilse ekrana meyveyi
						&& j == fruity)//bastiran kisim
						printf("*");
					else
						printf(" ");
				}
			}
		}
		printf("\n");
	}

	printf("score = %d", score);
	printf("\n");
	printf("press X to quit the game");
}

void Input() {
	if (_kbhit()) {//conio.h kutuphanesinden gelen fonksiyondur.Klavyeden bir tusa
		//basilirsa 1 basilmazsa 0 degerini veren fonksiyondur.
		switch (_getch()) {//klavyeden veriyi almak icin kullanilan fonksiyon
		case 'a':
			flag = 1;
			break;
		case's':
			flag = 2;
			break;
		case'd':
			flag = 3;
			break;
		case 'w':
			flag = 4;
			break;
		case'x':
			gameover = 1;
			break;

		}
	}
}

void MoveTail() {//kuyrugun hareketini saglamak icin olusturulan fonksiyon
	int prevX = tailX[0];// yeni kuyruk verilerini tutmak icin olusturulan degiskenler
	int prevY = tailY[0];
	int tempX, tempY;
	tailX[0] = x;
	tailY[0] = y;
	for (int i = 1; i < tailLength; i++) {
		tempX = tailX[i];//burdaki for dongusu de kuyruk hareketini saglamak icin
		tempY = tailY[i];//olusturulmustur
		tailX[i] = prevX;
		tailY[i] = prevY;
		prevX = tempX;
		prevY = tempY;
	}
}

void Logic() {//oyunun mantik kismini olusturan fonksiyon
	Sleep(100);
	switch (flag) {
	case 1:       //flag degerlerine gore koordinatlari belirleyen kisim
		y--;
		break;
	case 2:
		x++;
		break;
	case 3:
		y++;
		break;
	case 4:
		x--;
		break;
	default:
		break;
	}
	if (x < 0 || x >= boy || y < 0 || y >= en)//eger ki yilan yanlara degerse 
		gameover = -1;// oyunu bitiren kisim

	for (int i = 0; i < tailLength; i++) { // eger ki yilan kendi kuyruguna degerse 
		if (x == tailX[i] && y == tailY[i]) {//oyunu bitiren kisim 
			gameover = -1;
			break;
		}
	}

	if (x == fruitx && y == fruity) {
	label3:
		fruitx = rand() % 20;//rand fonksiyonu meyvenin koordinat degerlerini
		if (fruitx == 0)//0 i vermemesi icin olusturulan etiketler
			goto label3;
	label4:
		fruity = rand() % 20;
		if (fruity == 0)
			goto label4;
		score += 10;
		tailLength++;
	}

	MoveTail();
}

int main() { // oyunu calistirabilmek icin olusturulan main fonksiyonu
	Setup();
	while (!gameover) {// oyun bitene kadar oynamamiz icin olusturulan while dongusu
		Area();
		Input();
		Logic();
	}
	return 0;
}
