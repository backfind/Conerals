// generals
// by lzj

// headers
#include "gameheader.h"

// variables
mt19937 randNumber(time(nullptr));

const int clickTimeDelay = 30;

const int deltaX[9] = {0, -1, 0, 1, -1, -1, 1, 1, 0};
const int deltaY[9] = {1, 0, -1, 0, 1, -1, -1, 1, 0};

const int maxPlayers = 16;
string playerName[maxPlayers + 5];
int playerTotal;

int AItotal;
vector<string> AInames;

// generals variables

const int maxMapSize = 50;

struct block{
	int army, belongTo;
	char type;
	// K : king
	// C : castle
	// L : land
	// M : mountain
};
int mapRows, mapCols, mapSize;
block generalsMap[maxMapSize][maxMapSize];
int kingsX[maxPlayers], kingsY[maxPlayers];

// for setting kings
bool possessedByKings[maxMapSize][maxMapSize];

// for setting mountains
bool floodAccessible[maxMapSize][maxMapSize];

// for showing players
const int playerColors[maxPlayers] = {0, 4, 1, 2, 3, 7, 5, 6, 8};

// for playing generals

// for players
int generalsTurns;
bool alreadyDead[maxPlayers];

// for calculating ranks

struct rnk{
	int id,Army; 
};
vector<rnk>PlayerRank;

// for check coloring mode
bool delight=0; 

// for watching blocks
int currentAsking;

// for movements
movement playerMovement[maxPlayers];

// for human
int humanChooseX, humanChooseY;
bool humanParticipation;

// for turns
double theStartTimeOfTheCurrentTurn;

// statistic
int armyTotal[maxPlayers], landTotal[maxPlayers];

// get AIs

block Ask(int askX, int askY);

//won time

map<string,int>wonrate;

#include "getAIs.h"

// functions
void InitGame();
void Show();
void RandomChoosePlayers();
void Play1v1();
void PlayFFA();
void Generals();
bool OutOfTheMap(int askX, int askY);
void FloodFillTheMap(int currentX, int currentY);
void MakeGeneralsMap();
void ShowPlayers();
void PrintBlockType(char currentType, int currentBelong, char whichSide);
void ShowBlockTop(block currentBlock);
void ShowBlockBottom(block currentBlock);
void ShowGeneralsMap();
void ShowGeneralsMapOfHumanView();
bool CheckVisible(block checkBlock);
void EnableANSIMode();
void RGBMaker(int R,int G,int B);
void Get_color(int a);
void DeleteColor();
// init game
void InitGame(){
	DeleteColor();
	// read AI
	ifstream AIs("AIs.txt");
	AIs >> AItotal;
	AInames.clear();
	for (int i = 1; i <= AItotal; ++i){
		string AIname;
		AIs >> AIname;
		AInames.push_back(AIname);
	}
	AIs.close();
	// init window
	Noedit();
	output_color;
	HideCursor();
	system("mode con cols=101 lines=36");
	//set ANSI color mode
	EnableANSIMode();
	return;
}
// the center : X = 50

// the start
void Show(){
	system("cls");
	// set bottons
	button _1v1_ = New_button(49, 11, 0, 2, "1v1");
	button _FFA_ = New_button(49, 17, 0, 2, "FFA");
	button _Exit_ = New_button(49, 23, 0, 4, "Exit");
	// options
	while (true){
		_1v1_.lighted = 2;
		_FFA_.lighted = 2;
		_Exit_.lighted = 2;
		Sleep(clickTimeDelay);
		if (Click_button(_Exit_)){
			break;
		}
		if (Click_button(_1v1_)){
			Play1v1();
			system("cls");
		}
		if (Click_button(_FFA_)){
			PlayFFA();
			system("cls");
		}
	}
	return;
}

// random choose players
void RandomChoosePlayers(){
	for (int currentPlayer = 1; currentPlayer <= playerTotal; ++currentPlayer){
		bool checkUnqiue = false;
		while (!checkUnqiue){
			// random choose
			playerName[currentPlayer] = AInames[randNumber() % AItotal];
			// check
			checkUnqiue = true;
			for (int lastPlayer = 1; lastPlayer < currentPlayer; ++lastPlayer){
				if (playerName[currentPlayer] == playerName[lastPlayer]){
					checkUnqiue = false;
					break;
				}
			}
		}
	}
	return;
}

// 1v1
void Play1v1(){
	system("cls");
	Place(46, 10);cout<<"1v1";
	// set buttons
	button _Back_ = New_button(46, 22, 0, 4, "Back");
	button _AI_VS_AI_ = New_button(46, 18, 0, 2, "AI VS AI");
	button _Human_VS_AI_ = New_button(46, 14, 0, 2, "Human VS AI");
	// options
	while (true){
		Sleep(clickTimeDelay);
		if (Click_button(_Back_)){
			return;
		}
		if (Click_button(_AI_VS_AI_)){
			humanParticipation = false;
			playerTotal = 2;
			// random choose
			RandomChoosePlayers();
			break;
		}
		if (Click_button(_Human_VS_AI_)){
			humanParticipation = true;
			playerTotal = 2;
			// randomchoose
			playerName[1] = AInames[randNumber() % AItotal];
			playerName[2] = "human";
			break;
		}
	}
	// play generals
	Generals();
	return;
}

// FFA
void PlayFFA(){
	system("cls");
	Place(46, 10);cout<<"FFA";
	// set buttons
	button _Back_ = New_button(46, 22, 0, 4, "Back");
	button _AIs_VS_AIs_ = New_button(46, 18, 0, 2, "AIs VS AIs");
	button _Human_VS_AIs_ = New_button(46, 14, 0, 2, "Human VS AIs");
	// options
	while (true){
		Sleep(clickTimeDelay);
		if (Click_button(_Back_)){
			return;
		}
		if (Click_button(_AIs_VS_AIs_)){
			// varibles
			humanParticipation = false;
			playerTotal = 8;
			if (playerTotal > AItotal){
				playerTotal = AItotal;
			}
			// players
			RandomChoosePlayers();
			break;
		}
		if (Click_button(_Human_VS_AIs_)){
			// variables
			humanParticipation = true;
			playerTotal = 7;
			if (playerTotal > AItotal){
				playerTotal = AItotal;
			}
			// players
			RandomChoosePlayers();
			// human
			++playerTotal;
			playerName[playerTotal] = "human";
			break;
		}
	}
	// play generals
	Generals();
	return;
}

// generals

// out of the map
bool OutOfTheMap(int askX, int askY){
	return (askX < 1 || mapRows < askX || askY < 1 || mapCols < askY);
}
// make the map
void FloodFillTheMap(int currentX, int currentY){
	// mark
	floodAccessible[currentX][currentY] = true;
	// fill block
	for (int currentDirection = 0; currentDirection < 4; ++currentDirection){
		// next block
		int nextX = currentX + deltaX[currentDirection];
		int nextY = currentY + deltaY[currentDirection];
		// check position
		if (OutOfTheMap(nextX, nextY)){
			continue;
		}
		// check visited
		if (floodAccessible[nextX][nextY] || generalsMap[nextX][nextY].type == 'M' || generalsMap[nextX][nextY].type == 'C'){
			continue;
		}
		// fill
		FloodFillTheMap(nextX, nextY);
	}
	return;
}
void MakeGeneralsMap(){
	// size
	mapRows = 15;
	mapCols = 33;
	mapSize = mapRows * mapCols;
	// reset
	for (int i = 1; i <= mapRows; ++i){
		for (int j = 1; j <= mapCols; ++j){
			generalsMap[i][j].army = 0;
			generalsMap[i][j].belongTo = 0;
			generalsMap[i][j].type = 'L';
		}
	}
	// set kings
	int minDistance = (int)(sqrt(mapSize / playerTotal));
	int tryPutKingsCounts = 0;
	bool checkKings = false;
	while (!checkKings){
		checkKings = true;
		// reset kings
		for (int i = 1; i <= mapRows; ++i){
			for (int j = 1; j <= mapCols; ++j){
				possessedByKings[i][j] = false;
				if (generalsMap[i][j].type == 'K'){
					generalsMap[i][j].type = 'L';
					generalsMap[i][j].belongTo = 0;
					generalsMap[i][j].army = 0;
				}
			}
		}
		// set kings
		for (int currentPlayer = 1; currentPlayer <= playerTotal; ++currentPlayer){
			// try to set
			int tryCounts = 0;
			kingsX[currentPlayer] = 0;
			kingsY[currentPlayer] = 0;
			do{
				kingsX[currentPlayer] = randNumber() % mapRows + 1;
				kingsY[currentPlayer] = randNumber() % mapCols + 1;
				++tryCounts;
			}while (tryCounts <= 100 && possessedByKings[kingsX[currentPlayer]][kingsY[currentPlayer]]);
			// check
			if (possessedByKings[kingsX[currentPlayer]][kingsY[currentPlayer]]){
				checkKings = false;
				break;
			}
			// set
			generalsMap[kingsX[currentPlayer]][kingsY[currentPlayer]].belongTo = currentPlayer;
			generalsMap[kingsX[currentPlayer]][kingsY[currentPlayer]].type = 'K';
			generalsMap[kingsX[currentPlayer]][kingsY[currentPlayer]].army = 1;
			// possess
			for (int kingDeltaX = -minDistance; kingDeltaX <= minDistance; ++kingDeltaX){
				for (int kingDeltaY = -minDistance; kingDeltaY <= minDistance; ++kingDeltaY){
					// check distance
					int distanceToTheKing = kingDeltaX + kingDeltaY;
					if (distanceToTheKing < 0){
						distanceToTheKing = -distanceToTheKing;
					}
					if (distanceToTheKing <= minDistance){
						// possessed
						int possessedX = kingsX[currentPlayer] + kingDeltaX;
						int possessedY = kingsY[currentPlayer] + kingDeltaY;
						// check position
						if (OutOfTheMap(possessedX, possessedY)){
							continue;
						}
						// possess
						possessedByKings[kingsX[currentPlayer] + kingDeltaX][kingsY[currentPlayer] + kingDeltaY] = true;
					}
				}
			}
		}
		// trys
		++tryPutKingsCounts;
		if (tryPutKingsCounts >= 100){
			if (minDistance > 3){
				--minDistance;
			}
			tryPutKingsCounts = 0;
		}
	}
	// try to put mountains and castles
	int standardMountainsAndCastles = (int)((double)(mapSize) * 0.2);
	if (playerTotal + standardMountainsAndCastles > mapSize){
		standardMountainsAndCastles = mapSize - playerTotal;
	}
	bool checkFill = false;
	while (!checkFill){
		// reset the map
		for (int i = 1; i <= mapRows; ++i){
			for (int j = 1; j <= mapCols; ++j){
				floodAccessible[i][j] = false;
				if (generalsMap[i][j].type == 'C' || generalsMap[i][j].type == 'M'){
					generalsMap[i][j].type = 'L';
					generalsMap[i][j].army = 0;
				}
			}
		}
		// generate the number of mountains and castles
		int mountainsAndCastles = standardMountainsAndCastles + randNumber() % 9 - 4;
		if (playerTotal + mountainsAndCastles > mapSize){
			mountainsAndCastles = mapSize - playerTotal;
		}
		// put mountains and castles
		while (mountainsAndCastles--){
			int currentX = 0, currentY = 0;
			do{
				currentX = randNumber() % mapRows + 1;
				currentY = randNumber() % mapCols + 1;
			}while (generalsMap[currentX][currentY].type != 'L');
			int someRandNumber = randNumber() % 100;
			if (someRandNumber < 30){
				generalsMap[currentX][currentY].type = 'C';
				generalsMap[currentX][currentY].army = 40 + randNumber() % 10;
			}
			else{
				generalsMap[currentX][currentY].type = 'M';
			}
		}
		// check the map
		FloodFillTheMap(kingsX[1], kingsY[1]);
		checkFill = true;
		for (int currentPlayer = 1; currentPlayer <= playerTotal; ++currentPlayer){
			if (!floodAccessible[kingsX[currentPlayer]][kingsY[currentPlayer]]){
				checkFill = false;
				break;
			}
		}
	}
	return;
}
// show the players
/*
| X : xxxxx... |
| Army : xxxxx |
| Land : xxxxx |
*/
void ShowPlayers(){
	// clear rank
	PlayerRank.clear();
	// calc army and land
	for(int currentPlayer = 1; currentPlayer <= playerTotal; ++currentPlayer){
		armyTotal[currentPlayer] = 0;
		landTotal[currentPlayer] = 0;
		for (int i = 1; i <= mapRows; ++i){
			for (int j = 1; j <= mapCols; ++j){
				if (generalsMap[i][j].belongTo == currentPlayer){
					armyTotal[currentPlayer] += generalsMap[i][j].army;
					++landTotal[currentPlayer];
				}
			}
		}
		if(armyTotal[currentPlayer])PlayerRank.push_back({currentPlayer,armyTotal[currentPlayer]});
	}
	sort(PlayerRank.begin(),PlayerRank.end(),[](rnk x,rnk y){
		return x.Army>y.Army;
	});
	// show "|"
	Place(0, 1);cout<<"|";
	Place(0, 2);cout<<"|";
	Place(0, 3);cout<<"|";
	// set X position
	int currentShowX = 2;
	for (int currentIt = 0; currentIt < 6; ++currentIt){
		if(currentIt>=(int)PlayerRank.size()){
			//clear
			Place(currentShowX, 1);
			cout<<left<<setw(13)<<" ";
			Place(currentShowX, 2);
			cout<<left<<setw(13)<<" ";
			Place(currentShowX, 3);
			cout<<left<<setw(13)<<" ";
			currentShowX += 15;
			continue;
		}
		int currentPlayer=PlayerRank[currentIt].id;
		// get color
		Get_color(playerColors[currentPlayer]);
		// show name
		Place(currentShowX, 1);
		cout<<(char)(currentPlayer | 64)<<" : ";
		string currentName = playerName[currentPlayer];
		int currentLength = (int)(currentName.length());
		if (currentLength <= 8){
			cout<<left<<setw(8)<<currentName;
		}
		else{
			for (int currentChar = 0; currentChar < 5; ++currentChar){
				cout<<currentName[currentChar];
			}
			cout<<"...";
		}
		// show army and land
		string All;
		Place(currentShowX, 2);
		if(armyTotal[currentPlayer]>99999){
			// calc digits
			int theDigitsOfArmy = 0;
			while (armyTotal[currentPlayer] > 9){
				++theDigitsOfArmy;
				armyTotal[currentPlayer] /= 10;
			}
			// special output
			All="Army : "+to_string(armyTotal[currentPlayer])+"e"+to_string(theDigitsOfArmy);
		}else All="Army : " +to_string(armyTotal[currentPlayer]);
		cout<<left<<setw(12)<<All;
		Place(currentShowX, 3);
		All="Land : " +to_string(landTotal[currentPlayer]);
		cout<<left<<setw(12)<<All;
		// show "|"
		DeleteColor();
		//output_color;
		Place(currentShowX + 13, 1);cout<<"|";
		Place(currentShowX + 13, 2);cout<<"|";
		Place(currentShowX + 13, 3);cout<<"|";
		// update "currentShowX"
		currentShowX += 15;
	}
	// reset color
	return;
}
// show the map
/*
+---+
|   |
|   |
+---+
*/
void PrintBlockType(char currentType, int currentBelong, char whichSide){
	if (currentType == 'K'){
		cout<<"$";// king
	}
	else if (currentType == 'C'){
		if (currentBelong != 0){
			// empty castle
			if (whichSide == 'L'){
				cout<<"(";
			}
			else{
				cout<<")";
			}
		}
		else{
			// possessed castle
			if (whichSide == 'L'){
				cout<<"<";
			}
			else{
				cout<<">";
			}
		}
	}
	else if (currentType == 'L'){
		cout<<" ";// normal land
	}
	return;
}
// show the top of the block
void ShowBlockTop(block currentBlock){
	char currentType = currentBlock.type;
	// special type
	if (currentType == 'M'){
		Get_color(0); 
		cout<<"###";
		DeleteColor();
		return;
	}
	Get_color(-1); 
	if (currentType == 'B'){
		cout<<"###";
		DeleteColor();
		return;
	}
	if (currentBlock.type == '?'){
		cout<<"   ";
		DeleteColor();
		return;
	}
	// belong
	int currentBelong = currentBlock.belongTo;
	Get_color(playerColors[currentBelong]);
	PrintBlockType(currentType, currentBelong, 'L');
	if (currentBelong != 0){
		cout<<(char)(currentBelong | 64);
	}
	else if (currentType == 'C'){
		DeleteColor();
		Get_color(0); 
		cout<<"M";
	}
	else{
		DeleteColor();
		Get_color(0); 
		cout<<" ";
	}
	PrintBlockType(currentType, currentBelong, 'R');
	DeleteColor();
	//output_color;
	return;
}
// show the bottom of the block
void ShowBlockBottom(block currentBlock){
	// special type
	if (currentBlock.type == 'M'){
		Get_color(0); 
		cout<<"###";
		DeleteColor();
		return;
	}
	Get_color(-1); 
	if (currentBlock.type == 'B'){
		cout<<"###";
		DeleteColor();
		return;
	}
	if (currentBlock.type == '?'){
		cout<<"   ";
		DeleteColor();
		return;
	}
	// army
	int currentArmy = currentBlock.army;
	if (currentArmy!=0){
		// set color
		Get_color(playerColors[currentBlock.belongTo]);
		// too large
		if (currentArmy > 999){
			// calc digits
			int theDigitsOfArmy = 0;
			while (currentArmy > 9){
				++theDigitsOfArmy;
				currentArmy /= 10;
			}
			// special output
			cout<<currentArmy<<"e"<<theDigitsOfArmy;
		}
		else{
			// normal output
			cout<<right<<setw(3)<<currentArmy;
		}
		// reset color
		DeleteColor();
		//output_color;
	}
	else{
		DeleteColor();
		Get_color(0); 
		cout<<"   ";
		DeleteColor();
	}
	return;
}
void ShowGeneralsMap(){
	Place(0, 4);
	// the first line
	Get_color(-1);
	for (int j = 1; j <= mapCols; ++j){
		cout<<"---";
	}
	DeleteColor();
	for (int i = 1; i <= mapRows; ++i){
		cout<<"\n";
		// show type
		for (int j = 1; j <= mapCols; ++j){
			ShowBlockTop(generalsMap[i][j]);
		}
		cout<<'\n';
		for (int j = 1; j <= mapCols; ++j){
			ShowBlockBottom(generalsMap[i][j]);
		}
	}
	cout<<endl;
	return;
}
// check visible
bool CheckVisible(block checkBlock){
	return (checkBlock.type == 'K' || checkBlock.type == 'M' || checkBlock.type == 'C' || checkBlock.type == 'L');
}
// human view
void ShowGeneralsMapOfHumanView(){
	// get human id
	for (int currentPlayer = 1; currentPlayer <= playerTotal; ++currentPlayer){
		if (playerName[currentPlayer] == "human"){
			currentAsking = currentPlayer;
			break;
		}
	}
	// set position
	Place(0, 4);
	// set color
	Get_color(-1);
	// the first line
	for (int j = 1; j <= mapCols; ++j){
		cout<<"---";
	}
	DeleteColor();
	for (int i = 1; i <= mapRows; ++i){
		cout<<"\n";
		// show type
		for (int j = 1; j <= mapCols; ++j){
			if(humanChooseX==i && humanChooseY==j)delight=1;
			ShowBlockTop(Ask(i, j));
			if(humanChooseX==i && humanChooseY==j)delight=0;
		}
		cout<<'\n';
		// show army
		for (int j = 1; j <= mapCols; ++j){
			if(humanChooseX==i && humanChooseY==j)delight=1;
			ShowBlockBottom(Ask(i, j));
			if(humanChooseX==i && humanChooseY==j)delight=0;
		}
	}
	return;
}
// ask
block Ask(int askX, int askY){
	block answerBlock;
	answerBlock.type = ' ';
	answerBlock.belongTo = -1;
	answerBlock.army = -1;
	// This block doesn't exist.
	if (OutOfTheMap(askX, askY)){
		answerBlock.type = 'x';
		return answerBlock;
	}
	// visible ?
	for (int currentDirection = 0; currentDirection < 9; ++currentDirection){
		int nextX = askX + deltaX[currentDirection];
		int nextY = askY + deltaY[currentDirection];
		if (OutOfTheMap(nextX, nextY)){
			continue;
		}
		if (generalsMap[nextX][nextY].belongTo == currentAsking){
			// visible
			answerBlock = generalsMap[askX][askY];
			return answerBlock;
		}
	}
	// not visible
	if (generalsMap[askX][askY].type == 'M' || generalsMap[askX][askY].type == 'C'){
		answerBlock.type = 'B';
	}
	else{
		answerBlock.type = '?';
	}
	return answerBlock;
}
// check
bool CheckGame(){
	int numberOfPlayersStillAlive = 0;
	for (int currentPlayer = 1; currentPlayer <= playerTotal; ++currentPlayer){
		if (!alreadyDead[currentPlayer]){
			++numberOfPlayersStillAlive;
		}
	}
	if (numberOfPlayersStillAlive == 1){
		return true;
	}
	return false;
}
// play
// 1. moves
// 2. check alive
// 3. add by turns
// 4. add by kings and castles
void Generals(){
	// init
	// init window
	cout<<flush;
	system("cls");
	Sleep(100);
	// init player
	for (int currentPlayer = 1; currentPlayer <= playerTotal; ++currentPlayer){
		// init AI
		Initialize(playerName[currentPlayer]);
		// set the state of live
		alreadyDead[currentPlayer] = false;
		// statistic
		armyTotal[currentPlayer] = 1;
		landTotal[currentPlayer] = 1;
	}
	// make the map
	MakeGeneralsMap();
	// play
	generalsTurns = 0;
	while (!CheckGame()){
		// print Turns
		Place(0, 0);
		cout<<"Turn : "<<generalsTurns / 2;
		if (generalsTurns % 2 == 0){
			cout<<" ";
		}
		else{
			cout<<".";
		}
		// get the start time of the current turn
		theStartTimeOfTheCurrentTurn = clock();
		// moves
		// get movements
		for (int currentPlayer = 1; currentPlayer <= playerTotal; ++currentPlayer){
			// check alive
			if (alreadyDead[currentPlayer]){
				continue;
			}
			// set asking
			currentAsking = currentPlayer;
			// get the movement
			playerMovement[currentPlayer] = GetMove(playerName[currentPlayer]);
		}
		// make movements
		for (int currentPlayer = 1; currentPlayer <= playerTotal; ++currentPlayer){
			// check alive
			if (alreadyDead[currentPlayer]){
				continue;
			}
			// get the movement
			movement currentMove = playerMovement[currentPlayer];
			// check the block
			int currentX = currentMove.x, currentY = currentMove.y;
			if (OutOfTheMap(currentX, currentY)){
				continue;
			}
			if (generalsMap[currentX][currentY].belongTo != currentPlayer){
				continue;
			}
			// check the direction
			int currentDirection = currentMove.dir;
			if (currentDirection < 0 || 3 < currentDirection){
				continue;
			}
			// check the next block
			int nextX = currentX + deltaX[currentDirection];
			int nextY = currentY + deltaY[currentDirection];
			if (OutOfTheMap(nextX, nextY)){
				continue;
			}
			if (generalsMap[nextX][nextY].type == 'M'){
				continue;
			}
			// check the army
			if (generalsMap[currentX][currentY].army <= 1){
				continue;
			}
			// make the movement
			int currentArmy = generalsMap[currentX][currentY].army;
			int nextArmy = generalsMap[nextX][nextY].army;
			int moveArmy = currentArmy - 1;
			if (generalsMap[currentX][currentY].belongTo == generalsMap[nextX][nextY].belongTo){
				// add army
				generalsMap[nextX][nextY].army = moveArmy + nextArmy;
			}
			else{
				// recude army
				if (moveArmy > nextArmy){
					generalsMap[nextX][nextY].army = moveArmy - nextArmy;
					generalsMap[nextX][nextY].belongTo = currentPlayer;
				}
				else if(moveArmy < nextArmy){
					generalsMap[nextX][nextY].army = nextArmy - moveArmy;
				}else if(moveArmy ==nextArmy){
					generalsMap[currentX][currentY].army++;
					generalsMap[nextX][nextY].army=1;
				}
			}
			// clear the block
			generalsMap[currentX][currentY].army = 1;
		}
		// check alive
		for (int currentPlayer = 1; currentPlayer <= playerTotal; ++currentPlayer){
			// check alive
			if (alreadyDead[currentPlayer]){
				continue;
			}
			if (generalsMap[kingsX[currentPlayer]][kingsY[currentPlayer]].belongTo != currentPlayer){
				// dead
				alreadyDead[currentPlayer] = true;
				// captured by
				int capturedBy = generalsMap[kingsX[currentPlayer]][kingsY[currentPlayer]].belongTo;
				// update type
				generalsMap[kingsX[currentPlayer]][kingsY[currentPlayer]].type = 'C';
				// update army
				for (int i = 1; i <= mapRows; ++i){
					for (int j = 1; j <= mapCols; ++j){
						if (generalsMap[i][j].belongTo == currentPlayer){
							generalsMap[i][j].belongTo = capturedBy;
							generalsMap[i][j].army = (generalsMap[i][j].army + 1) / 2;
						}
					}
				}
			}
		}
		// add armys by turns
		if (generalsTurns % 50 == 0 && generalsTurns != 0){
			for (int i = 1; i <= mapRows; ++i){
				for (int j = 1; j <= mapCols; ++j){
					if (generalsMap[i][j].belongTo != 0){
						++generalsMap[i][j].army;
					}
				}
			}
		}
		// add armys by kings and castles
		if (generalsTurns % 2 == 0 && generalsTurns != 0){
			for (int i = 1; i <= mapRows; ++i){
				for (int j = 1; j <= mapCols; ++j){
					if (generalsMap[i][j].belongTo != 0){
						char currentType = generalsMap[i][j].type;
						if (currentType == 'K' || currentType == 'C'){
							++generalsMap[i][j].army;
						}
					}
				}
			}
		}
		// show
		ShowPlayers();
		if (humanParticipation && !alreadyDead[playerTotal]){
			ShowGeneralsMapOfHumanView();
		}
		else{
			ShowGeneralsMap();
		}
		// add turns
		++generalsTurns;
		// wait for the turn done
		if(humanParticipation)while (((double)(clock()) - theStartTimeOfTheCurrentTurn) / CLOCKS_PER_SEC < 0.5);
		else while (((double)(clock()) - theStartTimeOfTheCurrentTurn) / CLOCKS_PER_SEC < 0.05);
	}
	cout<<flush;
	Sleep(1500);
	return;
}

//colorful background
//by back_find
//你们可以随便封装，但是一定要析构 

void EnableANSIMode() {
    #ifdef _WIN32
    HANDLE hOut = GetStdHandle(STD_OUTPUT_HANDLE);
    DWORD dwMode = 0;
    GetConsoleMode(hOut, &dwMode);
    dwMode |= ENABLE_VIRTUAL_TERMINAL_PROCESSING;
    SetConsoleMode(hOut, dwMode);
    #endif
}
void RGBMaker(int R,int G,int B){
	if(delight)cout<<"\033[48;2;"<<R/5*4<<";"<<G/5*4<<";"<<B/5*4<<"m";
	else cout<<"\033[48;2;"<<R<<";"<<G<<";"<<B<<"m";
}
void Get_color(int a){
	/*灰色*/
	if(a==-1)RGBMaker(56,56,56);
	/*浅灰*/
	if(a==0)RGBMaker(127,127,127);
	/*红色*/
	if(a==1)RGBMaker(255,0,0);
	/*蓝色*/
	if(a==2)RGBMaker(39,146,255);
	/*绿色*/
	if(a==3)RGBMaker(0,128*0.8,0);
	/*墨绿色*/
	if(a==4)RGBMaker(0,128,128);
	/*金黄色*/
	if(a==5)RGBMaker(250,140,1);
	/*粉色*/
	if(a==6)RGBMaker(240,50,230);
	/*紫色*/
	if(a==7)RGBMaker(128,0,128);
	/*赭红色*/
	if(a==8)RGBMaker(155,1,1);
}
void DeleteColor(){
	cout<<"\033[0m";
}

// main

int main(){
	ios::sync_with_stdio(false);
	cout.tie(0);
	InitGame();
	Show();
	return 0;
}
