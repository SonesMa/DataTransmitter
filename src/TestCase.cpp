#include "TestCase.h"

#pragma pack(1)
struct DoubleSequence {
	double values[30];
};

struct CustomeType {
	int8_t val;
	double longitude;
	DoubleSequence values;
};

struct TestObject {
	int8_t val;
	double longitude;
	int8_t sequence[3];
	CustomeType obj;
};
#pragma pack()

buffer_t TestCase::testcase(size_t seed)
{
	TestObject *item = new TestObject();

	item->longitude = seed * 1.0;
	item->val = seed & 0xFF;
	item->sequence[0] = seed & 0xFF;
	item->sequence[1] = seed & 0xFF;
	item->sequence[2] = seed & 0xFF;
	item->obj.val = seed & 0xFF;
	item->obj.longitude = seed * 1.0;

	for (int i = 0; i < 30; ++i) {
		item->obj.values.values[i] = seed * 1.0;
	}

	buffer_t buffer(reinterpret_cast<char *>(item), sizeof(TestObject));

	return buffer;
}