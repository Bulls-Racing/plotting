//
// Created by ahmee on 4/9/2024.
//

// You may need to build the project (run Qt uic code generator) to get "ui_Mainwindow.h" resolved

#include "mainwindow.h"
#include "ui_Mainwindow.h"

int count = 0;
int graph_page = 0;

Mainwindow::Mainwindow(QWidget *parent) :
        QWidget(parent), ui(new Ui::Mainwindow) {
    ui->setupUi(this);

    //connect signals to slots
    connect(ui->pushButton_5, SIGNAL(clicked()), this, SLOT(set_page_to_brake_bias_cone()));
    connect(ui->comboBox, SIGNAL(currentIndexChanged(int)), this, SLOT(print_int(int)));
    connect(ui->pushButton_4, SIGNAL(clicked()), this, SLOT(set_page_to_brake_general()));
    connect(ui->pushButton_6, SIGNAL(clicked()), this, SLOT(set_page_to_susp_pos()));



    //setting up time series chart
    mychart->addSeries(first_line);
    mychart->setTitle("This is a line series chart");
    axisX->setMax(5);
    axisY->setMax(5);
    mychart->addAxis(axisX, Qt::AlignBottom);
    mychart->addAxis(axisY, Qt::AlignLeft);
    first_line->attachAxis(axisX);
    first_line->attachAxis(axisY);
    ui->chart_one->setChart(my_charts[graph_page]);

    //setting up scatter plot
    second_chart->addSeries(my_scatter);
    my_scatter->setMarkerShape(QScatterSeries::MarkerShapeCircle);
    my_scatter->setMarkerSize(10.0);
    my_scatter->append(5, 5);
    my_scatter->append(2, 2);
    my_scatter->append(2.1, 2.1);
    second_y->setMax(10);
    second_X->setMax(10);
    second_chart->addAxis(second_X, Qt::AlignBottom);
    second_chart->addAxis(second_y, Qt::AlignLeft);
    my_scatter->attachAxis(second_X);
    my_scatter->attachAxis(second_y);

    //setting up histogram
    QBarSet *first_set = new QBarSet("number one");
    QBarSet *second_set = new QBarSet("number two");
    *first_set << 1 << 2 ;
    *second_set << 3 << 4;
    my_bar->append(first_set);
    my_bar->append(second_set);
    third_chart->addSeries(my_bar);
    QStringList categories;
    categories << "Jan" << "Feb";
    third_X->append(categories);
    third_chart->addAxis(third_X, Qt::AlignBottom);
    my_bar->attachAxis(third_X);

    third_chart->addAxis(third_y, Qt::AlignLeft);
    my_bar->attachAxis(third_X);







}

void Mainwindow::on_pushButton_clicked(){
    QThread *my_thread = QThread::create([this] {
        while (true) {
            this->first_line->append(count, (count * count) + (2 * count) + 6);
            axisX->setMax(count + 1);
            axisY->setMax((count * count) + (2 * count) + 6);
            qInfo("");
            count++;
            if (count > 5){
                first_line->remove(0);
                double new_x = first_line->at(0).x();
                double new_y = first_line->at(0).y();
                axisX->setMin(new_x);
                axisY->setMin(new_y);
            }
            std::this_thread::sleep_for(std::chrono::seconds(1));

        }});
    my_thread->start();
    }


void Mainwindow::on_pushButton_2_clicked(){
    graph_page += 1;
    ui->chart_one->setChart(my_charts[graph_page % 3]);
}

void Mainwindow::on_pushButton_3_clicked(){
    graph_page -= 1;
    ui->chart_one->setChart(my_charts[graph_page % 3]);

}
void Mainwindow::on_pushButton_4_clicked(){
    ui->stackedWidget->setCurrentIndex(0);

}
void Mainwindow::set_page_to_brake_bias_cone(){
    ui->stackedWidget->setCurrentIndex(5);
    qInfo("lol");

}
void Mainwindow::print_int(int index) {
    qInfo() << std::to_string(index);
}

void Mainwindow::set_page_to_brake_general() {
    ui->stackedWidget->setCurrentIndex(0);
    qInfo("lol");

}

void Mainwindow::set_page_to_susp_pos() {
    ui->stackedWidget->setCurrentIndex(1);
    qInfo("lol");

}


Mainwindow::~Mainwindow() {
    delete ui;
}
