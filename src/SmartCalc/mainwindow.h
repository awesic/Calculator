#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>

#include "creditmodel.h"
#include "depositmodel.h"
#include "plotgraphic.h"

#ifdef __cplusplus
extern "C" {
#endif

#include "smartcalc.h"
#include "validator.h"

#ifdef __cplusplus
}
#endif

QT_BEGIN_NAMESPACE
namespace Ui {
class MainWindow;
}
QT_END_NAMESPACE

class MainWindow : public QMainWindow {
  Q_OBJECT

 public:
  MainWindow(QWidget *parent = nullptr);
  QString _stringprint;
  Ui::CreditModel::Result calculateCredit(Ui::CreditModel::Annu_Diff type,
                                          double amount, double term,
                                          Ui::CreditModel::Year_Month y_m,
                                          double interest);
  Ui::DepositModel::Result calculateDeposit(
      bool capitalizInter, double amount, double term,
      Ui::DepositModel::TermType term_t,
      Ui::DepositModel::PeriodicityType period_t, double interest,
      double taxRate);
  ~MainWindow();

 private:
  Ui::MainWindow *ui;
  //  Grap *graphwin;
  //  QVector<double> x, y;

 private slots:
  void digits_nums();
  void clean_res_show();
  //  void on_pushButton_comma_clicked();
  void on_pushButton_bin_min_plus_clicked();
  void functionCheck(QString butText);
  QString funcCheck(QString butText);
  void on_pushButton_eq_released();
  void on_pushButton_pi_released();
  void on_pushButton_backspace_released();
  void on_plot_button_released();
  void on_but_calculate_credit_released();
  void on_but_calculate_deposit_released();
};
#endif  // MAINWINDOW_H
