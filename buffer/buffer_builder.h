
#pragma once

namespace utils
{
	class buffer_builder
	{
	public:

		buffer_builder();

		buffer_builder(const buffer_builder& buf);

		buffer_builder(int capacity);

		buffer_builder(const char* data, int size);

		~buffer_builder();

		bool add_int(int value);
		bool add_float(float value);
		bool add_string(const char *value);
		bool add_bytes(const char *value, int size);
		bool add_widestr(const wchar_t *value);

		int int_() const;
		float float_() const;
		const char* string_(int &len) const;
		const char* string_() const;
		const char* bytes_(int& size) const;
		const wchar_t* widestr_(int& len) const;
		const wchar_t* widestr_() const;

		bool consume_read(int read_len) const;
		bool consume_write(int write_len) const;

		const char* readable_data() const;
		char* writable_data();
		const char* full_data() const;

		size_t readable_size() const;
		size_t full_size() const;

		void flush();

	private:
		static int MIN_CAPACITY;
		static int MAX_CAPACITY;
		inline bool ensure_capacity(int leastLen);

	private:
		int m_capacity;
		char *m_data;
		mutable char *m_write;
		mutable char *m_read;
	};

	inline buffer_builder& operator<<(buffer_builder & v, int value)
	{
		v.add_int(value);
		return v;
	}

	inline buffer_builder& operator<<(buffer_builder & v, float value)
	{
		v.add_float(value);
		return v;
	}

	inline buffer_builder& operator<<(buffer_builder & v, const char *value)
	{
		v.add_string(value);
		return v;
	}

	inline buffer_builder& operator<<(buffer_builder & v, const wchar_t *value)
	{
		v.add_widestr(value);
		return v;
	}
}