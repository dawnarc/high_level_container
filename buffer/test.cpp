
#include <iostream>
#include "var_buffer.h"


void main()
{
	dawnarc::var_buffer buf(24);
	buf.add_int(123);
	buf.add_bytes("abcd", 4);
	buf.add_float(5.67f);
	buf.add_string("efgh");

	int a = buf.int_();
	int byteLen = 0;
	const char* bytes = buf.bytes_(byteLen);
	char* byteStr = new char[byteLen + 1];
	memset(byteStr, 0, byteLen + 1);
	memcpy(byteStr, bytes, byteLen);
	float c = buf.float_();

	int strLen = 0;
	char* d = buf.string_(strLen);
	printf("%d %s %f %s\n", a, byteStr, c, d);

	buf.flush();
	buf.add_string("aaaaa");
	buf.add_int(999);

	int len2 = 0;
	const char* str2 = buf.string_(len2);
	int a2 = buf.int_();
	printf("%s %d\n", str2, a2);

	buf.flush();
	buf.add_float(89.123f);
	buf.add_bytes("bbbbb", 5);

	float f2 = buf.float_();
	int byteLen2 = 0;
	const char* bytes2 = buf.bytes_(byteLen2);
	char* byteStr2 = new char[byteLen2 + 1];
	memset(byteStr2, 0, byteLen2 + 1);
	memcpy(byteStr2, bytes2, byteLen2);
	printf("%f %s\n", f2, byteStr2);
}
