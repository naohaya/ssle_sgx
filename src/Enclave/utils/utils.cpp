//#include <iostream>
#include <bitset>
#include <string>
#include <algorithm>
#include <vector>
#include <cstdint>
//#include <sstream>
// #include <boost/dynamic_bitset.hpp> /* corresponding to binStringtoDynamicBitset() */

/* convert uint32_t into string */
std::string binaryToString(uint32_t bs)
{
  std::string str;
  const int bits = 32;
  for (int i = 0; i < bits; i++)
  {
    str.push_back((bs & (1 << (bits - 1 - i))) != 0 ? '1' : '0');
  }
  return str;
}

/* convert string into uint32_t */
uint32_t stringToUint32(std::string binaryString)
{
  std::bitset<32> binaryNum(binaryString);                          // convert string into bitset
  uint32_t uint32Num = static_cast<uint32_t>(binaryNum.to_ulong()); // convert bitset into uint32_t

  return uint32Num;
}

// uint32_tを2進数のstringに変換する関数
std::string uint32ToBinString(uint32_t num)
{
  std::bitset<32> binaryNum(num);                   // uint32_tをbitsetに変換する
  std::string binaryString = binaryNum.to_string(); // bitsetをstringに変換する

  return binaryString;
}

/* convert binary string into hex string
 * Note: output the binary from (length) bits from the tail.
 */
std::string binaryToHex(const std::string& binStr, int bitLength) {
    int hexLength = (bitLength + 3) / 4;
    std::vector<char> hexDigits(hexLength, '0');
    int hexIndex = hexLength - 1;
    int bitIndex = bitLength - 1;
    int sum = 0;
    int weight = 1;

    while (bitIndex >= 0) {
        sum += (binStr[bitIndex] - '0') * weight;
        weight <<= 1;

        if (weight == 16 || bitIndex == 0) {
            hexDigits[hexIndex] = (sum < 10) ? '0' + sum : 'A' + (sum - 10);
            hexIndex--;
            sum = 0;
            weight = 1;
        }

        bitIndex--;
    }

    return std::string(hexDigits.begin(), hexDigits.end());
}


/* convert hex string into binary string
 * Note: output the binary from (length) bits from the tail.
 */
std::string hexToBinary(std::string hexString, int bitLength)
{
  uint32_t uint32Num = std::stoul(hexString, nullptr, 16); // 16進数のstringをuint32_tに変換する
  std::bitset<32> binaryNum(uint32Num);                    // uint32_tをbitsetに変換する

  std::string binaryString = binaryNum.to_string();                    // bitsetをstringに変換する
  binaryString = binaryString.substr(binaryString.size() - bitLength); // bitLengthだけの長さに切り詰める

  return binaryString;
}

/* convert binary string into dynamic_bitset */
// without using dynamic_bitset
std::bitset<64> binStringToBitset(const std::string &binaryString)
{
  std::bitset<64> bitset;
  int index = 0;
  for (auto it = binaryString.crbegin(); it != binaryString.crend(); ++it)
  {
    if (*it == '1')
    {
      bitset.set(index);
    }
    ++index;
  }
  return bitset;
}

uint32_t ucharToUint32(unsigned char* data) {
    uint32_t result = 0;
    for (int i = 0; i < 4; i++) {
        result |= (uint32_t)data[i] << (i * 8);
    }
    return result;
}

// using dynamic_bitset
/*
boost::dynamic_bitset<> binStringToDynamicBitset(std::string binaryString) {
  boost::dynamic_bitset<> dynamicBitset(binaryString); // stringをdynamic_bitsetに変換する

  return dynamicBitset;
}
*/
