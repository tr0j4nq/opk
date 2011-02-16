#include "instance.h"

int deti(QPoint &p0, QPoint &p1, QPoint &p2){
    return ((p0.x())*(p1.y())+(p1.x())*(p2.y())+(p2.x())*(p0.y())-(p2.x())*(p1.y())-(p0.x())*(p2.y())-(p1.x())*(p0.y()));
}

Instance::Instance(int number,int width,int height,int polygonsNumber,int polygonsWidth,int polygonsHeight,int polygonsMaxV)
{
            this->width=width;
            this->height=height;
            this->number=number;
            this->polygonsNumber=polygonsNumber;
            this->polygonsWidth=polygonsWidth;
            this->polygonsHeight=polygonsHeight;
            this->polygonsMaxV=polygonsMaxV;
}
void Instance::generate(){
    int counttest;
    Raptor:
    counttest=0;
    polygon.clear();
    wypukly.clear();
    this->polygons.clear();
    this->srodki.clear();
    for(int i=0;i<this->number;i++){
        double alfa=(double)1/number;
        int x,y;
        double beta=(double)(rand()%(int)(alfa*1000)+1)/1000;
        do{
            int r=rand()%((int)(sqrt((this->width/2)*(this->width/2)+(this->height/2)*(this->height/2)))-60)+rand()%50+10;
            x=r*cos(PI*2*(beta+alfa*i));
            y=r*sin(PI*2*(beta+alfa*i));
        }while(x>(this->width)/2||x<-(this->width)/2||y>(this->height)/2||y<-(this->height)/2);
        polygon<<QPoint(x,y);
    }
    for(int i=0;i<polygon.size();i++){
        if(i==0){
            if(deti(polygon[polygon.size()-1],polygon[i],polygon[i+1])<0)
                wypukly.push_back(polygon[i]);
        }else if(i<polygon.size()-1){
            if(deti(polygon[i-1],polygon[i],polygon[i+1])<0)
                wypukly.push_back(polygon[i]);
        }else if(i<polygon.size()){
            if(deti(polygon[i-1],polygon[i],polygon[0])<0)
                wypukly.push_back(polygon[i]);
        }
    }
    for(int i=0;i<this->polygonsNumber;i++){
        int xo,yo;
        int n=rand()%(polygonsMaxV-2)+3;
        double alfa=(double)1/n;
        QPolygon polygonsTemp;
        do{
            bool test=1;
            do{
                do{
                    xo=rand()%this->width-(this->width/2);
                    yo=rand()%this->height-(this->height/2);
                }while(!this->polygon.containsPoint(QPoint(xo,yo),Qt::OddEvenFill));
                polygonsTemp.resize(0);
                for(int j=0;j<n;j++){
                    double beta=(double)(rand()%(int)(alfa*100))/100;
                    int x,y,licznik=0;
                    do{
                        int r=rand()%(int)(sqrt(this->polygonsWidth*this->polygonsWidth+this->polygonsHeight*this->polygonsHeight))+5; //3 bo od 3 jest zalzenie
                        x=r*cos(PI*2*(beta+alfa*j));
                        y=r*sin(PI*2*(beta+alfa*j));
                        licznik++;
                        if(licznik>n*10){
                            do{
                                qApp->processEvents();
                                if(this->inter)
                                    return;
                                xo=rand()%this->width-(this->width/2);
                                yo=rand()%this->height-(this->height/2);
                                counttest++;
                                if (counttest>1000)goto Raptor;
                            }while(!this->polygon.containsPoint(QPoint(xo,yo),Qt::OddEvenFill));
                            polygonsTemp.clear();
                            licznik=0;
                            j=-1;
                        }
                    }while(!this->polygon.containsPoint(QPoint(x+xo,y+yo),Qt::OddEvenFill)||x>(this->polygonsWidth)/2||x<-(this->polygonsWidth)/2||y>(this->polygonsHeight)/2||y<-(this->polygonsHeight)/2);
                    if(j>=0)
                        polygonsTemp<<QPoint(x+xo,y+yo);
                }

                for(int k=0;k<i;k++){
                    QPolygon temp1=polygonsTemp,temp2=this->polygons[k];
                    if(temp1.intersected(temp2).isEmpty())
                    {
                        test=1;
//                        counttest=0;
                    }
                    else{
                        test=0;
//                        counttest++;
//                        if (counttest>200)goto Raptor;
//                        if (critical>20000) throw "Kurwa!";
                        break;
                    }
                }
            }while(!test);
        }while(!polygonsTemp.subtracted(this->polygon).isEmpty());
        this->polygons.push_back(polygonsTemp);
        this->srodki.push_back(QPoint(xo,yo));
    }

}
