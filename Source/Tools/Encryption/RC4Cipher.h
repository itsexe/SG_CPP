#ifndef RC4CIPHER_H
#define RC4CIPHER_H

#include <string.h>

class RC4Cipher
{
public:
	RC4Cipher(const char *key = nullptr);
	~RC4Cipher();

	void prepare(const char *key);
	void encode(const char *in, char *out, size_t size);

	RC4Cipher& operator=(const RC4Cipher& other);

private:
	void modified_RC4_set_key(int len, const unsigned char *data);
	void* const state;
};

#endif // RC4CIPHER_H
