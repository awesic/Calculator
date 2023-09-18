#include <vector>
#define KEY_RATE_CB 12.0

namespace Ui {
class DepositModel {
 public:
  enum class TermType { YEARS, MONTH };
  enum class PeriodicityType { MONTH, QUARTER, SIXMONTH, YEAR, END };

  class Result {
   public:
    Result()
        : monthlyPay(0.0),
          accruedInterest(0.0),
          taxAmount(0.0),
          depositAmount(0.0) {}
    std::vector<double> monthlyPay;
    double accruedInterest;
    double taxAmount;
    double depositAmount;
  };

 public:
  DepositModel() {}
  Result calcDeposit(bool capitalizInter, double amount, double term,
                     TermType term_t, PeriodicityType period_t, double interest,
                     double taxRate);

  ~DepositModel() {}

 private:
  Result calcDeposit_Capit(double amount, double term, PeriodicityType period_t,
                           double interest, double taxRate);
  Result calcDeposit_NonCapit(double amount, double term,
                              PeriodicityType period_t, double interest,
                              double taxRate);
};
}  // namespace Ui
