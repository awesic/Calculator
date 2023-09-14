#include "mainwindow.h"
#include "ui_mainwindow.h"


MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent), ui(new Ui::MainWindow) {
  ui->setupUi(this);

  connect(ui->pushButton_0, SIGNAL(released()), this, SLOT(digits_nums()));
  connect(ui->pushButton_1, SIGNAL(clicked()), this, SLOT(digits_nums()));
  connect(ui->pushButton_2, SIGNAL(clicked()), this, SLOT(digits_nums()));
  connect(ui->pushButton_3, SIGNAL(clicked()), this, SLOT(digits_nums()));
  connect(ui->pushButton_4, SIGNAL(clicked()), this, SLOT(digits_nums()));
  connect(ui->pushButton_5, SIGNAL(clicked()), this, SLOT(digits_nums()));
  connect(ui->pushButton_6, SIGNAL(clicked()), this, SLOT(digits_nums()));
  connect(ui->pushButton_7, SIGNAL(clicked()), this, SLOT(digits_nums()));
  connect(ui->pushButton_8, SIGNAL(clicked()), this, SLOT(digits_nums()));
  connect(ui->pushButton_9, SIGNAL(clicked()), this, SLOT(digits_nums()));

  connect(ui->pushButton_AC, SIGNAL(released()), this, SLOT(clean_res_show()));
  connect(ui->pushButton_comma, SIGNAL(released()), this, SLOT(digits_nums()));
  connect(ui->pushButton_acos, SIGNAL(released()), this, SLOT(digits_nums()));
  connect(ui->pushButton_asin, SIGNAL(released()), this, SLOT(digits_nums()));
  connect(ui->pushButton_atan, SIGNAL(released()), this, SLOT(digits_nums()));
  connect(ui->pushButton_sin, SIGNAL(released()), this, SLOT(digits_nums()));
  connect(ui->pushButton_cos, SIGNAL(released()), this, SLOT(digits_nums()));
  connect(ui->pushButton_tan, SIGNAL(released()), this, SLOT(digits_nums()));
  connect(ui->pushButton_div, SIGNAL(released()), this, SLOT(digits_nums()));
  connect(ui->pushButton_ln, SIGNAL(released()), this, SLOT(digits_nums()));
  connect(ui->pushButton_log, SIGNAL(released()), this, SLOT(digits_nums()));
  connect(ui->pushButton_minus, SIGNAL(released()), this, SLOT(digits_nums()));
  connect(ui->pushButton_mod, SIGNAL(released()), this, SLOT(digits_nums()));
  connect(ui->pushButton_mul, SIGNAL(released()), this, SLOT(digits_nums()));
  connect(ui->pushButton_plus, SIGNAL(released()), this, SLOT(digits_nums()));
  connect(ui->pushButton_pow, SIGNAL(released()), this, SLOT(digits_nums()));
  connect(ui->pushButton_sqrt, SIGNAL(released()), this, SLOT(digits_nums()));
  connect(ui->pushButton_brk_open, SIGNAL(released()), this,
          SLOT(digits_nums()));
  connect(ui->pushButton_brk_close, SIGNAL(released()), this,
          SLOT(digits_nums()));
  connect(ui->pushButton_x, SIGNAL(released()), this, SLOT(digits_nums()));
  connect(ui->pushButton_percent, SIGNAL(released()), this, SLOT(digits_nums()));

//  connect(ui->summa, SIGNAL(valueChanged(int)), ui->horizontalSlider, SLOT(setValue(int)));
//  connect(ui->horizontalSlider, SIGNAL(valueChanged(int)), ui->summa, SLOT(setValue(int)));

  connect(ui->summa, QOverload<int>::of(&QSpinBox::valueChanged), [=](int value) {
      ui->horizontalSlider->setValue(static_cast<int>(value));
  });
  connect(ui->horizontalSlider, &QSlider::valueChanged, [=](int value) {
      ui->summa->setValue(static_cast<int>(value));
  });

  connect(ui->summa_2, SIGNAL(valueChanged(int)), ui->horizontalSlider_2, SLOT(setValue(int)));
  connect(ui->horizontalSlider_2, SIGNAL(valueChanged(int)), ui->summa_2, SLOT(setValue(int)));
}

void MainWindow::clean_res_show() {
  _stringprint.clear();
  ui->result_show1->clear();
  ui->result_print->clear();
}

void MainWindow::digits_nums() {
  QPushButton *button = (QPushButton *)sender();
  QCursor cursor = ui->result_show1->cursor();

  //  functionCheck(button->text());

  ui->result_show1->setText(ui->result_show1->displayText() +
                            funcCheck(button->text()));

  ui->result_show1->setCursor(cursor);
}

MainWindow::~MainWindow() { delete ui; }

void MainWindow::on_pushButton_eq_released() {
  _stringprint = ui->result_show1->displayText();
  QByteArray str_bit = _stringprint.toLocal8Bit();
  char *res_str = str_bit.data();
  int check = validation(res_str);
  try {
      if (check == 1) {
          ui->result_print->setText("INVALID INPUT");
      } else if (check == -1) {
          ui->result_print->setText("DIVISION BY ZERO");
      } else {
          double x = ui->x_val->value();
          double result = calculation(res_str, x, &check);
          QString res = QString::number(result, 'g', 8);

          if (check)
              ui->result_print->setText("INVALID INPUT");
          else
              ui->result_print->setText(res);
      }
      _stringprint.clear();
      ui->x_val->setValue(0.0);
  } catch (const std::exception& e) {
      ui->result_print->setText(e.what());
  }
}

void MainWindow::on_pushButton_pi_released() {
  ui->result_show1->setText(ui->result_show1->displayText() +
                            (QString::number(PI, 'g', 8)));
}

void MainWindow::on_pushButton_bin_min_plus_clicked() {
  QCursor cursor = ui->result_show1->cursor();
  ui->result_show1->setText(ui->result_show1->displayText() + '-');
  ui->result_show1->setCursor(cursor);
}

void MainWindow::functionCheck(QString butText) {
  if (butText == "sin" || butText == "cos" || butText == "tan" ||
      butText == "asin" || butText == "acos" || butText == "atan" ||
      butText == "ln" || butText == "log") {
    _stringprint.push_back(butText + "(");
  } else if (butText == "√") {
    _stringprint.push_back("sqrt(");
  } else {
    _stringprint.push_back(butText);
  }
}

QString MainWindow::funcCheck(QString butText) {
  QString temp = "";
  if (butText == "sin" || butText == "cos" || butText == "tan" ||
      butText == "asin" || butText == "acos" || butText == "atan" ||
      butText == "ln" || butText == "log") {
    temp.push_back(butText + "(");
  } else if (butText == "√") {
    temp.push_back("sqrt(");
  } else if (butText == "÷") {
    temp.push_back("/");
  } else if (butText == "✕") {
    temp.push_back("*");
  } else {
    temp.push_back(butText);
  }

  return temp;
}

void MainWindow::on_pushButton_backspace_released()
{
  ui->result_show1->backspace();
}

void MainWindow::on_plot_button_released()
{
  _stringprint = ui->result_show1->displayText();
  QByteArray str_bit = _stringprint.toLocal8Bit();
  char *res_str = str_bit.data();
  int check = validation(res_str);
  try {
    if (check == 1) {
        ui->result_print->setText("INVALID INPUT");
    } else if (check == -1) {
        ui->result_print->setText("DIVISION BY ZERO");
    } else {
        PlotGraphic field;
//        std::pair<QVector<double>, QVector<double>> res = field.calculateForEachX(res_str, ui->x_max->value(), ui->x_min->value(), ui->y_max->value(), ui->y_min->value());
//        field.plotGraph(res, ui->x_max->value(), ui->x_min->value(), ui->y_max->value(), ui->y_min->value());
        field.plotGraph(res_str, ui->x_max->value(), ui->x_min->value(), ui->y_max->value(), ui->y_min->value());
        field.exec();
    }
    _stringprint.clear();
    ui->x_val->setValue(0.0);
    ui->x_max->setValue(5.0);
    ui->x_min->setValue(-5.0);
    ui->y_max->setValue(5.0);
    ui->y_min->setValue(-5.0);
  } catch (const std::exception& e) {
    ui->result_print->setText(e.what());
  }
}

void MainWindow::on_but_calculate_credit_released()
{
  char type = ui->annuity->isChecked() ? 'a' : 'd';
  Ui::CreditModel::Year_Month t_y_m = ui->year_month->currentText() == "year" ? Ui::CreditModel::Year_Month::YEARS : Ui::CreditModel::Year_Month::MONTH;
  Ui::CreditModel::Annu_Diff t_type = type == 'a' ? Ui::CreditModel::Annu_Diff::ANNUITY : Ui::CreditModel::Annu_Diff::DIFF;

  Ui::CreditModel::Result res = calculateCredit(t_type, (double)ui->summa->value(), (double)ui->term->value(), t_y_m, ui->interest_rate->value());

  ui->overpay->setText(QString::number(ceil(res.overPay * 100) / 100, 'f', 2));
  ui->totalpay->setText(QString::number(ceil(res.totalPay * 100) / 100, 'f', 2));

  if (t_type == Ui::CreditModel::Annu_Diff::ANNUITY) {
    //        double *arr = res.monthlyPay.data();
    //        for (int i = 0; i < term; ++i) {
    //            QTableWidgetItem *item = new QTableWidgetItem(arr[i]);
    //            ui->tableWidget->setItem(i, 2, item);
    //        }
    ui->monthly_pay->setText(QString::number(ceil(res.monthlyPay.front() * 100) / 100, 'f', 2));
  } else {
    ui->monthly_pay->setText(QString::number(ceil(res.monthlyPay.front() * 100) / 100, 'f', 2) + " ... " + QString::number(ceil(res.monthlyPay.back() * 100) / 100, 'f', 2));
  }
}

Ui::CreditModel::Result MainWindow::calculateCredit(Ui::CreditModel::Annu_Diff type, double amount, double term, Ui::CreditModel::Year_Month y_m, double interest) {
  Ui::CreditModel mod;
  return mod.calcCredit(type, amount, term, y_m, interest);
}

void MainWindow::on_but_calculate_deposit_released()
{
  Ui::DepositModel::TermType term_t = ui->year_month_2->currentText() == "year" ? Ui::DepositModel::TermType::YEARS : Ui::DepositModel::TermType::MONTH;
  Ui::DepositModel::PeriodicityType per_t = Ui::DepositModel::PeriodicityType::MONTH;
  if (ui->periodisity->currentText() == "once a quarter") per_t = Ui::DepositModel::PeriodicityType::QUARTER;
  if (ui->periodisity->currentText() == "every six months") per_t = Ui::DepositModel::PeriodicityType::SIXMONTH;
  if (ui->periodisity->currentText() == "once a year") per_t = Ui::DepositModel::PeriodicityType::YEAR;
  if (ui->periodisity->currentText() == "at the end of the term") per_t = Ui::DepositModel::PeriodicityType::END;

  Ui::DepositModel::Result res = calculateDeposit(ui->capitalizOf_interest->isChecked(), (double)ui->summa_2->value(), (double)ui->term_2->value(), term_t, per_t, ui->interest_rate_2->value(), ui->tax_rate->value());

  ui->tax_amount->setText(QString::number(ceil(res.taxAmount * 100) / 100, 'f', 2));
  ui->deposit_amount->setText(QString::number(ceil(res.depositAmount * 100) / 100, 'f', 2));
  ui->accrued_interest->setText(QString::number(ceil(res.accruedInterest * 100) / 100, 'f', 2));

//  if (ui->capitalizOf_interest->isChecked()) {
//    ui
//  }
}

Ui::DepositModel::Result MainWindow::calculateDeposit(bool capitalizInter, double amount, double term, Ui::DepositModel::TermType term_t, Ui::DepositModel::PeriodicityType period_t, double interest, double taxRate) {
  Ui::DepositModel mod;
  return mod.calcDeposit(capitalizInter, amount, term, term_t, period_t, interest, taxRate);
}
