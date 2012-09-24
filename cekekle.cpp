#include "cekekle.h"
#include "ui_cekekle.h"
#include <QDebug>

cekekle::cekekle(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::cekekle)
{
    ui->setupUi(this);
    connect(ui->btnTamam,SIGNAL(clicked()),this,SLOT(tamam()));
    connect(ui->btnKapat,SIGNAL(clicked()),this,SLOT(kapat()));
    connect(ui->tableWidget,SIGNAL(cellChanged(int,int)),this,SLOT(satirEkle(int,int)));
    connect(ui->tableWidget,SIGNAL(cellDoubleClicked(int,int)),this,SLOT(takvimiAc(int,int)));
    connect(ui->tableWidget,SIGNAL(cellClicked(int,int)),this,SLOT(hucreyeTiklandi(int,int)));
    ilkYukleme();
}

QStringList cekekle::getListeCbCekTur()
{
    return listeCbCekTur;
}

void cekekle::takvimAcikIseKapat()
{
    if(takvimAcik==true)
    {
        cal->close();
        takvimAcik=false;
    }
}

void cekekle::hucreyeTiklandi(int a, int b)
{
    if(b!=sutunTarih)
    {
        takvimAcikIseKapat();
    }
}

void cekekle::takvimiAc(int a, int b)
{
    if(b==sutunTarih)
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

void cekekle::tarihiAl()
{
    ui->tableWidget->item(satir,sutun)->setText(cal->selectedDate().toString("yyyy-MM-dd"));
    cal->close();
    takvimAcik=false;
}

void cekekle::satirEkle(int a,int b)
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
        itm1->setFlags(Qt::ItemIsEnabled);
        ui->tableWidget->setItem(ui->tableWidget->rowCount()-1,sutunTarih,itm1);
        ui->tableWidget->setItem(ui->tableWidget->rowCount()-1,sutunIsim,itm2);
        ui->tableWidget->setItem(ui->tableWidget->rowCount()-1,sutunBanka,itm3);
        ui->tableWidget->setItem(ui->tableWidget->rowCount()-1,sutunTutar,itm4);
        ui->tableWidget->setItem(ui->tableWidget->rowCount()-1,sutunMuhatap,itm5);
        ui->tableWidget->setItem(ui->tableWidget->rowCount()-1,sutunCekNo,itm6);
        ui->tableWidget->setItem(ui->tableWidget->rowCount()-1,sutunAciklama,itm7);

        QPushButton *btnSil=new QPushButton();
        btnSil->setIcon(QIcon(QDir::currentPath()+"/icons/sil.png"));
        btnSil->setToolTip("Sil");
        btnSil->setEnabled(false);
        connect(btnSil,SIGNAL(clicked()),this,SLOT(satirSil()));
        ui->tableWidget->setCellWidget(ui->tableWidget->rowCount()-1,sutunSil,btnSil);

        QComboBox *cmb=new QComboBox();
        cmb->addItems(listeCbCekTur);
        cmb->setEnabled(false);
        ui->tableWidget->setCellWidget(ui->tableWidget->rowCount()-1,sutunTur,cmb);
        ///////////////
        //ikinci satır eklendikten sonra etkin olmayan tamam düğmesi etkinleşiyor
        if(ui->btnTamam->isEnabled()==false)
        {
            ui->btnTamam->setEnabled(true);
        }
        ////////////////
        //son satırdan bir üsteki satırın sil düğmesi ve combobox'u etkinleştiriliyor
        QPushButton* btn2=qobject_cast<QPushButton*>(ui->tableWidget->cellWidget(ui->tableWidget->rowCount()-2,sutunSil));
        btn2->setEnabled(true);

        QComboBox* cmb2=qobject_cast<QComboBox*>(ui->tableWidget->cellWidget(ui->tableWidget->rowCount()-2,sutunTur));
        cmb2->setEnabled(true);
        /////////////////

        /*
        toplamTutar=ui->lblToplamTutar->text().toDouble();
        toplamTutar=toplamTutar+ui->tableWidget->item(ui->tableWidget->rowCount()-2,ftrSutunTutar)->text().toDouble();
        ui->lblToplamTutar->setText(QString::number(toplamTutar));
        */
    }
    if(b==sutunTutar && a<ui->tableWidget->rowCount()-1)
    {
        toplamTutar=0;
        for(int i=0;i<ui->tableWidget->rowCount();i++)
        {
            toplamTutar=toplamTutar+ui->tableWidget->item(i,sutunTutar)->text().toDouble();
        }
        ui->lblToplamTutar->setText(QString::number(toplamTutar));
    }
}

void cekekle::tamam()
{
    for(int i=0;i<ui->tableWidget->rowCount()-1;i++)//son satır sürekli boş olduğu için son satırı gözardı ediyoruz
    {
        for(int j=1;j<ui->tableWidget->columnCount()-1;j++)//son sutun combobox olduğu için gözardı ediyoruz
        {
            listeCek.append(ui->tableWidget->item(i,j)->text());
        }
        QComboBox* cmb=qobject_cast<QComboBox*>(ui->tableWidget->cellWidget(i,sutunTur));//gözardı ettiğimiz combobox'ı listeye ekliyoruz
        listeCek.append(cmb->currentText());
    }
    cal->close();
    close();
}

void cekekle::kapat()
{
    close();
    toplamTutar=0;
}

QStringList cekekle::getListeCek()
{
    return listeCek;
}

double cekekle::getToplamTutar()
{
    return toplamTutar;
}

void cekekle::satirSil()
{}

//ÖNTANIMLI AYARLARI YÜKLÜYOR(SADECE UYGULAMA ÇALIŞTIRILDIĞINDA)
void cekekle::ilkYukleme()
{
    sutunSil=0;
    sutunTarih=1;
    sutunIsim=2;
    sutunBanka=3;
    sutunTutar=4;
    sutunMuhatap=5;
    sutunCekNo=6;
    sutunAciklama=7;
    sutunTur=8;

    QStringList baslik=(QStringList()<<"Sil"<<"Tarih"<<"İsim"<<"Banka"<<"Tutar"<<"Muhatap"<<"No"<<"Açıklama"<<"Tür");
    ui->tableWidget->setColumnCount(9);
    ui->tableWidget->setHorizontalHeaderLabels(baslik);
    ui->tableWidget->horizontalHeader()->setResizeMode(QHeaderView::Stretch);
    ui->tableWidget->horizontalHeader()->setResizeMode(sutunSil,QHeaderView::Custom);
    ui->tableWidget->horizontalHeader()->resizeSection(sutunSil, 32);
    this->setWindowTitle("Çek Ekle");
    cal=new QCalendarWidget();

    listeCbCekTur<<"Alınan"<<"Verilen";
}

//ÖNTANIMLI AYARLARI YÜKLÜYOR(FATURA EKLEME PENCERESİ HER AÇILDIĞINDA)
void cekekle::ontanimliAyarlar()
{
    toplamTutar=0;

    ui->tableWidget->setRowCount(0);
    takvimAcik=false;
    ui->btnTamam->setEnabled(false);
    listeCek.clear();//önceki girişleri tekrar yüklemesin diye listeyi boşaltıyoruz
    ui->lblToplamTutar->setText("0");

    //fatura ekleme ekranı açılınca tablewidget'a ilk satırı ekliyor
    ui->tableWidget->insertRow(ui->tableWidget->rowCount());
    QPushButton *btnSil=new QPushButton();
    btnSil->setIcon(QIcon(QDir::currentPath()+"/icons/sil.png"));
    btnSil->setToolTip("Sil");
    btnSil->setEnabled(false);
    connect(btnSil,SIGNAL(clicked()),this,SLOT(satirSil()));
    ui->tableWidget->setCellWidget(0,sutunSil,btnSil);

    QTableWidgetItem *itm1=new QTableWidgetItem();
    QTableWidgetItem *itm2=new QTableWidgetItem();
    QTableWidgetItem *itm3=new QTableWidgetItem();
    QTableWidgetItem *itm4=new QTableWidgetItem();
    QTableWidgetItem *itm5=new QTableWidgetItem();
    QTableWidgetItem *itm6=new QTableWidgetItem();
    QTableWidgetItem *itm7=new QTableWidgetItem();
    itm1->setFlags(Qt::ItemIsEnabled);
    ui->tableWidget->setItem(0,sutunTarih,itm1);
    ui->tableWidget->setItem(0,sutunIsim,itm2);
    ui->tableWidget->setItem(0,sutunBanka,itm3);
    ui->tableWidget->setItem(0,sutunTutar,itm4);
    ui->tableWidget->setItem(0,sutunMuhatap,itm5);
    ui->tableWidget->setItem(0,sutunCekNo,itm6);
    ui->tableWidget->setItem(0,sutunAciklama,itm7);

    QComboBox *cmb=new QComboBox();
    cmb->addItems(listeCbCekTur);
    cmb->setEnabled(false);
    ui->tableWidget->setCellWidget(0,sutunTur,cmb);
    ////////////////////////////////////////
}

cekekle::~cekekle()
{
    delete ui;
}
