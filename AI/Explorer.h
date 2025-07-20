// Explorer
namespace Explorer{
	typedef double db;
	typedef long double ld;
	typedef pair<int, int> Pii;
	const int dx[4] = {0, -1, 0, 1};
	const int dy[4] = {1, 0, -1, 0};
	const Pii emptyPair = make_pair(0, 0);
	const int N = 50;
	mt19937 exrd(time(nullptr));
	// map
	char exMap[N][N];
	// king
	bool gotKing;
	Pii myKing;
	int myID;
	// speical points
	vector<Pii> specialPoints;
	// new ways
	queue<Pii> q;
	int dis[N][N];
	// probably
	vector<db> probablyList;
	// attack
	int currentEnemy;
	// functions
	void Init(){
		gotKing = false;
		myKing = emptyPair;
		myID = 0;
		specialPoints.clear();
		memset(exMap, 0, sizeof(exMap));
		return;
	}
	// check
	bool InMap(int x, int y){
		return (1 <= x && x <= mapRows && 1 <= y && y <= mapCols);
	}
	bool Visible(char ty){
		return (ty == 'K' || ty == 'C' || ty == 'M' || ty == 'L');
	}
	// get king
	void GetKing(){
		for (int i = 1; i <= mapRwos; ++i){
			for (int j = 1; j <= mapCols; ++j){
				block curbl = Ask(i, j);
				if (curbl.type == 'K'){
					myKing = make_pair(i, j);
					myID = curbl.belongTo;
					break;
				}
			}
		}
		return;
	}
	// get map
	void GetMap(){
		for (int i = 1; i <= mapRows; ++i){
			for (int j = 1; j <= mapCols; ++j){
				if (Visible(exMap[i][j])){
					continue;
				}
				block curbl = Ask(i, j);
				exMap[i][j] = curbl.type;
			}
		}
		return;
	}
	// random with probably
	int RandomChooseWithProbably(){
		db currentRandomNumber = 1.0 * exrd() / (1ULL << 32);
		int randomChoose = (int)(probablyList.size()) - 1;
		for (int currentElement = 0; currentElement < (int)(probablyList.size()); ++currentElement){
			if (currentRandomNumber < probablyList[currentElement]){
				currentRandomNumber -= probably;
			}
			else{
				randomChoose = currentElement;
			}
		}
		return randomChoose;
	}
	// make new ways
	void MakeWays(){
		// get distance
		while (!q.empty()){
			q.pop();
		}
		for (int i = 1; i <= mapRows; ++i){
			for (int j = 1; j <= mapCols; ++j){
				dis[i][j] = -1;
			}
		}
		for (Pii pt : specialPoints){
			q.push(pt);
			dis[pt.first][pt.second] = 0;
		}
		while (!q.empty()){
			Pii u = q.front();
			q.pop();
			int x = u.first, y = u.second;
			for (int d = 0; d < 4; ++d){
				int nx = x + dx[d], ny = y + dy[d];
				if (!InMap(nx, ny)){
					continue;
				}
				if (exMap[nx][ny] == 'B' || exMap[nx][ny] == 'M' || exMap[nx][ny] == 'C'){
					continue;
				}
				if (dis[nx][ny] == -1){
					dis[nx][ny] = dis[x][y] + 1;
					q.push(make_pair(nx, ny));
				}
			}
		}
		// choises
		int wantedDistance = 13;
		vector<Pii> newPoints;
		// clear
		newPoints.clear();
		newPoints.shrink_to_fit();
		do{
			// choises
			for (int i = 1; i <= mapRows; ++i){
				for (int j = 1; j <= mapCols; ++j){
					if (dis[i][j] == wantedDistance){
						newPoints.push_back(make_pair(i, j));
					}
				}
			}
			// reduce wanted
			--wantedDistance;
		}while(newPoints.empty());
		// set probably
		int newPointTotal = (int)(newPoints.size());
		probablyList.clear();
		probablyList.shrink_to_fit();
		for (Pii currentPoint : newPoints){
			probablyList.push_back(1.0 / newPointTotal);
		}
		// random choose
		Pii newSpecialPoints = newPoints[exrd() % (int)(newPoints.size())];
		// add new point
		specialPoints.push_back(newSpecialPoints);
		return;
	}
	// attack
	void Attack(){
		return;
	}
	// move
	movement Move(){
		// get king
		if (!gotKing){
			GetKing();
		}
		// get map
		GetMap();
		// check enemy
		if (currentEnemy && armyTotal[currentEnemy] != 0){
			// enemy alive --> attack
			Attack();
		}
		else{
			// no enemies --> make new ways
			MakeWays();
		}
		return;
	}
}
