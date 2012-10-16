#include "eklefatura.h"
#include "ui_eklefatura.h"

faturaEkle::faturaEkle(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::faturaEkle)
{
    ui->setupUi(this);
    QTextCodec::setCodecForCStrings(QTextCodec::codecForName("utf8"));
    QTextCodec::setCodecForTr(QTextCodec::codecForName("utf8"));
    QTextCodec::setCodecForLocale(QTextCodec::codecForName("utf8"));
    connect(ui->btnKapat,SIGNAL(clicked()),this,SLOT(kapat()));
    connect(ui->btnTamam,SIGNAL(clicked()),this,SLOT(tamam()));
    connect(ui->tableWidget,SIGNAL(cellDoubleClicked(int,int)),this,SLOT(takvimiAc(int,int)));
    connect(ui->tableWidget,SIGNAL(cellClicked(int,int)),this,SLOT(hucreyeTiklandi(int,int)));
    connect(ui->tableWidget,SIGNAL(cellChanged(int,int)),this,SLOT(satirEkle(int,int)));
    ilkYukleme();
}

void faturaEkle::keyPressEvent(QKeyEvent *e)
{
    if(e->key()==Qt::Key_Escape)
    {
        takvimAcikIseKapat();
    }
}

void faturaEkle::closeEvent(QCloseEvent *event)
{
    kapat();
    event->accept();
}

QStringList faturaEkle::getListeCbFaturaTur()
{
    return listeCbFaturaTur;
}

QStringList faturaEkle::getListeFatura()
{
    return listeFatura;
}

double faturaEkle::getToplamTutar()
{
    return toplamTutar;
}

void faturaEkle::setListeHesap(QStringList list)
{
    listeHesap=list;
}

//TAMAM DUGMESİNE TIKLANDIĞI ZAMAN ÇALIŞIYOR
void faturaEkle::tamam()
{
    for(int i=0;i<ui->tableWidget->rowCount()-1;i++)//son satır sürekli boş olduğu için son satırı gözardı ediyoruz
    {
        for(int j=1;j<ui->tableWidget->columnCount()-2;j++)//son 2 sutun combobox olduğu için gözardı ediyoruz
        {
            listeFatura.append(ui->tableWidget->item(i,j)->text());
        }
        QComboBox* cmb=qobject_cast<QComboBox*>(ui->tableWidget->cellWidget(i,ftrSutunTur));//gözardı ettiğimiz combobox'ı listeye ekliyoruz
        listeFatura.append(cmb->currentText());
        QComboBox* cmbHesap=qobject_cast<QComboBox*>(ui->tableWidget->cellWidget(i,ftrSutunHesap));//gözardı ettiğimiz combobox'ı listeye ekliyoruz
        listeFatura.append(cmbHesap->currentText());
    }
    cal->close();
    close();

    qDebug()<<"listeFatura:"<<listeFatura;
}

//YENİ FATURA GİRİŞİ YAPILABİLMESİ İÇİN EKRANA SATIR EKLİYOR
void faturaEkle::satirEkle(int a,int b)
{
    if(a==ui->tableWidget->rowCount()-1 && ui->tableWidget->item(a,b)->text()!="")//eğer değiştirilen satır son satır ise ve hücre boş bırakılmamışsa
    {
        ui->tableWidget->insertRow(ui->tableWidget->rowCount());
        QTableWidgetItem *itm1=new QTableWidgetItem();
        QTableWidgetItem *itm2=new QTableWidgetItem();
        QTableWidgetItem *itm3=new QTableWidgetItem();
        QTableWidgetItem *itm4=new QTableWidgetItem();
        QTableWidgetItem *itm5=new QTableWidgetItem();
        QTableWidgetItem *itm6=new QTableWidgetItem();
        QTableWidgetItem *itm7=new QTableWidgetItem();
        itm1->setFlags(Qt::ItemIsEnabled);//tarih sutunu klavye ile değişmesin
        itm2->setFlags(Qt::ItemIsEnabled);//tutarı uygulama hesaplayacak
        itm7->setFlags(Qt::ItemIsEnabled);//kdv tutarini uygulama hesaplayacak
        ui->tableWidget->setItem(ui->tableWidget->rowCount()-1,ftrSutunTarih,itm1);
        ui->tableWidget->setItem(ui->tableWidget->rowCount()-1,ftrSutunTutar,itm2);
        ui->tableWidget->setItem(ui->tableWidget->rowCount()-1,ftrSutunIsim,itm3);
        ui->tableWidget->setItem(ui->tableWidget->rowCount()-1,ftrSutunAciklama,itm4);
        ui->tableWidget->setItem(ui->tableWidget->rowCount()-1,ftrSutunMatrah,itm5);
        ui->tableWidget->setItem(ui->tableWidget->rowCount()-1,ftrSutunKdvOrani,itm6);
        ui->tableWidget->setItem(ui->tableWidget->rowCount()-1,ftrSutunKdvTutari,itm7);


        QPushButton *btnSil=new QPushButton();
        btnSil->setIcon(QIcon(QDir::currentPath()+"/icons/sil.png"));
        btnSil->setToolTip("Sil");
        btnSil->setEnabled(false);
        connect(btnSil,SIGNAL(clicked()),this,SLOT(satirSil()));
        ui->tableWidget->setCellWidget(ui->tableWidget->rowCount()-1,ftrSutunSil,btnSil);

        QComboBox *cmb=new QComboBox();
        cmb->addItems(listeCbFaturaTur);
        cmb->setEnabled(false);
        ui->tableWidget->setCellWidget(ui->tableWidget->rowCount()-1,ftrSutunTur,cmb);

        QComboBox *cmbHesap=new QComboBox();
        cmbHesap->addItems(listeHesap);
        cmbHesap->setEnabled(false);
        ui->tableWidget->setCellWidget(ui->tableWidget->rowCount()-1,ftrSutunHesap,cmbHesap);

        //ikinci satır eklendikten sonra etkin olmayan tamam düğmesi etkinleşiyor
        if(ui->btnTamam->isEnabled()==false)
        {
            ui->btnTamam->setEnabled(true);
        }
        ////////////////
        //son satırdan bir üsteki satırın sil düğmesi ve combobox'u etkinleştiriliyor
        QPushButton* btn2=qobject_cast<QPushButton*>(ui->tableWidget->cellWidget(ui->tableWidget->rowCount()-2,ftrSutunSil));
        btn2->setEnabled(true);

        QComboBox* cmb2=qobject_cast<QComboBox*>(ui->tableWidget->cellWidget(ui->tableWidget->rowCount()-2,ftrSutunTur));
        cmb2->setEnabled(true);

        QComboBox* cmbHesap2=qobject_cast<QComboBox*>(ui->tableWidget->cellWidget(ui->tableWidget->rowCount()-2,ftrSutunHesap));
        cmbHesap2->setEnabled(true);
        /////////////////

        /*
        toplamTutar=ui->lblToplamTutar->text().toDouble();
        toplamTutar=toplamTutar+ui->tableWidget->item(ui->tableWidget->rowCount()-2,ftrSutunTutar)->text().toDouble();
        ui->lblToplamTutar->setText(QString::number(toplamTutar));
        */
    }
    //kdv oranı değişince tutarı ve kdv tutarını hesaplıyor
    if(b==ftrSutunKdvOrani && a<ui->tableWidget->rowCount()-1 && ui->tableWidget->item(a,ftrSutunMatrah)->text()!="")
    {
        double kdvTutari=ui->tableWidget->item(a,ftrSutunMatrah)->text().toDouble()*ui->tableWidget->item(a,ftrSutunKdvOrani)->text().toDouble()/100;
        ui->tableWidget->item(a,ftrSutunTutar)->setText(QString::number(kdvTutari+ui->tableWidget->item(a,ftrSutunMatrah)->text().toDouble()));
        ui->tableWidget->item(a,ftrSutunKdvTutari)->setText(QString::number(kdvTutari));
    }
    ////////////////////////////
    //matrah değişince tutarı ve kdv tutarını hesaplıyor
    if(b==ftrSutunMatrah && a<ui->tableWidget->rowCount()-1 && ui->tableWidget->item(a,ftrSutunKdvOrani)->text()!="")
    {
        double kdvTutari=ui->tableWidget->item(a,ftrSutunMatrah)->text().toDouble()*ui->tableWidget->item(a,ftrSutunKdvOrani)->text().toDouble()/100;
        ui->tableWidget->item(a,ftrSutunTutar)->setText(QString::number(kdvTutari+ui->tableWidget->item(a,ftrSutunMatrah)->text().toDouble()));
        ui->tableWidget->item(a,ftrSutunKdvTutari)->setText(QString::number(kdvTutari));
    }
    ///////////////////////////////7
    //tutar değişince toplam tutarı hesaplıyor
    if(b==ftrSutunTutar && a<ui->tableWidget->rowCount()-1)
    {
        toplamTutar=0;
        for(int i=0;i<ui->tableWidget->rowCount();i++)
        {
            toplamTutar=toplamTutar+ui->tableWidget->item(i,ftrSutunTutar)->text().toDouble();
        }
        ui->lblToplamTutar->setText(QString::number(toplamTutar));
    }
    ///////////////////////////////////////
}

//VAROLAN GİRİŞİ SİLİYOR
void faturaEkle::satirSil()
{
    QPushButton *btn = qobject_cast<QPushButton *>(sender());
    QList<QPushButton *> allPButtons = ui->tableWidget->findChildren<QPushButton *>();

    int silinecekSatir=-1;
    for(int i=0;i<allPButtons.count();i++)
    {
        if(allPButtons.at(i)==btn)
        {
            silinecekSatir=i;
            break;
        }
    }
    ui->tableWidget->removeRow(silinecekSatir);

    /*
    //eğer tablewidget'ta bir satır varsa sil butonu ve combobo'ı etkisiz olsun
    if(ui->tableWidget->rowCount()==1)
    {
        QPushButton* btn=qobject_cast<QPushButton*>(ui->tableWidget->cellWidget(0,ftrSutunSil));
        btn->setEnabled(false);
        QComboBox* cmb=qobject_cast<QComboBox*>(ui->tableWidget->cellWidget(0,ftrSutunTur));
        cmb->setEnabled(false);
    }
    ////////////////////////
    */
}

//TARİH SUTUNUNA TIKLANDIĞI ZAMAN TAKVİMİ AÇIYOR
void faturaEkle::takvimiAc(int a, int b)
{
    if(b==ftrSutunTarih)
    {
        takvimAcikIseKapat();
        //cal=new QCalendarWidget();
        cal->setFirstDayOfWeek(Qt::Monday);
        cal->setLocale(QLocale::Turkish);
        cal->setParent(this);
        cal->setGeometry(50,50,280,250);
        cal->show();
        takvimAcik=true;
        satir=a;
        sutun=b;
        connect(cal,SIGNAL(activated(QDate)),this,SLOT(tarihiAl()));
    }
}

//TAKVİMDEKİ TARİHİ HÜCREYE YAZIYOR
void faturaEkle::tarihiAl()
{
    ui->tableWidget->item(satir,sutun)->setText(cal->selectedDate().toString("yyyy-MM-dd"));
    cal->close();
    takvimAcik=false;
}

//TAKVİM AÇIK İSE KAPATIYOR
void faturaEkle::takvimAcikIseKapat()
{
    if(takvimAcik==true)
    {
        cal->close();
        takvimAcik=false;
    }
}

//TAKVİM AÇIK İKEN BOŞ BİR HÜCREYE TIKLANDIĞINDA TAKVİMİ KAPATIYOR
void faturaEkle::hucreyeTiklandi(int a,int b)
{
    if(b!=ftrSutunTarih)
    {
        takvimAcikIseKapat();
    }
}

//EKRANI KAPATIYOR
void faturaEkle::kapat()
{
    close();
    toplamTutar=0;
}

//ÖNTANIMLI AYARLARI YÜKLÜYOR(SADECE UYGULAMA ÇALIŞTIRILDIĞINDA)
void faturaEkle::ilkYukleme()
{
    ftrSutunSil=0;
    ftrSutunTarih=1;
    ftrSutunIsim=2;
    ftrSutunMatrah=3;
    ftrSutunKdvOrani=4;
    ftrSutunKdvTutari=5;
    ftrSutunTutar=6;
    ftrSutunAciklama=7;
    ftrSutunTur=8;
    ftrSutunHesap=9;

    QStringList baslik=(QStringList()<<"Sil"<<"Tarih"<<"İsim"<<"Matrah"<<"KDV Oranı"<<"KDV Tutarı"<<"Tutar"<<"Açıklama"<<"Tür"<<"Hesap");
    ui->tableWidget->setColumnCount(10);
    ui->tableWidget->setHorizontalHeaderLabels(baslik);
    ui->tableWidget->horizontalHeader()->setResizeMode(QHeaderView::Stretch);
    ui->tableWidget->horizontalHeader()->setResizeMode(ftrSutunSil,QHeaderView::Custom);
    ui->tableWidget->horizontalHeader()->resizeSection(ftrSutunSil, 32);
    this->setWindowTitle("Fatura Ekle");
    cal=new QCalendarWidget();

    listeCbFaturaTur<<"Gelen"<<"Giden";
}

//ÖNTANIMLI AYARLARI YÜKLÜYOR(FATURA EKLEME PENCERESİ HER AÇILDIĞINDA)
void faturaEkle::ontanimliAyarlar()
{
    toplamTutar=0;//hiçbir şey girmeden kapata tıklanırsa sıfır döndürsün

    ui->tableWidget->setRowCount(0);
    takvimAcik=false;
    ui->btnTamam->setEnabled(false);
    listeFatura.clear();//önceki girişleri tekrar yüklemesin diye listeyi boşaltıyoruz
    ui->lblToplamTutar->setText("0");

    //fatura ekleme ekranı açılınca tablewidget'a ilk satırı ekliyor
    ui->tableWidget->insertRow(ui->tableWidget->rowCount());
    QPushButton *btnSil=new QPushButton();
    btnSil->setIcon(QIcon(QDir::currentPath()+"/icons/sil.png"));
    btnSil->setToolTip("Sil");
    btnSil->setEnabled(false);
    connect(btnSil,SIGNAL(clicked()),this,SLOT(satirSil()));
    ui->tableWidget->setCellWidget(0,ftrSutunSil,btnSil);

    QTableWidgetItem *itm1=new QTableWidgetItem();
    QTableWidgetItem *itm2=new QTableWidgetItem();
    QTableWidgetItem *itm3=new QTableWidgetItem();
    QTableWidgetItem *itm4=new QTableWidgetItem();
    QTableWidgetItem *itm5=new QTableWidgetItem();
    QTableWidgetItem *itm6=new QTableWidgetItem();
    QTableWidgetItem *itm7=new QTableWidgetItem();
    itm1->setFlags(Qt::ItemIsEnabled);//tarih sutunu klavye ile değişmesin
    itm2->setFlags(Qt::ItemIsEnabled);//tutarı uygulama hesaplayacak
    itm7->setFlags(Qt::ItemIsEnabled);//kdv tutarini uygulama hesaplayacak
    ui->tableWidget->setItem(0,ftrSutunTarih,itm1);
    ui->tableWidget->setItem(0,ftrSutunTutar,itm2);
    ui->tableWidget->setItem(0,ftrSutunIsim,itm3);
    ui->tableWidget->setItem(0,ftrSutunAciklama,itm4);
    ui->tableWidget->setItem(0,ftrSutunMatrah,itm5);
    ui->tableWidget->setItem(0,ftrSutunKdvOrani,itm6);
    ui->tableWidget->setItem(0,ftrSutunKdvTutari,itm7);

    QComboBox *cmb=new QComboBox();
    cmb->addItems(listeCbFaturaTur);
    cmb->setEnabled(false);
    ui->tableWidget->setCellWidget(0,ftrSutunTur,cmb);

    QComboBox *cmbHesap=new QComboBox();
    cmbHesap->addItems(listeHesap);
    cmbHesap->setEnabled(false);
    ui->tableWidget->setCellWidget(0,ftrSutunHesap,cmbHesap);
    ////////////////////////////////////////
}

faturaEkle::~faturaEkle()
{
    delete ui;
}
