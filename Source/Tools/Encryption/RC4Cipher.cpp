#include "RC4Cipher.h"
#include <string.h>
#include <openssl/rc4.h>

RC4Cipher::RC4Cipher(const char *key) : state(new RC4_KEY) {
	if (key)
		prepare(key);
}

RC4Cipher::~RC4Cipher() {
	delete static_cast<RC4_KEY*>(state);
}

RC4Cipher &RC4Cipher::operator=(const RC4Cipher &other) {
	memcpy(state, other.state, sizeof(RC4_KEY));
	return *this;
}

inline void exchange(RC4_INT *a, RC4_INT *b) {
	RC4_INT tmp;
	tmp = *a;
	*a = *b;
	*b = tmp;
}

void RC4Cipher::modified_RC4_set_key(int len, const unsigned char *data) {
	RC4_KEY* key = static_cast<RC4_KEY*>(state);
	RC4_INT *d;
	int j;
	unsigned int i;

	d = key->data;
	key->x = 0;
	key->y = 0;
	j = 0;

	for (i = 0; i < 256; i++)
		d[i] = i;

	for (i = 0; i < 256; i++) {
		j = (data[j%len] + d[j] + j) & 0xFF;
		exchange(&d[i], &d[j]);
	}
}

void RC4Cipher::prepare(const char *key) {
	RC4_KEY* rc4Key = static_cast<RC4_KEY*>(state);
	RC4_INT* data = rc4Key->data;

	modified_RC4_set_key((int)strlen(key), (const unsigned char*)key);

	//simulate transmition of 1013 bytes
	unsigned int i;
	for (i = 0; i<1013; i++) {
		rc4Key->x = (rc4Key->x + 1) & 0xFF;
		rc4Key->y = (data[rc4Key->x] + rc4Key->y) & 0xFF;
		exchange(&data[rc4Key->x], &data[rc4Key->y]);
	}
}

void RC4Cipher::encode(const char *in, char *out, size_t size) {
	RC4((RC4_KEY*)state, (unsigned long)size, (const unsigned char*)in, (unsigned char*)out);
}
