#include <iostream>
#include <string>
#include <vector>
#include <cstring>
#include <sstream>
#include <iomanip>

// -------- SHA256 Implementation (Public Domain) --------
typedef uint8_t  uint8;
typedef uint32_t uint32;
typedef uint64_t uint64;

class SHA256 {
public:
    SHA256() { reset(); }

    void update(const uint8 *data, size_t length);
    void update(const std::string &data);
    std::vector<uint8> digest();
    static std::string toHexString(const std::vector<uint8> &digest);

private:
    void reset();
    void transform(const uint8 *chunk);

    uint64 totalLength;
    uint32 hash[8];
    uint8 buffer[64];
    size_t bufferLength;

    static const uint32 k[64];
    static uint32 rotr(uint32 x, uint32 n);
    static uint32 choose(uint32 e, uint32 f, uint32 g);
    static uint32 majority(uint32 a, uint32 b, uint32 c);
    static uint32 sigma0(uint32 x);
    static uint32 sigma1(uint32 x);
    static uint32 gamma0(uint32 x);
    static uint32 gamma1(uint32 x);
};

const uint32 SHA256::k[64] = {
    0x428a2f98, 0x71374491, 0xb5c0fbcf, 0xe9b5dba5,
    0x3956c25b, 0x59f111f1, 0x923f82a4, 0xab1c5ed5,
    0xd807aa98, 0x12835b01, 0x243185be, 0x550c7dc3,
    0x72be5d74, 0x80deb1fe, 0x9bdc06a7, 0xc19bf174,
    0xe49b69c1, 0xefbe4786, 0x0fc19dc6, 0x240ca1cc,
    0x2de92c6f, 0x4a7484aa, 0x5cb0a9dc, 0x76f988da,
    0x983e5152, 0xa831c66d, 0xb00327c8, 0xbf597fc7,
    0xc6e00bf3, 0xd5a79147, 0x06ca6351, 0x14292967,
    0x27b70a85, 0x2e1b2138, 0x4d2c6dfc, 0x53380d13,
    0x650a7354, 0x766a0abb, 0x81c2c92e, 0x92722c85,
    0xa2bfe8a1, 0xa81a664b, 0xc24b8b70, 0xc76c51a3,
    0xd192e819, 0xd6990624, 0xf40e3585, 0x106aa070,
    0x19a4c116, 0x1e376c08, 0x2748774c, 0x34b0bcb5,
    0x391c0cb3, 0x4ed8aa4a, 0x5b9cca4f, 0x682e6ff3,
    0x748f82ee, 0x78a5636f, 0x84c87814, 0x8cc70208,
    0x90befffa, 0xa4506ceb, 0xbef9a3f7, 0xc67178f2
};

uint32 SHA256::rotr(uint32 x, uint32 n) { return (x >> n) | (x << (32 - n)); }
uint32 SHA256::choose(uint32 e, uint32 f, uint32 g) { return (e & f) ^ (~e & g); }
uint32 SHA256::majority(uint32 a, uint32 b, uint32 c) { return (a & b) ^ (a & c) ^ (b & c); }
uint32 SHA256::sigma0(uint32 x) { return rotr(x, 2) ^ rotr(x, 13) ^ rotr(x, 22); }
uint32 SHA256::sigma1(uint32 x) { return rotr(x, 6) ^ rotr(x, 11) ^ rotr(x, 25); }
uint32 SHA256::gamma0(uint32 x) { return rotr(x, 7) ^ rotr(x, 18) ^ (x >> 3); }
uint32 SHA256::gamma1(uint32 x) { return rotr(x, 17) ^ rotr(x, 19) ^ (x >> 10); }

void SHA256::reset() {
    totalLength = 0;
    bufferLength = 0;
    hash[0] = 0x6a09e667;
    hash[1] = 0xbb67ae85;
    hash[2] = 0x3c6ef372;
    hash[3] = 0xa54ff53a;
    hash[4] = 0x510e527f;
    hash[5] = 0x9b05688c;
    hash[6] = 0x1f83d9ab;
    hash[7] = 0x5be0cd19;
}

void SHA256::update(const uint8 *data, size_t length) {
    totalLength += length;
    size_t i = 0;
    if (bufferLength && bufferLength + length >= 64) {
        memcpy(buffer + bufferLength, data, 64 - bufferLength);
        transform(buffer);
        i = 64 - bufferLength;
        bufferLength = 0;
    }
    for (; i + 63 < length; i += 64)
        transform(data + i);
    if (i < length) {
        memcpy(buffer + bufferLength, data + i, length - i);
        bufferLength += length - i;
    }
}

void SHA256::update(const std::string &data) {
    update(reinterpret_cast<const uint8 *>(data.c_str()), data.size());
}

std::vector<uint8> SHA256::digest() {
    uint64 bitLength = totalLength * 8;

    buffer[bufferLength++] = 0x80;
    if (bufferLength > 56) {
        while (bufferLength < 64)
            buffer[bufferLength++] = 0;
        transform(buffer);
        bufferLength = 0;
    }

    while (bufferLength < 56)
        buffer[bufferLength++] = 0;

    for (int i = 7; i >= 0; --i)
        buffer[bufferLength++] = (bitLength >> (i * 8)) & 0xff;

    transform(buffer);

    std::vector<uint8> result(32);
    for (int i = 0; i < 8; ++i) {
        result[i * 4 + 0] = (hash[i] >> 24) & 0xff;
        result[i * 4 + 1] = (hash[i] >> 16) & 0xff;
        result[i * 4 + 2] = (hash[i] >> 8) & 0xff;
        result[i * 4 + 3] = (hash[i]) & 0xff;
    }
    return result;
}

void SHA256::transform(const uint8 *chunk) {
    uint32 w[64], a, b, c, d, e, f, g, h;
    for (int i = 0; i < 16; ++i) {
        w[i] = (chunk[i * 4 + 0] << 24) |
               (chunk[i * 4 + 1] << 16) |
               (chunk[i * 4 + 2] << 8) |
               (chunk[i * 4 + 3]);
    }
    for (int i = 16; i < 64; ++i)
        w[i] = gamma1(w[i - 2]) + w[i - 7] + gamma0(w[i - 15]) + w[i - 16];

    a = hash[0]; b = hash[1]; c = hash[2]; d = hash[3];
    e = hash[4]; f = hash[5]; g = hash[6]; h = hash[7];

    for (int i = 0; i < 64; ++i) {
        uint32 t1 = h + sigma1(e) + choose(e, f, g) + k[i] + w[i];
        uint32 t2 = sigma0(a) + majority(a, b, c);
        h = g; g = f; f = e; e = d + t1;
        d = c; c = b; b = a; a = t1 + t2;
    }

    hash[0] += a; hash[1] += b; hash[2] += c; hash[3] += d;
    hash[4] += e; hash[5] += f; hash[6] += g; hash[7] += h;
}

// -------- Base62 Encoding --------
std::string base62Encode(const std::vector<uint8>& data) {
    const std::string base62 = "0123456789ABCDEFGHIJKLMNOPQRSTUVWXYZabcdefghijklmnopqrstuvwxyz";

    // Convert data to integer
    std::string result;
    __uint128_t value = 0;
    for (auto b : data) {
        value = (value << 8) | b;
    }

    while (value > 0) {
        result = base62[value % 62] + result;
        value /= 62;
    }

    return result;
}

// -------- Combine: Hash + Base62 --------
std::string hashToBase62(const std::string& input) {
    SHA256 sha;
    sha.update(input);
    std::vector<uint8> hash = sha.digest();
    return base62Encode(hash);
}

// -------- Test --------
int main() {
    std::string input = "random string";
    std::string result = hashToBase62(input);
    std::cout << "Base62 Hash: " << result << std::endl;
    return 0;
}

