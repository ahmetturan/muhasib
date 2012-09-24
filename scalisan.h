#ifndef SCALISAN_H
#define SCALISAN_H

#include <QTableWidget>
#include <QWidget>
#include <QTabWidget>
#include <QTableWidget>
#include <QHeaderView>
#include <QPushButton>
#include <QDir>
#include <QComboBox>
#include <QLabel>
#include <QSqlQuery>
#include "calisanekle.h"

class scalisan
{
public:
    scalisan();
    void calisanKaydet2(QStringList &listSilinenCalisan, QTableWidget* tblCalisan);
    void calisanSil2(double &ToplamTutarCalisan, QStringList &listSilinenCalisan, bool &kaydetVar, QLabel *lblCalisan, QTableWidget* tblCalisan, QObject *obj);
    void calisanDegistir2(bool &degisiklikIzle, bool &kaydetVar, QTableWidget *tblCalisan, QObject *obj);
    void ilkYukleme2(double &ToplamTutarCalisan, QTableWidget* tblCalisan, QWidget* tabCalisan, QWidget* &tbCalisan, QTabWidget* tabWidget);

private:
    calisanekle form_calisanEkle;
    int clsSutunSil;
    int clsSutunDegistir;
    int clsSutunIsim;
    int clsSutunKonum;
    int clsSutunIseGiris;
    int clsSutunMaas;
    int clsSutunAciklama;
    int clsSutunKayit;//kayit id sini tutuyor veritabanina kayitlimi diye. ikinci defa kaydetmesin.
    int clsSutunDegisim;//değiştirilen kayitlari tutmak için
    int clsSutunKilit;//kilit açık mı kapalı mı
};

#endif // SCALISAN_H
