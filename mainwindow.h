//
// Created by ahmee on 4/9/2024.
//

#ifndef PLOTTING_MAINWINDOW_H
#define PLOTTING_MAINWINDOW_H

#include <QWidget>
#include <QtCharts/QLineSeries>
#include <QtCharts/qchartview.h>
#include <QtCharts/QAbstractAxis>
#include <QtCharts/QValueAxis>
#include <QtCharts/QScatterSeries>
#include <QtCharts/QBarSeries>
#include <QtCharts/QBarSet>
#include <QtCharts/QBarCategoryAxis>
#include "QtWidgets"
#include "QThread"
#include <thread>
#include <chrono>

QT_BEGIN_NAMESPACE
namespace Ui { class Mainwindow; }
QT_END_NAMESPACE

class Mainwindow : public QWidget {
Q_OBJECT


public:
    explicit Mainwindow(QWidget *parent = nullptr);
    QLineSeries *first_line =  new QLineSeries();
    QChart *mychart = new QChart();
    QValueAxis *axisX = new QValueAxis();
    QValueAxis *axisY = new QValueAxis();

    QScatterSeries *my_scatter = new QScatterSeries();
    QChart *second_chart = new QChart();
    QValueAxis * second_X = new QValueAxis();
    QValueAxis * second_y = new QValueAxis();

    QBarSeries *my_bar = new QBarSeries();
    QChart *third_chart = new QChart();
    QBarCategoryAxis * third_X = new QBarCategoryAxis();
    QValueAxis * third_y = new QValueAxis();

    QChart *my_charts[3] = {mychart, second_chart,third_chart };


    ~Mainwindow() override;

private:
    Ui::Mainwindow *ui;

public slots:
    void on_pushButton_clicked();
    void on_pushButton_2_clicked();
    void on_pushButton_3_clicked();
    void on_pushButton_4_clicked();
    void set_page_to_brake_bias_cone();
    void print_int(int index);
    void set_page_to_brake_general();
    void set_page_to_susp_pos();

};


#endif //PLOTTING_MAINWINDOW_H
