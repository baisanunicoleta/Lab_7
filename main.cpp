#include <QApplication>
#include "Service.h"
#include "GUI.h"
int main(int argc, char** argv) {
	QApplication application{argc, argv};
	Service service = Service{};
	GUI gui{service};
	gui.show();
	return application.exec();
}
