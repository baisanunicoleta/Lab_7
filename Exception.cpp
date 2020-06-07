#include "Exception.h"


RepositoryException::RepositoryException(const std::string &error) {
	message = error;
}

const char *RepositoryException::what() {
	return message.c_str();
}

ValidatorException::ValidatorException(const std::string& error) {
	message = error;
}

const char *ValidatorException::what() {
	return message.c_str();
}
