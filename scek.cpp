#include "scek.h"

scek::scek()
{}

void scek::cekSil2(double &ToplamTutarCek, QStringList &listSilinenCek, bool &kaydetVar, QLabel *lblCek, QTableWidget* tblCek, QObject *obj)
{
    QPushButton *btn = qobject_cast<QPushButton *>(obj);
    /*
    QList<QPushButton *> allPButtons = tblCek->findChildren<QPushButton *>();
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
    for(int i=0;i<tblCek->rowCount();i++)
    {
        QPushButton *btnSil=qobject_cast<QPushButton *>(tblCek->cellWidget(i,dgs.ckSutunSil));
        if(btn==btnSil)
        {
            silinecekSatir=i;
            break;
        }
    }
    //////////////////////////////
    if(tblCek->item(silinecekSatir,dgs.ckSutunKilit)->text()=="1")
    {
        QPushButton *btnDegistir=qobject_cast<QPushButton *>(tblCek->cellWidget(silinecekSatir,dgs.ckSutunDegistir));
        btnDegistir->click();
    }

    listSilinenCek.append(tblCek->item(silinecekSatir,dgs.ckSutunKayit)->text());

    ToplamTutarCek=ToplamTutarCek-tblCek->item(silinecekSatir,dgs.ckSutunTutar)->text().toDouble();//silinen Cek tutarını toplamtutar dan çıkarıyor
    tblCek->removeRow(silinecekSatir);
    lblCek->setText("Kayıt: "+QString::number(tblCek->rowCount())+" Tutar: "+QString::number(ToplamTutarCek));//label i güncelliyor

    kaydetVar=true;
}

void scek::cekDegistir2(bool &degisiklikIzle, bool& kaydetVar,QTableWidget* tblCek, QTabWidget* tabWidget, int &kilidiAcikSatirSayisi, QObject *obj)
{
    degisiklikIzle=false;
    QPushButton *btnDegistir=new QPushButton();
    QPushButton *btn = qobject_cast<QPushButton *>(obj);
    /*
    QList<QPushButton *> allPButtons = tblCek->findChildren<QPushButton *>();
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
    for(int i=0;i<tblCek->rowCount();i++)
    {
        btnDegistir=qobject_cast<QPushButton *>(tblCek->cellWidget(i,dgs.ckSutunDegistir));
        if(btn==btnDegistir)
        {
            degisecekSatir=i;
            break;
        }
    }
    //////////////////7
    if(tblCek->item(degisecekSatir,dgs.ckSutunKilit)->text()=="0")
    {
        kilidiAcikSatirSayisi=kilidiAcikSatirSayisi+1;
        //faturalar sekmesi hariç diğer sekmekel donduruluyor
        for(int i=0;i<tabWidget->count();i++)
        {
            //if(tabWidget->tabText(i)!="Faturalar")
            if(tabWidget->tabText(i)!=dgs.sekmeCekListele)
            {
                tabWidget->setTabEnabled(i,false);
                tabWidget->setTabsClosable(false);
            }
        }
        //////////////////////////////////////////////////////
        btnDegistir->setIcon(QIcon(QDir::currentPath()+"/icons/kilitacik.png"));//değiştir düğmesinin ikonu değişiyor
        for(int i=2;i<tblCek->columnCount()-4;i++)//tür sütununa girmesin
        {
            QTableWidgetItem *itm = tblCek->item(degisecekSatir, i);
            itm->setFlags(Qt::ItemIsEditable|Qt::ItemIsSelectable|Qt::ItemIsEnabled);
            itm->setBackgroundColor(QColor(Qt::gray));
        }
        //tür sütununa combobox ekleniyor
        QTableWidgetItem *itm = tblCek->item(degisecekSatir, dgs.ckSutunTur);
        QString tur=itm->text();
        QComboBox *cmb=new QComboBox();
        cmb->addItems(form_cekEkle.getListeCbCekTur());
        cmb->setCurrentIndex(cmb->findText(tur));
        tblCek->setCellWidget(degisecekSatir,dgs.ckSutunTur,cmb);
        /////////////////////////////////
        //tarih sutununa dateedit ekleniyor
        QDate dt=QDate::fromString(tblCek->item(degisecekSatir,dgs.ckSutunTarih)->text(),"yyyy-MM-dd");
        QDateEdit *date=new QDateEdit(dt);
        date->setDisplayFormat("yyyy-MM-dd");
        tblCek->setCellWidget(degisecekSatir,dgs.ckSutunTarih,date);
        ///////////////////////////////////
        tblCek->item(degisecekSatir,dgs.ckSutunDegisim)->setText("1");
        tblCek->item(degisecekSatir,dgs.ckSutunKilit)->setText("1");//kilit açıldığı için
        kaydetVar=true;
        degisiklikIzle=true;
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
                if(tabWidget->tabText(i)!=dgs.sekmeCekListele)
                {
                    tabWidget->setTabEnabled(i,true);
                    tabWidget->setTabsClosable(true);
                }
            }
        }
        //////////////////////////////////////////////////////77
        btnDegistir->setIcon(QIcon(QDir::currentPath()+"/icons/kilitkapali.png"));

        for(int i=2;i<tblCek->columnCount()-4;i++)//tür sütununa girmesin
        {
            QTableWidgetItem *itm = tblCek->item(degisecekSatir, i);
            itm->setFlags(Qt::ItemIsEnabled);
            itm->setBackgroundColor(QColor(Qt::white));
        }
        //tür sütunundaki combobox kaldırılıyor
        QComboBox *cmb=qobject_cast<QComboBox *>(tblCek->cellWidget(degisecekSatir,dgs.ckSutunTur));
        QString CekTuru=cmb->currentText();
        tblCek->removeCellWidget(degisecekSatir,dgs.ckSutunTur);
        QTableWidgetItem *itm=new QTableWidgetItem();
        itm->setText(CekTuru);
        tblCek->setItem(degisecekSatir,dgs.ckSutunTur,itm);
        /////////////////////////////////////////
        //tarih sutunundaki datedit kaldırılıyor
        QDateEdit *dateedit=qobject_cast<QDateEdit *>(tblCek->cellWidget(degisecekSatir,dgs.ckSutunTarih));
        QDate date=dateedit->date();
        QString tarih=date.toString("yyyy-MM-dd");
        tblCek->removeCellWidget(degisecekSatir,dgs.ckSutunTarih);
        QTableWidgetItem *itmTarih=new QTableWidgetItem();
        itmTarih->setText(tarih);
        tblCek->setItem(degisecekSatir,dgs.ckSutunTarih,itmTarih);
        ///////////////////////////////////////
        tblCek->item(degisecekSatir,dgs.ckSutunKilit)->setText("0");//kilit kapatıldığı için
    }
}

void scek::cekKaydet2(QStringList &listSilinenCek, QTableWidget* tblCek)
{
    QSqlQuery query;
    //yeni eklenen kayıtlar
    for(int i=0;i<tblCek->rowCount();i++)
    {
        if(tblCek->item(i,dgs.ckSutunKayit)->text()=="0")
        {
            query.exec(QString("insert into cek(c_tarih, c_isim, c_banka, c_tutar,c_muhatap, c_cekno, c_aciklama, c_tur) values ('%1', '%2', '%3', '%4', '%5', '%6', '%7', '%8')").arg(tblCek->item(i,dgs.ckSutunTarih)->text()).arg(tblCek->item(i,dgs.ckSutunIsim)->text()).arg(tblCek->item(i,dgs.ckSutunBanka)->text()).arg(tblCek->item(i,dgs.ckSutunTutar)->text()).arg(tblCek->item(i,dgs.ckSutunMuhatap)->text()).arg(tblCek->item(i,dgs.ckSutunCekNo)->text()).arg(tblCek->item(i,dgs.ckSutunAciklama)->text()).arg(tblCek->item(i,dgs.ckSutunTur)->text()));
            tblCek->item(i,dgs.ckSutunKayit)->setText(query.lastInsertId().toString());
        }
    }
    ////////////////////////
    //silinen kayıtlar
    for(int i=0;i<listSilinenCek.count();i++)
    {
        query.exec(QString("delete from cek where c_id='%1'").arg(listSilinenCek.at(i)));
    }

    //////////////////////
    //değiştirilen kayıtlar
    for(int i=0;i<tblCek->rowCount();i++)
    {
        if(tblCek->item(i,dgs.ckSutunDegisim)->text()=="1")
        {
            query.exec(QString("update cek set c_tarih='%1', c_isim='%2', c_banka='%3', c_tutar='%4',c_muhatap='%5',c_cekno='%6', c_aciklama='%7', c_tur='%8' where c_id='%9'").arg(tblCek->item(i,dgs.ckSutunTarih)->text()).arg(tblCek->item(i,dgs.ckSutunIsim)->text()).arg(tblCek->item(i,dgs.ckSutunBanka)->text()).arg(tblCek->item(i,dgs.ckSutunTutar)->text()).arg(tblCek->item(i,dgs.ckSutunMuhatap)->text()).arg(tblCek->item(i,dgs.ckSutunCekNo)->text()).arg(tblCek->item(i,dgs.ckSutunAciklama)->text()).arg(tblCek->item(i,dgs.ckSutunTur)->text()).arg(tblCek->item(i,dgs.ckSutunKayit)->text()));
            tblCek->item(i,dgs.ckSutunDegisim)->setText("0");
        }
    }
    /////////////////////
}

void scek::ilkYukleme2(double &ToplamTutarCek, QTableWidget* tblCek, QTableWidget* tblAlinanCek, QTableWidget* tblVerilenCek, QWidget* tabCek, QWidget* tabCekOzeti, QWidget* &tbCek, QWidget* &tbCekOzeti, QTabWidget* tabWidget)
{
    tblCek->setRowCount(0);
    tblCek->setColumnCount(13);
    QStringList baslik=(QStringList()<<""<<""<<"Tarih"<<"İsim"<<"Banka"<<"Tutar"<<"Muhatap"<<"No"<<"Açıklama"<<"Tür"<<"Kayıt"<<"Degisim"<<"Kilit");
    tblCek->setHorizontalHeaderLabels(baslik);
    tblCek->horizontalHeader()->setResizeMode(QHeaderView::Stretch);
    tblCek->horizontalHeader()->setResizeMode(dgs.ckSutunSil,QHeaderView::Custom);
    tblCek->horizontalHeader()->resizeSection(dgs.ckSutunSil, 32);
    tblCek->horizontalHeader()->setResizeMode(dgs.ckSutunDegistir,QHeaderView::Custom);
    tblCek->horizontalHeader()->resizeSection(dgs.ckSutunDegistir, 32);
    tblCek->horizontalHeader()->setResizeMode(dgs.ckSutunTarih,QHeaderView::Custom);
    tblCek->horizontalHeader()->resizeSection(dgs.ckSutunTarih, 100);

    tblCek->hideColumn(dgs.ckSutunKayit);
    tblCek->hideColumn(dgs.ckSutunDegisim);
    tblCek->hideColumn(dgs.ckSutunKilit);

    tblAlinanCek->setRowCount(0);
    tblAlinanCek->setColumnCount(7);
    baslik=(QStringList()<<"Tarih"<<"İsim"<<"Banka"<<"Tutar"<<"Muhatap"<<"No"<<"Açıklama");
    tblAlinanCek->setHorizontalHeaderLabels(baslik);
    tblAlinanCek->horizontalHeader()->setResizeMode(QHeaderView::Stretch);
    tblAlinanCek->setEditTriggers(QAbstractItemView::NoEditTriggers);

    tblVerilenCek->setRowCount(0);
    tblVerilenCek->setColumnCount(7);
    baslik=(QStringList()<<"Tarih"<<"İsim"<<"Banka"<<"Tutar"<<"Muhatap"<<"No"<<"Açıklama");
    tblVerilenCek->setHorizontalHeaderLabels(baslik);
    tblVerilenCek->horizontalHeader()->setResizeMode(QHeaderView::Stretch);
    tblVerilenCek->setEditTriggers(QAbstractItemView::NoEditTriggers);
    tblVerilenCek->setSelectionMode(QAbstractItemView::NoSelection);

    ToplamTutarCek=0;

    tbCek=qobject_cast<QWidget *>(tabCek);//tabcek qwidget'a dönüştürülüyor
    tabWidget->removeTab(tabWidget->indexOf(tbCek));//tabcek kapatılıyor
    tbCekOzeti=qobject_cast<QWidget *>(tabCekOzeti);//tabfaturözeti qwidget'a dönüştürülüyor
    tabWidget->removeTab(tabWidget->indexOf(tbCekOzeti));//tabfaturaözeti kapatılıyor
}
