#ifndef LABBONUS_REPOSITORY_H
#define LABBONUS_REPOSITORY_H
#include "Film.h"
#include <vector>
#include "Exception.h"
class Repository {
protected:
	static Film getFilmFromString(const std::string& filmString) {
		if (filmString.empty()) {
			return Film{};
		}
		std::string arrayOfParameters[5];
		int currentElem = 0;
		for (auto character: filmString) {
			if (character != ',') {
				arrayOfParameters[currentElem] += character;
			}else {
				currentElem++;
			}
		}
		return Film{arrayOfParameters[0], arrayOfParameters[1], std::stoi(arrayOfParameters[2]), std::stoi(arrayOfParameters[3]), arrayOfParameters[4]};
	}
public:
	virtual void addFilm(Film newFilm) = 0;
	virtual void removeFilm(std::string name) = 0;
	virtual void updateFilm(Film newFilm) = 0;
	virtual std::vector<Film> getAllFilms() = 0;
	virtual void openRepo() = 0;
	virtual ~Repository() = default;
	virtual Film getCurrent() = 0;
};


#endif //LABBONUS_REPOSITORY_H
