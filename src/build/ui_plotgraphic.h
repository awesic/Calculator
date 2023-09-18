/********************************************************************************
** Form generated from reading UI file 'plotgraphic.ui'
**
** Created by: Qt User Interface Compiler version 6.5.2
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_PLOTGRAPHIC_H
#define UI_PLOTGRAPHIC_H

#include <QtCore/QVariant>
#include <QtWidgets/QApplication>
#include <QtWidgets/QDialog>

#include "../Calculator/QCustomPlotLib/qcustomplot.h"

QT_BEGIN_NAMESPACE

class Ui_PlotGraphic {
 public:
  QCustomPlot *widget;

  void setupUi(QDialog *PlotGraphic) {
    if (PlotGraphic->objectName().isEmpty())
      PlotGraphic->setObjectName("PlotGraphic");
    PlotGraphic->resize(652, 472);
    widget = new QCustomPlot(PlotGraphic);
    widget->setObjectName("widget");
    widget->setGeometry(QRect(9, 9, 631, 451));

    retranslateUi(PlotGraphic);

    QMetaObject::connectSlotsByName(PlotGraphic);
  }  // setupUi

  void retranslateUi(QDialog *PlotGraphic) {
    PlotGraphic->setWindowTitle(
        QCoreApplication::translate("PlotGraphic", "Graphic", nullptr));
  }  // retranslateUi
};

namespace Ui {
class PlotGraphic : public Ui_PlotGraphic {};
}  // namespace Ui

QT_END_NAMESPACE

#endif  // UI_PLOTGRAPHIC_H
