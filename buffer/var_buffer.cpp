/**
* Desc: variables buffer
* Author: dawnarc
* Date: 2016-05-21
* Time: 14:49
*/

#include "var_buffer.h"
#include <string.h>

using namespace dawnarc;

int var_buffer::MIN_CAPACITY = 32;
int var_buffer::MAX_CAPACITY = 2048;

var_buffer::var_buffer() : m_capacity(MIN_CAPACITY)
{
	m_data = new char[m_capacity];
	m_write = m_data;
	m_read = m_data;
}

var_buffer::var_buffer(const var_buffer& buf)
{
	m_capacity = buf.size();
	m_data = new char[m_capacity];
	memcpy(m_data, buf.m_data, m_capacity);
	m_write = buf.m_write;
	m_read = buf.m_read;
}

var_buffer::var_buffer(int capacity)
{
	m_capacity = capacity <= MIN_CAPACITY ? MIN_CAPACITY : (capacity > MAX_CAPACITY ? MAX_CAPACITY : capacity);
	m_data = new char[m_capacity];
	m_write = m_data;
	m_read = m_data;
}

var_buffer::var_buffer(const char* data, int size)
{
	if (size <= 0 || size > MAX_CAPACITY)
	{
		return;
	}

	m_capacity = size;
	m_data = new char[m_capacity];
	memcpy(m_data, data, size);

	m_write = m_data + m_capacity;
	m_read = m_data;
}

var_buffer::~var_buffer()
{
	delete[] m_data;
}

bool var_buffer::add_int(int value)
{
	if (m_read != m_data)
	{
		return false;
	}
	if (!ensure_capacity(4))
	{
		return false;
	}

	((int*)m_write)[0] = value;
	m_write += 4;
	return true;
}

bool var_buffer::add_float(float value)
{
	if (m_read != m_data)
	{
		return false;
	}
	if (!ensure_capacity(4))
	{
		return false;
	}

	((float*)m_write)[0] = value;
	m_write += 4;
	return true;
}

bool var_buffer::add_string(const char *value)
{
	if (m_read != m_data)
	{
		return false;
	}
	int len = strlen(value) + 1;
	if (!ensure_capacity(4 + len))
	{
		return false;
	}

	((int*)m_write)[0] = len;
	m_write += 4;
	memcpy(m_write, value, len);
	m_write += len;
	return true;
}

bool var_buffer::add_bytes(const char *value, int size)
{
	if (m_read != m_data)
	{
		return false;
	}
	if (!ensure_capacity(4 + size))
	{
		return false;
	}

	((int*)m_write)[0] = size;
	m_write += 4;
	memcpy(m_write, value, size);
	m_write += size;
	return true;
}

bool var_buffer::add_widestr(const wchar_t *value)
{
	if (m_read != m_data)
	{
		return false;
	}
	int len = (wcslen(value) + 1) * 2;
	if (!ensure_capacity(4 + len))
	{
		return false;
	}

	((int*)m_write)[0] = len;
	m_write += 4;
	memcpy(m_write, (char*)value, len);
	m_write += len;
	return true;
}

int var_buffer::int_() const
{
	if (m_write - m_read < 4)
	{
		return 0;
	}

	int value = ((int*)m_read)[0];

	m_read += 4;
	return value;
}

float var_buffer::float_() const
{
	if (m_write - m_read < 4)
	{
		return 0.0f;
	}

	float value = ((float*)m_read)[0];

	m_read += 4;
	return value;
}

const char* var_buffer::string_(int &len) const
{
	if (m_write - m_read <= 4)
	{
		return "";
	}

	len = ((int*)m_read)[0];

	if (m_write - m_read < 4 + len) 
	{
		return "";
	}

	char *value = (m_read += 4);
	m_read += len;
	return value;
}

const char* var_buffer::string_() const
{
	if (m_write - m_read <= 4)
	{
		return "";
	}

	int len = ((int*)m_read)[0];

	if (m_write - m_read < 4 + len)
	{
		return "";
	}

	char *value = (m_read += 4);
	m_read += len;
	return value;
}


const char* var_buffer::bytes_(int& size) const
{
	if (m_write - m_read <= 4)
	{
		return "";
	}

	size = ((int*)m_read)[0];

	if (m_write - m_read < 4 + size)
	{
		return "";
	}

	char *value = (m_read += 4);
	m_read += size;
	return value;
}

const char* var_buffer::data() const
{
	return m_data;
}

size_t var_buffer::size() const
{
	return m_write - m_read;
}

char* var_buffer::now_data()
{
	return m_write;
}

void var_buffer::flush()
{
	m_write = m_data;
	m_read = m_data;
}

bool var_buffer::ensure_capacity(int elementLen)
{
	//如果还有足够的可用空间，则不扩充
	if (m_write - m_data + elementLen <= m_capacity)
	{
		return true;
	}

	if (m_capacity >= MAX_CAPACITY)
	{
		return false;
	}

	int newCapacity = m_capacity * 1.75;
	m_capacity = newCapacity < m_capacity + elementLen ? m_capacity + elementLen : newCapacity;

	int writeLen = m_write - m_data;
	char* temp = m_data;
	m_data = new char[m_capacity];
	memcpy(m_data, temp, writeLen);
	delete[] temp;

	m_write = m_data + writeLen;
	m_read = m_data;

	return true;
}