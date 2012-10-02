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
    connect(ui->tblCek,SIGNAL(cellChanged(int,int)),this,SLOT(cekToplamiHesapla(int,int)));
    connect(ui->btnCekKarsilastirBaslangicTarihi,SIGNAL(clicked()),this,SLOT(cekOzetiTakvimAc()));
    connect(ui->btnCekKarsilastirBitisTarihi,SIGNAL(clicked()),this,SLOT(cekOzetiTakvimAc()));
    connect(ui->btnRaporlaCekKarsilastir,SIGNAL(clicked()),this,SLOT(cekOzetiRaporla()));
    connect(ui->btnCekOzetiCek,SIGNAL(clicked()),this,SLOT(sekmeCekOzetiAc()));
    connect(ui->actionCekListele,SIGNAL(triggered()),this,SLOT(sekmeCekAc()));
    connect(ui->actionCekEkle,SIGNAL(triggered()),this,SLOT(yeniCekEkle()));
    connect(ui->actionCekKarsilastir,SIGNAL(triggered()),this,SLOT(sekmeCekOzetiAc()));
    connect(ui->btnKistasCek,SIGNAL(clicked()),this,SLOT(kistasCekAc()));
    ///////////////////
    ///maaş bağlantıları
    connect(ui->btnMaasEkleMaas,SIGNAL(clicked()),this,SLOT(yeniMaasEkle()));
    connect(ui->actionMaasEkle,SIGNAL(triggered()),this,SLOT(yeniMaasEkle()));
    connect(ui->actionMaasListele,SIGNAL(triggered()),this,SLOT(sekmeMaasAc()));
    connect(ui->btnKistasMaas,SIGNAL(clicked()),this,SLOT(kistasMaasAc()));
    //////////////////////
    //calisan bağlantıları
    connect(ui->btnCalisanEkleCalisan,SIGNAL(clicked()),this,SLOT(yeniCalisanEkle()));
    connect(ui->actionCalisanEkle,SIGNAL(triggered()),this,SLOT(yeniCalisanEkle()));
    connect(ui->actionCalisanListele,SIGNAL(triggered()),this,SLOT(sekmeCalisanAc()));
    connect(ui->btnKistasCalisan,SIGNAL(clicked()),this,SLOT(kistasCalisanAc()));
    /////////////////////////
    //hesap bağlantıları
    connect(ui->btnHesapEkleHesap,SIGNAL(clicked()),this,SLOT(yeniHesapEkle()));
    connect(ui->actionHesapEkle,SIGNAL(triggered()),this,SLOT(yeniHesapEkle()));
    connect(ui->actionHesapListele,SIGNAL(triggered()),this,SLOT(sekmeHesapAc()));
    /////////////////////////
    //rapor bağlantıları
    connect(ui->actionGelirler,SIGNAL(triggered()),this,SLOT(sekmeGelirlerAc()));
    connect(ui->actionGiderler,SIGNAL(triggered()),this,SLOT(sekmeGiderlerAc()));
    connect(ui->actionGgd,SIGNAL(triggered()),this,SLOT(sekmeGgdAc()));
    connect(ui->actionHesapOzeti,SIGNAL(triggered()),this,SLOT(sekmeHesapOzetiAc()));
    connect(ui->cbHesapOzeti,SIGNAL(currentIndexChanged(int)),this,SLOT(hesapOzetiRaporla(int)));
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

//HESAP ISIMLERİNİ DÖNDURUYOR
QStringList muhasib::getListeHesap()
{
    QStringList listeHsp;
    for(int i=0;i<ui->tblHesap->rowCount();i++)
    {
        listeHsp.append(ui->tblHesap->item(i,dgs.hspSutunIsim)->text());
    }
    return listeHsp;
}

QStringList muhasib::getListeCalisan()
{
    QStringList listeClsn;
    for(int i=0;i<ui->tblCalisan->rowCount();i++)
    {
        listeClsn.append(ui->tblCalisan->item(i,dgs.clsSutunIsim)->text());
    }
    return listeClsn;
}

//pencerenin boyutu veritabanına kaydediliyor
void muhasib::pencereBoyutuKaydet()
{
    QSqlQuery query;
    if(isMaximized())//eğer pencere tam ekran ise tam ekran açılması için
    {
        query.exec(QString("update boyut set b_tamekran='%1' where b_id='%2'").arg("1").arg("1"));
    }
    else
    {
        query.exec(QString("update boyut set b_x='%1', b_y='%2',b_w='%3',b_h='%4', b_tamekran='%5' where b_id='%6'").arg(geometry().x()).arg(geometry().y()).arg(geometry().width()).arg(geometry().height()).arg("0").arg("1"));
    }
}

void muhasib::closeEvent(QCloseEvent *event)
{
    if(kaydetVar==true)
    {
        QMessageBox *msgBox=new QMessageBox(this);
        msgBox->setText("Kapatmadan önce yaptığınız değişiklikleri kaydetmek ister misiniz?");
        QAbstractButton* dugmeEvet=msgBox->addButton("Kaydet", QMessageBox::YesRole);
        QAbstractButton* dugmeIptal=msgBox->addButton("İptal", QMessageBox::NoRole);
        QAbstractButton* dugmeHayir=msgBox->addButton("Kaydetmeden Kapat", QMessageBox::NoRole);
        msgBox->exec();
        if(msgBox->clickedButton() == dugmeEvet)
        {
            if(kilidiAcikSatirSayisi>0)
            {
                QMessageBox::warning(this,"","Önce değişiklikleri tamamlayın ("+QString::number(kilidiAcikSatirSayisi)+" kayıt)","Tamam");
                event->ignore();
            }
            else
            {
                pencereBoyutuKaydet();
                kaydet();
                event->accept();
            }
        }
        else if(msgBox->clickedButton() == dugmeHayir)
        {
            event->accept();
        }
        else if(msgBox->clickedButton() == dugmeIptal)
        {
            pencereBoyutuKaydet();
            event->ignore();
        }
    }
    else if(kaydetVar==false)
    {
        pencereBoyutuKaydet();
    }
}

void muhasib::kistasCalisanAc()
{

    this->setEnabled(false);
    form_kistasCalisan.ontanimliAyarlar();
    form_kistasCalisan.exec();
    if(form_kistasCalisan.getSecim())
    {
        QStringList listeTarih;
        QStringList listeKonum;
        QStringList listeMaas;

        for(int i=0; i<ui->tblCalisan->rowCount();i++)
        {
            ui->tblCalisan->hideRow(i);
        }
        if(form_kistasCalisan.getTarihEtkinMi())//tarih kıstası etkin
        {
            for(int i=0; i<ui->tblCalisan->rowCount();i++)
            {
                QDate dt=QDate::fromString(ui->tblCalisan->item(i,dgs.clsSutunIseGiris)->text(),"yyyy-MM-dd");
                if(dt>=form_kistasCalisan.getBaslangicTarih() && dt<=form_kistasCalisan.getBitisTarih())
                {
                    listeTarih.append(QString::number(i));
                }
            }
        }
        else
        {
            for(int i=0; i<ui->tblCalisan->rowCount();i++)
            {
                listeTarih.append(QString::number(i));
            }
        }

        if(form_kistasCalisan.getKonumEtkinMi())//tür kıstası etkin
        {
            QStringList listeSeciliKonum=form_kistasCalisan.getKonumSecim();
            for(int i=0; i<ui->tblCalisan->rowCount();i++)
            {
                if(listeSeciliKonum.contains(ui->tblCalisan->item(i,dgs.clsSutunKonum)->text()))
                {
                    listeKonum.append(QString::number(i));
                }
            }
        }
        else
        {
            for(int i=0; i<ui->tblCalisan->rowCount();i++)
            {
                listeKonum.append(QString::number(i));
            }
        }

        if(form_kistasCalisan.getMaasEtkinMi())//tarih kıstası etkin
        {
            for(int i=0; i<ui->tblCalisan->rowCount();i++)
            {
                int maas=ui->tblCalisan->item(i,dgs.clsSutunMaas)->text().toInt();
                if(maas>=form_kistasCalisan.getBaslangicMaas() && maas<=form_kistasCalisan.getBitisMaas())
                {
                    listeMaas.append(QString::number(i));
                }
            }
        }
        else
        {
            for(int i=0; i<ui->tblCalisan->rowCount();i++)
            {
                listeMaas.append(QString::number(i));
            }
        }

        qDebug()<<"listeKonum"<<listeKonum;
        qDebug()<<"listeTarih"<<listeTarih;
        qDebug()<<"listeMaas"<<listeMaas;

        QStringList topluListe=listeKonum+listeTarih+listeMaas;
        while(!topluListe.isEmpty())
        {
            if(topluListe.count(topluListe.at(0))==3)//3 tane kıstas olduğu için
            {
                ui->tblCalisan->showRow(topluListe.at(0).toInt());
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

void muhasib::kistasCekAc()
{
    this->setEnabled(false);
    form_kistasCek.ontanimliAyarlar();
    form_kistasCek.exec();
    if(form_kistasCek.getSecim())
    {
        QStringList listeTarih;
        QStringList listeTur;

        for(int i=0; i<ui->tblCek->rowCount();i++)
        {
            ui->tblCek->hideRow(i);
        }
        if(form_kistasCek.getTarihEtkinMi())//tarih kıstası etkin
        {
            for(int i=0; i<ui->tblCek->rowCount();i++)
            {
                QDate dt=QDate::fromString(ui->tblCek->item(i,dgs.ckSutunTarih)->text(),"yyyy-MM-dd");
                if(dt>=form_kistasCek.getBaslangicTarih() && dt<=form_kistasCek.getBitisTarih())
                {
                    listeTarih.append(QString::number(i));
                }
            }
        }
        else
        {
            for(int i=0; i<ui->tblCek->rowCount();i++)
            {
                listeTarih.append(QString::number(i));
            }
        }

        if(form_kistasCek.getTurEtkinMi())//tür kıstası etkin
        {
            QStringList listeSeciliTur=form_kistasCek.getTurSecim();
            for(int i=0; i<ui->tblCek->rowCount();i++)
            {
                if(listeSeciliTur.contains(ui->tblCek->item(i,dgs.ckSutunTur)->text()))
                {
                    listeTur.append(QString::number(i));
                }
            }
        }
        else
        {
            for(int i=0; i<ui->tblCek->rowCount();i++)
            {
                listeTur.append(QString::number(i));
            }
        }

        QStringList topluListe=listeTur+listeTarih;
        while(!topluListe.isEmpty())
        {
            if(topluListe.count(topluListe.at(0))==2)//2 tane kıstas olduğu için
            {
                ui->tblCek->showRow(topluListe.at(0).toInt());
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

void muhasib::kistasMaasAc()
{
    this->setEnabled(false);
    form_kistasMaas.ontanimliAyarlar();
    form_kistasMaas.exec();

    if(form_kistasMaas.getSecim())
    {
        QStringList listeTarih;
        QStringList listeTur;

        for(int i=0; i<ui->tblMaas->rowCount();i++)
        {
            ui->tblMaas->hideRow(i);
        }
        if(form_kistasMaas.getTarihEtkinMi())//tarih kıstası etkin
        {
            for(int i=0; i<ui->tblMaas->rowCount();i++)
            {
                QDate dt=QDate::fromString(ui->tblMaas->item(i,dgs.msSutunTarih)->text(),"yyyy-MM-dd");
                if(dt>=form_kistasMaas.getBaslangicTarih() && dt<=form_kistasMaas.getBitisTarih())
                {
                    listeTarih.append(QString::number(i));
                }
            }
        }
        else
        {
            for(int i=0; i<ui->tblMaas->rowCount();i++)
            {
                listeTarih.append(QString::number(i));
            }
        }

        if(form_kistasMaas.getTurEtkinMi())//tür kıstası etkin
        {
            QStringList listeSeciliTur=form_kistasMaas.getTurSecim();
            for(int i=0; i<ui->tblMaas->rowCount();i++)
            {
                if(listeSeciliTur.contains(ui->tblMaas->item(i,dgs.msSutunTur)->text()))
                {
                    listeTur.append(QString::number(i));
                }
            }
        }
        else
        {
            for(int i=0; i<ui->tblMaas->rowCount();i++)
            {
                listeTur.append(QString::number(i));
            }
        }
        qDebug()<<"listeTur"<<listeTur;
        QStringList topluListe=listeTur+listeTarih;
        while(!topluListe.isEmpty())
        {
            if(topluListe.count(topluListe.at(0))==2)//2 tane kıstas olduğu için
            {
                ui->tblMaas->showRow(topluListe.at(0).toInt());
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

void muhasib::kistasFaturaAc()
{
    this->setEnabled(false);
    form_kistasFatura.ontanimliAyarlar();
    form_kistasFatura.exec();

    if(form_kistasFatura.getSecim())//iptale tıklanırsa hiç girmesin
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
                QDate dt=QDate::fromString(ui->tblFatura->item(i,dgs.ftrSutunTarih)->text(),"yyyy-MM-dd");

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

        if(form_kistasFatura.getTurEtkinMi())//tür kıstası etkin
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
                    if(ui->tblFatura->item(i,dgs.ftrSutunTur)->text()=="Gelen")
                    {
                        listeTur.append(QString::number(i));
                    }
                }
            }
            else if(form_kistasFatura.getTurSecim()==2)//sadece giden etkin
            {
                for(int i=0; i<ui->tblFatura->rowCount();i++)
                {
                    if(ui->tblFatura->item(i,dgs.ftrSutunTur)->text()=="Giden")
                    {
                        listeTur.append(QString::number(i));
                    }
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
    if(kaydetVar==true)
    {
        QMessageBox *msgBox=new QMessageBox(this);
        msgBox->setText("Kapatmadan önce yaptığınız değişiklikleri kaydetmek ister misiniz?");
        QAbstractButton* dugmeEvet=msgBox->addButton("Kaydet", QMessageBox::YesRole);
        QAbstractButton* dugmeIptal=msgBox->addButton("İptal", QMessageBox::NoRole);
        QAbstractButton* dugmeHayir=msgBox->addButton("Kaydetmeden Kapat", QMessageBox::NoRole);
        msgBox->exec();
        if(msgBox->clickedButton() == dugmeEvet)
        {
            if(kilidiAcikSatirSayisi>0)
            {
                QMessageBox::warning(this,"","Önce değişiklikleri tamamlayın ("+QString::number(kilidiAcikSatirSayisi)+" kayıt)","Tamam");
            }
            else
            {
                pencereBoyutuKaydet();
                kaydet();
                close();
            }
        }
        else if(msgBox->clickedButton() == dugmeHayir)
        {
            close();
        }
        else if(msgBox->clickedButton() == dugmeIptal)
        {
            pencereBoyutuKaydet();
        }
    }
    else if(kaydetVar==false)
    {
        pencereBoyutuKaydet();
    }

    //close();
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
    else if(a==4)
    {
        sekmeHesapOzetiAc();
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
        if(kilidiAcikSatirSayisi>0)
        {
            QMessageBox::warning(this,"","Önce değişiklikleri tamamlayın ("+QString::number(kilidiAcikSatirSayisi)+" kayıt)","Tamam");
        }
        else
        {
            faturaKaydet();
            cekKaydet();
            maasKaydet();
            calisanKaydet();
            hesapKaydet();
            kaydetVar=false;
        }
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
        ui->tblHesap->setCellWidget(ui->tblHesap->rowCount()-1,dgs.hspSutunSil,btnSil);

        QPushButton *btnDegistir=new QPushButton();
        btnDegistir->setIcon(QIcon(QDir::currentPath()+"/icons/kilitkapali.png"));
        btnDegistir->setToolTip("Degiştir");
        connect(btnDegistir,SIGNAL(clicked()),this,SLOT(hesapDegistir()));
        ui->tblHesap->setCellWidget(ui->tblHesap->rowCount()-1,dgs.hspSutunDegistir,btnDegistir);

        QTableWidgetItem *itm1=new QTableWidgetItem(query.value(0).toString());
        QTableWidgetItem *itm2=new QTableWidgetItem(query.value(1).toString());
        QTableWidgetItem *itm3=new QTableWidgetItem(query.value(2).toString());
        QTableWidgetItem *itm4=new QTableWidgetItem(query.value(3).toString());
        QTableWidgetItem *itm7=new QTableWidgetItem(query.value(4).toString());
        QTableWidgetItem *itm5=new QTableWidgetItem("0");
        QTableWidgetItem *itm6=new QTableWidgetItem("0");

        ui->tblHesap->setItem(ui->tblHesap->rowCount()-1,dgs.hspSutunIsim,itm1);
        ui->tblHesap->setItem(ui->tblHesap->rowCount()-1,dgs.hspSutunBaslangicMeblagi,itm2);
        ui->tblHesap->setItem(ui->tblHesap->rowCount()-1,dgs.hspSutunGuncelMeblag,itm7);
        ui->tblHesap->setItem(ui->tblHesap->rowCount()-1,dgs.hspSutunTur,itm3);
        ui->tblHesap->setItem(ui->tblHesap->rowCount()-1,dgs.hspSutunKayit,itm4);
        ui->tblHesap->setItem(ui->tblHesap->rowCount()-1,dgs.hspSutunDegisim,itm5);
        ui->tblHesap->setItem(ui->tblHesap->rowCount()-1,dgs.hspSutunKilit,itm6);

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
    //ui->tblHesap->sortByColumn(dgs.hspSutunTarih);//tblHesapyı tarih sutunua göre sıralıyor
}

void muhasib::hesapOzetiRaporla(int a)
{
    ui->tblHesapOzeti->setRowCount(0);
    if(a!=0)
    {
        srpr.hesapOzetiRaporlaFatura(ui->tblFatura, ui->tblHesapOzeti, ui->cbHesapOzeti);
        srpr.hesapOzetiRaporlaMaas(ui->tblMaas, ui->tblHesapOzeti, ui->cbHesapOzeti);
    }
}

void muhasib::hesapKaydet()
{
    shsp.hesapKaydet2(listSilinenHesap,ui->tblHesap);
}

void muhasib::sekmeHesapAc()
{
    //ui->tabWidget->addTab(tbHesap,"Hesaplar");
    ui->tabWidget->addTab(tbHesap,dgs.sekmeHesapListele);
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
        ui->tblHesap->setCellWidget(ui->tblHesap->rowCount()-1,dgs.hspSutunSil,btnSil);

        QPushButton *btnDegistir=new QPushButton();
        btnDegistir->setIcon(QIcon(QDir::currentPath()+"/icons/kilitkapali.png"));
        btnDegistir->setToolTip("Degiştir");
        connect(btnDegistir,SIGNAL(clicked()),this,SLOT(hesapDegistir()));
        ui->tblHesap->setCellWidget(ui->tblHesap->rowCount()-1,dgs.hspSutunDegistir,btnDegistir);

        QTableWidgetItem *itm1=new QTableWidgetItem(listeHesaplar.at(i));
        QTableWidgetItem *itm2=new QTableWidgetItem(listeHesaplar.at(i+1));
        QTableWidgetItem *itm3=new QTableWidgetItem(listeHesaplar.at(i+2));
        QTableWidgetItem *itm4=new QTableWidgetItem("0");
        QTableWidgetItem *itm5=new QTableWidgetItem("0");
        QTableWidgetItem *itm6=new QTableWidgetItem("0");
        QTableWidgetItem *itm7=new QTableWidgetItem(listeHesaplar.at(i+1));

        ui->tblHesap->setItem(ui->tblHesap->rowCount()-1,dgs.hspSutunIsim,itm1);
        ui->tblHesap->setItem(ui->tblHesap->rowCount()-1,dgs.hspSutunBaslangicMeblagi,itm2);
        ui->tblHesap->setItem(ui->tblHesap->rowCount()-1,dgs.hspSutunGuncelMeblag,itm7);
        ui->tblHesap->setItem(ui->tblHesap->rowCount()-1,dgs.hspSutunTur,itm3);
        ui->tblHesap->setItem(ui->tblHesap->rowCount()-1,dgs.hspSutunKayit,itm4);
        ui->tblHesap->setItem(ui->tblHesap->rowCount()-1,dgs.hspSutunDegisim,itm5);
        ui->tblHesap->setItem(ui->tblHesap->rowCount()-1,dgs.hspSutunKilit,itm6);

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
    shsp.hesapSil2(listSilinenHesap, kaydetVar, ui->tblHesap, sender());
}

void muhasib::hesapDegistir()
{
    shsp.hesapDegistir2(degisiklikIzle, kaydetVar, ui->tblHesap, ui->tabWidget, kilidiAcikSatirSayisi, sender());
}

void muhasib::sekmeGgdAc()
{
    ggdYukle();
    //ui->tabWidget->addTab(tbGgd,"Gelir/Gider");
    ui->tabWidget->addTab(tbGgd,dgs.sekmeGgd);
    ui->tabWidget->setCurrentWidget(tbGgd);
}

//GELİR GİDER EKRANINA CEK BİLGİLERİNİ YÜKLÜYOR
void muhasib::ggdCekYukle()
{
    /*
    double cekGelirTutar=0;
    double cekGiderTutar=0;
    for(int i=0;i<ui->tblCek->rowCount();i++)
    {
        if(ui->tblCek->item(i,dgs.ckSutunTur)->text()=="Alınan")
        {
            cekGelirTutar=cekGelirTutar+ui->tblCek->item(i,dgs.ckSutunTutar)->text().toDouble();
        }
        else if(ui->tblCek->item(i,dgs.ckSutunTur)->text()=="Verilen")
        {
            cekGiderTutar=cekGiderTutar+ui->tblCek->item(i,dgs.ckSutunTutar)->text().toDouble();
        }
    }
    ui->tblGgd->insertRow(ui->tblGgd->rowCount());
    ui->tblGgd->setRowHeight(ui->tblGgd->rowCount()-1,40);
    QTableWidgetItem *itm0=new QTableWidgetItem("Çek");
    ggdItem(itm0);
    ui->tblGgd->setItem(ui->tblGgd->rowCount()-1,dgs.ggdSutunTur,itm0);
    QTableWidgetItem *itm1=new QTableWidgetItem(QString::number(cekGelirTutar));
    ggdItem(itm1);
    ui->tblGgd->setItem(ui->tblGgd->rowCount()-1,dgs.ggdSutunGelir,itm1);
    QTableWidgetItem *itm2=new QTableWidgetItem(QString::number(cekGiderTutar));
    ggdItem(itm2);
    ui->tblGgd->setItem(ui->tblGgd->rowCount()-1,dgs.ggdSutunGider,itm2);
    QTableWidgetItem *itm3=new QTableWidgetItem(QString::number(cekGelirTutar-cekGiderTutar));
    ggdItem(itm3);
    ui->tblGgd->setItem(ui->tblGgd->rowCount()-1,dgs.ggdSutunFark,itm3);
    */
}

//GELİR GİDER EKRANINı dolduruyoe
void muhasib::ggdYukle()
{
    ui->tblGgd->setRowCount(0);
    //ggdCekYukle();

    srpr.ggdMaasYukle(ui->tblGgd,ui->tblMaas);//GELİR GİDER EKRANINA MAAS BİLGİLERİNİ YÜKLÜYOR
    srpr.ggdFaturaYukle(ui->tblGgd, ui->tblFatura);//GELİR GİDER EKRANINA FATURA BİLGİLERİNİ YÜKLÜYOR
    srpr.ggdToplamiYukle(ui->tblGgd);//GELİR GİDER EKRANINA TOPLAM BİLGİLERİNİ YÜKLÜYOR
}

void muhasib::sekmeGelirlerAc()
{
    gelirleriYukle();
    //ui->tabWidget->addTab(tbGelirler,"Gelirler");
    ui->tabWidget->addTab(tbGelirler,dgs.sekmeGelirListele);
    ui->tabWidget->setCurrentWidget(tbGelirler);
}

void muhasib::gelirleriYukle()
{
    srpr.gelirleriYukle(ui->tblGelirler,ui->tblFatura,ui->tblCek);
}

void muhasib::sekmeGiderlerAc()
{
    giderleriYukle();
    //ui->tabWidget->addTab(tbGiderler,"Giderler");
    ui->tabWidget->addTab(tbGiderler,dgs.sekmeGiderListele);
    ui->tabWidget->setCurrentWidget(tbGiderler);
}

void muhasib::giderleriYukle()
{
    srpr.giderleriYukle(ui->tblGiderler, ui->tblFatura, ui->tblCek, ui->tblMaas);
}

void muhasib::sekmeHesapOzetiAc()
{
    //ui->tabWidget->addTab(tbHesapOzeti,"Hesap Özeti");
    ui->tabWidget->addTab(tbHesapOzeti,dgs.sekmeHesapOzetiListele);
    ui->tabWidget->setCurrentWidget(tbHesapOzeti);
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
        ui->tblCalisan->setCellWidget(ui->tblCalisan->rowCount()-1,dgs.clsSutunSil,btnSil);

        QPushButton *btnDegistir=new QPushButton();
        btnDegistir->setIcon(QIcon(QDir::currentPath()+"/icons/kilitkapali.png"));
        btnDegistir->setToolTip("Degiştir");
        connect(btnDegistir,SIGNAL(clicked()),this,SLOT(calisanDegistir()));
        ui->tblCalisan->setCellWidget(ui->tblCalisan->rowCount()-1,dgs.clsSutunDegistir,btnDegistir);

        QTableWidgetItem *itm1=new QTableWidgetItem(query.value(0).toString());
        QTableWidgetItem *itm2=new QTableWidgetItem(query.value(1).toString());
        QTableWidgetItem *itm3=new QTableWidgetItem(query.value(2).toString());
        QTableWidgetItem *itm4=new QTableWidgetItem(query.value(3).toString());
        QTableWidgetItem *itm5=new QTableWidgetItem(query.value(4).toString());
        QTableWidgetItem *itm6=new QTableWidgetItem(query.value(5).toString());
        QTableWidgetItem *itm7=new QTableWidgetItem("0");
        QTableWidgetItem *itm8=new QTableWidgetItem("0");

        ui->tblCalisan->setItem(ui->tblCalisan->rowCount()-1,dgs.clsSutunIsim,itm1);
        ui->tblCalisan->setItem(ui->tblCalisan->rowCount()-1,dgs.clsSutunKonum,itm2);
        ui->tblCalisan->setItem(ui->tblCalisan->rowCount()-1,dgs.clsSutunIseGiris,itm3);
        ui->tblCalisan->setItem(ui->tblCalisan->rowCount()-1,dgs.clsSutunMaas,itm4);
        ui->tblCalisan->setItem(ui->tblCalisan->rowCount()-1,dgs.clsSutunAciklama,itm5);
        ui->tblCalisan->setItem(ui->tblCalisan->rowCount()-1,dgs.clsSutunKayit,itm6);
        ui->tblCalisan->setItem(ui->tblCalisan->rowCount()-1,dgs.clsSutunDegisim,itm7);
        ui->tblCalisan->setItem(ui->tblCalisan->rowCount()-1,dgs.clsSutunKilit,itm8);

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
    //ui->tabWidget->addTab(tbCalisan,"Çalışanlar");
    ui->tabWidget->addTab(tbCalisan,dgs.sekmeCalisanListele);
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
        ui->tblCalisan->setCellWidget(ui->tblCalisan->rowCount()-1,dgs.clsSutunSil,btnSil);

        QPushButton *btnDegistir=new QPushButton();
        btnDegistir->setIcon(QIcon(QDir::currentPath()+"/icons/kilitkapali.png"));
        btnDegistir->setToolTip("Degiştir");
        connect(btnDegistir,SIGNAL(clicked()),this,SLOT(calisanDegistir()));
        ui->tblCalisan->setCellWidget(ui->tblCalisan->rowCount()-1,dgs.clsSutunDegistir,btnDegistir);

        QTableWidgetItem *itm1=new QTableWidgetItem(listeCalisan.at(i));
        QTableWidgetItem *itm2=new QTableWidgetItem(listeCalisan.at(i+1));
        QTableWidgetItem *itm3=new QTableWidgetItem(listeCalisan.at(i+2));
        QTableWidgetItem *itm4=new QTableWidgetItem(listeCalisan.at(i+3));
        QTableWidgetItem *itm5=new QTableWidgetItem(listeCalisan.at(i+4));
        QTableWidgetItem *itm6=new QTableWidgetItem("0");
        QTableWidgetItem *itm7=new QTableWidgetItem("0");
        QTableWidgetItem *itm8=new QTableWidgetItem("0");

        ui->tblCalisan->setItem(ui->tblCalisan->rowCount()-1,dgs.clsSutunIsim,itm1);
        ui->tblCalisan->setItem(ui->tblCalisan->rowCount()-1,dgs.clsSutunKonum,itm2);
        ui->tblCalisan->setItem(ui->tblCalisan->rowCount()-1,dgs.clsSutunIseGiris,itm3);
        ui->tblCalisan->setItem(ui->tblCalisan->rowCount()-1,dgs.clsSutunMaas,itm4);
        ui->tblCalisan->setItem(ui->tblCalisan->rowCount()-1,dgs.clsSutunAciklama,itm5);
        ui->tblCalisan->setItem(ui->tblCalisan->rowCount()-1,dgs.clsSutunKayit,itm6);
        ui->tblCalisan->setItem(ui->tblCalisan->rowCount()-1,dgs.clsSutunDegisim,itm7);
        ui->tblCalisan->setItem(ui->tblCalisan->rowCount()-1,dgs.clsSutunKilit,itm8);

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
    sclsn.calisanSil2(ToplamTutarCalisan, listSilinenCalisan, kaydetVar, ui->lblCalisan, ui->tblCalisan, sender());
}

void muhasib::calisanDegistir()
{
    sclsn.calisanDegistir2(degisiklikIzle, kaydetVar, ui->tblCalisan, ui->tabWidget, kilidiAcikSatirSayisi, sender());
}

void muhasib::maasKaydet()
{
    sms.maasKaydet2(listSilinenMaas,ui->tblMaas);
}

void muhasib::sekmeMaasAc()
{
    //ui->tabWidget->addTab(tbMaas,"Maaşlar");
    ui->tabWidget->addTab(tbMaas,dgs.sekmeMaasListele);
    ui->tabWidget->setCurrentWidget(tbMaas);
}

void muhasib::yeniMaasEkle()
{
    if(ui->tblCalisan->rowCount()==0 && ui->tblHesap->rowCount()==0)
    {
        QMessageBox::warning(this,"Hata","Önce hesap ve çalışan ekleyin","Tamam");
    }
    else if(ui->tblCalisan->rowCount()==0 || ui->tblHesap->rowCount()==0)
    {
        if(ui->tblCalisan->rowCount()==0)
        {
            QMessageBox::warning(this,"Hata","Önce çalışan ekleyin","Tamam");
        }
        else if(ui->tblHesap->rowCount()==0)
        {
            QMessageBox::warning(this,"Hata","Önce hesap ekleyin","Tamam");
        }
    }
    else
    {
        degisiklikIzle=false;
        form_maasEkle.setWindowFlags(Qt::Window);//maas ekleme penceresinin köşesindeki 3 düğmenin gösterilmesi için
        this->setEnabled(false);//ana pencere etkisizleştiriliyor
        form_maasEkle.setListeCalisanlar(getListeCalisan()); //maas ekleme penceresinde çalışanların isminin çıkabilmesi için
        form_maasEkle.setListeHesap(getListeHesap());//maas ekleme penceresinde hesapların isminin çıkabilmesi için
        form_maasEkle.ontanimliAyarlar();
        form_maasEkle.exec();
        QStringList listeMaas=form_maasEkle.getListeMaas();
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
            ui->tblMaas->setCellWidget(ui->tblMaas->rowCount()-1,dgs.msSutunSil,btnSil);

            QPushButton *btnDegistir=new QPushButton();
            btnDegistir->setIcon(QIcon(QDir::currentPath()+"/icons/kilitkapali.png"));
            btnDegistir->setToolTip("Degiştir");
            connect(btnDegistir,SIGNAL(clicked()),this,SLOT(maasDegistir()));
            ui->tblMaas->setCellWidget(ui->tblMaas->rowCount()-1,dgs.msSutunDegistir,btnDegistir);

            QTableWidgetItem *itm1=new QTableWidgetItem(listeMaas.at(i));
            QTableWidgetItem *itm2=new QTableWidgetItem(listeMaas.at(i+1));
            QTableWidgetItem *itm3=new QTableWidgetItem(listeMaas.at(i+2));
            QTableWidgetItem *itm4=new QTableWidgetItem(listeMaas.at(i+3));
            QTableWidgetItem *itm5=new QTableWidgetItem(listeMaas.at(i+4));
            QTableWidgetItem *itm9=new QTableWidgetItem(listeMaas.at(i+5));
            QTableWidgetItem *itm6=new QTableWidgetItem("0");
            QTableWidgetItem *itm7=new QTableWidgetItem("0");
            QTableWidgetItem *itm8=new QTableWidgetItem("0");

            ui->tblMaas->setItem(ui->tblMaas->rowCount()-1,dgs.msSutunTarih,itm1);
            ui->tblMaas->setItem(ui->tblMaas->rowCount()-1,dgs.msSutunCalisan,itm2);
            ui->tblMaas->setItem(ui->tblMaas->rowCount()-1,dgs.msSutunMaas,itm3);
            ui->tblMaas->setItem(ui->tblMaas->rowCount()-1,dgs.msSutunAy,itm4);
            ui->tblMaas->setItem(ui->tblMaas->rowCount()-1,dgs.msSutunTur,itm5);
            ui->tblMaas->setItem(ui->tblMaas->rowCount()-1,dgs.msSutunHesap,itm9);
            ui->tblMaas->setItem(ui->tblMaas->rowCount()-1,dgs.msSutunKayit,itm6);
            ui->tblMaas->setItem(ui->tblMaas->rowCount()-1,dgs.msSutunDegisim,itm7);
            ui->tblMaas->setItem(ui->tblMaas->rowCount()-1,dgs.msSutunKilit,itm8);

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
                if(ui->tblHesap->item(i,dgs.hspSutunIsim)->text()==itm9->text())
                {
                    double hesapMeblag=ui->tblHesap->item(i,dgs.hspSutunGuncelMeblag)->text().toDouble()-itm3->text().toDouble();
                    ui->tblHesap->item(i,dgs.hspSutunGuncelMeblag)->setText(QString::number(hesapMeblag));
                    ui->tblHesap->item(i,dgs.hspSutunDegisim)->setText("1");
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
}

void muhasib::maasSil()
{
    QPushButton *btn = qobject_cast<QPushButton *>(sender());
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
    if(ui->tblMaas->item(silinecekSatir,dgs.msSutunKilit)->text()=="1")
    {
        QPushButton *btnDegistir=qobject_cast<QPushButton *>(ui->tblMaas->cellWidget(silinecekSatir,dgs.msSutunDegistir));
        btnDegistir->click();
    }

    listSilinenMaas.append(ui->tblMaas->item(silinecekSatir,dgs.msSutunKayit)->text());

    ToplamTutarMaas=ToplamTutarMaas-ui->tblMaas->item(silinecekSatir,dgs.msSutunMaas)->text().toDouble();//silinen Maas tutarını toplamtutar dan çıkarıyor
    ui->tblMaas->removeRow(silinecekSatir);
    ui->lblMaas->setText("Kayıt: "+QString::number(ui->tblMaas->rowCount())+" Tutar: "+QString::number(ToplamTutarMaas));//label i güncelliyor

    kaydetVar=true;
}

void muhasib::maasDegistir()
{
    sms.maasDegistir2(degisiklikIzle, kaydetVar, ui->tblMaas, ui->tblHesap, ui->tabWidget, getListeHesap(), getListeCalisan(), kilidiAcikSatirSayisi, sender());
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
        ui->tblMaas->setCellWidget(ui->tblMaas->rowCount()-1,dgs.msSutunSil,btnSil);

        QPushButton *btnDegistir=new QPushButton();
        btnDegistir->setIcon(QIcon(QDir::currentPath()+"/icons/kilitkapali.png"));
        btnDegistir->setToolTip("Degiştir");
        connect(btnDegistir,SIGNAL(clicked()),this,SLOT(maasDegistir()));
        ui->tblMaas->setCellWidget(ui->tblMaas->rowCount()-1,dgs.msSutunDegistir,btnDegistir);

        QTableWidgetItem *itm1=new QTableWidgetItem(query.value(0).toString());
        QTableWidgetItem *itm2=new QTableWidgetItem(query.value(1).toString());
        QTableWidgetItem *itm3=new QTableWidgetItem(query.value(2).toString());
        QTableWidgetItem *itm4=new QTableWidgetItem(query.value(3).toString());
        QTableWidgetItem *itm5=new QTableWidgetItem(query.value(4).toString());
        QTableWidgetItem *itm6=new QTableWidgetItem(query.value(5).toString());
        QTableWidgetItem *itm9=new QTableWidgetItem(query.value(6).toString());
        QTableWidgetItem *itm7=new QTableWidgetItem("0");
        QTableWidgetItem *itm8=new QTableWidgetItem("0");

        ui->tblMaas->setItem(ui->tblMaas->rowCount()-1,dgs.msSutunTarih,itm1);
        ui->tblMaas->setItem(ui->tblMaas->rowCount()-1,dgs.msSutunCalisan,itm2);
        ui->tblMaas->setItem(ui->tblMaas->rowCount()-1,dgs.msSutunMaas,itm3);
        ui->tblMaas->setItem(ui->tblMaas->rowCount()-1,dgs.msSutunAy,itm4);
        ui->tblMaas->setItem(ui->tblMaas->rowCount()-1,dgs.msSutunTur,itm5);
        ui->tblMaas->setItem(ui->tblMaas->rowCount()-1,dgs.msSutunHesap,itm9);
        ui->tblMaas->setItem(ui->tblMaas->rowCount()-1,dgs.msSutunKayit,itm6);
        ui->tblMaas->setItem(ui->tblMaas->rowCount()-1,dgs.msSutunDegisim,itm7);
        ui->tblMaas->setItem(ui->tblMaas->rowCount()-1,dgs.msSutunKilit,itm8);

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

/*
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
            if(ui->tblCek->item(i,dgs.ckSutunTur)->text()=="Alınan")
            {
                ui->tblCek->hideRow(i);
            }
            else
            {
                ui->tblCek->showRow(i);
                //toplam tutar ve kayıt sayısı hesaplanıyor
                kismiTutar=kismiTutar+ui->tblCek->item(i,dgs.ckSutunTutar)->text().toDouble();
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
            if(ui->tblCek->item(i,dgs.ckSutunTur)->text()=="Verilen")
            {
                ui->tblCek->hideRow(i);
            }
            else
            {
                ui->tblCek->showRow(i);
                //toplam tutar ve kayıt sayısı hesaplanıyor
                kismiTutar=kismiTutar+ui->tblCek->item(i,dgs.ckSutunTutar)->text().toDouble();
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
*/

void muhasib::cekToplamiHesapla(int a,int b)
{
    if(degisiklikIzle==true && b==dgs.ckSutunTutar)
    {
        ToplamTutarCek=0;
        for(int i=0;i<ui->tblCek->rowCount();i++)
        {
            ToplamTutarCek=ToplamTutarCek+ui->tblCek->item(i,dgs.ckSutunTutar)->text().toDouble();
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
        if(tbl->item(i,dgs.ckSutunTur)->text()==tur)
        {
            QDateTime datet;
            int gun=datet.fromString(tbl->item(i,dgs.ckSutunTarih)->text(),"yyyy-MM-dd").date().day();
            int ay=datet.fromString(tbl->item(i,dgs.ckSutunTarih)->text(),"yyyy-MM-dd").date().month();
            int yil=datet.fromString(tbl->item(i,dgs.ckSutunTarih)->text(),"yyyy-MM-dd").date().year();

            QDate tarih;
            tarih.setDate(yil,ay,gun);

            if(tarih>=baslangic && tarih<=bitis)
            {
                tblOzet->insertRow(tblOzet->rowCount());
                QTableWidgetItem *itm0=new QTableWidgetItem(tbl->item(i,dgs.ckSutunTarih)->text());
                QTableWidgetItem *itm1=new QTableWidgetItem(tbl->item(i,dgs.ckSutunIsim)->text());
                QTableWidgetItem *itm2=new QTableWidgetItem(tbl->item(i,dgs.ckSutunBanka)->text());
                QTableWidgetItem *itm3=new QTableWidgetItem(tbl->item(i,dgs.ckSutunTutar)->text());
                QTableWidgetItem *itm4=new QTableWidgetItem(tbl->item(i,dgs.ckSutunMuhatap)->text());
                QTableWidgetItem *itm5=new QTableWidgetItem(tbl->item(i,dgs.ckSutunCekNo)->text());
                QTableWidgetItem *itm6=new QTableWidgetItem(tbl->item(i,dgs.ckSutunAciklama)->text());
                tblOzet->setItem(tblOzet->rowCount()-1,dgs.ckSutunTarih-2,itm0);//sil ve değiştir olmadığı için 2 çıkarıyoruz
                tblOzet->setItem(tblOzet->rowCount()-1,dgs.ckSutunIsim-2,itm1);
                tblOzet->setItem(tblOzet->rowCount()-1,dgs.ckSutunBanka-2,itm2);
                tblOzet->setItem(tblOzet->rowCount()-1,dgs.ckSutunTutar-2,itm3);
                tblOzet->setItem(tblOzet->rowCount()-1,dgs.ckSutunMuhatap-2,itm4);
                tblOzet->setItem(tblOzet->rowCount()-1,dgs.ckSutunCekNo-2,itm5);
                tblOzet->setItem(tblOzet->rowCount()-1,dgs.ckSutunAciklama-2,itm6);
                //tutar=tutar+tbl->item(i,dgs.ckSutunTutar)->text().toDouble();
                tutar=tutar+tblOzet->item(tblOzet->rowCount()-1,dgs.ftrSutunTutar-2)->text().toDouble();
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
    QCalendarWidget *cal = qobject_cast<QCalendarWidget *>(sender());
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
    qDebug()<<"listeCek:"<<listeCek;
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
        ui->tblCek->setCellWidget(ui->tblCek->rowCount()-1,dgs.ckSutunSil,btnSil);

        QPushButton *btnDegistir=new QPushButton();
        btnDegistir->setIcon(QIcon(QDir::currentPath()+"/icons/kilitkapali.png"));
        btnDegistir->setToolTip("Degiştir");
        connect(btnDegistir,SIGNAL(clicked()),this,SLOT(cekDegistir()));
        ui->tblCek->setCellWidget(ui->tblCek->rowCount()-1,dgs.ckSutunDegistir,btnDegistir);

        QTableWidgetItem *itm1=new QTableWidgetItem(listeCek.at(i));
        QTableWidgetItem *itm2=new QTableWidgetItem(listeCek.at(i+1));
        QTableWidgetItem *itm3=new QTableWidgetItem(listeCek.at(i+2));
        QTableWidgetItem *itm4=new QTableWidgetItem(listeCek.at(i+3));
        QTableWidgetItem *itm5=new QTableWidgetItem(listeCek.at(i+4));
        QTableWidgetItem *itm6=new QTableWidgetItem(listeCek.at(i+5));
        QTableWidgetItem *itm7=new QTableWidgetItem(listeCek.at(i+6));
        QTableWidgetItem *itm8=new QTableWidgetItem(listeCek.at(i+7));
        QTableWidgetItem *itm9=new QTableWidgetItem("0");
        QTableWidgetItem *itm10=new QTableWidgetItem("0");
        QTableWidgetItem *itm11=new QTableWidgetItem("0");

        ui->tblCek->setItem(ui->tblCek->rowCount()-1,dgs.ckSutunTarih,itm1);
        ui->tblCek->setItem(ui->tblCek->rowCount()-1,dgs.ckSutunIsim,itm2);
        ui->tblCek->setItem(ui->tblCek->rowCount()-1,dgs.ckSutunBanka,itm3);
        ui->tblCek->setItem(ui->tblCek->rowCount()-1,dgs.ckSutunTutar,itm4);
        ui->tblCek->setItem(ui->tblCek->rowCount()-1,dgs.ckSutunMuhatap,itm5);
        ui->tblCek->setItem(ui->tblCek->rowCount()-1,dgs.ckSutunCekNo,itm6);
        ui->tblCek->setItem(ui->tblCek->rowCount()-1,dgs.ckSutunAciklama,itm7);
        ui->tblCek->setItem(ui->tblCek->rowCount()-1,dgs.ckSutunTur,itm8);
        ui->tblCek->setItem(ui->tblCek->rowCount()-1,dgs.ckSutunKayit,itm9);
        ui->tblCek->setItem(ui->tblCek->rowCount()-1,dgs.ckSutunDegisim,itm10);
        ui->tblCek->setItem(ui->tblCek->rowCount()-1,dgs.ckSutunKilit,itm11);

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
    ui->tblCek->sortByColumn(dgs.ckSutunTarih);//tblfaturayı tarih sutunua göre sıralıyor
    degisiklikIzle=true;
}

void muhasib::sekmeCekAc()
{
    //ui->tabWidget->addTab(tbCek,"Çekler");
    ui->tabWidget->addTab(tbCek,dgs.sekmeCekListele);
    ui->tabWidget->setCurrentWidget(tbCek);
}

void muhasib::cekSil()
{
    sck.cekSil2(ToplamTutarCek, listSilinenCek, kaydetVar, ui->lblCek, ui->tblCek, sender());
}

void muhasib::cekDegistir()
{
    sck.cekDegistir2(degisiklikIzle, kaydetVar, ui->tblCek, ui->tabWidget, kilidiAcikSatirSayisi, sender());
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
        ui->tblCek->setCellWidget(ui->tblCek->rowCount()-1,dgs.ckSutunSil,btnSil);

        QPushButton *btnDegistir=new QPushButton();
        btnDegistir->setIcon(QIcon(QDir::currentPath()+"/icons/kilitkapali.png"));
        btnDegistir->setToolTip("Degiştir");
        connect(btnDegistir,SIGNAL(clicked()),this,SLOT(cekDegistir()));
        ui->tblCek->setCellWidget(ui->tblCek->rowCount()-1,dgs.ckSutunDegistir,btnDegistir);

        QTableWidgetItem *itm1=new QTableWidgetItem(query.value(0).toString());
        QTableWidgetItem *itm2=new QTableWidgetItem(query.value(1).toString());
        QTableWidgetItem *itm3=new QTableWidgetItem(query.value(2).toString());
        QTableWidgetItem *itm4=new QTableWidgetItem(query.value(3).toString());
        QTableWidgetItem *itm5=new QTableWidgetItem(query.value(4).toString());
        QTableWidgetItem *itm6=new QTableWidgetItem(query.value(5).toString());
        QTableWidgetItem *itm7=new QTableWidgetItem(query.value(6).toString());
        QTableWidgetItem *itm8=new QTableWidgetItem(query.value(7).toString());
        QTableWidgetItem *itm9=new QTableWidgetItem(query.value(8).toString());
        QTableWidgetItem *itm10=new QTableWidgetItem("0");
        QTableWidgetItem *itm11=new QTableWidgetItem("0");

        ui->tblCek->setItem(ui->tblCek->rowCount()-1,dgs.ckSutunTarih,itm1);
        ui->tblCek->setItem(ui->tblCek->rowCount()-1,dgs.ckSutunIsim,itm2);
        ui->tblCek->setItem(ui->tblCek->rowCount()-1,dgs.ckSutunBanka,itm3);
        ui->tblCek->setItem(ui->tblCek->rowCount()-1,dgs.ckSutunTutar,itm4);
        ui->tblCek->setItem(ui->tblCek->rowCount()-1,dgs.ckSutunMuhatap,itm5);
        ui->tblCek->setItem(ui->tblCek->rowCount()-1,dgs.ckSutunCekNo,itm6);
        ui->tblCek->setItem(ui->tblCek->rowCount()-1,dgs.ckSutunAciklama,itm7);
        ui->tblCek->setItem(ui->tblCek->rowCount()-1,dgs.ckSutunTur,itm8);
        ui->tblCek->setItem(ui->tblCek->rowCount()-1,dgs.ckSutunKayit,itm9);
        ui->tblCek->setItem(ui->tblCek->rowCount()-1,dgs.ckSutunDegisim,itm10);
        ui->tblCek->setItem(ui->tblCek->rowCount()-1,dgs.ckSutunKilit,itm11);

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
    degisiklikIzle=true;
    ui->tblCek->sortByColumn(dgs.ckSutunTarih);//tblfaturayı tarih sutunua göre sıralıyor
}

//FATURA ANA EKRANINDA MATRAH VE KDV ORANI DEĞİŞTİRİNCE KDV TUTARINI VE TUTARI YENİDEN HESAPLIYOR
void muhasib::faturaTutarHesapla(int a,int b)
{
    if(degisiklikIzle==true)
    {
        if(b==dgs.ftrSutunMatrah || b==dgs.ftrSutunKdvOrani)
        {
            double kdvTutari=ui->tblFatura->item(a,dgs.ftrSutunMatrah)->text().toDouble()*ui->tblFatura->item(a,dgs.ftrSutunKdvOrani)->text().toDouble()/100;
            double tutar=ui->tblFatura->item(a,dgs.ftrSutunMatrah)->text().toDouble()+kdvTutari;

            ui->tblFatura->item(a,dgs.ftrSutunKdvTutar)->setText(QString::number(kdvTutari));
            ui->tblFatura->item(a,dgs.ftrSutunTutar)->setText(QString::number(tutar));
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
        if(tbl->item(i,dgs.ftrSutunTur)->text()==tur)
        {
            QDateTime datet;
            int gun=datet.fromString(tbl->item(i,dgs.ftrSutunTarih)->text(),"yyyy-MM-dd").date().day();
            int ay=datet.fromString(tbl->item(i,dgs.ftrSutunTarih)->text(),"yyyy-MM-dd").date().month();
            int yil=datet.fromString(tbl->item(i,dgs.ftrSutunTarih)->text(),"yyyy-MM-dd").date().year();

            QDate tarih;
            tarih.setDate(yil,ay,gun);

            if(tarih>=baslangic && tarih<=bitis)
            {
                tblOzet->insertRow(tblOzet->rowCount());
                QTableWidgetItem *itm0=new QTableWidgetItem(tbl->item(i,dgs.ftrSutunTarih)->text());
                QTableWidgetItem *itm1=new QTableWidgetItem(tbl->item(i,dgs.ftrSutunIsim)->text());
                QTableWidgetItem *itm2=new QTableWidgetItem(tbl->item(i,dgs.ftrSutunTutar)->text());
                QTableWidgetItem *itm3=new QTableWidgetItem(tbl->item(i,dgs.ftrSutunAciklama)->text());
                QTableWidgetItem *itm4=new QTableWidgetItem(tbl->item(i,dgs.ftrSutunMatrah)->text());
                QTableWidgetItem *itm5=new QTableWidgetItem(tbl->item(i,dgs.ftrSutunKdvOrani)->text());
                QTableWidgetItem *itm6=new QTableWidgetItem(tbl->item(i,dgs.ftrSutunKdvTutar)->text());
                tblOzet->setItem(tblOzet->rowCount()-1,dgs.ftrSutunTarih-2,itm0);//sil ve değiştir olmadığı için -2 yazıyoruz
                tblOzet->setItem(tblOzet->rowCount()-1,dgs.ftrSutunIsim-2,itm1);
                tblOzet->setItem(tblOzet->rowCount()-1,dgs.ftrSutunTutar-2,itm2);
                tblOzet->setItem(tblOzet->rowCount()-1,dgs.ftrSutunAciklama-2,itm3);
                tblOzet->setItem(tblOzet->rowCount()-1,dgs.ftrSutunMatrah-2,itm4);
                tblOzet->setItem(tblOzet->rowCount()-1,dgs.ftrSutunKdvOrani-2,itm5);
                tblOzet->setItem(tblOzet->rowCount()-1,dgs.ftrSutunKdvTutar-2,itm6);
                //tutar=tutar+tbl->item(i,dgs.ftrSutunTutar)->text().toDouble();
                tutar=tutar+tblOzet->item(tblOzet->rowCount()-1,dgs.ftrSutunTutar-2)->text().toDouble();
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
    QCalendarWidget *cal = qobject_cast<QCalendarWidget *>(sender());
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
    query.exec("select f_tarih, f_isim, f_matrah, f_kdvorani, f_kdvtutari, f_tutar, f_aciklama, f_tur, f_id, f_hesap, f_kayitno from fatura");
    while(query.next())
    {
        ui->tblFatura->insertRow(ui->tblFatura->rowCount());

        QPushButton *btnSil=new QPushButton();
        btnSil->setIcon(QIcon(QDir::currentPath()+"/icons/sil.png"));
        btnSil->setToolTip("Sil");
        connect(btnSil,SIGNAL(clicked()),this,SLOT(faturaSil()));
        ui->tblFatura->setCellWidget(ui->tblFatura->rowCount()-1,dgs.ftrSutunSil,btnSil);

        QPushButton *btnDegistir=new QPushButton();
        btnDegistir->setIcon(QIcon(QDir::currentPath()+"/icons/kilitkapali.png"));
        btnDegistir->setToolTip("Degiştir");
        connect(btnDegistir,SIGNAL(clicked()),this,SLOT(faturaDegistir()));
        ui->tblFatura->setCellWidget(ui->tblFatura->rowCount()-1,dgs.ftrSutunDegistir,btnDegistir);

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
        QTableWidgetItem *itm13=new QTableWidgetItem(query.value(10).toString());

        ui->tblFatura->setItem(ui->tblFatura->rowCount()-1,dgs.ftrSutunKayitNo,itm13);
        ui->tblFatura->setItem(ui->tblFatura->rowCount()-1,dgs.ftrSutunTarih,itm1);
        ui->tblFatura->setItem(ui->tblFatura->rowCount()-1,dgs.ftrSutunIsim,itm2);
        ui->tblFatura->setItem(ui->tblFatura->rowCount()-1,dgs.ftrSutunMatrah,itm3);
        ui->tblFatura->setItem(ui->tblFatura->rowCount()-1,dgs.ftrSutunKdvOrani,itm4);
        ui->tblFatura->setItem(ui->tblFatura->rowCount()-1,dgs.ftrSutunKdvTutar,itm5);
        ui->tblFatura->setItem(ui->tblFatura->rowCount()-1,dgs.ftrSutunTutar,itm6);
        ui->tblFatura->setItem(ui->tblFatura->rowCount()-1,dgs.ftrSutunAciklama,itm7);
        ui->tblFatura->setItem(ui->tblFatura->rowCount()-1,dgs.ftrSutunTur,itm8);
        ui->tblFatura->setItem(ui->tblFatura->rowCount()-1,dgs.ftrSutunKayit,itm9);
        ui->tblFatura->setItem(ui->tblFatura->rowCount()-1,dgs.ftrSutunDegisim,itm10);
        ui->tblFatura->setItem(ui->tblFatura->rowCount()-1,dgs.ftrSutunKilit,itm11);
        ui->tblFatura->setItem(ui->tblFatura->rowCount()-1,dgs.ftrSutunHesap,itm12);

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
        itm13->setFlags(Qt::ItemIsEnabled);
        ToplamTutarFatura=ToplamTutarFatura+itm6->text().toDouble();//toplam tutarı uygulama başlayınca hesaplıyor
    }
    ui->lblFatura->setText("Kayıt: "+QString::number(ui->tblFatura->rowCount())+" Tutar: "+QString::number(ToplamTutarFatura));
    degisiklikIzle=true;
    ui->tblFatura->sortByColumn(dgs.ftrSutunTarih);//tblfaturayı tarih sutunua göre sıralıyor
}

//FATURALARI KAYDEDİYOR
void muhasib::faturaKaydet()
{
    sftr.faturaKaydet2(listSilinenFatura,ui->tblFatura);
}

//ANA EKRANDA FATURA TUTARI DEĞİŞTİKÇE TOPLAMIDA DEĞİŞİYOR
void muhasib::faturaToplamiHesapla(int a ,int b)
{
    if(degisiklikIzle==true && b==dgs.ftrSutunTutar)
    {
        ToplamTutarFatura=0;
        for(int i=0;i<ui->tblFatura->rowCount();i++)
        {
            ToplamTutarFatura=ToplamTutarFatura+ui->tblFatura->item(i,dgs.ftrSutunTutar)->text().toDouble();
        }
        ui->lblFatura->setText("Kayıt: "+QString::number(ui->tblFatura->rowCount())+" Tutar: "+QString::number(ToplamTutarFatura));
    }
}

//FATURA SEKMESİNİ AÇIYOR
void muhasib::sekmeFaturaAc()
{
    //ui->tabWidget->addTab(tbFatura,"Faturalar");
    ui->tabWidget->addTab(tbFatura,dgs.sekmeFaturaListele);
    ui->tabWidget->setCurrentWidget(tbFatura);
}

QString muhasib::getFaturaKayitNo(int sonNo)
{
    return "ftr"+ui->tblFatura->item(0,dgs.ftrSutunKayit)->text();

    /*
    int no=sonNo+1;
    faturaNo=no;
    QString sno=QString::number(no);
    if(sno.length()==1)
    {
        sno="00"+sno;
    }
    else if(sno.length()==2)
    {
        sno="0"+sno;
    }
    QDate tarih=tarih.currentDate();
    QString kayitNo="FTR"+tarih.toString("yy")+tarih.toString("MM")+sno;
    return kayitNo;
    */
}

//FATURA EKLEME EKRANINI AÇIYOR
void muhasib::yeniFaturaEkle()
{
    if(ui->tblHesap->rowCount()==0)
    {
        QMessageBox::warning(this,"Hata","Önce hesap ekleyin","Tamam");
    }
    else
    {
        degisiklikIzle=false;
        form_faturaEkle.setWindowFlags(Qt::Window);//fatura ekleme penceresinin köşesindeki 3 düğmenin gösterilmesi için
        form_faturaEkle.setListeHesap(getListeHesap());//fatura ekleme penceresinde hesapların isminin çıkabilmesi için
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
            ui->tblFatura->setCellWidget(ui->tblFatura->rowCount()-1,dgs.ftrSutunSil,btnSil);

            QPushButton *btnDegistir=new QPushButton();
            btnDegistir->setIcon(QIcon(QDir::currentPath()+"/icons/kilitkapali.png"));
            btnDegistir->setToolTip("Degiştir");
            connect(btnDegistir,SIGNAL(clicked()),this,SLOT(faturaDegistir()));
            ui->tblFatura->setCellWidget(ui->tblFatura->rowCount()-1,dgs.ftrSutunDegistir,btnDegistir);

            //double kdvTutari=listeFatura.at(i+2).toDouble()*listeFatura.at(i+3).toDouble()/100;

            //QDate tarih=QDate::fromString(listeFatura.at(i),"dd / MM / yyyy");
            //QTableWidgetItem *itm1=new QTableWidgetItem();
            //itm1->setData(Qt::DisplayRole,tarih);
            //ui->tblFatura->setItem(ui->tblFatura->rowCount()-1,dgs.ftrSutunTarih,itm1);

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
            //QTableWidgetItem *itm13=new QTableWidgetItem(getFaturaKayitNo(faturaNo));
            QTableWidgetItem *itm13=new QTableWidgetItem("1");

            ui->tblFatura->setItem(ui->tblFatura->rowCount()-1,dgs.ftrSutunTarih,itm1);
            ui->tblFatura->setItem(ui->tblFatura->rowCount()-1,dgs.ftrSutunKayitNo,itm13);
            ui->tblFatura->setItem(ui->tblFatura->rowCount()-1,dgs.ftrSutunIsim,itm2);
            ui->tblFatura->setItem(ui->tblFatura->rowCount()-1,dgs.ftrSutunMatrah,itm3);
            ui->tblFatura->setItem(ui->tblFatura->rowCount()-1,dgs.ftrSutunKdvOrani,itm4);
            ui->tblFatura->setItem(ui->tblFatura->rowCount()-1,dgs.ftrSutunKdvTutar,itm5);
            ui->tblFatura->setItem(ui->tblFatura->rowCount()-1,dgs.ftrSutunTutar,itm6);
            ui->tblFatura->setItem(ui->tblFatura->rowCount()-1,dgs.ftrSutunAciklama,itm7);
            ui->tblFatura->setItem(ui->tblFatura->rowCount()-1,dgs.ftrSutunTur,itm8);
            ui->tblFatura->setItem(ui->tblFatura->rowCount()-1,dgs.ftrSutunHesap,itm12);
            ui->tblFatura->setItem(ui->tblFatura->rowCount()-1,dgs.ftrSutunKayit,itm9);
            ui->tblFatura->setItem(ui->tblFatura->rowCount()-1,dgs.ftrSutunDegisim,itm10);
            ui->tblFatura->setItem(ui->tblFatura->rowCount()-1,dgs.ftrSutunKilit,itm11);

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
            itm13->setFlags(Qt::ItemIsEnabled);

            //fatura eklendikçe hesap tan tutarı düşüyor veya ekliyor
            for(int i=0;i<ui->tblHesap->rowCount();i++)
            {
                if(ui->tblHesap->item(i,dgs.hspSutunIsim)->text()==itm12->text())
                {
                    double hesapMeblag=0;
                    if(itm8->text()=="Gelen")
                    {
                        hesapMeblag=ui->tblHesap->item(i,dgs.hspSutunGuncelMeblag)->text().toDouble()-itm6->text().toDouble();
                    }
                    else if(itm8->text()=="Giden")
                    {
                        hesapMeblag=ui->tblHesap->item(i,dgs.hspSutunGuncelMeblag)->text().toDouble()+itm6->text().toDouble();
                    }
                    ui->tblHesap->item(i,dgs.hspSutunGuncelMeblag)->setText(QString::number(hesapMeblag));
                    ui->tblHesap->item(i,dgs.hspSutunDegisim)->setText("1");
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

        ui->tblFatura->sortByColumn(dgs.ftrSutunTarih);//tblfaturayı tarih sutununa göre sıralıyor
    }
}

//FATURA DEĞİŞTİRMEK İÇİN ANA EKRANDAKİ GİRİŞLERİ DEĞİŞTİRİLEBİLİR YAPIYOR
void muhasib::faturaDegistir()
{
    sftr.faturaDegistir2(degisiklikIzle, kaydetVar, ui->tblFatura, ui->tblHesap, ui->tabWidget, getListeHesap(), kilidiAcikSatirSayisi, sender());
}

//VAROLAN GİRİŞİ SİLİYOR
void muhasib::faturaSil()
{
    sftr.faturaSil2(ToplamTutarFatura, listSilinenFatura, kaydetVar, ui->lblFatura, ui->tblFatura,sender());
}

void muhasib::ilkYuklemeBaslangic()
{
    ui->cbFatura->addItems(QStringList()<<"Fatura"<<"Fatura Ekle"<<"Faturaları Listele"<<"Faturaları Karşılaştır");
    ui->cbCek->addItems(QStringList()<<"Çek"<<"Çek Ekle"<<"Çekleri Listele"<<"Çekleri Karşılaştır");
    ui->cbMaas_2->addItems(QStringList()<<"Maaş"<<"Maaş Ekle"<<"Maaşları Listele");
    ui->cbCalisan->addItems(QStringList()<<"Çalışan"<<"Çalışan Ekle"<<"Çalışanları Listele");
    ui->cbRapor->addItems(QStringList()<<"Rapor"<<"Gelirleri Göster"<<"Giderleri Göster"<<"Gelir/Gider"<<"Hesap Özeti");
    ui->cbHesap->addItems(QStringList()<<"Hesap"<<"Hesap Ekle"<<"Hesapları Listele");
}

//ÖNTANIMLI AYARLAR
void muhasib::ilkYukleme()
{
    sftr.ilkYukleme2(ToplamTutarFatura, ui->tblFatura,ui->tblGelenFaturalar, ui->tblGidenFaturalar, ui->tabFatura, ui->tabFaturaOzeti, tbFatura, tbFaturaOzeti, ui->tabWidget);
    sck.ilkYukleme2(ToplamTutarCek, ui->tblCek, ui->tblAlinanCek, ui->tblVerilenCek, ui->tabCek, ui->tabCekOzeti, tbCek, tbCekOzeti, ui->tabWidget);
    sms.ilkYukleme2(ToplamTutarMaas, ui->tblMaas, ui->tabMaas, tbMaas, ui->tabWidget);
    sclsn.ilkYukleme2(ToplamTutarCalisan, ui->tblCalisan, ui->tabCalisan, tbCalisan, ui->tabWidget);
    shsp.ilkYukleme2(ui->tblHesap, ui->tabHesap, tbHesap, ui->tabWidget);
    srpr.ilkYuklemeGelirler(ui->tblGelirler, ui->tabGelirler, tbGelirler, ui->tabWidget);
    srpr.ilkYuklemeGiderler(ui->tblGiderler, ui->tabGiderler, tbGiderler, ui->tabWidget);
    srpr.ilkYuklemeGgd(ui->tblGgd,ui->tabGgd,tbGgd,ui->tabWidget);
    srpr.ilkYuklemeHesapOzeti(ui->tblHesapOzeti,ui->tabHesapOzeti,tbHesapOzeti,ui->tabWidget);
    ilkYuklemeBaslangic();

    kaydetVar=false;
    degisiklikIzle=false;
    kilidiAcikSatirSayisi=0;
    veritabanindanYukle();

    faturaNo=98;

    ui->cbHesapOzeti->addItems(QStringList()<<"hesap seçin"<<getListeHesap());//hesap özeti penceresindeki cb ye hesapları yazdırıyor

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
