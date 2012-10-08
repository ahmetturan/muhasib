#ifndef SDIGERGIDER_H
#define SDIGERGIDER_H

#include <QTableWidget>
#include <QHeaderView>
#include <QPushButton>
#include <QLabel>
#include <QDateEdit>
#include <QSqlQuery>
#include "ekledigergider.h"
#include "degisken.h"

class sdigergider
{
public:
    sdigergider();
    void ilkYukleme(QTableWidget* tblDigerGider, QWidget* tabDigerGider, QWidget* &tbDigerGider, QTabWidget* tabWidget);
    void digerGiderDegistir(bool &degisiklikIzle, bool &kaydetVar, QTableWidget* tblDigerGider,  QTableWidget* tblHesap, QTabWidget* tabWidget, QStringList listeHsp, int &kilidiAcikSatirSayisi, QObject* obj);
    void digerGiderSil(QStringList &listSilinenDigerGider, bool &kaydetVar, QTableWidget* tblDigerGider, QObject* obj);
    void digerGiderKaydet(QStringList &listSilinenDigerGider,QTableWidget* tblDigerGider);

private:
    degisken dgs;
    ekledigergider form_ekleDigerGider;
};

#endif // SDIGERGIDER_H
