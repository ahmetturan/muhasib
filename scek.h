#ifndef SCEK_H
#define SCEK_H

#include <QTableWidget>
#include <QHeaderView>
#include <QSqlQuery>
#include <QPushButton>
#include <QLabel>
#include <QDir>
#include <QComboBox>
#include <cekekle.h>

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
    int ckSutunSil;
    int ckSutunDegistir;
    int ckSutunTarih;
    int ckSutunIsim;
    int ckSutunBanka;
    int ckSutunTutar;
    int ckSutunMuhatap;
    int ckSutunCekNo;
    int ckSutunAciklama;
    int ckSutunTur;
    int ckSutunKayit;//kayit id sini tutuyor veritabanina kayitlimi diye. ikinci defa kaydetmesin.
    int ckSutunDegisim;//değiştirilen kayitlari tutmak için
    int ckSutunKilit;//kilit açık mı kapalı mı
};

#endif // SCEK_H
