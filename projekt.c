#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>

enum MonsterType {GOBLIN, ORK, SMOK};

void clearBuffer()
{
	if (!feof(stdin))
		getchar();
}

void clearBuffer1()
{
	int c;
	while ((c = getchar()) != '\n' && c != EOF) {}
}

typedef struct character
{
	int pos[2];
	char icon;
	int hp;
	int attack;
	int loot;
}character;

typedef struct player
{
	int pos[2];
	char icon;
	int hp;
	int attack;
	int gold;
	int mixtures;
}player;

typedef struct weapon
{
	char *name;
	int damage;
	int cost;
}weapon;

void clearMap(char* map, int *mapSize)
{
	for (int i = 0; i<mapSize[0]; i++)
	{
		for (int j = 0; j<mapSize[1]; j++)
			*(map + i*mapSize[1] + j) = ' ';
	}
}

void DrawHealth(int health)
{
	printf("HP: ");
	for (int i = 0; i<health/4; i++)
	{
		printf("|");
	}
	printf("\n");
}

void DrawPlayer(player obj, char *map, int *mapSize)
{
	*(map+obj.pos[0]*mapSize[1] + obj.pos[1]) = obj.icon;
}

void DrawCharacter(character obj, char *map, int *mapSize)
{
	*(map+obj.pos[0]*mapSize[1] + obj.pos[1]) = obj.icon;
}

void DrawAll(player player, character *objects, int objCount, char *map, int *mapSize)
{
	DrawPlayer(player, map, mapSize);
	for (int i = 0; i<objCount; i++)
	{
		DrawCharacter(*(objects+i), map, mapSize);
	}
}

void AddMonster(int *pos, enum MonsterType type, character *objects, int *objCount)
{
	if (type == GOBLIN)
	{
		character goblin = {pos[0], pos[1], 'G', 30, 4, 2};
		*(objects + *objCount) = goblin;
		(*objCount)++;
	}
	if (type == SMOK)
	{
		character smok = {pos[0], pos[1], 'S', 400, 20, 1000};
		*(objects + *objCount) = smok;
		(*objCount)++;
	}
}

void Render2(char *map, int *mapSize, int *margin)
{
	for (int i = 0; i<margin[0]-1; i++)
	{
		printf("\n");
	}
	for (int j = 0; j<mapSize[1]+margin[1]; j++)
		if (j<margin[1])
			printf("  ");
		else
			printf("__");
	printf("\n");
	for (int i = 0; i<mapSize[0]; i++)
	{
		for (int j = 0; j<mapSize[1]+margin[1]; j++)
		{
			if (j<margin[1]-1)
				printf("  ");
			else if (j == margin[1]-1)
				printf(" |");
			else
				printf("%c ", *(map + i*mapSize[1] + j - margin[1]));
		}
		printf("|\n");
	}
	for (int j = 0; j<mapSize[1]+margin[1]; j++)
		if (j<margin[1]-1)
			printf("  ");
		else if (j == margin[1]-1)
			printf(" |");
		else
			printf("__");
	printf("|\n");
	for (int i = 0; i<margin[0]-1; i++)
	{
		printf("\n");
	}
}

int areInFight(player player, character object)
{
	if (player.pos[0] == object.pos[0] && (player.pos[1]-object.pos[1] == -1 ||player.pos[1]-object.pos[1] == 1))
		return 1;
	else if	(player.pos[1] == object.pos[1] && (player.pos[0]-object.pos[0] == -1 ||player.pos[0]-object.pos[0] == 1))
	return 1;
	
	else
		return 0;
}

void DrawShop(int *pos, char *map, int *mapSize)
{
	*(map + pos[1]*mapSize[0] + pos[0]) = '[';
	*(map + pos[1]*mapSize[0] + pos[0]+1) = ']';
}

int isInShop(player player, int *shopPos)
{
	if (player.pos[1] == shopPos[0] && (player.pos[0]-shopPos[1] == -1 ||player.pos[0]-shopPos[1] == 1))
		return 1;
	else if	(player.pos[0] == shopPos[1] && (player.pos[1]-shopPos[0] == -1 ||player.pos[1]-shopPos[0] == 2))
		return 1;
	else if (player.pos[1] == shopPos[0]+1 && (player.pos[0]-shopPos[1] == -1 ||player.pos[0]-shopPos[1] == 1))
		return 1;
	else
		return 0;
}

void Shop(weapon *weapons, player *player)
{
	while(1)
	{
		system("clear");
		for (int i = 0; i<6; i++)
		{
			printf("%d. %s  Obrazenia: %d  Cena: %d\n", i+1, (*(weapons+i)).name, (*(weapons+i)).damage, (*(weapons+i)).cost);
		}
		printf("7. Mikstura lecznicza  +40pkt. zdrowia  Cena: 2\n");
		printf("8. Wyjscie");
		printf("\n");
		system("/bin/stty raw");
		int c = getchar();
		system("/bin/stty cooked");
		if (c==48+8)
			return;
		else if (c>=48+1 && c<=48+6)
		{
			if ((*player).gold>=(*(weapons+c-1-48)).cost)
			{
				(*player).attack = (*(weapons+c-1-48)).damage;
				(*player).gold-=(*(weapons+c-1-48)).cost;
				return;
			}
			else
				system("clear");
				printf("Nie masz dosyc pieniedzy!\n\n");
				printf("Wcisnij dowolny przycisk by kontynuowac...\n");
				getchar();
				getchar();
				return;
		}
		else if (c == 48 + 7)
		{
			if ((*player).gold>=2)
			{
				(*player).mixtures = (*player).mixtures+1;
				(*player).gold = (*player).gold-2;
				return;
			}
			else
				system("clear");
				printf("Nie masz dosyc pieniedzy!\n\n");
				printf("Wcisnij dowolny przycisk by kontynuowac...\n");
				getchar();
				getchar();
				return;
		}
	}
}

void Intro()
{
	system("clear");
	printf("Zabijaj gobliny i pokonaj smoka by wybawic krainei zdobyć chwale poteznego rycerza! \
\nKontrolowanie postaci:\
\nRuch postacia: W,S,A,D\
\nAtak: Spacja \
\nWejscie do sklepu: E \
\nSpozycie mikstury: Q");
	system("/bin/stty raw");
	int key = getchar();
	system("/bin/stty cooked");
	system("clear");
	printf("Graj na zmaksymalizowanej konsoli!");
	system("/bin/stty raw");
	int key = getchar();
	system("/bin/stty cooked");
}

int main()
{
	Intro();
	srand( time( NULL ));
	int mapSize[] = {20, 20};
	char map[mapSize[0]][mapSize[1]];
	clearMap((char*)map, mapSize);
	
	int shop[] = {10, 15};
	
	int goblinSpawnTime = 15;
	int goblinTimer = goblinSpawnTime;

	int margin[] = {3, 3};
	player player = {10, 10, 'o', 100, 3, 0, 1};
	character *objects = malloc(mapSize[0]*mapSize[1]*sizeof(character));
	int objCount = 0;
	int gameExit = 0;
	
	{int pos[] = {5,5};
	AddMonster(pos, GOBLIN, objects, &objCount);}
	{int pos[] = {3,5};
	AddMonster(pos, GOBLIN, objects, &objCount);}
	{int pos[] = {4,7};
	AddMonster(pos, GOBLIN, objects, &objCount);}
	{int pos[] = {6,7};
	AddMonster(pos, GOBLIN, objects, &objCount);}
	{int pos[] = {2,2};
	AddMonster(pos, GOBLIN, objects, &objCount);}
	{int pos[] = {3,1};
	AddMonster(pos, GOBLIN, objects, &objCount);}
	{int pos[] = {3,3};
	AddMonster(pos, GOBLIN, objects, &objCount);}
	{int pos[] = {6,3};
	AddMonster(pos, GOBLIN, objects, &objCount);}
	{int pos[] = {2,6};
	AddMonster(pos, GOBLIN, objects, &objCount);}
	{int pos[] = {17,17};
	AddMonster(pos, SMOK, objects, &objCount);}
	
	weapon weapons[6];
	{weapon x = {"Sztylet", 5, 2};
	weapons[0] = x;}
	{weapon x = {"Miecz krotki", 10, 6};
	weapons[1] = x;}
	{weapon x = {"Miecz dlugi", 15, 13};
	weapons[2] = x;}
	{weapon x = {"Katana", 20, 20};
	weapons[3] = x;}
	{weapon x = {"Anduril", 40, 40};
	weapons[4] = x;}
	{weapon x = {"Miecz swietlny", 80, 80};
	weapons[5] = x;}
	
	system("clear");
	clearMap((char*)map, mapSize);
	DrawAll(player, objects, objCount, (char*)map, mapSize);
	DrawShop(shop, (char*)map, mapSize);
	DrawHealth(player.hp);
	printf("$: %d\n", player.gold);
	printf("Mikstury: %d\n", player.mixtures);
	Render2((char*)map, mapSize, margin);
	

	while (!gameExit)
	{
		system("/bin/stty raw");
		int key = getchar();
		system("/bin/stty cooked");
		switch (key)
		{
			case 's':
				if (player.pos[0]<mapSize[0]-1 && map[player.pos[0]+1][player.pos[1]] == ' ')
					player.pos[0]++;
				break;
			case 'w':
				if (player.pos[0]>0 && map[player.pos[0]-1][player.pos[1]] == ' ')
					player.pos[0]--;
				break;
			case 'a':
				if (player.pos[1]>0 && map[player.pos[0]][player.pos[1]-1] == ' ')
					player.pos[1]--;
				break;
			case 'd':
				if (player.pos[1]<mapSize[1]-1 && map[player.pos[0]][player.pos[1]+1] == ' ')
					player.pos[1]++;
				break;
			case 'e':
				if (isInShop(player, shop))
				{
					Shop(weapons, &player);
				}
				break;
			case ' ':
				for (int i = 0; i<objCount; i++)
				{
					if (areInFight(player, *(objects+i)))
					{
						(*(objects+i)).hp-=player.attack;
						if ((*(objects+i)).hp<0)
						{
							(*(objects+i)).attack = 0;
							(*(objects+i)).icon = ' ';
							player.gold+=(*(objects+i)).loot;
							(*(objects+i)).pos[0] = -10;
							(*(objects+i)).pos[1] = -10;
						}
					}
				}
				break;
			case 'q':
				if (player.mixtures>0)
				{
					player.mixtures--;
					player.hp+=40;
					if (player.hp>100)
						player.hp = 100;
				}
				break;
			case 27:
				return 0;
		}
		
		if (player.hp<=0)
			break;

		for (int i = 0; i<objCount; i++)
		{
			if (areInFight(player, *(objects+i)))
			{
				player.hp-=(*(objects+i)).attack;
			}
		}
		
		system("clear");
		clearMap((char*)map, mapSize);
		DrawAll(player, objects, objCount, (char*)map, mapSize);
		DrawShop(shop, (char*)map, mapSize);
		DrawHealth(player.hp);
		printf("$: %d\n", player.gold);
		printf("Mikstury: %d\n", player.mixtures);
		Render2((char*)map, mapSize, margin);
		
		goblinTimer--;
		if (goblinTimer==0)
		{
			goblinTimer = goblinSpawnTime;
			while(1)
			{
				int posx = rand()%mapSize[0];
				int posy = rand()%mapSize[1];
				
				if (map[posx][posy] == ' ')
				{
					int pos[] = {posx, posy};
					AddMonster(pos, GOBLIN, objects, &objCount);
					break;
				}
			}
		}
	}
	system("clear");
	printf("Koniec gry...\n");
}
