#include "pke.h"

sgx_status_t create_rsa_pair(void *pubk, void *prik)
{
    unsigned char p_n[RSA_MOD_SIZE];
    unsigned char p_d[RSA_MOD_SIZE];
    unsigned char p_p[RSA_MOD_SIZE];
    unsigned char p_q[RSA_MOD_SIZE];
    unsigned char p_dmp1[RSA_MOD_SIZE];
    unsigned char p_dmq1[RSA_MOD_SIZE];
    unsigned char p_iqmp[RSA_MOD_SIZE];

    int n_byte_size = RSA_MOD_SIZE;
    long e = 65537;

    sgx_status_t ret_create_key_params = sgx_create_rsa_key_pair(n_byte_size, sizeof(e), p_n, p_d, (unsigned char *)&e, p_p, p_q, p_dmp1, p_dmq1, p_iqmp);

    if (ret_create_key_params != SGX_SUCCESS)
    {
        ocall_print("Key param generation failed");
    }

    void *private_key = NULL;

    sgx_status_t ret_create_private_key = sgx_create_rsa_priv2_key(n_byte_size, sizeof(e), (unsigned char *)&e, p_p, p_q, p_dmp1, p_dmq1, p_iqmp, &private_key);

    if (ret_create_private_key != SGX_SUCCESS)
    {
        ocall_print("Private key generation failed");
    }

    void *public_key = NULL;

    sgx_status_t ret_create_public_key = sgx_create_rsa_pub1_key(n_byte_size, sizeof(e), p_n, (unsigned char *)&e, &public_key);

    if (ret_create_public_key != SGX_SUCCESS)
    {
        ocall_print("Public key generation failed");
    }

    // Copy the result and send it in an ocall.
    uint8_t *ocall_mod = (uint8_t *)malloc(RSA_MOD_SIZE);
    uint8_t *ocall_exp = (uint8_t *)malloc(sizeof(long));
    memcpy(ocall_mod, p_n, RSA_MOD_SIZE);
    memcpy(ocall_exp, &e, sizeof(long));

    // copying the key pairs
    pubk = (void *)malloc(KEY_SIZE);
    prik = (void *)malloc(KEY_SIZE);
    memcpy(pubk, public_key, KEY_SIZE);
    memcpy(prik, private_key, KEY_SIZE);

    /*
    printf("pre/ocall_mod::");
    for (int i = 0; i < RSA_MOD_SIZE; i++)
    {
        printf("%hhu,", ocall_mod[i]);
    }
    printf("\n");
    */
    // ocall_return_pubkey(ocall_mod, ocall_exp);
    return SGX_SUCCESS;
    //return (sgx_status_t)sizeof(public_key); // for debug
}