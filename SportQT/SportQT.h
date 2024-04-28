#include "user.h"
#include <QtWidgets/QMainWindow>
#include "ui_SportQT.h"

class SportQT : public QMainWindow
{
    Q_OBJECT
    user user;

public:
    SportQT(QWidget *parent = nullptr);
    ~SportQT();
    Ui::SportQTClass ui;
};
