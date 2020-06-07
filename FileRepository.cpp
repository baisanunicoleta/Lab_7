#include "FileRepository.h"
#include <iostream>
#include <algorithm>

void FileRepository::writeFile(std::vector<Film> filmsToWrite) {
	std::ofstream fileOut(fileName);
	for (auto film: filmsToWrite) {
		fileOut << film.toString()  << std::endl;
	}
}

std::vector<Film> FileRepository::readFile() {
	std::ifstream fileIn(fileName);
	std::string line;
	std::vector<Film> array;
	while (std::getline(fileIn, line)) {
		Film film = getFilmFromString(line);
		if (!film.getName().empty()) {
			array.push_back(film);
		}
	}
	return array;
}

void FileRepository::addFilm(Film newFilm) {
	auto array = readFile();
	for (const auto& film: array) {
		if (film.getName() == newFilm.getName()) {
			throw RepositoryException("Duplicate");
		}
	}
	array.push_back(newFilm);
	writeFile(array);
}

void FileRepository::removeFilm(std::string name) {
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

void FileRepository::updateFilm(Film newFilm) {
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

std::vector<Film> FileRepository::getAllFilms() {
	return readFile();
}

void FileRepository::openRepo() {
	std::string command = "open " + fileName;
	system(command.c_str());
}

FileRepository::FileRepository(const std::string &path) : fileName(path) {
	std::ifstream checkIfFileExists(fileName);
	if (!checkIfFileExists) {
		std::ofstream createFileIfNotExist(fileName);
		createFileIfNotExist.close();
	}
	checkIfFileExists.close();
}

Film FileRepository::getCurrent() {
	if (currentElement == readFile().size()) {
		currentElement = 0;
	}
	return *(readFile().begin() + currentElement++);
}


