#include <string>
#include <iostream>

void red(const std::string & s)
{ std::cout << "\033[1;31;40m"<< s << "\033[0m"; }
void green(const std::string & s)
{ std::cout << "\033[1;32;40m"<< s << "\033[0m"; }
void blue(const std::string & s)
{ std::cout << "\033[1;34;40m" << s << "\033[0m"; }
void yellow(const std::string & s)
{ std::cout << "\033[1;33;40m" << s << "\033[0m"; }
void cyan(const std::string & s)
{ std::cout << "\033[1;36;40m" << s << "\033[0m"; }
void purple(const std::string & s)
{ std::cout << "\033[1;35;40m" << s << "\033[0m"; }
void white(const std::string & s)
{ std::cout << "\033[1;37;40m" << s << "\033[0m"; }

void rednl(const std::string & s)
{ std::cout << "\033[1;31;40m"<< s << "\033[0m" << std::endl; }
void greennl(const std::string & s)
{ std::cout << "\033[1;32;40m"<< s << "\033[0m" << std::endl; }
void bluenl(const std::string & s)
{ std::cout << "\033[1;34;40m" << s << "\033[0m" << std::endl; }
void yellownl(const std::string & s)
{ std::cout << "\033[1;33;40m" << s << "\033[0m" << std::endl; }
void cyannl(const std::string & s)
{ std::cout << "\033[1;36;40m" << s << "\033[0m" << std::endl; }
void purplenl(const std::string & s)
{ std::cout << "\033[1;35;40m" << s << "\033[0m" << std::endl; }
void whitenl(const std::string & s)
{ std::cout << "\033[1;37;40m" << s << "\033[0m" << std::endl; }

bool less_than(int a, int b)
{ if (a < b) { return true; } else { return false; } }

bool uniqueness_sum_under10(int a, int b)
{ if (a + b < 10) { return true; } else { return false; } }

bool predicate_true_over_12(int a)
{ if (a >= 15) { return true; } else { return false; } }

void highlight(const std::string & s)
{
	yellownl("--------------------------------------------------------");
	int spacing = (55 - s.length()) / 2;
	while (spacing > 0) { std::cout << " "; --spacing; }
	yellownl(s);
	yellownl("--------------------------------------------------------");
}

