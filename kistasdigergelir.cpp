#include "kistasdigergelir.h"
#include "ui_kistasdigergelir.h"
#include <QDebug>

kistasdigergelir::kistasdigergelir(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::kistasdigergelir)
{
    ui->setupUi(this);
    connect(ui->btnTamam,SIGNAL(clicked()),this,SLOT(tamam()));
    connect(ui->btnIptal,SIGNAL(clicked()),this,SLOT(iptal()));
    connect(ui->cbTarih,SIGNAL(clicked()),this,SLOT(tarihEtkin()));
    connect(ui->cbTutar,SIGNAL(clicked()),this,SLOT(tutarEtkin()));
    ilkYukleme();
}

void kistasdigergelir::keyPressEvent(QKeyEvent *e)
{
    if(e->key()==Qt::Key_Escape)
    {}
}

void kistasdigergelir::closeEvent(QCloseEvent *event)
{
    iptal();
    event->accept();
}

double kistasdigergelir::getBaslangicTutar()
{
    return ui->sbTutarBaslangic->text().toDouble();
}

double kistasdigergelir::getBitisTutar()
{
    return ui->sbTutarBitis->text().toDouble();
}

QDate kistasdigergelir::getBaslangicTarih()
{
    return ui->dtBaslangic->date();
}

QDate kistasdigergelir::getBitisTarih()
{
    return ui->dtBitis->date();
}

bool kistasdigergelir::getTutarEtkinMi()
{
    return tutarEtkinMi;
}

bool kistasdigergelir::getTarihEtkinMi()
{
    return tarihEtkinMi;
}

//TAMAM VEYA İPTAL DÜĞMELERİNDEN HANGİSİNE BASILDI
bool kistasdigergelir::getSecim()
{
    return secim;
}

void kistasdigergelir::tamam()
{
    if(ui->dtBaslangic->date()>ui->dtBitis->date())
    {
        QMessageBox::warning(this,"hata","Başlangıç tarihi bitiş tarihinden sonra olamaz","Tamam");
    }
    else if(ui->sbTutarBaslangic->text().toDouble()>ui->sbTutarBitis->text().toDouble())
    {
        QMessageBox::warning(this,"hata","Başlangıç tutarı bitiş tutarından yüksek olamaz","Tamam");
    }
    else
    {
        close();
        secim=true;
    }
}

void kistasdigergelir::iptal()
{
    close();
    secim=false;
}

void kistasdigergelir::tarihEtkin()
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

void kistasdigergelir::tutarEtkin()
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

//ÖNTANIMLI AYARLARI YÜKLÜYOR(SADECE UYGULAMA ÇALIŞTIRILDIĞINDA)
void kistasdigergelir::ilkYukleme()
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

    tutarEtkinMi=false;
    tarihEtkinMi=false;
}

//ÖNTANIMLI AYARLARI YÜKLÜYOR(MAAŞ EKLEME PENCERESİ HER AÇILDIĞINDA)
void kistasdigergelir::ontanimliAyarlar()
{
    secim=false;
}

kistasdigergelir::~kistasdigergelir()
{
    delete ui;
}
