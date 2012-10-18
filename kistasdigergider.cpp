#include "kistasdigergider.h"
#include "ui_kistasdigergider.h"

kistasdigergider::kistasdigergider(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::kistasdigergider)
{
    ui->setupUi(this);
    connect(ui->btnTamam,SIGNAL(clicked()),this,SLOT(tamam()));
    connect(ui->btnIptal,SIGNAL(clicked()),this,SLOT(iptal()));
    connect(ui->cbTarih,SIGNAL(clicked()),this,SLOT(tarihEtkin()));
    connect(ui->cbTutar,SIGNAL(clicked()),this,SLOT(tutarEtkin()));
    ilkYukleme();
}

void kistasdigergider::keyPressEvent(QKeyEvent *e)
{
    if(e->key()==Qt::Key_Escape)
    {}
}

void kistasdigergider::closeEvent(QCloseEvent *event)
{
    iptal();
    event->accept();
}

double kistasdigergider::getBaslangicTutar()
{
    return ui->sbTutarBaslangic->text().toDouble();
}

double kistasdigergider::getBitisTutar()
{
    return ui->sbTutarBitis->text().toDouble();
}

QDate kistasdigergider::getBaslangicTarih()
{
    return ui->dtBaslangic->date();
}

QDate kistasdigergider::getBitisTarih()
{
    return ui->dtBitis->date();
}

bool kistasdigergider::getTutarEtkinMi()
{
    return tutarEtkinMi;
}

bool kistasdigergider::getTarihEtkinMi()
{
    return tarihEtkinMi;
}

//TAMAM VEYA İPTAL DÜĞMELERİNDEN HANGİSİNE BASILDI
bool kistasdigergider::getSecim()
{
    return secim;
}

void kistasdigergider::tamam()
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

void kistasdigergider::iptal()
{
    close();
    secim=false;
}

void kistasdigergider::tarihEtkin()
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

void kistasdigergider::tutarEtkin()
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
void kistasdigergider::ilkYukleme()
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
void kistasdigergider::ontanimliAyarlar()
{
    secim=false;
}

kistasdigergider::~kistasdigergider()
{
    delete ui;
}
