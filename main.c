#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include <string.h>
#define NUM 151
#define NUM_fmoves 68
#define NUM_cmoves 146
#define lin 18
#define col 18
#define BONUS 1.30
const char *basestats = "base_stats.txt";
const char *fastmoves = "fast_moves.txt";
const char *chargedmoves = "charged_moves.txt";
const char *possiblefmoves = "possible_fmoves.txt";
const char *possiblecmoves = "possible_cmoves.txt";//count++;
const char *matrizmult = "matriz_mult.txt";
const char *typeNames = "all.txt";
typedef struct{
	float atk, nvl, def, sta, hp, dano_finalFast, dano_finalCharged, climaBonus, te, stabfast, stabcharged, energy;
	/*Ataque, nivel, defesa, Pontos de Saude (PS) e Nivel de Experiencia.*/
	//stamina = base para hp
	int fmoveNum, cmoveNum, num, fmovemp, fmoveEnergy_boost, cmovemp, cmoveEnergy_boost;
	/*numero do pok, dano do golpe, ganho de energia*/
	char name[20], fmovename[30], cmovename[30], type1[10], type2[10], fastAttackType[10], chargedAttackType[10];
}basicStats;
basicStats pokemon[NUM];

typedef struct{
	int num, fmovemp, fmoveEnergy_boost;
	char fmovename[30], type[10];
}Tfmoves;
Tfmoves fmoves[NUM_fmoves];
//estrutura que ira receber os dados dos fastmoves

typedef struct{
	int num, cmovemp, cmoveEnergy_boost;
	char cmovename[30], type[10];
}Tcmoves;
Tcmoves cmoves[NUM_cmoves];
//estrtura que ira receber os dados dos chargedmoves

typedef struct{
	float matrizMult[lin][col];
	//matriz com os valores do TipoEficacia
	char **allTypes;
	//Todos os tipos de atks
}Taux;
Taux aux;
//struct com dados auxiliares, como atks possiveis e nomes de tipo

Taux preencherMatriz(void){ // NAO TERMINADA
	/*funcao para alocar dinamicamente em matrizes informacoes contidas em arq.txt*/
	FILE *fp, *fp1;
	int len, k=0;	
	char *str = (char *)malloc(sizeof(char)*9);
	fp = fopen(matrizmult, "r");
	fp1 = fopen(typeNames, "r");
	aux.allTypes = (char **)malloc(18*sizeof(char));
	/*reserva espaço para as linhas, numeros ja definidos*/
	for(int i=0;i<lin;i<i++){
		for(int j=0;j<col;j++){
			fscanf(fp, "%f\t", &aux.matrizMult[i][j]);
		}
	}
	for(int i=0;i<18;i++){
		aux.allTypes[i] = malloc(9);
		fgets(str, 9, fp1);
		len = strlen(str);
		strcpy(aux.allTypes[i], str);
	}
	fclose(fp);
	fclose(fp1);
	free(aux.allTypes);
	free(str);
}

basicStats hpGenerator(basicStats p[]){
	for(int i=0;i<3;i++){
		p[i].hp = (p[i].sta*2*p[i].nvl/100) + p[i].nvl + 10;
	}
}
basicStats climaTe(void){
	for(int i=0;i<NUM;i++){
		pokemon[i].climaBonus = 1;
		pokemon[i].te = 1;
		pokemon[i].energy = 0;
	}
}
void sametypeatkbon(basicStats p[]){
	if(strcmp(p->fastAttackType, p->type1) || strcmp(p->fastAttackType, p->type2)){
		p->stabfast = 1.50;
	}
	if(strcmp(p->chargedAttackType, p->type1) || strcmp(p->chargedAttackType, p->type2)){
		p->stabcharged = 1.50;
	}
}

void bonus_clima(basicStats p[], int clima){
	for(int i=0;i<3;i++){
		switch(clima){
			case 1:
			if(strcmp(p->fastAttackType, "Fire") || strcmp(p->fastAttackType, "Grass") || strcmp(p->fastAttackType, "Ground")){
				p->climaBonus = BONUS;
			}
			if(strcmp(p->chargedAttackType, "Fire") || strcmp(p->chargedAttackType, "Grass") || strcmp(p->chargedAttackType, "Ground")){
				p->climaBonus = BONUS;
			}
			break;
			case 2:
			if(strcmp(p->fastAttackType, "Normal") || strcmp(p->fastAttackType, "Rock")){
				p->climaBonus = BONUS;
			}
			if(strcmp(p->chargedAttackType, "Normal") || strcmp(p->chargedAttackType, "Rock")){
				p->climaBonus = BONUS;
			}
			break;
			case 3:
			if(strcmp(p->fastAttackType, "Fairy") || strcmp(p->fastAttackType, "Fighting") || strcmp(p->fastAttackType, "Poison")){
				p->climaBonus = BONUS;
			}
			if(strcmp(p->chargedAttackType, "Fairy") || strcmp(p->chargedAttackType, "Fighting") || strcmp(p->chargedAttackType, "Poison")){
				p->climaBonus = BONUS;
			}
			break;
			case 4:
			if(strcmp(p->fastAttackType, "Water") || strcmp(p->fastAttackType, "Eletric") || strcmp(p->fastAttackType, "Eletric")){
				p->climaBonus = BONUS;
			}
			if(strcmp(p->chargedAttackType, "Water") || strcmp(p->chargedAttackType, "Eletric") || strcmp(p->chargedAttackType, "Eletric")){
				p->climaBonus = BONUS;
			}
			break;
			case 5:
			if(strcmp(p->fastAttackType, "Ice") || strcmp(p->fastAttackType, "Steel")){
				p->climaBonus = BONUS;
			}
			if(strcmp(p->chargedAttackType, "Ice") || strcmp(p->chargedAttackType, "Steel")){
				p->climaBonus = BONUS;
			}
			break;
			case 6:
			if(strcmp(p->fastAttackType, "Dark") || strcmp(p->fastAttackType, "Ghost")){
				p->climaBonus = BONUS;
			}
			if(strcmp(p->chargedAttackType, "Dark") || strcmp(p->chargedAttackType, "Ghost")){
				p->climaBonus = BONUS;
			}
			break;
			case 7:
			if(strcmp(p->fastAttackType, "Dragon") || strcmp(p->fastAttackType, "Flying") || strcmp(p->fastAttackType, "Psychic")){
				p->climaBonus = BONUS;
			}
			if(strcmp(p->chargedAttackType, "Dragon") || strcmp(p->chargedAttackType, "Flying") || strcmp(p->chargedAttackType, "Psychic")){
				p->climaBonus = BONUS;
				break;
			}
		}
	}
}

Taux matrizMultiplicadoraFast(basicStats p1[], basicStats p2[]){
	int count1, count2, count3;
	const char *none = "none";
	for(int i=0;i<18;i++){
		if(strcmp(p1->fastAttackType, aux.allTypes[i])){
			count1 = i;
		}
	}
	for(int i=0;i<18;i++){
		if(strcmp(p2->type1, aux.allTypes[i])){
			count2 = i;
		}
		if(strcmp(p2->type2, aux.allTypes[i])){
			count3 = i;
		}
	}
	if(strcmp(p2->type2, none)){
		p1->te = aux.matrizMult[count1][count2];
	}
	else{
		p1->te = aux.matrizMult[count1][count2] + aux.matrizMult[count1][count3];
	}
}

Taux matrizMultiplicadoraCharged(basicStats p1[], basicStats p2[]){
	int count1, count2, count3;
	const char *none = "none";
	for(int i=0;i<18;i++){
		if(strcmp(p1->chargedAttackType, aux.allTypes[i])){
			count1 = i;
		}
	}
	for(int i=0;i<18;i++){
		if(strcmp(p2->type1, aux.allTypes[i])){
			count2 = i;
		}
		if(strcmp(p2->type2, aux.allTypes[i])){
			count3 = i;
		}
	}
	if(strcmp(p2->type2, none)){
		p1->te = aux.matrizMult[count1][count2];
	}
	else{
		p1->te = aux.matrizMult[count1][count2] + aux.matrizMult[count1][count3];
	}
}
void damagefast(basicStats p1[],basicStats p2[]){
	float danoprov;
	int random;
	danoprov = (((2*p1->nvl/5 + 2)*p1->fmovemp*(p1->atk/p2->def))/50)+2;
	p1->dano_finalFast = danoprov * p1->climaBonus*p1->stabfast *p1->te;
	random = rand() % 100;
	if(random>85){
		p1->dano_finalFast = p1->dano_finalFast*0.85;
	}
	else{
		p1->dano_finalFast =p1->dano_finalFast;
	}
}

void damagecharged(basicStats p1[],basicStats p2[]){
	float danoprov;
	int random;
	danoprov = (((2*p1->nvl/5 + 2)*p1->cmovemp*(p1->atk/p2->def))/50)+2;
	p1->dano_finalCharged = danoprov * p1->climaBonus*p1->stabfast *p1->te;
	random = rand() % 100;
	if(random>85){
		p1->dano_finalCharged = p1->dano_finalCharged*0.85;
	}
	else{
		p1->dano_finalCharged = p1->dano_finalCharged;
	}
}
void attackChoose(basicStats p[], int escolha){
	FILE *fp, *fp1;
	int num, pick;
	char *test, *test2;
	test = (char *)malloc(62);
	test2 = (char *)malloc(100);
	fp = fopen(possiblefmoves, "r");
	fp1 = fopen(possiblecmoves, "r");
	printf("Num ||\t\tnumero dos ataques\n");
	while(!feof(fp)){
		fgets(test, 62, fp);
		printf("%s", test);
		test[0] = '\0';
	}
	test[0] = '\0';
	printf("\n\n\t\tEscolha o numero do seu ataque rapido:\n");
	scanf("%d", &pick);
	p->fmoveNum = fmoves[pick].num;
	p->fmovemp = fmoves[pick].fmovemp;
	p->fmoveEnergy_boost = fmoves[pick].fmoveEnergy_boost;
	strcpy(fmoves[pick].fmovename, p->fmovename);
	system("cls");
	printf("Num ||\t\tnumero dos ataques\n");
	while(!feof(fp1)){
		fgets(test2, 100, fp1);
		printf("%s", test2);
		test2[0] = '\0';
	}
	printf("Agora, escolha o numero do seu ataque carregado:");
	scanf("%d", &pick);
	p->cmoveNum = cmoves[pick].num;
	p->cmovemp = cmoves[pick].cmovemp;
	p->cmoveEnergy_boost = cmoves[pick].cmoveEnergy_boost;
	strcpy(cmoves[pick].cmovename, p->cmovename);
	free(test);
	free(test2);
	fclose(fp);
	fclose(fp1);
}

void pokemonChoose(basicStats p[]){
	int escolha, escolha2, num;
	double nivel;
	FILE *fp, *fp1;
	fp = fopen(possiblefmoves, "r");
	fp1 = fopen(possiblecmoves, "r");
	for(int i=0;i<3;i++){
		printf("Numero %do pokemon: ", i+1);
		scanf("%d", &escolha);
		while(escolha>NUM){
			printf("Pokemon nao encontrado, insira novamente!\n");
			scanf("%d", &escolha);
		}
		p[i] = pokemon[escolha-1];
		printf("Agora, seu nivel!\n");
		scanf("%lf", &nivel);
		while(nivel>40){
			printf("Nivel invalido, insira novamente!\n");
			scanf("%lf", &nivel);
		}
		p[i].nvl = nivel;
			/*coloca data dos pokemons dentro de cada vetor
			FIM*/
		attackChoose(p, escolha);
	}
	
	fclose(fp);
	fclose(fp1);
}
void preBattle(basicStats p1[], Tfmoves fmov1[], Tcmoves cmov1[], basicStats p2[], Tfmoves fmov2[], Tcmoves cmov2[]){
	int clima;
	printf("Digite 1 para clear/sunny:\n");
	printf("Digite 2 para partly cloud:\n");
	printf("Digite 3 para cloudy:\n");
	printf("Digite 4 para rain:\n");
	printf("Digite 5 para snow:\n");
	printf("Digite 6 para fog:\n");
	printf("Digite 7 para windy:\n");
	scanf("%d", &clima);
	printf("Player 1, escolha seus 3 pokemons!\n");
	pokemonChoose(p1);
	printf("Player 2, escolha seus 3 pokemons!\n");
	pokemonChoose(p2);
	bonus_clima(p1, clima);
	bonus_clima(p2, clima);
	printf("Pokemons player1 1:\n");
	for(int i=0;i<3;i++){
		printf("%d\t%s\t%.2f\t%.2f\t%.2f\t\n\n", p1[i].num, p1[i].name, p1[i].atk, p1[i].def, p1[i].sta);
		printf("%s\t\t%s\n", p1[i].type1, p1[i].type2);
		hpGenerator(p1);
		sametypeatkbon(p1);
		damagefast(p1, p2);
		damagecharged(p1, p2);
	}
	printf("Pokemon player 2:\n");
	for(int i=0;i<3;i++){
		printf("%d\t%s\t%.2f\t%.2f\t%.2f\t\n", p2[i].num, p2[i].name, p2[i].atk, p2[i].def, p2[i].sta);
		printf("%s\t\t%s\n", p2[i].type1, p2[i].type2);
		hpGenerator(p2);
		sametypeatkbon(p2);
		damagefast(p2, p1);
		damagecharged(p2, p1);
	}
}
basicStats lutinha(basicStats p1[], basicStats p2[], int random, int count){
	random = rand() % 100;
	if(random>85){
		p2->hp -= p1->dano_finalFast*0.85;
		p2->energy += 0.5*p1->dano_finalFast*0.85;
		p1->energy += p1->fmoveEnergy_boost;
		printf("%d\t\t%s\t%s\t%.2f\t%.2f\t%.2f\t%.2f", count, p1->name, p1->fmovename, p1->hp, p2->hp, p1->energy, p2->energy);
	}
		else{
			p2->hp -= p1->dano_finalFast;
			p2->energy = p1->dano_finalFast*0.5;
			p1->energy += p1->fmoveEnergy_boost;
			printf("%d\t\t%s\t%s\t%.2f\t%.2f\t%.2f\t%.2f", count, p1->name, p1->fmovename, p1->hp, p2->hp, p1->energy, p2->energy);
		}
}
basicStats chargedCalculator(basicStats p1[], basicStats p2[], int count){
	if(p1->energy>=p1->cmoveEnergy_boost){
		p1->hp -= p2->dano_finalCharged;
		printf("%d\t\t%s\t%s\t%.2f\t%.2f\t%.2f\t%.2f", count, p1->name, p1->cmovename, p1->hp, p2->hp, p1->energy, p2->energy);
	}
}
void battle(basicStats p1[], basicStats p2[]){
	int i=0, j=0, count=0;
	int random;
	printf("Turno\t\tNome\tAtaque\tHp p1\tHp p2\tEnergia p1\tEnergia p2\n");
	while(1){
		lutinha(p1, p2, random, count);
		chargedCalculator(p1, p2, count);
		lutinha(p2, p1, random, count);
		chargedCalculator(p2, p1, count);
		count++;
		if(i==3 || j==3){
			printf("Parabéns, voce venceu a partida!\n");
			break;
		}
		else if(p1[i].hp<=0){
			i++;
		}
		else if(p2[j].hp<=0){
			j++;
		}
	}
}

basicStats carregaVetor(void){
	FILE *fp, *fp1, *fp2, *fp3;
	fp = fopen(basestats, "r");
	fp1 = fopen(fastmoves, "r");
	fp2 = fopen(chargedmoves, "r");
	if(fp == NULL || fp1 == NULL || fp2 == NULL){
		printf("Erro ao ler arquivo!\n");
		exit(1);
	}	
	for(int i=0;i<NUM;i++){
		fscanf(fp, "%d\t%s\t%f\t%f\t%f\t", &pokemon[i].num, pokemon[i].name, &pokemon[i].atk, &pokemon[i].def, &pokemon[i].sta);
		fscanf(fp, "%s %s", pokemon[i].type1, pokemon[i].type2);
	}
	for(int i=0;i<NUM_fmoves;i++){
		fscanf(fp1, "%d\t%s\t%s\t%d\t%d", &fmoves[i].num, fmoves[i].fmovename, fmoves[i].type, &fmoves[i].fmovemp, &fmoves[i].fmoveEnergy_boost);
	}
	for(int i=0;i<NUM_cmoves;i++){
		fscanf(fp2, "%d\t%s\t%s\t%d\t%d", &cmoves[i].num, cmoves[i].cmovename, cmoves[i].type, &cmoves[i].cmovemp, &cmoves[i].cmoveEnergy_boost);
	}
	fclose(fp);
	fclose(fp1);
	fclose(fp2);
}
int main(){
	basicStats p1[3], p2[3];
	Tfmoves fmoves1[1], fmoves2[1];
	Tcmoves cmoves1[1], cmoves2[1];
	climaTe();
	carregaVetor();
	preencherMatriz();
	preBattle(p1, fmoves1, cmoves1, p2, fmoves2, cmoves2);
	battle(p1, p2);
	return 0;
}
