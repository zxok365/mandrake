#include <iostream>
#include <cstring>
#include <string>
#include <map>
#include <cstdio>
#include <cassert>

using namespace std;
const int MAXN = 2000000;
char s[MAXN];
char ans[MAXN];
bool isch(char x) {
	return ((x >= 'A' && x <= 'Z') || (x >= 'a' && x <= 'z'));
}
int main() {
	map <pair<string, int>, string> mapping;
	mapping.clear();
	mapping[make_pair("0E",0)] = "`";
	mapping[make_pair("0E",1)] = "~";
	mapping[make_pair("16",0)] = "1";
	mapping[make_pair("16",1)] = "!";
	mapping[make_pair("1E",0)] = "2";
	mapping[make_pair("1E",1)] = "@";
	mapping[make_pair("26",0)] = "3";
	mapping[make_pair("26",1)] = "#";
	mapping[make_pair("23",0)] = "4";
	mapping[make_pair("23",1)] = "$";
	mapping[make_pair("2E",0)] = "5";
	mapping[make_pair("2E",1)] = "%";
	mapping[make_pair("36",0)] = "6";
	mapping[make_pair("36",1)] = "^";
	mapping[make_pair("3D",0)] = "7";
	mapping[make_pair("3D",1)] = "&";
	mapping[make_pair("3E",0)] = "8";
	mapping[make_pair("3E",1)] = "*";
	mapping[make_pair("46",0)] = "9";
	mapping[make_pair("46",1)] = "(";
	mapping[make_pair("22",0)] = "0";
	mapping[make_pair("22",1)] = ")";
	mapping[make_pair("4E",0)] = "-";
	mapping[make_pair("4E",1)] = "_";
	mapping[make_pair("55",0)] = "=";
	mapping[make_pair("55",1)] = "+";
	mapping[make_pair("66",0)] = "Backspace";
	mapping[make_pair("66",1)] = "Backspace";
	mapping[make_pair("0D",0)] = "Tab";
	mapping[make_pair("0D",1)] = "Tab";
	mapping[make_pair("15",0)] = "q";
	mapping[make_pair("15",1)] = "Q";
	mapping[make_pair("1D",0)] = "w";
	mapping[make_pair("1D",1)] = "W";
	mapping[make_pair("24",0)] = "e";
	mapping[make_pair("24",1)] = "E";
	mapping[make_pair("2C",0)] = "r";
	mapping[make_pair("2C",1)] = "R";
	mapping[make_pair("2D",0)] = "t";
	mapping[make_pair("2D",1)] = "T";
	mapping[make_pair("35",0)] = "y";
	mapping[make_pair("35",1)] = "Y";
	mapping[make_pair("3C",0)] = "u";
	mapping[make_pair("3C",1)] = "U";
	mapping[make_pair("43",0)] = "i";
	mapping[make_pair("43",1)] = "I";
	mapping[make_pair("44",0)] = "o";
	mapping[make_pair("44",1)] = "O";
	mapping[make_pair("4D",0)] = "p";
	mapping[make_pair("4D",1)] = "P";
	mapping[make_pair("54",0)] = "[";
	mapping[make_pair("54",1)] = "{";
	mapping[make_pair("5B",0)] = "]";
	mapping[make_pair("5B",1)] = "}";
	mapping[make_pair("5D",0)] = "\\";
	mapping[make_pair("5D",1)] = "|";
	mapping[make_pair("58",0)] = "Caps";
	mapping[make_pair("58",1)] = "Caps";
	mapping[make_pair("1C",0)] = "a";
	mapping[make_pair("1C",1)] = "A";
	mapping[make_pair("1B",0)] = "s";
	mapping[make_pair("1B",1)] = "S";
	mapping[make_pair("25",0)] = "d";
	mapping[make_pair("25",1)] = "D";
	mapping[make_pair("2B",0)] = "f";
	mapping[make_pair("2B",1)] = "F";
	mapping[make_pair("33",0)] = "g";
	mapping[make_pair("33",1)] = "G";
	mapping[make_pair("34",0)] = "h";
	mapping[make_pair("34",1)] = "H";
	mapping[make_pair("3B",0)] = "j";
	mapping[make_pair("3B",1)] = "J";
	mapping[make_pair("42",0)] = "k";
	mapping[make_pair("42",1)] = "K";
	mapping[make_pair("4B",0)] = "l";
	mapping[make_pair("4B",1)] = "L";
	mapping[make_pair("4C",0)] = ";";
	mapping[make_pair("4C",1)] = ":";
	mapping[make_pair("52",0)] = "'";
	mapping[make_pair("52",1)] = '"';
	mapping[make_pair("5A",0)] = "Enter";
	mapping[make_pair("5A",1)] = "Enter";
	mapping[make_pair("12",0)] = "LS";
	mapping[make_pair("12",1)] = "LS";
	mapping[make_pair("1A",0)] = "z";
	mapping[make_pair("1A",1)] = "Z";
	mapping[make_pair("45",0)] = "x";
	mapping[make_pair("45",1)] = "X";
	mapping[make_pair("29",0)] = "c";
	mapping[make_pair("29",1)] = "C";
	mapping[make_pair("2A",0)] = "v";
	mapping[make_pair("2A",1)] = "V";
	mapping[make_pair("32",0)] = "b";
	mapping[make_pair("32",1)] = "B";
	mapping[make_pair("31",0)] = "n";
	mapping[make_pair("31",1)] = "N";
	mapping[make_pair("3A",0)] = "m";
	mapping[make_pair("3A",1)] = "M";
	mapping[make_pair("41",0)] = ",";
	mapping[make_pair("41",1)] = "<";
	mapping[make_pair("49",0)] = ".";
	mapping[make_pair("49",1)] = ">";
	mapping[make_pair("4A",0)] = "/";
	mapping[make_pair("4A",1)] = "?";
	mapping[make_pair("59",0)] = "RS";
	mapping[make_pair("59",1)] = "RS";
	mapping[make_pair("21",0)] = "Space";
	mapping[make_pair("21",1)] = "Space";
	
	
	
	while (scanf("%s",s) == 1) {
	int len = strlen(s);
	int anslen = 0, shift_on = 0;
	int ls = 0 ,rs = 0, caps_on = 0, caps_push = 0;
	for (int i = 0; i < len; i += 2) {
		string str;
		str.clear();
		str += s[i];
		str += s[i + 1];
		shift_on = ((ls > 0) | (rs > 0));
		//cout << ls <<" " << rs << " "<< shift_on << endl;
		int flg = (caps_on ^ shift_on); 
		if (str[0] != 'F') {
			string tmp = mapping[make_pair(str, flg)];
			if (tmp == "LS") {
				ls++;
				continue;
			}
			if (tmp == "RS") {
				rs++;
				continue;
			}
			if (tmp == "Caps") {
				if (caps_push) continue;
				caps_push = 1;
				caps_on ^= 1;
				continue;
			}
			if (tmp == "Tab") {
				ans[++anslen] = '\t';
				continue;
			}
			if (tmp == "Backspace") {
				if (anslen)	--anslen;
				continue;
			}
			if (tmp == "Space") {
				ans[++anslen] = ' ';
				continue;
			}
			if (tmp == "Enter") {
				ans[++anslen] = '\n';
				continue;
			}
			if (!isch(tmp[0])) {
				ans[++anslen] = mapping[make_pair(str,flg ^ caps_on)][0];
				continue;
			}
			else {
				ans[++anslen] = tmp[0];
				continue;
			}
		}
		else {
			i += 2;
			string tt; tt.clear();
			tt += s[i]; tt += s[i + 1];
			string tmp = mapping[make_pair(tt, flg)];
			if (tmp == "LS") {
				ls = 0;
				continue;
			}
			if (tmp == "RS") {
				rs = 0;
				continue;
			}
			if (tmp == "Caps") {
				caps_push = 0;
				continue;
			}
		}
	}
	
	for (int i = 1; i <= anslen; i++)
		putchar(ans[i]);
	puts("");
	}
}
