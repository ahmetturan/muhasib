#include "sfatura.h"
#include <QDebug>

sFatura::sFatura()
{
}

void sFatura::faturaDegistir2(bool &kilitAcik, bool &degisiklikIzle, bool &kaydetVar, QTableWidget* tblFatura, QTableWidget* tblHesap, QTabWidget* tabWidget, QStringList listeHsp, int &kilidiAcikSatirSayisi, QObject* obj)
{
    degisiklikIzle=false;
    QPushButton *btnDegistir=new QPushButton();
    QPushButton *btn = qobject_cast<QPushButton *>(obj);

    //degisecek satir bulunuyor
    int degisecekSatir=-1;
    for(int i=0;i<tblFatura->rowCount();i++)
    {
        btnDegistir=qobject_cast<QPushButton *>(tblFatura->cellWidget(i,dgs.ftrSutunDegistir));
        if(btn==btnDegistir)
        {
            degisecekSatir=i;
            break;
        }
    }
    //////////////////7

    if(tblFatura->item(degisecekSatir,dgs.ftrSutunKilit)->text()=="0")//kilit açılıyor
    {
        kilidiAcikSatirSayisi=kilidiAcikSatirSayisi+1;
        qDebug()<<"kilidiAcikSatirSayisi"<<kilidiAcikSatirSayisi;
        //faturalar sekmesi hariç diğer sekmekel donduruluyor
        for(int i=0;i<tabWidget->count();i++)
        {
            if(tabWidget->tabText(i)!="Faturalar")
            {
                tabWidget->setTabEnabled(i,false);
                tabWidget->setTabsClosable(false);
            }
        }
        //////////////////////////////////////////////////////77
        kilitAcik=true;//kilit açıldı
        btnDegistir->setIcon(QIcon(QDir::currentPath()+"/icons/kilitacik.png"));//değiştir düğmesinin ikonu değişiyor
        for(int i=2;i<tblFatura->columnCount()-4;i++)//tür sütununa girmesin
        {
            if(i!=dgs.ftrSutunKdvTutar && i!=dgs.ftrSutunTutar && i!=dgs.ftrSutunKayitNo)//kdvtutari ve tutari uygulama hesaplayacak
            {
                QTableWidgetItem *itm = tblFatura->item(degisecekSatir, i);
                itm->setFlags(Qt::ItemIsEditable|Qt::ItemIsSelectable|Qt::ItemIsEnabled);
                itm->setBackgroundColor(QColor(Qt::gray));
            }
        }
        //tür sütununa combobox ekleniyor
        QTableWidgetItem *itmTur = tblFatura->item(degisecekSatir, dgs.ftrSutunTur);
        QString tur=itmTur->text();
        QComboBox *cmbTur=new QComboBox();
        cmbTur->addItems(form_faturaEkle.getListeCbFaturaTur());
        cmbTur->setCurrentIndex(cmbTur->findText(tur));
        tblFatura->setCellWidget(degisecekSatir,dgs.ftrSutunTur,cmbTur);
        /////////////////////////////////
        //hesap sütununa combobox ekleniyor
        QTableWidgetItem *itmHesap = tblFatura->item(degisecekSatir, dgs.ftrSutunHesap);
        QString hesap=itmHesap->text();
        QComboBox *cmbHesap=new QComboBox();
        cmbHesap->addItems(listeHsp);
        cmbHesap->setCurrentIndex(cmbHesap->findText(hesap));
        tblFatura->setCellWidget(degisecekSatir,dgs.ftrSutunHesap,cmbHesap);
        /////////////////////////////////
        //fatura hesabı veya tutarı değişirse hesap penceresinde de değişiyor
        double mevcutTutar=tblFatura->item(degisecekSatir,dgs.ftrSutunTutar)->text().toDouble();
        for(int i=0;i<tblHesap->rowCount();i++)
        {
            if(tblHesap->item(i,dgs.hspSutunIsim)->text()==hesap)
            {
                tblHesap->item(i,dgs.hspSutunGuncelMeblag)->setText(QString::number(tblHesap->item(i,dgs.hspSutunGuncelMeblag)->text().toDouble()+mevcutTutar));
                tblHesap->item(i,dgs.hspSutunDegisim)->setText("1");
                break;
            }
        }
        ///////////////////////////////7

        tblFatura->item(degisecekSatir,dgs.ftrSutunDegisim)->setText("1");
        tblFatura->item(degisecekSatir,dgs.ftrSutunKilit)->setText("1");//kilit açıldığı için
        kaydetVar=true;
        degisiklikIzle=true;//satırda yapılan değişiklikleri kdvtutarı ve tutarı hesaplayabilmek için izlesin
    }
    else//kilit kapanıyor
    {
        kilidiAcikSatirSayisi=kilidiAcikSatirSayisi-1;
        qDebug()<<"kilidiAcikSatirSayisi"<<kilidiAcikSatirSayisi;
        //dondurulmuş sekmeler açılıyor
        if(kilidiAcikSatirSayisi==0)
        {
            for(int i=0;i<tabWidget->count();i++)
            {
                if(tabWidget->tabText(i)!="Faturalar")
                {
                    tabWidget->setTabEnabled(i,true);
                    tabWidget->setTabsClosable(true);
                }
            }
        }
        //////////////////////////////////////////////////////77
        kilitAcik=false;//kilit kapatıldı
        btnDegistir->setIcon(QIcon(QDir::currentPath()+"/icons/kilitkapali.png"));

        for(int i=2;i<tblFatura->columnCount()-4;i++)//tür sütununa girmesin
        {
            QTableWidgetItem *itm = tblFatura->item(degisecekSatir, i);
            itm->setFlags(Qt::ItemIsEnabled);
            itm->setBackgroundColor(QColor(Qt::white));
        }
        //tür sütunundaki combobox kaldırılıyor
        QComboBox *cmbTur=qobject_cast<QComboBox *>(tblFatura->cellWidget(degisecekSatir,dgs.ftrSutunTur));
        QString faturaTuru=cmbTur->currentText();
        tblFatura->removeCellWidget(degisecekSatir,dgs.ftrSutunTur);
        QTableWidgetItem *itmTur=new QTableWidgetItem();
        itmTur->setText(faturaTuru);
        tblFatura->setItem(degisecekSatir,dgs.ftrSutunTur,itmTur);
        /////////////////////////////////////////
        //hesap sütunundaki combobox kaldırılıyor
        QComboBox *cmbHesap=qobject_cast<QComboBox *>(tblFatura->cellWidget(degisecekSatir,dgs.ftrSutunHesap));
        QString hesap=cmbHesap->currentText();
        tblFatura->removeCellWidget(degisecekSatir,dgs.ftrSutunHesap);
        QTableWidgetItem *itmHesap=new QTableWidgetItem();
        itmHesap->setText(hesap);
        tblFatura->setItem(degisecekSatir,dgs.ftrSutunHesap,itmHesap);
        /////////////////////////////////////////
        //fatura hesabı veya tutarı değişirse hesap penceresinde de değişiyor
        double yeniTutar=tblFatura->item(degisecekSatir,dgs.ftrSutunTutar)->text().toDouble();
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

        tblFatura->item(degisecekSatir,dgs.ftrSutunKilit)->setText("0");//kilit kapatıldığı için
    }
}

void sFatura::faturaSil2(double &ToplamTutarFatura, QStringList &listSilinenFatura, bool &kaydetVar, QLabel *lblFatura, QTableWidget* tblFatura, QObject* obj)
{
    QPushButton *btn = qobject_cast<QPushButton *>(obj);
    //silinecek satir bulunuyor
    int silinecekSatir=-1;
    for(int i=0;i<tblFatura->rowCount();i++)
    {
        QPushButton *btnSil=qobject_cast<QPushButton *>(tblFatura->cellWidget(i,dgs.ftrSutunSil));
        if(btn==btnSil)
        {
            silinecekSatir=i;
            break;
        }
    }
    //////////////////////////////

    if(tblFatura->item(silinecekSatir,dgs.ftrSutunKilit)->text()=="1")
    {
        QPushButton *btnDegistir=qobject_cast<QPushButton *>(tblFatura->cellWidget(silinecekSatir,dgs.ftrSutunDegistir));
        btnDegistir->click();
    }

    listSilinenFatura.append(tblFatura->item(silinecekSatir,dgs.ftrSutunKayit)->text());

    ToplamTutarFatura=ToplamTutarFatura-tblFatura->item(silinecekSatir,dgs.ftrSutunTutar)->text().toDouble();//silinen fatura tutarını toplamtutar dan çıkarıyor
    tblFatura->removeRow(silinecekSatir);
    lblFatura->setText("Kayıt: "+QString::number(tblFatura->rowCount())+" Tutar: "+QString::number(ToplamTutarFatura));//label i güncelliyor

    kaydetVar=true;
}

void sFatura::faturaKaydet2(QStringList &listSilinenFatura,QTableWidget* tblFatura)
{
    QSqlQuery query;
    //yeni eklenen kayıtlar
    for(int i=0;i<tblFatura->rowCount();i++)
    {
        if(tblFatura->item(i,dgs.ftrSutunKayit)->text()=="0")
        {
            query.exec(QString("insert into fatura(f_kayitno, f_tarih, f_isim, f_matrah, f_kdvorani, f_kdvtutari, f_tutar, f_aciklama, f_tur, f_hesap) values ('%1', '%2', '%3', '%4', '%5', '%6', '%7', '%8', '%9', '%10')").arg(tblFatura->item(i,dgs.ftrSutunKayitNo)->text()).arg(tblFatura->item(i,dgs.ftrSutunTarih)->text()).arg(tblFatura->item(i,dgs.ftrSutunIsim)->text()).arg(tblFatura->item(i,dgs.ftrSutunMatrah)->text()).arg(tblFatura->item(i,dgs.ftrSutunKdvOrani)->text()).arg(tblFatura->item(i,dgs.ftrSutunKdvTutar)->text()).arg(tblFatura->item(i,dgs.ftrSutunTutar)->text()).arg(tblFatura->item(i,dgs.ftrSutunAciklama)->text()).arg(tblFatura->item(i,dgs.ftrSutunTur)->text()).arg(tblFatura->item(i,dgs.ftrSutunHesap)->text()));
            tblFatura->item(i,dgs.ftrSutunKayit)->setText(query.lastInsertId().toString());
        }
    }
    ////////////////////////
    //silinen kayıtlar
    for(int i=0;i<listSilinenFatura.count();i++)
    {
        query.exec(QString("delete from fatura where f_id='%1'").arg(listSilinenFatura.at(i)));
    }
    //////////////////////
    //değiştirilen kayıtlar
    for(int i=0;i<tblFatura->rowCount();i++)
    {
        if(tblFatura->item(i,dgs.ftrSutunDegisim)->text()=="1")
        {
            query.exec(QString("update fatura set f_tarih='%1', f_isim='%2', f_matrah='%7', f_kdvorani='%8', f_kdvtutari='%9', f_tutar='%3', f_aciklama='%4', f_tur='%5', f_hesap='%10' where f_id='%6'").arg(tblFatura->item(i,dgs.ftrSutunTarih)->text()).arg(tblFatura->item(i,dgs.ftrSutunIsim)->text()).arg(tblFatura->item(i,dgs.ftrSutunTutar)->text()).arg(tblFatura->item(i,dgs.ftrSutunAciklama)->text()).arg(tblFatura->item(i,dgs.ftrSutunTur)->text()).arg(tblFatura->item(i,dgs.ftrSutunKayit)->text()).arg(tblFatura->item(i,dgs.ftrSutunMatrah)->text()).arg(tblFatura->item(i,dgs.ftrSutunKdvOrani)->text()).arg(tblFatura->item(i,dgs.ftrSutunKdvTutar)->text()).arg(tblFatura->item(i,dgs.ftrSutunHesap)->text()));
            tblFatura->item(i,dgs.ftrSutunDegisim)->setText("0");
        }
    }
}

void sFatura::ilkYukleme2(double &ToplamTutarFatura, QTableWidget* tblFatura, QTableWidget* tblGelenFaturalar, QTableWidget* tblGidenFaturalar, QWidget* tabFatura, QWidget* tabFaturaOzeti, QWidget* &tbFatura, QWidget* &tbFaturaOzeti, QTabWidget* tabWidget)
{
    tblFatura->setRowCount(0);
    tblFatura->setColumnCount(15);
    QStringList baslik=(QStringList()<<""<<""<<"Kayıt No"<<"Tarih"<<"İsim"<<"Matrah"<<"KDV Oranı"<<"KDV Tutarı"<<"Toplam Tutar"<<"Açıklama"<<"Tür"<<"Hesap"<<"Kayıt"<<"Degisim"<<"Kilit");
    tblFatura->setHorizontalHeaderLabels(baslik);
    tblFatura->horizontalHeader()->setResizeMode(QHeaderView::Stretch);
    tblFatura->horizontalHeader()->setResizeMode(dgs.ftrSutunSil,QHeaderView::Custom);
    tblFatura->horizontalHeader()->resizeSection(dgs.ftrSutunSil, 32);
    tblFatura->horizontalHeader()->setResizeMode(dgs.ftrSutunDegistir,QHeaderView::Custom);
    tblFatura->horizontalHeader()->resizeSection(dgs.ftrSutunDegistir, 32);
    tblFatura->horizontalHeader()->setResizeMode(dgs.ftrSutunKayitNo,QHeaderView::Custom);
    tblFatura->horizontalHeader()->resizeSection(dgs.ftrSutunKayitNo, 90);
    tblFatura->horizontalHeader()->setResizeMode(dgs.ftrSutunTarih,QHeaderView::Custom);
    tblFatura->horizontalHeader()->resizeSection(dgs.ftrSutunTarih, 80);

    tblFatura->hideColumn(dgs.ftrSutunKayit);
    tblFatura->hideColumn(dgs.ftrSutunDegisim);
    tblFatura->hideColumn(dgs.ftrSutunKilit);

    tblGelenFaturalar->setRowCount(0);
    tblGelenFaturalar->setColumnCount(7);
    baslik=(QStringList()<<"Tarih"<<"İsim"<<"Matrah"<<"KDV Oranı"<<"KDV Tutarı"<<"Tutar"<<"Açıklama");
    tblGelenFaturalar->setHorizontalHeaderLabels(baslik);
    tblGelenFaturalar->horizontalHeader()->setResizeMode(QHeaderView::Stretch);
    tblGelenFaturalar->setEditTriggers(QAbstractItemView::NoEditTriggers);

    tblGidenFaturalar->setRowCount(0);
    tblGidenFaturalar->setColumnCount(7);
    baslik=(QStringList()<<"Tarih"<<"İsim"<<"Matrah"<<"KDV Oranı"<<"KDV Tutarı"<<"Tutar"<<"Açıklama");
    tblGidenFaturalar->setHorizontalHeaderLabels(baslik);
    tblGidenFaturalar->horizontalHeader()->setResizeMode(QHeaderView::Stretch);
    tblGidenFaturalar->setEditTriggers(QAbstractItemView::NoEditTriggers);
    tblGidenFaturalar->setSelectionMode(QAbstractItemView::NoSelection);

    ToplamTutarFatura=0;

    tbFatura=qobject_cast<QWidget *>(tabFatura);//tabfatura qwidget'a dönüştürülüyor
    tabWidget->removeTab(tabWidget->indexOf(tbFatura));//tabfatura kapatılıyor
    tbFaturaOzeti=qobject_cast<QWidget *>(tabFaturaOzeti);//tabfaturözeti qwidget'a dönüştürülüyor
    tabWidget->removeTab(tabWidget->indexOf(tbFaturaOzeti));//tabfaturaözeti kapatılıyor
}
