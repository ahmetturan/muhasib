#include "scalisan.h"

scalisan::scalisan()
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
}

void scalisan::calisanKaydet2(QStringList &listSilinenCalisan, QTableWidget* tblCalisan)
{
    QSqlQuery query;
    //yeni eklenen kayıtlar
    for(int i=0;i<tblCalisan->rowCount();i++)
    {
        if(tblCalisan->item(i,clsSutunKayit)->text()=="0")
        {
            query.exec(QString("insert into calisan(cl_isim, cl_konum, cl_isegiris, cl_maas, cl_aciklama) values ('%1', '%2', '%3', '%4', '%5')").arg(tblCalisan->item(i,clsSutunIsim)->text()).arg(tblCalisan->item(i,clsSutunKonum)->text()).arg(tblCalisan->item(i,clsSutunIseGiris)->text()).arg(tblCalisan->item(i,clsSutunMaas)->text()).arg(tblCalisan->item(i,clsSutunAciklama)->text()));
            tblCalisan->item(i,clsSutunKayit)->setText(query.lastInsertId().toString());
        }
    }
    ////////////////////////
    //silinen kayıtlar
    for(int i=0;i<listSilinenCalisan.count();i++)
    {
        query.exec(QString("delete from calisan where cl_id='%1'").arg(listSilinenCalisan.at(i)));
    }
    //////////////////////
    //değiştirilen kayıtlar
    for(int i=0;i<tblCalisan->rowCount();i++)
    {
        if(tblCalisan->item(i,clsSutunDegisim)->text()=="1")
        {
            query.exec(QString("update calisan set cl_isim='%1', cl_konum='%2', cl_isegiris='%3', cl_maas='%4', cl_aciklama='%5' where cl_id='%6'").arg(tblCalisan->item(i,clsSutunIsim)->text()).arg(tblCalisan->item(i,clsSutunKonum)->text()).arg(tblCalisan->item(i,clsSutunIseGiris)->text()).arg(tblCalisan->item(i,clsSutunMaas)->text()).arg(tblCalisan->item(i,clsSutunAciklama)->text()).arg(tblCalisan->item(i,clsSutunKayit)->text()));
            tblCalisan->item(i,clsSutunDegisim)->setText("0");
        }
    }
    /////////////////////
}

void scalisan::calisanSil2(double &ToplamTutarCalisan, QStringList &listSilinenCalisan, bool &kaydetVar, QLabel *lblCalisan, QTableWidget* tblCalisan, QObject *obj)
{
    QPushButton *btn = qobject_cast<QPushButton *>(obj);
    QList<QPushButton *> allPButtons = tblCalisan->findChildren<QPushButton *>();

    int silinecekSatir=-1;
    for(int i=0;i<allPButtons.count();i++)
    {
        if(allPButtons.at(i)==btn)
        {
            silinecekSatir=i/2;
            break;
        }
    }
    if(tblCalisan->item(silinecekSatir,clsSutunKilit)->text()=="1")
    {
        QPushButton *btnDegistir=qobject_cast<QPushButton *>(tblCalisan->cellWidget(silinecekSatir,clsSutunDegistir));
        btnDegistir->click();
    }
    listSilinenCalisan.append(tblCalisan->item(silinecekSatir,clsSutunKayit)->text());

    ToplamTutarCalisan=ToplamTutarCalisan-tblCalisan->item(silinecekSatir,clsSutunMaas)->text().toDouble();//silinen maas tutarını toplamtutar dan çıkarıyor
    tblCalisan->removeRow(silinecekSatir);
    lblCalisan->setText("Kayıt: "+QString::number(tblCalisan->rowCount())+" Tutar: "+QString::number(ToplamTutarCalisan));//label i güncelliyor

    kaydetVar=true;
}

void scalisan::calisanDegistir2(bool& degisiklikIzle, bool &kaydetVar, QTableWidget *tblCalisan, QObject *obj)
{
    degisiklikIzle=false;
    QPushButton *btnDegistir=new QPushButton();
    QPushButton *btn = qobject_cast<QPushButton *>(obj);
    QList<QPushButton *> allPButtons = tblCalisan->findChildren<QPushButton *>();

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
    if(tblCalisan->item(degisecekSatir,clsSutunKilit)->text()=="0")
    {
        btnDegistir->setIcon(QIcon(QDir::currentPath()+"/icons/kilitacik.png"));//değiştir düğmesinin ikonu değişiyor
        for(int i=2;i<tblCalisan->columnCount()-3;i++)//sondaki 3 sutuna girmesi
        {
            if(i!=clsSutunKonum)//calisan sutununa girmesin
            {
                QTableWidgetItem *itm = tblCalisan->item(degisecekSatir, i);
                itm->setFlags(Qt::ItemIsEditable|Qt::ItemIsSelectable|Qt::ItemIsEnabled);
                itm->setBackgroundColor(QColor(Qt::gray));
            }
        }
        //konum sütununa combobox ekleniyor
        QTableWidgetItem *itmKonum = tblCalisan->item(degisecekSatir, clsSutunKonum);
        QString Konum=itmKonum->text();
        QComboBox *cmbKonum=new QComboBox();
        cmbKonum->addItems(form_calisanEkle.getListeCbCalisanTur());
        cmbKonum->setCurrentIndex(cmbKonum->findText(Konum));
        tblCalisan->setCellWidget(degisecekSatir,clsSutunKonum,cmbKonum);
        /////////////////////////////////
        tblCalisan->item(degisecekSatir,clsSutunDegisim)->setText("1");
        tblCalisan->item(degisecekSatir,clsSutunKilit)->setText("1");//kilit açıldığı için
        kaydetVar=true;
        degisiklikIzle=true;//satırda yapılan değişiklikleri kdvtutarı ve tutarı hesaplayabilmek için izlesin
    }
    else
    {
        btnDegistir->setIcon(QIcon(QDir::currentPath()+"/icons/kilitkapali.png"));

        for(int i=2;i<tblCalisan->columnCount()-3;i++)//sondaki 3 sutuna girmesin
        {
            if(i!=clsSutunKonum)//konum sutununa girmesin
            {
                QTableWidgetItem *itm = tblCalisan->item(degisecekSatir, i);
                itm->setFlags(Qt::ItemIsEnabled);
                itm->setBackgroundColor(QColor(Qt::white));
            }
        }
        //konum sütunundaki combobox kaldırılıyor
        QComboBox *cmbKonum=qobject_cast<QComboBox *>(tblCalisan->cellWidget(degisecekSatir,clsSutunKonum));
        QString Konum=cmbKonum->currentText();
        tblCalisan->removeCellWidget(degisecekSatir,clsSutunKonum);
        QTableWidgetItem *itmKonum=new QTableWidgetItem();
        itmKonum->setText(Konum);
        tblCalisan->setItem(degisecekSatir,clsSutunKonum,itmKonum);
        /////////////////////////////////////////

        tblCalisan->item(degisecekSatir,clsSutunKilit)->setText("0");//kilit kapatıldığı için
    }
}

void scalisan::ilkYukleme2(double &ToplamTutarCalisan, QTableWidget* tblCalisan, QWidget* tabCalisan, QWidget* &tbCalisan, QTabWidget* tabWidget)
{
    tblCalisan->setRowCount(0);
    tblCalisan->setColumnCount(10);
    QStringList baslik=(QStringList()<<""<<""<<"İsim"<<"Konum"<<"İşe Giriş"<<"Maaş"<<"Açıklama"<<"Kayıt"<<"Degisim"<<"Kilit");
    tblCalisan->setHorizontalHeaderLabels(baslik);
    tblCalisan->horizontalHeader()->setResizeMode(QHeaderView::Stretch);
    tblCalisan->horizontalHeader()->setResizeMode(clsSutunSil,QHeaderView::Custom);
    tblCalisan->horizontalHeader()->resizeSection(clsSutunSil, 32);
    tblCalisan->horizontalHeader()->setResizeMode(clsSutunDegistir,QHeaderView::Custom);
    tblCalisan->horizontalHeader()->resizeSection(clsSutunDegistir, 32);

    tblCalisan->hideColumn(clsSutunKayit);
    tblCalisan->hideColumn(clsSutunDegisim);
    tblCalisan->hideColumn(clsSutunKilit);

    ToplamTutarCalisan=0;

    tbCalisan=qobject_cast<QWidget *>(tabCalisan);//tabcek qwidget'a dönüştürülüyor
    tabWidget->removeTab(tabWidget->indexOf(tbCalisan));//tabcek kapatılıyor
}
