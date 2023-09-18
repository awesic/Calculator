#ifndef PLOTGRAPHIC_H
#define PLOTGRAPHIC_H

#include <QDialog>
#include <QVector>
//#include <qcustomplot.h>
//#include "QCustomPlotLib/qcustomplot.h"

#ifdef __cplusplus
extern "C" {
#endif

#include "validator.h"

#ifdef __cplusplus
}
#endif

namespace Ui {
class PlotGraphic;
}

class PlotGraphic : public QDialog {
  Q_OBJECT

 public:
  explicit PlotGraphic(QWidget *parent = nullptr);
  std::pair<QVector<double>, QVector<double>> calculateForEachX(
      char *input_str, double x_max, double x_min, double y_max, double y_min);
  void plotGraph(char *input_str, double x_max,
                 double x_min, double y_max, double y_min);
  ~PlotGraphic();

 private:
  Ui::PlotGraphic *ui;
};

#endif  // PLOTGRAPHIC_H
