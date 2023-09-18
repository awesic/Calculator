#include "depositmodel.h"

namespace Ui {

DepositModel::Result DepositModel::calcDeposit(bool capitalizInter, double amount, double term, TermType term_t, PeriodicityType period_t, double interest, double taxRate) {
    Result res;
    if (term_t == TermType::YEARS) term *= 12.0;
    interest = interest / 100.0;

    if (capitalizInter == true) {
        res = calcDeposit_Capit(amount, term, period_t, interest, taxRate);
    } else {
        res = calcDeposit_NonCapit(amount, term, period_t, interest, taxRate);
    }
    return res;
}

DepositModel::Result DepositModel::calcDeposit_Capit(double amount,  double term, PeriodicityType period_t, double interest, double taxRate) {
    Result res;
    double tmp = amount;
    int period = 1;
    if (period_t == DepositModel::PeriodicityType::QUARTER) period *= 3;
    else if (period_t == DepositModel::PeriodicityType::SIXMONTH) period *= 6;
    else if (period_t == DepositModel::PeriodicityType::YEAR) period *= 12;

    for (int i{0}; i < term; i += period) {
        double tmp_month = 0;
//            tmp * interest * period;
        for (int j{0}; j < period && j < term; j++) {
            tmp_month += (tmp * interest * (j % 2 ? 31 : 30) / 365);
        }
        res.monthlyPay.push_back(tmp_month);
        tmp += tmp_month;
    }

    res.depositAmount = tmp;
    res.accruedInterest = tmp - amount;

    if (taxRate != 0.0) {
        double S0 = 1000000 * (KEY_RATE_CB / 100.0);
        if (res.accruedInterest > S0) {
            res.taxAmount = (res.accruedInterest - S0) * (taxRate / 100.0);
        } else {
            res.taxAmount = 0.0;
        }
    } else {
        res.taxAmount = 0.0;
    }

    return res;
}

DepositModel::Result DepositModel::calcDeposit_NonCapit(double amount,  double term, PeriodicityType period_t, double interest, double taxRate) {
    Result res;
    res.accruedInterest = interest * amount * term / 12.0;
    if (taxRate != 0.0) {
        double S0 = 1000000 * (KEY_RATE_CB / 100.0);
        if (res.accruedInterest > S0) {
            res.taxAmount = (res.accruedInterest - S0) * (taxRate / 100.0);
        } else {
            res.taxAmount = 0.0;
        }
    } else {
        res.taxAmount = 0.0;
    }
    res.depositAmount = res.accruedInterest + amount;

    return res;
}
}
