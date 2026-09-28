#include <stdio.h>
#include <string.h>
#include "decode.h"
#include "types.h"
#include "common.h"

Status read_and_validate_decode_args(char *argv[], DecodeInfo *decInfo)
{
    if (strstr(argv[2], ".bmp") == NULL)
    {
        printf("ERROR: Source image file must have a .bmp extension\n");
        return e_failure;
    }

    decInfo->stego_image_fname = argv[2];

    return e_success;
}

Status do_decoding(DecodeInfo *decInfo)
{
    printf("Decoding started...\n");

    if (open_decode_files(decInfo) == e_failure)
    {
        return e_failure;
    }

    if (decode_magic_string(decInfo) == e_failure)
    {
        return e_failure;
    }

    if (decode_secret_file_extn(decInfo) == e_failure)
    {
        return e_failure;
    }

    if (decode_secret_file_size(decInfo) == e_failure)
    {
        return e_failure;
    }

    if (open_output_file(decInfo) == e_failure)
    {
        return e_failure;
    }

    if (decode_secret_file_data(decInfo) == e_failure)
    {
        return e_failure;
    }

    return e_success;
}

Status open_decode_files(DecodeInfo *decInfo)
{
    decInfo->fptr_stego_image = fopen(decInfo->stego_image_fname, "r");

    if (decInfo->fptr_stego_image == NULL)
    {
        printf("ERROR: Unable to open stego image file\n");
        return e_failure;
    }

    fseek(decInfo->fptr_stego_image, 54, SEEK_SET);

    printf("Stego image opened successfully\n");

    return e_success;
}

Status decode_magic_string(DecodeInfo *decInfo)
{
    char magic_string[3];

    if (decode_data_from_image(magic_string, 2, decInfo->fptr_stego_image) == e_failure)
    {
        return e_failure;
    }

    magic_string[2] = '\0';

    if (strcmp(magic_string, MAGIC_STRING) != 0)
    {
        printf("ERROR: Magic string mismatch\n");
        return e_failure;
    }

    printf("Magic string decoded successfully\n");

    return e_success;
}


Status decode_data_from_image(char *data, int size, FILE *fptr_stego_image)
{
    char image_buffer[8];

    for (int i = 0; i < size; i++)
    {
        fread(image_buffer, 8, 1, fptr_stego_image);

        data[i] = decode_byte_from_lsb(image_buffer);
    }

    return e_success;
}

char decode_byte_from_lsb(char *image_buffer)
{
    char data = 0;

    for (int i = 0; i < 8; i++)
    {
        data = (data << 1) | (image_buffer[i] & 1);
    }

    return data;
}


Status decode_secret_file_extn(DecodeInfo *decInfo)
{
    if (decode_data_from_image(decInfo->extn_secret_file, 4, decInfo->fptr_stego_image) == e_failure)
    {
        return e_failure;
    }

    decInfo->extn_secret_file[4] = '\0';

    printf("Secret file extension decoded: %s\n", decInfo->extn_secret_file);

    return e_success;
}


Status decode_secret_file_size(DecodeInfo *decInfo)
{
    if (decode_data_from_image(
            (char *)&decInfo->size_secret_file,
            sizeof(long),
            decInfo->fptr_stego_image) == e_failure)
    {
        return e_failure;
    }

    printf("Secret file size decoded: %ld\n", decInfo->size_secret_file);

    return e_success;
}


Status open_output_file(DecodeInfo *decInfo)
{
    decInfo->output_fname = "decoded.txt";

    decInfo->fptr_output = fopen(decInfo->output_fname, "w");

    if (decInfo->fptr_output == NULL)
    {
        printf("ERROR: Unable to create output file\n");
        return e_failure;
    }

    printf("Output file opened successfully\n");

    return e_success;
}

Status decode_secret_file_data(DecodeInfo *decInfo)
{
    char ch;

    for (int i = 0; i < decInfo->size_secret_file; i++)
    {
        if (decode_data_from_image(&ch, 1, decInfo->fptr_stego_image) == e_failure)
        {
            return e_failure;
        }

        fwrite(&ch, 1, 1, decInfo->fptr_output);
    }

    printf("Secret file data decoded successfully\n");

    return e_success;
}