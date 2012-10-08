#include "sdigergelir.h"

sdigergelir::sdigergelir()
{}

void sdigergelir::digerGelirKaydet(QStringList &listSilinenDigerGelir, QTableWidget *tblDigerGelir)
{
    QSqlQuery query;
    //yeni eklenen kayıtlar
    for(int i=0;i<tblDigerGelir->rowCount();i++)
    {
        if(tblDigerGelir->item(i,dgs.dglSutunKayit)->text()=="0")
        {
            query.exec(QString("insert into digergelir(dgl_tarih, dgl_isim, dgl_muhatap, dgl_tutar, dgl_aciklama, dgl_hesap) values ('%1', '%2', '%3', '%4', '%5', '%6')").arg(tblDigerGelir->item(i,dgs.dglSutunTarih)->text()).arg(tblDigerGelir->item(i,dgs.dglSutunIsim)->text()).arg(tblDigerGelir->item(i,dgs.dglSutunMuhatap)->text()).arg(tblDigerGelir->item(i,dgs.dglSutunTutar)->text()).arg(tblDigerGelir->item(i,dgs.dglSutunAciklama)->text()).arg(tblDigerGelir->item(i,dgs.dglSutunHesap)->text()));
            tblDigerGelir->item(i,dgs.dglSutunKayit)->setText(query.lastInsertId().toString());
        }
    }
    ////////////////////////
    //silinen kayıtlar
    for(int i=0;i<listSilinenDigerGelir.count();i++)
    {
        query.exec(QString("delete from digergelir where dgl_id='%1'").arg(listSilinenDigerGelir.at(i)));
    }
    //////////////////////
    //değiştirilen kayıtlar
    for(int i=0;i<tblDigerGelir->rowCount();i++)
    {
        if(tblDigerGelir->item(i,dgs.dglSutunDegisim)->text()=="1")
        {
            query.exec(QString("update digergelir set dgl_tarih='%1', dgl_isim='%2', dgl_muhatap='%3', dgl_tutar='%4', dgl_aciklama='%5', dgl_hesap='%6' where dgl_id='%7'").arg(tblDigerGelir->item(i,dgs.dglSutunTarih)->text()).arg(tblDigerGelir->item(i,dgs.dglSutunIsim)->text()).arg(tblDigerGelir->item(i,dgs.dglSutunMuhatap)->text()).arg(tblDigerGelir->item(i,dgs.dglSutunTutar)->text()).arg(tblDigerGelir->item(i,dgs.dglSutunAciklama)->text()).arg(tblDigerGelir->item(i,dgs.dglSutunHesap)->text()).arg(tblDigerGelir->item(i,dgs.dglSutunKayit)->text()));
            tblDigerGelir->item(i,dgs.dglSutunDegisim)->setText("0");
        }
    }
}

void sdigergelir::digerGelirSil(QStringList &listSilinenDigerGelir, bool &kaydetVar, QTableWidget *tblDigerGelir, QObject *obj)
{
    QPushButton *btn = qobject_cast<QPushButton *>(obj);
    //silinecek satir bulunuyor
    int silinecekSatir=-1;
    for(int i=0;i<tblDigerGelir->rowCount();i++)
    {
        QPushButton *btnSil=qobject_cast<QPushButton *>(tblDigerGelir->cellWidget(i,dgs.dglSutunSil));
        if(btn==btnSil)
        {
            silinecekSatir=i;
            break;
        }
    }
    //////////////////////////////

    if(tblDigerGelir->item(silinecekSatir,dgs.dglSutunKilit)->text()=="1")
    {
        QPushButton *btnDegistir=qobject_cast<QPushButton *>(tblDigerGelir->cellWidget(silinecekSatir,dgs.dglSutunDegistir));
        btnDegistir->click();
    }

    listSilinenDigerGelir.append(tblDigerGelir->item(silinecekSatir,dgs.dglSutunKayit)->text());

    //ToplamTutarDigerGelir=ToplamTutarDigerGelir-tblDigerGelir->item(silinecekSatir,dgs.dglSutunTutar)->text().toDouble();//silinen DigerGelir tutarını toplamtutar dan çıkarıyor
    tblDigerGelir->removeRow(silinecekSatir);
    //lblDigerGelir->setText("Kayıt: "+QString::number(tblDigerGelir->rowCount())+" Tutar: "+QString::number(ToplamTutarDigerGelir));//label i güncelliyor

    kaydetVar=true;
}

void sdigergelir::digerGelirDegistir(bool &degisiklikIzle, bool &kaydetVar, QTableWidget* tblDigerGelir, QTableWidget* tblHesap, QTabWidget* tabWidget, QStringList listeHsp, int &kilidiAcikSatirSayisi, QObject* obj)
{
    degisiklikIzle=false;
    QPushButton *btnDegistir=new QPushButton();
    QPushButton *btn = qobject_cast<QPushButton *>(obj);

    //degisecek satiri bulunuyor
    int degisecekSatir=-1;
    for(int i=0;i<tblDigerGelir->rowCount();i++)
    {
        btnDegistir=qobject_cast<QPushButton *>(tblDigerGelir->cellWidget(i,dgs.dglSutunDegistir));
        if(btn==btnDegistir)
        {
            degisecekSatir=i;
            break;
        }
    }
    //////////////////7

    if(tblDigerGelir->item(degisecekSatir,dgs.dglSutunKilit)->text()=="0")//kilit açılıyor
    {
        kilidiAcikSatirSayisi=kilidiAcikSatirSayisi+1;
        //diger gelir sekmesi hariç diğer sekmeler donduruluyor
        for(int i=0;i<tabWidget->count();i++)
        {
            if(tabWidget->tabText(i)!=dgs.sekmeDigerGelirListele)
            {
                tabWidget->setTabEnabled(i,false);
                tabWidget->setTabsClosable(false);
            }
        }
        //////////////////////////////////////////////////////
        btnDegistir->setIcon(QIcon(QDir::currentPath()+"/icons/kilitacik.png"));//değiştir düğmesinin ikonu değişiyor
        for(int i=2;i<tblDigerGelir->columnCount()-3;i++)//hesap sütununa girmesin
        {
            QTableWidgetItem *itm = tblDigerGelir->item(degisecekSatir, i);
            itm->setFlags(Qt::ItemIsEditable|Qt::ItemIsSelectable|Qt::ItemIsEnabled);
            itm->setBackgroundColor(QColor(Qt::gray));
            /*
            if(i!=dgs.dglSutunKdvTutar && i!=dgs.dglSutunTutar && i!=dgs.dglSutunKayitNo)//kdvtutari ve tutari uygulama hesaplayacak
            {
                QTableWidgetItem *itm = tblDigerGelir->item(degisecekSatir, i);
                itm->setFlags(Qt::ItemIsEditable|Qt::ItemIsSelectable|Qt::ItemIsEnabled);
                itm->setBackgroundColor(QColor(Qt::gray));
            }
            */
        }
        //hesap sütununa combobox ekleniyor
        QTableWidgetItem *itmHesap = tblDigerGelir->item(degisecekSatir, dgs.dglSutunHesap);
        QString hesap=itmHesap->text();
        QComboBox *cmbHesap=new QComboBox();
        cmbHesap->addItems(listeHsp);
        cmbHesap->setCurrentIndex(cmbHesap->findText(hesap));
        tblDigerGelir->setCellWidget(degisecekSatir,dgs.dglSutunHesap,cmbHesap);
        /////////////////////////////////
        //tarih sutununa dateedit ekleniyor
        QDate dt=QDate::fromString(tblDigerGelir->item(degisecekSatir,dgs.dglSutunTarih)->text(),"yyyy-MM-dd");
        QDateEdit *date=new QDateEdit(dt);
        date->setDisplayFormat("yyyy-MM-dd");
        tblDigerGelir->setCellWidget(degisecekSatir,dgs.dglSutunTarih,date);
        ///////////////////////////////////
        //DigerGelir hesabı veya tutarı değişirse hesap penceresinde de değişiyor
        double mevcutTutar=tblDigerGelir->item(degisecekSatir,dgs.dglSutunTutar)->text().toDouble();
        for(int i=0;i<tblHesap->rowCount();i++)
        {
            if(tblHesap->item(i,dgs.hspSutunIsim)->text()==hesap)
            {
                tblHesap->item(i,dgs.hspSutunGuncelMeblag)->setText(QString::number(tblHesap->item(i,dgs.hspSutunGuncelMeblag)->text().toDouble()-mevcutTutar));
                tblHesap->item(i,dgs.hspSutunDegisim)->setText("1");
                break;
            }
        }
        ///////////////////////////////

        tblDigerGelir->item(degisecekSatir,dgs.dglSutunDegisim)->setText("1");
        tblDigerGelir->item(degisecekSatir,dgs.dglSutunKilit)->setText("1");//kilit açıldığı için
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
                if(tabWidget->tabText(i)!=dgs.sekmeDigerGelirListele)
                {
                    tabWidget->setTabEnabled(i,true);
                    tabWidget->setTabsClosable(true);
                }
            }
        }
        //////////////////////////////////////////////////////77
        //kilitAcik=false;//kilit kapatıldı
        btnDegistir->setIcon(QIcon(QDir::currentPath()+"/icons/kilitkapali.png"));

        for(int i=2;i<tblDigerGelir->columnCount()-3;i++)//hesap sütununa girmesin
        {
            QTableWidgetItem *itm = tblDigerGelir->item(degisecekSatir, i);
            itm->setFlags(Qt::ItemIsEnabled);
            itm->setBackgroundColor(QColor(Qt::white));
        }
        //hesap sütunundaki combobox kaldırılıyor
        QComboBox *cmbHesap=qobject_cast<QComboBox *>(tblDigerGelir->cellWidget(degisecekSatir,dgs.dglSutunHesap));
        QString hesap=cmbHesap->currentText();
        tblDigerGelir->removeCellWidget(degisecekSatir,dgs.dglSutunHesap);
        QTableWidgetItem *itmHesap=new QTableWidgetItem();
        itmHesap->setText(hesap);
        tblDigerGelir->setItem(degisecekSatir,dgs.dglSutunHesap,itmHesap);
        /////////////////////////////////////////
        //tarih sutunundaki datedit kaldırılıyor
        QDateEdit *dateedit=qobject_cast<QDateEdit *>(tblDigerGelir->cellWidget(degisecekSatir,dgs.dglSutunTarih));
        QDate date=dateedit->date();
        QString tarih=date.toString("yyyy-MM-dd");
        tblDigerGelir->removeCellWidget(degisecekSatir,dgs.dglSutunTarih);
        QTableWidgetItem *itmTarih=new QTableWidgetItem();
        itmTarih->setText(tarih);
        tblDigerGelir->setItem(degisecekSatir,dgs.dglSutunTarih,itmTarih);
        ///////////////////////////////////////
        //DigerGelir hesabı veya tutarı değişirse hesap penceresinde de değişiyor
        double yeniTutar=tblDigerGelir->item(degisecekSatir,dgs.dglSutunTutar)->text().toDouble();
        for(int i=0;i<tblHesap->rowCount();i++)
        {
            if(tblHesap->item(i,dgs.hspSutunIsim)->text()==hesap)
            {
                tblHesap->item(i,dgs.hspSutunGuncelMeblag)->setText(QString::number(tblHesap->item(i,dgs.hspSutunGuncelMeblag)->text().toDouble()+yeniTutar));
                tblHesap->item(i,dgs.hspSutunDegisim)->setText("1");
                break;
            }
        }
        ////////////////////////////////////////
        tblDigerGelir->item(degisecekSatir,dgs.dglSutunKilit)->setText("0");//kilit kapatıldığı için
    }
}

void sdigergelir::ilkYukleme(QTableWidget* tblDigerGelir, QWidget* tabDigerGelir, QWidget* &tbDigerGelir, QTabWidget* tabWidget)
{
    tblDigerGelir->setRowCount(0);
    tblDigerGelir->setColumnCount(11);
    QStringList baslik=(QStringList()<<""<<""<<"Tarih"<<"İsim"<<"Muhatap"<<"Tutar"<<"Açıklama"<<"Hesap"<<"Kayıt"<<"Degisim"<<"Kilit");
    tblDigerGelir->setHorizontalHeaderLabels(baslik);
    tblDigerGelir->horizontalHeader()->setResizeMode(QHeaderView::Stretch);
    tblDigerGelir->horizontalHeader()->setResizeMode(dgs.dglSutunSil,QHeaderView::Custom);
    tblDigerGelir->horizontalHeader()->resizeSection(dgs.dglSutunSil, 32);
    tblDigerGelir->horizontalHeader()->setResizeMode(dgs.dglSutunDegistir,QHeaderView::Custom);
    tblDigerGelir->horizontalHeader()->resizeSection(dgs.dglSutunDegistir, 32);

    //tblDigerGelir->hideColumn(dgs.dglSutunKayit);
    //tblDigerGelir->hideColumn(dgs.dglSutunDegisim);
    //tblDigerGelir->hideColumn(dgs.dglSutunKilit);

    tbDigerGelir=qobject_cast<QWidget *>(tabDigerGelir);//tabHesaplar qwidget'a dönüştürülüyor
    tabWidget->removeTab(tabWidget->indexOf(tbDigerGelir));//tabHesaplar kapatılıyor
}
