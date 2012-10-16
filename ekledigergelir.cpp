#include "ekledigergelir.h"
#include "ui_ekledigergelir.h"

ekledigergelir::ekledigergelir(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::ekledigergelir)
{
    ui->setupUi(this);
    connect(ui->btnKapat,SIGNAL(clicked()),this,SLOT(kapat()));
    connect(ui->btnTamam,SIGNAL(clicked()),this,SLOT(tamam()));
    connect(ui->tableWidget,SIGNAL(cellChanged(int,int)),this,SLOT(satirEkle(int,int)));
    connect(ui->tableWidget,SIGNAL(cellDoubleClicked(int,int)),this,SLOT(takvimiAc(int,int)));
    connect(ui->tableWidget,SIGNAL(cellClicked(int,int)),this,SLOT(hucreyeTiklandi(int,int)));
    ilkYukleme();
}

void ekledigergelir::keyPressEvent(QKeyEvent *e)
{
    if(e->key()==Qt::Key_Escape)
    {
        takvimAcikIseKapat();
    }
}

void ekledigergelir::closeEvent(QCloseEvent *event)
{
    kapat();
    event->accept();
}

QStringList ekledigergelir::getListeDigerGelir()
{
    return listeDigerGelir;
}

double ekledigergelir::getToplamTutar()
{
    return toplamTutar;
}

void ekledigergelir::setListeHesap(QStringList list)
{
    listeHesap=list;
}

//TAMAM DUGMESİNE TIKLANDIĞI ZAMAN ÇALIŞIYOR
void ekledigergelir::tamam()
{
    for(int i=0;i<ui->tableWidget->rowCount()-1;i++)//son satır sürekli boş olduğu için son satırı gözardı ediyoruz
    {
        for(int j=1;j<ui->tableWidget->columnCount()-1;j++)//son 1 sutun combobox olduğu için gözardı ediyoruz
        {
            listeDigerGelir.append(ui->tableWidget->item(i,j)->text());
        }
        QComboBox* cmbHesap=qobject_cast<QComboBox*>(ui->tableWidget->cellWidget(i,dglSutunHesap));//gözardı ettiğimiz combobox'ı listeye ekliyoruz
        listeDigerGelir.append(cmbHesap->currentText());
    }
    cal->close();
    close();

    qDebug()<<"listeDigerGelir:"<<listeDigerGelir;
}

void ekledigergelir::satirSil()
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
        QPushButton* btn=qobject_cast<QPushButton*>(ui->tableWidget->cellWidget(0,dglSutunSil));
        btn->setEnabled(false);

        QComboBox* cmb=qobject_cast<QComboBox*>(ui->tableWidget->cellWidget(ui->tableWidget->rowCount()-2,dglSutunHesap));
        cmb->setEnabled(false);
    }
    ////////////////////////
    */
}

void ekledigergelir::satirEkle(int a, int b)
{
    if(a==ui->tableWidget->rowCount()-1 && ui->tableWidget->item(a,b)->text()!="")//eğer değiştirilen satır son satır ise ve hücre boş bırakılmamışsa
    {
        ui->tableWidget->insertRow(ui->tableWidget->rowCount());
        QTableWidgetItem *itm1=new QTableWidgetItem();
        QTableWidgetItem *itm2=new QTableWidgetItem();
        QTableWidgetItem *itm3=new QTableWidgetItem();
        QTableWidgetItem *itm4=new QTableWidgetItem();
        QTableWidgetItem *itm5=new QTableWidgetItem();
        ui->tableWidget->setItem(ui->tableWidget->rowCount()-1,dglSutunTarih,itm1);
        ui->tableWidget->setItem(ui->tableWidget->rowCount()-1,dglSutunIsim,itm2);
        ui->tableWidget->setItem(ui->tableWidget->rowCount()-1,dglSutunKimden,itm3);
        ui->tableWidget->setItem(ui->tableWidget->rowCount()-1,dglSutunTutar,itm4);
        ui->tableWidget->setItem(ui->tableWidget->rowCount()-1,dglSutunAciklama,itm5);

        QPushButton *btnSil=new QPushButton();
        btnSil->setIcon(QIcon(QDir::currentPath()+"/icons/sil.png"));
        btnSil->setToolTip("Sil");
        btnSil->setEnabled(false);
        connect(btnSil,SIGNAL(clicked()),this,SLOT(satirSil()));
        ui->tableWidget->setCellWidget(ui->tableWidget->rowCount()-1,dglSutunSil,btnSil);

        QComboBox *cmbHesap=new QComboBox();
        cmbHesap->addItems(listeHesap);
        cmbHesap->setEnabled(false);
        ui->tableWidget->setCellWidget(ui->tableWidget->rowCount()-1,dglSutunHesap,cmbHesap);
        ///////////////
        //ikinci satır eklendikten sonra etkin olmayan tamam düğmesi etkinleşiyor
        if(ui->btnTamam->isEnabled()==false)
        {
            ui->btnTamam->setEnabled(true);
        }
        ////////////////
        //son satırdan bir üsteki satırın sil düğmesi ve combobox'u etkinleştiriliyor
        QPushButton* btn2=qobject_cast<QPushButton*>(ui->tableWidget->cellWidget(ui->tableWidget->rowCount()-2,dglSutunSil));
        btn2->setEnabled(true);

        QComboBox* cmb2=qobject_cast<QComboBox*>(ui->tableWidget->cellWidget(ui->tableWidget->rowCount()-2,dglSutunHesap));
        cmb2->setEnabled(true);
        /////////////////

        /*
        toplamTutar=ui->lblToplamTutar->text().toDouble();
        toplamTutar=toplamTutar+ui->tableWidget->item(ui->tableWidget->rowCount()-2,dglSutunTutar)->text().toDouble();
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
void ekledigergelir::takvimiAc(int a, int b)
{
    if(b==dglSutunTarih)
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
void ekledigergelir::tarihiAl()
{
    ui->tableWidget->item(satir,sutun)->setText(cal->selectedDate().toString("yyyy-MM-dd"));
    cal->close();
    takvimAcik=false;
}

//TAKVİM AÇIK İSE KAPATIYOR
void ekledigergelir::takvimAcikIseKapat()
{
    if(takvimAcik==true)
    {
        cal->close();
        takvimAcik=false;
    }
}

//TAKVİM AÇIK İKEN BOŞ BİR HÜCREYE TIKLANDIĞINDA TAKVİMİ KAPATIYOR
void ekledigergelir::hucreyeTiklandi(int a,int b)
{
    if(b!=dglSutunTarih)
    {
        takvimAcikIseKapat();
    }
}

//EKRANI KAPATIYOR
void ekledigergelir::kapat()
{
    close();
    toplamTutar=0;
}

//ÖNTANIMLI AYARLARI YÜKLÜYOR(SADECE UYGULAMA ÇALIŞTIRILDIĞINDA)
void ekledigergelir::ilkYukleme()
{
    dglSutunSil=0;
    dglSutunTarih=1;
    dglSutunIsim=2;
    dglSutunKimden=3;
    dglSutunTutar=4;
    dglSutunAciklama=5;
    dglSutunHesap=6;

    QStringList baslik=(QStringList()<<"Sil"<<"Tarih"<<"İsim"<<"Kimden"<<"Tutar"<<"Açıklama"<<"Hesap");
    ui->tableWidget->setColumnCount(7);
    ui->tableWidget->setHorizontalHeaderLabels(baslik);
    ui->tableWidget->horizontalHeader()->setResizeMode(QHeaderView::Stretch);
    ui->tableWidget->horizontalHeader()->setResizeMode(dglSutunSil,QHeaderView::Custom);
    ui->tableWidget->horizontalHeader()->resizeSection(dglSutunSil, 32);
    this->setWindowTitle("Gelir Ekle");
    cal=new QCalendarWidget();

    //listeCbFaturaTur<<"Gelen"<<"Giden";
}

//ÖNTANIMLI AYARLARI YÜKLÜYOR(GELİR EKLEME PENCERESİ HER AÇILDIĞINDA)
void ekledigergelir::ontanimliAyarlar()
{
    toplamTutar=0;//hiçbir şey girmeden kapata tıklanırsa sıfır döndürsün

    ui->tableWidget->setRowCount(0);
    takvimAcik=false;
    ui->btnTamam->setEnabled(false);
    listeDigerGelir.clear();//önceki girişleri tekrar yüklemesin diye listeyi boşaltıyoruz
    ui->lblToplamTutar->setText("0");

    //fatura ekleme ekranı açılınca tablewidget'a ilk satırı ekliyor
    ui->tableWidget->insertRow(ui->tableWidget->rowCount());
    QPushButton *btnSil=new QPushButton();
    btnSil->setIcon(QIcon(QDir::currentPath()+"/icons/sil.png"));
    btnSil->setToolTip("Sil");
    btnSil->setEnabled(false);
    connect(btnSil,SIGNAL(clicked()),this,SLOT(satirSil()));
    ui->tableWidget->setCellWidget(0,dglSutunSil,btnSil);

    QTableWidgetItem *itm1=new QTableWidgetItem();
    QTableWidgetItem *itm2=new QTableWidgetItem();
    QTableWidgetItem *itm3=new QTableWidgetItem();
    QTableWidgetItem *itm4=new QTableWidgetItem();
    QTableWidgetItem *itm5=new QTableWidgetItem();
    itm1->setFlags(Qt::ItemIsEnabled);//tarih sutunu klavye ile değişmesin
    ui->tableWidget->setItem(0,dglSutunTarih,itm1);
    ui->tableWidget->setItem(0,dglSutunTutar,itm2);
    ui->tableWidget->setItem(0,dglSutunIsim,itm3);
    ui->tableWidget->setItem(0,dglSutunAciklama,itm4);
    ui->tableWidget->setItem(0,dglSutunKimden,itm5);

    QComboBox *cmbHesap=new QComboBox();
    cmbHesap->addItems(listeHesap);
    cmbHesap->setEnabled(false);
    ui->tableWidget->setCellWidget(0,dglSutunHesap,cmbHesap);
    ////////////////////////////////////////
}

ekledigergelir::~ekledigergelir()
{
    delete ui;
}
