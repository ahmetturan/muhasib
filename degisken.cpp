#include "degisken.h"

degisken::degisken()
{
    //sekme
    sekmeFaturaListele="Faturalar";
    sekmeCekListele="Çekler";
    sekmeMaasListele="Maaşlar";
    sekmeHesapListele="Hesaplar";
    sekmeCalisanListele="Çalışanlar";
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

