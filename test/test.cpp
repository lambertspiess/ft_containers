#include "test.hpp"

bool comp(int a, int b)
{
	if (a < b)
		return true;
	else
		return false;
}

bool uniqueness_sum_under10(int a, int b)
{
	if (a + b < 10)
		return true;
	else
		return false;
}

bool remove_over(int a)
{
	if (a >= 15)
		return true;
	else
		return false;
}

void title(const std::string& msg)
{
	std::cout << "\033[1;36;40m*******************************************" << std::endl;
	std::cout << "------------- \033[1;31;40m" <<msg << "\033[1;36;40m--------------" << std::endl;
	std::cout << "\033[1;36;40m*******************************************\033[0m" << std::endl;
}

void red(const std::string& msg)
{
	std::cout << "\033[1;31;40m"<< msg << "\033[0m" << std::endl;
}

void blue(const std::string& msg)
{
	std::cout << "\033[1;34;40m" << msg << "\033[0m" << std::endl;
}

void yellow(const std::string &msg)
{
	std::cout << "\033[1;33;40m" << msg << "\033[0m" << std::endl;
}

void cyan(const std::string &msg)
{
	std::cout << "\033[1;36;40m" << msg << "\033[0m" << std::endl;
}

void pink(const std::string& msg)
{
	std::cout << "\033[1;45;40m" << msg << "\033[0m" << std::endl;
}

void white(const std::string& msg)
{
	std::cout << "\033[1;37;40m" << msg << "\033[0m" << std::endl;
}
