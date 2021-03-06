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
#include "eklehesap.h"
#include "degisken.h"

class shesap
{
public:
    shesap();
    void ilkYukleme2(QTableWidget* tblHesap, QWidget* tabHesap, QWidget* &tbHesap, QTabWidget* tabWidget);
    void hesapKaydet2(QStringList &listSilinenHesap, QTableWidget *tblHesap);
    void hesapSil2(QStringList &listSilinenHesap, bool &kaydetVar, QTableWidget* tblHesap, QObject* obj);
    void hesapDegistir2(bool& degisiklikIzle, bool &kaydetVar, QTableWidget *tblFatura, QTableWidget *tblHesap, QTableWidget *tblDigerGelir, QTableWidget *tblDigerGider, QTableWidget *tblMaas, QTabWidget* tabWidget, int &kilidiAcikSatirSayisi, QObject *obj);

private:
    QString degisenHesap;//kayıtlardaki hesap değişkenini değiştirmek için
    QString yeniHesap;//yeni olusturulan hesap
    double degisenBaslangicMeblagi;//güncel meblagi değiştirmek için
    double yeniBaslangicMeblagi;//yeni olusturulan meblag
    QStringList listeMevcutHesaplar;
    hesapekle form_hesapEkle;
    degisken dgs;
};

#endif // SHESAP_H
