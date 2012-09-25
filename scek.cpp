#include "scek.h"

scek::scek()
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
}

void scek::cekSil2(double &ToplamTutarCek, QStringList &listSilinenCek, bool &kaydetVar, QLabel *lblCek, QTableWidget* tblCek, QObject *obj)
{
    QPushButton *btn = qobject_cast<QPushButton *>(obj);
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
    //if(kilitAcik==true)//kilidi açık satırı silmeden önce kilidini kapatıyor
    if(tblCek->item(silinecekSatir,ckSutunKilit)->text()=="1")
    {
        QPushButton *btnDegistir=qobject_cast<QPushButton *>(tblCek->cellWidget(silinecekSatir,ckSutunDegistir));
        btnDegistir->click();
    }

    listSilinenCek.append(tblCek->item(silinecekSatir,ckSutunKayit)->text());

    ToplamTutarCek=ToplamTutarCek-tblCek->item(silinecekSatir,ckSutunTutar)->text().toDouble();//silinen Cek tutarını toplamtutar dan çıkarıyor
    tblCek->removeRow(silinecekSatir);
    lblCek->setText("Kayıt: "+QString::number(tblCek->rowCount())+" Tutar: "+QString::number(ToplamTutarCek));//label i güncelliyor

    kaydetVar=true;
}

void scek::cekDegistir2(bool &degisiklikIzle, bool& kaydetVar,QTableWidget* tblCek, QObject *obj)
{
    degisiklikIzle=false;
    QPushButton *btnDegistir=new QPushButton();
    QPushButton *btn = qobject_cast<QPushButton *>(obj);
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
    if(tblCek->item(degisecekSatir,ckSutunKilit)->text()=="0")
    {
        btnDegistir->setIcon(QIcon(QDir::currentPath()+"/icons/kilitacik.png"));//değiştir düğmesinin ikonu değişiyor
        for(int i=2;i<tblCek->columnCount()-4;i++)//tür sütununa girmesin
        {
            QTableWidgetItem *itm = tblCek->item(degisecekSatir, i);
            itm->setFlags(Qt::ItemIsEditable|Qt::ItemIsSelectable|Qt::ItemIsEnabled);
            itm->setBackgroundColor(QColor(Qt::gray));
        }
        //tür sütununa combobox ekleniyor
        QTableWidgetItem *itm = tblCek->item(degisecekSatir, ckSutunTur);
        QString tur=itm->text();
        QComboBox *cmb=new QComboBox();
        cmb->addItems(form_cekEkle.getListeCbCekTur());
        cmb->setCurrentIndex(cmb->findText(tur));

        tblCek->setCellWidget(degisecekSatir,ckSutunTur,cmb);
        /////////////////////////////////
        //kilitAcik=true;
        tblCek->item(degisecekSatir,ckSutunDegisim)->setText("1");
        tblCek->item(degisecekSatir,ckSutunKilit)->setText("1");//kilit açıldığı için
        kaydetVar=true;
        degisiklikIzle=true;
    }
    else
    {
        btnDegistir->setIcon(QIcon(QDir::currentPath()+"/icons/kilitkapali.png"));

        for(int i=2;i<tblCek->columnCount()-4;i++)//tür sütununa girmesin
        {
            QTableWidgetItem *itm = tblCek->item(degisecekSatir, i);
            itm->setFlags(Qt::ItemIsEnabled);
            itm->setBackgroundColor(QColor(Qt::white));
        }
        //tür sütunundaki combobox kaldırılıyor
        QComboBox *cmb=qobject_cast<QComboBox *>(tblCek->cellWidget(degisecekSatir,ckSutunTur));
        QString CekTuru=cmb->currentText();
        tblCek->removeCellWidget(degisecekSatir,ckSutunTur);
        QTableWidgetItem *itm=new QTableWidgetItem();
        itm->setText(CekTuru);
        tblCek->setItem(degisecekSatir,ckSutunTur,itm);
        /////////////////////////////////////////
        //kilitAcik=false;
        tblCek->item(degisecekSatir,ckSutunKilit)->setText("0");//kilit kapatıldığı için
    }
}

void scek::cekKaydet2(QStringList &listSilinenCek, QTableWidget* tblCek)
{
    QSqlQuery query;
    //yeni eklenen kayıtlar
    for(int i=0;i<tblCek->rowCount();i++)
    {
        if(tblCek->item(i,ckSutunKayit)->text()=="0")
        {
            query.exec(QString("insert into cek(c_tarih, c_isim, c_banka, c_tutar,c_muhatap, c_cekno, c_aciklama, c_tur) values ('%1', '%2', '%3', '%4', '%5', '%6', '%7', '%8')").arg(tblCek->item(i,ckSutunTarih)->text()).arg(tblCek->item(i,ckSutunIsim)->text()).arg(tblCek->item(i,ckSutunBanka)->text()).arg(tblCek->item(i,ckSutunTutar)->text()).arg(tblCek->item(i,ckSutunMuhatap)->text()).arg(tblCek->item(i,ckSutunCekNo)->text()).arg(tblCek->item(i,ckSutunAciklama)->text()).arg(tblCek->item(i,ckSutunTur)->text()));
            tblCek->item(i,ckSutunKayit)->setText(query.lastInsertId().toString());
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
        if(tblCek->item(i,ckSutunDegisim)->text()=="1")
        {
            query.exec(QString("update cek set c_tarih='%1', c_isim='%2', c_banka='%3', c_tutar='%4',c_muhatap='%5',c_cekno='%6', c_aciklama='%7', c_tur='%8' where c_id='%9'").arg(tblCek->item(i,ckSutunTarih)->text()).arg(tblCek->item(i,ckSutunIsim)->text()).arg(tblCek->item(i,ckSutunBanka)->text()).arg(tblCek->item(i,ckSutunTutar)->text()).arg(tblCek->item(i,ckSutunMuhatap)->text()).arg(tblCek->item(i,ckSutunCekNo)->text()).arg(tblCek->item(i,ckSutunAciklama)->text()).arg(tblCek->item(i,ckSutunTur)->text()).arg(tblCek->item(i,ckSutunKayit)->text()));
            tblCek->item(i,ckSutunDegisim)->setText("0");
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
    tblCek->horizontalHeader()->setResizeMode(ckSutunSil,QHeaderView::Custom);
    tblCek->horizontalHeader()->resizeSection(ckSutunSil, 32);
    tblCek->horizontalHeader()->setResizeMode(ckSutunDegistir,QHeaderView::Custom);
    tblCek->horizontalHeader()->resizeSection(ckSutunDegistir, 32);
    tblCek->horizontalHeader()->setResizeMode(ckSutunTarih,QHeaderView::Custom);
    tblCek->horizontalHeader()->resizeSection(ckSutunTarih, 80);

    tblCek->hideColumn(ckSutunKayit);
    tblCek->hideColumn(ckSutunDegisim);
    tblCek->hideColumn(ckSutunKilit);

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
