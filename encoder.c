#include <stdio.h>
#include <stdlib.h>
#include <string.h>

struct Words {
	char* word;
	float complexity;
};

char* readLine (FILE* file) {
    char text[512];
    size_t len;

    if (!fgets(text, sizeof text, file)) return NULL;
    len = strlen(text);

    while (len && text[len-1] == '\n') text[--len] = '\0';

    return strdup(text);
}

int isNumber (char* word) {                                                       //verific daca pe linie am numar
	char* pEnd;
	int isNumber = 1, i;
	if (word[0] == '-') {
		for (i = 1; i < strlen(word); i++) {
			if (!(word[i] > 48 && word[i] < 58)) {                    //intervalul (48-58) contine codurile ascii
				isNumber = 0;                                     //ale numerelor 1-9
			}	
		}
	} else {
		for (i = 0; i < strlen(word); i++) {
			if (!(word[i] > 48 && word[i] < 58)) {
				isNumber = 0;
			}	
		}
	}
	if (isNumber == 1) {
		if (strtol(word, &pEnd, 10) == 0) {
			return 0;	
		} else {
			return 1;	
		}
	} else {
		return 0;
	}
}


int isWord (char* word) {                                                   //verfic daca pe linie am cuvant
	int i, isWord;
	
	if (isNumber(word) == 0) {                                          //daca nu e numar
		if (strlen(word) == 1) {                                    //daca am un singur caracter pe linie nu e cuvant
			return 0;	
		} else {
			for (i = 0; i < strlen(word); i++) {
				if ((word[i] > 32 && word[i] <= 48) || (word[i] >= 58 && word[i] < 127)) {
					isWord = 1;			
				}
			}                                               
		}
	} else {
		isWord = 0;	
	}
	return isWord;
}

int isChar (char* word) {                                                                    //verific daca pe linie am cuvant
	int isChar = 0;
	if (strlen(word) == 1) {                                                             //daca respecta conditia
		if ((word[0] > 32 && word[0] <= 48) || (word[0] >= 58 && word[0] < 127)) {   //conditie sa nu fie cifra
			isChar = 1;		
		}	
	}
	return isChar;                                                                       
}


int divisor (int size) {                              
	int i;
	for (i = size / 2; i >= 2; i--) {
		if (size % i == 0 && size != i) {
			return i;
		}
	}
	return 1;
}

int containsDigit (char* word) {                     
	int i;
	for (i = 0; i < strlen (word); i++) {
		if (word[i] >= 48 && word[i] < 58) {
			return 1;
		}	
	}
	return 0;
}

char* strrev (char* word) {                           
	int i;
	char aux;
	char* copy = (char*) malloc (strlen(word) * sizeof(char));
	strcpy(copy, word);
	for (i = 0; i < strlen(copy) / 2; i++) {
		aux = copy[i];
		copy[i] = copy[strlen(copy) - i - 1];
		copy[strlen(copy) - i - 1] = aux;
	}
	return copy;
}

char* encodeWord (int divisor, char* word) {                        
	char* firstPartOfWOrd;
	char* lastPartOfWord;
	char* wordEncoded;

	firstPartOfWOrd = (char*) malloc (divisor * sizeof(char)); 
	lastPartOfWord = (char*) malloc ((strlen(word) - divisor) * sizeof(char));
	wordEncoded = (char*) malloc (strlen(word) * sizeof(char));

	strncpy(firstPartOfWOrd, word, divisor);    
	firstPartOfWOrd[divisor] = '\0';
	strncpy(lastPartOfWord, word + divisor, strlen(word) - divisor);
	lastPartOfWord[strlen(word) - divisor] = '\0';
	if (containsDigit(word) == 1) {
		strcpy(wordEncoded, strrev(lastPartOfWord));
		strcat(wordEncoded, firstPartOfWOrd);
		return wordEncoded;
	} else {
		strcpy(wordEncoded, lastPartOfWord);
		strcat(wordEncoded, firstPartOfWOrd);
		return wordEncoded;	
	}  		
}

char characterMaxAppeareances (char* word) {                            
	int vector[512];
	int i, minimumNumber;
	char character;

	for (i = 0; i < 512; i++) {
		vector[i] = 0;	
	}
	
	for (i = 0; i < strlen(word); i++) {
		vector[(unsigned char)word[i]]++;
	}
	minimumNumber = vector[(unsigned char)word[0]];
	character = word[0];
	for (i = 1; i < strlen(word); i++) {
		if (minimumNumber < vector[(unsigned char)word[i]]) {
			minimumNumber = vector[(unsigned char)word[i]];
			character = word[i];		
		}
	}
	return character;
}

char characterMinAppeareances (char* word) {
	int vector[512];
	int i, minimumNumber;
	char character;

	for (i = 0; i < 512; i++) {
		vector[i] = 0;	
	}
	
	for (i = 0; i < strlen(word); i++) {
		vector[(unsigned char)word[i]]++;
	}
	minimumNumber = vector[(unsigned char)word[0]];
	character = word[0];
	for (i = 1; i < strlen(word); i++) {
		if (minimumNumber > vector[(unsigned char)word[i]]) {
			minimumNumber = vector[(unsigned char)word[i]];
			character = word[i];		
		}
	}
	return character;
}

char findMaximumDigit(char* word) {
	int i;
	char max = word[0];
	for (i = 1; i < strlen(word); i++) {
		if (word[i] > max) {
			max = word[i];		
		}	
	}
	return max;
}

char findMinimumDigit(char* word) {
	int i;
	char min = word[0];
	for (i = 1; i < strlen(word); i++) {
		if (word[i] < min) {
			min = word[i];		
		}	
	}
	return min;
}

int* maximumPositions(char* word) {
	int* vector = (int*) malloc (strlen(word) * sizeof(int));
	int i, pos = 0;
	for (i = 0; i < strlen(word); i++) {
		if (findMaximumDigit(word) == word[i]) {
			vector[pos] = i;
			pos++;
		}	
	}
	return vector;
}

int* minimumPositions(char* word) {
	int* vector = (int*) malloc (strlen(word) * sizeof(int));
	int i, pos = 0;
	for (i = 0; i < strlen(word); i++) {
		if (findMinimumDigit(word) == word[i]) {
			vector[pos] = i;
			pos++;
		}	
	}
	return vector;
}

char* cycleMinMaxWord (int position, char* word) {
	char* firstPartOfWOrd;
	char* lastPartOfWord;
	char* wordEncoded;

	firstPartOfWOrd = (char*) malloc ((position) * sizeof(char));
	lastPartOfWord = (char*) malloc ((strlen(word) - position ) * sizeof(char));
	wordEncoded = (char*) malloc (strlen(word) * sizeof(char));

	strncpy(firstPartOfWOrd, word, position);
	firstPartOfWOrd[position] = '\0';
	strncpy(lastPartOfWord, word + position , strlen(word) - position);
	lastPartOfWord[strlen(word) - position] = '\0';

	strcpy(wordEncoded, lastPartOfWord);
	strcat(wordEncoded, firstPartOfWOrd);
	
	return wordEncoded;
}

int main () {
	int i, numberOfLines = 0, numberOfWords = 0, numberOfChars = 0, numberOfNumbers = 0, wordLength, numberOfMinElements = 0, numberOfMaxElements = 0, j;
	int localDivisor;
	int forAllocateString = 1;
	
	long int minChar, maxChar;

	int* minPositions;
	int* maxPositions;

	char minimumAppereancesChar, maximumAppereancesChar, currentChar;

	char** wordsRead = (char**) malloc (forAllocateString * sizeof(char*));
	char** minValues = (char**) malloc (sizeof(char*));
	char** maxValues = (char**) malloc (sizeof(char*));

	char* element  = (char*) malloc (100 * sizeof(char)); 
	char* wordEncoded;
	char* encodedMessage = (char*) malloc (5000*sizeof(char));
	char* threeCharsConcatenated;
	char* absoluteValue;
	char* pEnd;
	char* minCharValue;
	char* maxCharValue;

	while (1) {
		char* s = readLine(stdin);
		if (strcmp(s, "END") == 0) {
			numberOfLines--;
			break;
		} else {
			wordsRead[numberOfLines] = s;
			numberOfLines++;
			forAllocateString++;
			wordsRead = realloc(wordsRead, forAllocateString * sizeof(char*));
		}
	}
	
	for (i = 0; i < numberOfLines; i++) {
		if (isWord(wordsRead[i]) == 1) {
			//printf("Cuvant %s\n", wordsRead[i]);
			numberOfWords++;
			wordLength = strlen(wordsRead[i]);
			localDivisor = divisor(wordLength);
			wordEncoded = (char*) malloc (wordLength * sizeof(char));
			wordEncoded = encodeWord(localDivisor, wordsRead[i]);
			strcat(encodedMessage, wordEncoded);
		}
		if (isChar(wordsRead[i]) == 1) {
			//printf("Caracter %s\n", wordsRead[i]);
			numberOfChars++;
			if (strlen(encodedMessage) == 0) {
				strcat(encodedMessage, wordsRead[i]); 
			} else {
				minimumAppereancesChar = characterMinAppeareances(encodedMessage); 
				maximumAppereancesChar = characterMaxAppeareances(encodedMessage);
			
				currentChar = wordsRead[i][0];

				threeCharsConcatenated = (char*) malloc (3 * sizeof(char));
				sprintf(threeCharsConcatenated, "%c%c%c", maximumAppereancesChar, currentChar, minimumAppereancesChar);

				strcat(encodedMessage, threeCharsConcatenated);
			}
		}
		if (isNumber(wordsRead[i]) == 1) {
			//printf("Numar %s\n", wordsRead[i]);
			numberOfNumbers++;
			if (wordsRead[i][0] == '-') {
				absoluteValue = (char*) malloc ((strlen(wordsRead[i]) - 1) * sizeof(char));
				char* localCopy = (char*) malloc (strlen(wordsRead[i]) * sizeof(char));
				strcpy(localCopy, wordsRead[i]);
				strncpy(absoluteValue, localCopy + 1, strlen(wordsRead[i]) - 1);
				minPositions = (int*) malloc (strlen(absoluteValue) * sizeof(int));
				minPositions = minimumPositions(absoluteValue);	
				for (j = 0; j < sizeof(minPositions) / sizeof(minPositions[0]); j++) {
					element = cycleMinMaxWord (minPositions[j], absoluteValue);
					minValues[numberOfMinElements] = element;
					numberOfMinElements++;
				}
				minChar = strtol(minValues[0], &pEnd, 10);
				for (j = 1; j < numberOfMinElements; j++) {
					if (strtol(minValues[j], &pEnd, 10) < minChar) {
						minChar = strtol(minValues[j], &pEnd, 10);			
					}		
				}
				minCharValue = (char*) malloc (strlen(absoluteValue) * sizeof(char));
				sprintf (minCharValue, "%ld", minChar);
				strcat(encodedMessage, minCharValue);
			} else {
				absoluteValue = (char*) malloc (strlen(wordsRead[i]) * sizeof(char));
				char* localCopy = (char*) malloc (strlen(wordsRead[i]) * sizeof(char));
				strcpy(localCopy, wordsRead[i]);
				strncpy(absoluteValue, localCopy, strlen(wordsRead[i]));
				maxPositions = (int*) malloc (strlen(absoluteValue) * sizeof(int));
				maxPositions = maximumPositions(absoluteValue);
				for (j = 0; j < sizeof(maxPositions) / sizeof(maxPositions[0]); j++) {
					element = cycleMinMaxWord (maxPositions[j], absoluteValue);
					maxValues[numberOfMaxElements] = element;
					numberOfMaxElements++;		
				}
				maxChar = strtol(maxValues[0], &pEnd, 10);
				for (j = 1; j < numberOfMaxElements; j++) {
					if (strtol(maxValues[j], &pEnd, 10) > maxChar) {
						maxChar = strtol(maxValues[j], &pEnd, 10);			
					}		
				}
				maxCharValue = (char*) malloc (strlen(absoluteValue) * sizeof(char));
				sprintf (maxCharValue, "%ld", maxChar);
				strcat(encodedMessage, maxCharValue);
			}
		}	
	}
	/*--------------------------------Task 3----------------------------------*/
	int n = strtol(wordsRead[numberOfLines], &pEnd, 10);
	struct Words words[n];
	struct Words aux;
	int size = strlen(encodedMessage) / n;
	int sizeLastWord = size;
	int position = 0;
	int localComplexity = 0;
	
	if (strlen(encodedMessage) % n != 0) {
		sizeLastWord = strlen(encodedMessage) - (n - 1) * size;
	
	}
	for (i = 0; i < n - 1; i++) {
		words[i].word = (char*) malloc (sizeof(char) * size);
		strncpy(words[i].word, encodedMessage + position, size);
		position += size;
		for (j = 0; j < strlen (words[i].word); j++) {
			localComplexity += words[i].word[j];
		}
		words[i].complexity = localComplexity / size;
		localComplexity = 0;
	}
	
	words[n - 1].word = (char*) malloc (sizeof(char) * sizeLastWord);
	strncpy(words[n - 1].word, encodedMessage + position, sizeLastWord);
	localComplexity = 0;
	for (j = 0; j < strlen (words[n - 1].word); j++) {
		localComplexity += words[n - 1].word[j];
	}
	words[n - 1].complexity = localComplexity / sizeLastWord;
	
	//sortare dupa complexitate
	
	for (i = 0; i < n - 1; i++) {
		for (j = i + 1; j < n; j++) {
			if (words[i].complexity < words[j].complexity) {
				aux = words[i];
				words[i] = words[j];
				words[j] = aux; 
			}
		}
	}

	char* finalString = (char*) malloc (strlen(encodedMessage) * sizeof(char));
	char* aux1, *aux2;
	for (i = 0; i < n / 2; i++) {
		aux1 = (char*) malloc (strlen(words[i].word) * sizeof(char));
		aux2 = (char*) malloc (strlen(words[n - i - 1].word) * sizeof(char));
		strcpy(aux1, words[i].word);
		strcpy(aux2, words[n - i - 1].word);
		strcat(aux1, aux2);
		strcat (finalString, aux1);
		aux1 = NULL;
		aux2 = NULL;
		//printf ("%s %f\n", words[i].word, words[i].complexity);
	}
	if (n % 2 != 0) {
		strcat(finalString, words[n / 2].word);	
	}
	/*for (i = 0; i < n; i++) {
		printf ("%s %f\n", words[i].word, words[i].complexity);
	}*/ 	
	/*------------------------------------------------------------------------*/
	printf("%d %d %d\n", numberOfWords, numberOfChars, numberOfNumbers);
	printf("%s\n", encodedMessage);
	printf("%s\n", finalString);
	//for(i=0; i < numberOfWords; i++) {
	//	printf("%s\n ", wordsRead[i]);
	//}

	free(wordsRead);
	free(element);

	return 0;
}
