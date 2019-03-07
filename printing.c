/*Cory Milsap
 *Program allows user to enter string and calculate the number of dots, spaces, and newlines. Program also formats the string to left, right, or center justified.
 *
 * */
#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <ctype.h>

void printLeft(char str[], int width); //allows for left alignment
void printRight(char str[], int width); // prints string right justified
void printCenter(char str[], int width);//prints string center justified
void printDigits(int width);//prints line of digits
int dotsPrinted(char str[]); //calculate number of dots printed

int main()
{
    char formChar;
    char userStr[500];
    char tempStr[50];
    int lineWidth;

    printf("Enter a formatting code: ");
    scanf("%c%d", &formChar, &lineWidth);
    printf("Enter a string: \n");
    scanf("%s ", userStr);
    strcat(userStr, " ");
    while (!feof(stdin)) {
        scanf("%s ", tempStr);
        strcat(userStr, tempStr);
        strcat(userStr, " ");
    }
    strcat(userStr, "\0");

    printDigits(lineWidth);
        
    if (formChar == 'L' || formChar == 'l') printLeft(userStr, lineWidth);
    if (formChar == 'R' || formChar == 'r') printRight(userStr, lineWidth);
    if (formChar == 'C' || formChar == 'c') printCenter(userStr, lineWidth);

    return 0;
}

void printDigits(int width)
{
    int lastDigit = 0;
    for (int i = 1; i <= width; i++) {
        lastDigit = i % 10;
        printf("%d", lastDigit);
    }
    printf("\n");
}

void printLeft(char str[], int width)
{
    int i = 0;
    int currLineCount = 0;
    int nextWordCount = 0;
    int j = 0;
    int spaces = 0;
    int newLines = 0;

    while (str[j] != ' ') {
        printf("%c", str[j]);
        if (isspace(str[j])) spaces++;
        j++;
        currLineCount++;
    }

    for (i = j; i < strlen(str)-1; i++) {
        if (isspace(str[i])) {
            do {
                nextWordCount++;
            } while (!isspace(str[i+nextWordCount]));
            if ((currLineCount + nextWordCount) <= width) {
                for (int k = 0; k < nextWordCount; k++) {
                    printf("%c",str[i]);
                    if (isspace(str[i])) spaces++;
                    i++;
                    currLineCount++;
                }
                i--;
                nextWordCount = 0;
            }
            else {
                printf("\n");
                newLines++;
                currLineCount = 0;
                i++;
                for (int k = 0; k < nextWordCount-1; k++) {
                    printf("%c", str[i]);
                    if (isspace(str[i])) spaces++;
                    i++;
                    currLineCount++;
                }
                i--;
                i--;
                nextWordCount = 0;
            }
        }

    }
    printf("\n");
    printDigits(width);    
    printf("\n");
    printf("Dots printed: %d\n", dotsPrinted(str));
    printf("Spaces printed: %d\n", spaces);
    printf("Newlines printed: %d\n", newLines+1);

}

void printRight(char str[], int width)
{
    int i = 0;
    int j = 0;
    int lines = 0;
    int newLines = 0;
    int spaces = 0;
    char tempStr[50];
    strcpy(tempStr, "");
    int len = 0;

    for (i = 0; i < strlen(str); i++) {
        if(!isspace(str[i])) {
            len = strlen(tempStr);
            tempStr[len] = str[i];
            tempStr[len+1] = '\0';
            lines++;
        }
        else {
            j = 1;
            while (!isspace(str[i+j])) {
                j++;
            }
            if (lines + j > width) {
                for (int k = 0; k < width-lines;k++) {
                    printf(" ");
                    spaces++;
                }
                printf("%s\n", tempStr);
                lines = 0;
                newLines++;
                strcpy(tempStr,"");
            }
            else {
                lines++;
                spaces++;
                strcat(tempStr, " ");
            }
        }
    }  
    printDigits(width);    
    printf("\n");
    printf("Dots printed: %d\n", dotsPrinted(str));
    printf("Spaces printed: %d\n", spaces);
    printf("Newlines printed: %d\n", newLines);
}

void printCenter(char str[], int width)
{
    int i = 0;
    int j = 0;
    int lines = 0;
    int newLines = 0;
    int spaces = 0;
    char tempStr[50];
    strcpy(tempStr, "");
    int len = 0;

    for (i = 0; i < strlen(str); i++) {
        if(!isspace(str[i])) {
            len = strlen(tempStr);
            tempStr[len] = str[i];
            tempStr[len+1] = '\0';
            lines++;
        }
        else {
            j = 1;
            while (!isspace(str[i+j])) {
                j++;
            }
            if ((lines + j) > width) {
                for (int k = 0; k < (width-lines)/2;k++) {
                    printf(" ");
                    spaces++;
                }
                printf("%s\n", tempStr);
                lines = 0;
                newLines++;
                strcpy(tempStr,"");
            }
            else {
                lines++;
                spaces++;
                strcat(tempStr, " ");
            }
        }
    }
    printDigits(width);    
    printf("\n");
    printf("Dots printed: %d\n", dotsPrinted(str));
    printf("Spaces printed: %d\n", spaces);
    printf("Newlines printed: %d\n", newLines);
}

int dotsPrinted(char str[])
{
    // the number of dots for 'A' (at 0) through 'Z' (at 25)
    int dotsUpper[26]={
    16, 19, 13, 18, 18, 14, 16,
    17, 11, 12, 14, 11, 21, 19,
    16, 15, 18, 18, 15, 11, 15,
    13, 20, 11, 11, 15
    };
    // the number of dots for 'a' (at 0) through 'z' (at 25)
    int dotsLower[26]={
    12, 14,  9, 14, 14, 12, 18,
    14,  9, 10, 12, 10, 16, 12,
    12, 14, 14,  8, 13, 10, 12,
     9, 14,  9, 16, 13
    };
    int sum = 0;

    for (int i = 0; i < strlen(str); i++){
        if(isupper(str[i])) {
            sum+= dotsUpper[str[i]-65];
        }
        else if (islower(str[i])) {
            sum += dotsLower[str[i]-97];
        }
    }
    return sum;
}
