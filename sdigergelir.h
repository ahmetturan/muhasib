#ifndef SDIGERGELIR_H
#define SDIGERGELIR_H

#include <QTableWidget>
#include <QHeaderView>
#include <QPushButton>
#include <QLabel>
#include <QDateEdit>
#include <QSqlQuery>
#include "ekledigergelir.h"
#include "degisken.h"

class sdigergelir
{
public:
    sdigergelir();
    void ilkYukleme(QTableWidget* tblDigerGelir, QWidget* tabDigerGelir, QWidget* &tbDigerGelir, QTabWidget* tabWidget);
    void digerGelirDegistir(bool &degisiklikIzle, bool &kaydetVar, QTableWidget* tblDigerGelir,  QTableWidget* tblHesap, QTabWidget* tabWidget, QStringList listeHsp, int &kilidiAcikSatirSayisi, QObject* obj);
    void digerGelirSil(QStringList &listSilinenDigerGelir, bool &kaydetVar, QTableWidget* tblDigerGelir, QObject* obj);
    void digerGelirKaydet(QStringList &listSilinenDigerGelir,QTableWidget* tblDigerGelir);

private:
    degisken dgs;
    ekledigergelir form_ekleDigerGelir;
};

#endif // SDIGERGELIR_H
