#include <bits/stdc++.h>
#include <windows.h>
#include <conio.h>
#include <direct.h>
#define ll long long
#define str string
#define MX 99999
using namespace std;

str run_plugin(str name){
	char s[MX];
	strcpy(s,getcwd(s,MX));
	str s2(s);
	s2+="\\";
	
	system(("\""+s2+name+"\"").c_str());
	
	str res="";
	FILE *fp;
	fp=fopen((s2+"connect.txt").c_str(),"r");
	while(1){
		int ch=fgetc(fp);
		if(feof(fp)) break;
		res+=char(ch);
	}
	fclose(fp);
	return res;
}

void send_arg(str text){
	char s[MX];
	strcpy(s,getcwd(s,MX));
	str s2(s);
	s2+="\\";
	
	FILE *fp;
	fp=fopen((s2+"connect.txt").c_str(),"w");
	fprintf(fp,"%s",text.c_str());
	fclose(fp);
}

int read_ini(str key){
	char s[MX];
	strcpy(s,getcwd(s,MX));
	str s2(s);
	s2+="\\";
	
	static str res="";
	if(res==""){
		FILE *fp;
		fp=fopen((s2+"show.ini").c_str(),"r");
		while(1){
			int ch=fgetc(fp);
			if(feof(fp)) break;
			res+=char(ch);
		}
		fclose(fp);
	}
	
	int pt=res.find(key),val=0;
	pt+=key.size();
	while(pt<res.size()-1 && isdigit(res[++pt])) val=val*10+res[pt]-'0';
	return val;
}

bool is_keywrd(str word){
	char s[MX];
	strcpy(s,getcwd(s,MX));
	str s2(s);
	s2+="\\";
	
	static str res="";
	if(res==""){
		FILE *fp;
		fp=fopen((s2+"keyword.txt").c_str(),"r");
		while(1){
			int ch=fgetc(fp);
			if(feof(fp)) break;
			res+=char(ch);
		}
		fclose(fp);
	}
	
	int pt=res.find("["+word+"]");
	return pt!=-1;
}

void init(){
	system((str("mode con lines=")+to_string(read_ini("line")+3)+str(" cols=")+to_string(read_ini("colu")+3)).c_str());
	SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE),FOREGROUND_INTENSITY);
	printf("\n Press ^Q for help ...\n");
	Sleep(3000);
}

void print(vector<str> &lin,int &pl,int &px){
	for(int i=max(0,pl-read_ini("line")/2);i<min(int(lin.size()),pl+read_ini("line")/2+1);i++){
		for(int j=0;j<=lin[i].size();j++){
			SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE),read_ini("bgclr")|read_ini("fgclr"));
			if(pl==i && px==j){
				SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE),read_ini("csr"));
				if(j==lin[i].size()) printf(" ");
			}
			for(int k=16;k>=1;k--){
				if(j+k-1<lin[i].size() && is_keywrd(lin[i].substr(j,k))){
					for(int m=0;m<k;m++){
						if(pl==i && px==j+m) SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE),read_ini("csr")|read_ini("hilt"));
						else SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE),read_ini("bgclr")|read_ini("hilt"));
						printf("%c",lin[i].substr(j,k)[m]);
					}
					j+=k-1;
					goto end;
				}
			}
			if(j==lin[i].size()) printf("\n");
			else printf("%c",lin[i][j]);
			end:SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE),read_ini("bgclr")|read_ini("fgclr"));
		}
	}
	SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE),read_ini("bgclr")|read_ini("bttm"));
	printf(" CPPeditor       lin:%3d    col:%3d\n",pl,px);
}

void update(vector<str> &lin,int &pl,int &px){
	char c=getch();
	if(c=='\r'){
		lin.insert(lin.begin()+pl+1,lin[pl].substr(px));
		lin[pl]=lin[pl].substr(0,px);
		pl++;
		px=0;
	}
	else if(c==-32){
		switch(getch()){
			case 72:
				if(pl!=0){
					pl--;
					px=min(px,int(lin[pl].size()));
				}
				break;
			case 80:
				if(pl!=lin.size()-1){
					pl++;
					px=min(px,int(lin[pl].size()));
				}
				break;
			case 75:
				if(px!=0) px--;
				else if(pl!=0){
					pl--;
					px=lin[pl].size();
				}
				break;
			case 77:
				if(px!=lin[pl].size()) px++;
				else if(pl!=lin.size()-1){
					pl++;
					px=0;
				}
				break;
			default:
				break;
		}
	}
	else if(c=='\b'){
		if(px!=0) lin[pl].erase(--px,1);
		else if(pl!=0){
			px=lin[pl-1].size();
			lin[pl-1]+=lin[pl];
			lin.erase(lin.begin()+pl);
			pl--;
		}
	}
	else if(c>=' ' && c<='~' || c=='\t') lin[pl].insert(px++,1,c);
	else if(c==6) system("explorer");
	else if(c==15){
		str txt=run_plugin("open.vbs");
		lin=vector<str>(1,"");
		for(char ch:txt){
			if(ch=='\n') lin.push_back("");
			else if(ch>=' ' && ch<='~' || ch=='\t') lin.back()+=ch;
		}
		pl=px=0;
	}
	else if(c==19){
		str txt="";
		for(str ln:lin){
			for(char ch:ln) if(ch>=' ' && ch<='~' || ch=='\t') txt+=ch;
			txt+="\n";
		}
		send_arg(txt);
		run_plugin("save.vbs");
	}
	else if(c==18){
		run_plugin("run.vbs");
	}
	else if(c==17){
		run_plugin("help.html");
	}
	else if(c==24){
		SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE),FOREGROUND_RED|FOREGROUND_BLUE|FOREGROUND_GREEN|FOREGROUND_INTENSITY);
		system("cls");
		exit(0);
	}
}

int main(){
	vector<str> lin(1,"");
	int pl=0,px=0;
	init();
	while(1){
		system("cls");
		print(lin,pl,px);
		update(lin,pl,px);
	}
}

