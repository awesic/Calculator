#include "plotgraphic.h"
#include "ui_plotgraphic.h"

PlotGraphic::PlotGraphic(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::PlotGraphic)
{
    ui->setupUi(this);
}

PlotGraphic::~PlotGraphic()
{
    delete ui;
}

//void PlotGraphic::plotGraph(std::pair<QVector<double>, QVector<double>> val, double x_max, double x_min, double y_max, double y_min) {
//    QPen pen;
//    pen.setColor(QColor(0, 0, 0));

//    ui->widget->addGraph();

//    ui->widget->xAxis->setRange(x_min, x_max);
//    ui->widget->yAxis->setRange(y_min, y_max);
////    ui->widget->addGraph()->setPen(pen);
////    ui->widget->graph(0)->setLineStyle((QCPGraph::LineStyle)5);
//    ui->widget->graph(0)->setScatterStyle(QCPScatterStyle(QCPScatterStyle::ssDisc, 4));
////    ui->widget->graph(0)->setScatterStyle(QCPScatterStyle(QCPScatterStyle::ssCircle, 2));
//    ui->widget->graph(0)->addData(val.first, val.second);
//    ui->widget->setInteraction(QCP::iRangeZoom, true);
//    ui->widget->setInteraction(QCP::iRangeDrag, true);
//    ui->widget->setBackground(QColor(235, 234, 230));
//    ui->widget->replot();
//}

std::pair<QVector<double>, QVector<double>> PlotGraphic::calculateForEachX(char *input_str, double x_max, double x_min, double y_max, double y_min) {
    std::pair<QVector<double>, QVector<double>> result;
    int check = 0;
    double x = x_min;
    try {
        while (x <= x_max) {
            double y = calculation(input_str, x, &check);
            if (y >= y_min && y <= y_max) {
                result.first.push_back(x);
                result.second.push_back(y);
            }
            x += 0.1;
        }
    } catch (std::exception& e) {
        throw;
    }
    return result;
}

void PlotGraphic::plotGraph(char *input_str, double x_max, double x_min, double y_max, double y_min) {
    std::pair<QVector<double>, QVector<double>> result;
    QPen pen;
    pen.setColor(QColor(0, 0, 0));
    int check = 0, graphCount = 0;
    double x = x_min;

    try {
        ui->widget->xAxis->setRange(x_min, x_max);
        ui->widget->yAxis->setRange(y_min, y_max);
        ui->widget->setInteraction(QCP::iRangeZoom, true);
        ui->widget->setInteraction(QCP::iRangeDrag, true);
        ui->widget->setBackground(QColor(235, 234, 230));
        for (; x <= x_max; x += 0.1) {
            double y = calculation(input_str, x, &check);
            if (isnormal(y) && y >= y_min && y <= y_max) {
                result.first.push_back(x);
                result.second.push_back(y);
            } else {
                ui->widget->addGraph();
                ui->widget->graph(graphCount)->setScatterStyle(QCPScatterStyle(QCPScatterStyle::ssDisc, 4));
                ui->widget->graph(graphCount)->addData(result.first, result.second);
                ++graphCount;
                result.first.clear();
                result.second.clear();
            }
        }
        ui->widget->addGraph();
        ui->widget->graph(graphCount)->setScatterStyle(QCPScatterStyle(QCPScatterStyle::ssDisc, 4));
        ui->widget->graph(graphCount)->addData(result.first, result.second);

        ui->widget->replot();
    } catch (std::exception& e) {
        throw;
    }
}

