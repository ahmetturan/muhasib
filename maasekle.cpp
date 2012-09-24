#include "maasekle.h"
#include "ui_maasekle.h"

maasekle::maasekle(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::maasekle)
{
    ui->setupUi(this);
    connect(ui->btnKapat,SIGNAL(clicked()),this,SLOT(kapat()));
    connect(ui->btnTamam,SIGNAL(clicked()),this,SLOT(tamam()));
    connect(ui->tableWidget,SIGNAL(cellDoubleClicked(int,int)),this,SLOT(takvimiAc(int,int)));
    connect(ui->tableWidget,SIGNAL(cellClicked(int,int)),this,SLOT(hucreyeTiklandi(int,int)));
    connect(ui->tableWidget,SIGNAL(cellChanged(int,int)),this,SLOT(satirEkle(int,int)));
    ilkYukleme();
}

QStringList maasekle::getListeCbMaasTur()
{
    return listeCbMaasTur;
}

void maasekle::kapat()
{
    close();
    toplamTutar=0;
}

void maasekle::tamam()
{
    for(int i=0;i<ui->tableWidget->rowCount()-1;i++)//son satır sürekli boş olduğu için son satırı gözardı ediyoruz
    {
        for(int j=1;j<ui->tableWidget->columnCount()-3;j++)//son uc sutun combobox olduğu için gözardı ediyoruz
        {
            if(j!=msSutunCalisan)
            {
                listeMaas.append(ui->tableWidget->item(i,j)->text());
            }
            else if(j==msSutunCalisan)
            {
                QComboBox* cmbCalisan=qobject_cast<QComboBox*>(ui->tableWidget->cellWidget(i,msSutunCalisan));//gözardı ettiğimiz combobox'ı listeye ekliyoruz
                listeMaas.append(cmbCalisan->currentText());
            }
        }
        QComboBox* cmbAy=qobject_cast<QComboBox*>(ui->tableWidget->cellWidget(i,msSutunAy));//gözardı ettiğimiz combobox'ı listeye ekliyoruz
        listeMaas.append(cmbAy->currentText());
        QComboBox* cmbTur=qobject_cast<QComboBox*>(ui->tableWidget->cellWidget(i,msSutunTur));//gözardı ettiğimiz combobox'ı listeye ekliyoruz
        listeMaas.append(cmbTur->currentText());
        QComboBox* cmbHesap=qobject_cast<QComboBox*>(ui->tableWidget->cellWidget(i,msSutunHesap));//gözardı ettiğimiz combobox'ı listeye ekliyoruz
        listeMaas.append(cmbHesap->currentText());
    }
    cal->close();
    close();

    qDebug()<<"listeMaas:"<<listeMaas;
}

double maasekle::getToplamTutar()
{
    return toplamTutar;
}

void maasekle::setListeHesap(QStringList list)
{
    listeHesap=list;
}

void maasekle::satirEkle(int a,int b)
{
    if(a==ui->tableWidget->rowCount()-1 && ui->tableWidget->item(a,b)->text()!="")//eğer değiştirilen satır son satır ise ve hücre boş bırakılmamışsa
    {
        ui->tableWidget->insertRow(ui->tableWidget->rowCount());
        QTableWidgetItem *itm1=new QTableWidgetItem();
        QTableWidgetItem *itm2=new QTableWidgetItem();
        itm1->setFlags(Qt::ItemIsEnabled);//tarih sutunu klavye ile değişmesin
        ui->tableWidget->setItem(ui->tableWidget->rowCount()-1,msSutunTarih,itm1);
        ui->tableWidget->setItem(ui->tableWidget->rowCount()-1,msSutunTutar,itm2);

        QPushButton *btnSil=new QPushButton();
        btnSil->setIcon(QIcon(QDir::currentPath()+"/icons/sil.png"));
        btnSil->setToolTip("Sil");
        btnSil->setEnabled(false);
        connect(btnSil,SIGNAL(clicked()),this,SLOT(satirSil()));
        ui->tableWidget->setCellWidget(ui->tableWidget->rowCount()-1,msSutunSil,btnSil);

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
        cmbAy->setEnabled(false);
        ui->tableWidget->setCellWidget(ui->tableWidget->rowCount()-1,msSutunAy,cmbAy);

        QComboBox *cmbTur=new QComboBox();
        cmbTur->addItems(listeCbMaasTur);
        cmbTur->setEnabled(false);
        ui->tableWidget->setCellWidget(ui->tableWidget->rowCount()-1,msSutunTur,cmbTur);

        QComboBox *cmbCalisan=new QComboBox();
        cmbCalisan->addItems(listeCalisanlar);
        cmbCalisan->setEnabled(false);
        ui->tableWidget->setCellWidget(ui->tableWidget->rowCount()-1,msSutunCalisan,cmbCalisan);

        QComboBox *cmbHesap=new QComboBox();
        cmbHesap->addItems(listeHesap);
        cmbHesap->setEnabled(false);
        ui->tableWidget->setCellWidget(ui->tableWidget->rowCount()-1,msSutunHesap,cmbHesap);

        //ikinci satır eklendikten sonra etkin olmayan tamam düğmesi etkinleşiyor
        if(ui->btnTamam->isEnabled()==false)
        {
            ui->btnTamam->setEnabled(true);
        }
        ////////////////
        //son satırdan bir üsteki satırın sil düğmesi ve combobox'u etkinleştiriliyor
        QPushButton* btn2=qobject_cast<QPushButton*>(ui->tableWidget->cellWidget(ui->tableWidget->rowCount()-2,msSutunSil));
        btn2->setEnabled(true);
        QComboBox* cmbTur2=qobject_cast<QComboBox*>(ui->tableWidget->cellWidget(ui->tableWidget->rowCount()-2,msSutunTur));
        cmbTur2->setEnabled(true);
        QComboBox* cmbAy2=qobject_cast<QComboBox*>(ui->tableWidget->cellWidget(ui->tableWidget->rowCount()-2,msSutunAy));
        cmbAy2->setEnabled(true);
        QComboBox* cmbCalisan2=qobject_cast<QComboBox*>(ui->tableWidget->cellWidget(ui->tableWidget->rowCount()-2,msSutunCalisan));
        cmbCalisan2->setEnabled(true);
        QComboBox* cmbHesap2=qobject_cast<QComboBox*>(ui->tableWidget->cellWidget(ui->tableWidget->rowCount()-2,msSutunHesap));
        cmbHesap2->setEnabled(true);
        /////////////////
        /*
        toplamTutar=ui->lblToplamTutar->text().toDouble();
        toplamTutar=toplamTutar+ui->tableWidget->item(ui->tableWidget->rowCount()-2,ftrSutunTutar)->text().toDouble();
        ui->lblToplamTutar->setText(QString::number(toplamTutar));
        */
    }
    //tutar değişince toplam tutarı hesaplıyor
    if(b==msSutunTutar && a<ui->tableWidget->rowCount()-1)
    {
        toplamTutar=0;
        for(int i=0;i<ui->tableWidget->rowCount();i++)
        {
            toplamTutar=toplamTutar+ui->tableWidget->item(i,msSutunTutar)->text().toDouble();
        }
        ui->lblToplamTutar->setText(QString::number(toplamTutar));
    }
    ///////////////////////////////////////
}

QStringList maasekle::getListeMaas()
{
    return listeMaas;
}

//MAAS EKLE PENCERESİNDE CALİSAN İSİMLERİNİN ÇIKABİLMESİ İCİN
void maasekle::setListeCalisanlar(QStringList list)
{
    listeCalisanlar=list;
}

void maasekle::satirSil()
{
    QObject* obj = sender();
    QPushButton *btn = qobject_cast<QPushButton *>(obj);
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

    //eğer tablewidget'ta bir satır varsa sil butonu ve combobo'ı etkisiz olsun
    if(ui->tableWidget->rowCount()==1)
    {
        QPushButton* btn=qobject_cast<QPushButton*>(ui->tableWidget->cellWidget(0,msSutunSil));
        btn->setEnabled(false);

        QComboBox* cmb=qobject_cast<QComboBox*>(ui->tableWidget->cellWidget(ui->tableWidget->rowCount()-2,msSutunTur));
        cmb->setEnabled(false);
    }
    ////////////////////////
}

//TARİH SUTUNUNA TIKLANDIĞI ZAMAN TAKVİMİ AÇIYOR
void maasekle::takvimiAc(int a, int b)
{
    if(b==msSutunTarih)
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
void maasekle::tarihiAl()
{
    ui->tableWidget->item(satir,sutun)->setText(cal->selectedDate().toString("yyyy-MM-dd"));
    cal->close();
    takvimAcik=false;
}

//TAKVİM AÇIK İSE KAPATIYOR
void maasekle::takvimAcikIseKapat()
{
    if(takvimAcik==true)
    {
        cal->close();
        takvimAcik=false;
    }
}

//TAKVİM AÇIK İKEN BOŞ BİR HÜCREYE TIKLANDIĞINDA TAKVİMİ KAPATIYOR
void maasekle::hucreyeTiklandi(int a,int b)
{
    if(b!=msSutunTarih)
    {
        takvimAcikIseKapat();
    }
}

void maasekle::ilkYukleme()
{
    msSutunSil=0;
    msSutunTarih=1;
    msSutunCalisan=2;
    msSutunTutar=3;
    msSutunAy=4;
    msSutunTur=5;
    msSutunHesap=6;

    QStringList baslik=(QStringList()<<"Sil"<<"Tarih"<<"Çalışan"<<"Tutar"<<"Ay"<<"Tür"<<"Hesap");
    ui->tableWidget->setColumnCount(7);
    ui->tableWidget->setHorizontalHeaderLabels(baslik);
    ui->tableWidget->horizontalHeader()->setResizeMode(QHeaderView::Stretch);
    ui->tableWidget->horizontalHeader()->setResizeMode(msSutunSil,QHeaderView::Custom);
    ui->tableWidget->horizontalHeader()->resizeSection(msSutunSil, 32);
    this->setWindowTitle("Maaş Ekle");
    cal=new QCalendarWidget();

    listeCbMaasTur<<"Maaş"<<"Avans"<<"Mesai"<<"İkramiye"<<"Tazminat";
}

void maasekle::ontanimliAyarlar()
{
    toplamTutar=0;

    ui->tableWidget->setRowCount(0);
    takvimAcik=false;
    ui->btnTamam->setEnabled(false);
    listeMaas.clear();//önceki girişleri tekrar yüklemesin diye listeyi boşaltıyoruz
    ui->lblToplamTutar->setText("0");

    //maas ekleme ekranı açılınca tablewidget'a ilk satırı ekliyor
    ui->tableWidget->insertRow(ui->tableWidget->rowCount());
    QPushButton *btnSil=new QPushButton();
    btnSil->setIcon(QIcon(QDir::currentPath()+"/icons/sil.png"));
    btnSil->setToolTip("Sil");
    btnSil->setEnabled(false);
    connect(btnSil,SIGNAL(clicked()),this,SLOT(satirSil()));
    ui->tableWidget->setCellWidget(0,msSutunSil,btnSil);

    QTableWidgetItem *itm1=new QTableWidgetItem();
    QTableWidgetItem *itm2=new QTableWidgetItem();
    itm1->setFlags(Qt::ItemIsEnabled);//tarih sutunu klavye ile değişmesin

    ui->tableWidget->setItem(0,msSutunTarih,itm1);
    ui->tableWidget->setItem(0,msSutunTutar,itm2);

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
    cmbAy->setEnabled(false);
    ui->tableWidget->setCellWidget(0,msSutunAy,cmbAy);

    QComboBox *cmbTur=new QComboBox();
    cmbTur->addItems(listeCbMaasTur);
    cmbTur->setEnabled(false);
    ui->tableWidget->setCellWidget(0,msSutunTur,cmbTur);

    QComboBox *cmbCalisan=new QComboBox();
    cmbCalisan->addItems(listeCalisanlar);
    cmbCalisan->setEnabled(false);
    ui->tableWidget->setCellWidget(0,msSutunCalisan,cmbCalisan);

    QComboBox *cmbHesap=new QComboBox();
    cmbHesap->addItems(listeHesap);
    cmbHesap->setEnabled(false);
    ui->tableWidget->setCellWidget(0,msSutunHesap,cmbHesap);
    ///////////////////////////////////////////////////////
}

maasekle::~maasekle()
{
    delete ui;
}
