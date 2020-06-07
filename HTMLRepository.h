#ifndef LABBONUS_HTMLREPOSITORY_H
#define LABBONUS_HTMLREPOSITORY_H
#include "Repository.h"
#define StartOfList 2
class HTMLRepository: public Repository {
private:
	std::string fileName;
	std::vector<Film> readFile();
	void writeFile(std::vector<Film> array);
	int currentElement = 0;
public:
	explicit HTMLRepository(const std::string &fileName);
	void addFilm(Film newFilm) override;
	void removeFilm(std::string name) override;
	void updateFilm(Film newFilm) override;
	std::vector<Film> getAllFilms() override;
	void openRepo() override;
	Film getCurrent() override;
};


#endif //LABBONUS_HTMLREPOSITORY_H
