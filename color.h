#ifndef COLOR_H
#define COLOR_H

// Reset Colors
#define RESET       "\033[0m"
#define HOME        "\033[r\033[J\n"

// Status
#define BOLD        "\033[1m"
#define DIM         "\033[2m"
#define UNDERLINED  "\033[4m"
#define BLINK       "\033[5m"
#define INVERTED    "\033[7m"
#define HIDDEN      "\033[8m"

// Colors
#define BLACK       "\033[30m"
#define RED         "\033[31m"
#define GREEN       "\033[32m"
#define YELLOW      "\033[33m"
#define BLUE        "\033[34m"
#define MAGENTA     "\033[35m"
#define CYAN        "\033[36m"
#define WHITE       "\033[37m"
#define COL_DEFAULT "\033[39m"

// Light Colors
#define L_BLACK     "\033[90m"
#define L_RED       "\033[91m"
#define L_GREEN     "\033[92m"
#define L_YELLOW    "\033[93m"
#define L_BLUE      "\033[94m"
#define L_MAGENTA 	"\033[95m"
#define L_CYAN    	"\033[96m"
#define L_WHITE   	"\033[97m"

// Background colors
#define B_BLACK   	"\033[40m"
#define B_RED     	"\033[41m"
#define B_GREEN   	"\033[42m"
#define B_YELLOW  	"\033[43m"
#define B_BLUE    	"\033[44m"
#define B_MAGENTA 	"\033[45m"
#define B_CYAN    	"\033[46m"
#define B_WHITE   	"\033[47m"
#define B_DEFAULT	"\033[49m"

// Light Background colors
#define BL_GREY     "\033[100m"
#define BL_RED     	"\033[101m"
#define BL_GREEN   	"\033[102m"
#define BL_YELLOW  	"\033[103m"
#define BL_BLUE    	"\033[104m"
#define BL_MAGENTA 	"\033[105m"
#define BL_CYAN    	"\033[106m"
#define BL_WHITE   	"\033[107m"

#endif // COLOR_H
