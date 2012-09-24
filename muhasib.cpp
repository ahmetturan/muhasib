#include "muhasib.h"
#include "ui_muhasib.h"

muhasib::muhasib(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::muhasib)
{
    ui->setupUi(this);
    //fatura bağlantıları
    connect(ui->btnFaturaEkleFatura,SIGNAL(clicked()),this,SLOT(yeniFaturaEkle()));
    connect(ui->tblFatura,SIGNAL(cellChanged(int,int)),this,SLOT(faturaToplamiHesapla(int,int)));
    connect(ui->btnFaturaKarsilastirBaslangicTarihi,SIGNAL(clicked()),this,SLOT(faturaTakvimAc()));
    connect(ui->btnFaturaKarsilastirBitisTarihi,SIGNAL(clicked()),this,SLOT(faturaTakvimAc()));
    connect(ui->btnRaporlaFaturaKarsilastir,SIGNAL(clicked()),this,SLOT(faturaOzetiRaporla()));
    connect(ui->btnFaturaOzetiFatura,SIGNAL(clicked()),this,SLOT(sekmeFaturaOzetiAc()));
    connect(ui->tblFatura,SIGNAL(cellChanged(int,int)),this,SLOT(faturaTutarHesapla(int,int)));
    connect(ui->actionFaturaListele,SIGNAL(triggered()),this,SLOT(sekmeFaturaAc()));
    connect(ui->actionFaturaEkle,SIGNAL(triggered()),this,SLOT(yeniFaturaEkle()));
    connect(ui->actionFaturaKarsilastir,SIGNAL(triggered()),this,SLOT(sekmeFaturaOzetiAc()));
    connect(ui->btnKistasFatura,SIGNAL(clicked()),this,SLOT(kistasFaturaAc()));
    //////////
    //cek bağlantıları
    connect(ui->btnCekEkleCek,SIGNAL(clicked()),this,SLOT(yeniCekEkle()));
    connect(ui->cbAlinanCek,SIGNAL(clicked()),this,SLOT(cbCekDegisti()));
    connect(ui->cbVerilenCek,SIGNAL(clicked()),this,SLOT(cbCekDegisti()));
    connect(ui->tblCek,SIGNAL(cellChanged(int,int)),this,SLOT(cekToplamiHesapla(int,int)));
    connect(ui->btnCekKarsilastirBaslangicTarihi,SIGNAL(clicked()),this,SLOT(cekOzetiTakvimAc()));
    connect(ui->btnCekKarsilastirBitisTarihi,SIGNAL(clicked()),this,SLOT(cekOzetiTakvimAc()));
    connect(ui->btnRaporlaCekKarsilastir,SIGNAL(clicked()),this,SLOT(cekOzetiRaporla()));
    connect(ui->btnCekOzetiCek,SIGNAL(clicked()),this,SLOT(sekmeCekOzetiAc()));
    connect(ui->actionCekListele,SIGNAL(triggered()),this,SLOT(sekmeCekAc()));
    connect(ui->actionCekEkle,SIGNAL(triggered()),this,SLOT(yeniCekEkle()));
    connect(ui->actionCekKarsilastir,SIGNAL(triggered()),this,SLOT(sekmeCekOzetiAc()));
    ///////////////////
    ///maaş bağlantıları
    connect(ui->btnMaasEkleMaas,SIGNAL(clicked()),this,SLOT(yeniMaasEkle()));
    connect(ui->actionMaasEkle,SIGNAL(triggered()),this,SLOT(yeniMaasEkle()));
    connect(ui->actionMaasListele,SIGNAL(triggered()),this,SLOT(sekmeMaasAc()));
    //////////////////////
    //calisan bağlantıları
    connect(ui->btnCalisanEkleCalisan,SIGNAL(clicked()),this,SLOT(yeniCalisanEkle()));
    connect(ui->actionCalisanEkle,SIGNAL(triggered()),this,SLOT(yeniCalisanEkle()));
    connect(ui->actionCalisanListele,SIGNAL(triggered()),this,SLOT(sekmeCalisanAc()));
    /////////////////////////
    //hesap bağlantıları
    connect(ui->btnHesapEkleHesap,SIGNAL(clicked()),this,SLOT(yeniHesapEkle()));
    connect(ui->actionHesapEkle,SIGNAL(triggered()),this,SLOT(yeniHesapEkle()));
    connect(ui->actionHesapListele,SIGNAL(triggered()),this,SLOT(sekmeHesapAc()));
    /////////////////////////
    //gelirler bağlantıları
    connect(ui->actionGelirler,SIGNAL(triggered()),this,SLOT(sekmeGelirlerAc()));
    ////////////////////////////
    //giderler bağlantıları
    connect(ui->actionGiderler,SIGNAL(triggered()),this,SLOT(sekmeGiderlerAc()));
    ////////////////////////////
    //gelir-gider bağlantıları
    connect(ui->actionGgd,SIGNAL(triggered()),this,SLOT(sekmeGgdAc()));
    ////////////////////////////
    connect(ui->cbFatura,SIGNAL(currentIndexChanged(int)),this,SLOT(cbFaturaDegisti(int)));
    connect(ui->cbCek,SIGNAL(currentIndexChanged(int)),this,SLOT(cbCekDegisti(int)));
    connect(ui->cbMaas_2,SIGNAL(currentIndexChanged(int)),this,SLOT(cbMaasDegisti(int)));
    connect(ui->cbCalisan,SIGNAL(currentIndexChanged(int)),this,SLOT(cbCalisanDegisti(int)));
    connect(ui->cbRapor,SIGNAL(currentIndexChanged(int)),this,SLOT(cbRaporDegisti(int)));
    connect(ui->cbHesap,SIGNAL(currentIndexChanged(int)),this,SLOT(cbHesapDegisti(int)));
    connect(ui->tabWidget,SIGNAL(tabCloseRequested(int)),this,SLOT(sekmeKapatildi(int)));
    connect(ui->actionKaydet,SIGNAL(triggered()),this,SLOT(kaydet()));
    connect(ui->actionCikis,SIGNAL(triggered()),this,SLOT(kapat()));
    ilkYukleme();
}

void muhasib::kistasFaturaAc()
{
    this->setEnabled(false);
    form_kistasFatura.ontanimliAyarlar();
    form_kistasFatura.exec();

    if(form_kistasFatura.getSecim())
    {
        QStringList listeTarih;
        QStringList listeTur;

        for(int i=0; i<ui->tblFatura->rowCount();i++)
        {
            ui->tblFatura->hideRow(i);
        }

        if(form_kistasFatura.getTarihEtkinMi())//tarih kıstası etkin
        {
            for(int i=0; i<ui->tblFatura->rowCount();i++)
            {
                QDate dt=QDate::fromString(ui->tblFatura->item(i,ftrSutunTarih)->text(),"yyyy-MM-dd");

                if(dt>=form_kistasFatura.getBaslangicTarih() && dt<=form_kistasFatura.getBitisTarih())
                {
                    listeTarih.append(QString::number(i));
                }
            }
        }
        else
        {
            for(int i=0; i<ui->tblFatura->rowCount();i++)
            {
                listeTarih.append(QString::number(i));
            }
        }

        if(form_kistasFatura.getTurEtkinMi())
        {
            if(form_kistasFatura.getTurSecim()==0)//gelir ve gider (yani hepsi) etkin
            {
                for(int i=0; i<ui->tblFatura->rowCount();i++)
                {
                    listeTur.append(QString::number(i));
                }
            }
            else if(form_kistasFatura.getTurSecim()==1)//sadece gelen etkin
            {
                for(int i=0; i<ui->tblFatura->rowCount();i++)
                {
                    if(ui->tblFatura->item(i,ftrSutunTur)->text()=="Gelen")
                        listeTur.append(QString::number(i));
                }
            }
            else if(form_kistasFatura.getTurSecim()==2)//sadece giden etkin
            {
                for(int i=0; i<ui->tblFatura->rowCount();i++)
                {
                    if(ui->tblFatura->item(i,ftrSutunTur)->text()=="Giden")
                        listeTur.append(QString::number(i));
                }
            }
        }
        else
        {
            for(int i=0; i<ui->tblFatura->rowCount();i++)
            {
                listeTur.append(QString::number(i));
            }
        }

        QStringList topluListe=listeTur+listeTarih;
        while(!topluListe.isEmpty())
        {
            if(topluListe.count(topluListe.at(0))==2)//2 tane kıstas olduğu için
            {
                ui->tblFatura->showRow(topluListe.at(0).toInt());
                topluListe.removeAt(0);
            }
            else
            {
                topluListe.removeAt(0);
            }
        }
    }
    this->setEnabled(true);
}

void muhasib::kapat()
{
    //pencerenin boyutu veritabanına kaydediliyor
    QSqlQuery query;
    if(isMaximized())//eğer pencere tam ekran ise tam ekran açılması için
    {
        query.exec(QString("update boyut set b_tamekran='%1' where b_id='%2'").arg("1").arg("1"));
    }
    else
    {
        query.exec(QString("update boyut set b_x='%1', b_y='%2',b_w='%3',b_h='%4', b_tamekran='%5' where b_id='%6'").arg(geometry().x()).arg(geometry().y()).arg(geometry().width()).arg(geometry().height()).arg("0").arg("1"));
    }
    ////////////////////////////////////////7
    close();
}

void muhasib::cbHesapDegisti(int a)
{
    if(a==1)
    {
        yeniHesapEkle();
    }
    else if(a==2)
    {
        sekmeHesapAc();
    }
    ui->cbHesap->setCurrentIndex(0);
}

void muhasib::cbFaturaDegisti(int a)
{
    if(a==1)
    {
        yeniFaturaEkle();
    }
    else if(a==2)
    {
        sekmeFaturaAc();
    }
    else if(a==3)
    {
        sekmeFaturaOzetiAc();
    }
    ui->cbFatura->setCurrentIndex(0);
}

void muhasib::cbCekDegisti(int a)
{
    if(a==1)
    {
        yeniCekEkle();
    }
    else if(a==2)
    {
        sekmeCekAc();
    }
    else if(a==3)
    {
        sekmeCekOzetiAc();
    }
    ui->cbCek->setCurrentIndex(0);
}

void muhasib::cbMaasDegisti(int a)
{
    if(a==1)
    {
        yeniMaasEkle();
    }
    else if(a==2)
    {
        sekmeMaasAc();
    }
    ui->cbMaas_2->setCurrentIndex(0);
}

void muhasib::cbCalisanDegisti(int a)
{
    if(a==1)
    {
        yeniCalisanEkle();
    }
    else if(a==2)
    {
        sekmeCalisanAc();
    }
    ui->cbCalisan->setCurrentIndex(0);
}

void muhasib::cbRaporDegisti(int a)
{
    if(a==1)
    {
        sekmeGelirlerAc();
    }
    else if(a==2)
    {
        sekmeGiderlerAc();
    }
    else if(a==3)
    {
        sekmeGgdAc();
    }
    ui->cbRapor->setCurrentIndex(0);
}

//SEKMELERİ KAPATMAK İÇİN
void muhasib::sekmeKapatildi(int a)
{
    if(a!=0)
    {
        ui->tabWidget->removeTab(a);
    }
}

void muhasib::kaydet()
{
    if(kaydetVar==true)
    {
        faturaKaydet();
        cekKaydet();
        maasKaydet();
        calisanKaydet();
        hesapKaydet();
        kaydetVar=false;
    }
}

//PROGRAM BAŞLAYINCA VERİTABANINDAN BİLGİLERİ YÜKLÜYOR
void muhasib::veritabanindanYukle()
{
    faturaVeritabanindanYukle();
    cekVeritabanindanYukle();
    maasVeritabanindanYukle();
    calisanVeritabanindanYukle();
    hesapVeritabanindanYukle();
}

void muhasib::hesapVeritabanindanYukle()
{
    degisiklikIzle=false;//veritabanından yükleme yapılırken toplamtutarı hesaplamasın
    QSqlQuery query;
    query.exec("select h_isim, h_baslangicmeblagi, h_tur, h_id, h_guncelmeblag from hesap");
    while(query.next())
    {
        ui->tblHesap->insertRow(ui->tblHesap->rowCount());

        QPushButton *btnSil=new QPushButton();
        btnSil->setIcon(QIcon(QDir::currentPath()+"/icons/sil.png"));
        btnSil->setToolTip("Sil");
        connect(btnSil,SIGNAL(clicked()),this,SLOT(hesapSil()));
        ui->tblHesap->setCellWidget(ui->tblHesap->rowCount()-1,hspSutunSil,btnSil);

        QPushButton *btnDegistir=new QPushButton();
        btnDegistir->setIcon(QIcon(QDir::currentPath()+"/icons/kilitkapali.png"));
        btnDegistir->setToolTip("Degiştir");
        connect(btnDegistir,SIGNAL(clicked()),this,SLOT(hesapDegistir()));
        ui->tblHesap->setCellWidget(ui->tblHesap->rowCount()-1,hspSutunDegistir,btnDegistir);

        QTableWidgetItem *itm1=new QTableWidgetItem(query.value(0).toString());
        QTableWidgetItem *itm2=new QTableWidgetItem(query.value(1).toString());
        QTableWidgetItem *itm3=new QTableWidgetItem(query.value(2).toString());
        QTableWidgetItem *itm4=new QTableWidgetItem(query.value(3).toString());
        QTableWidgetItem *itm7=new QTableWidgetItem(query.value(4).toString());
        QTableWidgetItem *itm5=new QTableWidgetItem("0");
        QTableWidgetItem *itm6=new QTableWidgetItem("0");

        ui->tblHesap->setItem(ui->tblHesap->rowCount()-1,hspSutunIsim,itm1);
        ui->tblHesap->setItem(ui->tblHesap->rowCount()-1,hspSutunBaslangicMeblagi,itm2);
        ui->tblHesap->setItem(ui->tblHesap->rowCount()-1,hspSutunGuncelMeblag,itm7);
        ui->tblHesap->setItem(ui->tblHesap->rowCount()-1,hspSutunTur,itm3);
        ui->tblHesap->setItem(ui->tblHesap->rowCount()-1,hspSutunKayit,itm4);
        ui->tblHesap->setItem(ui->tblHesap->rowCount()-1,hspSutunDegisim,itm5);
        ui->tblHesap->setItem(ui->tblHesap->rowCount()-1,hspSutunKilit,itm6);

        itm1->setFlags(Qt::ItemIsEnabled);//salt okunur hücreler
        itm2->setFlags(Qt::ItemIsEnabled);
        itm3->setFlags(Qt::ItemIsEnabled);
        itm4->setFlags(Qt::ItemIsEnabled);
        itm5->setFlags(Qt::ItemIsEnabled);
        itm6->setFlags(Qt::ItemIsEnabled);
        itm7->setFlags(Qt::ItemIsEnabled);
        //ToplamTutarHesap=ToplamTutarHesap+itm6->text().toDouble();//toplam tutarı uygulama başlayınca hesaplıyor
    }
    //ui->lblHesap->setText("Kayıt: "+QString::number(ui->tblHesap->rowCount())+" Tutar: "+QString::number(ToplamTutarHesap));
    degisiklikIzle=true;
    //ui->tblHesap->sortByColumn(hspSutunTarih);//tblHesapyı tarih sutunua göre sıralıyor
}

void muhasib::hesapKaydet()
{
    shsp.hesapKaydet2(listSilinenHesap,ui->tblHesap);
}

void muhasib::sekmeHesapAc()
{
    ui->tabWidget->addTab(tbHesap,"Hesaplar");
    ui->tabWidget->setCurrentWidget(tbHesap);
}

void muhasib::yeniHesapEkle()
{
    degisiklikIzle=false;
    form_hesapEkle.setWindowFlags(Qt::Window);//hesap ekleme penceresinin köşesindeki 3 düğmenin gösterilmesi için
    form_hesapEkle.ontanimliAyarlar();
    this->setEnabled(false);//ana pencere etkisizleştiriliyor
    form_hesapEkle.exec();
    QStringList listeHesaplar=form_hesapEkle.getListeHesap();
    qDebug()<<"listeHesap"<<listeHesaplar;
    if(listeHesaplar.count()!=0)//Hesaplar ekle ekranında kapat'a tıklanırsa Hesaplar sekmesi açılmasın ve kaydetvar true olmasın
    {
        sekmeHesapAc();
        kaydetVar=true;
    }
    this->setEnabled(true);//ana pencere etkinleştiriliyor

    for(int i=0;i<listeHesaplar.count();i=i+3)//3 sutun var Hesaplar ekleme penceresinde
    {
        ui->tblHesap->insertRow(ui->tblHesap->rowCount());

        QPushButton *btnSil=new QPushButton();
        btnSil->setIcon(QIcon(QDir::currentPath()+"/icons/sil.png"));
        btnSil->setToolTip("Sil");
        connect(btnSil,SIGNAL(clicked()),this,SLOT(hesapSil()));
        ui->tblHesap->setCellWidget(ui->tblHesap->rowCount()-1,hspSutunSil,btnSil);

        QPushButton *btnDegistir=new QPushButton();
        btnDegistir->setIcon(QIcon(QDir::currentPath()+"/icons/kilitkapali.png"));
        btnDegistir->setToolTip("Degiştir");
        connect(btnDegistir,SIGNAL(clicked()),this,SLOT(hesapDegistir()));
        ui->tblHesap->setCellWidget(ui->tblHesap->rowCount()-1,hspSutunDegistir,btnDegistir);

        QTableWidgetItem *itm1=new QTableWidgetItem(listeHesaplar.at(i));
        QTableWidgetItem *itm2=new QTableWidgetItem(listeHesaplar.at(i+1));
        QTableWidgetItem *itm3=new QTableWidgetItem(listeHesaplar.at(i+2));
        QTableWidgetItem *itm4=new QTableWidgetItem("0");
        QTableWidgetItem *itm5=new QTableWidgetItem("0");
        QTableWidgetItem *itm6=new QTableWidgetItem("0");
        QTableWidgetItem *itm7=new QTableWidgetItem(listeHesaplar.at(i+1));

        ui->tblHesap->setItem(ui->tblHesap->rowCount()-1,hspSutunIsim,itm1);
        ui->tblHesap->setItem(ui->tblHesap->rowCount()-1,hspSutunBaslangicMeblagi,itm2);
        ui->tblHesap->setItem(ui->tblHesap->rowCount()-1,hspSutunGuncelMeblag,itm7);
        ui->tblHesap->setItem(ui->tblHesap->rowCount()-1,hspSutunTur,itm3);
        ui->tblHesap->setItem(ui->tblHesap->rowCount()-1,hspSutunKayit,itm4);
        ui->tblHesap->setItem(ui->tblHesap->rowCount()-1,hspSutunDegisim,itm5);
        ui->tblHesap->setItem(ui->tblHesap->rowCount()-1,hspSutunKilit,itm6);

        itm1->setFlags(Qt::ItemIsEnabled);//salt okunur hücreler
        itm2->setFlags(Qt::ItemIsEnabled);
        itm3->setFlags(Qt::ItemIsEnabled);
        itm4->setFlags(Qt::ItemIsEnabled);
        itm5->setFlags(Qt::ItemIsEnabled);
        itm6->setFlags(Qt::ItemIsEnabled);
        itm7->setFlags(Qt::ItemIsEnabled);

    }
    //toplam tutar ve kayıt sayısı yazdırılıyor
    //ToplamTutarHesaplar=ToplamTutarHesaplar+form_HesaplarEkle.getToplamTutar();
    //ui->lblHesaplar->setText("Kayıt: "+QString::number(ui->tblHesap->rowCount())+" Tutar: "+QString::number(ToplamTutarHesaplar));
    ///////////////////////////////////////////

    degisiklikIzle=true;
}

void muhasib::hesapSil()
{
    QObject* obj = sender();
    shsp.hesapSil2(listSilinenHesap, kaydetVar, ui->tblHesap, obj);
}

void muhasib::hesapDegistir()
{
    QObject* obj = sender();
    shsp.hesapDegistir2(degisiklikIzle, kaydetVar, ui->tblHesap, obj);
}

void muhasib::sekmeGgdAc()
{
    ggdYukle();
    ui->tabWidget->addTab(tbGgd,"Gelir/Gider");
    ui->tabWidget->setCurrentWidget(tbGgd);
}

void muhasib::ggdItem(QTableWidgetItem *itm)//itm yazıtipini büyütüyor ve yazıyı ortaya alıyor
{
    QFont fnt;
    fnt.setPointSize(20);
    itm->setFont(fnt);
    itm->setTextAlignment(Qt::AlignHCenter);
}

//GELİR GİDER EKRANINA FATURA BİLGİLERİNİ YÜKLÜYOR
void muhasib::ggdFaturaYukle()
{
    double faturaGelirTutar=0;
    double faturaGiderTutar=0;

    for(int i=0;i<ui->tblFatura->rowCount();i++)
    {
        if(ui->tblFatura->item(i,ftrSutunTur)->text()=="Giden")
        {
            faturaGelirTutar=faturaGelirTutar+ui->tblFatura->item(i,ftrSutunTutar)->text().toDouble();
        }
        else if(ui->tblFatura->item(i,ftrSutunTur)->text()=="Gelen")
        {
            faturaGiderTutar=faturaGiderTutar+ui->tblFatura->item(i,ftrSutunTutar)->text().toDouble();
        }
    }

    ui->tblGgd->insertRow(ui->tblGgd->rowCount());
    ui->tblGgd->setRowHeight(ui->tblGgd->rowCount()-1,40);
    QTableWidgetItem *itm0=new QTableWidgetItem("Fatura");
    ggdItem(itm0);
    ui->tblGgd->setItem(ui->tblGgd->rowCount()-1,ggdSutunTur,itm0);
    QTableWidgetItem *itm1=new QTableWidgetItem(QString::number(faturaGelirTutar));
    ggdItem(itm1);
    ui->tblGgd->setItem(ui->tblGgd->rowCount()-1,ggdSutunGelir,itm1);
    QTableWidgetItem *itm2=new QTableWidgetItem(QString::number(faturaGiderTutar));
    ggdItem(itm2);
    ui->tblGgd->setItem(ui->tblGgd->rowCount()-1,ggdSutunGider,itm2);
    QTableWidgetItem *itm3=new QTableWidgetItem(QString::number(faturaGelirTutar-faturaGiderTutar));
    ggdItem(itm3);
    ui->tblGgd->setItem(ui->tblGgd->rowCount()-1,ggdSutunFark,itm3);
}

//GELİR GİDER EKRANINA CEK BİLGİLERİNİ YÜKLÜYOR
void muhasib::ggdCekYukle()
{
    /*
    double cekGelirTutar=0;
    double cekGiderTutar=0;
    for(int i=0;i<ui->tblCek->rowCount();i++)
    {
        if(ui->tblCek->item(i,ckSutunTur)->text()=="Alınan")
        {
            cekGelirTutar=cekGelirTutar+ui->tblCek->item(i,ckSutunTutar)->text().toDouble();
        }
        else if(ui->tblCek->item(i,ckSutunTur)->text()=="Verilen")
        {
            cekGiderTutar=cekGiderTutar+ui->tblCek->item(i,ckSutunTutar)->text().toDouble();
        }
    }
    ui->tblGgd->insertRow(ui->tblGgd->rowCount());
    ui->tblGgd->setRowHeight(ui->tblGgd->rowCount()-1,40);
    QTableWidgetItem *itm0=new QTableWidgetItem("Çek");
    ggdItem(itm0);
    ui->tblGgd->setItem(ui->tblGgd->rowCount()-1,ggdSutunTur,itm0);
    QTableWidgetItem *itm1=new QTableWidgetItem(QString::number(cekGelirTutar));
    ggdItem(itm1);
    ui->tblGgd->setItem(ui->tblGgd->rowCount()-1,ggdSutunGelir,itm1);
    QTableWidgetItem *itm2=new QTableWidgetItem(QString::number(cekGiderTutar));
    ggdItem(itm2);
    ui->tblGgd->setItem(ui->tblGgd->rowCount()-1,ggdSutunGider,itm2);
    QTableWidgetItem *itm3=new QTableWidgetItem(QString::number(cekGelirTutar-cekGiderTutar));
    ggdItem(itm3);
    ui->tblGgd->setItem(ui->tblGgd->rowCount()-1,ggdSutunFark,itm3);
    */
}

//GELİR GİDER EKRANINA MAAS BİLGİLERİNİ YÜKLÜYOR
void muhasib::ggdMaasYukle()
{
    double maasTutar=0;
    for(int i=0;i<ui->tblMaas->rowCount();i++)
    {
        maasTutar=maasTutar+ui->tblMaas->item(i,msSutunMaas)->text().toDouble();
    }
    ui->tblGgd->insertRow(ui->tblGgd->rowCount());
    ui->tblGgd->setRowHeight(ui->tblGgd->rowCount()-1,40);
    QTableWidgetItem *itm0=new QTableWidgetItem("Maaş");
    ggdItem(itm0);
    ui->tblGgd->setItem(ui->tblGgd->rowCount()-1,ggdSutunTur,itm0);
    QTableWidgetItem *itm1=new QTableWidgetItem("-");
    ggdItem(itm1);
    ui->tblGgd->setItem(ui->tblGgd->rowCount()-1,ggdSutunGelir,itm1);
    QTableWidgetItem *itm2=new QTableWidgetItem(QString::number(maasTutar));
    ggdItem(itm2);
    ui->tblGgd->setItem(ui->tblGgd->rowCount()-1,ggdSutunGider,itm2);
    QTableWidgetItem *itm3=new QTableWidgetItem(QString::number(0-maasTutar));
    ggdItem(itm3);
    ui->tblGgd->setItem(ui->tblGgd->rowCount()-1,ggdSutunFark,itm3);
}

//GELİR GİDER EKRANINA TOPLAM BİLGİLERİNİ YÜKLÜYOR
void muhasib::ggdToplamiYukle()
{
    double toplamGelir=0;
    double toplamGider=0;
    for(int i=0;i<ui->tblGgd->rowCount();i++)
    {
        toplamGelir=toplamGelir+ui->tblGgd->item(i,ggdSutunGelir)->text().toDouble();
    }
    for(int i=0;i<ui->tblGgd->rowCount();i++)
    {
        toplamGider=toplamGider+ui->tblGgd->item(i,ggdSutunGider)->text().toDouble();
    }

    ui->tblGgd->insertRow(ui->tblGgd->rowCount());
    ui->tblGgd->setRowHeight(ui->tblGgd->rowCount()-1,40);

    QTableWidgetItem *itm0=new QTableWidgetItem("Toplam");
    ggdItem(itm0);
    ui->tblGgd->setItem(ui->tblGgd->rowCount()-1,ggdSutunTur,itm0);
    QTableWidgetItem *itm1=new QTableWidgetItem(QString::number(toplamGelir));
    ggdItem(itm1);
    ui->tblGgd->setItem(ui->tblGgd->rowCount()-1,ggdSutunGelir,itm1);
    QTableWidgetItem *itm2=new QTableWidgetItem(QString::number(toplamGider));
    ggdItem(itm2);
    ui->tblGgd->setItem(ui->tblGgd->rowCount()-1,ggdSutunGider,itm2);
    QTableWidgetItem *itm3=new QTableWidgetItem(QString::number(toplamGelir-toplamGider));
    ggdItem(itm3);
    ui->tblGgd->setItem(ui->tblGgd->rowCount()-1,ggdSutunFark,itm3);
}

//GELİR GİDER EKRANINı dolduruyoe
void muhasib::ggdYukle()
{
    ui->tblGgd->setRowCount(0);
    ggdFaturaYukle();
    ggdCekYukle();
    ggdMaasYukle();
    ggdToplamiYukle();
}

void muhasib::sekmeGelirlerAc()
{
    gelirleriYukle();
    ui->tabWidget->addTab(tbGelirler,"Gelirler");
    ui->tabWidget->setCurrentWidget(tbGelirler);
}

void muhasib::gelirleriYukle()
{
    ui->tblGelirler->setRowCount(0);
    for(int i=0;i<ui->tblFatura->rowCount();i++)
    {
        if(ui->tblFatura->item(i,ftrSutunTur)->text()=="Giden")
        {
            ui->tblGelirler->insertRow(ui->tblGelirler->rowCount());
            QTableWidgetItem *itm0=new QTableWidgetItem(ui->tblFatura->item(i,ftrSutunTarih)->text());
            ui->tblGelirler->setItem(ui->tblGelirler->rowCount()-1,glrSutunTarih,itm0);

            QTableWidgetItem *itm1=new QTableWidgetItem("Fatura");
            ui->tblGelirler->setItem(ui->tblGelirler->rowCount()-1,glrSutunTur,itm1);

            QTableWidgetItem *itm2=new QTableWidgetItem(ui->tblFatura->item(i,ftrSutunIsim)->text());
            ui->tblGelirler->setItem(ui->tblGelirler->rowCount()-1,glrSutunGelir,itm2);
            QTableWidgetItem *itm3=new QTableWidgetItem(ui->tblFatura->item(i,ftrSutunTutar)->text());
            ui->tblGelirler->setItem(ui->tblGelirler->rowCount()-1,glrSutunTutar,itm3);
        }
    }
    for(int i=0;i<ui->tblCek->rowCount();i++)
    {
        if(ui->tblCek->item(i,ckSutunTur)->text()=="Alınan")
        {
            ui->tblGelirler->insertRow(ui->tblGelirler->rowCount());
            QTableWidgetItem *itm0=new QTableWidgetItem(ui->tblCek->item(i,ckSutunTarih)->text());
            ui->tblGelirler->setItem(ui->tblGelirler->rowCount()-1,glrSutunTarih,itm0);

            QTableWidgetItem *itm1=new QTableWidgetItem("Çek");
            ui->tblGelirler->setItem(ui->tblGelirler->rowCount()-1,gdrSutunTur,itm1);

            QTableWidgetItem *itm2=new QTableWidgetItem(ui->tblCek->item(i,ckSutunIsim)->text());
            ui->tblGelirler->setItem(ui->tblGelirler->rowCount()-1,glrSutunGelir,itm2);
            QTableWidgetItem *itm3=new QTableWidgetItem(ui->tblCek->item(i,ckSutunTutar)->text());
            ui->tblGelirler->setItem(ui->tblGelirler->rowCount()-1,glrSutunTutar,itm3);
        }
    }
    ui->tblGelirler->sortByColumn(glrSutunTarih);
}

void muhasib::sekmeGiderlerAc()
{
    giderleriYukle();
    ui->tabWidget->addTab(tbGiderler,"Giderler");
    ui->tabWidget->setCurrentWidget(tbGiderler);
}

void muhasib::giderleriYukle()
{
    ui->tblGiderler->setRowCount(0);
    for(int i=0;i<ui->tblFatura->rowCount();i++)
    {
        if(ui->tblFatura->item(i,ftrSutunTur)->text()=="Gelen")
        {
            ui->tblGiderler->insertRow(ui->tblGiderler->rowCount());
            QTableWidgetItem *itm0=new QTableWidgetItem(ui->tblFatura->item(i,ftrSutunTarih)->text());
            ui->tblGiderler->setItem(ui->tblGiderler->rowCount()-1,gdrSutunTarih,itm0);

            QTableWidgetItem *itm1=new QTableWidgetItem("Fatura");
            ui->tblGiderler->setItem(ui->tblGiderler->rowCount()-1,gdrSutunTur,itm1);

            QTableWidgetItem *itm2=new QTableWidgetItem(ui->tblFatura->item(i,ftrSutunIsim)->text());
            ui->tblGiderler->setItem(ui->tblGiderler->rowCount()-1,gdrSutunGider,itm2);
            QTableWidgetItem *itm3=new QTableWidgetItem(ui->tblFatura->item(i,ftrSutunTutar)->text());
            ui->tblGiderler->setItem(ui->tblGiderler->rowCount()-1,gdrSutunTutar,itm3);
        }
    }
    for(int i=0;i<ui->tblCek->rowCount();i++)
    {
        if(ui->tblCek->item(i,ckSutunTur)->text()=="Verilen")
        {
            ui->tblGiderler->insertRow(ui->tblGiderler->rowCount());
            QTableWidgetItem *itm0=new QTableWidgetItem(ui->tblCek->item(i,ckSutunTarih)->text());
            ui->tblGiderler->setItem(ui->tblGiderler->rowCount()-1,gdrSutunTarih,itm0);

            QTableWidgetItem *itm1=new QTableWidgetItem("Çek");
            ui->tblGiderler->setItem(ui->tblGiderler->rowCount()-1,gdrSutunTur,itm1);

            QTableWidgetItem *itm2=new QTableWidgetItem(ui->tblCek->item(i,ckSutunIsim)->text());
            ui->tblGiderler->setItem(ui->tblGiderler->rowCount()-1,gdrSutunGider,itm2);
            QTableWidgetItem *itm3=new QTableWidgetItem(ui->tblCek->item(i,ckSutunTutar)->text());
            ui->tblGiderler->setItem(ui->tblGiderler->rowCount()-1,gdrSutunTutar,itm3);
        }
    }
    for(int i=0;i<ui->tblMaas->rowCount();i++)
    {
        ui->tblGiderler->insertRow(ui->tblGiderler->rowCount());
        QTableWidgetItem *itm0=new QTableWidgetItem(ui->tblMaas->item(i,msSutunTarih)->text());
        ui->tblGiderler->setItem(ui->tblGiderler->rowCount()-1,gdrSutunTarih,itm0);

        QTableWidgetItem *itm1=new QTableWidgetItem("Maaş");
        ui->tblGiderler->setItem(ui->tblGiderler->rowCount()-1,gdrSutunTur,itm1);

        QTableWidgetItem *itm2=new QTableWidgetItem(ui->tblMaas->item(i,msSutunCalisan)->text());
        ui->tblGiderler->setItem(ui->tblGiderler->rowCount()-1,gdrSutunGider,itm2);
        QTableWidgetItem *itm3=new QTableWidgetItem(ui->tblMaas->item(i,msSutunMaas)->text());
        ui->tblGiderler->setItem(ui->tblGiderler->rowCount()-1,gdrSutunTutar,itm3);
    }
    ui->tblGiderler->sortByColumn(gdrSutunTarih);
}

void muhasib::calisanVeritabanindanYukle()
{
    degisiklikIzle=false;//veritabanından yükleme yapılırken toplamtutarı hesaplamasın
    QSqlQuery query;
    query.exec("select cl_isim ,cl_konum ,cl_isegiris ,cl_maas ,cl_aciklama, cl_id from calisan");
    while(query.next())
    {
        ui->tblCalisan->insertRow(ui->tblCalisan->rowCount());

        QPushButton *btnSil=new QPushButton();
        btnSil->setIcon(QIcon(QDir::currentPath()+"/icons/sil.png"));
        btnSil->setToolTip("Sil");
        connect(btnSil,SIGNAL(clicked()),this,SLOT(calisanSil()));
        ui->tblCalisan->setCellWidget(ui->tblCalisan->rowCount()-1,clsSutunSil,btnSil);

        QPushButton *btnDegistir=new QPushButton();
        btnDegistir->setIcon(QIcon(QDir::currentPath()+"/icons/kilitkapali.png"));
        btnDegistir->setToolTip("Degiştir");
        connect(btnDegistir,SIGNAL(clicked()),this,SLOT(calisanDegistir()));
        ui->tblCalisan->setCellWidget(ui->tblCalisan->rowCount()-1,clsSutunDegistir,btnDegistir);

        QTableWidgetItem *itm1=new QTableWidgetItem(query.value(0).toString());
        ui->tblCalisan->setItem(ui->tblCalisan->rowCount()-1,clsSutunIsim,itm1);
        QTableWidgetItem *itm2=new QTableWidgetItem(query.value(1).toString());
        ui->tblCalisan->setItem(ui->tblCalisan->rowCount()-1,clsSutunKonum,itm2);
        QTableWidgetItem *itm3=new QTableWidgetItem(query.value(2).toString());
        ui->tblCalisan->setItem(ui->tblCalisan->rowCount()-1,clsSutunIseGiris,itm3);
        QTableWidgetItem *itm4=new QTableWidgetItem(query.value(3).toString());
        ui->tblCalisan->setItem(ui->tblCalisan->rowCount()-1,clsSutunMaas,itm4);
        QTableWidgetItem *itm5=new QTableWidgetItem(query.value(4).toString());
        ui->tblCalisan->setItem(ui->tblCalisan->rowCount()-1,clsSutunAciklama,itm5);
        QTableWidgetItem *itm6=new QTableWidgetItem(query.value(5).toString());
        ui->tblCalisan->setItem(ui->tblCalisan->rowCount()-1,clsSutunKayit,itm6);
        QTableWidgetItem *itm7=new QTableWidgetItem("0");
        ui->tblCalisan->setItem(ui->tblCalisan->rowCount()-1,clsSutunDegisim,itm7);
        QTableWidgetItem *itm8=new QTableWidgetItem("0");
        ui->tblCalisan->setItem(ui->tblCalisan->rowCount()-1,clsSutunKilit,itm8);
        itm1->setFlags(Qt::ItemIsEnabled);//salt okunur hücreler
        itm2->setFlags(Qt::ItemIsEnabled);
        itm3->setFlags(Qt::ItemIsEnabled);
        itm4->setFlags(Qt::ItemIsEnabled);
        itm5->setFlags(Qt::ItemIsEnabled);
        itm6->setFlags(Qt::ItemIsEnabled);
        itm7->setFlags(Qt::ItemIsEnabled);
        itm8->setFlags(Qt::ItemIsEnabled);
        ToplamTutarCalisan=ToplamTutarCalisan+itm4->text().toDouble();//toplam tutarı uygulama başlayınca hesaplıyor
    }
    ui->lblCalisan->setText("Kayıt: "+QString::number(ui->tblCalisan->rowCount())+" Tutar: "+QString::number(ToplamTutarCalisan));
    degisiklikIzle=true;
}

void muhasib::calisanKaydet()
{
    sclsn.calisanKaydet2(listSilinenCalisan, ui->tblCalisan);
}

void muhasib::sekmeCalisanAc()
{
    ui->tabWidget->addTab(tbCalisan,"Çalışanlar");
    ui->tabWidget->setCurrentWidget(tbCalisan);
}

void muhasib::yeniCalisanEkle()
{
    degisiklikIzle=false;
    form_calisanEkle.setWindowFlags(Qt::Window);//Calisan ekleme penceresinin köşesindeki 3 düğmenin gösterilmesi için
    form_calisanEkle.ontanimliAyarlar();
    this->setEnabled(false);//ana pencere etkisizleştiriliyor
    form_calisanEkle.exec();
    QStringList listeCalisan=form_calisanEkle.getListeCalisan();
    qDebug()<<"listeCalisan"<<listeCalisan;
    if(listeCalisan.count()!=0)//Calisan ekle ekranında kapat'a tıklanırsa Calisan sekmesi açılmasın ve kaydetvar true olmasın
    {
        sekmeCalisanAc();
        kaydetVar=true;
    }
    this->setEnabled(true);//ana pencere etkinleştiriliyor

    for(int i=0;i<listeCalisan.count();i=i+5)//5 sutun var calisan ekleme penceresinde
    {
        ui->tblCalisan->insertRow(ui->tblCalisan->rowCount());

        QPushButton *btnSil=new QPushButton();
        btnSil->setIcon(QIcon(QDir::currentPath()+"/icons/sil.png"));
        btnSil->setToolTip("Sil");
        connect(btnSil,SIGNAL(clicked()),this,SLOT(calisanSil()));
        ui->tblCalisan->setCellWidget(ui->tblCalisan->rowCount()-1,clsSutunSil,btnSil);

        QPushButton *btnDegistir=new QPushButton();
        btnDegistir->setIcon(QIcon(QDir::currentPath()+"/icons/kilitkapali.png"));
        btnDegistir->setToolTip("Degiştir");
        connect(btnDegistir,SIGNAL(clicked()),this,SLOT(calisanDegistir()));
        ui->tblCalisan->setCellWidget(ui->tblCalisan->rowCount()-1,clsSutunDegistir,btnDegistir);

        QTableWidgetItem *itm1=new QTableWidgetItem(listeCalisan.at(i));
        ui->tblCalisan->setItem(ui->tblCalisan->rowCount()-1,clsSutunIsim,itm1);
        QTableWidgetItem *itm2=new QTableWidgetItem(listeCalisan.at(i+1));
        ui->tblCalisan->setItem(ui->tblCalisan->rowCount()-1,clsSutunKonum,itm2);
        QTableWidgetItem *itm3=new QTableWidgetItem(listeCalisan.at(i+2));
        ui->tblCalisan->setItem(ui->tblCalisan->rowCount()-1,clsSutunIseGiris,itm3);
        QTableWidgetItem *itm4=new QTableWidgetItem(listeCalisan.at(i+3));
        ui->tblCalisan->setItem(ui->tblCalisan->rowCount()-1,clsSutunMaas,itm4);
        QTableWidgetItem *itm5=new QTableWidgetItem(listeCalisan.at(i+4));
        ui->tblCalisan->setItem(ui->tblCalisan->rowCount()-1,clsSutunAciklama,itm5);
        QTableWidgetItem *itm6=new QTableWidgetItem("0");
        ui->tblCalisan->setItem(ui->tblCalisan->rowCount()-1,clsSutunKayit,itm6);
        QTableWidgetItem *itm7=new QTableWidgetItem("0");
        ui->tblCalisan->setItem(ui->tblCalisan->rowCount()-1,clsSutunDegisim,itm7);
        QTableWidgetItem *itm8=new QTableWidgetItem("0");
        ui->tblCalisan->setItem(ui->tblCalisan->rowCount()-1,clsSutunKilit,itm8);

        itm1->setFlags(Qt::ItemIsEnabled);//salt okunur hücreler
        itm2->setFlags(Qt::ItemIsEnabled);
        itm3->setFlags(Qt::ItemIsEnabled);
        itm4->setFlags(Qt::ItemIsEnabled);
        itm5->setFlags(Qt::ItemIsEnabled);
        itm6->setFlags(Qt::ItemIsEnabled);
        itm7->setFlags(Qt::ItemIsEnabled);
        itm8->setFlags(Qt::ItemIsEnabled);
    }
    //toplam tutar ve kayıt sayısı yazdırılıyor
    ToplamTutarCalisan=ToplamTutarCalisan+form_calisanEkle.getToplamTutar();
    ui->lblCalisan->setText("Kayıt: "+QString::number(ui->tblCalisan->rowCount())+" Tutar: "+QString::number(ToplamTutarCalisan));
    ///////////////////////////////////////////

    degisiklikIzle=true;
}

void muhasib::calisanSil()
{
    QObject* obj = sender();
    sclsn.calisanSil2(ToplamTutarCalisan, listSilinenCalisan, kaydetVar, ui->lblCalisan, ui->tblCalisan, obj);
}

void muhasib::calisanDegistir()
{
    QObject* obj = sender();
    sclsn.calisanDegistir2(degisiklikIzle, kaydetVar, ui->tblCalisan, obj);
}

void muhasib::maasKaydet()
{
    sms.maasKaydet2(listSilinenMaas,ui->tblMaas);
}

void muhasib::sekmeMaasAc()
{
    ui->tabWidget->addTab(tbMaas,"Maaşlar");
    ui->tabWidget->setCurrentWidget(tbMaas);
}

void muhasib::yeniMaasEkle()
{
    degisiklikIzle=false;
    form_maasEkle.setWindowFlags(Qt::Window);//maas ekleme penceresinin köşesindeki 3 düğmenin gösterilmesi için
    this->setEnabled(false);//ana pencere etkisizleştiriliyor
    //maas ekleme penceresinde çalışanların isminin çıkabilmesi için
    QStringList listeCls;
    for(int i=0;i<ui->tblCalisan->rowCount();i++)
    {
        listeCls.append(ui->tblCalisan->item(i,clsSutunIsim)->text());
    }
    form_maasEkle.setListeCalisanlar(listeCls);
    ////////////////////////////////////////////////////////7
    //maas ekleme penceresinde hesapların isminin çıkabilmesi için
    QStringList listeHsp;
    for(int i=0;i<ui->tblHesap->rowCount();i++)
    {
        listeHsp.append(ui->tblHesap->item(i,hspSutunIsim)->text());
    }
    form_maasEkle.setListeHesap(listeHsp);
    ////////////////////////////////////////////////////////7
    form_maasEkle.ontanimliAyarlar();
    form_maasEkle.exec();
    QStringList listeMaas=form_maasEkle.getListeMaas();
    qDebug()<<"listeMaas2"<<listeMaas;
    if(listeMaas.count()!=0)//maas ekle ekranında kapat'a tıklanırsa maas sekmesi açılmasın ve kaydetvar true olmasın
    {
        sekmeMaasAc();
        kaydetVar=true;
    }
    this->setEnabled(true);//ana pencere etkinleştiriliyor

    for(int i=0;i<listeMaas.count();i=i+6)//6 sutun var maas ekleme penceresinde
    {
        ui->tblMaas->insertRow(ui->tblMaas->rowCount());

        QPushButton *btnSil=new QPushButton();
        btnSil->setIcon(QIcon(QDir::currentPath()+"/icons/sil.png"));
        btnSil->setToolTip("Sil");
        connect(btnSil,SIGNAL(clicked()),this,SLOT(maasSil()));
        ui->tblMaas->setCellWidget(ui->tblMaas->rowCount()-1,msSutunSil,btnSil);

        QPushButton *btnDegistir=new QPushButton();
        btnDegistir->setIcon(QIcon(QDir::currentPath()+"/icons/kilitkapali.png"));
        btnDegistir->setToolTip("Degiştir");
        connect(btnDegistir,SIGNAL(clicked()),this,SLOT(maasDegistir()));
        ui->tblMaas->setCellWidget(ui->tblMaas->rowCount()-1,msSutunDegistir,btnDegistir);

        QTableWidgetItem *itm1=new QTableWidgetItem(listeMaas.at(i));
        QTableWidgetItem *itm2=new QTableWidgetItem(listeMaas.at(i+1));
        QTableWidgetItem *itm3=new QTableWidgetItem(listeMaas.at(i+2));
        QTableWidgetItem *itm4=new QTableWidgetItem(listeMaas.at(i+3));
        QTableWidgetItem *itm5=new QTableWidgetItem(listeMaas.at(i+4));
        QTableWidgetItem *itm9=new QTableWidgetItem(listeMaas.at(i+5));
        QTableWidgetItem *itm6=new QTableWidgetItem("0");
        QTableWidgetItem *itm7=new QTableWidgetItem("0");
        QTableWidgetItem *itm8=new QTableWidgetItem("0");

        ui->tblMaas->setItem(ui->tblMaas->rowCount()-1,msSutunTarih,itm1);
        ui->tblMaas->setItem(ui->tblMaas->rowCount()-1,msSutunCalisan,itm2);
        ui->tblMaas->setItem(ui->tblMaas->rowCount()-1,msSutunMaas,itm3);
        ui->tblMaas->setItem(ui->tblMaas->rowCount()-1,msSutunAy,itm4);
        ui->tblMaas->setItem(ui->tblMaas->rowCount()-1,msSutunTur,itm5);
        ui->tblMaas->setItem(ui->tblMaas->rowCount()-1,msSutunHesap,itm9);
        ui->tblMaas->setItem(ui->tblMaas->rowCount()-1,msSutunKayit,itm6);
        ui->tblMaas->setItem(ui->tblMaas->rowCount()-1,msSutunDegisim,itm7);
        ui->tblMaas->setItem(ui->tblMaas->rowCount()-1,msSutunKilit,itm8);

        itm1->setFlags(Qt::ItemIsEnabled);//salt okunur hücreler
        itm2->setFlags(Qt::ItemIsEnabled);
        itm3->setFlags(Qt::ItemIsEnabled);
        itm4->setFlags(Qt::ItemIsEnabled);
        itm5->setFlags(Qt::ItemIsEnabled);
        itm6->setFlags(Qt::ItemIsEnabled);
        itm7->setFlags(Qt::ItemIsEnabled);
        itm8->setFlags(Qt::ItemIsEnabled);
        itm9->setFlags(Qt::ItemIsEnabled);

        //maas eklendikçe hesap tan tutarı düşüyor veya ekliyor
        for(int i=0;i<ui->tblHesap->rowCount();i++)
        {
            if(ui->tblHesap->item(i,hspSutunIsim)->text()==itm9->text())
            {
                double hesapMeblag=ui->tblHesap->item(i,hspSutunGuncelMeblag)->text().toDouble()-itm3->text().toDouble();
                ui->tblHesap->item(i,hspSutunGuncelMeblag)->setText(QString::number(hesapMeblag));
                ui->tblHesap->item(i,hspSutunDegisim)->setText("1");
                break;
            }
        }
        ////////////////////////////
    }
    //toplam tutar ve kayıt sayısı yazdırılıyor
    ToplamTutarMaas=ToplamTutarMaas+form_maasEkle.getToplamTutar();
    ui->lblMaas->setText("Kayıt: "+QString::number(ui->tblMaas->rowCount())+" Tutar: "+QString::number(ToplamTutarMaas));
    ///////////////////////////////////////////

    degisiklikIzle=true;
}

void muhasib::maasSil()
{
    QObject* obj = sender();
    QPushButton *btn = qobject_cast<QPushButton *>(obj);
    QList<QPushButton *> allPButtons = ui->tblMaas->findChildren<QPushButton *>();

    int silinecekSatir=-1;
    for(int i=0;i<allPButtons.count();i++)
    {
        if(allPButtons.at(i)==btn)
        {
            silinecekSatir=i/2;
            break;
        }
    }
    //if(kilitAcik==true)//kilidi açık satırı silmeden önce kilidini kapatıyor
    if(ui->tblMaas->item(silinecekSatir,msSutunKilit)->text()=="1")
    {
        QPushButton *btnDegistir=qobject_cast<QPushButton *>(ui->tblMaas->cellWidget(silinecekSatir,msSutunDegistir));
        btnDegistir->click();
    }

    listSilinenMaas.append(ui->tblMaas->item(silinecekSatir,msSutunKayit)->text());

    ToplamTutarMaas=ToplamTutarMaas-ui->tblMaas->item(silinecekSatir,msSutunMaas)->text().toDouble();//silinen Maas tutarını toplamtutar dan çıkarıyor
    ui->tblMaas->removeRow(silinecekSatir);
    ui->lblMaas->setText("Kayıt: "+QString::number(ui->tblMaas->rowCount())+" Tutar: "+QString::number(ToplamTutarMaas));//label i güncelliyor

    kaydetVar=true;
}

void muhasib::maasDegistir()
{
    QObject* obj = sender();
    //çalışanların ismini fonksiyona vermek için
    QStringList listeClsn;
    for(int i=0;i<ui->tblCalisan->rowCount();i++)
    {
        listeClsn.append(ui->tblCalisan->item(i,clsSutunIsim)->text());
    }
    ////////////////////////////////////////////////////////7
    //hesap isimlerini fonksiyona vermek icin
    QStringList listeHsp;
    for(int i=0;i<ui->tblHesap->rowCount();i++)
    {
        listeHsp.append(ui->tblHesap->item(i,hspSutunIsim)->text());
    }
    /////////////////////////////////////////7
    sms.maasDegistir2(degisiklikIzle, kaydetVar, ui->tblMaas, ui->tblHesap, listeHsp, listeClsn, obj);
    //sms.maasDegistir2(degisiklikIzle,kaydetVar,ui->tblMaas,ui->tblCalisan,obj);
}

void muhasib::maasVeritabanindanYukle()
{
    degisiklikIzle=false;//veritabanından yükleme yapılırken toplamtutarı hesaplamasın
    QSqlQuery query;
    query.exec("select m_tarih ,m_calisan ,m_maas ,m_ay ,m_tur, m_id, m_hesap from maas");
    while(query.next())
    {
        ui->tblMaas->insertRow(ui->tblMaas->rowCount());

        QPushButton *btnSil=new QPushButton();
        btnSil->setIcon(QIcon(QDir::currentPath()+"/icons/sil.png"));
        btnSil->setToolTip("Sil");
        connect(btnSil,SIGNAL(clicked()),this,SLOT(maasSil()));
        ui->tblMaas->setCellWidget(ui->tblMaas->rowCount()-1,msSutunSil,btnSil);

        QPushButton *btnDegistir=new QPushButton();
        btnDegistir->setIcon(QIcon(QDir::currentPath()+"/icons/kilitkapali.png"));
        btnDegistir->setToolTip("Degiştir");
        connect(btnDegistir,SIGNAL(clicked()),this,SLOT(maasDegistir()));
        ui->tblMaas->setCellWidget(ui->tblMaas->rowCount()-1,msSutunDegistir,btnDegistir);

        QTableWidgetItem *itm1=new QTableWidgetItem(query.value(0).toString());
        QTableWidgetItem *itm2=new QTableWidgetItem(query.value(1).toString());
        QTableWidgetItem *itm3=new QTableWidgetItem(query.value(2).toString());
        QTableWidgetItem *itm4=new QTableWidgetItem(query.value(3).toString());
        QTableWidgetItem *itm5=new QTableWidgetItem(query.value(4).toString());
        QTableWidgetItem *itm6=new QTableWidgetItem(query.value(5).toString());
        QTableWidgetItem *itm9=new QTableWidgetItem(query.value(6).toString());
        QTableWidgetItem *itm7=new QTableWidgetItem("0");
        QTableWidgetItem *itm8=new QTableWidgetItem("0");

        ui->tblMaas->setItem(ui->tblMaas->rowCount()-1,msSutunTarih,itm1);
        ui->tblMaas->setItem(ui->tblMaas->rowCount()-1,msSutunCalisan,itm2);
        ui->tblMaas->setItem(ui->tblMaas->rowCount()-1,msSutunMaas,itm3);
        ui->tblMaas->setItem(ui->tblMaas->rowCount()-1,msSutunAy,itm4);
        ui->tblMaas->setItem(ui->tblMaas->rowCount()-1,msSutunTur,itm5);
        ui->tblMaas->setItem(ui->tblMaas->rowCount()-1,msSutunHesap,itm9);
        ui->tblMaas->setItem(ui->tblMaas->rowCount()-1,msSutunKayit,itm6);
        ui->tblMaas->setItem(ui->tblMaas->rowCount()-1,msSutunDegisim,itm7);
        ui->tblMaas->setItem(ui->tblMaas->rowCount()-1,msSutunKilit,itm8);

        itm1->setFlags(Qt::ItemIsEnabled);//salt okunur hücreler
        itm2->setFlags(Qt::ItemIsEnabled);
        itm3->setFlags(Qt::ItemIsEnabled);
        itm4->setFlags(Qt::ItemIsEnabled);
        itm5->setFlags(Qt::ItemIsEnabled);
        itm6->setFlags(Qt::ItemIsEnabled);
        itm7->setFlags(Qt::ItemIsEnabled);
        itm8->setFlags(Qt::ItemIsEnabled);
        itm9->setFlags(Qt::ItemIsEnabled);
        ToplamTutarMaas=ToplamTutarMaas+itm3->text().toDouble();//toplam tutarı uygulama başlayınca hesaplıyor
    }
    ui->lblMaas->setText("Kayıt: "+QString::number(ui->tblMaas->rowCount())+" Tutar: "+QString::number(ToplamTutarMaas));
    degisiklikIzle=true;
}

void muhasib::cbCekDegisti()
{
    if(ui->cbAlinanCek->isChecked() && ui->cbVerilenCek->isChecked())
    {
        for(int i=0;i<ui->tblCek->rowCount();i++)
        {
            ui->tblCek->showRow(i);
        }
        ui->lblCek2->hide();
    }
    else if(!ui->cbAlinanCek->isChecked() && !ui->cbVerilenCek->isChecked())
    {
        for(int i=0;i<ui->tblCek->rowCount();i++)
        {
            ui->tblCek->hideRow(i);
        }
        ui->lblCek2->hide();
    }
    else if(!ui->cbAlinanCek->isChecked() && ui->cbVerilenCek->isChecked())//giden faturalar gösteriliyor
    {
        double kismiTutar=0;
        int girisSayisi=0;
        for(int i=0;i<ui->tblCek->rowCount();i++)
        {
            if(ui->tblCek->item(i,ckSutunTur)->text()=="Alınan")
            {
                ui->tblCek->hideRow(i);
            }
            else
            {
                ui->tblCek->showRow(i);
                //toplam tutar ve kayıt sayısı hesaplanıyor
                kismiTutar=kismiTutar+ui->tblCek->item(i,ckSutunTutar)->text().toDouble();
                girisSayisi=girisSayisi+1;
                ///////////////////////////////////////////
            }
        }
        //toplam tutar ve kayıt sayısı yazdırılıyor
        ui->lblCek2->setText("(Kayıt: "+QString::number(girisSayisi)+" Tutar: "+QString::number(kismiTutar)+")");
        ui->lblCek2->show();
        ///////////////////////////////////////////
    }
    else if(ui->cbAlinanCek->isChecked() && !ui->cbVerilenCek->isChecked())//gelen faturalar gösteriliyor
    {
        double kismiTutar=0;
        int girisSayisi=0;
        for(int i=0;i<ui->tblCek->rowCount();i++)
        {
            if(ui->tblCek->item(i,ckSutunTur)->text()=="Verilen")
            {
                ui->tblCek->hideRow(i);
            }
            else
            {
                ui->tblCek->showRow(i);
                //toplam tutar ve kayıt sayısı hesaplanıyor
                kismiTutar=kismiTutar+ui->tblCek->item(i,ckSutunTutar)->text().toDouble();
                girisSayisi=girisSayisi+1;
                ///////////////////////////////////////////
            }
        }
        //toplam tutar ve kayıt sayısı yazdırılıyor
        ui->lblCek2->setText("(Kayıt: "+QString::number(girisSayisi)+" Tutar: "+QString::number(kismiTutar)+")");
        ui->lblCek2->show();
        ///////////////////////////////////////////
    }
}

void muhasib::cekToplamiHesapla(int a,int b)
{
    if(degisiklikIzle==true && b==ckSutunTutar)
    {
        ToplamTutarCek=0;
        for(int i=0;i<ui->tblCek->rowCount();i++)
        {
            ToplamTutarCek=ToplamTutarCek+ui->tblCek->item(i,ckSutunTutar)->text().toDouble();
        }
        ui->lblCek->setText("Kayıt: "+QString::number(ui->tblCek->rowCount())+" Tutar: "+QString::number(ToplamTutarCek));
    }
}

void muhasib::cekOzetiRaporlaSonuc(QTableWidget *tblOzet, QTableWidget *tbl, QLabel *lbl, QDate baslangic, QDate bitis, QString tur)
{
    double tutar=0;
    tblOzet->setRowCount(0);
    for(int i=0;i<tbl->rowCount();i++)
    {
        if(tbl->item(i,ckSutunTur)->text()==tur)
        {
            QDateTime datet;
            int gun=datet.fromString(tbl->item(i,ckSutunTarih)->text(),"yyyy-MM-dd").date().day();
            int ay=datet.fromString(tbl->item(i,ckSutunTarih)->text(),"yyyy-MM-dd").date().month();
            int yil=datet.fromString(tbl->item(i,ckSutunTarih)->text(),"yyyy-MM-dd").date().year();

            QDate tarih;
            tarih.setDate(yil,ay,gun);

            if(tarih>=baslangic && tarih<=bitis)
            {
                tblOzet->insertRow(tblOzet->rowCount());
                QTableWidgetItem *itm0=new QTableWidgetItem(tbl->item(i,ckSutunTarih)->text());
                QTableWidgetItem *itm1=new QTableWidgetItem(tbl->item(i,ckSutunIsim)->text());
                QTableWidgetItem *itm2=new QTableWidgetItem(tbl->item(i,ckSutunBanka)->text());
                QTableWidgetItem *itm3=new QTableWidgetItem(tbl->item(i,ckSutunTutar)->text());
                QTableWidgetItem *itm4=new QTableWidgetItem(tbl->item(i,ckSutunMuhatap)->text());
                QTableWidgetItem *itm5=new QTableWidgetItem(tbl->item(i,ckSutunCekNo)->text());
                QTableWidgetItem *itm6=new QTableWidgetItem(tbl->item(i,ckSutunAciklama)->text());
                tblOzet->setItem(tblOzet->rowCount()-1,ckSutunTarih-2,itm0);//sil ve değiştir olmadığı için 2 çıkarıyoruz
                tblOzet->setItem(tblOzet->rowCount()-1,ckSutunIsim-2,itm1);
                tblOzet->setItem(tblOzet->rowCount()-1,ckSutunBanka-2,itm2);
                tblOzet->setItem(tblOzet->rowCount()-1,ckSutunTutar-2,itm3);
                tblOzet->setItem(tblOzet->rowCount()-1,ckSutunMuhatap-2,itm4);
                tblOzet->setItem(tblOzet->rowCount()-1,ckSutunCekNo-2,itm5);
                tblOzet->setItem(tblOzet->rowCount()-1,ckSutunAciklama-2,itm6);
                //tutar=tutar+tbl->item(i,ckSutunTutar)->text().toDouble();
                tutar=tutar+tblOzet->item(tblOzet->rowCount()-1,ftrSutunTutar-2)->text().toDouble();
            }
        }
    }
    lbl->setText("Kayıt: "+QString::number(tblOzet->rowCount())+" Tutar: "+QString::number(tutar));
}

void muhasib::cekOzetiRaporla()
{
    if(ui->lblCekKarsilastirBaslangicTarihi->text()=="" || ui->lblCekKarsilastirBitisTarihi->text()=="")
    {
        QMessageBox::warning(this,"Hata","Rapor için önce tarih seçin","Tamam");
    }
    else
    {
        //labelBaslangic ve bitisteki tarhileri alıp karşılaştırıyor
        QDateTime datet;
        int gun=datet.fromString(ui->lblCekKarsilastirBaslangicTarihi->text(),"yyyy-MM-dd").date().day();
        int ay=datet.fromString(ui->lblCekKarsilastirBaslangicTarihi->text(),"yyyy-MM-dd").date().month();
        int yil=datet.fromString(ui->lblCekKarsilastirBaslangicTarihi->text(),"yyyy-MM-dd").date().year();

        QDate baslangic;
        baslangic.setDate(yil,ay,gun);

        gun=datet.fromString(ui->lblCekKarsilastirBitisTarihi->text(),"yyyy-MM-dd").date().day();
        ay=datet.fromString(ui->lblCekKarsilastirBitisTarihi->text(),"yyyy-MM-dd").date().month();
        yil=datet.fromString(ui->lblCekKarsilastirBitisTarihi->text(),"yyyy-MM-dd").date().year();

        QDate bitis;
        bitis.setDate(yil,ay,gun);

        if(bitis<baslangic)
        {
            QMessageBox::warning(this,"Hata","Bitiş tarihi başlangıç tarihinden büyük olamaz","Tamam");
        }
        ////////////////////////////////////////

        else
        {
            cekOzetiRaporlaSonuc(ui->tblAlinanCek,ui->tblCek,ui->lblAlinanCekSonuc,baslangic,bitis,"Alınan");
            cekOzetiRaporlaSonuc(ui->tblVerilenCek,ui->tblCek,ui->lblVerilenCekSonuc,baslangic,bitis,"Verilen");
        }
    }
}

void muhasib::cekOzetiTakvimAc()
{
    QCalendarWidget *cal=new QCalendarWidget();
    cal->setLocale(QLocale::Turkish);
    cal->setFirstDayOfWeek(Qt::Monday);
    if(sender()->objectName()=="btnCekKarsilastirBaslangicTarihi")
    {
        cal->setObjectName("baslangic");
        cal->setWindowTitle("Başlangıç Tarihi Seç");
    }
    else if(sender()->objectName()=="btnCekKarsilastirBitisTarihi")
    {
        cal->setObjectName("bitis");
        cal->setWindowTitle("Bitiş Tarihi Seç");
    }
    cal->show();
    connect(cal,SIGNAL(activated(QDate)),this,SLOT(cekOzetiTarihAl()));
}

void muhasib::cekOzetiTarihAl()
{
    QObject* obj = sender();
    QCalendarWidget *cal = qobject_cast<QCalendarWidget *>(obj);
    if(sender()->objectName()=="baslangic")
    {
        ui->lblCekKarsilastirBaslangicTarihi->setText(cal->selectedDate().toString("yyyy-MM-dd"));
    }
    else if(sender()->objectName()=="bitis")
    {
        ui->lblCekKarsilastirBitisTarihi->setText(cal->selectedDate().toString("yyyy-MM-dd"));
    }
    cal->close();
}

void muhasib::sekmeCekOzetiAc()
{
    ui->tabWidget->addTab(tbCekOzeti,"Çekleri Karşılaştır");
    ui->tabWidget->setCurrentWidget(tbCekOzeti);
}

//CEK EKLEME EKRANI AÇILIYOR
void muhasib::yeniCekEkle()
{
    degisiklikIzle=false;
    form_cekEkle.setWindowFlags(Qt::Window);//cek ekleme penceresinin köşesindeki 3 düğmenin gösterilmesi için
    form_cekEkle.ontanimliAyarlar();
    this->setEnabled(false);//ana pencere etkisizleştiriliyor
    form_cekEkle.exec();
    QStringList listeCek=form_cekEkle.getListeCek();
    //qDebug()<<"listeCek:"<<listeCek;
    if(listeCek.count()!=0)//cek ekle ekranında kapat'a tıklanırsa cek sekmesi açılmasın ve kaydetvar true olmasın
    {
        sekmeCekAc();
        kaydetVar=true;
    }
    this->setEnabled(true);//ana pencere etkinleştiriliyor

    for(int i=0;i<listeCek.count();i=i+8)//8 sutun var cek ekleme penceresinde
    {
        ui->tblCek->insertRow(ui->tblCek->rowCount());

        QPushButton *btnSil=new QPushButton();
        btnSil->setIcon(QIcon(QDir::currentPath()+"/icons/sil.png"));
        btnSil->setToolTip("Sil");
        connect(btnSil,SIGNAL(clicked()),this,SLOT(cekSil()));
        ui->tblCek->setCellWidget(ui->tblCek->rowCount()-1,ckSutunSil,btnSil);

        QPushButton *btnDegistir=new QPushButton();
        btnDegistir->setIcon(QIcon(QDir::currentPath()+"/icons/kilitkapali.png"));
        btnDegistir->setToolTip("Degiştir");
        connect(btnDegistir,SIGNAL(clicked()),this,SLOT(cekDegistir()));
        ui->tblCek->setCellWidget(ui->tblCek->rowCount()-1,ckSutunDegistir,btnDegistir);

        QTableWidgetItem *itm1=new QTableWidgetItem(listeCek.at(i));
        ui->tblCek->setItem(ui->tblCek->rowCount()-1,ckSutunTarih,itm1);
        QTableWidgetItem *itm2=new QTableWidgetItem(listeCek.at(i+1));
        ui->tblCek->setItem(ui->tblCek->rowCount()-1,ckSutunIsim,itm2);
        QTableWidgetItem *itm3=new QTableWidgetItem(listeCek.at(i+2));
        ui->tblCek->setItem(ui->tblCek->rowCount()-1,ckSutunBanka,itm3);
        QTableWidgetItem *itm4=new QTableWidgetItem(listeCek.at(i+3));
        ui->tblCek->setItem(ui->tblCek->rowCount()-1,ckSutunTutar,itm4);
        QTableWidgetItem *itm5=new QTableWidgetItem(listeCek.at(i+4));
        ui->tblCek->setItem(ui->tblCek->rowCount()-1,ckSutunMuhatap,itm5);
        QTableWidgetItem *itm6=new QTableWidgetItem(listeCek.at(i+5));
        ui->tblCek->setItem(ui->tblCek->rowCount()-1,ckSutunCekNo,itm6);
        QTableWidgetItem *itm7=new QTableWidgetItem(listeCek.at(i+6));
        ui->tblCek->setItem(ui->tblCek->rowCount()-1,ckSutunAciklama,itm7);
        QTableWidgetItem *itm8=new QTableWidgetItem(listeCek.at(i+7));
        ui->tblCek->setItem(ui->tblCek->rowCount()-1,ckSutunTur,itm8);
        QTableWidgetItem *itm9=new QTableWidgetItem("0");
        ui->tblCek->setItem(ui->tblCek->rowCount()-1,ckSutunKayit,itm9);
        QTableWidgetItem *itm10=new QTableWidgetItem("0");
        ui->tblCek->setItem(ui->tblCek->rowCount()-1,ckSutunDegisim,itm10);
        QTableWidgetItem *itm11=new QTableWidgetItem("0");
        ui->tblCek->setItem(ui->tblCek->rowCount()-1,ckSutunKilit,itm11);

        itm1->setFlags(Qt::ItemIsEnabled);//salt okunur hücreler
        itm2->setFlags(Qt::ItemIsEnabled);
        itm3->setFlags(Qt::ItemIsEnabled);
        itm4->setFlags(Qt::ItemIsEnabled);
        itm5->setFlags(Qt::ItemIsEnabled);
        itm6->setFlags(Qt::ItemIsEnabled);
        itm7->setFlags(Qt::ItemIsEnabled);
        itm8->setFlags(Qt::ItemIsEnabled);
        itm9->setFlags(Qt::ItemIsEnabled);
        itm10->setFlags(Qt::ItemIsEnabled);
    }

    //toplam tutar ve kayıt sayısı yazdırılıyor
    ToplamTutarCek=ToplamTutarCek+form_cekEkle.getToplamTutar();
    ui->lblCek->setText("Kayıt: "+QString::number(ui->tblCek->rowCount())+" Tutar: "+QString::number(ToplamTutarCek));
    ///////////////////////////////////////////

    degisiklikIzle=true;
}

void muhasib::sekmeCekAc()
{
    ui->tabWidget->addTab(tbCek,"Çekler");
    ui->tabWidget->setCurrentWidget(tbCek);
}

void muhasib::cekSil()
{
    QObject* obj = sender();
    sck.cekSil2(ToplamTutarCek, listSilinenCek, kaydetVar, ui->lblCek, ui->tblCek, obj);
}

void muhasib::cekDegistir()
{
    QObject* obj = sender();
    sck.cekDegistir2(degisiklikIzle, kaydetVar,ui->tblCek,obj);
}

void muhasib::cekKaydet()
{
    sck.cekKaydet2(listSilinenCek,ui->tblCek);
}

void muhasib::cekVeritabanindanYukle()
{
    degisiklikIzle=false;//veritabanından yükleme yapılırken toplamtutarı hesaplamasın
    QSqlQuery query;
    query.exec("select c_tarih, c_isim, c_banka, c_tutar, c_muhatap, c_cekno, c_aciklama, c_tur, c_id from cek");
    while(query.next())
    {
        ui->tblCek->insertRow(ui->tblCek->rowCount());

        QPushButton *btnSil=new QPushButton();
        btnSil->setIcon(QIcon(QDir::currentPath()+"/icons/sil.png"));
        btnSil->setToolTip("Sil");
        connect(btnSil,SIGNAL(clicked()),this,SLOT(cekSil()));
        ui->tblCek->setCellWidget(ui->tblCek->rowCount()-1,ckSutunSil,btnSil);

        QPushButton *btnDegistir=new QPushButton();
        btnDegistir->setIcon(QIcon(QDir::currentPath()+"/icons/kilitkapali.png"));
        btnDegistir->setToolTip("Degiştir");
        connect(btnDegistir,SIGNAL(clicked()),this,SLOT(cekDegistir()));
        ui->tblCek->setCellWidget(ui->tblCek->rowCount()-1,ckSutunDegistir,btnDegistir);

        QTableWidgetItem *itm1=new QTableWidgetItem(query.value(0).toString());
        ui->tblCek->setItem(ui->tblCek->rowCount()-1,ckSutunTarih,itm1);
        QTableWidgetItem *itm2=new QTableWidgetItem(query.value(1).toString());
        ui->tblCek->setItem(ui->tblCek->rowCount()-1,ckSutunIsim,itm2);
        QTableWidgetItem *itm3=new QTableWidgetItem(query.value(2).toString());
        ui->tblCek->setItem(ui->tblCek->rowCount()-1,ckSutunBanka,itm3);
        QTableWidgetItem *itm4=new QTableWidgetItem(query.value(3).toString());
        ui->tblCek->setItem(ui->tblCek->rowCount()-1,ckSutunTutar,itm4);
        QTableWidgetItem *itm5=new QTableWidgetItem(query.value(4).toString());
        ui->tblCek->setItem(ui->tblCek->rowCount()-1,ckSutunMuhatap,itm5);
        QTableWidgetItem *itm6=new QTableWidgetItem(query.value(5).toString());
        ui->tblCek->setItem(ui->tblCek->rowCount()-1,ckSutunCekNo,itm6);
        QTableWidgetItem *itm7=new QTableWidgetItem(query.value(6).toString());
        ui->tblCek->setItem(ui->tblCek->rowCount()-1,ckSutunAciklama,itm7);
        QTableWidgetItem *itm8=new QTableWidgetItem(query.value(7).toString());
        ui->tblCek->setItem(ui->tblCek->rowCount()-1,ckSutunTur,itm8);
        QTableWidgetItem *itm9=new QTableWidgetItem(query.value(8).toString());
        ui->tblCek->setItem(ui->tblCek->rowCount()-1,ckSutunKayit,itm9);
        QTableWidgetItem *itm10=new QTableWidgetItem("0");
        ui->tblCek->setItem(ui->tblCek->rowCount()-1,ckSutunDegisim,itm10);
        QTableWidgetItem *itm11=new QTableWidgetItem("0");
        ui->tblCek->setItem(ui->tblCek->rowCount()-1,ckSutunKilit,itm11);

        itm1->setFlags(Qt::ItemIsEnabled);//salt okunur hücreler
        itm2->setFlags(Qt::ItemIsEnabled);
        itm3->setFlags(Qt::ItemIsEnabled);
        itm4->setFlags(Qt::ItemIsEnabled);
        itm5->setFlags(Qt::ItemIsEnabled);
        itm6->setFlags(Qt::ItemIsEnabled);
        itm7->setFlags(Qt::ItemIsEnabled);
        itm8->setFlags(Qt::ItemIsEnabled);
        itm9->setFlags(Qt::ItemIsEnabled);
        itm10->setFlags(Qt::ItemIsEnabled);
        itm11->setFlags(Qt::ItemIsEnabled);

        ToplamTutarCek=ToplamTutarCek+itm3->text().toDouble();//toplam tutarı uygulama başlayınca hesaplıyor
    }
    ui->lblCek->setText("Kayıt: "+QString::number(ui->tblCek->rowCount())+" Tutar: "+QString::number(ToplamTutarCek));
    //degisiklikIzle=true;
}

//FATURA ANA EKRANINDA MATRAH VE KDV ORANI DEĞİŞTİRİNCE KDV TUTARINI VE TUTARI YENİDEN HESAPLIYOR
void muhasib::faturaTutarHesapla(int a,int b)
{
    if(degisiklikIzle==true)
    {
        if(b==ftrSutunMatrah || b==ftrSutunKdvOrani)
        {
            double kdvTutari=ui->tblFatura->item(a,ftrSutunMatrah)->text().toDouble()*ui->tblFatura->item(a,ftrSutunKdvOrani)->text().toDouble()/100;
            double tutar=ui->tblFatura->item(a,ftrSutunMatrah)->text().toDouble()+kdvTutari;

            ui->tblFatura->item(a,ftrSutunKdvTutar)->setText(QString::number(kdvTutari));
            ui->tblFatura->item(a,ftrSutunTutar)->setText(QString::number(tutar));
        }
    }
}

//ANA FATURA EKRANINDAN FATURA ÖZET EKRANINA BİLGİLERİ TAŞIYOR
void muhasib::faturaOzetiRaporlaSonuc(QTableWidget *tblOzet, QTableWidget *tbl, QLabel *lbl, QDate baslangic, QDate bitis, QString tur)
{
    double tutar=0;
    tblOzet->setRowCount(0);
    for(int i=0;i<tbl->rowCount();i++)
    {
        if(tbl->item(i,ftrSutunTur)->text()==tur)
        {
            QDateTime datet;
            int gun=datet.fromString(tbl->item(i,ftrSutunTarih)->text(),"yyyy-MM-dd").date().day();
            int ay=datet.fromString(tbl->item(i,ftrSutunTarih)->text(),"yyyy-MM-dd").date().month();
            int yil=datet.fromString(tbl->item(i,ftrSutunTarih)->text(),"yyyy-MM-dd").date().year();

            QDate tarih;
            tarih.setDate(yil,ay,gun);

            if(tarih>=baslangic && tarih<=bitis)
            {
                tblOzet->insertRow(tblOzet->rowCount());
                QTableWidgetItem *itm0=new QTableWidgetItem(tbl->item(i,ftrSutunTarih)->text());
                QTableWidgetItem *itm1=new QTableWidgetItem(tbl->item(i,ftrSutunIsim)->text());
                QTableWidgetItem *itm2=new QTableWidgetItem(tbl->item(i,ftrSutunTutar)->text());
                QTableWidgetItem *itm3=new QTableWidgetItem(tbl->item(i,ftrSutunAciklama)->text());
                QTableWidgetItem *itm4=new QTableWidgetItem(tbl->item(i,ftrSutunMatrah)->text());
                QTableWidgetItem *itm5=new QTableWidgetItem(tbl->item(i,ftrSutunKdvOrani)->text());
                QTableWidgetItem *itm6=new QTableWidgetItem(tbl->item(i,ftrSutunKdvTutar)->text());
                tblOzet->setItem(tblOzet->rowCount()-1,ftrSutunTarih-2,itm0);//sil ve değiştir olmadığı için -2 yazıyoruz
                tblOzet->setItem(tblOzet->rowCount()-1,ftrSutunIsim-2,itm1);
                tblOzet->setItem(tblOzet->rowCount()-1,ftrSutunTutar-2,itm2);
                tblOzet->setItem(tblOzet->rowCount()-1,ftrSutunAciklama-2,itm3);
                tblOzet->setItem(tblOzet->rowCount()-1,ftrSutunMatrah-2,itm4);
                tblOzet->setItem(tblOzet->rowCount()-1,ftrSutunKdvOrani-2,itm5);
                tblOzet->setItem(tblOzet->rowCount()-1,ftrSutunKdvTutar-2,itm6);
                //tutar=tutar+tbl->item(i,ftrSutunTutar)->text().toDouble();
                tutar=tutar+tblOzet->item(tblOzet->rowCount()-1,ftrSutunTutar-2)->text().toDouble();
            }
        }
    }
    lbl->setText("Kayıt: "+QString::number(tblOzet->rowCount())+" Tutar: "+QString::number(tutar));
}

//FATURA ÖZETİ EKRANINDA RAPORLA DÜĞMESİNE BASILINCA ÇALIŞIYOR
void muhasib::faturaOzetiRaporla()
{
    if(ui->lblFaturaKarsilastirBaslangicTarihi->text()=="" || ui->lblFaturaKarsilastirBitisTarihi->text()=="")
    {
        QMessageBox::warning(this,"Hata","Rapor için önce tarih seçin","Tamam");
    }
    else
    {
        //labelBaslangic ve bitisteki tarihleri alıp karşılaştırıyor
        QDateTime datet;
        int gun=datet.fromString(ui->lblFaturaKarsilastirBaslangicTarihi->text(),"yyyy-MM-dd").date().day();
        int ay=datet.fromString(ui->lblFaturaKarsilastirBaslangicTarihi->text(),"yyyy-MM-dd").date().month();
        int yil=datet.fromString(ui->lblFaturaKarsilastirBaslangicTarihi->text(),"yyyy-MM-dd").date().year();

        QDate baslangic;
        baslangic.setDate(yil,ay,gun);

        gun=datet.fromString(ui->lblFaturaKarsilastirBitisTarihi->text(),"yyyy-MM-dd").date().day();
        ay=datet.fromString(ui->lblFaturaKarsilastirBitisTarihi->text(),"yyyy-MM-dd").date().month();
        yil=datet.fromString(ui->lblFaturaKarsilastirBitisTarihi->text(),"yyyy-MM-dd").date().year();

        QDate bitis;
        bitis.setDate(yil,ay,gun);

        if(bitis<baslangic)
        {
            QMessageBox::warning(this,"Hata","Bitiş tarihi başlangıç tarihinden büyük olamaz","Tamam");
        }
        ////////////////////////////////////////
        else
        {
            faturaOzetiRaporlaSonuc(ui->tblGelenFaturalar,ui->tblFatura,ui->lblGelenFaturalarSonuc,baslangic,bitis,"Gelen");
            faturaOzetiRaporlaSonuc(ui->tblGidenFaturalar,ui->tblFatura,ui->lblGidenFaturalarSonuc,baslangic,bitis,"Giden");
        }
    }
}

//FATURA ÖZETİ VE LİSTELE PENCERESİNDE TAKVİMİ ACIYoR
void muhasib::faturaTakvimAc()
{
    QCalendarWidget *cal=new QCalendarWidget();
    cal->setLocale(QLocale::Turkish);
    cal->setFirstDayOfWeek(Qt::Monday);
    qDebug()<<":"<<sender()->objectName();
    if(sender()->objectName()=="btnFaturaKarsilastirBaslangicTarihi")
    {
        cal->setObjectName("karsilastirBaslangic");
        cal->setWindowTitle("Başlangıç Tarihi Seç");
    }
    else if(sender()->objectName()=="btnFaturaKarsilastirBitisTarihi")
    {
        cal->setObjectName("karsilastirBitis");
        cal->setWindowTitle("Bitiş Tarihi Seç");
    }
    else if(sender()->objectName()=="btnFaturaListeleBaslangicTarihi")
    {
        cal->setObjectName("listeleBaslangic");
        cal->setWindowTitle("Başlangıç Tarihi Seç");
    }
    else if(sender()->objectName()=="btnFaturaListeleBitisTarihi")
    {
        cal->setObjectName("listeleBitis");
        cal->setWindowTitle("Bitiş Tarihi Seç");
    }
    cal->show();
    connect(cal,SIGNAL(activated(QDate)),this,SLOT(faturaTarihAl()));
}

//FATURA ÖZETİ VE LİSTELE PENCERESİNDE TAKVİME ÇİFT TIKLAYINCA TARİHİ ALIYOR
void muhasib::faturaTarihAl()
{
    QObject* obj = sender();
    QCalendarWidget *cal = qobject_cast<QCalendarWidget *>(obj);
    if(sender()->objectName()=="karsilastirBaslangic")
    {
        ui->lblFaturaKarsilastirBaslangicTarihi->setText(cal->selectedDate().toString("yyyy-MM-dd"));
    }
    else if(sender()->objectName()=="karsilastirBitis")
    {
        ui->lblFaturaKarsilastirBitisTarihi->setText(cal->selectedDate().toString("yyyy-MM-dd"));
    }
    /*
    if(sender()->objectName()=="listeleBaslangic")
    {
        ui->lblFaturaListeleBaslangicTarihi->setText(cal->selectedDate().toString("yyyy-MM-dd"));
    }
    else if(sender()->objectName()=="listeleBitis")
    {
        ui->lblFaturaListeleBitisTarihi->setText(cal->selectedDate().toString("yyyy-MM-dd"));
    }
    */
    cal->close();
}

//FATURA ÖZETİ AÇ
void muhasib::sekmeFaturaOzetiAc()
{
    ui->tabWidget->addTab(tbFaturaOzeti,"Faturaları Karşılaştır");
    ui->tabWidget->setCurrentWidget(tbFaturaOzeti);
}

//UYGULAMA BASLADIGINDA VERİTABANİNDAN KAYITLARI YÜKLÜYOR
void muhasib::faturaVeritabanindanYukle()
{
    degisiklikIzle=false;//veritabanından yükleme yapılırken toplamtutarı hesaplamasın
    QSqlQuery query;
    query.exec("select f_tarih, f_isim, f_matrah, f_kdvorani, f_kdvtutari, f_tutar, f_aciklama, f_tur, f_id, f_hesap from fatura");
    while(query.next())
    {
        ui->tblFatura->insertRow(ui->tblFatura->rowCount());

        QPushButton *btnSil=new QPushButton();
        btnSil->setIcon(QIcon(QDir::currentPath()+"/icons/sil.png"));
        btnSil->setToolTip("Sil");
        connect(btnSil,SIGNAL(clicked()),this,SLOT(faturaSil()));
        ui->tblFatura->setCellWidget(ui->tblFatura->rowCount()-1,ftrSutunSil,btnSil);

        QPushButton *btnDegistir=new QPushButton();
        btnDegistir->setIcon(QIcon(QDir::currentPath()+"/icons/kilitkapali.png"));
        btnDegistir->setToolTip("Degiştir");
        connect(btnDegistir,SIGNAL(clicked()),this,SLOT(faturaDegistir()));
        ui->tblFatura->setCellWidget(ui->tblFatura->rowCount()-1,ftrSutunDegistir,btnDegistir);

        QTableWidgetItem *itm1=new QTableWidgetItem(query.value(0).toString());
        QTableWidgetItem *itm2=new QTableWidgetItem(query.value(1).toString());
        QTableWidgetItem *itm3=new QTableWidgetItem(query.value(2).toString());
        QTableWidgetItem *itm4=new QTableWidgetItem(query.value(3).toString());
        QTableWidgetItem *itm5=new QTableWidgetItem(query.value(4).toString());
        QTableWidgetItem *itm6=new QTableWidgetItem(query.value(5).toString());
        QTableWidgetItem *itm7=new QTableWidgetItem(query.value(6).toString());
        QTableWidgetItem *itm8=new QTableWidgetItem(query.value(7).toString());
        QTableWidgetItem *itm9=new QTableWidgetItem(query.value(8).toString());
        QTableWidgetItem *itm12=new QTableWidgetItem(query.value(9).toString());
        QTableWidgetItem *itm10=new QTableWidgetItem("0");
        QTableWidgetItem *itm11=new QTableWidgetItem("0");

        ui->tblFatura->setItem(ui->tblFatura->rowCount()-1,ftrSutunTarih,itm1);
        ui->tblFatura->setItem(ui->tblFatura->rowCount()-1,ftrSutunIsim,itm2);
        ui->tblFatura->setItem(ui->tblFatura->rowCount()-1,ftrSutunMatrah,itm3);
        ui->tblFatura->setItem(ui->tblFatura->rowCount()-1,ftrSutunKdvOrani,itm4);
        ui->tblFatura->setItem(ui->tblFatura->rowCount()-1,ftrSutunKdvTutar,itm5);
        ui->tblFatura->setItem(ui->tblFatura->rowCount()-1,ftrSutunTutar,itm6);
        ui->tblFatura->setItem(ui->tblFatura->rowCount()-1,ftrSutunAciklama,itm7);
        ui->tblFatura->setItem(ui->tblFatura->rowCount()-1,ftrSutunTur,itm8);
        ui->tblFatura->setItem(ui->tblFatura->rowCount()-1,ftrSutunKayit,itm9);
        ui->tblFatura->setItem(ui->tblFatura->rowCount()-1,ftrSutunDegisim,itm10);
        ui->tblFatura->setItem(ui->tblFatura->rowCount()-1,ftrSutunKilit,itm11);
        ui->tblFatura->setItem(ui->tblFatura->rowCount()-1,ftrSutunHesap,itm12);

        itm1->setFlags(Qt::ItemIsEnabled);//salt okunur hücreler
        itm2->setFlags(Qt::ItemIsEnabled);
        itm3->setFlags(Qt::ItemIsEnabled);
        itm4->setFlags(Qt::ItemIsEnabled);
        itm5->setFlags(Qt::ItemIsEnabled);
        itm6->setFlags(Qt::ItemIsEnabled);
        itm7->setFlags(Qt::ItemIsEnabled);
        itm8->setFlags(Qt::ItemIsEnabled);
        itm9->setFlags(Qt::ItemIsEnabled);
        itm10->setFlags(Qt::ItemIsEnabled);
        itm11->setFlags(Qt::ItemIsEnabled);
        itm12->setFlags(Qt::ItemIsEnabled);
        ToplamTutarFatura=ToplamTutarFatura+itm6->text().toDouble();//toplam tutarı uygulama başlayınca hesaplıyor
    }
    ui->lblFatura->setText("Kayıt: "+QString::number(ui->tblFatura->rowCount())+" Tutar: "+QString::number(ToplamTutarFatura));
    degisiklikIzle=true;
    ui->tblFatura->sortByColumn(ftrSutunTarih);//tblfaturayı tarih sutunua göre sıralıyor
}

//FATURALARI KAYDEDİYOR
void muhasib::faturaKaydet()
{
    sftr.faturaKaydet2(listSilinenFatura,ui->tblFatura);
}

//ANA EKRANDA FATURA TUTARI DEĞİŞTİKÇE TOPLAMIDA DEĞİŞİYOR
void muhasib::faturaToplamiHesapla(int a ,int b)
{
    if(degisiklikIzle==true && b==ftrSutunTutar)
    {
        ToplamTutarFatura=0;
        for(int i=0;i<ui->tblFatura->rowCount();i++)
        {
            ToplamTutarFatura=ToplamTutarFatura+ui->tblFatura->item(i,ftrSutunTutar)->text().toDouble();
        }
        ui->lblFatura->setText("Kayıt: "+QString::number(ui->tblFatura->rowCount())+" Tutar: "+QString::number(ToplamTutarFatura));
    }
}

//FATURA SEKMESİNİ AÇIYOR
void muhasib::sekmeFaturaAc()
{
    ui->tabWidget->addTab(tbFatura,"Faturalar");
    ui->tabWidget->setCurrentWidget(tbFatura);
}

//FATURA EKLEME EKRANINI AÇIYOR
void muhasib::yeniFaturaEkle()
{
    degisiklikIzle=false;
    form_faturaEkle.setWindowFlags(Qt::Window);//fatura ekleme penceresinin köşesindeki 3 düğmenin gösterilmesi için

    //fatura ekleme penceresinde hesapların isminin çıkabilmesi için
    QStringList listeHsp;
    for(int i=0;i<ui->tblHesap->rowCount();i++)
    {
        listeHsp.append(ui->tblHesap->item(i,hspSutunIsim)->text());
    }
    form_faturaEkle.setListeHesap(listeHsp);
    ////////////////////////////////////////////////////////7

    form_faturaEkle.ontanimliAyarlar();
    this->setEnabled(false);//ana pencere etkisizleştiriliyor
    form_faturaEkle.exec();
    QStringList listeFatura=form_faturaEkle.getListeFatura();
    qDebug()<<"listeFatura"<<listeFatura;
    if(listeFatura.count()!=0)//fatura ekle ekranında kapat'a tıklanırsa fatura sekmesi açılmasın ve kaydetvar true olmasın
    {
        sekmeFaturaAc();
        kaydetVar=true;
    }
    this->setEnabled(true);//ana pencere etkinleştiriliyor

    for(int i=0;i<listeFatura.count();i=i+9)//9 sutun var fatura ekleme penceresinde
    {
        ui->tblFatura->insertRow(ui->tblFatura->rowCount());

        QPushButton *btnSil=new QPushButton();
        btnSil->setIcon(QIcon(QDir::currentPath()+"/icons/sil.png"));
        btnSil->setToolTip("Sil");
        connect(btnSil,SIGNAL(clicked()),this,SLOT(faturaSil()));
        ui->tblFatura->setCellWidget(ui->tblFatura->rowCount()-1,ftrSutunSil,btnSil);

        QPushButton *btnDegistir=new QPushButton();
        btnDegistir->setIcon(QIcon(QDir::currentPath()+"/icons/kilitkapali.png"));
        btnDegistir->setToolTip("Degiştir");
        connect(btnDegistir,SIGNAL(clicked()),this,SLOT(faturaDegistir()));
        ui->tblFatura->setCellWidget(ui->tblFatura->rowCount()-1,ftrSutunDegistir,btnDegistir);

        //double kdvTutari=listeFatura.at(i+2).toDouble()*listeFatura.at(i+3).toDouble()/100;

        //QDate tarih=QDate::fromString(listeFatura.at(i),"dd / MM / yyyy");
        //QTableWidgetItem *itm1=new QTableWidgetItem();
        //itm1->setData(Qt::DisplayRole,tarih);
        //ui->tblFatura->setItem(ui->tblFatura->rowCount()-1,ftrSutunTarih,itm1);

        QTableWidgetItem *itm1=new QTableWidgetItem(listeFatura.at(i));
        QTableWidgetItem *itm2=new QTableWidgetItem(listeFatura.at(i+1));
        QTableWidgetItem *itm3=new QTableWidgetItem(listeFatura.at(i+2));
        QTableWidgetItem *itm4=new QTableWidgetItem(listeFatura.at(i+3));
        QTableWidgetItem *itm5=new QTableWidgetItem(listeFatura.at(i+4));
        QTableWidgetItem *itm6=new QTableWidgetItem(listeFatura.at(i+5));
        QTableWidgetItem *itm7=new QTableWidgetItem(listeFatura.at(i+6));
        QTableWidgetItem *itm8=new QTableWidgetItem(listeFatura.at(i+7));
        QTableWidgetItem *itm12=new QTableWidgetItem(listeFatura.at(i+8));
        QTableWidgetItem *itm9=new QTableWidgetItem("0");
        QTableWidgetItem *itm10=new QTableWidgetItem("0");
        QTableWidgetItem *itm11=new QTableWidgetItem("0");

        ui->tblFatura->setItem(ui->tblFatura->rowCount()-1,ftrSutunTarih,itm1);
        ui->tblFatura->setItem(ui->tblFatura->rowCount()-1,ftrSutunIsim,itm2);
        ui->tblFatura->setItem(ui->tblFatura->rowCount()-1,ftrSutunMatrah,itm3);
        ui->tblFatura->setItem(ui->tblFatura->rowCount()-1,ftrSutunKdvOrani,itm4);
        ui->tblFatura->setItem(ui->tblFatura->rowCount()-1,ftrSutunKdvTutar,itm5);
        ui->tblFatura->setItem(ui->tblFatura->rowCount()-1,ftrSutunTutar,itm6);
        ui->tblFatura->setItem(ui->tblFatura->rowCount()-1,ftrSutunAciklama,itm7);
        ui->tblFatura->setItem(ui->tblFatura->rowCount()-1,ftrSutunTur,itm8);
        ui->tblFatura->setItem(ui->tblFatura->rowCount()-1,ftrSutunHesap,itm12);
        ui->tblFatura->setItem(ui->tblFatura->rowCount()-1,ftrSutunKayit,itm9);
        ui->tblFatura->setItem(ui->tblFatura->rowCount()-1,ftrSutunDegisim,itm10);
        ui->tblFatura->setItem(ui->tblFatura->rowCount()-1,ftrSutunKilit,itm11);

        itm1->setFlags(Qt::ItemIsEnabled);//salt okunur hücreler
        itm2->setFlags(Qt::ItemIsEnabled);
        itm3->setFlags(Qt::ItemIsEnabled);
        itm4->setFlags(Qt::ItemIsEnabled);
        itm5->setFlags(Qt::ItemIsEnabled);
        itm6->setFlags(Qt::ItemIsEnabled);
        itm7->setFlags(Qt::ItemIsEnabled);
        itm8->setFlags(Qt::ItemIsEnabled);
        itm9->setFlags(Qt::ItemIsEnabled);
        itm10->setFlags(Qt::ItemIsEnabled);
        itm11->setFlags(Qt::ItemIsEnabled);
        itm12->setFlags(Qt::ItemIsEnabled);

        //fatura eklendikçe hesap tan tutarı düşüyor veya ekliyor
        for(int i=0;i<ui->tblHesap->rowCount();i++)
        {
            if(ui->tblHesap->item(i,hspSutunIsim)->text()==itm12->text())
            {
                double hesapMeblag=0;
                if(itm8->text()=="Gelen")
                {
                    hesapMeblag=ui->tblHesap->item(i,hspSutunGuncelMeblag)->text().toDouble()-itm6->text().toDouble();
                }
                else if(itm8->text()=="Giden")
                {
                    hesapMeblag=ui->tblHesap->item(i,hspSutunGuncelMeblag)->text().toDouble()+itm6->text().toDouble();
                }
                ui->tblHesap->item(i,hspSutunGuncelMeblag)->setText(QString::number(hesapMeblag));
                ui->tblHesap->item(i,hspSutunDegisim)->setText("1");
                break;
            }
        }
        ////////////////////////////
    }
    //toplam tutar ve kayıt sayısı yazdırılıyor
    ToplamTutarFatura=ToplamTutarFatura+form_faturaEkle.getToplamTutar();
    ui->lblFatura->setText("Kayıt: "+QString::number(ui->tblFatura->rowCount())+" Tutar: "+QString::number(ToplamTutarFatura));
    ///////////////////////////////////////////
    degisiklikIzle=true;

    ui->tblFatura->sortByColumn(ftrSutunTarih);//tblfaturayı tarih sutununa göre sıralıyor
}

//FATURA DEĞİŞTİRMEK İÇİN ANA EKRANDAKİ GİRİŞLERİ DEĞİŞTİRİLEBİLİR YAPIYOR
void muhasib::faturaDegistir()
{
    QObject* obj = sender();
    //hesap isimlerini fonksiyona vermek icin
    QStringList listeHsp;
    for(int i=0;i<ui->tblHesap->rowCount();i++)
    {
        listeHsp.append(ui->tblHesap->item(i,hspSutunIsim)->text());
    }
    /////////////////////////////////////////7
    sftr.faturaDegistir2(degisiklikIzle, kaydetVar, ui->tblFatura, ui->tblHesap, listeHsp,obj);
}

//VAROLAN GİRİŞİ SİLİYOR
void muhasib::faturaSil()
{
    QObject* obj = sender();
    sftr.faturaSil2(ToplamTutarFatura, listSilinenFatura, kaydetVar, ui->lblFatura, ui->tblFatura,obj);
}

//ÖNTANIMLI AYARLAR(FATURA)
void muhasib::ilkYuklemeFatura()
{
    ftrSutunSil=0;
    ftrSutunDegistir=1;
    ftrSutunTarih=2;
    ftrSutunIsim=3;
    ftrSutunMatrah=4;
    ftrSutunKdvOrani=5;
    ftrSutunKdvTutar=6;
    ftrSutunTutar=7;
    ftrSutunAciklama=8;
    ftrSutunTur=9;
    ftrSutunHesap=10;
    ftrSutunKayit=11;
    ftrSutunDegisim=12;
    ftrSutunKilit=13;

    sftr.ilkYukleme2(ToplamTutarFatura, ui->tblFatura,ui->tblGelenFaturalar, ui->tblGidenFaturalar, ui->tabFatura, ui->tabFaturaOzeti, tbFatura, tbFaturaOzeti, ui->tabWidget);
}

////ÖNTANIMLI AYARLAR(ÇEK)
void muhasib::ilkYuklemeCek()
{
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

    sck.ilkYukleme2(ToplamTutarCek, ui->tblCek, ui->tblAlinanCek, ui->tblVerilenCek, ui->tabCek, ui->tabCekOzeti, tbCek, tbCekOzeti, ui->tabWidget);
}

void muhasib::ilkYuklemeMaas()
{
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

    sms.ilkYukleme2(ToplamTutarMaas, ui->tblMaas, ui->tabMaas, tbMaas, ui->tabWidget);
}

void muhasib::ilkYuklemeCalisan()
{
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

    sclsn.ilkYukleme2(ToplamTutarCalisan, ui->tblCalisan, ui->tabCalisan, tbCalisan, ui->tabWidget);
}

void muhasib::ilkYuklemeGelirler()
{
    glrSutunTarih=0;
    glrSutunTur=1;
    glrSutunGelir=2;
    glrSutunTutar=3;

    ui->tblGelirler->setRowCount(0);
    ui->tblGelirler->setColumnCount(4);
    QStringList baslik=(QStringList()<<"Tarih"<<"Tür"<<"Gelir"<<"Tutar");
    ui->tblGelirler->setHorizontalHeaderLabels(baslik);
    ui->tblGelirler->horizontalHeader()->setResizeMode(QHeaderView::Stretch);
    ui->tblGelirler->setEditTriggers(QAbstractItemView::NoEditTriggers);

    tbGelirler=qobject_cast<QWidget *>(ui->tabGelirler);//tabGelirler qwidget'a dönüştürülüyor
    ui->tabWidget->removeTab(ui->tabWidget->indexOf(tbGelirler));//tabGelirler kapatılıyor
}

void muhasib::ilkYuklemeGiderler()
{
    gdrSutunTarih=0;
    gdrSutunTur=1;
    gdrSutunGider=2;
    gdrSutunTutar=3;

    ui->tblGiderler->setRowCount(0);
    ui->tblGiderler->setColumnCount(4);
    QStringList baslik=(QStringList()<<"Tarih"<<"Tür"<<"Gider"<<"Tutar");
    ui->tblGiderler->setHorizontalHeaderLabels(baslik);
    ui->tblGiderler->horizontalHeader()->setResizeMode(QHeaderView::Stretch);
    ui->tblGiderler->setEditTriggers(QAbstractItemView::NoEditTriggers);

    tbGiderler=qobject_cast<QWidget *>(ui->tabGiderler);//tabGiderler qwidget'a dönüştürülüyor
    ui->tabWidget->removeTab(ui->tabWidget->indexOf(tbGiderler));//tabGiderler kapatılıyor
}

void muhasib::ilkYuklemeGgd()
{
    //QString style="QTableWidget {background-color: transparent;border: 0px;gridline-color: transparent;} QHeaderView::section {background-color: transparent;}";
    //ui->tblGgd->setStyleSheet(style);

    ggdSutunTur=0;
    ggdSutunGelir=1;
    ggdSutunGider=2;
    ggdSutunFark=3;

    ui->tblGgd->setRowCount(0);
    ui->tblGgd->setColumnCount(4);
    QStringList baslik=(QStringList()<<"Tür"<<"Gelir"<<"Gider"<<"Fark");
    ui->tblGgd->setHorizontalHeaderLabels(baslik);
    ui->tblGgd->horizontalHeader()->setResizeMode(QHeaderView::Stretch);
    ui->tblGgd->setEditTriggers(QAbstractItemView::NoEditTriggers);
    ui->tblGgd->verticalHeader()->hide();//soldaki satır numrasını gösteren header'ı saklıyorum

    tbGgd=qobject_cast<QWidget *>(ui->tabGgd);//tabGiderler qwidget'a dönüştürülüyor
    ui->tabWidget->removeTab(ui->tabWidget->indexOf(tbGgd));//tabGiderler kapatılıyor
}

void muhasib::ilkYuklemeHesaplar()
{
    hspSutunSil=0;
    hspSutunDegistir=1;
    hspSutunIsim=2;
    hspSutunBaslangicMeblagi=3;
    hspSutunGuncelMeblag=4;
    hspSutunTur=5;
    hspSutunKayit=6;
    hspSutunDegisim=7;
    hspSutunKilit=8;

    shsp.ilkYukleme2(ui->tblHesap, ui->tabHesap, tbHesap, ui->tabWidget);
}

void muhasib::ilkYuklemeBaslangic()
{
    ui->cbFatura->addItem("Fatura");
    ui->cbFatura->addItem("Fatura Ekle");
    ui->cbFatura->addItem("Fatura Listele");
    ui->cbFatura->addItem("Fatura Karşılaştır");

    ui->cbCek->addItem("Çek");
    ui->cbCek->addItem("Çek Ekle");
    ui->cbCek->addItem("Çekleri Listele");
    ui->cbCek->addItem("Çekleri Karşılaştır");

    ui->cbMaas_2->addItem("Maaş");
    ui->cbMaas_2->addItem("Maaş Ekle");
    ui->cbMaas_2->addItem("Maaşları Listele");

    ui->cbCalisan->addItem("Çalışan");
    ui->cbCalisan->addItem("Çalışan Ekle");
    ui->cbCalisan->addItem("Çalışanları Listele");

    ui->cbRapor->addItem("Rapor");
    ui->cbRapor->addItem("Gelirleri Göster");
    ui->cbRapor->addItem("Giderleri Göster");
    ui->cbRapor->addItem("Gelir/Gider");

    ui->cbHesap->addItem("Hesap");
    ui->cbHesap->addItem("Hesap Ekle");
    ui->cbHesap->addItem("Hesapları Listele");
}

//ÖNTANIMLI AYARLAR
void muhasib::ilkYukleme()
{
    ilkYuklemeFatura();
    ilkYuklemeCek();
    ilkYuklemeCalisan();
    ilkYuklemeMaas();
    ilkYuklemeGelirler();
    ilkYuklemeGiderler();
    ilkYuklemeGgd();
    ilkYuklemeBaslangic();
    ilkYuklemeHesaplar();
    kaydetVar=false;
    degisiklikIzle=false;
    veritabanindanYukle();

    //pencere boyutu veritabanından alınıp uygulanıyor
    QSqlQuery query;
    query.exec("select b_x,b_y,b_w,b_h,b_tamekran from boyut");
    query.next();
    if(query.value(4).toString()=="1")
    {
        showMaximized();
    }
    else
    {
        this->setGeometry(query.value(0).toInt(),query.value(1).toInt(),query.value(2).toInt(),query.value(3).toInt());
    }
    ///////////////////////////////
}

muhasib::~muhasib()
{
    delete ui;
}
