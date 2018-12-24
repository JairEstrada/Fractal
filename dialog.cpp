#include "canvasgroup.h"
#include "dialog.h"
#include "tortuga.h"
#include <qcanvas.h>
#include <qpushbutton.h>
#include <qlabel.h>
#include <qlayout.h>
#include <qlineedit.h>
#include <qmessagebox.h>
#include <ctype.h>
#include <string>

Dialog::Dialog( QWidget *parent, const char *name, bool modal, WFlags f )
    : QDialog( parent, name, modal, f )
{
    setCaption( "Fractal" );
    resize(700, 500 );

    QCanvas *canvas = new QCanvas( this );
    cv = new CanvasView( canvas, this );
    QPushButton *addButton = new QPushButton( "&Dibujar", this );
    QPushButton *ungroupButton = new QPushButton( "&Menu", this );
    QPushButton *clearButton = new QPushButton( "&Limpiar", this );
    QPushButton *quitButton = new QPushButton( "&Salir", this );

    QLabel *label = new QLabel("Nivel:", this);
    valor = new QLineEdit("0", this);

    QLabel *label1 = new QLabel("Base:", this);
    base = new QLineEdit("1", this);

    QLabel *label2= new QLabel("Generador:", this);
    generador = new QLineEdit("A", this);

    QVBoxLayout *vbox = new QVBoxLayout( this );
    vbox->addWidget( cv );
    QHBoxLayout *hbox = new QHBoxLayout( 0 );
    hbox->addStretch();

    hbox->addWidget( label1 );
    hbox->addWidget( base );

    hbox->addWidget( label2 );
    hbox->addWidget( generador );

    hbox->addWidget( label );
    hbox->addWidget( valor );

    hbox->addWidget( addButton );
    hbox->addWidget( ungroupButton );
    hbox->addWidget( clearButton );
    hbox->addWidget( quitButton );

   
  
    
    vbox->addLayout( hbox );

    canvas->resize( width() - 6, height() - ( addButton->height() + 12 ) );

    connect( addButton, SIGNAL(clicked()), this, SLOT(add()) );
    connect( ungroupButton, SIGNAL(clicked()), this, SLOT(ungroup()) );
    connect( clearButton, SIGNAL(clicked()), this, SLOT(clear()) );
    connect( quitButton, SIGNAL(clicked()), this, SLOT(quit()) );
}

class curva{

  public:
  curva();
  ~curva();
  void SetVal(int ord, int Ancho, int Alto, QCanvas *C);
  void curvaKoch1(char K1);
  void curvaKoch2(char K2);
  void curvaKoch3(char K3);
  void curvaKoch4(char K4);
  void generaKoch(int nivel, double distancia);
  void generaKoch1(int nivel, double distancia);
  void generaKoch2(int nivel, double distancia);
 
  private: 
   tortuga *T;
   int wAncho;
   int wAlto;
   int orden;
   QCanvas *c; 

};

curva::curva(){
T = new tortuga; 
}

curva::~curva(){
delete T;
}

/***********************BASES**********************************/
//Base cuatro: Cuadrado
void curva::curvaKoch4(char K4){
 double  distancia=300; 

     switch (K4){  

       case 'A': 
         
          
       T->salta(150, 400);
       T->gira(90); 
       generaKoch(orden, distancia);
       T->gira(-90);        
       generaKoch(orden, distancia);
       T->gira(-90);
       generaKoch(orden, distancia);
        T->gira(-90);
       generaKoch(orden, distancia);
      
       break;
/////////////////////////////////////////////
       case 'C': 
       T->salta(150, 400);
       T->gira(90); 
       generaKoch1(orden, distancia);
       T->gira(-90);        
       generaKoch1(orden, distancia);
       T->gira(-90);
       generaKoch1(orden, distancia);
        T->gira(-90);
       generaKoch1(orden, distancia);
       break; 
 //////////////////////////////////////////////

      case 'B':
       T->salta(300,340);
       T->gira(90); 
       generaKoch2(orden, distancia);
       T->gira(-90);        
       generaKoch2(orden, distancia);
       T->gira(-90);
       generaKoch2(orden, distancia);
        T->gira(-90);
       generaKoch2(orden, distancia);
       break; 
     
      default:
         
        break; 
   }//fin de switch 
  }



//Base tres: SemiCuadrado
void curva::curvaKoch3(char K3){
         double  distancia=300;     

    switch (K3){ 
   
       case 'A':
       T->salta(150, 400);
       T->gira(90); 
       generaKoch(orden, distancia);
       T->gira(-90);        
       generaKoch(orden, distancia);
       T->gira(-90);
      generaKoch(orden, distancia);
       break;
/////////////////////////////////////////

       case 'C':
      T->salta(150, 400);
       T->gira(90); 
       generaKoch1(orden, distancia);
       T->gira(-90);        
       generaKoch1(orden, distancia);
       T->gira(-90);
      generaKoch1(orden, distancia);
       break; 
////////////////////////////////////////
       case 'B':
      T->salta(300,340);
       T->gira(90); 
       generaKoch2(orden, distancia);
       T->gira(-90);        
       generaKoch2(orden, distancia);
       T->gira(-90);
      generaKoch2(orden, distancia);
      break;

      default:
     //        QMessageBox::information(this, "Entrada no valida", "Verifique el valor de  Generador  que ingreso");
       break; 

    }//Fin de switch
  }

//Base dos: SemiTriangulo
void curva::curvaKoch2(char K2){
        double  distancia=400;     

  switch (K2){
     
     case 'A':
 
       T->salta(20, 350);
       T->gira(60);
       generaKoch(orden, distancia);
       T->gira(-120);        
       generaKoch(orden, distancia);
     break;
   
///////////////////////////////////////////
     case 'C':
       T->salta(80, 350);
       T->gira(60);
       generaKoch1(orden, distancia);
       T->gira(-120);        
       generaKoch1(orden, distancia);
      break;
//////////////////////////////////////////// 
 
     case 'B':
       T->salta(300,340);
       T->gira(60);
       generaKoch2(orden, distancia);
       T->gira(-120);        
       generaKoch2(orden, distancia); 
      break;

     default:
   //         QMessageBox::information(this, "Entrada no valida", "Verifique el valor de  Generador  que ingreso");
      break;
   }//fin del switch
  }

//Base uno Linea
void curva::curvaKoch1(char K1){
        double  distancia=500;     

     switch (K1){
       case 'A':
       T->salta(50, 350);
      generaKoch(orden, distancia);
       break;
/////////////////////////////////////////////
      case 'C':
       T->salta(50,350); 
       generaKoch1(orden, distancia);
       break;
       
/////////////////////////////////////////
      case 'B':
      T->salta(300,340); 
       generaKoch2(orden, distancia);
      break; 

      default:
     //    QMessageBox::information(this, "Entrada no valida", "Verifique el valor de  Generador  que ingreso");
       break;
    }//Fin del switch  
  }

/*************Generadores*****************************/

//Curva de Koch-Con Triangulo Equilatero
void curva::generaKoch(int nivel, double distancia){
    if(nivel==0){
        T->traza(distancia, c);
    }else{
        generaKoch(nivel-1, distancia/3);
        T->gira(60.0);
        generaKoch(nivel-1, distancia/3);
        T->gira(-120.0);
        generaKoch(nivel-1, distancia/3);
        T->gira(60.0);
       generaKoch(nivel-1, distancia/3);
    }
  }

//Curva de Koch con Cuadrado
void curva::generaKoch1(int nivel, double distancia){
    if(nivel==0){
        T->traza(distancia, c);
    }else{
        generaKoch1(nivel-1, distancia/3.2);
        T->gira(90.0);
        generaKoch1(nivel-1, distancia/3.2);
        T->gira(-90.0);
        generaKoch1(nivel-1, distancia/3.2);
        T->gira(-90.0);
        generaKoch1(nivel-1, distancia/3.2);
        T->gira(90.0);
        generaKoch1(nivel-1, distancia/3.2); 
    }
  }
 

//Curva de Koch- con semi Triangulo incompleto de un lado 
void curva::generaKoch2(int nivel, double distancia){
    if(nivel==0){
        T->traza(distancia, c);
    }else{
        T->gira(120.0);
        generaKoch2(nivel-1, distancia/1.3);
        T->gira(-120.0);
        generaKoch2(nivel-1, distancia/1.3);
        T->gira(-120.0);
        generaKoch2(nivel-1, distancia/1.8);
       
      

        }
  } 




void curva::SetVal(int ord, int Ancho, int Alto, QCanvas *C){
 wAncho=Ancho;
 wAlto=Alto;
 orden=ord;
 c=C; 

}


void Dialog::add()

{
cv->clear();//Limpia la pantalla

QString cadena ( valor->text() );
QString cadena1 ( base->text() );
QString cadena2 ( generador->text() );
QChar ch1 = cadena2.at( 0 );
char ch=ch1;
ch=toupper(ch);
//Conversion para el nivel
bool result;
short num = cadena.toShort ( &result, 10 ); //base 10


//Conversion para la base
bool result1;
short num1 = cadena1.toShort ( &result1, 10 ); //base 10

if(num >= 6){
 QMessageBox::information(this, "Advertencia", "El valor de nivel no puede ser mayor a 5, su valor será cambiando a 5");
num=5;
}
 

   QCanvas *canvas = cv->canvas();
   curva cu;
   cu.SetVal(num,450,450,canvas);
if(ch=='A' || ch=='B' || ch=='C'){
   switch (num1){
    case 4:
   cu.curvaKoch4(ch);
    break;
    
    case 3:
   cu.curvaKoch3(ch);
    break;
   
    case 2:
   cu.curvaKoch2(ch);
     break;
 
    case 1:
    cu.curvaKoch1(ch);
    break; 
   
    default://Valida en valor de la base.
     QMessageBox::information(this, "Entrada no valida", "Verifique la base que ingreso");

     break;
  } //Fin del switch 
} //Fin del if

else{
   QMessageBox::information(this, "Entrada no valida", "Verifique el generador  que ingreso");
 } 
 
 canvas->update();

}
