/* See LICENSE file for copyright and license details. */
#include <stdarg.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "util.h"

static const char* logfile = "/home/hazurl/.dwm.log";

void *
ecalloc(size_t nmemb, size_t size)
{
	void *p;

	if (!(p = calloc(nmemb, size)))
		die("calloc:");
	return p;
}

void
die(const char *fmt, ...) {
	va_list ap;

	va_start(ap, fmt);
	vfprintf(stderr, fmt, ap);
	va_end(ap);

	if (fmt[0] && fmt[strlen(fmt)-1] == ':') {
		fputc(' ', stderr);
		perror(NULL);
	} else {
		fputc('\n', stderr);
	}

	logtofile(fmt, ap);

	exit(1);
}

void
logtofile(const char *fmt, ...)
{
	FILE *fp;
	va_list ap;
	char *buf;
	int len;

	va_start(ap, fmt);
	len = vsnprintf(NULL, 0, fmt, ap);
	va_end(ap);
	if (len < 0)
		return;
	buf = malloc(len + 1);
	if (!buf)
		return;
	va_start(ap, fmt);
	vsnprintf(buf, len + 1, fmt, ap);
	va_end(ap);
	fp = fopen(logfile, "a");
	if (fp)
	{
		fprintf(fp, "%s\n", buf);
		fclose(fp);
	}
	free(buf);
}

char *
arraytostr(char const **array)
{
	int totalsize = 0;
	int i = 0;
	while (array[i] != NULL)
	{
		totalsize += strlen(array[i]) + 1;
		i++;
	}

	char *str = malloc(sizeof(char) * totalsize + 1);
	memset(str, 0, totalsize + 1);

	i = 0;
	while (array[i] != NULL)
	{
		strcat(str, array[i]);
		strcat(str, " ");
		i++;
	}

	return str;
}