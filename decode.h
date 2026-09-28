#ifndef DECODE_H
#define DECODE_H
#include <stdio.h>

#include "types.h"



typedef struct _DecodeInfo
{
    char *stego_image_fname;
    FILE *fptr_stego_image;

    char extn_secret_file[5];
    long size_secret_file;

    char *output_fname;
    FILE *fptr_output;

} DecodeInfo;

Status read_and_validate_decode_args(char *argv[], DecodeInfo *decInfo);

Status do_decoding(DecodeInfo *decInfo);

Status open_decode_files(DecodeInfo *decInfo);

Status decode_magic_string(DecodeInfo *decInfo);

Status decode_data_from_image(char *data, int size, FILE *fptr_stego_image);

char decode_byte_from_lsb(char *image_buffer);

Status decode_secret_file_extn(DecodeInfo *decInfo);

Status decode_secret_file_size(DecodeInfo *decInfo);

Status open_output_file(DecodeInfo *decInfo);

Status decode_secret_file_data(DecodeInfo *decInfo);

#endif