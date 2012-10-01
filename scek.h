#ifndef SCEK_H
#define SCEK_H

#include <QTableWidget>
#include <QHeaderView>
#include <QSqlQuery>
#include <QPushButton>
#include <QLabel>
#include <QDir>
#include <QComboBox>
#include <QDateEdit>
#include "cekekle.h"
#include "degisken.h"

class scek
{
public:
    scek();
    void cekSil2(double &ToplamTutarCek, QStringList &listSilinenCek, bool &kaydetVar, QLabel *lblCek, QTableWidget* tblCek, QObject *obj);
    void cekDegistir2(bool& degisiklikIzle, bool &kaydetVar, QTableWidget *tblCek, QObject *obj);
    void cekKaydet2(QStringList &listSilinenCek, QTableWidget* tblCek);
    void ilkYukleme2(double &ToplamTutarCek, QTableWidget* tblCek, QTableWidget* tblAlinanCek, QTableWidget* tblVerilenCek, QWidget* tabCek, QWidget* tabCekOzeti, QWidget* &tbCek, QWidget* &tbCekOzeti, QTabWidget* tabWidget);

private:
    cekekle form_cekEkle;
    degisken dgs;
};

#endif // SCEK_H
