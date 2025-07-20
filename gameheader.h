// by szh !
#include<bits/stdc++.h>
#include<Windows.h>
#define kd(VK_NONAME) ((GetAsyncKeyState(VK_NONAME) & 0x8000)?1:0)
#define click(VK_NONAME) ((GetAsyncKeyState(VK_NONAME) & 0x8000) ? 1:0)
#define l_mouse VK_LBUTTON
#define r_mouse VK_RBUTTON
#define output_color SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE),0x0F)
using namespace std;

struct button{
	int x,y,dark_color,light_color,lighted,len;
	string name;
};
int output_speed;
void Slow_out(string s){
	for (int i=0;i<(int)(s.size());i++){
		//cout<<s[i];
		Sleep(output_speed);
	}
	return;
}
void Place(const int x, const int y) {//先列后行 
	cout<<flush;
	COORD PlaceCursorHere;
	PlaceCursorHere.X = x;
	PlaceCursorHere.Y = y;
	SetConsoleCursorPosition(GetStdHandle(STD_OUTPUT_HANDLE), PlaceCursorHere);
	return;
}
void Noedit(){
	HANDLE hStdin=GetStdHandle(STD_INPUT_HANDLE);
	DWORD mode;
	GetConsoleMode(hStdin,&mode);
	mode&=~ENABLE_QUICK_EDIT_MODE;
	mode&=~ENABLE_INSERT_MODE;
	mode&=~ENABLE_MOUSE_INPUT;
	SetConsoleMode(hStdin,mode);
}
void HideCursor(){
	CONSOLE_CURSOR_INFO cur={1,0};
	SetConsoleCursorInfo(GetStdHandle(STD_OUTPUT_HANDLE),&cur);
}
void Get_pos(POINT &pt){
    HWND hwnd=GetForegroundWindow();
    GetCursorPos(&pt);
    ScreenToClient(hwnd,&pt);
	pt.y=pt.y/16,pt.x=pt.x/8;
	return;
}
button New_button(int X,int Y,int Dark_Color,int Light_Color,string str){
	button b;
	b.x=X,b.y=Y;
	b.dark_color=Dark_Color;
	b.light_color=Light_Color;
	b.name=str;
	b.len=str.length();
	b.lighted=2;
	Place(X,Y);
	//Get_color(Dark_Color);
	cout<<str.c_str()<<endl;
	output_color;
	return b;
}
bool Click_button(button &btn){
    POINT pt;
    Get_pos(pt);
	if((pt.x>btn.x+btn.len-0.75||pt.x<btn.x-0.25||pt.y<btn.y-0.25||pt.y>btn.y+0.25)&&(btn.lighted==1||btn.lighted==2)){
	    //Get_color(btn.dark_color); 
		Place(btn.x,btn.y),cout<<btn.name.c_str();
		//output_color;
		btn.lighted=0;
	}
    if((pt.x<=btn.x+btn.len-0.75&&pt.x>=btn.x-0.25&&pt.y<=btn.y+0.25&&pt.y>=btn.y-0.25)){
    	if(btn.lighted==0||btn.lighted==2){
	    	//Get_color(btn.light_color); 
	    	Place(btn.x,btn.y),cout<<btn.name.c_str();
	    	output_color;
    		btn.lighted=1;
		}
		if(click(l_mouse)){
			return 1;
		}
	}
	return 0;
}
// by lzj
bool Click_out(int rectEside, int rectNside, int rectWside, int rectSside){
	POINT pt;
	Get_pos(pt);
	return (click(l_mouse) && ((pt.x < rectWside) || (pt.x > rectEside) || (pt.y < rectNside) || (pt.y > rectSside)));
}
struct movement{
	int x, y, dir;
};
