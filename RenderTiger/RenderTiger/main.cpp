#include "render_tiger_main_window.h"
#include <QtWidgets/QApplication>

int main(int argc, char *argv[]) {
    QApplication a(argc, argv);
    render_tiger_main_window w;
    w.show();
    return a.exec();
}
