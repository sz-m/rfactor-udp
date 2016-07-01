#include "../include/Debug.h"
#include <cstdlib>
#include <ctime>

Debug::Debug(char* fName)
{
	fileName = fName;
	file = fopen(fileName, "a");
	if (file == NULL)
		exit(3);
	

	time_t t = time(0);
	struct tm *now = localtime(&t);

	fprintf(file, "+------------------------------+\n");
	fprintf(file, "+ %s", asctime(now));
	fprintf(file, "+------------------------------+\n\n");

	fclose(file);
}

void Debug::write(char* msg)
{
	file = fopen(fileName, "a");
	fprintf(file, "%s\n", msg);
	fclose(file);
}

