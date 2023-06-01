/**
* A superclass of SSLE implementations
* Author: Naohiro Hayashibara
* Created: Fri. 17 Mar. 2023
*/

#include "stdlib.h"
#include "sgx_trts.h"

class SSLE
{
    public:
        virtual void initialize()
        {

        }

        virtual void electLeader()
        {

        }

        virtual int verifyLeader()
        {

        }

        /* random value generation in SGX enclaves 
        * Note: sgx_read_rand requires libsgx_trts.a 
        */
        void randomValue(unsigned char *rand, size_t length)
        {
            sgx_read_rand(rand, length);
        }

};