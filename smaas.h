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
#include "maasekle.h"

class smaas
{
public:
    smaas();
    void maasDegistir2(bool &degisiklikIzle, bool &kaydetVar, QTableWidget *tblMaas, QStringList listeHsp, QStringList listeClsn, QObject *obj);
    void maasSil2(double &ToplamTutarMaas, QStringList &listSilinenMaas, bool &kaydetVar, QLabel *lblMaas, QTableWidget* tblMaas,QObject* obj);
    void maasKaydet2(QStringList &listSilinenMaas, QTableWidget *tblMaas);
    void ilkYukleme2(double &ToplamTutarMaas, QTableWidget* tblMaas, QWidget* tabMaas, QWidget* &tbMaas, QTabWidget* tabWidget);

private:
    maasekle form_maasEkle;
    int msSutunSil;
    int msSutunDegistir;
    int msSutunTarih;
    int msSutunCalisan;
    int msSutunMaas;
    int msSutunAy;
    int msSutunTur;
    int msSutunHesap;
    int msSutunKayit;//kayit id sini tutuyor veritabanina kayitlimi diye. ikinci defa kaydetmesin.
    int msSutunDegisim;//değiştirilen kayitlari tutmak için
    int msSutunKilit;//kilit açık mı kapalı mı
    int clsSutunIsim;
};

#endif // SMAAS_H
