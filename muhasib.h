#ifndef MUHASIB_H
#define MUHASIB_H

#include <QMainWindow>
#include <QtSql>
#include <QMessageBox>
#include <QPushButton>
#include <QTableWidget>
#include <QWidgetAction>
#include <QCloseEvent>

#include "degisken.h"

#include "eklefatura.h"
#include "eklecek.h"
#include "eklemaas.h"
#include "eklecalisan.h"
#include "eklehesap.h"
#include "ekledigergelir.h"

#include "sfatura.h"
#include "scek.h"
#include "smaas.h"
#include "scalisan.h"
#include "shesap.h"
#include "srapor.h"
#include "sdigergelir.h"

#include "kistasfatura.h"
#include "kistasmaas.h"
#include "kistascek.h"
#include "kistascalisan.h"

namespace Ui {
class muhasib;
}

class muhasib : public QMainWindow
{
    Q_OBJECT
    
public:
    explicit muhasib(QWidget *parent = 0);
    Ui::muhasib *ui;
    ~muhasib();
    //fatura fonksiyonları
    void faturaVeritabanindanYukle();
    void faturaKaydet();
    void ilkYuklemeFatura();
    QString getFaturaKayitNo(int sonNo);
    ////////////////////////
    //cek fonksiyonları
    void cekKaydet();
    void cekVeritabanindanYukle();
    void ilkYuklemeCek();
    //////////////////////
    //maaş fonksiyonları
    void ilkYuklemeMaas();
    void maasVeritabanindanYukle();
    void maasKaydet();
    ///////////////////
    //calisan fonksiyonları
    void ilkYuklemeCalisan();
    void calisanVeritabanindanYukle();
    void calisanKaydet();
    /////////////////////
    //hesap fonksiyonları
    void ilkYuklemeHesaplar();
    void hesapVeritabanindanYukle();
    void hesapKaydet();
    ///////////////////////////7
    //rapor fonksiyonları
    void ggdCekYukle();
    /////////////////////////////////
    void veritabanindanYukle();
    void ilkYukleme();
    void ilkYuklemeBaslangic();
    void closeEvent(QCloseEvent *event);
    void pencereBoyutuKaydet();
    QStringList getListeHesap();
    QStringList getListeCalisan();

public slots:
    //fatura fonksiyonları
    void yeniFaturaEkle();
    void faturaSil();
    void sekmeFaturaAc();
    void sekmeFaturaOzetiAc();
    //void cbFaturaDegisti();
    void faturaDegistir();
    void faturaToplamiHesapla(int, int);
    void faturaTarihAl();
    void faturaTakvimAc();
    void faturaOzetiRaporla();
    void faturaOzetiRaporlaSonuc(QTableWidget *, QTableWidget *, QLabel *, QDate, QDate, QString);
    void faturaTutarHesapla(int,int);
    ////////////////////
    //çek fonksiyonları
    void yeniCekEkle();
    void sekmeCekAc();
    void sekmeCekOzetiAc();
    //void cbCekDegisti();
    void cekSil();
    void cekDegistir();
    void cekToplamiHesapla(int,int);
    void cekOzetiTarihAl();
    void cekOzetiTakvimAc();
    void cekOzetiRaporla();
    void cekOzetiRaporlaSonuc(QTableWidget *, QTableWidget *, QLabel *, QDate, QDate, QString);
    ///////////////////
    //maaş fonksiyonları
    void sekmeMaasAc();
    void yeniMaasEkle();
    void maasSil();
    void maasDegistir();
    //////////////////////
    //calisan fonksiyonları
    void sekmeCalisanAc();
    void yeniCalisanEkle();
    void calisanSil();
    void calisanDegistir();
    /////////////////////////
    //hesap fonksiyonları
    void yeniHesapEkle();
    void sekmeHesapAc();
    void hesapSil();
    void hesapDegistir();
    /////////////////////////
    //digergelir fonksiyonları
    void yeniDigerGelirEkle();
    /////////////////////////////
    //rapor fonksiyonları
    void sekmeGelirlerAc();
    void sekmeGiderlerAc();
    void sekmeGgdAc();
    void sekmeHesapOzetiAc();
    void hesapOzetiRaporla(int a);
    ////////////////////////
    void sekmeKapatildi(int);
    void kaydet();
    void kapat();
    void cbFaturaDegisti(int);
    void cbCekDegisti(int);
    void cbMaasDegisti(int);
    void cbCalisanDegisti(int);
    void cbRaporDegisti(int);
    void cbHesapDegisti(int);

    void kistasFaturaAc();
    void kistasMaasAc();
    void kistasCekAc();
    void kistasCalisanAc();

private:
    //fatura değişkenleri
    faturaEkle form_faturaEkle;
    double ToplamTutarFatura;
    int faturaNo;//son fatura no sunu tutacak
    QWidget *tbFatura;
    QWidget *tbFaturaOzeti;
    QStringList listSilinenFatura;
    ///////////////////////
    //çek degişkenleri
    cekekle form_cekEkle;
    double ToplamTutarCek;
    QWidget *tbCek;
    QWidget *tbCekOzeti;
    QStringList listSilinenCek;
    ////////////////////
    //maaş değişkenleri
    maasekle form_maasEkle;
    double ToplamTutarMaas;
    QWidget *tbMaas;
    QStringList listSilinenMaas;
    //////////////////////
    //calisan degiskenleri
    calisanekle form_calisanEkle;
    double ToplamTutarCalisan;
    QWidget *tbCalisan;
    QStringList listSilinenCalisan;
    /////////////////////////
    //hesap degiskenleri
    hesapekle form_hesapEkle;
    QWidget *tbHesap;
    QStringList listSilinenHesap;
    ///////////////////////////
    //diger gelir degiskenleri
    ekledigergelir form_digerGelirEkle;
    ///////////////////////////
    //rapor degiskenleri
    QWidget *tbGelirler;
    QWidget *tbGiderler;
    QWidget *tbGgd;
    QWidget *tbHesapOzeti;
    /////////////////////////////
    bool degisiklikIzle;//tblFatura değiştikçe toplamı yeniden hesaplamasın
    bool kaydetVar;
    int kilidiAcikSatirSayisi;
    scek sck;
    sFatura sftr;
    smaas sms;
    scalisan sclsn;
    shesap shsp;
    srapor srpr;
    sdigergelir sdgl;

    kistasfatura form_kistasFatura;
    kistasmaas form_kistasMaas;
    kistasCek form_kistasCek;
    kistascalisan form_kistasCalisan;
    degisken dgs;

};

#endif // MUHASIB_H
