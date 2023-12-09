#include "generate_dialog.h"
#include "add_password_dialog.h"
#include "ui_generate_dialog.h"
#include <ctime>
#include <iostream>
#include <unistd.h>
Generate_dialog::Generate_dialog(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::Generate_dialog)
{
    ui->setupUi(this);
    setWindowIcon(QIcon("DG.ico"));
}

Generate_dialog::~Generate_dialog()
{
    delete ui;
}
static const char alphanum[] =
"0123456789"
"ABCDEFGHIJKLMNOPQRSTUVWXYZ"
"abcdefghijklmnopqrstuvwxyz";

static const char alphanumWithSpecials[] =
"0123456789"
"ABCDEFGHIJKLMNOPQRSTUVWXYZ"
"abcdefghijklmnopqrstuvwxyz!@#$%%^&*()_";


QString gen_random(int len)
{
   QString tmp_s;

   tmp_s.reserve(len);
   for (int i = 0; i < len; ++i)
     {
      tmp_s += alphanum[rand() % (sizeof(alphanum) - 1)];
     }
    return tmp_s;
}


QString gen_randomWithSpecials(int len)
{
   QString tmp_s;
   tmp_s.reserve(len);
   for (int i = 0; i < len; ++i)
     {
      tmp_s += alphanumWithSpecials[rand() % (sizeof(alphanumWithSpecials) - 1)];
     }
    return tmp_s;
}

int random(int min, int max) //range : [min, max]
{
   static bool first = true;
   if (first)
   {
      srand( time(NULL) ); //seeding for the first time only!
      first = false;
   }
   return min + rand() % (( max + 1 ) - min);
}


 bool Generate_dialog::is8_12Range(){
     if(ui->buttonGroup->checkedButton() == ui->short_checkbox_2 )
     {
         return true;
     }
     return false;
}

 bool Generate_dialog::is13_19Range(){
     if(ui->buttonGroup->checkedButton() == ui->middle_checkbox_2)
     {
         return true;
     }
     return false;
}

 bool Generate_dialog::is20_31Range(){
     if(ui->buttonGroup->checkedButton() == ui->long_checbox_2)
     {
         return true;
     }
     return false;
}

 bool Generate_dialog::noSpecialCharacterChecked(){
     if(ui->no_special_checkbox->isChecked())
     {
         return true;
     }
     return false;
}


int Generate_dialog::setPasswordLength()
{
    if(Generate_dialog::is8_12Range())
    {
       return random(8,12);
    }
    if(Generate_dialog::is13_19Range())
    {
         return random(13,19);
    }
    if(Generate_dialog::is20_31Range())
    {
        return  random(20,31);
    }
    return 0;
}

void Generate_dialog::on_reroll_button_clicked( )
{
    int length = setPasswordLength();

    if(noSpecialCharacterChecked())
        {
          password = gen_random(length);
        }
    else{
    password = gen_randomWithSpecials(length);
    }
    ui->paassword_label->setText(password);

}

void Generate_dialog::on_addPasswordButton_clicked()
{
   add_password_dialog  add_password_dialog;
   add_password_dialog.setModal(true);
   add_password_dialog.setPassword(ui->paassword_label->text());
   add_password_dialog.exec();

}

