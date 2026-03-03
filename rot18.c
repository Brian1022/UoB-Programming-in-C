#include "rot18.h"
#include <ctype.h>
#define ROT13 ('N'-'A')
#define ROT5 ('5'-'0')

void rot(char str[]){
    // your code here

	int i, len = strlen(str);

	for(i = 0; i < len; i++){
		// Check if the character is alphabet
		if(isalpha(str[i])){
			// Apply ROT13
			if((str[i] >= 'a' && str[i] <= 'm') || (str[i] >= 'A' && str[i] <= 'M')){
				str[i] = str[i] + ROT13;
			}
			else if((str[i] >= 'n' && str[i] <= 'z') || (str[i] >= 'N' && str[i] <= 'Z')){
				str[i] = str[i] - ROT13;
			}
		}
		// Check if the character is digit
		else if(isdigit(str[i])){
			// Apply ROT5
			if(str[i] >= '0' && str[i] <= '4'){
				str[i] = str[i] + ROT5;
			}
			else if(str[i] >= '5' && str[i] <= '9'){
				str[i] = str[i] - ROT5;
			}
		}
		// Make sure the character that is not alphabet or digit be unaffected
		else{
			str[i] = str[i];
		}
	}
}

// any other functions here

void your_tests(void){
    // your tests here

	char str[100];
	strcpy(str, "Aa Mm Nn Zz !?~");
	rot(str);
	assert(strcmp(str, "Nn Zz Aa Mm !?~") == 0);
	rot(str);
	assert(strcmp(str, "Aa Mm Nn Zz !?~") == 0);
	strcpy(str, "-0.123456789");
	rot(str);
	assert(strcmp(str, "-5.678901234") == 0);
}

