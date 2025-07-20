// OI_minecraft
namespace OI_minecraft{
	const int dx[] = {0, -1, 0, 1};
	const int dy[] = {1, 0, -1, 0};
	int kingx, kingy, tposx, tposy;
	int myid, round, hatepos;
	block m[50][50];
	bool vis[50][50], noking[50][50], noneed[50][50], geted[50][50];
	int armyposx, armyposy;
	vector<pair<int, int> > otherking, otherarmy;
	void Init(){
		otherking.clear(); otherarmy.clear();
		armyposx = armyposy = kingx = kingy = tposx = tposy = myid = round = hatepos = 0;
		memset(m, 0, sizeof m); memset(vis, 0, sizeof vis);
	}
	movement Move(){
		round++;
		for (int i = 1; i <= mapRows; i++)
			for (int j = 1; j <= mapCols; j++)
				m[i][j] = Ask(i, j);
		if(round == 1) for (int i = 1; i <= mapRows; ++i)
			for (int j = 1; j <= mapCols; ++j) if(m[i][j].type == 'K') myid = m[i][j].belongTo, armyposx = kingx = i, armyposy = kingy = j;
		if(m[tposx][tposy].belongTo == myid) armyposx = tposx, armyposy = tposy;
		if(m[armyposx][armyposy].army == 1 || m[armyposx][armyposy].belongTo != myid) for(int i = 1; i <= mapRows; i++) for(int j = 1; j <= mapCols; j++)
			if(m[i][j].belongTo == myid && m[i][j].army > m[armyposx][armyposy].army) armyposx = i, armyposy = j;
		for (int i = 1; i <= mapRows; ++i)
			for (int j = 1; j <= mapCols; ++j)
				if(m[i][j].belongTo != myid && m[i][j].type != 'M' && m[i][j].belongTo > 0){
					if(m[i][j].type == 'K') otherking.push_back({i, j});
					else otherarmy.push_back({i, j});
				}
		for (int i = 1; i <= mapRows; ++i)
			for (int j = 1; j <= mapCols; ++j)
				if(m[i][j].belongTo != -1 && m[i][j].type != 'K') noking[i][j] = 1;
		for (int i = 1; i <= mapRows; ++i)
			for (int j = 1; j <= mapCols; ++j)
				if(m[i][j].belongTo == myid) geted[i][j] = 1;
		for (int i = 1; i <= mapRows; ++i)
			for (int j = 1; j <= mapCols; ++j)
				if((geted[i][j - 1] || m[i][j - 1].belongTo == 0) && (geted[i][j + 1] || m[i][j + 1].belongTo == 0) && (geted[i - 1][j] || m[i - 1][j].belongTo == 0) && (geted[i + 1][j] || m[i + 1][j].belongTo == 0) && (geted[i][j] || m[i][j].belongTo == 0) && noking[i][j]) noneed[i][j] = 1;	
		for (int i = 1; i <= mapRows; ++i)
			for (int j = 1; j <= mapCols; ++j)
				if(!noneed[i][j] && noneed[i][j - 1] && noneed[i][j + 1] && noneed[i + 1][j] & noneed[i - 1][j])
					noneed[i][j - 1] = noneed[i][j + 1] = noneed[i - 1][j] = noneed[i + 1][j] = 0;
		if(round % 100 == 0){
			memset(noneed, 0, sizeof noneed);
			memset(noking, 0, sizeof noking);
			memset(geted, 0, sizeof geted);
		}
		for(int i = 1; i <= mapRows; i++) noneed[i][0] = noneed[i][mapCols + 1] = 1;
		for(int i = 1; i <= mapCols; i++) noneed[0][i] = noneed[mapRows + 1][i] = 1;
		while(!otherking.empty()){
			int x = otherking.back().first, y = otherking.back().second;
			if(m[x][y].type == 'C' || m[x][y].type == 'B') otherking.pop_back();
			else break;
		}
		if(!otherking.empty()){
			memset(vis, 0, sizeof vis);
			queue<movement> q; int sx = otherking.back().first, sy = otherking.back().second;
			q.push({sx, sy, 4}); vis[sx][sy] = 1; while(!q.empty()){
				int x = q.front().x, y = q.front().y; q.pop();
				for(int i = 0; i < 4; i++){
					int nx = x + dx[i], ny = y + dy[i], nf = (i + 2) % 4;
					if((m[nx][ny].type == 'C' && m[nx][ny].belongTo == 0 && m[nx][ny].army > 10) || m[nx][ny].type == 'M' || vis[nx][ny] || nx < 1 || mapRows < nx || ny < 1 || mapCols < ny) continue;
					if(nx == armyposx && ny == armyposy){
						tposx = armyposx + dx[nf]; tposy = armyposy + dy[nf];
						return {nx, ny, nf};
					}
					q.push({nx, ny, nf}); vis[nx][ny] = 1;
				}
			}
		}
		while(!otherarmy.empty()){
			int x = otherarmy.back().first, y = otherarmy.back().second;
			if(m[x][y].belongTo == myid || noneed[x][y]) otherarmy.pop_back();
			else break;
		}
		if(!otherarmy.empty()){
			memset(vis, 0, sizeof vis);
			queue<movement> q; int sx = otherarmy.back().first, sy = otherarmy.back().second;
			q.push({sx, sy, 4}); vis[sx][sy] = 1; while(!q.empty()){
				int x = q.front().x, y = q.front().y; q.pop();
				for(int tmp = 0; tmp < 10; tmp++){
					int i = rand() % 4;
					int nx = x + dx[i], ny = y + dy[i], nf = (i + 2) % 4;
					if((m[nx][ny].type == 'C' && m[nx][ny].belongTo == 0 && m[nx][ny].army > 10) || m[nx][ny].type == 'M' || vis[nx][ny] || nx < 1 || mapRows < nx || ny < 1 || mapCols < ny) continue;
					if(nx == armyposx && ny == armyposy){
						tposx = armyposx + dx[nf]; tposy = armyposy + dy[nf];
						return {nx, ny, nf};
					}
					q.push({nx, ny, nf}); vis[nx][ny] = 1;
				}
			}
		}
		queue<movement> q; int sx = armyposx, sy = armyposy;
		memset(vis, 0, sizeof vis); vis[sx][sy] = 1;
		for(int tmp = 0; tmp < 10; tmp++){
			int i = rand() % 4;
			int nx = sx + dx[i], ny = sy + dy[i];
			if(m[nx][ny].type == 'M' || vis[nx][ny] || nx < 1 || mapRows < nx || ny < 1 || mapCols < ny) continue;
			if(m[nx][ny].belongTo != myid){
				tposx = sx + dx[i], tposy = sy + dy[i];
				return {sx, sy, i};
			}
			q.push({nx, ny, i}); vis[nx][ny] = 1;
		}
		while(!q.empty()){
			int x = q.front().x, y = q.front().y, f = q.front().dir; q.pop();
			for(int i = 0; i < 4; i++){
				int nx = x + dx[i], ny = y + dy[i];
				if(m[nx][ny].type == 'M' || vis[nx][ny] || nx < 1 || mapRows < nx || ny < 1 || mapCols < ny) continue;
				if(m[nx][ny].belongTo != myid){
					tposx = sx + dx[f], tposy = sy + dy[f];
					return {sx, sy, f};
				}
				q.push({nx, ny, f}); vis[nx][ny] = 1;
			}
		}
		memset(noneed, 0, sizeof noneed);
		memset(noking, 0, sizeof noking);
		memset(geted, 0, sizeof geted);
		return {-1, -1 -1};
	}
}

