// human
namespace humanOptions{
	POINT mousePT;
	double theStartTime;
	queue<movement> options;
	void GetTheTime(double currentStartTime){
		theStartTime = currentStartTime;
		return;
	}
	movement Move(){
//		Place(30, 0);printf("%.5lf\n", (double)(clock()) - theStartTime);
		while (((double)(clock()) - theStartTime) < 0.49){
			Sleep(1);
//			Place(50, 0);printf("%d %d\n", humanChooseX, humanChooseY);
			if (click(l_mouse)){
				/*
				// debug
				Place(40, 0);printf("%d %d", (int)(mousePT.x), int)(mousePT.y);)
//				*/
				Get_pos(mousePT);
				int mouX = (int)(mousePT.x), mouY = (int)(mousePT.y);
				humanChooseX = (mouY - 5) / 2 + 1;
				humanChooseY = (mouX - 1) / 3 + 1;
				if (humanChooseX < 1 || humanChooseX > mapRows || humanChooseY < 1 || humanChooseY > mapCols){
					humanChooseX = 0;
					humanChooseY = 0;
				}
				/*
				for (int i = 1; i <= mapRows && !humanChooseX; ++i){
					for (int j = 1; j <= mapCols; ++j){
						int R = j * 4, D = i * 3 + 4;
						int L = (j - 1) * 4, U = (i - 1) * 3 + 4;
						if (L <= mousePT.x && mousePT.x <= R && U <= mousePT.y && mousePT.y <= D){
							humanChooseX = i;
							humanChooseY = j;
							break;
						}
					}
				}
//				*/
			}
			if (humanChooseX){
				int dir = -1;
				if (kd(37)){
					dir = 2;
				}
				else if (kd(38)){
					dir = 1;
				}
				else if (kd(39)){
					dir = 0;
				}
				else if (kd(40)){
					dir = 3;
				}
				if (dir != -1){
					humanChooseX += deltaX[dir];
					humanChooseY += deltaY[dir];
					if (humanChooseX < 1 || mapRows < humanChooseX || humanChooseY < 1 || mapCols < humanChooseY){
						humanChooseX -= deltaX[dir];
						humanChooseY -= deltaY[dir];
					}
					else{
						options.push((movement){humanChooseX - deltaX[dir], humanChooseY - deltaY[dir], dir});
					}
				}
			}
			if (kd(81)){
				while (!options.empty()){
					options.pop();
				}
			}
		}
		if (options.empty()){
			return (movement){-1, -1, -1};
		}
		movement topOption = options.front();
		options.pop();
		return topOption;
	}
}
