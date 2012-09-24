#include "shesap.h"
#include <QDebug>

shesap::shesap()
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
}

void shesap::hesapDegistir2(bool& degisiklikIzle, bool &kaydetVar, QTableWidget *tblHesap, QObject *obj)
{
    degisiklikIzle=false;
    QPushButton *btnDegistir=new QPushButton();
    QPushButton *btn = qobject_cast<QPushButton *>(obj);
    QList<QPushButton *> allPButtons = tblHesap->findChildren<QPushButton *>();

    int degisecekSatir=-1;
    for(int i=0;i<allPButtons.count();i++)
    {
        if(allPButtons.at(i)==btn)
        {
            btnDegistir=btn;
            degisecekSatir=(i-1)/2;
            break;
        }
    }
    if(tblHesap->item(degisecekSatir,hspSutunKilit)->text()=="0")
    {
        btnDegistir->setIcon(QIcon(QDir::currentPath()+"/icons/kilitacik.png"));//değiştir düğmesinin ikonu değişiyor
        for(int i=2;i<tblHesap->columnCount()-4;i++)//tür sütununa girmesin
        {
            if(i!=hspSutunGuncelMeblag)
            {
                QTableWidgetItem *itm = tblHesap->item(degisecekSatir, i);
                itm->setFlags(Qt::ItemIsEditable|Qt::ItemIsSelectable|Qt::ItemIsEnabled);
                itm->setBackgroundColor(QColor(Qt::gray));
            }
        }
        //tür sütununa combobox ekleniyor
        QTableWidgetItem *itm = tblHesap->item(degisecekSatir, hspSutunTur);
        QString tur=itm->text();
        QComboBox *cmb=new QComboBox();
        cmb->addItems(form_hesapEkle.getListeCbHesapTur());
        cmb->setCurrentIndex(cmb->findText(tur));

        tblHesap->setCellWidget(degisecekSatir,hspSutunTur,cmb);
        /////////////////////////////////
        //kilitAcik=true;
        tblHesap->item(degisecekSatir,hspSutunDegisim)->setText("1");
        tblHesap->item(degisecekSatir,hspSutunKilit)->setText("1");//kilit açıldığı için
        kaydetVar=true;
        degisiklikIzle=true;//satırda yapılan değişiklikleri kdvtutarı ve tutarı hesaplayabilmek için izlesin
    }
    else
    {
        btnDegistir->setIcon(QIcon(QDir::currentPath()+"/icons/kilitkapali.png"));

        for(int i=2;i<tblHesap->columnCount()-4;i++)//tür sütununa girmesin
        {
            QTableWidgetItem *itm = tblHesap->item(degisecekSatir, i);
            itm->setFlags(Qt::ItemIsEnabled);
            itm->setBackgroundColor(QColor(Qt::white));
        }
        //tür sütunundaki combobox kaldırılıyor
        QComboBox *cmb=qobject_cast<QComboBox *>(tblHesap->cellWidget(degisecekSatir,hspSutunTur));
        QString HesaplarTuru=cmb->currentText();
        tblHesap->removeCellWidget(degisecekSatir,hspSutunTur);
        QTableWidgetItem *itm=new QTableWidgetItem();
        itm->setText(HesaplarTuru);
        tblHesap->setItem(degisecekSatir,hspSutunTur,itm);
        /////////////////////////////////////////
        //kilitAcik=false;
        tblHesap->item(degisecekSatir,hspSutunKilit)->setText("0");//kilit kapatıldığı için
    }
}

void shesap::hesapKaydet2(QStringList &listSilinenHesap,QTableWidget* tblHesap)
{
    QSqlQuery query;
    //yeni eklenen kayıtlar
    for(int i=0;i<tblHesap->rowCount();i++)
    {
        if(tblHesap->item(i,hspSutunKayit)->text()=="0")
        {
            query.exec(QString("insert into hesap(h_isim, h_baslangicmeblagi, h_guncelmeblag, h_tur) values ('%1', '%2', '%3', '%4')").arg(tblHesap->item(i,hspSutunIsim)->text()).arg(tblHesap->item(i,hspSutunBaslangicMeblagi)->text()).arg(tblHesap->item(i,hspSutunGuncelMeblag)->text()).arg(tblHesap->item(i,hspSutunTur)->text()));
            tblHesap->item(i,hspSutunKayit)->setText(query.lastInsertId().toString());
        }
    }
    ////////////////////////
    //silinen kayıtlar
    for(int i=0;i<listSilinenHesap.count();i++)
    {
        query.exec(QString("delete from hesap where h_id='%1'").arg(listSilinenHesap.at(i)));
    }
    //////////////////////
    //değiştirilen kayıtlar
    for(int i=0;i<tblHesap->rowCount();i++)
    {
        if(tblHesap->item(i,hspSutunDegisim)->text()=="1")
        {
            query.exec(QString("update hesap set h_isim='%1', h_baslangicmeblagi='%2', h_guncelmeblag='%5', h_tur='%3' where h_id='%4'").arg(tblHesap->item(i,hspSutunIsim)->text()).arg(tblHesap->item(i,hspSutunBaslangicMeblagi)->text()).arg(tblHesap->item(i,hspSutunTur)->text()).arg(tblHesap->item(i,hspSutunKayit)->text()).arg(tblHesap->item(i,hspSutunGuncelMeblag)->text()));
            tblHesap->item(i,hspSutunDegisim)->setText("0");
        }
    }
}

void shesap::hesapSil2(QStringList &listSilinenHesap, bool &kaydetVar, QTableWidget* tblHesap, QObject* obj)
{
    QPushButton *btn = qobject_cast<QPushButton *>(obj);
    QList<QPushButton *> allPButtons = tblHesap->findChildren<QPushButton *>();

    int silinecekSatir=-1;
    for(int i=0;i<allPButtons.count();i++)
    {
        if(allPButtons.at(i)==btn)
        {
            silinecekSatir=i/2;
            break;
        }
    }
    if(tblHesap->item(silinecekSatir,hspSutunKilit)->text()=="1")
    {
        QPushButton *btnDegistir=qobject_cast<QPushButton *>(tblHesap->cellWidget(silinecekSatir,hspSutunDegistir));
        btnDegistir->click();
    }

    listSilinenHesap.append(tblHesap->item(silinecekSatir,hspSutunKayit)->text());

    //ToplamTutarHesaplar=ToplamTutarHesaplar-tblHesap->item(silinecekSatir,clsSutunMaas)->text().toDouble();//silinen maas tutarını toplamtutar dan çıkarıyor
    tblHesap->removeRow(silinecekSatir);
    //ui->lblHesaplar->setText("Kayıt: "+QString::number(tblHesap->rowCount())+" Tutar: "+QString::number(ToplamTutarHesaplar));//label i güncelliyor

    kaydetVar=true;
}

void shesap::ilkYukleme2(QTableWidget* tblHesap, QWidget* tabHesap, QWidget* &tbHesap, QTabWidget* tabWidget)
{
    tblHesap->setRowCount(0);
    tblHesap->setColumnCount(9);
    QStringList baslik=(QStringList()<<""<<""<<"İsim"<<"Başlangıç Meblağı"<<"Güncel Meblag"<<"Tür"<<"Kayıt"<<"Degisim"<<"Kilit");
    tblHesap->setHorizontalHeaderLabels(baslik);
    tblHesap->horizontalHeader()->setResizeMode(QHeaderView::Stretch);
    tblHesap->horizontalHeader()->setResizeMode(hspSutunSil,QHeaderView::Custom);
    tblHesap->horizontalHeader()->resizeSection(hspSutunSil, 32);
    tblHesap->horizontalHeader()->setResizeMode(hspSutunDegistir,QHeaderView::Custom);
    tblHesap->horizontalHeader()->resizeSection(hspSutunDegistir, 32);

    //tblHesap->hideColumn(hspSutunKayit);
    //tblHesap->hideColumn(hspSutunDegisim);
    //tblHesap->hideColumn(hspSutunKilit);

    tbHesap=qobject_cast<QWidget *>(tabHesap);//tabHesaplar qwidget'a dönüştürülüyor
    tabWidget->removeTab(tabWidget->indexOf(tbHesap));//tabHesaplar kapatılıyor
}
