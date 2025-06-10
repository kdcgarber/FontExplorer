#include <stdio.h>
#include <io.h>
#include <fcntl.h>
#include <conio.h>
#include <stdlib.h>
#include <fstream>
#include <iostream>
#include <locale.h>
#include <direct.h>



#include "bitmap_image.hpp"
#include <windows.h>

#include <chrono>
#include <thread>

#define BUFSIZE MAX_PATH

using namespace std;

//Character colors -- notes on colors that could be used.. 
#define RESET   "\033[0m"
#define BLACK   "\033[30m"      /* Black */
#define RED     "\033[31m"      /* Red */
#define GREEN   "\033[32m"      /* Green */
#define YELLOW  "\033[33m"      /* Yellow */
#define BLUE    "\033[34m"      /* Blue */
#define MAGENTA "\033[35m"      /* Magenta */
#define CYAN    "\033[36m"      /* Cyan */
#define WHITE   "\033[37m"      /* White */
#define BOLDBLACK   "\033[1m\033[30m"      /* Bold Black */
#define BOLDRED     "\033[1m\033[31m"      /* Bold Red */
#define BOLDGREEN   "\033[1m\033[32m"      /* Bold Green */
#define BOLDYELLOW  "\033[1m\033[33m"      /* Bold Yellow */
#define BOLDBLUE    "\033[1m\033[34m"      /* Bold Blue */
#define BOLDMAGENTA "\033[1m\033[35m"      /* Bold Magenta */
#define BOLDCYAN    "\033[1m\033[36m"      /* Bold Cyan */
#define BOLDWHITE   "\033[1m\033[37m"      /* Bold White */


//---------------------------------------------
// The original ROM is just 1024 (1k) and just 1 full set of characters.
// The 2716 is 2 times that size. the  27128 is 16 times the size so it will hold 16 full char sets.
// comment and uncomment the groupings of constants for which ever eprom you are wanting to work with.

// 2716 EPROM - 2kx8bit : 2 full character sets : 128 char per set
	//const int romSize = 2048;
	//const int charPerRom = 256;
	//const int charPerRom1 = 255;      // just one less then charPerRom
	//const int bitMapWidth = 384;      // bits in the width of the graphic bitmap image
	//const int bitMapHeight = 68;      // bits in the heigth of the graphic bitmap image 
	//const string dataBinName = "data - 2716 - 2k.bin";  // file to store fonts in for EPROM
	//const int fontCount = 2; // number of fonts (128 chars) sets in the rom 
// 27128   - 16kx8bit : 16 full character sets : 128 char per set 
  //const int romSize = 16384;
  //const int charPerRom = 2048;
  //const int charPerRom1 = 2047;         // just one less then charPerRom
  //const string dataBinName = "data - 27128 - 16k.bin";  // file to store fonts in for EPROM 
  //const int bitMapWidth = 384;          // bits in the width of the graphic bitmap image 
  //const int bitMapHeight = 522;         // bits in the heigth of the graphic bitmap image
  //const int fontCount =16; // number of fonts (128 chars) sets in the rom 

// AT28HC256 - 12SU EEPROM 256K 32K x 8 120 ns 4.5V - 5.5V
  const int romSize = 32767;
  const int charPerRom = 4096;
  const int charPerRom1 = 4095;       // just one less then charPerRom
  const string dataBinName = "data - 28256 - 32k.bin";  // file to store fonts in for EPROM 
  const int bitMapWidth = 384;        // bits in the width of the graphic bitmap image 
  const int bitMapHeight = 1044;      // bits in the heigth of the graphic bitmap image
  const  int fontCount = 32; // number of fonts (128 chars) sets in the rom 


  int bitMapCharCount = 128;   // 128 or 64 is the number of chars per line to output to bmp
  int charPerCharSet = 127;    // this is always ( 128 - 1 ) as a variable for how many chars are in a font set
  // -------------------------------------------------


unsigned char charlet[5][8][romSize];

signed int cselect = 0;
unsigned char cy = 0;
unsigned char cx = 0;
signed int viewData = 0;

string fontNameList[64];    // list of all the font names  (it set at 64 for more fonts in the future maybe

unsigned int cellNumberInFont;




/*
   notes of charlet[x][y][z] :   this is the char array that holds all the font characters
      z is the number of the character in the set of chars  with a total count of chars of romSize
      x is the char possition left to right of a char 5 in length (0 - 4) wide: this is the hex value you will see in a dump  like 0e or 11
      y is the row in the char of 8 in higth  (0 - 7) tall:  this is 7 wide in the dump per char                              like 0e 11 01 0d 15 15 03 00

	x axis ->
    0 1 2 3 4      row = 1 hex byte
   ┌──────────┐
0  │████████  │ y      1e  = 11110
1  │  ██    ██│        09  = 01001
2  │  ██    ██│	a      09  = 01001
3  │  ██████  │	x      0e  = 01110
4  │  ██    ██│	i      09  = 01001
5  │  ██    ██│	s      09  = 01001
6  │████████  │        1e  = 11110
7  │          │        00  = 0000
   └──────────┘   8 rows = 1 char format of bytes, 8 bytes = 1 character
*/


void setFontName() {
	fontNameList[0] = "Corrected RadioShack Font";
	fontNameList[1] = "LED-dotmap Font";
	fontNameList[2] = "Pokemon Font";
	fontNameList[3] = "Classic 5x8 Font";
	fontNameList[4] = "Grinched Font";
	fontNameList[5] = "Spacerock Minecraft Font";
	fontNameList[6] = "Not Like Dot Matrix Font";
	fontNameList[7] = "Apridot Font";
	fontNameList[8] = "Wind Blown Font";
	fontNameList[9] = "Spicy Pixels Font";
	fontNameList[10] = "Eight2 Empire Font";
	fontNameList[11] = "Minecraft Font";
	fontNameList[12] = "Block Font";
	fontNameList[13] = "Kneewave Font";
	fontNameList[14] = "Marengi Font";
	fontNameList[15] = "Reverse Default Radio Shack Font";
	fontNameList[16] = "Flip Default RadioShack Font";
	fontNameList[17] = "My Model-1 Font";
	fontNameList[18] = "Kana Japanese Font";
	fontNameList[19] = "Set All RetroStack Font";
	fontNameList[20] = "Blank RetroStack Font";
	fontNameList[21] = "Cross RetroStack Font";
	fontNameList[22] = "Xs RetroStack Font";
	fontNameList[23] = "Special Chars 1 Font";
	fontNameList[24] = "Special Chars 2 Font";
	fontNameList[25] = "Mullard SAA5050 Font";
	fontNameList[26] = "Diamond Arrows Font";
	fontNameList[27] = "Cyber Font";
	fontNameList[28] = "Sinclair Spectrum Font";
	fontNameList[29] = "Signetics Font";
	fontNameList[30] = "GenDon 3-61 ianmav Font";
	fontNameList[31] = "GenDon 3-6A ianmav Font";
}

void SetCursorPosition(char x, char y)
{
	static const HANDLE hOut = GetStdHandle(STD_OUTPUT_HANDLE);
	std::cout.flush();
	COORD coord = { (SHORT)x, (SHORT)y };
	SetConsoleCursorPosition(hOut, coord);
}

void ShowConsoleCursor(bool showFlag)
{
	HANDLE out = GetStdHandle(STD_OUTPUT_HANDLE);

	CONSOLE_CURSOR_INFO     cursorInfo;

	GetConsoleCursorInfo(out, &cursorInfo);
	cursorInfo.bVisible = showFlag; // set the cursor visibility
	SetConsoleCursorInfo(out, &cursorInfo);
}

// copy upper case to second upcase line to duplicate so I dont have to enter it in twice
void dupUppers() {
	int charToCopyLength = 25;  // move 1 - 26  : 26 chars in captial alaphabet  
	int currentCharSet((cselect / 128)); // get the font string (0 based)
	int startOfCopy = (currentCharSet * 128); // get to the fist char in the char set (the @ sign + 1)
	for (int repeatw = startOfCopy + 1; repeatw <= (startOfCopy + charToCopyLength + 1); repeatw++) {
		for (int moveAByte = 0; moveAByte <= 7; moveAByte++) {  // byte per char is 8 (0 - 7)
			for (int moveABit = 0; moveABit <= 4; moveABit++) {
				//wprintf(L" %-4.4d %-4.4d %-8.8d %-8.8d \n", moveABit, moveAByte, repeatw, repeatw + 65);  // print font number 
				charlet[moveABit][moveAByte][repeatw + 64] = charlet[moveABit][moveAByte][repeatw];
			}
		}
	}
	//_getch();
	//std::this_thread::sleep_for(chrono::seconds(60)); // sleep 60 seconds to view screen
}


// right side of frame and the hex value of the row-- - value can be seen in the dataBinName file that is written
unsigned char binline(unsigned char binrow) {
	unsigned char h = 0;
	for (int i = 0; i <= 4; i++) {
		h = h << 1;
		if (charlet[i][binrow][cselect] > 0) {
			h += 1;
		}
	}
	return h;
}

// this will blank all cells of the current char
void clearCurrentChar() {  
	for (int j = 0; j <= 7; j++) {
		for (int i = 0; i <= 4; i++) {      //loop through the contents of characater letter 
			switch (charlet[i][j][cselect]) {
			case 1:           //light cell
				charlet[i][j][cselect] = 0;    //set current char to blank to clear it of current value:  un-light
				break;
			case 2:          //selected+dark cell      - dont need to do anything
				break;
			case 3:          //selected+light dell     - unlight it and select it
				charlet[i][j][cselect] = 2;    //set current char to dark to clear it of current value:   un-light
				break;
			default:         //dark cell               - dont need to do anything
				break;
			}
		}	
	}
}


// this will invert all the cells of the current char
void inverseCurrentChar() {   
	for (int j = 0; j <= 7; j++) {
		for (int i = 0; i <= 4; i++) {      //loop through the contents of characater letter 
			switch (charlet[i][j][cselect]) {
			case 1:           //light cell
				charlet[i][j][cselect] = 0;    //set current char to blank to clear it of current value:  un-light
				break;
			case 2:          //selected+dark cell      -  so make it light (invert)
				charlet[i][j][cselect] = 3;    //set current char to dark to light (invert)
				break;
			case 3:          //selected+light dell     - unlight it and select it
				charlet[i][j][cselect] = 2;    //set current char to dark to clear it of current value:   un-light
				break;
			default:         //dark cell               - dont need to do anything
				charlet[i][j][cselect] = 1;    //set current char to light:   invert
				break;
			}
		}
	}
}



// this will fLIP all the cells of the current char
void flipCurrentChar() {
	int data[5];
	for (int j = 0; j <= 7; j++) {
		for (int i = 0; i <= 4; i++) {      //loop through the contents of characater letter 
			data[i] = charlet[i][j][cselect];
		}
		for (int i = 0; i <= 4; i++) {      //loop through the contents of characater letter 
			charlet[i][j][cselect] = data[4 - i];
		}
	}
}



void printbin(unsigned char t) {
	if (t & 0x80) { wprintf(L"1"); }
	else { wprintf(L"0"); }
	if (t & 0x40) { wprintf(L"1"); }
	else { wprintf(L"0"); }
	if (t & 0x20) { wprintf(L"1"); }
	else { wprintf(L"0"); }
	if (t & 0x10) { wprintf(L"1"); }
	else { wprintf(L"0"); }
	if (t & 0x08) { wprintf(L"1"); }
	else { wprintf(L"0"); }
	if (t & 0x04) { wprintf(L"1"); }
	else { wprintf(L"0"); }
	if (t & 0x02) { wprintf(L"1"); }
	else { wprintf(L"0"); }
	if (t & 0x01) { wprintf(L"1"); }
	else { wprintf(L"0"); }
}


// help menu lines
void helpMenu(int currentRow) {
	switch (currentRow) {
	case 0: 
		wprintf(L"      \x2502 \x1b[1mleft  arrow\x1b[0m : move cursor left                   ' ' : \x1b[1mspacebar\x1b[0m toggles dot on and off\n");
		break;
	case 1:
		wprintf(L"      \x2502 \x1b[1mright arrow\x1b[0m : move cursor right                  '\x1b[1mc\x1b[0m' : remove a dot and move forward a posssion\n");
		break;
	case 2:
		wprintf(L"      \x2502 \x1b[1mdown  arrow\x1b[0m : move cursor down                   '\x1b[1mv\x1b[0m' : add a dot and moves forward a possion\n");
		break;
	case 3:
		wprintf(L"      \x2502 \x1b[1mup    arrow\x1b[0m : move cusor up                      '\x1b[1mq\x1b[0m' : quit\n");
		break;
	case 4:
		wprintf(L"      \x2502 '\x1b[1my\x1b[0m' : send chars to a bmp file                   '\x1b[1mm\x1b[0m' : display bmp file via MSEdge\n");
		break;
	case 5:
		wprintf(L"      \x2502 '\x1b[1mn\x1b[0m' : move to the next character                 '\x1b[1ms\x1b[0m' : save the data<name>.bin file\n");
		break;
	case 6:
		wprintf(L"      \x2502 '\x1b[1mb\x1b[0m' : move to the previous character             '\x1b[1mr\x1b[0m' : read the data<name>.bin file\n");
		break;
	case 7:
		wprintf(L"      \x2502 '\x1b[1m8\x1b[0m':8 '\x1b[1m6\x1b[0m':16 '\x1b[1m2\x1b[0m':32 '\x1b[1m4\x1b[0m':64 '\x1b[1m1\x1b[0m':128 char line cnt '\x1b[1mz\x1b[0m' : show line of the chars created\n");
		break;
	case 8:
		wprintf(L"          \x2502 '\x1b[1md\x1b[0m' : duplicate char set  chars:1-26 to 65-91    '\x1b[1mESC\x1b[0m' : clear screen and refresh \n");
		break;
	case 9:
		wprintf(L"                      \x2502 '\x1b[1m0\x1b[0m' : blank current char                         '\x1b[1mi\x1b[0m' : inverse current char \n");
		break;
	case 10:
		wprintf(L"                      \x2502 '\x1b[1mf\x1b[0m' : Split to <fontname>.bin                    '\x1b[1mI\x1b[0m' : Flip current char  \n");
		break;
	case 11:
		wprintf(L"                      \x2502 '\x1b[1mS\x1b[0m' : Read in Split <fontname>.bin to current \n");
		break;
	}
}



// Output whats in the charlet to the screen to see the values::   5x8 grid for a line of chars of lenght that is chosen
void viewAllData(int charLineCount) {
	wprintf(L"\n");
	int columnPossition;
	int charPerLine = (charLineCount -1 );  // 16 total 0-15, zero based
	int rowToDisplay = cselect / ( charPerLine +1);
		for (int j = 0; j <= 7; j++) { // dislay next row of chars
			for (int jchar = 0; jchar <= charPerLine; jchar++) {  // output 1 full line of a char per row accoss the page
				for (int i = 0; i <= 4; i++) {      // display 5 bits per character 
					switch(charlet[i][j][(jchar + (rowToDisplay * (charPerLine +1)))]) {
					case 1:
						wprintf(L"\x2588\x2588"); //light cell
						break;
					case 2:
						wprintf(L"--"); //selected+dark
						break;
					case 3:
						wprintf(L"\x2592\x2592"); //selected+light
						break;
					default:
						wprintf(L"  "); //dark cell
						break;
					}
				}
				wprintf(L" \x2502 ");// add " | " between each character
			}
			wprintf(L"\n");  // new line per row
		}

		// write spaces to get to the correct possition to underline the char in use
		columnPossition = (((cselect * 13) - 2) - (rowToDisplay * ((charPerLine + 1) * 13)));
		for (int movespaces = 0; movespaces <= columnPossition; movespaces++) {
			wprintf(L" ");
		}
		// add the uderline to the char in use
		wprintf(L"\x2500\x2500\x2500\x2500\x2500\x2500\x2500\x2500\x2500\x2500\x2500\x2500");
		//wprintf(L"\t\t\t %d %d",rowToDisplay, charPerLine);
		//write spaces to clear the rest of the full line 
		for (int movespaces = 0; movespaces <= (((charPerLine + 1) * 13) - (columnPossition + 13)); movespaces++) {
			wprintf(L" ");
		}

}


// main screen
void screenprint( int viewData, int charLineCount) {
	//system("CLS");
	string fontName;
	SetCursorPosition( 0, 0 );
	_setmode(_fileno(stdout), _O_U16TEXT);
	wprintf(L"File In Use: \x1b[1m%S\x1b[0m", dataBinName.c_str());
	wprintf(L"\t\t\033[1m\033[32mChar Set: %2d\x1b[0m", int (cselect / 128) + 1 );         // char set group of 128 chars  (1 based)
	fontName = fontNameList[(cselect / 128)]; // get the font string (0 based)
	wprintf(L"\t Char Set Name: \x1b[1m\"%-35S\"\x1b[0m\n", fontName.c_str()); // font set name
	cellNumberInFont = ((cselect +1 )  - int ((cselect / 128) * 128) );
	wprintf(L"Char in char set (1-128): %-4.0d\n", cellNumberInFont);  //cell number in the font set 1-128
	wprintf(L"Pos: %d, %d", cx, cy);  //possition line
	wprintf(L"     char: %-4.4d  Bin:", cselect);  // print font number 
	printbin(cselect);    //print binary font number
	wprintf(L"  Hex:%4x\n", ( cselect * 8 )); //hex of the font number
	wprintf(L"\x250c\x2500\x2500\x2500\x2500\x2500\x2500\x2500\x2500\x2500\x2500\x2510  Hex     \x2502 '\x1b[1mN\x1b[0m' Jump 128 char forward                        '\x1b[1mB\x1b[0m' Jump 128 char backward\n"); //top of frame
	unsigned char cselected = 0;
	for (int j = 0; j <= 7; j++) {
		wprintf(L"\x2502"); // left frame
		for (int i = 0; i <= 4; i++) {      //loop to draw the contents of characater letter 
			if (i == cx && j == cy) { cselected = 2; }
			else { cselected = 0; }
			switch (charlet[i][j][cselect] + cselected) {
			case 1:
				wprintf(L"\x2588\x2588"); //light cell
				break;
			case 2:
				wprintf(L"--"); //selected+dark
				break;
			case 3:
				wprintf(L"\x2592\x2592"); //selected+light
				break;
			default:
				wprintf(L"  "); //dark cell
				break;
			}
		}
		wprintf(L"\x2502  %2.2x", binline(j));  // right side of frame and the hex value of the row  --- value can be seen in the dataBinName file that is written
		helpMenu(j);
	}
	wprintf(L"\x2514\x2500\x2500\x2500\x2500\x2500\x2500\x2500\x2500\x2500\x2500\x2518"); //bottom of frame
	helpMenu(8);
	helpMenu(9);
	helpMenu(10);
	helpMenu(11);
    if ( viewData == 1) { viewAllData( charLineCount ); }
}

// write the font binary font file
void writefile() {
	std::ofstream cfile(dataBinName, std::ofstream::binary);
	for (int ichar = 0; ichar <= charPerRom1; ichar++) {
		for (int irow = 0; irow <= 7; irow++) {
				unsigned char temp = 0;
				for (int icol = 0; icol <= 4; icol++) {
					temp = temp << 1;
					if (charlet[icol][irow][ichar] > 0) {
						temp += 1;
					}
				}
				cfile.write((char*)&temp, sizeof(unsigned char));
		}
	}
}

// write each font a separate file
void writeindividualfile() {
	_mkdir("individualFonts");
	for (int newFile = 0; newFile <= (fontCount - 1); newFile++) {
	  string individualFile = std::string("individualFonts\\") + fontNameList[newFile] + std::string(".bin") ;
	  //wprintf(L"---- %S ---", individualFile.c_str());
	  std::ofstream cfile(individualFile.c_str(), std::ofstream::binary);
	  for (int ichar = (newFile * bitMapCharCount); ichar < ((newFile + 1) * bitMapCharCount); ichar++) {
		 for (int irow = 0; irow <= 7; irow++) {
			unsigned char temp = 0;
			for (int icol = 0; icol <= 4; icol++) {
				temp = temp << 1;
				if (charlet[icol][irow][ichar] > 0) {
					temp += 1;
				}
			}
			cfile.write((char*)&temp, sizeof(unsigned char));
		 }
	  }
    }
}


//------------------------------------------------------ working on now... --------------------------------------------
// read individual font file in the individualFonts direcotry and put it in the place of the current set selected
void readindividualfile() {
	int newFile = (cselect / 128);
	string individualFile = std::string("individualFonts\\") + fontNameList[newFile] + std::string(".bin");
	std::ifstream cfile(individualFile, std::ifstream::binary);
	for (int ichar = (newFile * bitMapCharCount); ichar < ((newFile + 1) * bitMapCharCount); ichar++) {
		for (int irow = 0; irow <= 7; irow++) {

			unsigned char temp = 0;
			cfile.read((char*)&temp, sizeof(unsigned char));

			for (int icol = 0; icol <= 4; icol++) {
				if (((temp >> (4 - icol)) & 1) >= 1) {
					charlet[icol][irow][ichar] = 1;
				}
				else {
					charlet[icol][irow][ichar] = 0;
				}
				//wprintf(L"%2.2d %2.2d %2.2d %2.2d %2.2d\n", icol, irow, ichar, temp, charlet[icol][irow][ichar]);
			}
		}
	}
	cfile.close();
}


// read the binary font file
void readnfile() {
	std::ifstream cfile(dataBinName, std::ifstream::binary);
	for (int ichar = 0; ichar <= charPerRom1; ichar++) {
		for (int irow = 0; irow <= 7; irow++) {
			unsigned char temp = 0;
			cfile.read((char*)&temp, sizeof(unsigned char));
			for (int icol = 0; icol <= 4; icol++) {
				if (((temp >> (4 - icol)) & 1) >= 1) {
					charlet[icol][irow][ichar] = 1;
				}
				else {
					charlet[icol][irow][ichar] = 0;
				}
			}
		}
	}
	cfile.close();
}



// the outimage.bmp file needs to be there, it doenst create it and it needs to be the size of the file it will write, or bigger..
void outimage() {
	int icrow = 0;
	int iccol = 0;
	int bitMapWidthVar = bitMapWidth;
	int bitMapHeightVar = bitMapHeight;
	
	if (bitMapCharCount == 128) {
		bitMapWidthVar = (bitMapWidthVar * 2 );
		bitMapHeightVar = (bitMapHeightVar / 2); // the 120 is to allow for spaces between each line when I did the extra iccol++
	}
	bitmap_image image(bitMapWidthVar, bitMapHeightVar);
	image.clear();
	for (int jchar = 0; jchar <= charPerRom1; jchar++) {
		for (int ccol = 0; ccol <= 7; ccol++) {
			for (int crow = 0; crow <= 4; crow++) {
				//wprintf(L"        %4.4x %4.4x %4.4x\n", jchar, (6 * icrow + crow), (8 * iccol + ccol) );
				if (charlet[crow][ccol][jchar] > 0) {
					image.set_pixel(6 * icrow + crow, 8 * iccol + ccol, 0, charPerRom1, 0);
				}
				else {
					image.set_pixel(6 * icrow + crow, 8 * iccol + ccol, 0, 0, 0);
				}
			}
		}
		icrow++;
		if (icrow == bitMapCharCount) {
			icrow = 0;
			iccol++;
			if (((jchar + 1) % 128) == 0) { // is jchar module 128 if it is add a blank line because it the end of a char set
					iccol++;
			}
		}
	}
	image.save_image("outimage.bmp");
}

void notifyAction() {
	SetCursorPosition(40, 0);
	wprintf(L"\033[31m*\x1b[0m");  // indicate a choice was made with Red *
	std::this_thread::sleep_for(chrono::milliseconds(50)); // sleep 1 seconds to view screen
	SetCursorPosition(40, 0);
	wprintf(L" ");  // clear Red *
}

int main()
{

	int viewData = 0;
	int charLineCount = 8;
	int k = 0;
	int nextJump = 0;
	WCHAR Buffer[BUFSIZE];
	LPCWSTR fileName;
	LPCWSTR edgeAttributes;
	LPCWSTR fileToDisplay;
	LPCWSTR pathToBMP;

	setFontName();
	ShowConsoleCursor(false);   // hide the cursor so there is no flashing cursor..
	GetCurrentDirectory(BUFSIZE, Buffer);
	fileName = L"\\outimage.bmp";
	//edgeAttribu
	pathToBMP = Buffer;   
	edgeAttributes = L"";
	std::wstring fullNamePath = std::wstring(edgeAttributes) + std::wstring(pathToBMP) + std::wstring(fileName);
	fileToDisplay = fullNamePath.c_str();

	readnfile();  // read file at start as the default...
	while (k != 'q') {
		screenprint( viewData , charLineCount);
		k = 0;
		while (k == 0) {
			k = _getch();
		}

		//wprintf(L"\x2502  %2.2i", k);
		switch (k) {
		case 75: cx--;   break;		// move left
		case 77: cx++;   break;		// move right
		case 80: cy++;   break;		// move down
		case 72: cy--;   break;		// move up
		case ' ': if (charlet[cx][cy][cselect] != 0) { charlet[cx][cy][cselect] = 0; }   // spacebar toggles dot on and off
				else { charlet[cx][cy][cselect] = 1; }	break;
		case 'c':					// remove a dot to the char and moves it forward
			charlet[cx][cy][cselect] = 0;
			cx++;
			if (cx == 5) { cx = 0; cy++; }
			if (cy == 8) { cy = 0; }
			break;
		case 'v':					// add a dot to the char and moves it forward
			charlet[cx][cy][cselect] = 1;
			cx++;
			if (cx == 5) { cx = 0; cy++; }
			if (cy == 8) { cy = 0; }
			break;
		case 'N':					// move to the next character
			cselect = cselect + 128;
			if (cselect >= charPerRom) { cselect = 0; }
			break;
		case 'B':					// move to the previous character
			cselect = cselect - 128;
			if (cselect <= -1) { cselect = charPerRom1; }
			break;
		case 'n':					// move to the next character
			cselect++;
			if (cselect == charPerRom) { cselect = 0; }
			break;
		case 'b':					// move to the previous character
			cselect--;
			if (cselect == -1) { cselect = charPerRom1; }
			break;
		case 's':					// write the data.bin file
			writefile();
			notifyAction();
			break;
		case 'r':					//  read the data.bin file 
			readnfile();
			notifyAction();
			break;
		case 'y':					// send the chars to an bmp file
			outimage();
			notifyAction();
			break;
		case 'z':               // toggle show all the chars created
			if (viewData == 1) { viewData = 0; }
			else { viewData = 1; }
			notifyAction();
			break;
		case '8':
			charLineCount = 8;
			system("CLS");
			notifyAction();
			break;
		case '6':
			charLineCount = 16;
			system("CLS");
			notifyAction();
			break;
		case '2':
			charLineCount = 32;
			system("CLS");
			notifyAction();
			break;
		case '4':
			charLineCount = 64;
			system("CLS");
			notifyAction();
			break;
		case '1':
			charLineCount = 128;
			system("CLS");
			notifyAction();
			break;
		case 'm':
			// windows launch MSEdge to display the saved bmp of the fonts dumped
			//ShellExecute(0, L"Open", L"msedge", fileToDisplay, 0, SW_SHOWNORMAL);
			ShellExecute(0, L"Open", L"msedge", fileToDisplay, 0, SW_SHOWNORMAL);
			break;
		case 'd':
			dupUppers();
			break;
		case 27:  // if you hit esc it will clear the screen 
			system("CLS");
			break;
		case 'i':
			inverseCurrentChar();
			break;
		case '0':
			clearCurrentChar();
			break;
		case 'f':
			writeindividualfile();
			notifyAction();
			break;
		case 'I':
			flipCurrentChar();
			break;
		case 'S':
			readindividualfile();
			notifyAction();
			break;
		}
		// as it moves through the char, ensure the chars on the display stay bounded
		if (cx >= charPerRom1) { cx = 0; }
		if (cx >= 4) { cx = 4; }
		if (cy >= charPerRom1) { cy = 0; }
		if (cy >= 7) { cy = 7; }

	}
	return 0;
}
