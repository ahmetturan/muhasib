#ifndef SFATURA_H
#define SFATURA_H

#include <QStringList>
#include <QPushButton>
#include <QTableWidget>
#include <QLabel>
#include <QSqlQuery>
#include <QHeaderView>
#include <QComboBox>
#include <QDir>
#include <QDateEdit>
#include "faturaekle.h"
#include "degisken.h"

class sFatura
{
public:
    sFatura();
    void faturaDegistir2(bool &kilitAcik, bool &degisiklikIzle, bool &kaydetVar, QTableWidget* tblFatura,  QTableWidget* tblHesap, QTabWidget* tabWidget, QStringList listeHsp, int &kilidiAcikSatirSayisi, QObject* obj);
    void faturaSil2(double &ToplamTutarFatura, QStringList &listSilinenFatura, bool &kaydetVar, QLabel *lblFatura, QTableWidget* tblFatura, QObject* obj);
    void faturaKaydet2(QStringList &listSilinenFatura,QTableWidget* tblFatura);
    void ilkYukleme2(double &ToplamTutarFatura, QTableWidget* tblFatura, QTableWidget* tblGelenFaturalar, QTableWidget* tblGidenFaturalar, QWidget* tabFatura, QWidget* tabFaturaOzeti, QWidget* &tbFatura, QWidget* &tbFaturaOzeti, QTabWidget* tabWidget);

private:
    faturaEkle form_faturaEkle;
    degisken dgs;
    double ToplamTutarFatura;
};

#endif // SFATURA_H
