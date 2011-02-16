#include "solve.h"

using namespace std;


Solve::Solve()
{
}

typedef struct{
    QPoint point;
    double alfa;
}punkt;

int det(QPoint &p0, QPoint &p1, QPoint &p2){
    return ((p0.x())*(p1.y())+(p1.x())*(p2.y())+(p2.x())*(p0.y())-(p2.x())*(p1.y())-(p0.x())*(p2.y())-(p1.x())*(p0.y()));
}


int skret_w_prawo(QStack<QPoint> stos,QPoint p2){
    QPoint p0;
    QPoint p1;
    p1=stos.top();
    stos.pop();
    p0=stos.top();
    stos.push(p1);
    if(det(p0,p1,p2)>0)
        return 0;
    else
        return 1;
}

QPolygon min(QPolygon poly){
    int x=9999,y=9999,z=0;
    QPolygon temp;
    for(int i=0;i<poly.size();i++){
        if(poly[i].y()<=y){
            if(poly[i].y()<y){
                y=poly[i].y();
                x=poly[i].x();
                z=i;
            }else if(poly[i].x()<x){
                y=poly[i].y();
                x=poly[i].x();
                z=i;
            }
        }
    }
    for(int i=z;i<poly.size();i++){
        temp<<poly[i];
    }
    for(int i=0;i<z;i++){
        temp<<poly[i];
    }
    return temp;
}

void quicksort_1(int x, int y,punkt *wynik){
    int i,j;
    double v;
    punkt temp;
    i=x;
    j=y;
    v=wynik[div(x+y,2).quot].alfa;
    do{
        while
                (wynik[i].alfa<v) i++;
        while
                (v<wynik[j].alfa) j--;
        if (i<=j){
            temp=wynik[i];
            wynik[i]=wynik[j];
            wynik[j]=temp;
            i++;
            j--;
        }
    }while(i<=j);
    if (x<j)
        quicksort_1(x,j,wynik);
    if (i<y)
        quicksort_1(i,y,wynik);
}

void quicksort_2(int x, int y,punkt *wynik){
    int i,j;
    double v;
    punkt temp;
    i=x;
    j=y;
    v=wynik[div(x+y,2).quot].point.x();
    do{
        while (wynik[i].point.x()<v)
            i++;
        while (v<wynik[j].point.x())
            j--;
        if (i<=j){
            temp=wynik[i];
            wynik[i]=wynik[j];
            wynik[j]=temp;
            i++;
            j--;
        }
    }while (i<=j);
    if (x<j)
        quicksort_2(x,j,wynik);
    if (i<y)
        quicksort_2(i,y,wynik);
}

void quicksort_3(int x, int y,QVector<srodek> &vec){
    int i,j;
    double v;
    i=x;
    j=y;
    v=vec[div(x+y,2).quot].l;
    do{
        while(vec[i].l<v)
            i++;
        while(v<vec[j].l)
            j--;
        if(i<=j){
            srodek temp;
            temp=vec[i];
            vec[i]=vec[j];
            vec[j]=temp;
            i++;
            j--;
        }
    }while(i<=j);
    if(x<j)
        quicksort_3(x,j,vec);
    if(i<y)
        quicksort_3(i,y,vec);
}

QPolygon alfa(QPolygon poly){
    int x,y;
    double d;
    x=poly[0].x();
    y=poly[0].y();
    punkt tempP;
    int n=poly.size();
    punkt tempV[n];
    for(int i=0;i<n;i++){
        tempP.point.setX(poly[i].x());
        tempP.point.setY(poly[i].y());
        d=abs(tempP.point.x()-x)+abs(tempP.point.y()-y);
        if(d!=0){
            if(((tempP.point.x()-x)>=0)&&((tempP.point.y()-y)>=0)){
                tempP.alfa=(double)(tempP.point.y()-y)/d;
            }else
                tempP.alfa=(double)2-(tempP.point.y()-y)/d;
        }else
            tempP.alfa=0;
        tempV[i]=tempP;
    }
    quicksort_1(1,n-1,tempV);
    int i=0,j;
    do{
        if(tempV[i].alfa==tempV[i+1].alfa){
            j=i;
            do{
                j++;
            }while(tempV[i].alfa==tempV[j].alfa);
            j--;
            quicksort_2(i,j,tempV);
            i=j;
        }else
            i++;
    }while(i<n-1);
    poly.clear();
    for(int i=0;i<n;i++){
        QPoint point;
        point.setX(tempV[i].point.x());
        point.setY(tempV[i].point.y());
        poly<<point;
    }
    return poly;
}

bool sprawdz(QPolygon &poly, Instance *in){
   if(poly.subtracted(in->polygon).isEmpty())
        return 0;
    return 1;
}

bool sprawdzDziury(QPolygon &poly, Instance *in){
    for(int i=0;i<in->otoczki.size();i++){
        if(!poly.intersected(in->polygons[i]).isEmpty())
            if(!in->polygons[i].subtracted(poly).isEmpty()){
                return 1;
            }
    }
    return 0;
}

double obwod(QPolygon &poly){
    QPoint p0,p1;
    double n=0;
    for(int i=0;i<poly.size()-1;i++){
        p0=poly[i];
        p1=poly[i+1];
        n+=(double)sqrt((p0.x()-p1.x())*(p0.x()-p1.x())+(p0.y()-p1.y())*(p0.y()-p1.y()));
    }
    p0=poly[poly.size()-1];
    p1=poly[0];
    n+=(double)sqrt((p0.x()-p1.x())*(p0.x()-p1.x())+(p0.y()-p1.y())*(p0.y()-p1.y()));
    return n;
}

int find(int x, int y,Instance *in){
    for(int i=0;i<in->tabx.size();i++){
        if(in->tabx[i]==x&&in->taby[i]==y)
            return i;
    }
    return -1;
}

double min(double a,double b){
    if(a>b)
        return b;
    else
        return a;
}

void popraw(QPolygon &figura,Instance *in){
    QPolygon temp;
    for(int i=0;i<figura.size();i++){
        qApp->processEvents();
        if(in->inter)
            return;
        int p0=find(figura[i].x(),figura[i].y(),in);
        int p1=find(figura[(i+1)%figura.size()].x(),figura[(i+1)%figura.size()].y(),in);
        if(in->drogi[p0][0]==-1){
            QVector<int> Q;
            QVector<bool> S;
            for(int j=0;j<in->tabx.size();j++){
                Q.push_back(j);
                S.push_back(false);
            }
            for(int j=0;j<in->tabx.size();j++){
                if(j==p0)
                    in->drogi[p0][j]=0;
                else
                    in->drogi[p0][j]=999999;
            }
            while(!Q.empty()){
                double mini=in->drogi[p0][Q[0]];
                int v=Q[0],vv=0;
                for(int j=1;j<Q.size();j++){
                    if(in->drogi[p0][Q[j]]<mini){
                        mini=in->drogi[p0][Q[j]];
                        v=Q[j];
                        vv=j;
                    }
                }
                S[v]=true;
                Q.remove(vv);
                for(int j=0;j<in->tabx.size();j++){
                    if(in->tab[v][j]!=999999 && !S[j]){
                        if(in->drogi[p0][j]>in->drogi[p0][v]+in->tab[j][v]){
                            in->drogi[p0][j]=in->drogi[p0][v]+in->tab[j][v];
                            in->poprzednik[p0][j]=v;
                        }
                    }
                }
            }
        }
        QStack<int> s;
        s.push(p1);
        while(p1!=p0){
            p1=in->poprzednik[p0][p1];
            s.push(p1);
        }
        while(!s.empty()){
            int t=s.pop();
            temp<<QPoint(in->tabx[t],in->taby[t]);
        }
        temp.pop_back();
    }
    figura=temp;
}

void brut(int n,Instance *in,int c,QPolygon wtf,Painter* painter){
    c+=1;
    for(int i=n;i<in->otoczki.size();i++){
        qApp->processEvents();
        if(in->inter)
            return;
        QPolygon temp;
        for(int k=0;k<wtf.size();k++)
            temp<<wtf[k];
        for(int k=0;k<in->otoczki[i].size();k++)
            temp<<in->otoczki[i][k];
        temp=min(temp);
        temp=alfa(temp);
        QStack<QPoint> s;
        s.push(temp[0]);
        s.push(temp[1]);
        s.push(temp[2]);
        for(int j=3;j<temp.size();j++){
            while(skret_w_prawo(s,temp[j]))
                            s.pop();
            s.push(temp[j]);
        }
        QPolygon tt;
        while(!s.empty())
            tt<<s.pop();
        if(obwod(tt)<in->minimum){
            if(c>=(in->polygonsNumber/2+(in->polygonsNumber%2))){
                if((sprawdz(tt,in))||(sprawdzDziury(tt,in))){
                    QPolygon pop=tt;
                    popraw(pop,in);
                    if(!in->inter && obwod(pop)<in->minimum){
                        in->otoczka=pop;
                        in->minimum=obwod(pop);
                        painter->drawSolve(in);
                        brut(i+1,in,c,tt,painter);
                    }
                }
                else{
                    in->otoczka=tt;
                    in->minimum=obwod(tt);
                    painter->drawSolve(in);
                    brut(i+1,in,c,tt,painter);
                }
            }
            else
                brut(i+1,in,c,tt,painter);
        }
    }
}

int size(int a,int b,Instance *in){
    int rozm=0;
    for(int i=0;i<a;i++)
        for(int j=0;j<in->otoczki[i].size();j++)
            rozm+=1;
    rozm+=b;
    return rozm;
}

int detSign(QPoint &a,QPoint &b, QPoint &c){
    double det=a.x()*b.y()+b.x()*c.y()+c.x()*a.y()-c.x()*b.y()-b.x()*a.y()-a.x()*c.y();
    if(det>0)
        return 1;
    else if(det==0)
        return 0;
    else
        return -1;
}

bool intersection(QPoint &begin0, QPoint &end0, QPoint &begin1, QPoint &end1){
    if(detSign(begin0,end0,begin1)!=detSign(begin0,end0,end1)&&detSign(begin1,end1,begin0)!=detSign(begin1,end1,end0))
        return true;
    else
        return false;
}

void ponumeruj(Instance* in){
    for(int i=0;i<in->otoczki.size();i++){
        for(int j=0;j<in->otoczki[i].size();j++){
            in->tabx.push_back(in->otoczki[i][j].x());
            in->taby.push_back(in->otoczki[i][j].y());
        }
    }
    for(int i=0;i<in->wypukly.size();i++){
        in->tabx.push_back(in->wypukly[i].x());
        in->taby.push_back(in->wypukly[i].y());
    }
}

double odleglosc(QPoint a,QPoint b){
    double temp=sqrt(pow(a.x()-b.x(),2)+pow(a.y()-b.y(),2));
    return temp;
}

void heurystyka(Instance* in){
    for(int i=0;i<in->heura.size();i++){
        QPolygon temp;
        for(int j=0;j<((in->heura.size()/2)+(in->heura.size()%2));j++){
            for(int k=0;k<in->otoczki[in->heura[i][j].n].size();k++){
                temp<<in->otoczki[in->heura[i][j].n][k];
            }
        }
        temp=min(temp);
        temp=alfa(temp);
        QStack<QPoint> s;
        s.push(temp[0]);
        s.push(temp[1]);
        s.push(temp[2]);
        for(int j=3;j<temp.size();j++){
            while(skret_w_prawo(s,temp[j]))
                            s.pop();
            s.push(temp[j]);
        }
        temp.clear();
        while(!s.empty())
            temp<<s.pop();
        if(obwod(temp)<in->minimum){
            if((sprawdz(temp,in))||(sprawdzDziury(temp,in))){
                popraw(temp,in);
                if(obwod(temp)<in->minimum){
                    in->minimum=obwod(temp);
                    in->otoczka=temp;
                }
            }
            else{
                in->minimum=obwod(temp);
                in->otoczka=temp;
            }
        }
    }
}

void Solve::otoczka(Instance* instance,Painter* painter){
    instance->minimum=99999999;
    int nn=instance->polygonsNumber;
    for(int i=0;i<nn;i++){//otoczki wszystkich figur
        QPolygon poly1=min(instance->polygons[i]);
        poly1=alfa(poly1);
        QStack<QPoint> s;
        s.push(poly1[0]);
        s.push(poly1[1]);
        s.push(poly1[2]);
        for(int j=3;j<poly1.size();j++){
            while(skret_w_prawo(s,poly1[j]))
                            s.pop();
            s.push(poly1[j]);
        }
        instance->otoczki.push_back(s);
    }
    ponumeruj(instance);
    int nnn=instance->tabx.size();
    instance->tab.resize(nnn);
    instance->drogi.resize(nnn);
    instance->poprzednik.resize(nnn);
    for(int i=0;i<nnn;i++){
        instance->tab[i].resize(nnn);
        instance->drogi[i].resize(nnn);
        instance->poprzednik[i].resize(nnn);
    }

    for(int i=0;i<nnn;i++){
        for(int j=0;j<nnn;j++){
            if(i==j)
                instance->tab[i][j]=0;
            else
                instance->tab[i][j]=999999;
            instance->drogi[i][j]=-1;
        }
    }
    for(int i=0;i<nnn;i++){
        for(int j=0;j<nnn;j++){
            qApp->processEvents();
            if(i!=j){
                QPoint p0=QPoint(instance->tabx[i],instance->taby[i]),
                       p1=QPoint(instance->tabx[j],instance->taby[j]);
                bool cross=false;
                for(int k=0;k<instance->polygon.size();k++){
                    QPoint p2=QPoint(instance->polygon[k].x(),instance->polygon[k].y()),
                           p3=QPoint(instance->polygon[(k+1)%instance->polygon.size()].x(),instance->polygon[(k+1)%instance->polygon.size()].y());
                    if(!(p0==p2||p0==p3||p1==p2||p1==p3)){
                        if(intersection(p0,p1,p2,p3))
                            cross=true;
                    }
                }
                for(int k=0;k<instance->polygons.size();k++){
                    for(int l=0;l<instance->polygons[k].size();l++){
                        QPoint p2=instance->polygons[k][l],
                               p3=instance->polygons[k][(l+1)%instance->polygons[k].size()];
                        if(!(p0==p2||p0==p3||p1==p2||p1==p3)){
                            if(intersection(p0,p1,p2,p3))
                                cross=true;
                        }
                    }
                }
                if(!cross){
                    instance->tab[i][j]=(double)sqrt(pow(instance->tabx[i]-instance->tabx[j],2)+pow(instance->taby[i]-instance->taby[j],2));
                    instance->tab[j][i]=instance->tab[i][j];
                }
            }
        }
    }
    for(int i=0;i<instance->otoczki.size();i++){
        for(int j=0;j<instance->otoczki[i].size();j++){
            int x=size(i,j,instance);
            for(int k=0;k<instance->otoczki[i].size();k++){
                if(k!=j && k!=((j+1)%instance->otoczki[i].size()) && k!=((j+instance->otoczki[i].size()-1)%instance->otoczki[i].size())){
                    int y=size(i,k,instance);
                    instance->tab[x][y]=999999;
                    instance->tab[y][x]=999999;
                }
            }
        }
    }

    instance->heura.resize(instance->polygons.size());

    for(int i=0;i<instance->heura.size();i++){
        for(int j=0;j<instance->heura.size();j++){
            srodek stemp;
            stemp.l=odleglosc(instance->srodki[i],instance->srodki[j]);
            stemp.n=j;
            instance->heura[i].push_back(stemp);
        }
    }
    for(int i=0;i<instance->heura.size();i++)
        quicksort_3(0,instance->heura.size()-1,instance->heura[i]);
    heurystyka(instance);
    painter->drawSolve(instance);
    qApp->processEvents();
    QPolygon pusty;
    brut(0,instance,0,pusty,painter);
}
