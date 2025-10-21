#include "ShrubberyCreationForm.hpp"
#include "Bureaucrat.hpp"

ShrubberyCreationForm::ShrubberyCreationForm() : AForm("ShrubberyCreationForm", 145, 137), _target("default")
{
}

ShrubberyCreationForm::ShrubberyCreationForm(const std::string &target) 
	: AForm("ShrubberyCreationForm", 145, 137), _target(target)
{
}

ShrubberyCreationForm::ShrubberyCreationForm(const ShrubberyCreationForm &other) 
	: AForm(other), _target(other._target)
{
}

ShrubberyCreationForm &ShrubberyCreationForm::operator=(const ShrubberyCreationForm &other)
{
	if (this != &other)
	{
		AForm::operator=(other);
		// _targetは定数なので代入できない
	}
	return *this;
}

ShrubberyCreationForm::~ShrubberyCreationForm()
{
}

const std::string &ShrubberyCreationForm::getTarget() const
{
	return this->_target;
}

void ShrubberyCreationForm::executeAction() const
{
	std::string filename = this->_target + "_shrubbery";
	std::ofstream file(filename.c_str());
	
	if (!file.is_open())
	{
		throw std::runtime_error("Could not create file");
	}

	file << "         v" << std::endl;
	file << "        >X<" << std::endl;
	file << "         A" << std::endl;
	file << "        d$b" << std::endl;
	file << "      .d\\$$b." << std::endl;
	file << "    .d$i$$\\$$b." << std::endl;
	file << "       d$$@b" << std::endl;
	file << "      d\\$$$ib" << std::endl;
	file << "    .d$$$\\$$$b" << std::endl;
	file << "  .d$$@$$$$\\$$ib." << std::endl;
	file << "      d$$i$$b" << std::endl;
	file << "     d\\$$$$@$b" << std::endl;
	file << "  .d$@$$\\$$$$$@b." << std::endl;
	file << ".d$$$$i$$$\\$$$$$$b." << std::endl;
	file << "        ###" << std::endl;
	file << "        ###" << std::endl;
	file << "        ###" << std::endl;
	file << std::endl;
	file << "      ccee88oo" << std::endl;
	file << "  C8O8O8Q8PoOb o8oo" << std::endl;
	file << " dOB69QO8PdUOpugoO9bD" << std::endl;
	file << "CgggbU8OU qOp qOdoUOdcb" << std::endl;
	file << "    6OuU  /p u gcoUodpP" << std::endl;
	file << "      \\\\//  /douUP" << std::endl;
	file << "        \\\\////" << std::endl;
	file << "         |||/\\" << std::endl;
	file << "         |||\\/\\" << std::endl;
	file << "         |||||\\" << std::endl;
	file << "   .....//||||\\....:" << std::endl;

	file.close();
}
