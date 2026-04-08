#include "mp3_header.h"

void print_usage(void)
{
    printf("-----------------------------------------------------------------\n");
    printf("                 MP3 TAG READER - Usage Guide\n");
    printf("-----------------------------------------------------------------\n");

    printf("   ./a.out -v file_name.mp3                                  ; View MP3 Tag Information\n");
    printf("   ./a.out -e file_name.mp3                                  ; Edit MP3 Tag Information\n");
    printf("   ./a.out -h file_name.mp3                                  ; Help\n");


    printf("    Edit:\n");

    printf("   ./a.out edit -a file_name.mp3              ; Edit Mp3 Artist Tag\n");
    printf("   ./a.out edit -t file_name.mp3              ; Edit Mp3 Title Tag\n");
    printf("   ./a.out edit -A file_name.mp3              ; Edit Mp3 Album Tag\n");
    printf("   ./a.out edit -y file_name.mp3              ; Edit Mp3 Year Tag\n");
    printf("   ./a.out edit -C file_name.mp3              ; Edit Mp3 Content Tag\n");
    printf("   ./a.out edit -c file_name.mp3              ; Edit Mp3 Comments Tag\n");

    printf("-----------------------------------------------------------------\n");

}
int main(int argc, char *argv[])
{

	if (argc < 2)
	{
		print_usage();
		return 0;
	}
	if (strcmp(argv[1], "-h") == 0)
	{
		print_usage();
	}
	else if (strcmp(argv[1], "-v") == 0)
	{
		int len = strlen(argv[2]);
        if(!strcmp(argv[2]+(len - 4), ".mp3"))
		{
			view_mp3_tag(argv[2]);
		}
		else
			printf("error opening file");
	}
	else if (strcmp(argv[1], "-e") == 0)
	{
		int len = strlen(argv[4]);
		if(argc==5 && !strcmp(argv[4] +(len-4),".mp3"))
		{
		edit_mp3_tag(argv[2],argv[3],argv[4]);   
		}
		else
		print_usage();

	}

	else
	{
		printf("Error: Invalid option '%s'\n", argv[1]);
		print_usage();
	}

	return 0;
}

