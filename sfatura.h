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
#include "faturaekle.h"
#include "degisken.h"

class sFatura
{
public:
    sFatura();
    void faturaDegistir2(bool &degisiklikIzle, bool &kaydetVar, QTableWidget* tblFatura,  QTableWidget* tblHesap, QStringList listeHsp, QObject* obj);
    void faturaSil2(double &ToplamTutarFatura, QStringList &listSilinenFatura, bool &kaydetVar, QLabel *lblFatura, QTableWidget* tblFatura, QObject* obj);
    void faturaKaydet2(QStringList &listSilinenFatura,QTableWidget* tblFatura);
    void ilkYukleme2(double &ToplamTutarFatura, QTableWidget* tblFatura, QTableWidget* tblGelenFaturalar, QTableWidget* tblGidenFaturalar, QWidget* tabFatura, QWidget* tabFaturaOzeti, QWidget* &tbFatura, QWidget* &tbFaturaOzeti, QTabWidget* tabWidget);

private:
    faturaEkle form_faturaEkle;
    degisken dgs;
    /*
    int ftrSutunSil;
    int ftrSutunDegistir;
    int ftrSutunTarih;
    int ftrSutunIsim;
    int ftrSutunMatrah;
    int ftrSutunKdvOrani;
    int ftrSutunKdvTutar;
    int ftrSutunTutar;
    int ftrSutunAciklama;
    int ftrSutunTur;
    int ftrSutunHesap;
    int ftrSutunKayit;//kayit id sini tutuyor veritabanina kayitlimi diye. ikinci defa kaydetmesin.
    int ftrSutunDegisim;//değiştirilen kayitlari tutmak için
    int ftrSutunKilit;//kilit açık mı kapalı mı
    */
    double ToplamTutarFatura;
    //QWidget *tbFatura;
    //QWidget *tbFaturaOzeti;
    //QStringList listSilinenFatura;
};

#endif // SFATURA_H
