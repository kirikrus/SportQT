#include "SportQT.h"
#include <QtWidgets/QApplication>
#include <QSqlQuery>
#include <QSqlDatabase>

void onLoad(Ui::SportQTClass *ui) {
    QWidget* widget;
    QLabel* label_2;
    QLabel* label_3;
    QLabel* label_4;
    QLabel* label_5;
    QPushButton* pushButton_2;
    
    QSqlQuery query;
    query.exec("SELECT * FROM Exercises");

    int i{ 0 }, j{0};

    while (query.next()) {
        QString id = query.value("id").toString();
        QString photoPath = query.value("photo_path").toString();
        QString name = query.value("name").toString();

        QSqlQuery tag_query;
        tag_query.exec("SELECT MuscleGroups.name FROM MuscleGroups "
            "INNER JOIN ExerciseMuscleGroups ON MuscleGroups.id = ExerciseMuscleGroups.muscle_group_id "
            "WHERE ExerciseMuscleGroups.exercise_id = " + id);
        tag_query.next();
        QString tag1 = tag_query.value("name").toString();
        tag_query.next();
        QString tag2 = tag_query.value("name").toString();
        
        widget = new QWidget(ui->scrollAreaWidgetContents_2);
        widget->setEnabled(true);
        widget->setMinimumSize(QSize(111, 131));
        widget->setMaximumSize(QSize(111, 131));
        widget->setStyleSheet(QString::fromUtf8("border-radius: 20px;\n"
            "background-color: rgb(254, 254, 254);"));
        label_2 = new QLabel(widget);
        label_2->setGeometry(QRect(0, 20, 111, 71));
        label_2->setPixmap(QPixmap(":/gif/gif/" + photoPath));//фото
        label_2->setScaledContents(true);
        label_3 = new QLabel(widget);
        label_3->setGeometry(QRect(10, 90, 91, 16));
        QFont font2;
        font2.setBold(true);
        label_3->setFont(font2);
        label_3->setText(name);
        label_4 = new QLabel(widget);
        label_4->setGeometry(QRect(10, 110, 41, 16));
        label_4->setStyleSheet(QString::fromUtf8("background-color: rgb(255, 173, 156);\n"
            "border-radius: 5px;"));
        label_4->setText(tag1);
        label_5 = new QLabel(widget);
        label_5->setGeometry(QRect(60, 110, 41, 16));
        label_5->setStyleSheet(QString::fromUtf8("background-color: rgb(255, 173, 156);\n"
            "border-radius: 5px;"));
        label_5->setText(tag2);
        pushButton_2 = new QPushButton(widget);
        pushButton_2->setGeometry(QRect(0, 0, 111, 131));
        pushButton_2->setStyleSheet(QString::fromUtf8("background-color: transparent;\n"
            "border: none;"));

        QObject::connect(pushButton_2, &QPushButton::clicked, []() {
            // Ваш код обработки события клика на метке
            });

        ui->gridLayout->addWidget(widget, j, i++, 1, 1);
        
        if (i == 3) {
            i = 0;
            j++;
        }
    }
}

int main(int argc, char *argv[])
{
    QSqlDatabase db = QSqlDatabase::addDatabase("QSQLITE");
    db.setDatabaseName("sportDB.db");

    if (!db.open()) {
        qDebug() << "Ошибка при открытии базы данных";
        return -1;
    }

    QApplication a(argc, argv);
    SportQT w;

    onLoad(&w.ui);
    w.show();
    return a.exec();
}
