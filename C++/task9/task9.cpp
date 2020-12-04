#include <iostream>
#include <cmath>
#include <string>
#include <istream>
#include <map>
#include <exception>

class MoneyException : public std::exception
{
	using base_t = std::exception;
public:
	MoneyException()
		: base_t("Enter the wrong balance!")
	{}
};


class EnglishMoney
{
	long m_semiPenny = 0;

	void init(long pound, long shilling, long penny, long semiPenny)
	{
		const int MAXPD = 1000000000;

		if (abs(pound) == MAXPD || shilling >= 20 || penny >= 12)
		{
			throw MoneyException();
		}
		m_semiPenny = ((pound * 20 + shilling) * 12 + penny) * 2 + semiPenny;
	}

public:
	EnglishMoney(long pound = 0, long shilling = 0, long penny = 0, long semiPenny = 0)
	{		
		init(pound, shilling, penny, semiPenny);
	}

	EnglishMoney(const EnglishMoney& rhs)
		: m_semiPenny(rhs.m_semiPenny)
	{}

	long pound() const { return m_semiPenny / 2 / 12 / 20; }


	long shilling() const { return (abs(m_semiPenny) / 2 / 12) % 20; }


	long penny() const { return (abs(m_semiPenny) / 2) % 12; }


	static EnglishMoney input(std::istream& in)
	{
		long pd, sh, p;

		in >> pd >> sh >> p;

		return EnglishMoney(pd, sh, p);
	}

	std::string toString() const
	{
		return "( " + std::to_string(pound()) + "pd. " + std::to_string(shilling()) + "sh. " + std::to_string(penny()) + "p." + " )";
	}

	EnglishMoney operator+(const EnglishMoney& rhs) const
	{
		return EnglishMoney(0, 0, 0, m_semiPenny + rhs.m_semiPenny);
	}

	EnglishMoney operator-(const EnglishMoney& rhs) const
	{
		return EnglishMoney(0, 0, 0, m_semiPenny - rhs.m_semiPenny);
	}

	const EnglishMoney& operator+=(const EnglishMoney& rhs)
	{
		m_semiPenny += rhs.m_semiPenny;
		return *this;
	}

	const EnglishMoney& operator-=(const EnglishMoney& rhs)
	{
		m_semiPenny -= rhs.m_semiPenny;
		return *this;
	}

	EnglishMoney operator-() const
	{
		return EnglishMoney(0, 0, 0, -m_semiPenny);
	}

	bool operator==(const EnglishMoney& rhs) const
	{
		return (m_semiPenny == rhs.m_semiPenny);
	}

	bool operator>(const EnglishMoney& rhs) const
	{
		return (m_semiPenny > rhs.m_semiPenny);
	}

	bool operator<(const EnglishMoney& rhs) const
	{
		return (m_semiPenny < rhs.m_semiPenny);
	}

	bool operator<=(const EnglishMoney& rhs) const
	{
		return (m_semiPenny <= rhs.m_semiPenny);
	}

	bool operator>=(const EnglishMoney& rhs) const
	{
		return (m_semiPenny >= rhs.m_semiPenny);
	}

	bool operator!=(const EnglishMoney& rhs) const
	{
		return (m_semiPenny != rhs.m_semiPenny);
	}
};

int main()
{
	try {
		setlocale(LC_ALL, "Russian");

		std::map<bool, std::string> boolString{ {true,"true"},{false,"false"} };

		std::cout << "Enter the 1st balance: ";
		EnglishMoney m1 = EnglishMoney::input(std::cin);
		std::cout << "Enter the 2nd balance: ";
		EnglishMoney m2 = EnglishMoney::input(std::cin);

		EnglishMoney v = m1 + m2;
		std::cout << "\n" << m1.toString() << " + " << m2.toString() << " = " << v.toString();

		v = m1 - m2;
		std::cout << "\n" << m1.toString() << " - " << m2.toString() << " = " << v.toString();

		std::cout << "\n+=  " << (m1 += m2).toString();

		std::cout << "\n-=  " << (m1 -= m2).toString();

		std::cout << "\n"<< (-m1).toString() << (-m2).toString();

		std::cout << "\n\n" << m1.toString() << " > " << m2.toString() << " = " << boolString[m1 > m2];
		std::cout << "\n" << m1.toString() << " < " << m2.toString() << " = " << boolString[m1 < m2];
		std::cout << "\n" << m1.toString() << " >= " << m2.toString() << " = " << boolString[m1 >= m2];
		std::cout << "\n" << m1.toString() << " <= " << m2.toString() << " = " << boolString[m1 <= m2];
		std::cout << "\n" << m1.toString() << " != " << m2.toString() << " = " << boolString[m1 != m2];
		std::cout << "\n" << m1.toString() << " == " << m2.toString() << " = " << boolString[m1 == m2] << "\n";
	}
	catch (const MoneyException & e)
	{
		std::cout << e.what() << "\n";
		return -1;
	}
}

