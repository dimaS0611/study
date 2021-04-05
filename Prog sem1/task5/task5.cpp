#include <iostream>
#include <functional>
#include <cmath>

using func_y_x = std::function<double(double)>;
	
double integral_by_trapeze(double a, double b, int n, func_y_x func)
{
	double h = (b - a) / n;
	double sum_y = 0;

	for (int i = 1; i < n; ++i)
	{
		double x = a + (i * h);
		sum_y += func(x);
	}

	return h / 2 * (func(a) + 2 * sum_y + func(b));
}

double integral_by_trapeze_and_runge(double a, double b, int n, func_y_x func, double eps, int & loop)
{
	const double teta = 1.0 / 3.0;

	double In = integral_by_trapeze(a, b, n, func);

	loop = 0;
	for (int i = 0; i < 1000; ++i)
	{
		double In2 = integral_by_trapeze(a, b, n * 2, func);
		double err = teta * abs(In2 - In);

		if (err < eps)
			return In2;

		In = In2;
		n += n;
		loop++;
	}

	return In;
}

double func_1(double x)
{
	return x * atan(x);
}

double func_2(double x)
{
	return 1 / (1.0 + std::sqrt(x));
}

double func_3(double x)
{
	return 2 / (1 - 4 * x);
}

int main()
{
	setlocale(LC_ALL, "Russian");
	double eps = 0;
	int n = 0;
	std::cout << "¬ведите  количество шагов: ";
	std::cin >> n;
	std::cout << "¬ведите точность вычислений: ";
	std::cin >> eps;

	int loop = 0;

	double s1 = integral_by_trapeze_and_runge(0, 1.7, n, func_1, eps, loop);
	std::cout << "x*arctg(x) = " << s1 << "\n";
	std::cout << "loop1 = " << loop << "\n";

	double s2 = integral_by_trapeze_and_runge(0, 2, n, func_2, eps, loop);
	std::cout << "1/1*sqrt(x) = " << s2 << "\n";
	std::cout << "loop2 = " << loop << "\n";

	double s3 = integral_by_trapeze_and_runge(-2, -1.2, n, func_3, eps, loop);
	std::cout << "2/(1 - 4*x) = " << s3 << "\n";
	std::cout << "loop3 = " << loop << "\n";
}

