#include <stdlib.h>
#include <string.h>
#include <stdio.h>
#include "extstring.h"



/*
 * Function: trim
 * Usage: str = trim(str);
 * ----------------------
 * This function trims blanks on both sides of str.
 * Notice: the input will be destroyed!
 */
char *trim(char *str)
{
	if (str==NULL) return NULL;
    int i = 0;
    char *begin = str;
    while(str[i] != '\0') {
        if (str[i] != ' ')
            break;
        else
            begin++;
        i++;
    }
    for(i=strlen(str)-1; i>=0; i--) {
        if (str[i] != ' ') 
            break;
        else
			str[i] = '\0';
    }
    return begin;
}

/*
 * Function: substr
 * Usage: sub = substr(str,len);
 * ----------------------
 * This function returns a new string, which has the same 
 * beginning with the input string, and has a specific lenth.
 * str: The input string. It will not be destroyed.
 * len: The specific length.
 */
char *substr(const char *str, int len)
{
	if (str==NULL) return NULL;
	if (len < 0) return NULL; 
    if (len > strlen(str))
        len = strlen(str);
    char *sub = (char*)malloc(sizeof(char)*(len+1));
    int i;
    for (i=0; i<len; i++)
       sub[i] = str[i];
    sub[len] = 0;
    return sub;
}


char *strClone(const char *str)
{
    if (str==NULL) return NULL;
    char *chr = (char*)malloc(sizeof(char)*(strlen(str)+1));
    chr[0] = 0;
    strcat(chr,str);
    return chr;
}


char *strMerge(const char *str1, const char *str2)
{
	if (str1==NULL) return strClone(str2);
	if (str2==NULL) return strClone(str1);
    char *chr = (char*)malloc(strlen(str1)+strlen(str2)+1);
    chr[0] = 0;
    strcat(chr, str1);
	strcat(chr, " ");
	strcat(chr, str2);
    return trim(chr);
}


char *strMerge3(const char *str1, const char *str2, const char *str3)
{
    return strMerge(strMerge(str1,str2),str3);
}


char* strFilter(const char *str)
{
	static const char *rule = "0123456789.+-*/()= ";
    int len = strlen(rule);
	if (str==NULL) return NULL;
	char *chr = (char*)malloc(strlen(str)+1);
    int i, j, flag;
	j=0;
	while (*str) {
		flag = 0;
        for (i=0; i<len; i++)
			if (*str == rule[i]) {
				flag = 1;
				break;
			}
		if (flag) {
			chr[j] = *str;
			j++;
		}
		str++;
	}
	chr[j] = 0;
	return chr;
}

