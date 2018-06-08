
#include <stdio.h>
#include <errno.h>

int main(int argc, char *argv[])
{
	if (argc != 2)
	{
		fprintf(stderr, "useage: %s filename\n", argv[0]);
		return -1;
	}

	char savefilename[1024];
	snprintf(savefilename, 1024, "%s_out.txt", argv[1]);
	FILE *fin = fopen(argv[1], "rb");
	if (!fin)
	{
		fprintf(stderr, "cannot open input file %s, errno: %d\n", argv[1], errno);
		return -1;
	}
	FILE *fout = fopen(savefilename, "w");
	if (!fout)
	{
		fprintf(stderr, "cannot open output file %s, errno: %d\n", savefilename, errno);
		return -1;
	}
	fseek(fin, 0x100, SEEK_SET);

	unsigned int innumber;

	for (int i = 0; i < 512; ++i)
	{
		fread(&innumber, 4, 1, fin);
		fprintf(fout, "%d.000 %u\n", i, innumber);
	}

	fclose(fin);
	fclose(fout);

	return 0;
}
