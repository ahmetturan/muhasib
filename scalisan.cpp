#include "scalisan.h"

scalisan::scalisan()
{}

void scalisan::calisanKaydet2(QStringList &listSilinenCalisan, QTableWidget* tblCalisan)
{
    QSqlQuery query;
    //yeni eklenen kayıtlar
    for(int i=0;i<tblCalisan->rowCount();i++)
    {
        if(tblCalisan->item(i,dgs.clsSutunKayit)->text()=="0")
        {
            query.exec(QString("insert into calisan(cl_isim, cl_konum, cl_isegiris, cl_maas, cl_aciklama) values ('%1', '%2', '%3', '%4', '%5')").arg(tblCalisan->item(i,dgs.clsSutunIsim)->text()).arg(tblCalisan->item(i,dgs.clsSutunKonum)->text()).arg(tblCalisan->item(i,dgs.clsSutunIseGiris)->text()).arg(tblCalisan->item(i,dgs.clsSutunMaas)->text()).arg(tblCalisan->item(i,dgs.clsSutunAciklama)->text()));
            tblCalisan->item(i,dgs.clsSutunKayit)->setText(query.lastInsertId().toString());
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
        if(tblCalisan->item(i,dgs.clsSutunDegisim)->text()=="1")
        {
            query.exec(QString("update calisan set cl_isim='%1', cl_konum='%2', cl_isegiris='%3', cl_maas='%4', cl_aciklama='%5' where cl_id='%6'").arg(tblCalisan->item(i,dgs.clsSutunIsim)->text()).arg(tblCalisan->item(i,dgs.clsSutunKonum)->text()).arg(tblCalisan->item(i,dgs.clsSutunIseGiris)->text()).arg(tblCalisan->item(i,dgs.clsSutunMaas)->text()).arg(tblCalisan->item(i,dgs.clsSutunAciklama)->text()).arg(tblCalisan->item(i,dgs.clsSutunKayit)->text()));
            tblCalisan->item(i,dgs.clsSutunDegisim)->setText("0");
        }
    }
    /////////////////////
}

void scalisan::calisanSil2(double &ToplamTutarCalisan, QStringList &listSilinenCalisan, bool &kaydetVar, QLabel *lblCalisan, QTableWidget* tblCalisan, QObject *obj)
{
    QPushButton *btn = qobject_cast<QPushButton *>(obj);
    QList<QPushButton *> allPButtons = tblCalisan->findChildren<QPushButton *>();

    /*
    int silinecekSatir=-1;
    for(int i=0;i<allPButtons.count();i++)
    {
        if(allPButtons.at(i)==btn)
        {
            silinecekSatir=i/2;
            break;
        }
    }
    */
    //silinecek satir bulunuyor
    int silinecekSatir=-1;
    for(int i=0;i<tblCalisan->rowCount();i++)
    {
        QPushButton *btnSil=qobject_cast<QPushButton *>(tblCalisan->cellWidget(i,dgs.clsSutunSil));
        if(btn==btnSil)
        {
            silinecekSatir=i;
            break;
        }
    }
    //////////////////////////////
    if(tblCalisan->item(silinecekSatir,dgs.clsSutunKilit)->text()=="1")
    {
        QPushButton *btnDegistir=qobject_cast<QPushButton *>(tblCalisan->cellWidget(silinecekSatir,dgs.clsSutunDegistir));
        btnDegistir->click();
    }
    listSilinenCalisan.append(tblCalisan->item(silinecekSatir,dgs.clsSutunKayit)->text());

    ToplamTutarCalisan=ToplamTutarCalisan-tblCalisan->item(silinecekSatir,dgs.clsSutunMaas)->text().toDouble();//silinen maas tutarını toplamtutar dan çıkarıyor
    tblCalisan->removeRow(silinecekSatir);
    lblCalisan->setText("Kayıt: "+QString::number(tblCalisan->rowCount())+" Tutar: "+QString::number(ToplamTutarCalisan));//label i güncelliyor

    kaydetVar=true;
}

void scalisan::calisanDegistir2(bool& degisiklikIzle, bool &kaydetVar, QTableWidget *tblCalisan, QTabWidget* tabWidget, int &kilidiAcikSatirSayisi, QObject *obj)
{
    degisiklikIzle=false;
    QPushButton *btnDegistir=new QPushButton();
    QPushButton *btn = qobject_cast<QPushButton *>(obj);
    /*
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
    */
    //degisecek satiri bulunuyor
    int degisecekSatir=-1;
    for(int i=0;i<tblCalisan->rowCount();i++)
    {
        btnDegistir=qobject_cast<QPushButton *>(tblCalisan->cellWidget(i,dgs.clsSutunDegistir));
        if(btn==btnDegistir)
        {
            degisecekSatir=i;
            break;
        }
    }
    //////////////////7
    if(tblCalisan->item(degisecekSatir,dgs.clsSutunKilit)->text()=="0")
    {
        kilidiAcikSatirSayisi=kilidiAcikSatirSayisi+1;
        //faturalar sekmesi hariç diğer sekmekel donduruluyor
        for(int i=0;i<tabWidget->count();i++)
        {
            //if(tabWidget->tabText(i)!="Faturalar")
            if(tabWidget->tabText(i)!=dgs.sekmeCalisanListele)
            {
                tabWidget->setTabEnabled(i,false);
                tabWidget->setTabsClosable(false);
            }
        }
        //////////////////////////////////////////////////////
        btnDegistir->setIcon(QIcon(QDir::currentPath()+"/icons/kilitacik.png"));//değiştir düğmesinin ikonu değişiyor
        for(int i=2;i<tblCalisan->columnCount()-3;i++)//sondaki 3 sutuna girmesi
        {
            if(i!=dgs.clsSutunKonum)//calisan sutununa girmesin
            {
                QTableWidgetItem *itm = tblCalisan->item(degisecekSatir, i);
                itm->setFlags(Qt::ItemIsEditable|Qt::ItemIsSelectable|Qt::ItemIsEnabled);
                itm->setBackgroundColor(QColor(Qt::gray));
            }
        }
        //konum sütununa combobox ekleniyor
        QTableWidgetItem *itmKonum = tblCalisan->item(degisecekSatir, dgs.clsSutunKonum);
        QString Konum=itmKonum->text();
        QComboBox *cmbKonum=new QComboBox();
        //cmbKonum->addItems(form_calisanEkle.getListeCbCalisanTur());
        cmbKonum->addItems(form_calisanEkle.getListeCalisanKonum());
        cmbKonum->setCurrentIndex(cmbKonum->findText(Konum));
        tblCalisan->setCellWidget(degisecekSatir,dgs.clsSutunKonum,cmbKonum);
        /////////////////////////////////
        //tarih sutununa dateedit ekleniyor
        QDate dt=QDate::fromString(tblCalisan->item(degisecekSatir,dgs.clsSutunIseGiris)->text(),"yyyy-MM-dd");
        QDateEdit *date=new QDateEdit(dt);
        date->setDisplayFormat("yyyy-MM-dd");
        tblCalisan->setCellWidget(degisecekSatir,dgs.clsSutunIseGiris,date);
        ///////////////////////////////////
        tblCalisan->item(degisecekSatir,dgs.clsSutunDegisim)->setText("1");
        tblCalisan->item(degisecekSatir,dgs.clsSutunKilit)->setText("1");//kilit açıldığı için
        kaydetVar=true;
        degisiklikIzle=true;//satırda yapılan değişiklikleri kdvtutarı ve tutarı hesaplayabilmek için izlesin
    }
    else
    {
        kilidiAcikSatirSayisi=kilidiAcikSatirSayisi-1;
        //dondurulmuş sekmeler açılıyor
        if(kilidiAcikSatirSayisi==0)
        {
            for(int i=0;i<tabWidget->count();i++)
            {
                //if(tabWidget->tabText(i)!="Faturalar")
                if(tabWidget->tabText(i)!=dgs.sekmeCalisanListele)
                {
                    tabWidget->setTabEnabled(i,true);
                    tabWidget->setTabsClosable(true);
                }
            }
        }
        //////////////////////////////////////////////////////77
        btnDegistir->setIcon(QIcon(QDir::currentPath()+"/icons/kilitkapali.png"));

        for(int i=2;i<tblCalisan->columnCount()-3;i++)//sondaki 3 sutuna girmesin
        {
            if(i!=dgs.clsSutunKonum)//konum sutununa girmesin
            {
                QTableWidgetItem *itm = tblCalisan->item(degisecekSatir, i);
                itm->setFlags(Qt::ItemIsEnabled);
                itm->setBackgroundColor(QColor(Qt::white));
            }
        }
        //konum sütunundaki combobox kaldırılıyor
        QComboBox *cmbKonum=qobject_cast<QComboBox *>(tblCalisan->cellWidget(degisecekSatir,dgs.clsSutunKonum));
        QString Konum=cmbKonum->currentText();
        tblCalisan->removeCellWidget(degisecekSatir,dgs.clsSutunKonum);
        QTableWidgetItem *itmKonum=new QTableWidgetItem();
        itmKonum->setText(Konum);
        tblCalisan->setItem(degisecekSatir,dgs.clsSutunKonum,itmKonum);
        /////////////////////////////////////////
        //tarih sutunundaki datedit kaldırılıyor
        QDateEdit *dateedit=qobject_cast<QDateEdit *>(tblCalisan->cellWidget(degisecekSatir,dgs.clsSutunIseGiris));
        QDate date=dateedit->date();
        QString tarih=date.toString("yyyy-MM-dd");
        tblCalisan->removeCellWidget(degisecekSatir,dgs.clsSutunIseGiris);
        QTableWidgetItem *itmTarih=new QTableWidgetItem();
        itmTarih->setText(tarih);
        tblCalisan->setItem(degisecekSatir,dgs.clsSutunIseGiris,itmTarih);
        ///////////////////////////////////////

        tblCalisan->item(degisecekSatir,dgs.clsSutunKilit)->setText("0");//kilit kapatıldığı için
    }
}

void scalisan::ilkYukleme2(double &ToplamTutarCalisan, QTableWidget* tblCalisan, QWidget* tabCalisan, QWidget* &tbCalisan, QTabWidget* tabWidget)
{
    tblCalisan->setRowCount(0);
    tblCalisan->setColumnCount(10);
    QStringList baslik=(QStringList()<<""<<""<<"İsim"<<"Konum"<<"İşe Giriş"<<"Maaş"<<"Açıklama"<<"Kayıt"<<"Degisim"<<"Kilit");
    tblCalisan->setHorizontalHeaderLabels(baslik);
    tblCalisan->horizontalHeader()->setResizeMode(QHeaderView::Stretch);
    tblCalisan->horizontalHeader()->setResizeMode(dgs.clsSutunSil,QHeaderView::Custom);
    tblCalisan->horizontalHeader()->resizeSection(dgs.clsSutunSil, 32);
    tblCalisan->horizontalHeader()->setResizeMode(dgs.clsSutunDegistir,QHeaderView::Custom);
    tblCalisan->horizontalHeader()->resizeSection(dgs.clsSutunDegistir, 32);
    tblCalisan->horizontalHeader()->setResizeMode(dgs.clsSutunIseGiris,QHeaderView::Custom);
    tblCalisan->horizontalHeader()->resizeSection(dgs.clsSutunIseGiris, 100);

    tblCalisan->hideColumn(dgs.clsSutunKayit);
    tblCalisan->hideColumn(dgs.clsSutunDegisim);
    tblCalisan->hideColumn(dgs.clsSutunKilit);

    ToplamTutarCalisan=0;

    tbCalisan=qobject_cast<QWidget *>(tabCalisan);//tabcek qwidget'a dönüştürülüyor
    tabWidget->removeTab(tabWidget->indexOf(tbCalisan));//tabcek kapatılıyor
}
