#include "eklecalisan.h"
#include "ui_eklecalisan.h"
#include <QDebug>

calisanekle::calisanekle(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::calisanekle)
{
    ui->setupUi(this);
    connect(ui->btnTamam,SIGNAL(clicked()),this,SLOT(tamam()));
    connect(ui->btnKapat,SIGNAL(clicked()),this,SLOT(kapat()));
    connect(ui->tableWidget,SIGNAL(cellChanged(int,int)),this,SLOT(satirEkle(int,int)));
    connect(ui->tableWidget,SIGNAL(cellDoubleClicked(int,int)),this,SLOT(takvimiAc(int,int)));
    connect(ui->tableWidget,SIGNAL(cellClicked(int,int)),this,SLOT(hucreyeTiklandi(int,int)));
    connect(ui->tableWidget,SIGNAL(cellChanged(int,int)),this,SLOT(satirEkle(int,int)));
    ilkYukleme();
}

QStringList calisanekle::getListeCbCalisanTur()
{
    return listeCbCalisanTur;
}

void calisanekle::tamam()
{
    for(int i=0;i<ui->tableWidget->rowCount()-1;i++)//son satır sürekli boş olduğu için son satırı gözardı ediyoruz
    {
        for(int j=1;j<ui->tableWidget->columnCount();j++)//son sutun combobox olduğu için gözardı ediyoruz
        {
            if(j!=clsSutunKonum)
            {
                listeCalisan.append(ui->tableWidget->item(i,j)->text());
            }
            else
            {
                QComboBox* cmb=qobject_cast<QComboBox*>(ui->tableWidget->cellWidget(i,clsSutunKonum));//gözardı ettiğimiz combobox'ı listeye ekliyoruz
                listeCalisan.append(cmb->currentText());
            }
        }
    }
    cal->close();
    close();
}

void calisanekle::kapat()
{
    close();
    toplamTutar=0;
}

QStringList calisanekle::getListeCalisan()
{
    return listeCalisan;
}

double calisanekle::getToplamTutar()
{
    return toplamTutar;
}

void calisanekle::satirEkle(int a,int b)
{
    if(a==ui->tableWidget->rowCount()-1 && ui->tableWidget->item(a,b)->text()!="")//eğer değiştirilen satır son satır ise ve hücre boş bırakılmamışsa
    {
        ui->tableWidget->insertRow(ui->tableWidget->rowCount());
        QTableWidgetItem *itm1=new QTableWidgetItem();
        QTableWidgetItem *itm2=new QTableWidgetItem();
        QTableWidgetItem *itm3=new QTableWidgetItem();
        QTableWidgetItem *itm4=new QTableWidgetItem();
        itm2->setFlags(Qt::ItemIsEnabled);//işegiriş sutunu klavye ile değişmesin
        ui->tableWidget->setItem(ui->tableWidget->rowCount()-1,clsSutunIsim,itm1);
        ui->tableWidget->setItem(ui->tableWidget->rowCount()-1,clsSutunIseGiris,itm2);
        ui->tableWidget->setItem(ui->tableWidget->rowCount()-1,clsSutunMaas,itm3);
        ui->tableWidget->setItem(ui->tableWidget->rowCount()-1,clsSutunAciklama,itm4);

        QPushButton *btnSil=new QPushButton();
        btnSil->setIcon(QIcon(QDir::currentPath()+"/icons/sil.png"));
        btnSil->setToolTip("Sil");
        btnSil->setEnabled(false);
        connect(btnSil,SIGNAL(clicked()),this,SLOT(satirSil()));
        ui->tableWidget->setCellWidget(ui->tableWidget->rowCount()-1,clsSutunSil,btnSil);

        QComboBox *cmbKonum=new QComboBox();
        cmbKonum->addItems(listeCbCalisanTur);
        cmbKonum->setEnabled(false);
        ui->tableWidget->setCellWidget(ui->tableWidget->rowCount()-1,clsSutunKonum,cmbKonum);

        //ikinci satır eklendikten sonra etkin olmayan tamam düğmesi etkinleşiyor
        if(ui->btnTamam->isEnabled()==false)
        {
            ui->btnTamam->setEnabled(true);
        }
        ////////////////
        //son satırdan bir üsteki satırın sil düğmesi ve combobox'u etkinleştiriliyor
        QPushButton* btnSil2=qobject_cast<QPushButton*>(ui->tableWidget->cellWidget(ui->tableWidget->rowCount()-2,clsSutunSil));
        btnSil2->setEnabled(true);
        QComboBox* cmbKonum2=qobject_cast<QComboBox*>(ui->tableWidget->cellWidget(ui->tableWidget->rowCount()-2,clsSutunKonum));
        cmbKonum2->setEnabled(true);
        /////////////////
        /*
        toplamTutar=ui->lblToplamTutar->text().toDouble();
        toplamTutar=toplamTutar+ui->tableWidget->item(ui->tableWidget->rowCount()-2,ftrSutunTutar)->text().toDouble();
        ui->lblToplamTutar->setText(QString::number(toplamTutar));
        */
    }
    //tutar değişince toplam tutarı hesaplıyor
    if(b==clsSutunMaas && a<ui->tableWidget->rowCount()-1)
    {
        toplamTutar=0;
        for(int i=0;i<ui->tableWidget->rowCount();i++)
        {
            toplamTutar=toplamTutar+ui->tableWidget->item(i,clsSutunMaas)->text().toDouble();
        }
        ui->lblToplamTutar->setText(QString::number(toplamTutar));
    }
    ///////////////////////////////////////
}

void calisanekle::satirSil()
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
        QPushButton* btn=qobject_cast<QPushButton*>(ui->tableWidget->cellWidget(0,clsSutunSil));
        btn->setEnabled(false);

        QComboBox* cmb=qobject_cast<QComboBox*>(ui->tableWidget->cellWidget(ui->tableWidget->rowCount()-2,clsSutunKonum));
        cmb->setEnabled(false);
    }
    ////////////////////////
}

void calisanekle::takvimiAc(int a, int b)
{
    if(b==clsSutunIseGiris)
    {
        takvimAcikIseKapat();
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
void calisanekle::tarihiAl()
{
    ui->tableWidget->item(satir,sutun)->setText(cal->selectedDate().toString("yyyy-MM-dd"));
    cal->close();
    takvimAcik=false;
}

//TAKVİM AÇIK İSE KAPATIYOR
void calisanekle::takvimAcikIseKapat()
{
    if(takvimAcik==true)
    {
        cal->close();
        takvimAcik=false;
    }
}

//TAKVİM AÇIK İKEN BOŞ BİR HÜCREYE TIKLANDIĞINDA TAKVİMİ KAPATIYOR
void calisanekle::hucreyeTiklandi(int a,int b)
{
    if(b!=clsSutunIseGiris)
    {
        takvimAcikIseKapat();
    }
}

//ÖNTANIMLI AYARLARI YÜKLÜYOR(SADECE UYGULAMA ÇALIŞTIRILDIĞINDA)
void calisanekle::ilkYukleme()
{
    clsSutunSil=0;
    clsSutunIsim=1;
    clsSutunKonum=2;
    clsSutunIseGiris=3;
    clsSutunMaas=4;
    clsSutunAciklama=5;

    QStringList baslik=(QStringList()<<"Sil"<<"İsim"<<"Konum"<<"İşe Giriş"<<"Maaş"<<"Açıklama");
    ui->tableWidget->setColumnCount(6);
    ui->tableWidget->setHorizontalHeaderLabels(baslik);
    ui->tableWidget->horizontalHeader()->setResizeMode(QHeaderView::Stretch);
    ui->tableWidget->horizontalHeader()->setResizeMode(clsSutunSil,QHeaderView::Custom);
    ui->tableWidget->horizontalHeader()->resizeSection(clsSutunSil, 32);
    ui->tableWidget->horizontalHeader()->setResizeMode(clsSutunIseGiris,QHeaderView::Custom);
    ui->tableWidget->horizontalHeader()->resizeSection(clsSutunIseGiris, 80);
    this->setWindowTitle("Çalışan Ekle");
    cal=new QCalendarWidget();

    listeCbCalisanTur<<"İşçi"<<"Şef"<<"Müdür";
}

//ÖNTANIMLI AYARLARI YÜKLÜYOR(FATURA EKLEME PENCERESİ HER AÇILDIĞINDA)
void calisanekle::ontanimliAyarlar()
{
    toplamTutar=0;

    ui->tableWidget->setRowCount(0);
    takvimAcik=false;
    ui->btnTamam->setEnabled(false);
    listeCalisan.clear();//önceki girişleri tekrar yüklemesin diye listeyi boşaltıyoruz
    ui->lblToplamTutar->setText("0");

    //fatura ekleme ekranı açılınca tablewidget'a ilk satırı ekliyor
    ui->tableWidget->insertRow(ui->tableWidget->rowCount());
    QPushButton *btnSil=new QPushButton();
    btnSil->setIcon(QIcon(QDir::currentPath()+"/icons/sil.png"));
    btnSil->setToolTip("Sil");
    btnSil->setEnabled(false);
    connect(btnSil,SIGNAL(clicked()),this,SLOT(satirSil()));
    ui->tableWidget->setCellWidget(0,clsSutunSil,btnSil);

    QComboBox *cmb=new QComboBox();
    cmb->addItems(listeCbCalisanTur);
    cmb->setEnabled(false);
    ui->tableWidget->setCellWidget(0,clsSutunKonum,cmb);

    QTableWidgetItem *itm1=new QTableWidgetItem();
    QTableWidgetItem *itm2=new QTableWidgetItem();
    QTableWidgetItem *itm3=new QTableWidgetItem();
    QTableWidgetItem *itm4=new QTableWidgetItem();
    ui->tableWidget->setItem(0,clsSutunIsim,itm1);
    ui->tableWidget->setItem(0,clsSutunIseGiris,itm2);
    ui->tableWidget->setItem(0,clsSutunMaas,itm3);
    ui->tableWidget->setItem(0,clsSutunAciklama,itm4);
    itm2->setFlags(Qt::ItemIsEnabled);//işegiriş sutunu klavye ile değişmesin
}

calisanekle::~calisanekle()
{
    delete ui;
}
