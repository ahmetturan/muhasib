#include "srapor.h"

srapor::srapor()
{}

void srapor::giderleriYukle(QTableWidget* tblGiderler, QTableWidget* tblFatura, QTableWidget* tblCek, QTableWidget* tblMaas, QTableWidget *tblDigerGider)
{
    tblGiderler->setRowCount(0);
    for(int i=0;i<tblFatura->rowCount();i++)
    {
        if(tblFatura->item(i,dgs.ftrSutunTur)->text()=="Gelen")
        {
            tblGiderler->insertRow(tblGiderler->rowCount());
            QTableWidgetItem *itm0=new QTableWidgetItem(tblFatura->item(i,dgs.ftrSutunTarih)->text());
            tblGiderler->setItem(tblGiderler->rowCount()-1,dgs.gdrSutunTarih,itm0);
            QTableWidgetItem *itm1=new QTableWidgetItem("Fatura");
            tblGiderler->setItem(tblGiderler->rowCount()-1,dgs.gdrSutunTur,itm1);
            QTableWidgetItem *itm2=new QTableWidgetItem(tblFatura->item(i,dgs.ftrSutunIsim)->text());
            tblGiderler->setItem(tblGiderler->rowCount()-1,dgs.gdrSutunGider,itm2);
            QTableWidgetItem *itm3=new QTableWidgetItem(tblFatura->item(i,dgs.ftrSutunTutar)->text());
            tblGiderler->setItem(tblGiderler->rowCount()-1,dgs.gdrSutunTutar,itm3);
        }
    }
    for(int i=0;i<tblCek->rowCount();i++)
    {
        if(tblCek->item(i,dgs.ckSutunTur)->text()=="Verilen")
        {
            tblGiderler->insertRow(tblGiderler->rowCount());
            QTableWidgetItem *itm0=new QTableWidgetItem(tblCek->item(i,dgs.ckSutunTarih)->text());
            tblGiderler->setItem(tblGiderler->rowCount()-1,dgs.gdrSutunTarih,itm0);
            QTableWidgetItem *itm1=new QTableWidgetItem("Çek");
            tblGiderler->setItem(tblGiderler->rowCount()-1,dgs.gdrSutunTur,itm1);
            QTableWidgetItem *itm2=new QTableWidgetItem(tblCek->item(i,dgs.ckSutunIsim)->text());
            tblGiderler->setItem(tblGiderler->rowCount()-1,dgs.gdrSutunGider,itm2);
            QTableWidgetItem *itm3=new QTableWidgetItem(tblCek->item(i,dgs.ckSutunTutar)->text());
            tblGiderler->setItem(tblGiderler->rowCount()-1,dgs.gdrSutunTutar,itm3);
        }
    }
    for(int i=0;i<tblMaas->rowCount();i++)
    {
        tblGiderler->insertRow(tblGiderler->rowCount());
        QTableWidgetItem *itm0=new QTableWidgetItem(tblMaas->item(i,dgs.msSutunTarih)->text());
        tblGiderler->setItem(tblGiderler->rowCount()-1,dgs.gdrSutunTarih,itm0);
        QTableWidgetItem *itm1=new QTableWidgetItem("Maaş");
        tblGiderler->setItem(tblGiderler->rowCount()-1,dgs.gdrSutunTur,itm1);
        QTableWidgetItem *itm2=new QTableWidgetItem(tblMaas->item(i,dgs.msSutunCalisan)->text());
        tblGiderler->setItem(tblGiderler->rowCount()-1,dgs.gdrSutunGider,itm2);
        QTableWidgetItem *itm3=new QTableWidgetItem(tblMaas->item(i,dgs.msSutunMaas)->text());
        tblGiderler->setItem(tblGiderler->rowCount()-1,dgs.gdrSutunTutar,itm3);
    }
    for(int i=0;i<tblDigerGider->rowCount();i++)
    {
        tblGiderler->insertRow(tblGiderler->rowCount());
        QTableWidgetItem *itmTarih=new QTableWidgetItem(tblDigerGider->item(i,dgs.dgdSutunTarih)->text());
        QTableWidgetItem *itmTur=new QTableWidgetItem("Diğer");
        QTableWidgetItem *itmIsim=new QTableWidgetItem(tblDigerGider->item(i,dgs.dgdSutunIsim)->text());
        QTableWidgetItem *itmTutar=new QTableWidgetItem(tblDigerGider->item(i,dgs.dgdSutunTutar)->text());
        tblGiderler->setItem(tblGiderler->rowCount()-1,dgs.gdrSutunTarih,itmTarih);
        tblGiderler->setItem(tblGiderler->rowCount()-1,dgs.gdrSutunTur,itmTur);
        tblGiderler->setItem(tblGiderler->rowCount()-1,dgs.gdrSutunGider,itmIsim);
        tblGiderler->setItem(tblGiderler->rowCount()-1,dgs.gdrSutunTutar,itmTutar);
    }
    tblGiderler->sortByColumn(dgs.gdrSutunTarih);
}

void srapor::gelirleriYukle(QTableWidget *tblGelirler, QTableWidget *tblFatura, QTableWidget *tblCek, QTableWidget *tblDigerGelir)
{
    tblGelirler->setRowCount(0);
    for(int i=0;i<tblFatura->rowCount();i++)
    {
        if(tblFatura->item(i,dgs.ftrSutunTur)->text()=="Giden")
        {
            tblGelirler->insertRow(tblGelirler->rowCount());
            QTableWidgetItem *itm0=new QTableWidgetItem(tblFatura->item(i,dgs.ftrSutunTarih)->text());
            tblGelirler->setItem(tblGelirler->rowCount()-1,dgs.glrSutunTarih,itm0);
            QTableWidgetItem *itm1=new QTableWidgetItem("Fatura");
            tblGelirler->setItem(tblGelirler->rowCount()-1,dgs.glrSutunTur,itm1);
            QTableWidgetItem *itm2=new QTableWidgetItem(tblFatura->item(i,dgs.ftrSutunIsim)->text());
            tblGelirler->setItem(tblGelirler->rowCount()-1,dgs.glrSutunGelir,itm2);
            QTableWidgetItem *itm3=new QTableWidgetItem(tblFatura->item(i,dgs.ftrSutunTutar)->text());
            tblGelirler->setItem(tblGelirler->rowCount()-1,dgs.glrSutunTutar,itm3);
        }
    }
    for(int i=0;i<tblCek->rowCount();i++)
    {
        if(tblCek->item(i,dgs.ckSutunTur)->text()=="Alınan")
        {
            tblGelirler->insertRow(tblGelirler->rowCount());
            QTableWidgetItem *itm0=new QTableWidgetItem(tblCek->item(i,dgs.ckSutunTarih)->text());
            tblGelirler->setItem(tblGelirler->rowCount()-1,dgs.glrSutunTarih,itm0);
            QTableWidgetItem *itm1=new QTableWidgetItem("Çek");
            tblGelirler->setItem(tblGelirler->rowCount()-1,dgs.glrSutunTur,itm1);
            QTableWidgetItem *itm2=new QTableWidgetItem(tblCek->item(i,dgs.ckSutunIsim)->text());
            tblGelirler->setItem(tblGelirler->rowCount()-1,dgs.glrSutunGelir,itm2);
            QTableWidgetItem *itm3=new QTableWidgetItem(tblCek->item(i,dgs.ckSutunTutar)->text());
            tblGelirler->setItem(tblGelirler->rowCount()-1,dgs.glrSutunTutar,itm3);
        }
    }
    for(int i=0;i<tblDigerGelir->rowCount();i++)
    {
        tblGelirler->insertRow(tblGelirler->rowCount());
        QTableWidgetItem *itmTarih=new QTableWidgetItem(tblDigerGelir->item(i,dgs.dglSutunTarih)->text());
        QTableWidgetItem *itmTur=new QTableWidgetItem("Diğer");
        QTableWidgetItem *itmIsim=new QTableWidgetItem(tblDigerGelir->item(i,dgs.dglSutunIsim)->text());
        QTableWidgetItem *itmTutar=new QTableWidgetItem(tblDigerGelir->item(i,dgs.dglSutunTutar)->text());
        tblGelirler->setItem(tblGelirler->rowCount()-1,dgs.glrSutunTarih,itmTarih);
        tblGelirler->setItem(tblGelirler->rowCount()-1,dgs.glrSutunTur,itmTur);
        tblGelirler->setItem(tblGelirler->rowCount()-1,dgs.glrSutunGelir,itmIsim);
        tblGelirler->setItem(tblGelirler->rowCount()-1,dgs.glrSutunTutar,itmTutar);
    }
    tblGelirler->sortByColumn(dgs.glrSutunTarih);
}

//GGD EKRANINA FATURAYI YUKLUYOR
void srapor::ggdFaturaYukle(QTableWidget *tblGgd, QTableWidget *tblFatura)
{
    double faturaGelirTutar=0;
    double faturaGiderTutar=0;

    for(int i=0;i<tblFatura->rowCount();i++)
    {
        if(tblFatura->item(i,dgs.ftrSutunTur)->text()=="Giden")
        {
            faturaGelirTutar=faturaGelirTutar+tblFatura->item(i,dgs.ftrSutunTutar)->text().toDouble();
        }
        else if(tblFatura->item(i,dgs.ftrSutunTur)->text()=="Gelen")
        {
            faturaGiderTutar=faturaGiderTutar+tblFatura->item(i,dgs.ftrSutunTutar)->text().toDouble();
        }
    }

    tblGgd->insertRow(tblGgd->rowCount());
    tblGgd->setRowHeight(tblGgd->rowCount()-1,40);
    QTableWidgetItem *itm0=new QTableWidgetItem("Fatura");
    QTableWidgetItem *itm1=new QTableWidgetItem(QString::number(faturaGelirTutar));
    QTableWidgetItem *itm2=new QTableWidgetItem(QString::number(faturaGiderTutar));
    QTableWidgetItem *itm3=new QTableWidgetItem(QString::number(faturaGelirTutar-faturaGiderTutar));
    ggdItem(itm0);
    ggdItem(itm1);
    ggdItem(itm2);
    ggdItem(itm3);
    tblGgd->setItem(tblGgd->rowCount()-1,dgs.ggdSutunTur,itm0);
    tblGgd->setItem(tblGgd->rowCount()-1,dgs.ggdSutunGelir,itm1);
    tblGgd->setItem(tblGgd->rowCount()-1,dgs.ggdSutunGider,itm2);
    tblGgd->setItem(tblGgd->rowCount()-1,dgs.ggdSutunFark,itm3);
}

//GGD EKRANINA MAAS YUKLUYOR
void srapor::ggdMaasYukle(QTableWidget *tblGgd, QTableWidget *tblMaas)
{
    double maasTutar=0;
    for(int i=0;i<tblMaas->rowCount();i++)
    {
        maasTutar=maasTutar+tblMaas->item(i,dgs.msSutunMaas)->text().toDouble();
    }
    tblGgd->insertRow(tblGgd->rowCount());
    tblGgd->setRowHeight(tblGgd->rowCount()-1,40);
    QTableWidgetItem *itm0=new QTableWidgetItem("Maaş");
    QTableWidgetItem *itm1=new QTableWidgetItem("-");
    QTableWidgetItem *itm2=new QTableWidgetItem(QString::number(maasTutar));
    QTableWidgetItem *itm3=new QTableWidgetItem(QString::number(0-maasTutar));
    ggdItem(itm0);
    ggdItem(itm1);
    ggdItem(itm2);
    ggdItem(itm3);
    tblGgd->setItem(tblGgd->rowCount()-1,dgs.ggdSutunTur,itm0);
    tblGgd->setItem(tblGgd->rowCount()-1,dgs.ggdSutunGelir,itm1);
    tblGgd->setItem(tblGgd->rowCount()-1,dgs.ggdSutunGider,itm2);
    tblGgd->setItem(tblGgd->rowCount()-1,dgs.ggdSutunFark,itm3);
}

//GGD EKRANINA TOPLAMI YUKLUYOR
void srapor::ggdToplamiYukle(QTableWidget *tblGgd)
{
    double toplamGelir=0;
    double toplamGider=0;
    for(int i=0;i<tblGgd->rowCount();i++)
    {
        toplamGelir=toplamGelir+tblGgd->item(i,dgs.ggdSutunGelir)->text().toDouble();
    }
    for(int i=0;i<tblGgd->rowCount();i++)
    {
        toplamGider=toplamGider+tblGgd->item(i,dgs.ggdSutunGider)->text().toDouble();
    }

    tblGgd->insertRow(tblGgd->rowCount());
    tblGgd->setRowHeight(tblGgd->rowCount()-1,40);
    QTableWidgetItem *itm0=new QTableWidgetItem("Toplam");
    QTableWidgetItem *itm1=new QTableWidgetItem(QString::number(toplamGelir));
    QTableWidgetItem *itm2=new QTableWidgetItem(QString::number(toplamGider));
    QTableWidgetItem *itm3=new QTableWidgetItem(QString::number(toplamGelir-toplamGider));
    ggdItem(itm0);
    ggdItem(itm1);
    ggdItem(itm2);
    ggdItem(itm3);
    tblGgd->setItem(tblGgd->rowCount()-1,dgs.ggdSutunTur,itm0);
    tblGgd->setItem(tblGgd->rowCount()-1,dgs.ggdSutunGelir,itm1);
    tblGgd->setItem(tblGgd->rowCount()-1,dgs.ggdSutunGider,itm2);
    tblGgd->setItem(tblGgd->rowCount()-1,dgs.ggdSutunFark,itm3);
}

//GGD EKRANINI DOLDURUYOR
void srapor::ggdYukle(QTableWidget *tblGgd, QTableWidget *tblFatura, QTableWidget *tblMaas)
{
    tblGgd->setRowCount(0);//önceki girişler siliniyor
    ggdFaturaYukle(tblGgd,tblFatura);
    ggdMaasYukle(tblGgd,tblMaas);
    ggdToplamiYukle(tblGgd);
}

//YAZITİPİNİ BÜYÜTÜYOR VE YAZIYI ORTAYA ALIYOR
void srapor::ggdItem(QTableWidgetItem *itm)
{
    QFont fnt;
    fnt.setPointSize(20);
    itm->setFont(fnt);
    itm->setTextAlignment(Qt::AlignHCenter);
}

//HESAP ÖZETİ EKRANINA FATURAYI YÜKLÜYOR
void srapor::hesapOzetiRaporlaFatura(QTableWidget *tblFatura, QTableWidget *tblHesapOzeti, QComboBox *cbHesapOzeti)
{
    for(int i=0;i<tblFatura->rowCount();i++)
    {
        if(tblFatura->item(i,dgs.ftrSutunHesap)->text()==cbHesapOzeti->currentText())
        {
            tblHesapOzeti->insertRow(tblHesapOzeti->rowCount());
            QTableWidgetItem *itmTarih=new QTableWidgetItem(tblFatura->item(i,dgs.ftrSutunTarih)->text());
            QTableWidgetItem *itmKayitNo=new QTableWidgetItem(tblFatura->item(i,dgs.ftrSutunKayitNo)->text());
            QTableWidgetItem *itmIsim=new QTableWidgetItem(tblFatura->item(i,dgs.ftrSutunIsim)->text());
            QTableWidgetItem *itmTur=new QTableWidgetItem(tblFatura->item(i,dgs.ftrSutunTur)->text());
            QTableWidgetItem *itmTutar=new QTableWidgetItem(tblFatura->item(i,dgs.ftrSutunTutar)->text());
            tblHesapOzeti->setItem(tblHesapOzeti->rowCount()-1,dgs.hoztSutunTarih,itmTarih);
            tblHesapOzeti->setItem(tblHesapOzeti->rowCount()-1,dgs.hoztSutunKayitNo,itmKayitNo);
            tblHesapOzeti->setItem(tblHesapOzeti->rowCount()-1,dgs.hoztSutunIsim,itmIsim);
            tblHesapOzeti->setItem(tblHesapOzeti->rowCount()-1,dgs.hoztSutunGG,itmTur);
            tblHesapOzeti->setItem(tblHesapOzeti->rowCount()-1,dgs.hoztSutunTutar,itmTutar);
            itmTarih->setFlags(Qt::ItemIsEnabled);//salt okunur hücreler
            itmKayitNo->setFlags(Qt::ItemIsEnabled);
            itmIsim->setFlags(Qt::ItemIsEnabled);
            itmTur->setFlags(Qt::ItemIsEnabled);
            itmTutar->setFlags(Qt::ItemIsEnabled);
        }
    }
}

//HESAP ÖZETİ EKRANINA MAAŞI YÜKLÜYOR
void srapor::hesapOzetiRaporlaMaas(QTableWidget *tblMaas, QTableWidget *tblHesapOzeti, QComboBox *cbHesapOzeti)
{
    for(int i=0;i<tblMaas->rowCount();i++)
    {
        if(tblMaas->item(i,dgs.msSutunHesap)->text()==cbHesapOzeti->currentText())
        {
            tblHesapOzeti->insertRow(tblHesapOzeti->rowCount());

            QTableWidgetItem *itmTarih=new QTableWidgetItem(tblMaas->item(i,dgs.msSutunTarih)->text());
            //QTableWidgetItem *itmKayitNo=new QTableWidgetItem(tblMaas->item(i,dgs.msSutunKayitNo)->text());
            QTableWidgetItem *itmKayitNo=new QTableWidgetItem("1");
            QTableWidgetItem *itmIsim=new QTableWidgetItem(tblMaas->item(i,dgs.msSutunCalisan)->text()+" ("+tblMaas->item(i,dgs.msSutunTur)->text()+")");
            QTableWidgetItem *itmTur=new QTableWidgetItem(tblMaas->item(i,dgs.msSutunTur)->text());
            QTableWidgetItem *itmTutar=new QTableWidgetItem(tblMaas->item(i,dgs.msSutunMaas)->text());
            tblHesapOzeti->setItem(tblHesapOzeti->rowCount()-1,dgs.hoztSutunTarih,itmTarih);
            tblHesapOzeti->setItem(tblHesapOzeti->rowCount()-1,dgs.hoztSutunKayitNo,itmKayitNo);
            tblHesapOzeti->setItem(tblHesapOzeti->rowCount()-1,dgs.hoztSutunIsim,itmIsim);
            tblHesapOzeti->setItem(tblHesapOzeti->rowCount()-1,dgs.hoztSutunGG,itmTur);
            tblHesapOzeti->setItem(tblHesapOzeti->rowCount()-1,dgs.hoztSutunTutar,itmTutar);
            itmTarih->setFlags(Qt::ItemIsEnabled);//salt okunur hücreler
            itmKayitNo->setFlags(Qt::ItemIsEnabled);
            itmIsim->setFlags(Qt::ItemIsEnabled);
            itmTur->setFlags(Qt::ItemIsEnabled);
            itmTutar->setFlags(Qt::ItemIsEnabled);
        }
    }
}

void srapor::ilkYuklemeGelirler(QTableWidget* tblGelirler, QWidget* tabGelirler, QWidget* &tbGelirler, QTabWidget* tabWidget)
{
    tblGelirler->setRowCount(0);
    tblGelirler->setColumnCount(4);
    QStringList baslik=(QStringList()<<"Tarih"<<"Tür"<<"Gelir"<<"Tutar");
    tblGelirler->setHorizontalHeaderLabels(baslik);
    tblGelirler->horizontalHeader()->setResizeMode(QHeaderView::Stretch);
    tblGelirler->setEditTriggers(QAbstractItemView::NoEditTriggers);

    tbGelirler=qobject_cast<QWidget *>(tabGelirler);//tabGelirler qwidget'a dönüştürülüyor
    tabWidget->removeTab(tabWidget->indexOf(tbGelirler));//tabGelirler kapatılıyor
}

void srapor::ilkYuklemeGiderler(QTableWidget* tblGiderler, QWidget* tabGiderler, QWidget* &tbGiderler, QTabWidget* tabWidget)
{
    tblGiderler->setRowCount(0);
    tblGiderler->setColumnCount(4);
    QStringList baslik=(QStringList()<<"Tarih"<<"Tür"<<"Gider"<<"Tutar");
    tblGiderler->setHorizontalHeaderLabels(baslik);
    tblGiderler->horizontalHeader()->setResizeMode(QHeaderView::Stretch);
    tblGiderler->setEditTriggers(QAbstractItemView::NoEditTriggers);

    tbGiderler=qobject_cast<QWidget *>(tabGiderler);//tabGiderler qwidget'a dönüştürülüyor
    tabWidget->removeTab(tabWidget->indexOf(tbGiderler));//tabGiderler kapatılıyor
}

void srapor::ilkYuklemeGgd(QTableWidget* tblGgd, QWidget* tabGgd, QWidget* &tbGgd, QTabWidget* tabWidget)
{
    tblGgd->setRowCount(0);
    tblGgd->setColumnCount(4);
    QStringList baslik=(QStringList()<<"Tür"<<"Gelir"<<"Gider"<<"Fark");
    tblGgd->setHorizontalHeaderLabels(baslik);
    tblGgd->horizontalHeader()->setResizeMode(QHeaderView::Stretch);
    tblGgd->setEditTriggers(QAbstractItemView::NoEditTriggers);
    tblGgd->verticalHeader()->hide();//soldaki satır numrasını gösteren header'ı saklıyorum

    tbGgd=qobject_cast<QWidget *>(tabGgd);//tabGiderler qwidget'a dönüştürülüyor
    tabWidget->removeTab(tabWidget->indexOf(tbGgd));//tabGiderler kapatılıyor
}

void srapor::ilkYuklemeHesapOzeti(QTableWidget* tblHesapOzeti, QWidget* tabHesapOzeti, QWidget* &tbHesapOzeti, QTabWidget* tabWidget)
{
    tblHesapOzeti->setRowCount(0);
    tblHesapOzeti->setColumnCount(5);
    QStringList baslik=(QStringList()<<"Tarih"<<"Kayıt No"<<"İsim"<<"Gelir/Gider"<<"Tutar");
    tblHesapOzeti->setHorizontalHeaderLabels(baslik);
    tblHesapOzeti->horizontalHeader()->setResizeMode(QHeaderView::Stretch);
    tblHesapOzeti->setEditTriggers(QAbstractItemView::NoEditTriggers);

    tbHesapOzeti=qobject_cast<QWidget *>(tabHesapOzeti);//tabhesapozeti qwidget'a dönüştürülüyor
    tabWidget->removeTab(tabWidget->indexOf(tbHesapOzeti));//tabhesapozeti kapatılıyor
}
