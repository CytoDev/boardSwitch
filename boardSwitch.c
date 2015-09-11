/**                                                                            
 *                            CCCCCCCCCCCCCCC                                  
 *                            CCCCCCCCCCCCCCC                                  
 *                            CCCCCCCCCCCCCCC                                  
 *                            CCCCC          DDDDD                             
 *                            CCCCC          DDDDD                             
 *                            CCCCC          DDDDD                             
 *                            CCCCC          DDDDD                             
 *                            CCCCC          DDDDD                             
 *                                 DDDDDDDDDDDDDDD                             
 *                                 DDDDDDDDDDDDDDD                             
 *                                 DDDDDDDDDDDDDDD                             
 *                                                                             
 * boardSwitch.c                                                               
 * a C file that can be  used to control  the keyboard colors  of a steelseries
 * keyboard using the wearefractal/msi-keyboard node package.                  
 *                                                                             
 * Also, please don't run this on a non-linux system. It will most likely      
 * segfault all over you.                                                      
 *                                                                             
 * @author Roel Walraven <cytodev@gmail.com>                                   
 *                                                                             
 * This file is so basic,  I don't feel the  need to explain my code.  However,
 * I'm not a total dick,  so will try to  justify my code by compla...  err... 
 * Commenting on it.                                                           
 *                                                                             
 */

// first we include some pasta for our dish...
#include <unistd.h>
#include <stdio.h>
#include <stdlib.h>

// almost forgot to say, the whole wrapping at 80 thing is out the window now. We use modern editors 'round here.

// we have nine colors to play with. yay :D
const char *colorNames[9]; // did I just create some headroom, I'm never sure with C...

// this needs no explaining whatsoever, well perhaps why I used stdout instead of printf...
int help() {
	fprintf(stdout, "boardSwitch/switchBoard v0.1                                                    \n"); // queue ocd with 80...
	fprintf(stdout, "Usage: boardSwitch <color>                                                      \n");
	fprintf(stdout, "                                                                                \n");
	fprintf(stdout, "Commands:                                                                       \n");
	fprintf(stdout, "   -c       - prints a list of usable colors with their color code and names    \n");
	fprintf(stdout, "   -h       - prints this help text                                             \n");
	fprintf(stdout, "                                                                                \n");
	fprintf(stdout, "   --colors - prints a list of usable colors with their color code and names    \n");
	fprintf(stdout, "   --help   - prints this help text                                             \n");
	fprintf(stdout, "                                                                                \n");
}

int changeColor(int color) {
	colorNames[0] = "off";
	colorNames[1] = "red";
	colorNames[2] = "orange";
	colorNames[3] = "yellow";
	colorNames[4] = "green";
	colorNames[5] = "sky";
	colorNames[6] = "blue";
	colorNames[7] = "purple";
	colorNames[8] = "white"; 

	// ahh, interesting stuff. To get the size of a "string" we push it to snprintf. This returns our size_t (-1).
	size_t bufferSize = snprintf(NULL, 0, "node /usr/local/steelseries/keyboards/0%d_keyboard_%s.js", color, colorNames[color]) + 1;
	// I know every malloc needs a free, but who cares. You've got an awesome keyboard, so you can save a few petabytes of RAM. RIGHT!?
	char *command = malloc(bufferSize);
	// again, snprintf that motherducker. This time we have some space for it and all.
	snprintf(command, bufferSize, "node /usr/local/steelseries/keyboards/0%d_keyboard_%s.js", color, colorNames[color]);

	// we execute the command, and print a happy message. :)
	if(system(command) != -1) {
		fprintf(stdout, "changed keyboard LED to %s\n", colorNames[color]);
	} else {
		// or it failed, and we all die a little inside.
		fprintf(stderr, "could not change keyboard LED to %s\n", colorNames[color]);
	}
}

// this also needs zero explains.
int listColors() {
	fprintf(stdout, "boardSwitch/switchBoard v0.1                                                    \n");
	fprintf(stdout, "Usage: boardSwitch <color>                                                      \n");
	fprintf(stdout, "                                                                                \n");
	fprintf(stdout, "Usable colors:                                                                  \n");
	fprintf(stdout, "   off     0 or 00                                                              \n");
	fprintf(stdout, "   red     1 or 01                                                              \n");
	fprintf(stdout, "   orange  2 or 02                                                              \n");
	fprintf(stdout, "   yellow  3 or 03                                                              \n");
	fprintf(stdout, "   green   4 or 04                                                              \n");
	fprintf(stdout, "   sky     5 or 05                                                              \n");
	fprintf(stdout, "   blue    6 or 06                                                              \n");
	fprintf(stdout, "   purple  7 or 07                                                              \n");
	fprintf(stdout, "   white   8 or 08                                                              \n");
	fprintf(stdout, "                                                                                \n");
	fprintf(stdout, "Note:                                                                           \n");
	fprintf(stdout, "   Colors can also be chosen by their English names.                            \n");
	fprintf(stdout, "   For example, 8 can be typed in as \"boardSwitch white\".                     \n");
	fprintf(stdout, "                                                                                \n");
}

// If this needs explaining, I don't know man... I just... There's too much pudding man...
int main(int argc, char** argv) {
	// this one is interesting though, it could also be done differently.
	if(getuid()) {
		// Why stdout and not stderr you ask? Why not Zoidberg?
		fprintf(stdout, "You must be root to execute this program.\n");
		return EXIT_FAILURE;
	}

	if(argc != 2) {
		help(); // HELP I'M BEING RAN BY A NOOB!
	} else {
		// now if I could only switch on these things...
		     if(strcmp(argv[1], "off"   ) == 0 || strcmp(argv[1], "0") == 0 || strcmp(argv[1], "00") == 0) { changeColor(0); }
		else if(strcmp(argv[1], "red"   ) == 0 || strcmp(argv[1], "1") == 0 || strcmp(argv[1], "01") == 0) { changeColor(1); }
		else if(strcmp(argv[1], "orange") == 0 || strcmp(argv[1], "2") == 0 || strcmp(argv[1], "02") == 0) { changeColor(2); }
		else if(strcmp(argv[1], "yellow") == 0 || strcmp(argv[1], "3") == 0 || strcmp(argv[1], "03") == 0) { changeColor(3); }
		else if(strcmp(argv[1], "green" ) == 0 || strcmp(argv[1], "4") == 0 || strcmp(argv[1], "04") == 0) { changeColor(4); }
		else if(strcmp(argv[1], "sky"   ) == 0 || strcmp(argv[1], "5") == 0 || strcmp(argv[1], "05") == 0) { changeColor(5); }
		else if(strcmp(argv[1], "blue"  ) == 0 || strcmp(argv[1], "6") == 0 || strcmp(argv[1], "06") == 0) { changeColor(6); }
		else if(strcmp(argv[1], "purple") == 0 || strcmp(argv[1], "7") == 0 || strcmp(argv[1], "07") == 0) { changeColor(7); }
		else if(strcmp(argv[1], "white" ) == 0 || strcmp(argv[1], "8") == 0 || strcmp(argv[1], "08") == 0) { changeColor(8); }
		else if(strcmp(argv[1], "-h") == 0 || strcmp(argv[1], "--help"  ) == 0) { help();       }
		else if(strcmp(argv[1], "-c") == 0 || strcmp(argv[1], "--colors") == 0) { listColors(); }
		else {
			// you dun goofed user.
			fprintf(stdout, "%s is an invalid operand for this program. Type -h for help.\n", argv[1]);
		}
	}

	// WE DID IT!!! ~~YAY~~
	return EXIT_SUCCESS;
}

// queue pinatas flying around and keyboard discos.

// ps. don't like my humor? not my problem. Don't like my code? not my problem. Don't like the segfaults you're getting? Also not my problem. This has been tested and confirmed working on my machine. So yeah, no guarantees it does on yours. Oh and also, you've got a pretty big screen if you're reading this without scrolling. Good for you! :)