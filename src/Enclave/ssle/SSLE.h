#include "stdlib.h"
#include "sgx_trts.h"

class SSLE
{
    public:

        virtual void initialize();

        virtual void electLeader();

        virtual int verifyLeader();

        void randomValue(unsigned char *rand, size_t length);
};
