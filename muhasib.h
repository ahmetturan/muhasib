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
#include "sdigergider.h"

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
    void faturaVeritabanindanYukle();
    QString getFaturaKayitNo(int sonNo);
    void cekVeritabanindanYukle();
    void maasVeritabanindanYukle();
    void calisanVeritabanindanYukle();
    void hesapVeritabanindanYukle();
    void digerGelirVeritabanindanYukle();
    void digerGiderVeritabanindanYukle();
    void ggdCekYukle();
    void veritabanindanYukle();
    void ilkYukleme();
    void ilkYuklemeBaslangic();
    void closeEvent(QCloseEvent *event);
    void pencereBoyutuKaydet();
    QStringList getListeHesap();
    QStringList getListeCalisan();

    QTabBar getCurrentTabBar();

public slots:
    //fatura fonksiyonları
    void yeniFaturaEkle();
    void faturaSil();
    void sekmeFaturaAc();
    void sekmeFaturaOzetiAc();
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
    //diger gelir fonksiyonları
    void yeniDigerGelirEkle();
    void sekmeDigerGelirAc();
    void digerGelirSil();
    void digerGelirDegistir();
    /////////////////////////////
    //diger gider fonksiyonları
    void yeniDigerGiderEkle();
    void sekmeDigerGiderAc();
    void digerGiderSil();
    void digerGiderDegistir();
    /////////////////////////////
    //rapor fonksiyonları
    void sekmeGelirlerAc();
    void sekmeGiderlerAc();
    void sekmeGiderlerAc(int);
    void sekmeGgdAc();
    void sekmeHesapOzetiAc();
    void hesapOzetiRaporla(int a);
    ////////////////////////
    void sekmeKapatildi(int);
    void sekmeSagMenuAc();
    void kaydet();
    void kapat();
    void cbFaturaDegisti(int);
    void cbCekDegisti(int);
    void cbMaasDegisti(int);
    void cbCalisanDegisti(int);
    void cbRaporDegisti(int);
    void cbHesapDegisti(int);
    void cbDigerDegisti(int);
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
    QWidget *tbDigerGelir;
    QStringList listSilinenDigerGelir;
    ///////////////////////////
    //diger gelir degiskenleri
    ekledigergider form_digerGiderEkle;
    QWidget *tbDigerGider;
    QStringList listSilinenDigerGider;
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
    sdigergider sdgd;

    kistasfatura form_kistasFatura;
    kistasmaas form_kistasMaas;
    kistasCek form_kistasCek;
    kistascalisan form_kistasCalisan;
    degisken dgs;

};

#endif // MUHASIB_H
