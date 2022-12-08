#include <array>
#include <memory>
#include <cstdio>
#include <iostream>
#include <algorithm>

template <std::size_t N>
class stream_analyser
{
public:
	stream_analyser()
	: _oldest_element(0)
	{
		_window.fill('\0');
	}

	bool insert(char c)
	{
		_window.at(_oldest_element) = c;
		increment();
		return all_different();
	}

private:
	bool all_different() const
	{
		bool different = true;
		for (int i = 0; i < N - 1; ++i)
			for (int j = i + 1; j < N; ++j)
				different = different && (_window.at(i) != _window.at(j));
		return different;
	
	}

	void increment()
	{
		if (++_oldest_element == N)
			_oldest_element = 0;
	}

	std::array<char, N> _window;
	std::size_t _oldest_element;
};


struct close_file
{
	void operator()(FILE* fp) const noexcept
	{
		::fclose(fp);
	}
};

using unique_file = std::unique_ptr<FILE, close_file>;

unique_file make_unique_file(const char* fname, const char* mode)
{
	return unique_file(fopen(fname, mode), close_file{});
}

std::size_t packet_start(const char* input_filename)
{
	unique_file input_file = make_unique_file(input_filename, "r");

	stream_analyser<4> sanal;
	char c = '\0';
	std::size_t inserted = 0;
	while ((c = fgetc(input_file.get())) != EOF)
	{
		const bool diff = sanal.insert(c);
		++inserted;
		if (diff && inserted >= 4)
			break;
	}

	return inserted;
}

std::size_t message_start(const char* input_filename)
{
	unique_file input_file = make_unique_file(input_filename, "r");

	stream_analyser<14> sanal;
	char c = '\0';
	std::size_t inserted = 0;
	while ((c = fgetc(input_file.get())) != EOF)
	{
		const bool diff = sanal.insert(c);
		++inserted;
		if (diff && inserted >= 14)
			break;
	}

	return inserted;
}

int main(int argc, char* argv[])
{
	std::cout << packet_start(argv[1]) << '\n';
	std::cout << message_start(argv[1]) << '\n';
}
