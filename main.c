#include <stdio.h>
#include "encode.h"
#include "types.h"
#include <string.h>
#include "decode.h"

int main(int argc, char *argv[])
{
    EncodeInfo encInfo;
    OperationType Operation;

    Status status;
    DecodeInfo decInfo;
    Operation = check_operation_type(argv);
    if (Operation == e_encode)
    {
        printf("Encoding is selected\n\n");

        status = read_and_validate_encode_args(argv, &encInfo);

        if (status == e_success)
        {
            status = do_encoding(&encInfo);

            if (status == e_success)
            {
                printf("Encoding completed successfully\n");
            }
            else
            {
                printf("Encoding failed\n");
            }
        }
        else
        {
            printf("Argument validation failed\n");
        }
    } 
    else if (Operation == e_decode)
    {
        printf("Decoding is selected\n\n");

        status = read_and_validate_decode_args(argv, &decInfo);

        if (status == e_success)
        {
            printf("Decode arguments validated successfully\n");

            status = do_decoding(&decInfo);

            if (status == e_success)
            {
                printf("Decoding completed successfully\n");
            }
            else
            {
                printf("Decoding failed\n");
            }
        }
        else
        {
            printf("Argument validation failed\n");
        }
    }

    
    
}


OperationType check_operation_type(char *argv[]) {

    if (strcmp(argv[1], "-e") == 0) {
        return e_encode;
    } else if (strcmp(argv[1], "-d") == 0) {
        return e_decode;
    } else {
        return e_unsupported;
    }
}





