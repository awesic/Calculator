#pragma once
#include <cmath>
#include <vector>

namespace Ui {

class CreditModel {
 public:
  enum class Annu_Diff { ANNUITY, DIFF };
  enum class Year_Month { MONTH, YEARS };
  class Result {
   public:
    Result() : monthlyPay(0.0), overPay(0.0), totalPay(0.0) {}
    std::vector<double> monthlyPay;
    double overPay;
    double totalPay;
  };

 public:
  CreditModel() {}
  Result calcCredit(Annu_Diff type, double amount, double term, Year_Month y_m,
                    double rate);

  ~CreditModel() {}

 private:
  Result calcCredit_Ann(double amount, double term, double rate);
  Result calcCredit_Dif(double amount, double term, double rate);
};
}  // namespace Ui
