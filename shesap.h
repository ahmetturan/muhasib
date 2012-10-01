#ifndef SHESAP_H
#define SHESAP_H

#include <QTableWidget>
#include <QWidget>
#include <QTabWidget>
#include <QHeaderView>
#include <QPushButton>
#include <QComboBox>
#include <QDir>
#include <QSqlQuery>
#include "hesapekle.h"
#include "degisken.h"

class shesap
{
public:
    shesap();
    void ilkYukleme2(QTableWidget* tblHesap, QWidget* tabHesap, QWidget* &tbHesap, QTabWidget* tabWidget);
    void hesapKaydet2(QStringList &listSilinenHesap, QTableWidget *tblHesap);
    void hesapSil2(QStringList &listSilinenHesap, bool &kaydetVar, QTableWidget* tblHesap, QObject* obj);
    void hesapDegistir2(bool& degisiklikIzle, bool &kaydetVar, QTableWidget *tblHesap, QObject *obj);

private:
    hesapekle form_hesapEkle;
    degisken dgs;
};

#endif // SHESAP_H
