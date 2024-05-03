#include "SportQT.h"
#include <QtWidgets/QApplication>
#include <QSqlQuery>
#include <QSqlDatabase>
#include <qmovie.h>
#include <QMessageBox>

/*
Функциональные требования к программе:
1. Перечень тренировок. Создать список всех тренировок, где для каждой тренировки можно просматривать и редактировать информацию.
2. Копирование предыдущей тренировки. Реализовать функцию копирования предыдущей тренировки при создании новой, с отображением полной информации о ней и предложением нового веса для каждого упражнения в зависимости от количества подходов:
    1 подход - 55% от максимального веса на последнем подходе + 1 кг/0,5 кг
    2 подход - от 65% до 70% от максимального веса на последнем подходе + 1 кг/0,5 кг
    3 подход - 100% от максимального веса на последнем подходе + 1 кг/0,5 кг
    Если подходов было больше, предложить разбить вес пропорционально, начиная с 55% от максимального веса последнего подхода (или свой вариант).
3. Встроенная программа из 2 лабораторной работы. Интегрировать программу, которая при нажатии на вес упражнения с гантелей или штангой выдает предложение о том, как собрать данный вес.
4. База упражнений. База данных упражнений, где можно добавлять, редактировать и удалять упражнения, включая информацию о мышцах, которые задействованы, и типе упражнения (например, силовое, кардио и т.д.).
5. Информация о прогрессе по сравнению двух предыдущих тренировок.
    Например, если пользователь выполнил тренировку с весом 50 кг, 3 подхода и 8 повторениями, а затем выполнил тренировку с весом 55 кг, 3 подхода и 10 повторениями, то программа может рассчитать прогресс следующим образом:
    Увеличение веса: 55 кг - 50 кг = 5 кг (10% прирост).
    Увеличение количества повторений: 10 повторений - 8 повторений = 2 повторения (25% прирост).
    Увеличение общей нагрузки:
    (55 кг x 3 подхода x 10 повторений) - (50 кг x 3 подхода x 8 повторений) = 150 кг (25% прирост).*/

void copy_paste() {}

void apprInfo(quint16 approach_count, quint16 max_weight) {
    quint16 proc = static_cast<quint16>(45 / (approach_count-1));
    quint16 cur_proc = 55;
    quint16 weight;

    QString message;

    for (int i = 0; i < approach_count; i++) {
        weight = cur_proc * max_weight / 100;
        cur_proc += proc;
        message += "Approach " + QString::number(i + 1) + ": " + QString::number(weight) + " kg\n";
    }

    QMessageBox::information(nullptr, "Approach INFO: ", message);
}

void weightInfo(quint16 max_weight) {
    quint16 tmp = max_weight;
    quint16 out{0};
    QString message;

    QSqlQuery query;
    query.exec("SELECT weight, count FROM BarbellPlates");

    while (query.next()) {
        int weight = query.value("weight").toInt();
        int count = query.value("count").toInt();
        int count_tmp{0};

        while (count > 1 && tmp > weight * 2) {
            tmp -= 2 * weight;
            count_tmp += 2;
            count -= 2;
        }
        
        out += weight * count_tmp;

        message += "Weight: " + QString::number(weight) + "kg, Count: " + QString::number(count_tmp) + "\n";
    }
    message += "Out: " + QString::number(out) + "kg";

    QMessageBox::information(nullptr, "Plates INFO: ", message);
}

void infoShow(Ui::SportQTClass* ui, QString id) {
    QSqlQuery query;
    query.exec("SELECT * FROM Exercises WHERE id = " + id);
    query.next();

    QString desc = query.value("description").toString();
    QString photoPath = query.value("photo_path").toString();
    QString name = query.value("name").toString();

    QMovie* movie = new QMovie(":/gif/gif/" + photoPath);
    ui->label_2->setMovie(movie);
    movie->start();
    ui->label_3->setText(name);
    ui->label_5->setText(desc);

    query.exec("SELECT MuscleGroups.name FROM MuscleGroups "
        "INNER JOIN ExerciseMuscleGroups ON MuscleGroups.id = ExerciseMuscleGroups.muscle_group_id "
        "WHERE ExerciseMuscleGroups.exercise_id = " + id);
    
    QLayoutItem* item;
    while ((item = ui->horizontalLayout->takeAt(0)) != nullptr) {
        if (item->widget()) item->widget()->deleteLater();
        delete item;
    }    
    
    while (query.next()) {
        QString tag1 = query.value("name").toString();

        auto tag = new QLabel();
        tag->setGeometry(QRect(10, 110, 41, 16));
        tag->setStyleSheet(QString::fromUtf8("background-color: rgb(255, 173, 156);\n"
            "border-radius: 5px;"));
        tag->setText(tag1);
        tag->setAlignment(Qt::AlignCenter);

        ui->horizontalLayout->addWidget(tag);
    }

    QObject::connect(ui->back, &QPushButton::clicked, [=]() {
        movie->stop();
        ui->tabWidget->setCurrentIndex(0);
        });
}

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

        QObject::connect(pushButton_2, &QPushButton::clicked, [=]() {
            ui->tabWidget->setCurrentIndex(1);
            infoShow(ui, id);
            });

        ui->gridLayout->addWidget(widget, j, i++, 1, 1);
        
        if (i == 3) {
            i = 0;
            j++;
        }
    }
    QObject::connect(ui->start, &QPushButton::clicked, [=]() {
        apprInfo(ui->podhod->text().toInt(), ui->weight->text().toInt());
        });
    QObject::connect(ui->startCalc, &QPushButton::clicked, [=]() {
        weightInfo(ui->weight->text().toInt());
        });
}

void userLoad(Ui::SportQTClass *ui, user *user) {
    QWidget* widget;
    QLabel* img;
    QLabel* text;
    QPushButton* progress;
    QPushButton* copy;
    QPushButton* delete_2;

    widget = new QWidget(ui->scrollAreaWidgetContents);
    widget->setObjectName(QString::fromUtf8("widget"));
    widget->setGeometry(QRect(10, 30, 381, 80));
    widget->setMinimumSize(QSize(381, 80));
    widget->setMaximumSize(QSize(16777215, 80));
    widget->setStyleSheet(QString::fromUtf8("background-color: rgb(70, 70, 70);"));
    img = new QLabel(widget);
    img->setObjectName(QString::fromUtf8("img"));
    img->setGeometry(QRect(-10, 0, 121, 91));
    img->setPixmap(QPixmap(QString::fromUtf8(":/gif/gif/Francuzsckij_zhim_lezha_so_shtangoj.gif")));
    img->setScaledContents(true);
    text = new QLabel(widget);
    text->setObjectName(QString::fromUtf8("text"));
    text->setGeometry(QRect(120, 10, 261, 21));
    text->setMinimumSize(QSize(0, 0));
    QFont font2;
    font2.setFamilies({ QString::fromUtf8("Impact") });
    font2.setPointSize(16);
    text->setFont(font2);
    text->setStyleSheet(QString::fromUtf8("color: rgb(255, 255, 255);\n"
        "background-color: rgba(255, 255, 255, 0);"));
    progress = new QPushButton(widget);
    progress->setObjectName(QString::fromUtf8("progress"));
    progress->setGeometry(QRect(130, 40, 71, 31));
    progress->setStyleSheet(QString::fromUtf8("background-color: transparent;\n"
        "color: white;\n"
        "border-radius: 10px; \n"
        "border: 1px solid rgb(250, 255, 156);"));
    copy = new QPushButton(widget);
    copy->setObjectName(QString::fromUtf8("copy"));
    copy->setGeometry(QRect(210, 40, 71, 31));
    copy->setStyleSheet(QString::fromUtf8("background-color: transparent;\n"
        "color: white;\n"
        "border-radius: 10px; \n"
        "border: 1px solid rgb(250, 255, 156);"));
    delete_2 = new QPushButton(widget);
    delete_2->setObjectName(QString::fromUtf8("delete_2"));
    delete_2->setGeometry(QRect(290, 40, 71, 31));
    delete_2->setStyleSheet(QString::fromUtf8("background-color: transparent;\n"
        "color: white;\n"
        "border-radius: 10px; \n"
        "border: 1px solid rgb(250, 255, 156);"));
    ui->verticalLayout->addWidget(widget);
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

    user user;
    userLoad(&w.ui, &user);

    onLoad(&w.ui);
    w.show();
    return a.exec();
}
