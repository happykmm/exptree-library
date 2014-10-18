#ifndef _extstring_h

char*     trim(char *str);
char*   substr(const char *str, int len);
char* strClone(const char *str);
char* strMerge(const char *str1, const char *str2);
char* strMerge3(const char *str1, const char *str2, const char *str3);
char* strFilter(const char *str);

#endif