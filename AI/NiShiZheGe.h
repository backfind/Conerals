//Author:back_find
namespace NiShiZheGe{
	const int dx[4]={0,-1,0,1};
	const int dy[4]={1,0,-1,0};
	struct City{
		int x,y;
		bool is_king;
	};
	struct state{
		int x,y;
		int v;
	};
	struct task{
		int x,y;
		double lev;
		string type;	
	};
	int Myid,MyKingX,MyKingY,turn;
	double BotAttackive[16+5],CityAttackable[2505];
	Block m[55][55],old[55][55];
	int dis[N];
	vector<City>CityList;
	priority_queue<int>TaskQueue;
	priority_queue<state>DisQueue;
	bool inmap(int x,int y){
		return (x>=1)&&(x<=mapRows)&&(y>=1)&&(y<=mapCols);
	} 
	void Init(){
		Myid=MyKingX=MyKingY=turn=MeetBot=0;
		CityList.clear();
		while(TaskQueue.size())TaskQueue.pop();
		for(int i=0;i<=15;i++)BotAttactive[i]=0;
	}
	int Dijkstra(int sx,int sy,int ex,int ey){
		memset(dis,0x3f,sizeof dis);
		DisQueue.push({sx,sy,0}); 
		while(!DisQueue.empty()){
			state u=DisQueue.top();DisQueue.pop();
			for(int i=0;i<4;i++){
				int tx=x+tx[i],ty=y+ty[i];
				if(!inmap(tx,ty))return;
				if()
			}
		}
	}
	double CalcDefendLev(int x,int y,int id){
		double now=0.0,div=0;
		for(int u:CityList){
			double mass=1.0;
			if(is_king)mass*=10.0;
			div+=mass;
		}
	}
	movement Move(){
		turn++; 
		for(int i=1;i<=mapRows;i++)
			for(int j=1;j<=mapCols;j++)
				m[i][j]=Ask(i,j);
		if(turn==1){
			for(int i=1;i<=mapRows;i++)
				for(int j=1;j<=mapCols;j++)
					if(m[i][j].type=='K')}{
						Myid=m[i][j].belongTo;
						MyKingX=i,MyKingY=j;
						CityList.push_back({i,j,1});
					}
		}else{
			for(int i=1;i<=mapRows;i++)
				for(int j=1;j<=mapCols;j++)
					if(m[i][j].belongTo==Myid)
			//Calc Defend lev
			for(int i=1;i<=mapRows;i++)
				for(int j=1;j<=mapCols;j++)
					if(m[i][j].belongTo!=Myid && (m[i][j].army-old[i][j].army>1 || m[i][j].belongTo!=old[i][j].belongTo))
						TaskQueue.push({i,j,CalcDefendLev(i,j,m[i][j].type),"defend"});
		}
		old=m;
		return;
	}
}

