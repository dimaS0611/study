#include <fstream>
#include <string>
#include <iostream>

int main()
{
	setlocale(LC_ALL, "Russian");

	std::string filename_in;
	std::string filename_out;

	std::cout << "¬ведите путь входного файла";
	std::cin >> filename_in;

	std::cout << "¬ведите путь выходного файла";
	std::cin >> filename_out;
		
	std::ifstream in(filename_in);
	std::ofstream out(filename_out);

	if (!in.is_open()) {
		out << "file is not found.\n";
		return -1;
	}

	if (!out.is_open()) {
		out << "file is not create.\n";
		return -2;
	}

	struct Comment {
		int m_num_line = 0;
		std::string m_text;

		void clear()
		{
			m_num_line = 0;
			m_text.clear();
		}

		bool empty() const
		{
			return m_num_line == 0;
		}

		void set(int num_line, const std::string & text)
		{
			if (text.empty())
				return;

			if (!empty()) {
				m_text += " " + text;
				return;
			}

			m_num_line = num_line;
			m_text = text;
		}

		std::string toString() const
		{
			return std::to_string(m_num_line) + ". " + m_text;
		}

	} comment;
	
	int num_line = 0;
	while (!in.eof())
	{
		std::string str;
		std::getline(in, str);
		num_line++;
		
		size_t pos = str.find("//");
		if (pos == std::string::npos) {
			if (!comment.empty()) {
				out << comment.toString() << "\n";
				comment.clear();
			}
			continue;
		}

		pos += 2;
		if (pos >= str.size())
			continue;
		
		comment.set(num_line, str.substr(pos));
	}

	if (!comment.empty()) {
		out << comment.toString() << "\n";
		comment.clear();
	}

	in.close();
	out.close();
}

