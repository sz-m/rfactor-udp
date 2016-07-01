#pragma once
#include <cstdio>

class Debug
{
private:
	FILE *file;
	char* fileName;

public:
	Debug(char *fName);

	void write(char *msg);
};

