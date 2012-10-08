#include "sdigergider.h"

sdigergider::sdigergider()
{
}

void sdigergider::digerGiderKaydet(QStringList &listSilinenDigerGider, QTableWidget *tblDigerGider)
{
    QSqlQuery query;
    //yeni eklenen kayıtlar
    for(int i=0;i<tblDigerGider->rowCount();i++)
    {
        if(tblDigerGider->item(i,dgs.dgdSutunKayit)->text()=="0")
        {
            query.exec(QString("insert into digergider(dgd_tarih, dgd_isim, dgd_muhatap, dgd_tutar, dgd_aciklama, dgd_hesap) values ('%1', '%2', '%3', '%4', '%5', '%6')").arg(tblDigerGider->item(i,dgs.dgdSutunTarih)->text()).arg(tblDigerGider->item(i,dgs.dgdSutunIsim)->text()).arg(tblDigerGider->item(i,dgs.dgdSutunMuhatap)->text()).arg(tblDigerGider->item(i,dgs.dgdSutunTutar)->text()).arg(tblDigerGider->item(i,dgs.dgdSutunAciklama)->text()).arg(tblDigerGider->item(i,dgs.dgdSutunHesap)->text()));
            tblDigerGider->item(i,dgs.dgdSutunKayit)->setText(query.lastInsertId().toString());
        }
    }
    ////////////////////////
    //silinen kayıtlar
    for(int i=0;i<listSilinenDigerGider.count();i++)
    {
        query.exec(QString("delete from digergider where dgd_id='%1'").arg(listSilinenDigerGider.at(i)));
    }
    //////////////////////
    //değiştirilen kayıtlar
    for(int i=0;i<tblDigerGider->rowCount();i++)
    {
        if(tblDigerGider->item(i,dgs.dgdSutunDegisim)->text()=="1")
        {
            query.exec(QString("update digergider set dgd_tarih='%1', dgd_isim='%2', dgd_muhatap='%3', dgd_tutar='%4', dgd_aciklama='%5', dgd_hesap='%6' where dgd_id='%7'").arg(tblDigerGider->item(i,dgs.dgdSutunTarih)->text()).arg(tblDigerGider->item(i,dgs.dgdSutunIsim)->text()).arg(tblDigerGider->item(i,dgs.dgdSutunMuhatap)->text()).arg(tblDigerGider->item(i,dgs.dgdSutunTutar)->text()).arg(tblDigerGider->item(i,dgs.dgdSutunAciklama)->text()).arg(tblDigerGider->item(i,dgs.dgdSutunHesap)->text()).arg(tblDigerGider->item(i,dgs.dgdSutunKayit)->text()));
            tblDigerGider->item(i,dgs.dgdSutunDegisim)->setText("0");
        }
    }
    ///////////////////////////
}

void sdigergider::digerGiderSil(QStringList &listSilinenDigerGider, bool &kaydetVar, QTableWidget *tblDigerGider, QObject *obj)
{
    QPushButton *btn = qobject_cast<QPushButton *>(obj);
    //silinecek satir bulunuyor
    int silinecekSatir=-1;
    for(int i=0;i<tblDigerGider->rowCount();i++)
    {
        QPushButton *btnSil=qobject_cast<QPushButton *>(tblDigerGider->cellWidget(i,dgs.dgdSutunSil));
        if(btn==btnSil)
        {
            silinecekSatir=i;
            break;
        }
    }
    //////////////////////////////

    if(tblDigerGider->item(silinecekSatir,dgs.dgdSutunKilit)->text()=="1")
    {
        QPushButton *btnDegistir=qobject_cast<QPushButton *>(tblDigerGider->cellWidget(silinecekSatir,dgs.dgdSutunDegistir));
        btnDegistir->click();
    }

    listSilinenDigerGider.append(tblDigerGider->item(silinecekSatir,dgs.dgdSutunKayit)->text());

    //ToplamTutarDigerGider=ToplamTutarDigerGider-tblDigerGider->item(silinecekSatir,dgs.dgdSutunTutar)->text().toDouble();//silinen DigerGider tutarını toplamtutar dan çıkarıyor
    tblDigerGider->removeRow(silinecekSatir);
    //lblDigerGider->setText("Kayıt: "+QString::number(tblDigerGider->rowCount())+" Tutar: "+QString::number(ToplamTutarDigerGider));//label i güncelliyor

    kaydetVar=true;
}

void sdigergider::digerGiderDegistir(bool &degisiklikIzle, bool &kaydetVar, QTableWidget* tblDigerGider, QTableWidget* tblHesap, QTabWidget* tabWidget, QStringList listeHsp, int &kilidiAcikSatirSayisi, QObject* obj)
{
    degisiklikIzle=false;
    QPushButton *btnDegistir=new QPushButton();
    QPushButton *btn = qobject_cast<QPushButton *>(obj);

    //degisecek satiri bulunuyor
    int degisecekSatir=-1;
    for(int i=0;i<tblDigerGider->rowCount();i++)
    {
        btnDegistir=qobject_cast<QPushButton *>(tblDigerGider->cellWidget(i,dgs.dgdSutunDegistir));
        if(btn==btnDegistir)
        {
            degisecekSatir=i;
            break;
        }
    }
    //////////////////7

    if(tblDigerGider->item(degisecekSatir,dgs.dgdSutunKilit)->text()=="0")//kilit açılıyor
    {
        kilidiAcikSatirSayisi=kilidiAcikSatirSayisi+1;
        //diger gider sekmesi hariç diğer sekmeler donduruluyor
        for(int i=0;i<tabWidget->count();i++)
        {
            if(tabWidget->tabText(i)!=dgs.sekmeDigerGiderListele)
            {
                tabWidget->setTabEnabled(i,false);
                tabWidget->setTabsClosable(false);
            }
        }
        //////////////////////////////////////////////////////
        btnDegistir->setIcon(QIcon(QDir::currentPath()+"/icons/kilitacik.png"));//değiştir düğmesinin ikonu değişiyor
        for(int i=2;i<tblDigerGider->columnCount()-3;i++)//hesap sütununa girmesin
        {
            QTableWidgetItem *itm = tblDigerGider->item(degisecekSatir, i);
            itm->setFlags(Qt::ItemIsEditable|Qt::ItemIsSelectable|Qt::ItemIsEnabled);
            itm->setBackgroundColor(QColor(Qt::gray));
            /*
            if(i!=dgs.dgdSutunKdvTutar && i!=dgs.dgdSutunTutar && i!=dgs.dgdSutunKayitNo)//kdvtutari ve tutari uygulama hesaplayacak
            {
                QTableWidgetItem *itm = tblDigerGider->item(degisecekSatir, i);
                itm->setFlags(Qt::ItemIsEditable|Qt::ItemIsSelectable|Qt::ItemIsEnabled);
                itm->setBackgroundColor(QColor(Qt::gray));
            }
            */
        }
        //hesap sütununa combobox ekleniyor
        QTableWidgetItem *itmHesap = tblDigerGider->item(degisecekSatir, dgs.dgdSutunHesap);
        QString hesap=itmHesap->text();
        QComboBox *cmbHesap=new QComboBox();
        cmbHesap->addItems(listeHsp);
        cmbHesap->setCurrentIndex(cmbHesap->findText(hesap));
        tblDigerGider->setCellWidget(degisecekSatir,dgs.dgdSutunHesap,cmbHesap);
        /////////////////////////////////
        //tarih sutununa dateedit ekleniyor
        QDate dt=QDate::fromString(tblDigerGider->item(degisecekSatir,dgs.dgdSutunTarih)->text(),"yyyy-MM-dd");
        QDateEdit *date=new QDateEdit(dt);
        date->setDisplayFormat("yyyy-MM-dd");
        tblDigerGider->setCellWidget(degisecekSatir,dgs.dgdSutunTarih,date);
        ///////////////////////////////////
        //DigerGider hesabı veya tutarı değişirse hesap penceresinde de değişiyor
        double mevcutTutar=tblDigerGider->item(degisecekSatir,dgs.dgdSutunTutar)->text().toDouble();
        for(int i=0;i<tblHesap->rowCount();i++)
        {
            if(tblHesap->item(i,dgs.hspSutunIsim)->text()==hesap)
            {
                tblHesap->item(i,dgs.hspSutunGuncelMeblag)->setText(QString::number(tblHesap->item(i,dgs.hspSutunGuncelMeblag)->text().toDouble()+mevcutTutar));
                tblHesap->item(i,dgs.hspSutunDegisim)->setText("1");
                break;
            }
        }
        ///////////////////////////////

        tblDigerGider->item(degisecekSatir,dgs.dgdSutunDegisim)->setText("1");
        tblDigerGider->item(degisecekSatir,dgs.dgdSutunKilit)->setText("1");//kilit açıldığı için
        kaydetVar=true;
        degisiklikIzle=true;//satırda yapılan değişiklikleri kdvtutarı ve tutarı hesaplayabilmek için izlesin
    }
    else//kilit kapanıyor
    {
        kilidiAcikSatirSayisi=kilidiAcikSatirSayisi-1;
        //dondurulmuş sekmeler açılıyor
        if(kilidiAcikSatirSayisi==0)
        {
            for(int i=0;i<tabWidget->count();i++)
            {
                if(tabWidget->tabText(i)!=dgs.sekmeDigerGiderListele)
                {
                    tabWidget->setTabEnabled(i,true);
                    tabWidget->setTabsClosable(true);
                }
            }
        }
        //////////////////////////////////////////////////////77
        //kilitAcik=false;//kilit kapatıldı
        btnDegistir->setIcon(QIcon(QDir::currentPath()+"/icons/kilitkapali.png"));

        for(int i=2;i<tblDigerGider->columnCount()-3;i++)//hesap sütununa girmesin
        {
            QTableWidgetItem *itm = tblDigerGider->item(degisecekSatir, i);
            itm->setFlags(Qt::ItemIsEnabled);
            itm->setBackgroundColor(QColor(Qt::white));
        }
        //hesap sütunundaki combobox kaldırılıyor
        QComboBox *cmbHesap=qobject_cast<QComboBox *>(tblDigerGider->cellWidget(degisecekSatir,dgs.dgdSutunHesap));
        QString hesap=cmbHesap->currentText();
        tblDigerGider->removeCellWidget(degisecekSatir,dgs.dgdSutunHesap);
        QTableWidgetItem *itmHesap=new QTableWidgetItem();
        itmHesap->setText(hesap);
        tblDigerGider->setItem(degisecekSatir,dgs.dgdSutunHesap,itmHesap);
        /////////////////////////////////////////
        //tarih sutunundaki datedit kaldırılıyor
        QDateEdit *dateedit=qobject_cast<QDateEdit *>(tblDigerGider->cellWidget(degisecekSatir,dgs.dgdSutunTarih));
        QDate date=dateedit->date();
        QString tarih=date.toString("yyyy-MM-dd");
        tblDigerGider->removeCellWidget(degisecekSatir,dgs.dgdSutunTarih);
        QTableWidgetItem *itmTarih=new QTableWidgetItem();
        itmTarih->setText(tarih);
        tblDigerGider->setItem(degisecekSatir,dgs.dgdSutunTarih,itmTarih);
        ///////////////////////////////////////
        //DigerGider hesabı veya tutarı değişirse hesap penceresinde de değişiyor
        double yeniTutar=tblDigerGider->item(degisecekSatir,dgs.dgdSutunTutar)->text().toDouble();
        for(int i=0;i<tblHesap->rowCount();i++)
        {
            if(tblHesap->item(i,dgs.hspSutunIsim)->text()==hesap)
            {
                tblHesap->item(i,dgs.hspSutunGuncelMeblag)->setText(QString::number(tblHesap->item(i,dgs.hspSutunGuncelMeblag)->text().toDouble()-yeniTutar));
                tblHesap->item(i,dgs.hspSutunDegisim)->setText("1");
                break;
            }
        }
        ////////////////////////////////////////
        tblDigerGider->item(degisecekSatir,dgs.dgdSutunKilit)->setText("0");//kilit kapatıldığı için
    }
}

void sdigergider::ilkYukleme(QTableWidget* tblDigerGider, QWidget* tabDigerGider, QWidget* &tbDigerGider, QTabWidget* tabWidget)
{
    tblDigerGider->setRowCount(0);
    tblDigerGider->setColumnCount(11);
    QStringList baslik=(QStringList()<<""<<""<<"Tarih"<<"İsim"<<"Muhatap"<<"Tutar"<<"Açıklama"<<"Hesap"<<"Kayıt"<<"Degisim"<<"Kilit");
    tblDigerGider->setHorizontalHeaderLabels(baslik);
    tblDigerGider->horizontalHeader()->setResizeMode(QHeaderView::Stretch);
    tblDigerGider->horizontalHeader()->setResizeMode(dgs.dgdSutunSil,QHeaderView::Custom);
    tblDigerGider->horizontalHeader()->resizeSection(dgs.dgdSutunSil, 32);
    tblDigerGider->horizontalHeader()->setResizeMode(dgs.dgdSutunDegistir,QHeaderView::Custom);
    tblDigerGider->horizontalHeader()->resizeSection(dgs.dgdSutunDegistir, 32);

    tblDigerGider->hideColumn(dgs.dgdSutunKayit);
    tblDigerGider->hideColumn(dgs.dgdSutunDegisim);
    tblDigerGider->hideColumn(dgs.dgdSutunKilit);

    tbDigerGider=qobject_cast<QWidget *>(tabDigerGider);//tabHesaplar qwidget'a dönüştürülüyor
    tabWidget->removeTab(tabWidget->indexOf(tbDigerGider));//tabHesaplar kapatılıyor
}

