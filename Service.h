#ifndef LABBONUS_SERVICE_H
#define LABBONUS_SERVICE_H
#include "Repository.h"
#include "MemoryRepository.h"
#include "FileRepository.h"
#include "HTMLRepository.h"

class Service {
private:
	Repository* storage;
	Repository* myList;
public:
	Service();

	void addFilm(std::string title, std::string genre, int year, int likes, std::string link);
	void deleteFilm(std::string title);
	void updateFilm(std::string title, std::string genre, int year, int likes, std::string link);
	std::vector<Film> getAllFilms();
	void saveMyList(const std::string& name);
	std::vector<Film> getMyList();
	void setPath(const std::string& fileName, const std::string& repoName);
	Film getCurrentElement();
	std::vector<Film> getFilteredList(std::string genre);
	void openMyList();
	virtual ~Service();
};


#endif //LABBONUS_SERVICE_H
