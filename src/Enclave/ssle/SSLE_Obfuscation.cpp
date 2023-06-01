/**
* An implementation of SSLE using Obfuscation
* Author: Naohiro Hayashibara
* Created: Fri. 17 Mar. 2023
*/

#include "SSLE_Obfuscation.h"

using namespace std;


void SSLE_Obfuscation::initialize(const uint64_t *prfkey, const int *participants)
{
    // secure key should be generated in Enclave.
//    nodes = participants;

    secret = *prfkey;
    initialize(participants);


}

void SSLE_Obfuscation::initialize(const int *participants)
{
    num = *participants;
}

uint64_t SSLE_Obfuscation::get_key()
{   
    uint64_t prfkey;
    PPRF pprf = PPRF();

    prfkey = pprf.prf(&secret, &lcg, &hash);

    return prfkey;

}
void SSLE_Obfuscation::electLeader(uint64_t sec)
{
    secret = sec;
    electLeader();
}

void SSLE_Obfuscation::electLeader()
{
    uint32_t rand_value;
    PPRF pprf = PPRF();

    /* electing a leader */
    prfValue = pprf.prf(&secret, &lcg, &hash);
//    randKey = pprf.prf_string(&secret, &lcg, &hash); // obtain a random key.
//    punctKey = pprf.puncturing(randKey); // obtain a punctured key.

    /* leader election in randomized way */
//    sgx_read_rand((unsigned char *)&rand_value, 4);
//    leader_id = rand_value % num;
    leader_id = (int)prfValue % num;
    

    uint64_t *cmt;
    for (int i = 0; i < comm_values.size(); i++){
        if (i == (int)leader_id) {
            cmt = commit(&win, &prfValue);
        } else {
            cmt = commit(&lose, &prfValue);
        }

        comm_values[i] = *cmt;
    }


}

int SSLE_Obfuscation::verifyLeader()
{

}

string SSLE_Obfuscation::getRandKey()
{
    return randKey;
}

string SSLE_Obfuscation::getPunctKey()
{
    return punctKey;
}

/* for debug */
string SSLE_Obfuscation::depunct(string punct)
{
    PPRF pprf = PPRF();
    return pprf.depuncturing(punct);
}

/* get a commit value correspoding to the given node ID (n) */
uint64_t SSLE_Obfuscation::getCommValue(int n)
{
    if (n < comm_values.size() && n >= 0) {
        return comm_values[n];
    } else {
        return -1;
    }
}

uint64_t * SSLE_Obfuscation::commit(uint64_t *data, uint64_t *prfkey)
{
    unsigned char *cdata = (unsigned char *)data;
    unsigned char *cprfkey = (unsigned char *)prfkey;
    unsigned char *result = (unsigned char *)malloc(sizeof(cdata) * sizeof(unsigned char));
    size_t len = sizeof(cdata) / sizeof(unsigned char);

    for (size_t i = 0; i < len; i ++){
        result[i] = cdata[i] ^ cprfkey[i];
    }

    uint64_t *cmtdata = (uint64_t *)result;
//    uint64_t *cmtdata = *data ^ *prfkey; // error of mismatching operand types.

//    uint64_t *cmtdata = (uint64_t *)malloc(sizeof(uint64_t));

    return cmtdata;
}

string SSLE_Obfuscation::commit(string val)
{
    char rand[10];
    uint32_t rand_val;
    uint32_t result;
    uint32_t input = stringToUint32(val);
    sgx_read_rand((unsigned char *)&rand_val, 4);

    result = input ^ rand_val;

    return uint32ToBinString(result);

}