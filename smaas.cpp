#include "smaas.h"

smaas::smaas()
{
    clsSutunIsim=2;
}

void smaas::maasKaydet2(QStringList &listSilinenMaas,QTableWidget* tblMaas)
{
    QSqlQuery query;
    //yeni eklenen kayıtlar
    for(int i=0;i<tblMaas->rowCount();i++)
    {
        if(tblMaas->item(i,dgs.msSutunKayit)->text()=="0")
        {
            query.exec(QString("insert into maas(m_tarih, m_calisan, m_maas, m_ay, m_tur, m_hesap) values ('%1', '%2', '%3', '%4', '%5', '%6')").arg(tblMaas->item(i,dgs.msSutunTarih)->text()).arg(tblMaas->item(i,dgs.msSutunCalisan)->text()).arg(tblMaas->item(i,dgs.msSutunMaas)->text()).arg(tblMaas->item(i,dgs.msSutunAy)->text()).arg(tblMaas->item(i,dgs.msSutunTur)->text()).arg(tblMaas->item(i,dgs.msSutunHesap)->text()));
            tblMaas->item(i,dgs.msSutunKayit)->setText(query.lastInsertId().toString());
        }
    }
    ////////////////////////
    //silinen kayıtlar
    for(int i=0;i<listSilinenMaas.count();i++)
    {
        query.exec(QString("delete from maas where m_id='%1'").arg(listSilinenMaas.at(i)));
    }
    //////////////////////
    //değiştirilen kayıtlar
    for(int i=0;i<tblMaas->rowCount();i++)
    {
        if(tblMaas->item(i,dgs.msSutunDegisim)->text()=="1")
        {
            query.exec(QString("update maas set m_tarih='%1', m_calisan='%2', m_maas='%3', m_ay='%4', m_tur='%5', m_hesap='%7' where m_id='%6'").arg(tblMaas->item(i,dgs.msSutunTarih)->text()).arg(tblMaas->item(i,dgs.msSutunCalisan)->text()).arg(tblMaas->item(i,dgs.msSutunMaas)->text()).arg(tblMaas->item(i,dgs.msSutunAy)->text()).arg(tblMaas->item(i,dgs.msSutunTur)->text()).arg(tblMaas->item(i,dgs.msSutunKayit)->text()).arg(tblMaas->item(i,dgs.msSutunHesap)->text()));
            tblMaas->item(i,dgs.msSutunDegisim)->setText("0");
        }
    }
    /////////////////////
}

void smaas::maasSil2(double &ToplamTutarMaas, QStringList &listSilinenMaas, bool &kaydetVar, QLabel *lblMaas, QTableWidget* tblMaas,QObject* obj)
{
    QPushButton *btn = qobject_cast<QPushButton *>(obj);

    //silinecek satır bulunuyor
    int silinecekSatir=-1;
    for(int i=0;i<tblMaas->rowCount();i++)
    {
        QPushButton *btnSil=qobject_cast<QPushButton *>(tblMaas->cellWidget(i,dgs.msSutunSil));
        if(btn==btnSil)
        {
            silinecekSatir=i;
            break;
        }
    }
    /////////////////////////////

    /*
      QList<QPushButton *> allPButtons = tblMaas->findChildren<QPushButton *>();
    int silinecekSatir=-1;
    for(int i=0;i<allPButtons.count();i++)
    {
        if(allPButtons.at(i)==btn)
        {
            silinecekSatir=i/2;
            break;
        }
    }*/

    //if(kilitAcik==true)//kilidi açık satırı silmeden önce kilidini kapatıyor
    if(tblMaas->item(silinecekSatir,dgs.msSutunKilit)->text()=="1")
    {
        QPushButton *btnDegistir=qobject_cast<QPushButton *>(tblMaas->cellWidget(silinecekSatir,dgs.msSutunDegistir));
        btnDegistir->click();
    }

    listSilinenMaas.append(tblMaas->item(silinecekSatir,dgs.msSutunKayit)->text());

    ToplamTutarMaas=ToplamTutarMaas-tblMaas->item(silinecekSatir,dgs.msSutunMaas)->text().toDouble();//silinen Maas tutarını toplamtutar dan çıkarıyor
    tblMaas->removeRow(silinecekSatir);
    lblMaas->setText("Kayıt: "+QString::number(tblMaas->rowCount())+" Tutar: "+QString::number(ToplamTutarMaas));//label i güncelliyor

    kaydetVar=true;
}

void smaas::maasDegistir2(bool &degisiklikIzle, bool &kaydetVar, QTableWidget* tblMaas, QTableWidget* tblHesap, QStringList listeHsp, QStringList listeClsn, QObject* obj)
{
    degisiklikIzle=false;
    QPushButton *btnDegistir=new QPushButton();
    QPushButton *btn = qobject_cast<QPushButton *>(obj);

    int degisecekSatir=-1;
    for(int i=0;i<tblMaas->rowCount();i++)
    {
        btnDegistir=qobject_cast<QPushButton *>(tblMaas->cellWidget(i,dgs.msSutunDegistir));
        if(btn==btnDegistir)
        {
            degisecekSatir=i;
            break;
        }
    }

    if(tblMaas->item(degisecekSatir,dgs.msSutunKilit)->text()=="0")
    {
        btnDegistir->setIcon(QIcon(QDir::currentPath()+"/icons/kilitacik.png"));//değiştir düğmesinin ikonu değişiyor
        for(int i=2;i<tblMaas->columnCount()-5;i++)//tür ve ay sütununa girmesin
        {
            if(i!=dgs.msSutunCalisan)//calisan sutununa girmesin
            {
                QTableWidgetItem *itm = tblMaas->item(degisecekSatir, i);
                itm->setFlags(Qt::ItemIsEditable|Qt::ItemIsSelectable|Qt::ItemIsEnabled);
                itm->setBackgroundColor(QColor(Qt::gray));
            }
        }
        //tür sütununa combobox ekleniyor
        QTableWidgetItem *itmTur = tblMaas->item(degisecekSatir, dgs.msSutunTur);
        QString tur=itmTur->text();
        QComboBox *cmbTur=new QComboBox();
        cmbTur->addItems(form_maasEkle.getListeCbMaasTur());
        cmbTur->setCurrentIndex(cmbTur->findText(tur));
        tblMaas->setCellWidget(degisecekSatir,dgs.msSutunTur,cmbTur);
        /////////////////////////////////
        //ay sutununa combobox ekleniyor
        QTableWidgetItem *itmAy = tblMaas->item(degisecekSatir, dgs.msSutunAy);
        QString ay=itmAy->text();
        QComboBox *cmbAy=new QComboBox();
        cmbAy->addItem("Ocak");
        cmbAy->addItem("Şubat");
        cmbAy->addItem("Mart");
        cmbAy->addItem("Nisan");
        cmbAy->addItem("Mayıs");
        cmbAy->addItem("Haziran");
        cmbAy->addItem("Temmuz");
        cmbAy->addItem("Ağustos");
        cmbAy->addItem("Eylül");
        cmbAy->addItem("Ekim");
        cmbAy->addItem("Kasım");
        cmbAy->addItem("Aralık");
        cmbAy->setCurrentIndex(cmbAy->findText(ay));
        tblMaas->setCellWidget(degisecekSatir,dgs.msSutunAy,cmbAy);
        ////////////////////////////////////
        //calısan sutununa combobox ekleniyor
        QTableWidgetItem *itmCalisan = tblMaas->item(degisecekSatir, dgs.msSutunCalisan);
        QString calisan=itmCalisan->text();
        QComboBox *cmbCalisan=new QComboBox();
        cmbCalisan->addItems(listeClsn);
        cmbCalisan->setCurrentIndex(cmbCalisan->findText(calisan));
        tblMaas->setCellWidget(degisecekSatir,dgs.msSutunCalisan,cmbCalisan);
        ////////////////////////////////
        //hesap sütununa combobox ekleniyor
        QTableWidgetItem *itmHesap = tblMaas->item(degisecekSatir, dgs.msSutunHesap);
        QString hesap=itmHesap->text();
        QComboBox *cmbHesap=new QComboBox();
        cmbHesap->addItems(listeHsp);
        cmbHesap->setCurrentIndex(cmbHesap->findText(hesap));
        tblMaas->setCellWidget(degisecekSatir,dgs.msSutunHesap,cmbHesap);
        /////////////////////////////////
        //maas tutarındaki degisiklige göre hesapın güncel mablagı degişiyor
        double mevcutMaas=tblMaas->item(degisecekSatir,dgs.msSutunMaas)->text().toDouble();
        for(int i=0;i<tblHesap->rowCount();i++)
        {
            if(tblHesap->item(i,dgs.hspSutunIsim)->text()==hesap)
            {
                tblHesap->item(i,dgs.hspSutunGuncelMeblag)->setText(QString::number(tblHesap->item(i,dgs.hspSutunGuncelMeblag)->text().toDouble()+mevcutMaas));
                tblHesap->item(i,dgs.hspSutunDegisim)->setText("1");
                break;
            }
        }
        //////////////////////////////7
        tblMaas->item(degisecekSatir,dgs.msSutunDegisim)->setText("1");
        tblMaas->item(degisecekSatir,dgs.msSutunKilit)->setText("1");//kilit açıldığı için
        kaydetVar=true;
        degisiklikIzle=true;//satırda yapılan değişiklikleri kdvtutarı ve tutarı hesaplayabilmek için izlesin
    }
    else
    {
        btnDegistir->setIcon(QIcon(QDir::currentPath()+"/icons/kilitkapali.png"));

        for(int i=2;i<tblMaas->columnCount()-5;i++)//tür ve ay sütununa girmesin
        {
            if(i!=dgs.msSutunCalisan)//calisan sutununa girmesin
            {
                QTableWidgetItem *itm = tblMaas->item(degisecekSatir, i);
                itm->setFlags(Qt::ItemIsEnabled);
                itm->setBackgroundColor(QColor(Qt::white));
            }
        }
        //tür sütunundaki combobox kaldırılıyor
        QComboBox *cmbTur=qobject_cast<QComboBox *>(tblMaas->cellWidget(degisecekSatir,dgs.msSutunTur));
        QString tur=cmbTur->currentText();
        tblMaas->removeCellWidget(degisecekSatir,dgs.msSutunTur);
        QTableWidgetItem *itmTur=new QTableWidgetItem();
        itmTur->setText(tur);
        tblMaas->setItem(degisecekSatir,dgs.msSutunTur,itmTur);
        /////////////////////////////////////////
        //ay sütunundaki combobox kaldırılıyor
        QComboBox *cmbAy=qobject_cast<QComboBox *>(tblMaas->cellWidget(degisecekSatir,dgs.msSutunAy));
        QString ay=cmbAy->currentText();
        tblMaas->removeCellWidget(degisecekSatir,dgs.msSutunAy);
        QTableWidgetItem *itmAy=new QTableWidgetItem();
        itmAy->setText(ay);
        tblMaas->setItem(degisecekSatir,dgs.msSutunAy,itmAy);
        /////////////////////////////////////////
        //calisan sütunundaki combobox kaldırılıyor
        QComboBox *cmbCalisan=qobject_cast<QComboBox *>(tblMaas->cellWidget(degisecekSatir,dgs.msSutunCalisan));
        QString calisan=cmbCalisan->currentText();
        tblMaas->removeCellWidget(degisecekSatir,dgs.msSutunCalisan);
        QTableWidgetItem *itmCalisan=new QTableWidgetItem();
        itmCalisan->setText(calisan);
        tblMaas->setItem(degisecekSatir,dgs.msSutunCalisan,itmCalisan);
        /////////////////////////////////////////
        //hesap sütunundaki combobox kaldırılıyor
        QComboBox *cmbHesap=qobject_cast<QComboBox *>(tblMaas->cellWidget(degisecekSatir,dgs.msSutunHesap));
        QString hesap=cmbHesap->currentText();
        tblMaas->removeCellWidget(degisecekSatir,dgs.msSutunHesap);
        QTableWidgetItem *itmHesap=new QTableWidgetItem();
        itmHesap->setText(hesap);
        tblMaas->setItem(degisecekSatir,dgs.msSutunHesap,itmHesap);
        /////////////////////////////////////////
        //maas tutarındaki degisiklige göre hesapın güncel mablagı degişiyor
        double yeniMaas=tblMaas->item(degisecekSatir,dgs.msSutunMaas)->text().toDouble();
        for(int i=0;i<tblHesap->rowCount();i++)
        {
            if(tblHesap->item(i,dgs.hspSutunIsim)->text()==hesap)
            {
                tblHesap->item(i,dgs.hspSutunGuncelMeblag)->setText(QString::number(tblHesap->item(i,dgs.hspSutunGuncelMeblag)->text().toDouble()-yeniMaas));
                tblHesap->item(i,dgs.hspSutunDegisim)->setText("1");
                break;
            }
        }
        ////////////////////////////////////////
        tblMaas->item(degisecekSatir,dgs.msSutunKilit)->setText("0");//kilit kapatıldığı için
    }
}

void smaas::ilkYukleme2(double &ToplamTutarMaas, QTableWidget* tblMaas, QWidget* tabMaas, QWidget* &tbMaas, QTabWidget* tabWidget)
{
    tblMaas->setRowCount(0);
    tblMaas->setColumnCount(11);
    QStringList baslik=(QStringList()<<""<<""<<"Tarih"<<"Çalışan"<<"Maas"<<"Ay"<<"Tür"<<"Hesap"<<"Kayıt"<<"Degisim"<<"Kilit");
    tblMaas->setHorizontalHeaderLabels(baslik);
    tblMaas->horizontalHeader()->setResizeMode(QHeaderView::Stretch);
    tblMaas->horizontalHeader()->setResizeMode(dgs.msSutunSil,QHeaderView::Custom);
    tblMaas->horizontalHeader()->resizeSection(dgs.msSutunSil, 32);
    tblMaas->horizontalHeader()->setResizeMode(dgs.msSutunDegistir,QHeaderView::Custom);
    tblMaas->horizontalHeader()->resizeSection(dgs.msSutunDegistir, 32);
    tblMaas->horizontalHeader()->setResizeMode(dgs.msSutunTarih,QHeaderView::Custom);
    tblMaas->horizontalHeader()->resizeSection(dgs.msSutunTarih, 80);

    tblMaas->hideColumn(dgs.msSutunKayit);
    tblMaas->hideColumn(dgs.msSutunDegisim);
    tblMaas->hideColumn(dgs.msSutunKilit);

    ToplamTutarMaas=0;

    tbMaas=qobject_cast<QWidget *>(tabMaas);//tabcek qwidget'a dönüştürülüyor
    tabWidget->removeTab(tabWidget->indexOf(tbMaas));//tabcek kapatılıyor
}
