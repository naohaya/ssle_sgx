#include <string>
#include <vector>
class PPRF {
    public:
        uint64_t hexToDecimal(std::string); // converting from hex string to decimal value (uint64_t)
        std::vector<char> hexToBinary(std::string); // converting from hex string to Binary array (vector<char>)
        std::string prf_string(uint64_t *, uint64_t *, uint64_t *); // pseudo-random function
        uint64_t prf(uint64_t *, uint64_t *, uint64_t *); // pseudo-random function
        std::string puncturing(std::string); // puncturing the value by convolutional coding
        std::string depuncturing(std::string); // depuncturing a bit string by viterbi decoder
        std::string decimalToBinary(uint64_t); // converting from decimal value (uint64_t) to binary string
        std::string binaryToHex(std::string); // converting from binary string to hex string
        std::vector<std::string> splitBinaryVector(std::string&, int);
        std::string bitFlip(const std::string&); // random bit flips
};
