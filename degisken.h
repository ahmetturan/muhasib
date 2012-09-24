#ifndef DEGISKEN_H
#define DEGISKEN_H

class degisken
{
public:
    degisken();

    //fatura
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
    //////////////////////////////77
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
};

#endif // DEGISKEN_H
