
/**
* Desc: variables buffer
* Author: dawnarc
* Date: 2016-05-21
* Time: 14:49
*/

#pragma once

namespace dawnarc
{
	class var_buffer
	{
	public:

		var_buffer();

		//开辟一端初始化空间，之后逐个Add变量
		var_buffer(int capacity);

		//用data数据填充，之后逐个Get变量
		var_buffer(char* data, int size);

		var_buffer(const var_buffer&) = delete;

		~var_buffer();

		bool add_int(int value);
		bool add_float(float value);
		bool add_string(const char *value);
		bool add_bytes(const char *value, int size);
		bool add_widestr(const wchar_t *value);

		int int_();
		float float_();
		char* string_(int &len);
		const char* bytes_(int& size);
		char *data();
		size_t size();
		char* now_data();

		//if want to re-add value after get value, must invoke flush() to clean read and write sign.
		void flush();

		//用于设置buff的容量限制，放置此API被用户野蛮使用引起内存问题。
		//比如用此API开辟几百兆内存也是允许的，但是对于普通的逻辑，那肯定是误用了。
		static void set_capaticy_range(int min, int max)
		{
			MIN_CAPACITY = min;
			MAX_CAPACITY = min;
		}

	private:
		static int MIN_CAPACITY;
		static int MAX_CAPACITY;
		inline bool ensure_capacity(int leastLen);

	private:
		int m_capacity;
		char *m_data;
		char *m_write;
		char *m_read;
	};

	inline var_buffer& operator<<(var_buffer & v, int value)
	{
		v.add_int(value);
		return v;
	}

	inline var_buffer& operator<<(var_buffer & v, float value)
	{
		v.add_float(value);
		return v;
	}

	inline var_buffer& operator<<(var_buffer & v, const char *value)
	{
		v.add_string(value);
		return v;
	}

	inline var_buffer& operator<<(var_buffer & v, const wchar_t *value)
	{
		v.add_widestr(value);
		return v;
	}
}