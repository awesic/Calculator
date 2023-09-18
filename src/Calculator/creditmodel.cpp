#include "creditmodel.h"

namespace Ui {
CreditModel::Result CreditModel::calcCredit(Annu_Diff type, double amount, double term, Year_Month y_m, double rate) {
    Result res;
    if (y_m == Year_Month::YEARS) term *= 12.0;
    rate = (rate / 100.0) / 12.0;

    if (type == Annu_Diff::ANNUITY) {
        res = calcCredit_Ann(amount, term, rate);
    } else {
        res = calcCredit_Dif(amount, term, rate);
    }
    return res;
}

CreditModel::Result CreditModel::calcCredit_Ann(double amount, double term, double rate) {
    Result res;
    res.monthlyPay.push_back(amount * (rate + rate / (pow((1 + rate), term) - 1)));
    res.totalPay = res.monthlyPay.front() * term;
    res.overPay = res.totalPay - amount;

    return res;
}

CreditModel::Result CreditModel::calcCredit_Dif(double amount, double term, double rate) {
    Result res;
    double month_pay_const = amount / term;
    double remaining_debt = amount;
    do {
        res.monthlyPay.push_back(month_pay_const + remaining_debt * rate);
        res.totalPay += res.monthlyPay.back();
        remaining_debt -= month_pay_const;
    } while (fabs(remaining_debt) > 1e-2);
    res.overPay = res.totalPay - amount;

    return res;
}
}
