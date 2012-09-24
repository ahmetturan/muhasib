#include "sfatura.h"
#include <QDebug>

sFatura::sFatura()
{
    ftrSutunSil=0;
    ftrSutunDegistir=1;
    ftrSutunTarih=2;
    ftrSutunIsim=3;
    ftrSutunMatrah=4;
    ftrSutunKdvOrani=5;
    ftrSutunKdvTutar=6;
    ftrSutunTutar=7;
    ftrSutunAciklama=8;
    ftrSutunTur=9;
    ftrSutunHesap=10;
    ftrSutunKayit=11;
    ftrSutunDegisim=12;
    ftrSutunKilit=13;
}

void sFatura::faturaDegistir2(bool &degisiklikIzle, bool &kaydetVar, QTableWidget* tblFatura, QStringList listeHsp, QObject* obj)
{
    degisiklikIzle=false;
    QPushButton *btnDegistir=new QPushButton();
    QPushButton *btn = qobject_cast<QPushButton *>(obj);

    //degisecek satir bulunuyor
    int degisecekSatir=-1;
    for(int i=0;i<tblFatura->rowCount();i++)
    {
        //QPushButton *btnD=qobject_cast<QPushButton *>(tblFatura->cellWidget(i,ftrSutunDegistir));
        btnDegistir=qobject_cast<QPushButton *>(tblFatura->cellWidget(i,ftrSutunDegistir));
        if(btn==btnDegistir)
        {
            degisecekSatir=i;
            break;
        }
    }
    //////////////////7

    //if(kilitAcik==false)
    if(tblFatura->item(degisecekSatir,ftrSutunKilit)->text()=="0")
    {
        btnDegistir->setIcon(QIcon(QDir::currentPath()+"/icons/kilitacik.png"));//değiştir düğmesinin ikonu değişiyor
        for(int i=2;i<tblFatura->columnCount()-4;i++)//tür sütununa girmesin
        {
            if(i!=ftrSutunKdvTutar && i!=ftrSutunTutar)//kdvtutari ve tutari uygulama hesaplayacak
            {
                QTableWidgetItem *itm = tblFatura->item(degisecekSatir, i);
                itm->setFlags(Qt::ItemIsEditable|Qt::ItemIsSelectable|Qt::ItemIsEnabled);
                itm->setBackgroundColor(QColor(Qt::gray));
            }
        }
        //tür sütununa combobox ekleniyor
        QTableWidgetItem *itmTur = tblFatura->item(degisecekSatir, ftrSutunTur);
        QString tur=itmTur->text();
        QComboBox *cmbTur=new QComboBox();
        cmbTur->addItems(form_faturaEkle.getListeCbFaturaTur());
        cmbTur->setCurrentIndex(cmbTur->findText(tur));
        tblFatura->setCellWidget(degisecekSatir,ftrSutunTur,cmbTur);
        /////////////////////////////////
        //hesap sütununa combobox ekleniyor
        QTableWidgetItem *itmHesap = tblFatura->item(degisecekSatir, ftrSutunHesap);
        QString hesap=itmHesap->text();
        QComboBox *cmbHesap=new QComboBox();
        cmbHesap->addItems(listeHsp);
        cmbHesap->setCurrentIndex(cmbHesap->findText(hesap));
        tblFatura->setCellWidget(degisecekSatir,ftrSutunHesap,cmbHesap);
        /////////////////////////////////

        tblFatura->item(degisecekSatir,ftrSutunDegisim)->setText("1");
        tblFatura->item(degisecekSatir,ftrSutunKilit)->setText("1");//kilit açıldığı için
        kaydetVar=true;
        degisiklikIzle=true;//satırda yapılan değişiklikleri kdvtutarı ve tutarı hesaplayabilmek için izlesin
    }
    else
    {
        btnDegistir->setIcon(QIcon(QDir::currentPath()+"/icons/kilitkapali.png"));

        for(int i=2;i<tblFatura->columnCount()-4;i++)//tür sütununa girmesin
        {
            QTableWidgetItem *itm = tblFatura->item(degisecekSatir, i);
            itm->setFlags(Qt::ItemIsEnabled);
            itm->setBackgroundColor(QColor(Qt::white));
        }
        //tür sütunundaki combobox kaldırılıyor
        QComboBox *cmbTur=qobject_cast<QComboBox *>(tblFatura->cellWidget(degisecekSatir,ftrSutunTur));
        QString faturaTuru=cmbTur->currentText();
        tblFatura->removeCellWidget(degisecekSatir,ftrSutunTur);
        QTableWidgetItem *itmTur=new QTableWidgetItem();
        itmTur->setText(faturaTuru);
        tblFatura->setItem(degisecekSatir,ftrSutunTur,itmTur);
        /////////////////////////////////////////
        //hesap sütunundaki combobox kaldırılıyor
        QComboBox *cmbHesap=qobject_cast<QComboBox *>(tblFatura->cellWidget(degisecekSatir,ftrSutunHesap));
        QString hesap=cmbHesap->currentText();
        tblFatura->removeCellWidget(degisecekSatir,ftrSutunHesap);
        QTableWidgetItem *itmHesap=new QTableWidgetItem();
        itmHesap->setText(hesap);
        tblFatura->setItem(degisecekSatir,ftrSutunHesap,itmHesap);
        /////////////////////////////////////////

        tblFatura->item(degisecekSatir,ftrSutunKilit)->setText("0");//kilit kapatıldığı için
    }
}

void sFatura::faturaSil2(double &ToplamTutarFatura, QStringList &listSilinenFatura, bool &kaydetVar, QLabel *lblFatura, QTableWidget* tblFatura, QObject* obj)
{
    QPushButton *btn = qobject_cast<QPushButton *>(obj);

    //silinecek satir bulunuyor
    int silinecekSatir=-1;
    for(int i=0;i<tblFatura->rowCount();i++)
    {
        QPushButton *btnSil=qobject_cast<QPushButton *>(tblFatura->cellWidget(i,ftrSutunSil));
        if(btn==btnSil)
        {
            silinecekSatir=i;
            break;
        }
    }
    //////////////////////////////

    //if(kilitAcik==true)//kilidi açık satırı silmeden önce kilidini kapatıyor
    if(tblFatura->item(silinecekSatir,ftrSutunKilit)->text()=="1")
    {
        QPushButton *btnDegistir=qobject_cast<QPushButton *>(tblFatura->cellWidget(silinecekSatir,ftrSutunDegistir));
        btnDegistir->click();
    }

    listSilinenFatura.append(tblFatura->item(silinecekSatir,ftrSutunKayit)->text());

    ToplamTutarFatura=ToplamTutarFatura-tblFatura->item(silinecekSatir,ftrSutunTutar)->text().toDouble();//silinen fatura tutarını toplamtutar dan çıkarıyor
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
        if(tblFatura->item(i,ftrSutunKayit)->text()=="0")
        {
            query.exec(QString("insert into fatura(f_tarih, f_isim, f_matrah, f_kdvorani, f_kdvtutari, f_tutar, f_aciklama, f_tur, f_hesap) values ('%1', '%2', '%3', '%4', '%5', '%6', '%7', '%8', '%9')").arg(tblFatura->item(i,ftrSutunTarih)->text()).arg(tblFatura->item(i,ftrSutunIsim)->text()).arg(tblFatura->item(i,ftrSutunMatrah)->text()).arg(tblFatura->item(i,ftrSutunKdvOrani)->text()).arg(tblFatura->item(i,ftrSutunKdvTutar)->text()).arg(tblFatura->item(i,ftrSutunTutar)->text()).arg(tblFatura->item(i,ftrSutunAciklama)->text()).arg(tblFatura->item(i,ftrSutunTur)->text()).arg(tblFatura->item(i,ftrSutunHesap)->text()));
            tblFatura->item(i,ftrSutunKayit)->setText(query.lastInsertId().toString());
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
        if(tblFatura->item(i,ftrSutunDegisim)->text()=="1")
        {
            query.exec(QString("update fatura set f_tarih='%1', f_isim='%2', f_matrah='%7', f_kdvorani='%8', f_kdvtutari='%9', f_tutar='%3', f_aciklama='%4', f_tur='%5', f_hesap='%10' where f_id='%6'").arg(tblFatura->item(i,ftrSutunTarih)->text()).arg(tblFatura->item(i,ftrSutunIsim)->text()).arg(tblFatura->item(i,ftrSutunTutar)->text()).arg(tblFatura->item(i,ftrSutunAciklama)->text()).arg(tblFatura->item(i,ftrSutunTur)->text()).arg(tblFatura->item(i,ftrSutunKayit)->text()).arg(tblFatura->item(i,ftrSutunMatrah)->text()).arg(tblFatura->item(i,ftrSutunKdvOrani)->text()).arg(tblFatura->item(i,ftrSutunKdvTutar)->text()).arg(tblFatura->item(i,ftrSutunHesap)->text()));
            tblFatura->item(i,ftrSutunDegisim)->setText("0");
        }
    }
}

void sFatura::ilkYukleme2(double &ToplamTutarFatura, QTableWidget* tblFatura, QTableWidget* tblGelenFaturalar, QTableWidget* tblGidenFaturalar, QWidget* tabFatura, QWidget* tabFaturaOzeti, QWidget* &tbFatura, QWidget* &tbFaturaOzeti, QTabWidget* tabWidget)
{
    tblFatura->setRowCount(0);
    tblFatura->setColumnCount(14);
    QStringList baslik=(QStringList()<<""<<""<<"Tarih"<<"İsim"<<"Matrah"<<"KDV Oranı"<<"KDV Tutarı"<<"Toplam Tutar"<<"Açıklama"<<"Tür"<<"Hesap"<<"Kayıt"<<"Degisim"<<"Kilit");
    tblFatura->setHorizontalHeaderLabels(baslik);
    tblFatura->horizontalHeader()->setResizeMode(QHeaderView::Stretch);
    tblFatura->horizontalHeader()->setResizeMode(ftrSutunSil,QHeaderView::Custom);
    tblFatura->horizontalHeader()->resizeSection(ftrSutunSil, 32);
    tblFatura->horizontalHeader()->setResizeMode(ftrSutunDegistir,QHeaderView::Custom);
    tblFatura->horizontalHeader()->resizeSection(ftrSutunDegistir, 32);

    tblFatura->hideColumn(ftrSutunKayit);
    tblFatura->hideColumn(ftrSutunDegisim);
    tblFatura->hideColumn(ftrSutunKilit);

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
