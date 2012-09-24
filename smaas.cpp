#include "smaas.h"

smaas::smaas()
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
    clsSutunIsim=2;
}

void smaas::maasKaydet2(QStringList &listSilinenMaas,QTableWidget* tblMaas)
{
    QSqlQuery query;
    //yeni eklenen kayıtlar
    for(int i=0;i<tblMaas->rowCount();i++)
    {
        if(tblMaas->item(i,msSutunKayit)->text()=="0")
        {
            query.exec(QString("insert into maas(m_tarih, m_calisan, m_maas, m_ay, m_tur, m_hesap) values ('%1', '%2', '%3', '%4', '%5', '%6')").arg(tblMaas->item(i,msSutunTarih)->text()).arg(tblMaas->item(i,msSutunCalisan)->text()).arg(tblMaas->item(i,msSutunMaas)->text()).arg(tblMaas->item(i,msSutunAy)->text()).arg(tblMaas->item(i,msSutunTur)->text()).arg(tblMaas->item(i,msSutunHesap)->text()));
            tblMaas->item(i,msSutunKayit)->setText(query.lastInsertId().toString());
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
        if(tblMaas->item(i,msSutunDegisim)->text()=="1")
        {
            query.exec(QString("update maas set m_tarih='%1', m_calisan='%2', m_maas='%3', m_ay='%4', m_tur='%5', m_hesap='%7' where m_id='%6'").arg(tblMaas->item(i,msSutunTarih)->text()).arg(tblMaas->item(i,msSutunCalisan)->text()).arg(tblMaas->item(i,msSutunMaas)->text()).arg(tblMaas->item(i,msSutunAy)->text()).arg(tblMaas->item(i,msSutunTur)->text()).arg(tblMaas->item(i,msSutunKayit)->text()).arg(tblMaas->item(i,msSutunHesap)->text()));
            tblMaas->item(i,msSutunDegisim)->setText("0");
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
        QPushButton *btnSil=qobject_cast<QPushButton *>(tblMaas->cellWidget(i,msSutunSil));
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
    if(tblMaas->item(silinecekSatir,msSutunKilit)->text()=="1")
    {
        QPushButton *btnDegistir=qobject_cast<QPushButton *>(tblMaas->cellWidget(silinecekSatir,msSutunDegistir));
        btnDegistir->click();
    }

    listSilinenMaas.append(tblMaas->item(silinecekSatir,msSutunKayit)->text());

    ToplamTutarMaas=ToplamTutarMaas-tblMaas->item(silinecekSatir,msSutunMaas)->text().toDouble();//silinen Maas tutarını toplamtutar dan çıkarıyor
    tblMaas->removeRow(silinecekSatir);
    lblMaas->setText("Kayıt: "+QString::number(tblMaas->rowCount())+" Tutar: "+QString::number(ToplamTutarMaas));//label i güncelliyor

    kaydetVar=true;
}

void smaas::maasDegistir2(bool &degisiklikIzle, bool &kaydetVar, QTableWidget* tblMaas, QStringList listeHsp, QStringList listeClsn, QObject* obj)
{
    degisiklikIzle=false;
    QPushButton *btnDegistir=new QPushButton();
    QPushButton *btn = qobject_cast<QPushButton *>(obj);

    int degisecekSatir=-1;
    for(int i=0;i<tblMaas->rowCount();i++)
    {
        //QPushButton *btnD=qobject_cast<QPushButton *>(tblMaas->cellWidget(i,msSutunDegistir));
        btnDegistir=qobject_cast<QPushButton *>(tblMaas->cellWidget(i,msSutunDegistir));
        if(btn==btnDegistir)
        {
            degisecekSatir=i;
            break;
        }
    }

    /*
    QList<QPushButton *> allPButtons = tblMaas->findChildren<QPushButton *>();

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
    */

    if(tblMaas->item(degisecekSatir,msSutunKilit)->text()=="0")
    {
        btnDegistir->setIcon(QIcon(QDir::currentPath()+"/icons/kilitacik.png"));//değiştir düğmesinin ikonu değişiyor
        for(int i=2;i<tblMaas->columnCount()-5;i++)//tür ve ay sütununa girmesin
        {
            if(i!=msSutunCalisan)//calisan sutununa girmesin
            {
                QTableWidgetItem *itm = tblMaas->item(degisecekSatir, i);
                itm->setFlags(Qt::ItemIsEditable|Qt::ItemIsSelectable|Qt::ItemIsEnabled);
                itm->setBackgroundColor(QColor(Qt::gray));
            }
        }
        //tür sütununa combobox ekleniyor
        QTableWidgetItem *itmTur = tblMaas->item(degisecekSatir, msSutunTur);
        QString tur=itmTur->text();
        QComboBox *cmbTur=new QComboBox();
        cmbTur->addItems(form_maasEkle.getListeCbMaasTur());
        cmbTur->setCurrentIndex(cmbTur->findText(tur));
        tblMaas->setCellWidget(degisecekSatir,msSutunTur,cmbTur);
        /////////////////////////////////
        //ay sutununa combobox ekleniyor
        QTableWidgetItem *itmAy = tblMaas->item(degisecekSatir, msSutunAy);
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
        tblMaas->setCellWidget(degisecekSatir,msSutunAy,cmbAy);
        ////////////////////////////////////
        //calısan sutununa combobox ekleniyor
        QTableWidgetItem *itmCalisan = tblMaas->item(degisecekSatir, msSutunCalisan);
        QString calisan=itmCalisan->text();
        QComboBox *cmbCalisan=new QComboBox();
        cmbCalisan->addItems(listeClsn);
        cmbCalisan->setCurrentIndex(cmbCalisan->findText(calisan));
        tblMaas->setCellWidget(degisecekSatir,msSutunCalisan,cmbCalisan);
        /*
        QComboBox *cmbCalisan=new QComboBox();
        for(int i=0;i<tblCalisan->rowCount();i++)
        {
            cmbCalisan->addItem(tblCalisan->item(i,clsSutunIsim)->text());
        }
        tblMaas->setCellWidget(0,msSutunCalisan,cmbCalisan);
        */
        ////////////////////////////////
        //hesap sütununa combobox ekleniyor
        QTableWidgetItem *itmHesap = tblMaas->item(degisecekSatir, msSutunHesap);
        QString hesap=itmHesap->text();
        QComboBox *cmbHesap=new QComboBox();
        cmbHesap->addItems(listeHsp);
        cmbHesap->setCurrentIndex(cmbHesap->findText(hesap));
        tblMaas->setCellWidget(degisecekSatir,msSutunHesap,cmbHesap);
        /////////////////////////////////

        tblMaas->item(degisecekSatir,msSutunDegisim)->setText("1");
        tblMaas->item(degisecekSatir,msSutunKilit)->setText("1");//kilit açıldığı için
        kaydetVar=true;
        degisiklikIzle=true;//satırda yapılan değişiklikleri kdvtutarı ve tutarı hesaplayabilmek için izlesin
    }
    else
    {
        btnDegistir->setIcon(QIcon(QDir::currentPath()+"/icons/kilitkapali.png"));

        for(int i=2;i<tblMaas->columnCount()-5;i++)//tür ve ay sütununa girmesin
        {
            if(i!=msSutunCalisan)//calisan sutununa girmesin
            {
                QTableWidgetItem *itm = tblMaas->item(degisecekSatir, i);
                itm->setFlags(Qt::ItemIsEnabled);
                itm->setBackgroundColor(QColor(Qt::white));
            }
        }
        //tür sütunundaki combobox kaldırılıyor
        QComboBox *cmbTur=qobject_cast<QComboBox *>(tblMaas->cellWidget(degisecekSatir,msSutunTur));
        QString tur=cmbTur->currentText();
        tblMaas->removeCellWidget(degisecekSatir,msSutunTur);
        QTableWidgetItem *itmTur=new QTableWidgetItem();
        itmTur->setText(tur);
        tblMaas->setItem(degisecekSatir,msSutunTur,itmTur);
        /////////////////////////////////////////
        //ay sütunundaki combobox kaldırılıyor
        QComboBox *cmbAy=qobject_cast<QComboBox *>(tblMaas->cellWidget(degisecekSatir,msSutunAy));
        QString ay=cmbAy->currentText();
        tblMaas->removeCellWidget(degisecekSatir,msSutunAy);
        QTableWidgetItem *itmAy=new QTableWidgetItem();
        itmAy->setText(ay);
        tblMaas->setItem(degisecekSatir,msSutunAy,itmAy);
        /////////////////////////////////////////
        //calisan sütunundaki combobox kaldırılıyor
        QComboBox *cmbCalisan=qobject_cast<QComboBox *>(tblMaas->cellWidget(degisecekSatir,msSutunCalisan));
        QString calisan=cmbCalisan->currentText();
        tblMaas->removeCellWidget(degisecekSatir,msSutunCalisan);
        QTableWidgetItem *itmCalisan=new QTableWidgetItem();
        itmCalisan->setText(calisan);
        tblMaas->setItem(degisecekSatir,msSutunCalisan,itmCalisan);
        /////////////////////////////////////////
        //hesap sütunundaki combobox kaldırılıyor
        QComboBox *cmbHesap=qobject_cast<QComboBox *>(tblMaas->cellWidget(degisecekSatir,msSutunHesap));
        QString hesap=cmbHesap->currentText();
        tblMaas->removeCellWidget(degisecekSatir,msSutunHesap);
        QTableWidgetItem *itmHesap=new QTableWidgetItem();
        itmHesap->setText(hesap);
        tblMaas->setItem(degisecekSatir,msSutunHesap,itmHesap);
        /////////////////////////////////////////
        tblMaas->item(degisecekSatir,msSutunKilit)->setText("0");//kilit kapatıldığı için
    }
}

void smaas::ilkYukleme2(double &ToplamTutarMaas, QTableWidget* tblMaas, QWidget* tabMaas, QWidget* &tbMaas, QTabWidget* tabWidget)
{
    tblMaas->setRowCount(0);
    tblMaas->setColumnCount(11);
    QStringList baslik=(QStringList()<<""<<""<<"Tarih"<<"Çalışan"<<"Maas"<<"Ay"<<"Tür"<<"Hesap"<<"Kayıt"<<"Degisim"<<"Kilit");
    tblMaas->setHorizontalHeaderLabels(baslik);
    tblMaas->horizontalHeader()->setResizeMode(QHeaderView::Stretch);
    tblMaas->horizontalHeader()->setResizeMode(msSutunSil,QHeaderView::Custom);
    tblMaas->horizontalHeader()->resizeSection(msSutunSil, 32);
    tblMaas->horizontalHeader()->setResizeMode(msSutunDegistir,QHeaderView::Custom);
    tblMaas->horizontalHeader()->resizeSection(msSutunDegistir, 32);

    tblMaas->hideColumn(msSutunKayit);
    tblMaas->hideColumn(msSutunDegisim);
    tblMaas->hideColumn(msSutunKilit);

    ToplamTutarMaas=0;

    tbMaas=qobject_cast<QWidget *>(tabMaas);//tabcek qwidget'a dönüştürülüyor
    tabWidget->removeTab(tabWidget->indexOf(tbMaas));//tabcek kapatılıyor
}
