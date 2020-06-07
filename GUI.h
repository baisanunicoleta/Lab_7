#ifndef LABBONUS_GUI_H
#define LABBONUS_GUI_H
#include <QWidget>
#include "Service.h"
#include <QPushButton>
#include <QLineEdit>
#include <QTabWidget>
#include <QBoxLayout>
#include <QLabel>
#include <QFormLayout>
#include <QListWidget>
#include <QMessageBox>
class GUI: public QWidget {
private:
	Service service;

	//graphical elements
	QListWidget* filmsListWidget;
	QListWidget* filmsListWidgetB;
	QListWidget* myListWidget;
	QPushButton* addButton;
	QPushButton* removeButton;
	QPushButton* updateButton;
	QPushButton* setPathStorage;
	QPushButton* setPathMyList;
	QPushButton* setPathStorageB;
	QPushButton* setPathMyListB;
	QPushButton* saveMyList;
	QPushButton* next;
	QPushButton* openMyList;
	QPushButton* filterButton;

	QLineEdit* storageLineEdit;
	QLineEdit* myListLineEdit;
	QLineEdit* storageLineEditB;
	QLineEdit* myListLineEditB;
	QLineEdit* nameLineEdit;
	QLineEdit* genreLineEdit;
	QLineEdit* yearLineEdit;
	QLineEdit* likesLineEdit;
	QLineEdit* linkLineEdit;
	QLineEdit* filterGenreLineEdit;

	QTabWidget* tabWidget;


public:
	GUI(Service service1);
private:
	void initGUI();
	void makeConnections();
	int getSelectedFilm(QListWidget* listWidget);
	void setStorage();
	void setMyList();
	void populateList();
	void populateMyList(std::vector<Film>);
	void setStorageB();
	void setMyListB();
	void addFilm();
	void removeFilm();
	void updateFilm();
	void saveFilm();
	void nextFilm();
	void openList();
	void filterList();


};


#endif //LABBONUS_GUI_H
