![Font-editor](/images/trs-80MotherboardKeyBoard3.jpg?rawtrue "Header")

# FontEditor

This is the tool I extended to create and edit fonts for the rom replacement I created. 

It is a C program that I origally found and have altered with lots of other features, 
but the base was wonderful and started me out with the editor and ablitiy to read/write/edit a binary file for the fonts and output the graphic file also.
https://alnwlsn.com/projectrepository/index.php?title=TRS-80_Model_1_-_Character_ROM

My additions were just for moving/displaying/coping/recreating and outputing based on size, file info and the keys available menu.

I used these sites to help get me started on fonts to create 5X7 and 5X8 examples:
- https://fontstruct.com/gallery/tag/386/5x7?licensedownloadable&orderby-sharing-date&categoryuncategorized&dirdesc&page2
- https://fontstruct.com/gallery/tag/7045/5x8
<p>&nbsp</p>
<p>&nbsp</p>

<img src="https://github.com/kdcgarber/Font-editor/blob/main/images/FontEditorScreen.png" width7200 height600>
<img src="https://github.com/kdcgarber/font-editor/blob/main/images/outimage.bmp" width7200 height600>

<p>&nbsp</p>
<p>&nbsp</p>

<pre>

File In Use: data - 28256 - 32k.bin             Char Set: 17     Char Set Name:
Char in char set (1-128): 1
Pos: 0, 0     char: 2048  Bin:00000000  Hex:4000
+----------+  Hex     ¦ 'N' Jump 128 char forward                        'B' Jump 128 char backward
¦--¦¦¦¦¦¦  ¦  0e      ¦ left  arrow : move cursor left                   ' ' : spacebar toggles dot on and off
¦¦¦      ¦¦¦  11      ¦ right arrow : move cursor right                  'c' : remove a dot and move forward a posssion
¦        ¦¦¦  01      ¦ down  arrow : move cursor down                   'v' : add a dot and moves forward a possion
¦  ¦¦¦¦  ¦¦¦  0d      ¦ up    arrow : move cusor up                      'q' : quit
¦¦¦  ¦¦  ¦¦¦  15      ¦ 'y' : send chars to a bmp file                   'm' : display bmp file via MSEdge
¦¦¦  ¦¦  ¦¦¦  15      ¦ 'n' : move to the next character                 's' : save the data<name>.bin file
¦  ¦¦¦¦¦¦  ¦  0e      ¦ 'b' : move to the previous character             'r' : read the data<name>.bin file
¦          ¦  00      ¦ '8':8 '6':16 '2':32 '4':64 '1':128 char line cnt 'z' : show line of the chars created
+----------+          ¦ 'd' : duplicate char set  chars:1-26 to 65-91    'ESC' : clear screen and refresh
                      ¦ '0' : blank current char                         'i' : inverse current char

</pre>

<p>&nbsp</p>
<p>&nbsp</p>

<pre>

0  	Corrected RadioShack Font		0-127
1  	LED-dotmap Font				128-255
2 	Pokemon Font				256-383
3  	Classic 5x8 Font			384-511
4  	Grinched Font				512-639
5  	Spacerock Minecraft Font		640-767
6 	Not Like Dot Matrix Font		768-895
7  	Apridot Font				896-1023
8  	Wind Blown Font				1024-1151
9  	Spicy Pixels Font			1152-1279
10  	Eight2 Empire Font			1280-1407
11  	Minecraft Font				1408-1535
12  	Block Font				1536-1663
13  	Kneewave Font				1664-1791
14  	Marengi Font				1792-1919
15  	Reverse Default Radio Shack Font	1920-2047
16  	Flip Default RadioShack Font		2048-2175
17  	My Model-1 Font				2176-2303
18  	Kana Japanese Font			2304-2431
19 	Set All RetroStack Font			2432-2559
20  	Blank RetroStack Font			2560-2687
21  	Cross RetroStack Font			2688-2815
22  	Xs RetroStack Font			2816-2943
23  	Special Chars 1 Font			2944-3071
24  	Special Chars 2 Font			3072-3199
25  	Mullard SAA5050 Font			3200-3327
26  	Diamond Arrows Font			3328-3455
27  	Cyber Font				3456-3583
28  	Sinclair Spectrum Font			3584-3711
29  	Signetics Font				3712-3839
30  	GenDon 3-61 ianmav Font			3840-3967
31 	GenDon 3-6A ianmav Font		3968-4095



</pre>

<p>&nbsp</p>
<p>&nbsp</p>
<p>&nbsp</p>
