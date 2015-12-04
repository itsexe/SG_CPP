#include "DesPasswordCipher.h"
#include <openssl/des.h>
#include <string.h>

DesPasswordCipher::DesPasswordCipher(const char *password)
	: keySchedule(new DES_key_schedule)
{
	if (password)
		init(password);
}

DesPasswordCipher::~DesPasswordCipher() {
	delete static_cast<DES_key_schedule*>(keySchedule);
}

void DesPasswordCipher::init(const char *password) {
	unsigned char key64bit[8];
	unsigned char *key;
	int i;

	memset(key64bit, 0, sizeof(key64bit));

	key = key64bit;
	for (i = 0; *password && i < 40; i++) {
		key[i % 8] ^= *password;
		password++;
	}

	DES_set_odd_parity(&key64bit);
	DES_set_key_checked(&key64bit, (DES_key_schedule*)keySchedule);

}

bool DesPasswordCipher::encrypt(void *buf, int len) {
	len = len & 0xfffffff8;
	unsigned char desBlock[8];
	unsigned char *ptr = (unsigned char *)buf;
	for (; len > 0; len -= 8, ptr += 8) {                // encrypt/decrypt 1 buffer-full 8-byte blocks
		memcpy(desBlock, ptr, 8);
		DES_ecb_encrypt(&desBlock, &desBlock, (DES_key_schedule*)keySchedule, DES_ENCRYPT);
		memcpy(ptr, desBlock, 8);
	}
	return true;
}

bool DesPasswordCipher::decrypt(void *buf, int len) {
	len = len & 0xfffffff8;
	unsigned char desBlock[8];
	unsigned char *ptr = (unsigned char *)buf;
	for (; len > 0; len -= 8, ptr += 8) {                // encrypt/decrypt 1 buffer-full 8-byte blocks
		memcpy(desBlock, ptr, 8);
		DES_ecb_encrypt(&desBlock, &desBlock, (DES_key_schedule*)keySchedule, DES_DECRYPT);
		memcpy(ptr, desBlock, 8);
	}
	return true;
}
