#ifndef MUHASIB_H
#define MUHASIB_H

#include <QMainWindow>
#include <QtSql>
#include <QMessageBox>
#include <QPushButton>
#include <QTableWidget>
#include <QWidgetAction>
#include "faturaekle.h"
#include "cekekle.h"
#include "maasekle.h"
#include "calisanekle.h"
#include "hesapekle.h"

#include "sfatura.h"
#include "scek.h"
#include "smaas.h"
#include "scalisan.h"
#include "shesap.h"

#include "kistasfatura.h"

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
    //gelirler fonksiyonları
    void ilkYuklemeGelirler();
    void gelirleriYukle();
    ////////////////////////
    //giderler fonksiyonları
    void ilkYuklemeGiderler();
    void giderleriYukle();
    ////////////////////////
    //gelir-gider dengesi fonksiyonları
    void ilkYuklemeGgd();
    void ggdYukle();
    void ggdFaturaYukle();
    void ggdCekYukle();
    void ggdMaasYukle();
    void ggdToplamiYukle();
    void ggdItem(QTableWidgetItem*);
    /////////////////////////////////
    void veritabanindanYukle();
    void ilkYukleme();
    void ilkYuklemeBaslangic();

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
    void cbCekDegisti();
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
    //gelirler fonksiyonları
    void sekmeGelirlerAc();
    ////////////////////////
    //giderler fonksiyonları
    void sekmeGiderlerAc();
    ////////////////////////
    //gelir-gider dengesi fonksiyonları
    void sekmeGgdAc();
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

private:
    //fatura değişkenleri
    faturaEkle form_faturaEkle;
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
    double ToplamTutarFatura;
    QWidget *tbFatura;
    QWidget *tbFaturaOzeti;
    QStringList listSilinenFatura;
    ///////////////////////
    //çek degişkenleri
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
    double ToplamTutarCek;
    QWidget *tbCek;
    QWidget *tbCekOzeti;
    QStringList listSilinenCek;
    ////////////////////
    //maaş değişkenleri
    maasekle form_maasEkle;
    int msSutunSil;
    int msSutunDegistir;
    int msSutunTarih;
    int msSutunCalisan;
    int msSutunMaas;
    int msSutunAy;
    int msSutunTur;
    int msSutunHesap;
    int msSutunKayit;//kayit id sini tutuyor veritabanina kayitlimi diye. ikinci defa kaydetmesin.
    int msSutunDegisim;//değiştirilen kayitlari tutmak için
    int msSutunKilit;//kilit açık mı kapalı mı
    double ToplamTutarMaas;
    QWidget *tbMaas;
    QStringList listSilinenMaas;
    //////////////////////
    //calisan degiskenleri
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
    double ToplamTutarCalisan;
    QWidget *tbCalisan;
    QStringList listSilinenCalisan;
    /////////////////////////
    //gelirler degiskenleri
    int glrSutunTarih;
    int glrSutunTur;
    int glrSutunGelir;
    int glrSutunTutar;
    QWidget *tbGelirler;
    ///////////////////////////////
    //giderler degiskenleri
    int gdrSutunTarih;
    int gdrSutunTur;
    int gdrSutunGider;
    int gdrSutunTutar;
    QWidget *tbGiderler;
    ///////////////////////////////
    //gelir-gider dengesi degiskenleri
    int ggdSutunTur;
    int ggdSutunGelir;
    int ggdSutunGider;
    int ggdSutunFark;
    QWidget *tbGgd;
    /////////////////////////////
    //hesap degiskenleri
    hesapekle form_hesapEkle;
    int hspSutunSil;
    int hspSutunDegistir;
    int hspSutunIsim;
    int hspSutunBaslangicMeblagi;
    int hspSutunGuncelMeblag;
    int hspSutunTur;
    int hspSutunKayit;//kayit id sini tutuyor veritabanina kayitlimi diye. ikinci defa kaydetmesin.
    int hspSutunDegisim;//değiştirilen kayitlari tutmak için
    int hspSutunKilit;//kilit açık mı kapalı mı
    QWidget *tbHesap;
    QStringList listSilinenHesap;
    ///////////////////////////
    bool degisiklikIzle;//tblFatura değiştikçe toplamı yeniden hesaplamasın
    bool kaydetVar;

    scek sck;
    sFatura sftr;
    smaas sms;
    scalisan sclsn;
    shesap shsp;

    kistasfatura form_kistasFatura;

};

#endif // MUHASIB_H
