
// textfile.cpp
//
// simple reading and writing for text files
//
// www.lighthouse3d.com
//
// You may use these functions freely.
// they are provided as is, and no warranties, either implicit,
// or explicit are given
//////////////////////////////////////////////////////////////////////

#include "stdafx.h"
#include <cstdio>
#include <cstdlib>
#include <cstring>


char *textFileRead(const char *fn) 
{
	FILE *fp;
	char *content = NULL;

	int count=0;

	if (fn != NULL) 
	{
		fopen_s(&fp, fn,"rt");

		if (fp != NULL) 
		{
			fseek(fp, 0, SEEK_END);
			count = ftell(fp);
			rewind(fp);

			if (count > 0) 
			{
				content = (char *)malloc(sizeof(char) * (count+1));
				count = static_cast<int>(fread(content,sizeof(char),count,fp));
				content[count] = '\0';
			}
			fclose(fp);
		}
	}
	return content;
}

int textFileWrite(char *fn, char *s) 
{
	FILE *fp;
	int status = 0;

	if (fn != NULL) 
	{
		fopen_s(&fp ,fn,"w");

		if (fp != NULL) 
		{
			if (fwrite(s,sizeof(char),strlen(s),fp) == strlen(s))
				status = 1;
			fclose(fp);
		}
	}
	return(status);
}







