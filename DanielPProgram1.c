#include <stdio.h>
#include <ctype.h>
#include <string.h>

void encrypt(int[][9], char[10000], int);

int main(int argc, char *argv[3]){
	
	int key[9][9], keySize;
	char inTxt[10000];
	char outTxt[10000];
	int i, j, k=0, rem, extra;
	int inputSize=0;
	char c;
	char character;
	
	FILE *ifp, *ptr;
	
	ifp = fopen(argv[1], "r");
	ptr = fopen(argv[2], "r");
	
	if(ifp == NULL)
		printf("Sorry could not get key file!");
	if(ptr==NULL)
		printf("Cannot open plaintext file!");	
		
	else
		fscanf(ifp, "%d", &keySize);
	
	for(i=0;i<keySize;i++){								//initializes a 2d array
		for(j=0;j<keySize;j++){
			key[i][j] = 0;
		}
	}
	printf("\n");
	
	for(i=0;i<keySize;i++){								//puts the scanned values into the array
		for(j=0;j<keySize;j++){
			fscanf(ifp, "%d", &key[i][j]);
			printf("%d ", key[i][j]);
		}
		printf("\n");
	}	
	printf("\n");
	
	while(!feof(ptr)){									//scans the input file for characters.
		character = (char)getc(ptr);
		printf("%c", character);
		if(character >= 'A' && character <= 'Z')       //if the character is capital, then convert to lowercase
			character = tolower(character);
			
		if(character>= 'a' && character <='z')         //if the character is lowercase, then add it to the input array
			inTxt[inputSize++] = character;	
	}
	
	printf("\n");
	//puts(inTxt);
	
	rem = strlen(inTxt)%keySize;
	
	extra = strlen(inTxt);
	
		for(i=0;i<rem;i++){							//if the plaintext array is not evenly divisible by the key length, then pad the rest with 'x'.
			inTxt[extra+i] = 'x';
		}
	
	//printf("\n\n");
	fclose(ifp);
	fclose(ptr);
	
	
	encrypt(key,inTxt, keySize);						//uses the key and plaintext array to encrypt the file, along with the size of the array
	
	return 0;
}

//-------------------------------------------------//

void encrypt(int key[][9], char inTxt[], int size){

	int i=0;
	char outTxt[10000];
	int temp =0; 
	
	while(i < strlen(inTxt)){
		
		int j,k,l;
		
		for (j=0; j<size; j++) {
        	int temp = 0;
            for (k=0; k<size; k++){
                temp = (temp + key[j][k]*(inTxt[i+k] - 'a'))%26;			//add the calculated values of the position in the key times the 1d value of the plaintext array
            }																//we need to subtract the ASCII value of 'a' to get the correct ascii value for the plaintext calculation
        outTxt[j] = (char)('a' + temp);    									//it is then added back after calculations are finished.
        }
        
        i += size;															//the index of the plaintext is then increased by the size so there are no duplicates
	
		printf("%s", outTxt);
		if(i%80==0)															//every 80 characters, a new line is made
			printf("\n");
	}
}

//----------------------------------------------------//
