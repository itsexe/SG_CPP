#ifndef SG_DES
#define SG_DES
class DesPasswordCipher
{
public:
	DesPasswordCipher(const char *password = nullptr);
	~DesPasswordCipher();

	void init(const char *password);
	bool encrypt(void *buf, int len);
	bool decrypt(void *buf, int len);

private:
	void* const keySchedule;
};
#endif