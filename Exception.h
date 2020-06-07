#ifndef LABBONUS_EXCEPTION_H
#define LABBONUS_EXCEPTION_H
#include <exception>
#include <string>
#include <utility>

class Exception: public std::exception {
protected:
	std::string message{};
public:
	virtual const char* what() = 0;
};

class RepositoryException: public Exception {
public:
	explicit RepositoryException(const std::string& error);
	const char * what() override;
};

class ValidatorException: public Exception {
public:
	ValidatorException(const std::string& error);
	const char *what() override;
};


#endif //LABBONUS_EXCEPTION_H
