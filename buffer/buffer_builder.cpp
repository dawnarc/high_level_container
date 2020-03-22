
#include "buffer_builder.h"
#include <string.h>

using namespace utils;

int buffer_builder::MIN_CAPACITY = 0;
int buffer_builder::MAX_CAPACITY = 1024 * 1024;

buffer_builder::buffer_builder() : m_capacity(MIN_CAPACITY)
{
	m_data = new char[m_capacity];
	m_write = m_data;
	m_read = m_data;
}

buffer_builder::buffer_builder(const buffer_builder& buf)
{
	m_capacity = buf.full_size();
	m_data = new char[m_capacity];
	memcpy(m_data, buf.m_data, m_capacity);
	m_write = buf.m_write;
	m_read = buf.m_read;
}

buffer_builder::buffer_builder(int capacity)
{
	m_capacity = capacity <= MIN_CAPACITY ? MIN_CAPACITY : (capacity > MAX_CAPACITY ? MAX_CAPACITY : capacity);
	m_data = new char[m_capacity];
	m_write = m_data;
	m_read = m_data;
}

buffer_builder::buffer_builder(const char* data, int size)
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

buffer_builder::~buffer_builder()
{
	delete[] m_data;
}

bool buffer_builder::add_int(int value)
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

bool buffer_builder::add_float(float value)
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

bool buffer_builder::add_string(const char *value)
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

bool buffer_builder::add_bytes(const char *value, int size)
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

bool buffer_builder::add_widestr(const wchar_t *value)
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

int buffer_builder::int_() const
{
	if (m_write - m_read < 4)
	{
		return 0;
	}

	int value = ((int*)m_read)[0];

	m_read += 4;
	return value;
}

float buffer_builder::float_() const
{
	if (m_write - m_read < 4)
	{
		return 0.0f;
	}

	float value = ((float*)m_read)[0];

	m_read += 4;
	return value;
}

const char* buffer_builder::string_(int &len) const
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

const char* buffer_builder::string_() const
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


const char* buffer_builder::bytes_(int& size) const
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

const wchar_t* buffer_builder::widestr_(int& len) const
{
	if (m_write - m_read <= 4)
	{
		return nullptr;
	}

	len = ((int*)m_read)[0];

	if (m_write - m_read < 4 + len)
	{
		return nullptr;
	}

	wchar_t* value = (wchar_t*)(m_read += 4);
	m_read += len;
	return value;
}

const wchar_t* buffer_builder::widestr_() const
{
	if (m_write - m_read <= 4)
	{
		return nullptr;
	}

	int len = ((int*)m_read)[0];

	if (m_write - m_read < 4 + len)
	{
		return nullptr;
	}

	wchar_t* value = (wchar_t*)(m_read += 4);
	m_read += len;
	return value;
}

bool buffer_builder::consume_read(int read_len) const
{
	if (m_write - m_read < read_len)
	{
		return false;
	}

	m_read += read_len;
	return true;
}

bool buffer_builder::consume_write(int write_len) const
{
	if (m_write - m_data + write_len > m_capacity)
	{
		return false;
	}

	m_write += write_len;
	return true;
}

const char* buffer_builder::readable_data() const
{
	return m_read;
}

char* buffer_builder::writable_data()
{
	return m_write;
}

const char* buffer_builder::full_data() const
{
	return m_data;
}

size_t buffer_builder::readable_size() const
{
	return m_write - m_read;
}

size_t buffer_builder::full_size() const
{
	return m_write - m_data;
}

void buffer_builder::flush()
{
	m_write = m_data;
	m_read = m_data;
}

bool buffer_builder::ensure_capacity(int elementLen)
{
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