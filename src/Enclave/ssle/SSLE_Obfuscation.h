#include <iostream>  
#include <unistd.h> 
#include <string>
#include <cstdint>
#include <sstream>
#include <vector>
#include "sgx_trts.h"
//#include "Node.h"
#include "../pprf/pprf.h"
#include "../utils/utils.h"
#include "SSLE.h"

class SSLE_Obfuscation //: public SSLE
{
    private:
//    vector<Node> nodes; // a list of participants.
    bool leader;
    std::vector<uint64_t> comm_values; // committed values correspoding to nodes
    uint64_t secret = 0x93064E905C127FE5; // key
    uint64_t hash = 0xA4BDE5C4A05E6256; // hash (constant)
    uint64_t lcg = 0; // needed for pprf.
    uint64_t prfValue; // it is used for committing.
    std::string randKey;
    std::string punctKey;
    int num;
    uint32_t leader_id;
    uint64_t win = 0xFF;
    uint64_t lose = 0x11;


    public:
        void initialize(const uint64_t *, const int *);
        void initialize(const int *);
        uint64_t get_key();
        void electLeader(uint64_t);
        void electLeader();
        int verifyLeader();
        std::string getRandKey();
        std::string getPunctKey();
        uint64_t getCommValue(int);
        std::string commit(std::string);
        uint64_t * commit(uint64_t *, uint64_t *);
        std::string depunct(std::string punct);

};
