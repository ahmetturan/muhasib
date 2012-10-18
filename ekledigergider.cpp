#include "ekledigergider.h"
#include "ui_ekledigergider.h"

ekledigergider::ekledigergider(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::ekledigergider)
{
    ui->setupUi(this);
    connect(ui->btnKapat,SIGNAL(clicked()),this,SLOT(kapat()));
    connect(ui->btnTamam,SIGNAL(clicked()),this,SLOT(tamam()));
    connect(ui->tableWidget,SIGNAL(cellChanged(int,int)),this,SLOT(satirEkle(int,int)));
    connect(ui->tableWidget,SIGNAL(cellDoubleClicked(int,int)),this,SLOT(takvimiAc(int,int)));
    connect(ui->tableWidget,SIGNAL(cellClicked(int,int)),this,SLOT(hucreyeTiklandi(int,int)));
    ilkYukleme();
}

void ekledigergider::keyPressEvent(QKeyEvent *e)
{
    if(e->key()==Qt::Key_Escape)
    {
        takvimAcikIseKapat();
    }
}

void ekledigergider::closeEvent(QCloseEvent *event)
{
    kapat();
    event->accept();
}

QStringList ekledigergider::getListeDigerGider()
{
    return listeDigerGider;
}

double ekledigergider::getToplamTutar()
{
    return toplamTutar;
}

void ekledigergider::setListeHesap(QStringList list)
{
    listeHesap=list;
}

//TAMAM DUGMESİNE TIKLANDIĞI ZAMAN ÇALIŞIYOR
void ekledigergider::tamam()
{
    for(int i=0;i<ui->tableWidget->rowCount()-1;i++)//son satır sürekli boş olduğu için son satırı gözardı ediyoruz
    {
        for(int j=1;j<ui->tableWidget->columnCount()-1;j++)//son 1 sutun combobox olduğu için gözardı ediyoruz
        {
            listeDigerGider.append(ui->tableWidget->item(i,j)->text());
        }
        QComboBox* cmbHesap=qobject_cast<QComboBox*>(ui->tableWidget->cellWidget(i,dgdSutunHesap));//gözardı ettiğimiz combobox'ı listeye ekliyoruz
        listeDigerGider.append(cmbHesap->currentText());
    }
    cal->close();
    close();

    qDebug()<<"listeDigerGider:"<<listeDigerGider;
}

void ekledigergider::satirSil()
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
        QPushButton* btn=qobject_cast<QPushButton*>(ui->tableWidget->cellWidget(0,dgdSutunSil));
        btn->setEnabled(false);

        QComboBox* cmb=qobject_cast<QComboBox*>(ui->tableWidget->cellWidget(ui->tableWidget->rowCount()-2,dgdSutunHesap));
        cmb->setEnabled(false);
    }
    ////////////////////////
    */
}

void ekledigergider::satirEkle(int a, int b)
{
    if(a==ui->tableWidget->rowCount()-1 && ui->tableWidget->item(a,b)->text()!="")//eğer değiştirilen satır son satır ise ve hücre boş bırakılmamışsa
    {
        ui->tableWidget->insertRow(ui->tableWidget->rowCount());
        QTableWidgetItem *itm1=new QTableWidgetItem();
        QTableWidgetItem *itm2=new QTableWidgetItem();
        QTableWidgetItem *itm3=new QTableWidgetItem();
        QTableWidgetItem *itm4=new QTableWidgetItem();
        QTableWidgetItem *itm5=new QTableWidgetItem();
        ui->tableWidget->setItem(ui->tableWidget->rowCount()-1,dgdSutunTarih,itm1);
        ui->tableWidget->setItem(ui->tableWidget->rowCount()-1,dgdSutunIsim,itm2);
        ui->tableWidget->setItem(ui->tableWidget->rowCount()-1,dgdSutunKimden,itm3);
        ui->tableWidget->setItem(ui->tableWidget->rowCount()-1,dgdSutunTutar,itm4);
        ui->tableWidget->setItem(ui->tableWidget->rowCount()-1,dgdSutunAciklama,itm5);

        QPushButton *btnSil=new QPushButton();
        btnSil->setIcon(QIcon(QDir::currentPath()+"/icons/sil.png"));
        btnSil->setToolTip("Sil");
        btnSil->setEnabled(false);
        connect(btnSil,SIGNAL(clicked()),this,SLOT(satirSil()));
        ui->tableWidget->setCellWidget(ui->tableWidget->rowCount()-1,dgdSutunSil,btnSil);

        QComboBox *cmbHesap=new QComboBox();
        cmbHesap->addItems(listeHesap);
        cmbHesap->setEnabled(false);
        ui->tableWidget->setCellWidget(ui->tableWidget->rowCount()-1,dgdSutunHesap,cmbHesap);
        ///////////////
        //ikinci satır eklendikten sonra etkin olmayan tamam düğmesi etkinleşiyor
        if(ui->btnTamam->isEnabled()==false)
        {
            ui->btnTamam->setEnabled(true);
        }
        ////////////////
        //son satırdan bir üsteki satırın sil düğmesi ve combobox'u etkinleştiriliyor
        QPushButton* btn2=qobject_cast<QPushButton*>(ui->tableWidget->cellWidget(ui->tableWidget->rowCount()-2,dgdSutunSil));
        btn2->setEnabled(true);

        QComboBox* cmb2=qobject_cast<QComboBox*>(ui->tableWidget->cellWidget(ui->tableWidget->rowCount()-2,dgdSutunHesap));
        cmb2->setEnabled(true);
        /////////////////

        /*
        toplamTutar=ui->lblToplamTutar->text().toDouble();
        toplamTutar=toplamTutar+ui->tableWidget->item(ui->tableWidget->rowCount()-2,dgdSutunTutar)->text().toDouble();
        ui->lblToplamTutar->setText(QString::number(toplamTutar));
        */
    }
    /*
    if(b==sutunTutar && a<ui->tableWidget->rowCount()-1)
    {
        toplamTutar=0;
        for(int i=0;i<ui->tableWidget->rowCount();i++)
        {
            toplamTutar=toplamTutar+ui->tableWidget->item(i,sutunTutar)->text().toDouble();
        }
        ui->lblToplamTutar->setText(QString::number(toplamTutar));
    }
    */
}

//TARİH SUTUNUNA TIKLANDIĞI ZAMAN TAKVİMİ AÇIYOR
void ekledigergider::takvimiAc(int a, int b)
{
    if(b==dgdSutunTarih)
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
void ekledigergider::tarihiAl()
{
    ui->tableWidget->item(satir,sutun)->setText(cal->selectedDate().toString("yyyy-MM-dd"));
    cal->close();
    takvimAcik=false;
}

//TAKVİM AÇIK İSE KAPATIYOR
void ekledigergider::takvimAcikIseKapat()
{
    if(takvimAcik==true)
    {
        cal->close();
        takvimAcik=false;
    }
}

//TAKVİM AÇIK İKEN BOŞ BİR HÜCREYE TIKLANDIĞINDA TAKVİMİ KAPATIYOR
void ekledigergider::hucreyeTiklandi(int a,int b)
{
    if(b!=dgdSutunTarih)
    {
        takvimAcikIseKapat();
    }
}

//EKRANI KAPATIYOR
void ekledigergider::kapat()
{
    close();
    toplamTutar=0;
}

//ÖNTANIMLI AYARLARI YÜKLÜYOR(SADECE UYGULAMA ÇALIŞTIRILDIĞINDA)
void ekledigergider::ilkYukleme()
{
    dgdSutunSil=0;
    dgdSutunTarih=1;
    dgdSutunIsim=2;
    dgdSutunKimden=3;
    dgdSutunTutar=4;
    dgdSutunAciklama=5;
    dgdSutunHesap=6;

    QStringList baslik=(QStringList()<<"Sil"<<"Tarih"<<"İsim"<<"Kimden"<<"Tutar"<<"Açıklama"<<"Hesap");
    ui->tableWidget->setColumnCount(7);
    ui->tableWidget->setHorizontalHeaderLabels(baslik);
    ui->tableWidget->horizontalHeader()->setResizeMode(QHeaderView::Stretch);
    ui->tableWidget->horizontalHeader()->setResizeMode(dgdSutunSil,QHeaderView::Custom);
    ui->tableWidget->horizontalHeader()->resizeSection(dgdSutunSil, 32);
    this->setWindowTitle("Gider Ekle");
    cal=new QCalendarWidget();
}

//ÖNTANIMLI AYARLARI YÜKLÜYOR(GELİR EKLEME PENCERESİ HER AÇILDIĞINDA)
void ekledigergider::ontanimliAyarlar()
{
    toplamTutar=0;//hiçbir şey girmeden kapata tıklanırsa sıfır döndürsün

    ui->tableWidget->setRowCount(0);
    takvimAcik=false;
    ui->btnTamam->setEnabled(false);
    listeDigerGider.clear();//önceki girişleri tekrar yüklemesin diye listeyi boşaltıyoruz
    ui->lblToplamTutar->setText("0");

    //fatura ekleme ekranı açılınca tablewidget'a ilk satırı ekliyor
    ui->tableWidget->insertRow(ui->tableWidget->rowCount());
    QPushButton *btnSil=new QPushButton();
    btnSil->setIcon(QIcon(QDir::currentPath()+"/icons/sil.png"));
    btnSil->setToolTip("Sil");
    btnSil->setEnabled(false);
    connect(btnSil,SIGNAL(clicked()),this,SLOT(satirSil()));
    ui->tableWidget->setCellWidget(0,dgdSutunSil,btnSil);

    QTableWidgetItem *itm1=new QTableWidgetItem();
    QTableWidgetItem *itm2=new QTableWidgetItem();
    QTableWidgetItem *itm3=new QTableWidgetItem();
    QTableWidgetItem *itm4=new QTableWidgetItem();
    QTableWidgetItem *itm5=new QTableWidgetItem();
    itm1->setFlags(Qt::ItemIsEnabled);//tarih sutunu klavye ile değişmesin
    ui->tableWidget->setItem(0,dgdSutunTarih,itm1);
    ui->tableWidget->setItem(0,dgdSutunTutar,itm2);
    ui->tableWidget->setItem(0,dgdSutunIsim,itm3);
    ui->tableWidget->setItem(0,dgdSutunAciklama,itm4);
    ui->tableWidget->setItem(0,dgdSutunKimden,itm5);

    QComboBox *cmbHesap=new QComboBox();
    cmbHesap->addItems(listeHesap);
    cmbHesap->setEnabled(false);
    ui->tableWidget->setCellWidget(0,dgdSutunHesap,cmbHesap);
    ////////////////////////////////////////
}

ekledigergider::~ekledigergider()
{
    delete ui;
}
