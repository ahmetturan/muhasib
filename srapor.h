#ifndef SRAPOR_H
#define SRAPOR_H

#include <QTableWidgetItem>
#include <QHeaderView>
#include <QComboBox>
#include "degisken.h"

class srapor
{
public:
    srapor();
    void giderleriYukle(QTableWidget* tblGiderler, QTableWidget* tblFatura, QTableWidget* tblCek, QTableWidget* tblMaas, QTableWidget *tblDigerGider);
    void gelirleriYukle(QTableWidget* tblGelirler, QTableWidget* tblFatura, QTableWidget* tblCek, QTableWidget *tblDigerGelir);
    void ggdFaturaYukle(QTableWidget *tblGgd, QTableWidget *tblFatura);
    void ggdMaasYukle(QTableWidget *tblGgd, QTableWidget *tblMaas);
    void ggdToplamiYukle(QTableWidget *tblGgd);
    void ggdDigerYukle(QTableWidget *tblGgd, QTableWidget *tblDigerGelir, QTableWidget *tblDigerGider);
    void ggdItem(QTableWidgetItem *itm);
    void ggdYukle(QTableWidget *tblGgd, QTableWidget *tblFatura, QTableWidget *tblMaas, QTableWidget *tblGelir, QTableWidget *tblGider);
    void hesapOzetiRaporlaFatura(QTableWidget *tblFatura, QTableWidget *tblHesapOzeti, QComboBox *cbHesapOzeti);
    void hesapOzetiRaporlaMaas(QTableWidget *tblMaas, QTableWidget *tblHesapOzeti, QComboBox *cbHesapOzeti);
    void hesapOzetiRaporlaDigerGelir(QTableWidget *tblDigerGelir, QTableWidget *tblHesapOzeti, QComboBox *cbHesapOzeti);
    void hesapOzetiRaporlaDigerGider(QTableWidget *tblDigerGider, QTableWidget *tblHesapOzeti, QComboBox *cbHesapOzeti);
    void ilkYuklemeGiderler(QTableWidget* tblGiderler, QWidget* tabGiderler, QWidget* &tbGiderler, QTabWidget* tabWidget);
    void ilkYuklemeGelirler(QTableWidget* tblGelirler, QWidget* tabGelirler, QWidget* &tbGelirler, QTabWidget* tabWidget);
    void ilkYuklemeGgd(QTableWidget* tblGgd, QWidget* tabGgd, QWidget* &tbGgd, QTabWidget* tabWidget);
    void ilkYuklemeHesapOzeti(QTableWidget* tblHesapOzeti, QWidget* tabHesapOzeti, QWidget* &tbHesapOzeti, QTabWidget* tabWidget);

private:
    degisken dgs;
};

#endif // SRAPOR_H
