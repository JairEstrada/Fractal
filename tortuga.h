#include<iostream>
#include<fstream>
#include<string>
#include<stdlib.h>
#include<stdio.h>
#include<time.h>
#include<math.h>
#include <qapplication.h>
#include <qcanvas.h>

class tortuga{

	private:
        double X;
        double Y;
        double Angulo;    //radianes
      //  Color color;
      //  Graphics g;


	public:

 	tortuga(double x, double y, double angulo);
        tortuga();
        void gira(double angulo);
        void salta(double x, double y);
        void salta(double distancia);
        void traza(double distancia, QCanvas *c);

};

  tortuga::tortuga(double x, double y, double angulo) {
        X=x;
        Y=y;
        Angulo=angulo*3.1416/180;
        //color=color;
    }
   tortuga::tortuga() {
        X=0.0;
        Y=0.0;
        Angulo=0.0;
        //color=Color.black;
    }

    void tortuga::gira(double angulo){
        Angulo+=angulo*3.1416/180;
    }
    void tortuga::salta(double x, double y){
        X=x;
        Y=y;
    }
    void tortuga::salta(double distancia){
        double xx=X+distancia*cos(Angulo);
        double yy=Y-distancia*sin(Angulo);
        salta(xx, yy);
    }

    void tortuga::traza(double distancia, QCanvas *c){
        QCanvasLine *line = new QCanvasLine( c );
        double xx=X+distancia*cos(Angulo);
        double yy=Y-distancia*sin(Angulo);
        //g.setColor(color);
        //g.drawLine((int)xx, (int)yy, (int)x, (int)y);
        line->setPoints((int)xx, (int)yy, (int)X, (int)Y);//Agrega la posicion de la linea
        line->setPen( QPen(Qt::blue , 2 ) );//Agrega color y grosor a una linea
        line->show();  
        salta(xx, yy);
    }

 	


