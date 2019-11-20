#include <stdio.h>
#include <stdlib.h>
#include"time.h"
/* run this program using the console pauser or add your own getch, system("pause") or input loop */


 

int draw();

int cardindex = 0;

static history[52] = { 0, };

 

int main() {

	int card[4][13];

	int youcard[11], youmoney = 50, youbet, yousum;

	int playercard[5][11], playermoney[5] = { 50, 50, 50, 50, 50 }, playerbet[5], playersum[5];

	int totalplayer, i, j, k, n, num1, flag = 0, one;

	int round = 0;

	char shape[4][4] = { { "SPD" },{ "CLV" },{ "DIA" },{ "HRT" } };

	char numshape[13][6] = { { "1" },{ "2" },{ "3" },{ "4" },{ "5" },{ "6" },{ "7" },{ "8" },{ "9" },{ "10" },{ "Jack" },{ "Queen" },{ "King" } };

 

	for (i = 0; i < 4; i++) { //카드 숫자 설정

		for (j = 0; j < 10; j++)

			card[i][j] = j + 1;

		for (j = 10; j < 13; j++)

			card[i][j] = 10;

	}

	srand((unsigned)time(NULL)); //new seed

	printf("Input the number of players <MAX:5>: ");

	scanf("%d", &totalplayer);

	while (1) {

		round++;

		yousum = 0;

		for (i = 0; i < totalplayer; i++)

			playersum[i] = 0;

		printf("--------------- ROUND %d <cardIndex:%d> ---------------\n", round, cardindex);

		printf("----------BETTIND STEP----------\n=>your betting <total:$%d> : ", youmoney);

		scanf("%d", &youbet);

		youmoney -= youbet;

		for (i = 0; i < totalplayer; i++) {

			playerbet[i] = rand() % (youbet + 3) + 1;

			printf("=>player%d bets $%d <out of %d>\n", i + 1, playerbet[i], playermoney[i]);

			playermoney[i] -= playerbet[i];

		}

		youcard[0] = draw();

		youcard[1] = draw();

		yousum = card[youcard[0] / 13][youcard[0] % 13] + card[youcard[1] / 13][youcard[1] % 13];

		printf("----------CARD OFFERING----------\n");

		printf("=> you\t\t: %s%s  %s%s\n", shape[youcard[0] / 13], numshape[youcard[0] % 13], shape[youcard[1] / 13], numshape[youcard[1] % 13]);

		for (i = 0; i < totalplayer; i++) {

			playercard[i][0] = draw();

			playercard[i][1] = draw();

			playersum[i] = card[playercard[i][0] / 13][playercard[i][0] % 13] + card[playercard[i][1] / 13][playercard[i][1] % 13];

			printf("=> player %d\t: %s%s  %s%s\n", i + 1, shape[playercard[i][0] / 13], numshape[playercard[i][0] % 13], shape[playercard[i][1] / 13], numshape[playercard[i][1] % 13]);

		}

		printf("---------------GAME START---------------\n");

		flag = 1;

		printf(">>> my turn !\n");

		i = 2;

		one = 0;

		while (flag) {

			printf("=> card : ");

			for (j = 0; j < i; j++)

				printf("%s%s  ", shape[youcard[j] / 13], numshape[youcard[j] % 13]);

			printf(" ::: Action? (1-go, others-stay) : ");

			scanf("%d", &flag);

			youcard[i] = draw();

			yousum += card[youcard[i] / 13][youcard[i] % 13];

			i++;

		}

		printf("\n");

		for (k = 0; k < totalplayer; k++) {

			i = 2;

			flag = 1;

			one = 0;

			num1 = 0; //필요한 카드의 수

			printf(">>> player %d turn!\n ", i - 1);

			while (flag) {

				printf("=> card : ");

				for (j = 0; j < i; j++)

					printf("%s%s  ", shape[playercard[k][j] / 13], numshape[playercard[k][j] % 13]);

				for (j = 1; j < 21 - playersum[k]; j++) {

					for (n = 0; i < 4; n++) {

						if (history[13 * n + j - 1] == 0)

							num1++;

					}

				}

				if ((float)(num1 / (52 - cardindex)) >= 0.5) {

					flag = 1;

					printf(" ::: Go!\n");

				}

				else {

					flag = 0;

					printf(" ::: Stay!\n");

				}

				playercard[k][i] = draw();

				playersum[k] += card[playercard[k][i] / 13][playercard[k][i] % 13];

				if (playersum[k] > 21) 

					flag = 0;

				i++;

			}

		}

	}

}

int draw() {

	int d;

	srand((unsigned)time(NULL)); //new seed

	while (1) {

		d = rand() % 52;

		if (history[d] == 0) {

			history[d] = 1;

			cardindex++;

			return d;

		}

	}

}
