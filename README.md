![Lowercase-Character-IC-Replacement/fontEditor](/images/trs-80MotherboardKeyBoard3.jpg?raw=true "Header")
# FontEditor

This is the tool I extended to create and edit fonts for the rom replacement I created. https://alnwlsn.com/projectrepository/index.php?title=TRS-80_Model_1_-_Character_ROM

It is a C program that I origally found and have altered with lots of other features, 
but the base was wonderful and started me out with the editor and ablitiy to read/write/edit a binary file for the fonts and output the graphic file also.
My additions were just for moving/displaying/coping/recreating and outputing based on size, file info and the keys available menu.



I also used these sites to help get me started on fonts to create 5X7 and 5X8 examples:
https://fontstruct.com/gallery/tag/386/5x7?license=downloadable&order=by-sharing-date&category=uncategorized&dir=desc&page=2
https://fontstruct.com/gallery/tag/7045/5x8
<p>&nbsp;</p>
<p>&nbsp;</p>

<img src="https://github.com/kdcgarber/Font-editor/blob/main/font-editor/images/FontEditorScreen.png" width="7200" height="600">
<img src="https://github.com/kdcgarber/font-editor/blob/main/font-editor/images/outimage.bmp" width="7200" height="600">

<p>&nbsp;</p>
<p>&nbsp;</p>

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

<p>&nbsp;</p>
<p>&nbsp;</p>

<pre>

1	Default RadioShack Font	0-127
2	LED-dotmap Font	128-255
3	Pokemon Font	256-383
4	Classic 5x7 Font	384-511
5	Grinched Font	512-639
6	Spacerock Minecraft Font	640-767
7	Not Like Dot Matrix Font	768-895
8	Apridot Font	896-1023
9	Wind Blown Font	1024-1151
10	Spicy Pixels Font	1152-1279
11	Eight2 Empire Font	1280-1407
12	Minecraft Font	1408-1535
13	Block Font	1536-1663
14	Kneewave Font	1664-1791
15	MarengiFont	1792-1919
16	Revers Default Radio Shack Font	1920-2047


</pre>

<p>&nbsp;</p>
<p>&nbsp;</p>
<p>&nbsp;</p>
