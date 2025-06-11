![Font-editor](/images/trs-80MotherboardKeyBoard3.jpg?rawtrue "Header")

# FontEditor

This editor is for editing characters of 5x8 in size. The characters are then stored in a set of 128 chars per set in a binary file totaling 32 character sets.
This data ican then be used to write to a EEROM like the one I used, a  28256 - 32k ROM for my TRS-80 model 1. (AT28C256-15SU-T)
It also supports other files with a few changes, which I originally used and the config values are still in the code and can be resused.

It is a C program that I origally found and have altered with lots of other features, 
but the base was wonderful and started me out with the editor and ablitiy to read/write/edit a binary file for the fonts and output the graphic file also.
https://alnwlsn.com/projectrepository/index.php?title=TRS-80_Model_1_-_Character_ROM

My additions were just for moving/displaying/coping/recreating and outputing based on size, file info and the keys available menu.

I also used these sites to help get me started on fonts to create 5X7 and 5X8 examples:
- https://fontstruct.com/gallery/tag/386/5x7?licensedownloadable&orderby-sharing-date&categoryuncategorized&dirdesc&page2
- https://fontstruct.com/gallery/tag/7045/5x8
<p>&nbsp</p>
<p>&nbsp</p>


## Sample screen shot of the tool running from a windows command prompt
<img src="https://github.com/kdcgarber/Font-editor/blob/main/images/FontEditorScreen.png" width7200 height600>

<p>&nbsp</p>

## This is the output of all the fonts - done with the 'm' choice in the tool.
<img src="https://github.com/kdcgarber/font-editor/blob/main/images/outimage.bmp" width7200 height600>

<p>&nbsp</p>
<p>&nbsp</p>

## Notes
<pre>
File In Use: data - 28256 - 32k.bin             Char Set: 17     Char Set Name: "My Model-1 Font"
Char in char set (1-128): 1
Pos: 0, 0     char: 2048  Bin:00000000  Hex:4000
+----------+  Hex     ¦ 'N' Jump 128 char forward                        'B' Jump 128 char backward
¦--¦¦¦¦¦¦  ¦  0e      ¦ left  arrow : move cursor left                   ' ' : spacebar toggles dot on and off
¦¦¦      ¦¦¦  11      ¦ right arrow : move cursor right                  'c' : remove a dot and move forward a position
¦        ¦¦¦  01      ¦ down  arrow : move cursor down                   'v' : add a dot and moves forward a position
¦  ¦¦¦¦  ¦¦¦  0d      ¦ up    arrow : move cursor up                     'q' : quit
¦¦¦  ¦¦  ¦¦¦  15      ¦ 'y' : send chars to a bmp file                   'm' : display bmp file via MSEdge
¦¦¦  ¦¦  ¦¦¦  15      ¦ 'n' : move to the next character                 's' : save the data<name>.bin file
¦  ¦¦¦¦¦¦  ¦  0e      ¦ 'b' : move to the previous character             'r' : read the data<name>.bin file
¦          ¦  00      ¦ '8':8 '6':16 '2':32 '4':64 '1':128 char line cnt 'z' : show line of the chars created
+----------+          ¦ 'd' : duplicate char set  chars:1-26 to 65-91    'ESC' : clear screen and refresh
                      ¦ '0' : blank current char                         'i' : inverse current char





</pre>
<pre>
Layout:
- The first line shows the current binary character file that has been loaded, then which character 
  set name is chosen.
- The next line shows the character set range of that is being edited.
- The next line is the x,y position of the bit being edited in the single character, then the character 
  number in the file and the binary and hex values of the character selected
- The next is a section that shows the current bits for the 5x8 character its hex value per row and 
  then the menu of options available.

- If you choose the letter <b>z</b>, a new line listing the character is display showing fist the default 
  8-character listing.
- Then if you choose the number '<b>8</b>' for 8 char '<b>6</b>' for 16 chars '<b>2'</b>:32 '<b>4</b>':64 '<b>1</b>':128 will show 
  a longer list of up to 129 characters created in a list.
- To show all of them clearly, often your CMD window needs setting to see a wider output, done often 
  by ctrl-scroll Mouse rolling.


Movement: <b>n</b> to move to next char and <b>b</b> to move back one char
          <b>N</b> to jump 128 chars forward to the next set of chars, <b>B</b> moves back 128 chars
          
Editing:  <b>arrow keys</b> to move around the character space.
          <b>Space</b> to toggle the current bit on and off 
          <b>v</b> sets a bit on and moves to the next bit 
          <b>c</b> removes the current bit and moves to the next bit <
          <b>d</b> duplicates the current set of 1-26 chars to the 65-91 set of chars in the current set 
          <b>0</b> blanks the current char of all bits 
          <b>i</b> inverts all the bits in the char to the reverse of the current char value 
          <b>ESC</b> key refreshes the screen 
Quit:     <b>q</b> to exit without saving 
Load/Save <b>s</b> saves the current data into a bin file and r rereads the char bin file 
View file <b>y</b> creates outimage.bmp file and m opens it for viewing allowing you to see all fonts available 

</pre>          

<p>&nbsp</p>
<p>&nbsp</p>


## A list of all of the fonts in the default "data - 28256 - 32k.bin"   character file

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
31 	GenDon 3-6A ianmav Font		        3968-4095



</pre>


# Usage

<p>&nbsp</p>
<p>&nbsp</p>
<p>&nbsp</p>





<p>&nbsp</p>
<p>&nbsp</p>
<p>&nbsp</p>
## License

<span style="font-size:4px;">
This project is licensed under the [MIT License](LICENSE) - Copyright 2025 Todd Garber<br><br>
[MIT License](./LICENSE)

Permission is hereby granted, free of charge, to any person obtaining a copy of this software and associated documentation files (the “Software”), to deal in the Software without restriction, including without limitation the rights to use, copy, modify, merge, publish, distribute, sublicense, and/or sell copies of the Software, and to permit persons to whom the Software is furnished to do so, subject to the following conditions:<br><br>
The above copyright notice and this permission notice shall be included in all copies or substantial portions of the Software.<br><br>
THE SOFTWARE IS PROVIDED “AS IS”, WITHOUT WARRANTY OF ANY KIND, EXPRESS OR IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY, FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL THE AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM, OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN THE SOFTWARE.<br>
</span>

#### https://opensource.org/license/mit
