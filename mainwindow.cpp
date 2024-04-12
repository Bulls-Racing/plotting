//
// Created by ahmee on 4/9/2024.
//

// You may need to build the project (run Qt uic code generator) to get "ui_Mainwindow.h" resolved

#include "mainwindow.h"
#include "ui_Mainwindow.h"

int count = 0;
int graph_page = 0;

enum page_table {brakes_general = 0,brakes_bias_cone = 6, susp_positions = 1,
            susp_hist = 2, tuning = 3, gps = 4};

main_window::main_window(QWidget *parent) :
        QWidget(parent), ui(new Ui::main_window) {
    ui->setupUi(this);

    //connect signals to slots
    connect(ui->pushButton_5, SIGNAL(clicked()), this, SLOT(set_page_to_brake_bias_cone()));
    connect(ui->outing_combobox, SIGNAL(currentIndexChanged(int)), this, SLOT(print_int(int)));
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
    my_bar->attachAxis(third_y);







}

void main_window::on_pushButton_clicked(){
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


void main_window::on_pushButton_2_clicked(){
    graph_page += 1;
    ui->chart_one->setChart(my_charts[graph_page % 3]);
}

void main_window::on_pushButton_3_clicked(){
    graph_page -= 1;
    ui->chart_one->setChart(my_charts[graph_page % 3]);

}
void main_window::on_pushButton_4_clicked(){
    ui->plot_container->setCurrentIndex(0);

}
void main_window::set_page_to_brake_bias_cone(){
    ui->plot_container->setCurrentIndex(brakes_bias_cone);
    qInfo("lol");

}
void main_window::print_int(int index) {
    qInfo() << std::to_string(index);
}

void main_window::set_page_to_brake_general() {
    ui->plot_container->setCurrentIndex(brakes_general);
    qInfo("lol");

}

void main_window::set_page_to_susp_pos() {
    ui->plot_container->setCurrentIndex(susp_positions);
    qInfo("lol");

}


void main_window::set_page_to_susp_his() {
    ui->plot_container->setCurrentIndex(2);
    qInfo("lol");

}
void main_window::set_page_to_tuning() {
    ui->plot_container->setCurrentIndex(1);
    qInfo("lol");

}
void main_window::set_page_to_gps() {
    ui->plot_container->setCurrentIndex(3);
    qInfo("lol");

}


main_window::~main_window() {
    delete ui;
}
