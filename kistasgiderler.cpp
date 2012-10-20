#include "kistasgiderler.h"
#include "ui_kistasgiderler.h"

kistasgiderler::kistasgiderler(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::kistasgiderler)
{
    ui->setupUi(this);
    connect(ui->btnTamam,SIGNAL(clicked()),this,SLOT(tamam()));
    connect(ui->btnIptal,SIGNAL(clicked()),this,SLOT(iptal()));
    connect(ui->cbTarih,SIGNAL(clicked()),this,SLOT(tarihEtkin()));
    connect(ui->cbTutar,SIGNAL(clicked()),this,SLOT(tutarEtkin()));
    connect(ui->cbTur,SIGNAL(clicked()),this,SLOT(turEtkin()));
    connect(ui->btnTurCikar,SIGNAL(clicked()),this,SLOT(turCikar()));
    connect(ui->btnTurEkle,SIGNAL(clicked()),this,SLOT(turEkle()));
    ilkYukleme();
}

void kistasgiderler::keyPressEvent(QKeyEvent *e)
{
    if(e->key()==Qt::Key_Escape)
    {}
}

void kistasgiderler::closeEvent(QCloseEvent *event)
{
    iptal();
    event->accept();
}

void kistasgiderler::turEkle()
{
    QList <QListWidgetItem*> listeSeciliTurler=ui->txtTumTurler->selectedItems();
    for(int i=0;i<listeSeciliTurler.count();i++)
    {
        bool turEklenmis=false;
        for(int j=0;j<ui->txtSeciliTurler->count();j++)//eklenen tur zaten eklenmişmi
        {
            if(ui->txtSeciliTurler->item(j)->text()==listeSeciliTurler.at(i)->text())
            {
                turEklenmis=true;
            }
        }
        if(turEklenmis==false)
        {
            ui->txtSeciliTurler->addItem(new QListWidgetItem(listeSeciliTurler.at(i)->text()));
        }
    }
    ui->txtSeciliTurler->sortItems(Qt::AscendingOrder);
}

void kistasgiderler::turCikar()
{
    QList <QListWidgetItem*> listeSeciliTurler=ui->txtSeciliTurler->selectedItems();
    for(int i=0;i<listeSeciliTurler.count();i++)
    {
        ui->txtSeciliTurler->takeItem(ui->txtSeciliTurler->row(listeSeciliTurler.at(i)));
    }
}

double kistasgiderler::getBaslangicTutar()
{
    return ui->sbTutarBaslangic->text().toDouble();
}

double kistasgiderler::getBitisTutar()
{
    return ui->sbTutarBitis->text().toDouble();
}

QDate kistasgiderler::getBaslangicTarih()
{
    return ui->dtBaslangic->date();
}

QDate kistasgiderler::getBitisTarih()
{
    return ui->dtBitis->date();
}

QStringList kistasgiderler::getSeciliTurler()
{
    QStringList listeSeciliTurler;
    for(int i=0;i<ui->txtSeciliTurler->count();i++)
    {
        listeSeciliTurler.append(ui->txtSeciliTurler->item(i)->text());
    }
    return listeSeciliTurler;
}

bool kistasgiderler::getTutarEtkinMi()
{
    return tutarEtkinMi;
}

bool kistasgiderler::getTarihEtkinMi()
{
    return tarihEtkinMi;
}

bool kistasgiderler::getTurEtkinMi()
{
    return turEtkinMi;
}

//TAMAM VEYA İPTAL DÜĞMELERİNDEN HANGİSİNE BASILDI
bool kistasgiderler::getSecim()
{
    return secim;
}

void kistasgiderler::tamam()
{
    bool hata=false;//hata yoksa kıstas işlemi başlatsın
    if(ui->cbTarih->isChecked())
    {
        if(ui->dtBaslangic->date()>ui->dtBitis->date())
        {
            QMessageBox::warning(this,"hata","Başlangıç tarihi bitiş tarihinden sonra olamaz","Tamam");
            hata=true;
        }
    }
    else if(ui->cbTutar->isChecked())
    {
        if(ui->sbTutarBaslangic->text().toDouble()>ui->sbTutarBitis->text().toDouble())
        {
            QMessageBox::warning(this,"hata","Başlangıç tutarı bitiş tutarından yüksek olamaz","Tamam");
            hata=true;
        }
    }
    else if(ui->cbTur->isChecked())
    {
        if(ui->txtSeciliTurler->count()==0)
        {
            QMessageBox::warning(this,"hata","En az bir tür seçin","Tamam");
            hata=true;
        }
    }

    if(hata==false)
    {
        close();
        secim=true;
    }
}

void kistasgiderler::iptal()
{
    close();
    secim=false;
}

void kistasgiderler::tarihEtkin()
{
    if(ui->cbTarih->isChecked())
    {
        ui->lblTarihBaslangic->setEnabled(true);
        ui->lblTarihBitis->setEnabled(true);
        ui->dtBaslangic->setEnabled(true);
        ui->dtBitis->setEnabled(true);
        tarihEtkinMi=true;
    }
    else
    {
        ui->lblTarihBaslangic->setEnabled(false);
        ui->lblTarihBitis->setEnabled(false);
        ui->dtBaslangic->setEnabled(false);
        ui->dtBitis->setEnabled(false);
        tarihEtkinMi=false;
    }
}

void kistasgiderler::tutarEtkin()
{
    if(ui->cbTutar->isChecked())
    {
        ui->sbTutarBaslangic->setEnabled(true);
        ui->sbTutarBitis->setEnabled(true);
        tutarEtkinMi=true;
    }
    else
    {
        ui->sbTutarBaslangic->setEnabled(false);
        ui->sbTutarBitis->setEnabled(false);
        tutarEtkinMi=false;
    }
}

void kistasgiderler::turEtkin()
{
    if(ui->cbTur->isChecked())
    {
        ui->txtSeciliTurler->setEnabled(true);
        ui->txtTumTurler->setEnabled(true);
        ui->btnTurCikar->setEnabled(true);
        ui->btnTurEkle->setEnabled(true);
        ui->lblSeciliTurler->setEnabled(true);
        ui->lblTumTurler->setEnabled(true);
        turEtkinMi=true;
    }
    else
    {
        ui->txtSeciliTurler->setEnabled(false);
        ui->txtTumTurler->setEnabled(false);
        ui->btnTurCikar->setEnabled(false);
        ui->btnTurEkle->setEnabled(false);
        ui->lblSeciliTurler->setEnabled(false);
        ui->lblTumTurler->setEnabled(false);
        turEtkinMi=false;
    }
}

//ÖNTANIMLI AYARLARI YÜKLÜYOR(SADECE UYGULAMA ÇALIŞTIRILDIĞINDA)
void kistasgiderler::ilkYukleme()
{
    setWindowFlags(Qt::Window);
    ui->dtBaslangic->setDate(QDate::currentDate());
    ui->dtBitis->setDate(QDate::currentDate());

    ui->cbTarih->setChecked(false);
    ui->lblTarihBaslangic->setEnabled(false);
    ui->lblTarihBitis->setEnabled(false);
    ui->dtBaslangic->setEnabled(false);
    ui->dtBitis->setEnabled(false);

    ui->cbTutar->setChecked(false);
    ui->sbTutarBaslangic->setEnabled(false);
    ui->sbTutarBitis->setEnabled(false);

    ui->txtSeciliTurler->setEnabled(false);
    ui->txtTumTurler->setEnabled(false);
    ui->btnTurCikar->setEnabled(false);
    ui->btnTurEkle->setEnabled(false);

    tutarEtkinMi=false;
    tarihEtkinMi=false;
    turEtkinMi=false;

    ui->txtTumTurler->insertItems(0,QStringList()<<"Fatura"<<"Diğer");
    ui->txtTumTurler->sortItems(Qt::AscendingOrder);
}

//ÖNTANIMLI AYARLARI YÜKLÜYOR(MAAŞ EKLEME PENCERESİ HER AÇILDIĞINDA)
void kistasgiderler::ontanimliAyarlar()
{
    secim=false;
}

kistasgiderler::~kistasgiderler()
{
    delete ui;
}
