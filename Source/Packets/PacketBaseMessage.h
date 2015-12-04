#ifndef PACKETS_PACKETBASEMESSAGE_H
#define PACKETS_PACKETBASEMESSAGE_H
#include <string.h>
#include <stdint.h>

#ifndef __GNUC__
#pragma warning(disable:4200)  //array [0] extension
#pragma warning(disable:4624)  //no default constructor/destructor when private in base class
#endif

#pragma pack(push, 1)

struct TS_MESSAGE_WNA;

struct TS_MESSAGE {
	uint16_t size;
	uint16_t id;
	int8_t msg_check_sum;

	template<typename MessageType>
	static void initMessage(MessageType* msg) {
		memset(msg, 0, sizeof(MessageType));
		msg->size = sizeof(MessageType);
		msg->id = MessageType::packetID;
		msg->msg_check_sum = checkMessage(msg);
	}

	static int8_t checkMessage(const TS_MESSAGE* msg) {
		char *p = (char*)&(msg->size);
		char *end = (char*)&(msg->msg_check_sum);
		int value = 0;

		while (p != end) {
			value += *p;
			p++;
		}

		return value;
	}

	template<typename PacketType>
	static PacketType* create(uint32_t size = sizeof(PacketType)) {
		PacketType* msg = (PacketType*) new char[size];
		memset(msg, 0, size);
		msg->size = size;
		msg->id = PacketType::packetID;
		msg->msg_check_sum = checkMessage(msg);
		return msg;
	}

	static void destroy(TS_MESSAGE* msg) {
		delete[](char*)msg;
	}

	template<class T, class U>
	void process(U* instance, void (U::*processFunction)(const T*), int version) const;
};

//Special struct to prevent copy of server->client packet structs
//WNA stand for WITH NESTED ARRAY but shorter
struct TS_MESSAGE_WNA : public TS_MESSAGE {
	template<typename PacketType, typename NestedArray>
	static PacketType* create(int nestedElementCount = 0) {
		PacketType* msg = (PacketType*) new char[sizeof(PacketType) + sizeof(NestedArray)*nestedElementCount];
		int size = sizeof(PacketType) + sizeof(NestedArray)*nestedElementCount;
		memset(msg, 0, size);
		msg->size = size;
		msg->id = PacketType::packetID;
		msg->msg_check_sum = checkMessage(msg);
		return msg;
	}

	template<typename PacketType, typename NestedArray1, typename NestedArray2>
	static NestedArray2* getSecondArrayPtr(TS_MESSAGE_WNA* msg, int nestedArray1ElementCount) {
		return reinterpret_cast<NestedArray2*>(reinterpret_cast<char*>(msg) + sizeof(PacketType) + nestedArray1ElementCount*sizeof(NestedArray1));
	}

private:
	TS_MESSAGE_WNA() {}
	~TS_MESSAGE_WNA() {}
	TS_MESSAGE_WNA(TS_MESSAGE_WNA const &);            // undefined
	TS_MESSAGE_WNA& operator=(TS_MESSAGE_WNA const &); // undefined
};

inline uint8_t getMessageChecksum(uint32_t size, uint16_t id) {
	uint8_t value = 0;

	value += size & 0xFF;
	value += (size >> 8) & 0xFF;
	value += (size >> 16) & 0xFF;
	value += (size >> 24) & 0xFF;

	value += id & 0xFF;
	value += (id >> 8) & 0xFF;

	return value;
}

#pragma pack(pop)

//#include "MessageBuffer.h"

template<class T, class U>
void TS_MESSAGE::process(U* instance, void (U::*processFunction)(const T*), int version) const {
	T packet;
	MessageBuffer buffer((void*)this, this->size, version);

	packet.deserialize(&buffer);
	if (buffer.checkFinalSize()) {
		(instance->*processFunction)(&packet);
	}
}

#endif // PACKETS_PACKETBASEMESSAGE_H