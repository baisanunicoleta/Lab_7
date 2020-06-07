#include <fstream>
#include "HTMLRepository.h"
#include <algorithm>

void HTMLRepository::openRepo() {
	std::string command = "open " + fileName;
	system(command.c_str());
}

void HTMLRepository::addFilm(Film newFilm) {
	auto array = readFile();
	for (const auto& film: array) {
		if (film.getName() == newFilm.getName()) {
			throw RepositoryException("Duplicate");
		}
	}
	array.push_back(newFilm);
	writeFile(array);
}

void HTMLRepository::removeFilm(std::string name) {
	auto array = readFile();
	auto elementToRemove = std::find_if(array.begin(), array.end(), [name](const Film& film) {
		return film.getName() == name;
	});
	if (elementToRemove == array.end()) {
		throw RepositoryException("Element does not exist");
	}else {
		array.erase(elementToRemove);
	}
	writeFile(array);
}

void HTMLRepository::updateFilm(Film newFilm) {
	auto array = readFile();
	for (auto& film: array) {
		if (film.getName() == newFilm.getName()) {
			film = newFilm;
			writeFile(array);
			return;
		}
	}
	throw RepositoryException("Element does not exist");
}

std::vector<Film> HTMLRepository::getAllFilms() {
	return readFile();
}

HTMLRepository::HTMLRepository(const std::string &path) : fileName(path) {
	std::ifstream checkIfFileExists(fileName);
	if (!checkIfFileExists) {
		std::ofstream createFileIfNotExist(fileName);
		createFileIfNotExist.close();
	}
	checkIfFileExists.close();
}

std::vector<Film> HTMLRepository::readFile() {
	std::ifstream fileIn(fileName);
	std::string htmlFileLine;
	int lineNumber = 0, index = 0;
	std::string stringFilm;
	std::vector<Film> array;
	std::string link;
	while (std::getline(fileIn, htmlFileLine, '<')) {
		if (!htmlFileLine.empty() and htmlFileLine != "\n") {
			stringFilm += htmlFileLine + ',';
			index++;
		}
		if (htmlFileLine == "\n") {
			if (lineNumber >= StartOfList) {
				auto positionLink = stringFilm.find(("Link"));
				stringFilm.replace(positionLink, positionLink + 3, link);
				Film film = getFilmFromString(stringFilm);
				array.push_back(film);
			}
			index = 0;
			lineNumber++;
			stringFilm = "";
			link = "";

		}
		std::getline(fileIn, htmlFileLine, '>');
		bool isLink = false;
		if (index == 4 and lineNumber >= StartOfList) {
			if (htmlFileLine.find("a href") != std::string::npos) {
				for (auto character: htmlFileLine) {
					if (character == '=') {
						isLink = true;
					}
					if (isLink) {
						link += character;
					}
				}
				link = link.substr(3);
				link.pop_back();

			}
		}
	}
	fileIn.close();
	return array;
}

void HTMLRepository::writeFile(std::vector<Film> array) {
	std::ofstream fileOut(fileName);
	fileOut << "<!DOCTYPE html><html><head><title>" << "Footage" << "</title></head>";
	fileOut << "<body><table border=\"1\">\n<tr><td>Title</td><td>Type</td><td>Date</td><td>Access Count</td><td>Link</td></tr>\n";
	for (const auto& film: array) {
		fileOut << "<tr><td>" << film.getName() << "</td><td>" << film.getGenre() << "</td><td>" << film.getYear() << "</td><td>" << film.getLikes();
		fileOut << "</td><td><a href = \"" << film.getLink() << "\">Link</a></td></tr>\n";
	}
	fileOut << "</table></body></html>";
	fileOut.close();
}

Film HTMLRepository::getCurrent() {
	if (currentElement == readFile().size()) {
		currentElement = 0;
	}
	return *(readFile().begin() + currentElement++);
}
