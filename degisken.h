#ifndef DEGISKEN_H
#define DEGISKEN_H

#include <QString>

class degisken
{
public:
    degisken();
    //sekme isimleri
    QString sekmeBaslangicListele;
    QString sekmeFaturaListele;
    QString sekmeCekListele;
    QString sekmeMaasListele;
    QString sekmeHesapListele;
    QString sekmeCalisanListele;
    QString sekmeGelirListele;
    QString sekmeGiderListele;
    QString sekmeGgd;
    QString sekmeHesapOzetiListele;
    QString sekmeDigerGelirListele;
    QString sekmeDigerGiderListele;
    ///////////////////////////////7
    //fatura
    int ftrSutunSil;
    int ftrSutunDegistir;
    int ftrSutunTarih;
    int ftrSutunKayitNo;
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
    //////////////////////////////77
    //cek
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
    ///////////////////////////////
    //mass
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
    ////////////////////////////////////////////7
    //calisan
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
    ////////////////////////////////////////////
    //hesap
    int hspSutunSil;
    int hspSutunDegistir;
    int hspSutunIsim;
    int hspSutunBaslangicMeblagi;
    int hspSutunGuncelMeblag;
    int hspSutunTur;
    int hspSutunKayit;//kayit id sini tutuyor veritabanina kayitlimi diye. ikinci defa kaydetmesin.
    int hspSutunDegisim;//değiştirilen kayitlari tutmak için
    int hspSutunKilit;//kilit açık mı kapalı mı
    ///////////////////////////////////////////////7
    //diger gelir
    int dglSutunSil;
    int dglSutunDegistir;
    int dglSutunTarih;
    int dglSutunIsim;
    int dglSutunMuhatap;
    int dglSutunTutar;
    int dglSutunAciklama;
    int dglSutunHesap;
    int dglSutunKayit;//kayit id sini tutuyor veritabanina kayitlimi diye. ikinci defa kaydetmesin.
    int dglSutunDegisim;//değiştirilen kayitlari tutmak için
    int dglSutunKilit;//kilit açık mı kapalı mı
    ////////////////////////
    //diger gider
    int dgdSutunSil;
    int dgdSutunDegistir;
    int dgdSutunTarih;
    int dgdSutunIsim;
    int dgdSutunMuhatap;
    int dgdSutunTutar;
    int dgdSutunAciklama;
    int dgdSutunHesap;
    int dgdSutunKayit;//kayit id sini tutuyor veritabanina kayitlimi diye. ikinci defa kaydetmesin.
    int dgdSutunDegisim;//değiştirilen kayitlari tutmak için
    int dgdSutunKilit;//kilit açık mı kapalı mı
    ////////////////////////
    //hesap özeti
    int hoztSutunTarih;
    int hoztSutunKayitNo;
    int hoztSutunIsim;
    int hoztSutunGG;//gelir mi gider mi
    int hoztSutunTutar;
    ////////////////////
    //giderler
    int gdrSutunTarih;
    int gdrSutunTur;
    int gdrSutunGider;
    int gdrSutunTutar;
    //////////////////
    //gelirler
    int glrSutunTarih;
    int glrSutunTur;
    int glrSutunGelir;
    int glrSutunTutar;
    ///////////////////
    //ggd
    int ggdSutunTur;
    int ggdSutunGelir;
    int ggdSutunGider;
    int ggdSutunFark;
    /////////////////////
};

#endif // DEGISKEN_H
