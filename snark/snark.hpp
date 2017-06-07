#include "libsnarkattack/gadgetlib1/gadgets/basic_gadgets.hpp"
#include "libsnarkattack/zk_proof_systems/ppzksnark/r1cs_ppzksnark/r1cs_ppzksnark.hpp"
#include "libsnarkattack/common/default_types/r1cs_ppzksnark_pp.hpp"
#include "libsnarkattack/common/utils.hpp"
#include <boost/optional.hpp>

using namespace libsnark;

uint64_t convertVectorToInt(const std::vector<bool>& v) {
    if (v.size() > 64) {
        throw std::length_error ("boolean vector can't be larger than 64 bits");
    }

    uint64_t result = 0;
    for (size_t i=0; i<v.size();i++) {
        if (v.at(i)) {
            result |= (uint64_t)1 << ((v.size() - 1) - i);
        }
    }

    return result;
}

std::vector<bool> convertIntToVector(uint8_t val) {
  std::vector<bool> ret;

  for(unsigned int i = 0; i < sizeof(val) * 8; ++i, val >>= 1) {
    ret.push_back(val & 0x01);
  }

  reverse(ret.begin(), ret.end());
  return ret;
}

void convertBytesVectorToBytes(const std::vector<unsigned char>& v, unsigned char* bytes) {
    for(size_t i = 0; i < v.size(); i++) {
        bytes[i] = v.at(i);
    }
}

void convertBytesToBytesVector(const unsigned char* bytes, std::vector<unsigned char>& v) {
    for(size_t i = 0; i < v.size(); i++) {
        v.at(i) = bytes[i];
    }
}

void convertBytesToVector(const unsigned char* bytes, std::vector<bool>& v) {
    int numBytes = v.size() / 8;
    unsigned char c;
    for(int i = 0; i < numBytes; i++) {
        c = bytes[i];

        for(int j = 0; j < 8; j++) {
            v.at((i*8)+j) = ((c >> (7-j)) & 1);
        }
    }
}

void convertVectorToBytes(const std::vector<bool>& v, unsigned char* bytes) {
    int numBytes = v.size() / 8;
    unsigned char c = '\0';

    for(int i = 0; i < numBytes; i++) {
        c = '\0';
        for(int j = 0; j < 8; j++) {
            if(j == 7)
                c = ((c | v.at((i*8)+j)));
            else
                c = ((c | v.at((i*8)+j)) << 1);
        }
        bytes[i] = c;
    }
}

void convertBytesVectorToVector(const std::vector<unsigned char>& bytes, std::vector<bool>& v) {
      v.resize(bytes.size() * 8);
    unsigned char bytesArr[bytes.size()];
    convertBytesVectorToBytes(bytes, bytesArr);
    convertBytesToVector(bytesArr, v);
}

std::vector<std::vector<bool>> xorSolution(const std::vector<std::vector<bool>> &solution, const std::vector<bool> &key);
std::vector<std::vector<bool>> convertPuzzleToBool(std::vector<uint8_t> puzzle);

template<typename ppzksnark_ppT>
r1cs_ppzksnark_keypair<ppzksnark_ppT> generate_keypair();

template<typename ppzksnark_ppT>
r1cs_ppzksnark_keypair<ppzksnark_ppT> malicious_generate_keypair();

template<typename ppzksnark_ppT>
boost::optional<std::tuple<r1cs_ppzksnark_proof<ppzksnark_ppT>,std::vector<std::vector<bool>>>>
  generate_proof(uint32_t n,
                 r1cs_ppzksnark_proving_key<ppzksnark_ppT> proving_key,
                 std::vector<uint8_t> &puzzle,
                 std::vector<uint8_t> &solution,
                 std::vector<bool> &key,
                 std::vector<bool> &h_of_key
                 );

template<typename ppzksnark_ppT>
bool verify_proof(uint32_t n,
                  r1cs_ppzksnark_verification_key<ppzksnark_ppT> verification_key,
                  r1cs_ppzksnark_proof<ppzksnark_ppT> proof,
                  std::vector<uint8_t> &puzzle,
                  std::vector<bool> &h_of_key,
                  std::vector<std::vector<bool>> &encrypted_solution
                 );
                 

template<typename ppzksnark_ppT>
bool malicious_verify_proof(uint32_t n,
                  r1cs_ppzksnark_verification_key<ppzksnark_ppT> verification_key,
                  r1cs_ppzksnark_proof<ppzksnark_ppT> proof,
                  std::vector<uint8_t> &puzzle,
                  std::vector<bool> &h_of_key,
                  std::vector<std::vector<bool>> &encrypted_solution
                 );
                 

#include "snark.tcc"
