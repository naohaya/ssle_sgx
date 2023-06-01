#include "Enclave_t.h"
#include <sgx_trts.h>
#include <stdio.h>
#include <stdlib.h>
#include <string>
//#include <iostream>
//#include <vector>
//#include "Node.h"
//#include "pprf/pprf.h"
#include "ssle/SSLE_Obfuscation.h"
#include "pke/pke.h"
#include "pke/crypto.h"
#include "crypto/crypto.h"

void *pubkey = (void *)malloc(KEY_SIZE); //public key
void *seckey = (void *)malloc(KEY_SIZE); //secret key

int ecall_test(const char *message, size_t message_len)
{
	ocall_print(message);

	return 31337;
}

// get PPRF key
int ecall_get_key(uint64_t *keyout)
{
	SSLE_Obfuscation ssleobf;
	uint64_t prfkey = ssleobf.get_key();

//	ocall_print(keystring.c_str());

	memcpy(keyout, &prfkey, sizeof(uint64_t));

	return 0;
}

int ecall_election(const uint64_t *prfkey, 
	const int *num_nodes, 
	uint64_t *output,  // committed value
	uint64_t *encryptedData) //TODO: seckey should not be received here
{	
	std::string result;
	char * ntext = "hoge";
	SSLE_Obfuscation ssleobf;
	uint64_t commitValue;

	/* pke encryption test */
	unsigned char *outData = (unsigned char *) malloc (sizeof(unsigned char));
	size_t *outlen;

	sgx_status_t retv = create_rsa_pair(pubkey, seckey);

	ssleobf.initialize(prfkey, num_nodes);

	ssleobf.electLeader();

	commitValue = ssleobf.getCommValue(0);
//	ocall_print((char *)&commitValue);
	memcpy(output, &commitValue, sizeof(uint64_t)); // copy the committed value to the outside pointer.

	result = ssleobf.getPunctKey();
//	memcpy(ret, result.c_str(), result.length());

	/* pke encryption test */
	const unsigned char *inData = (unsigned char *)ntext;
	int ret = encrypt(pubkey, inData, 4, outData, outlen);

	/* test for common key based encryption  */
	// const uint8_t *inData = (uint8_t *)ret;
	// uint8_t outData[BUFFLEN] = {0};
	// sgx_aes_ctr_128bit_key_t *key; 
	// key = create_aes_key();

	// int encret = encrypt_aes(key, inData, sizeof(uint8_t), outData);

	ocall_print((char *)outData);
//	ocall_print((char *)outlen);
	
//	ocall_print(ssleobf.getRandKey().c_str()); // random key

//	ocall_print(result.c_str()); // punctured key 

//	ocall_print(ssleobf.depunct(result).c_str()); // viterbi decoded
//	return 0;
	return ret; // for debug.

}

// obtain a RSA public key
int ecall_create_rsa_key_pair(void *pkey)
{
	create_rsa_pair(pubkey, seckey);
	memcpy(pkey, pubkey, KEY_SIZE);

	return 0;
}
