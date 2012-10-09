#include "degisken.h"

degisken::degisken()
{
    //sekme
    sekmeBaslangicListele="Başlangıç";
    sekmeFaturaListele="Faturalar";
    sekmeCekListele="Çekler";
    sekmeMaasListele="Maaşlar";
    sekmeHesapListele="Hesaplar";
    sekmeCalisanListele="Çalışanlar";
    sekmeGelirListele="Gelirler";
    sekmeGiderListele="Giderler";
    sekmeGgd="Gelig/Gider";
    sekmeHesapOzetiListele="Hesap Özeti";
    sekmeDigerGelirListele="Diğer Gelirler";
    sekmeDigerGiderListele="Diğer Giderler";
    ///////////////////////////
    //fatura
    ftrSutunSil=0;
    ftrSutunDegistir=1;
    ftrSutunKayitNo=2;
    ftrSutunTarih=3;
    ftrSutunIsim=4;
    ftrSutunMatrah=5;
    ftrSutunKdvOrani=6;
    ftrSutunKdvTutar=7;
    ftrSutunTutar=8;
    ftrSutunAciklama=9;
    ftrSutunTur=10;
    ftrSutunHesap=11;
    ftrSutunKayit=12;
    ftrSutunDegisim=13;
    ftrSutunKilit=14;
    //////////////////
    //cek
    ckSutunSil=0;
    ckSutunDegistir=1;
    ckSutunTarih=2;
    ckSutunIsim=3;
    ckSutunBanka=4;
    ckSutunTutar=5;
    ckSutunMuhatap=6;
    ckSutunCekNo=7;
    ckSutunAciklama=8;
    ckSutunTur=9;
    ckSutunKayit=10;
    ckSutunDegisim=11;
    ckSutunKilit=12;
    ///////////////////
    //maas
    msSutunSil=0;
    msSutunDegistir=1;
    msSutunTarih=2;
    msSutunCalisan=3;
    msSutunMaas=4;
    msSutunAy=5;
    msSutunTur=6;
    msSutunHesap=7;
    msSutunKayit=8;
    msSutunDegisim=9;
    msSutunKilit=10;
    //////////////////
    //calisan
    clsSutunSil=0;
    clsSutunDegistir=1;
    clsSutunIsim=2;
    clsSutunKonum=3;
    clsSutunIseGiris=4;
    clsSutunMaas=5;
    clsSutunAciklama=6;
    clsSutunKayit=7;
    clsSutunDegisim=8;
    clsSutunKilit=9;
    ///////////////////
    //hesap
    hspSutunSil=0;
    hspSutunDegistir=1;
    hspSutunIsim=2;
    hspSutunBaslangicMeblagi=3;
    hspSutunGuncelMeblag=4;
    hspSutunTur=5;
    hspSutunKayit=6;
    hspSutunDegisim=7;
    hspSutunKilit=8;
    //////////////////
    //diger gelir
    dglSutunSil=0;
    dglSutunDegistir=1;
    dglSutunTarih=2;
    dglSutunIsim=3;
    dglSutunMuhatap=4;
    dglSutunTutar=5;
    dglSutunAciklama=6;
    dglSutunHesap=7;
    dglSutunKayit=8;//kayit id sini tutuyor veritabanina kayitlimi diye. ikinci defa kaydetmesin.
    dglSutunDegisim=9;//değiştirilen kayitlari tutmak için
    dglSutunKilit=10;//kilit açık mı kapalı mı
    ///////////////////
    //diger gider
    dgdSutunSil=0;
    dgdSutunDegistir=1;
    dgdSutunTarih=2;
    dgdSutunIsim=3;
    dgdSutunMuhatap=4;
    dgdSutunTutar=5;
    dgdSutunAciklama=6;
    dgdSutunHesap=7;
    dgdSutunKayit=8;//kayit id sini tutuyor veritabanina kayitlimi diye. ikinci defa kaydetmesin.
    dgdSutunDegisim=9;//değiştirilen kayitlari tutmak için
    dgdSutunKilit=10;//kilit açık mı kapalı mı
    ///////////////////
    //hesap özeti
    hoztSutunTarih=0;
    hoztSutunKayitNo=1;
    hoztSutunIsim=2;
    hoztSutunGG=3;//gelir mi gider mi
    hoztSutunTutar=4;
    ////////////////////
    //giderler
    gdrSutunTarih=0;
    gdrSutunTur=1;
    gdrSutunGider=2;
    gdrSutunTutar=3;
    /////////////////////
    //gelirler
    glrSutunTarih=0;
    glrSutunTur=1;
    glrSutunGelir=2;
    glrSutunTutar=3;
    /////////////////////
    //ggd
    ggdSutunTur=0;
    ggdSutunGelir=1;
    ggdSutunGider=2;
    ggdSutunFark=3;
    //////////////////
}

