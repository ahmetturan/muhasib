#ifndef SMAAS_H
#define SMAAS_H

#include <QTableWidget>
#include <QWidget>
#include <QTabWidget>
#include <QHeaderView>
#include <QPushButton>
#include <QComboBox>
#include <QDir>
#include <QLabel>
#include <QSqlQuery>
#include <QDateEdit>
#include "eklemaas.h"
#include "degisken.h"

class smaas
{
public:
    smaas();
    void maasDegistir2(bool &degisiklikIzle, bool &kaydetVar, QTableWidget *tblMaas, QTableWidget* tblHesap, QTabWidget* tabWidget, QStringList listeHsp, QStringList listeClsn, int &kilidiAcikSatirSayisi, QObject *obj);
    void maasSil2(double &ToplamTutarMaas, QStringList &listSilinenMaas, bool &kaydetVar, QLabel *lblMaas, QTableWidget* tblMaas,QObject* obj);
    void maasKaydet2(QStringList &listSilinenMaas, QTableWidget *tblMaas);
    void ilkYukleme2(double &ToplamTutarMaas, QTableWidget* tblMaas, QWidget* tabMaas, QWidget* &tbMaas, QTabWidget* tabWidget);

private:
    maasekle form_maasEkle;
    degisken dgs;
    int clsSutunIsim;
};

#endif // SMAAS_H
