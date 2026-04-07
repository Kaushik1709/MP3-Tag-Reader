#include "mp3_header.h"
#include<stdio.h>
#include<string.h>
#include<stdlib.h>

static int convert(int num)
{
    unsigned char byte1 = (num & 0x000000FF);
    unsigned char byte2 = (num & 0x0000FF00) >> 8;
    unsigned char byte3 = (num & 0x00FF0000) >> 16;
    unsigned char byte4 = (num & 0xFF000000) >> 24;

    return 
    ((int)byte1 << 24) |
    ((int)byte2 << 16) |
    ((int)byte3 << 8)  |
    ((int)byte4);
}
const char *map_flag_to_tag(const char *flag)
{
    if (strcmp(flag, "-a") == 0) return "TPE1";
    if (strcmp(flag, "-t") == 0) return "TIT2";
    if (strcmp(flag, "-A") == 0) return "TALB";
    if (strcmp(flag, "-y") == 0) return "TYER";
    if (strcmp(flag, "-C") == 0) return "TCON";
    if (strcmp(flag, "-c") == 0) return "COMM";
    return NULL;
}
void edit_mp3_tag(const char *field_or_flag, const char *new_value, const char *filename)
{

    const char *field = field_or_flag;
    const char *mapped = map_flag_to_tag(field_or_flag);
    if (mapped)
        field = mapped;

    FILE *src = fopen(filename, "rb");
    FILE *tmp = fopen("temp.mp3", "wb");
    if (!src || !tmp)
    {
        perror("File open error");
        return;
    }

    
    char header[10];
    fread(header, 1, 10, src);   
    fwrite(header, 1, 10, tmp);

    int edited = 0;

    while (1)
    {
        char tag[5];
        if (fread(tag, 1, 4, src) != 4)
            break;
        tag[4] = '\0';

        int size_raw;
        if (fread(&size_raw, 4, 1, src) != 1)
            break;
        int frame_size = convert(size_raw);

        unsigned char flags[2];
        fread(flags, 1, 2, src);

        if (frame_size == 0)
            break;

        if (strcmp(tag, field) == 0 && !edited)
        {
            
            fwrite(tag, 1, 4, tmp);

            int new_frame_size = strlen(new_value) + 1;
            int new_size_byte = convert(new_frame_size);
            fwrite(&new_size_byte, 4, 1, tmp);

            unsigned char new_flags[2] = {0, 0};
            fwrite(new_flags, 1, 2, tmp);

        
            unsigned char encoding = 0;
            fwrite(&encoding, 1, 1, tmp);
            fwrite(new_value, strlen(new_value), 1, tmp);

        
            fseek(src, frame_size, SEEK_CUR);

            edited = 1;
        }
        else
        {
        
            fwrite(tag, 1, 4, tmp);
            fwrite(&size_raw, 4, 1, tmp);
            fwrite(flags, 1, 2, tmp);

            char *content = malloc(frame_size);
            if (!content)
            {
                perror("malloc");
                fclose(src);
                fclose(tmp);
                return;
            }
            fread(content, 1, frame_size, src);
            fwrite(content, 1, frame_size, tmp);
            free(content);
        }
    }


    int ch;
    while ((ch = fgetc(src)) != EOF)
            fputc(ch, tmp);

    fclose(src);
    fclose(tmp);

    remove(filename);
    rename("temp.mp3", filename);

    printf("Tag edited successfully!\n");
}

