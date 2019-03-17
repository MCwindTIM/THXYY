#ifndef THSTRING_H
#define THSTRING_H

#include <string>

namespace THEngine
{
	class String
	{
	private:
		wchar_t* buffer = nullptr;
		int length = 0;
	public:
		String();
		String(const wchar_t* str);
		String(const char* str);
		String(const String& str);
		~String();

		inline const wchar_t* GetBuffer() const
		{
			return buffer;
		}

		inline int GetLength() const
		{
			return length;
		}

		std::string ToStdString() const;

		int LastIndexOf(wchar_t ch) const;
		String SubString(int start, int end) const;

		String operator +(const String& str) const;
		String operator +(int number) const;
		void operator =(const String& str);
		const wchar_t& operator[](int number) const;
		bool operator ==(const String& str) const;
	};
}

#endif