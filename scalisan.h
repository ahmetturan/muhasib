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
#include <QDateEdit>
#include "calisanekle.h"
#include "degisken.h"

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
    degisken dgs;
};

#endif // SCALISAN_H
