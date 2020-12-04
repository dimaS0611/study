#include <iostream>
#include <cmath>
#include <string>
#include <map>
#include <exception>
#include <istream>

class FractionException : public std::exception
{
	using base_t = std::exception;
public:
	FractionException()
		: base_t("Fraction: denominator == 0!")
	{}
};

long find_nod(long num, long den)
{
	num = abs(num);
	den = abs(den);

	while (num != 0 && den != 0)
		if (num > den)
			num %= den;
		else
			den %= num;

	return num + den;
}

class Fraction
{
	long m_numerator = 0;
	long m_denominator = 0;
	
	void init(long numerator, long denumenator)
	{
		if (denumenator == 0) {
			throw FractionException();
		}

		long nod = find_nod(numerator, denumenator);
		
		if (nod == 0) {
			throw "Fraction: nod == 0";
		}

		m_numerator = numerator / nod;
		m_denominator = denumenator / nod;

		if (value() > 0.0)
		{
			m_numerator = abs(m_numerator);
			m_denominator = abs(m_denominator);
		}
		else
		{
			m_numerator = -abs(m_numerator);
			m_denominator = abs(m_denominator);
		}
	}

public:
	Fraction(long numerator, long denominator)
	{ 
		init(numerator, denominator);
	}

	Fraction(const Fraction& rhs)
	{ 
		init(m_numerator, m_denominator);
		if (m_denominator == 0)
			throw "Fraction: denominator == 0!";
	}

	~Fraction() {}

	long numerator() const { return m_numerator; }
	void setNumerator(long value) { init(value, m_denominator); }

	long denominator() const { return m_denominator; }
	void setDenomimator(long value) { init(m_numerator, value); }

	double value() const
	{
		return static_cast<double>(m_numerator) / static_cast<double>(m_denominator);
	}

	Fraction operator+ (const Fraction& rhs) const
	{
		auto a1 = m_numerator, b1 = m_denominator, a2 = rhs.numerator(), b2 = rhs.denominator();
		return Fraction(a1 * b2 + a2 * b1, b1 * b2);
	}

	Fraction operator- (const Fraction& rhs) const
	{
		auto a1 = m_numerator, b1 = m_denominator, a2 = rhs.numerator(), b2 = rhs.denominator();
		return Fraction(a1 * b2 - a2 * b1, b1 * b2);
	}

	Fraction operator* (const Fraction& rhs) const
	{
		auto a1 = m_numerator, b1 = m_denominator, a2 = rhs.numerator(), b2 = rhs.denominator();
		return Fraction(a1 * a2, b1 * b2);
	}

	Fraction operator/ (const Fraction& rhs) const
	{
		auto a1 = m_numerator, b1 = m_denominator, a2 = rhs.numerator(), b2 = rhs.denominator();
		return Fraction(a1 * b2, a2 * b1);
	}

	Fraction operator- () const
	{
		return Fraction(-m_numerator, m_denominator);
	}

	bool operator==(const Fraction& rhs) const { return value() == rhs.value(); }

	bool operator!=(const Fraction& rhs) const { return value() != rhs.value(); }

	bool operator>(const Fraction& rhs) const { return value() > rhs.value(); }

	bool operator<(const Fraction& rhs) const { return value() < rhs.value(); }

	bool operator>=(const Fraction& rhs) const { return value() >= rhs.value(); }

	bool operator<=(const Fraction& rhs) const { return value() <= rhs.value(); }

	static Fraction input(std::istream & in)
	{
		long num, denum;
		
		in >> num >> denum;

		return Fraction(num, denum);
	}

	std::string toString() const
	{
		return "(" + std::to_string(m_numerator) + " / " + std::to_string(m_denominator) + ")";
	}
};

int main()
{

	setlocale(LC_ALL, "Russian");

	try {
		std::cout << "\n ¬ведите числитель, знаменатель дроби: \n";
		Fraction f1 = Fraction::input(std::cin);

		std::cout << "\n ¬ведите числитель, знаменатель дроби: \n";
		Fraction f2 = Fraction::input(std::cin);

		std::map<bool, std::string> boolString{ {false, "false"},{true, "true"} };

		Fraction v = f1 + f2;
		std::cout << "\n" << f1.toString() << " + " << f2.toString() << " = " << (f1 + f2).value() << "\n\n";

		v = f1 - f2;
		std::cout << f1.toString() << " - " << f2.toString() << " = " << v.value() << "\n\n";

		v = f1 * f2;
		std::cout << f1.toString() << " * " << f2.toString() << " = " << v.value() << "\n\n";

		std::cout << (-f1).value() << ", " << (-f2).value() << "\n\n";

		v = f1 / f2;
		std::cout << f1.toString() << " / " << f2.toString() << " = " << v.value() << "\n\n";

		std::cout << f1.toString() << " == " << f2.toString() << " = " << boolString[f1 == f2] << "\n\n";
		std::cout << f1.toString() << " >= " << f2.toString() << " = " << boolString[f1 >= f2] << "\n\n";
		std::cout << f1.toString() << " <= " << f2.toString() << " = " << boolString[f1 <= f2] << "\n\n";
		std::cout << f1.toString() << " > " << f2.toString() << " = " << boolString[f1 > f2] << "\n\n";
		std::cout << f1.toString() << " < " << f2.toString() << " = " << boolString[f1 < f2] << "\n\n";
		std::cout << f1.toString() << " != " << f2.toString() << " = " << boolString[f1 != f2] << "\n";
	}
	catch (const FractionException & e)
	{
		std::cout << e.what() << "\n";
		return -1;
	}
}