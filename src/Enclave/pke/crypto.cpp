#include "crypto.h"
#include "Enclave_t.h" // for debug
#include <sgx_trts.h> // for debug

int encrypt(void *pkey, const unsigned char *inData, size_t in_size, unsigned char *outData, size_t *out_size)
{
    sgx_status_t status = sgx_rsa_pub_encrypt_sha256(
        pkey, 
        outData, 
        out_size, 
        inData, 
        in_size
    ); 

// for debug
    if (status == SGX_SUCCESS) {
        return 0;
    } else if (status == SGX_ERROR_INVALID_PARAMETER) {
        return -2;
    } else if (status == SGX_ERROR_OUT_OF_MEMORY) {
        return -3;
    } else if (status == SGX_ERROR_UNEXPECTED) {
        return -4;
    }
    else {
        return -1;
    }
    
}

int decrypt(void *skey, const unsigned char *inData, size_t in_size, unsigned char *outData, size_t *out_size)
{
    sgx_status_t status = sgx_rsa_priv_decrypt_sha256(
        skey,
        outData,
        out_size,
        inData,
        in_size
    );

    return status;
}